//******************************************************
//*** Merges events from .daq files 
//*** 
//*** usage:   daqFileMerger [-omit n] -o output.daq fn1.daq fn2.daq ...
//***
//***          merges daq files. 
//***          The events in the file will be ordered such that 
//***          
//*****************************************************

#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

#include <rtsLog.h>	// for my LOG() call
#include <rtsSystems.h>
#include <vector>
#include <string>

// this needs to be always included
#include <DAQ_READER/daqReader.h>
#include <DAQ_READER/daq_dta.h>

void displayHelp()
{
    printf("Usage:  daqFileMerger -o output_fn_base -i listOfFiles file_0.daq file_1.daq ...\n");
    printf("        The files will be merged such that:\n");
    printf("                a)  The events will be (approximately!) ordered\n");
    printf("                b)  The files will of maximum 500Gb\n");
}

struct Spec {
    std::string fn;
    int file;
    unsigned int firstEvent;
    unsigned int lastEvent;
    unsigned int n_evts;
    daqReader *rdr;
};

std::vector<Spec> inputFiles;
char *outputBase = NULL;
int nowrite = 0;

void addInputFileList(char *fn) {
    char inputFile[1024];

    FILE *f = fopen(fn,"ro");
    if(!f) { 
	printf("Bad file %s\n", fn);
	exit(0);
    }

    while(fscanf(f, "%s", inputFile) == 1) {
	Spec spec;
	spec.file = 0;
	spec.firstEvent = 0;
	spec.lastEvent = 0;
	spec.n_evts = 0;
	spec.rdr = NULL;
	spec.fn = inputFile;
	inputFiles.push_back(spec);
    }
}

void parseArgs(int argc, char *argv[])
{
    int arg = 1;
    
    for(arg=1;arg<argc;arg++) {
	if(strcmp(argv[arg], "-o") == 0) {
	    arg++;
	    outputBase = argv[arg];

	    printf("outputBase: %s\n", outputBase);
	    continue;
	}
	else if(strcmp(argv[arg], "-i") == 0) {
	    arg++;
	    addInputFileList(argv[arg]);
	    continue;
	}
	else if(strcmp(argv[arg], "-n") == 0) {
	    nowrite = 1;
	    continue;
	}
	else {
	    Spec spec;
	    spec.file = 0;
	    spec.firstEvent = 0;
	    spec.lastEvent = 0;
	    spec.n_evts = 0;
	    spec.rdr = NULL;
	    spec.fn = argv[arg];
	    inputFiles.push_back(spec);
	}
    }
    
  

    if((outputBase == NULL) || (inputFiles.size() == 0)) {
	displayHelp();
	exit(0);
    }
}
	
int getGoodEvent(daqReader *rdr) {
    for(;;) {
	char *ret = rdr->get(0, EVP_TYPE_ANY);

	if(ret) {
	    if(rdr->status) continue;    // Not a good event?
	    return 0;
	}
	else {    // what happened?
	    if(rdr->status == EVP_STAT_OK) continue;
	    if(rdr->status == EVP_STAT_EOR) return 1;

	    // An error!
	    LOG(ERR, "Error reading!");
	    return -1;
	}
    }
}
	


int main(int argc, char *argv[])
{
    rtsLogOutput(RTS_LOG_STDERR) ;
    rtsLogLevel((char *)WARN) ;

    parseArgs(argc, argv);

    int cnt=0;
    for(auto &x : inputFiles) {
	printf("inputFile[%d] = %s\n", cnt++, x.fn.c_str());
    }	
    
    for(auto &x : inputFiles) {
	daqReader *rdr = new daqReader(x.fn.c_str());

	int oo = 0;
	int oos = 0;
	
	while(getGoodEvent(rdr) == 0) {
	    if(x.firstEvent == 0) x.firstEvent = rdr->seq;
	    if(rdr->seq < x.firstEvent) x.firstEvent = rdr->seq;

	    if(rdr->seq <= x.lastEvent) {
		oo++;
		oos += x.lastEvent - rdr->seq;
		//printf("OOO %10d %10d %10d\n",rdr->seq, x.lastEvent, x.lastEvent - rdr->seq);
	    }
	    if(rdr->seq > x.lastEvent)
		x.lastEvent = rdr->seq;
	    
	    x.n_evts++;
	}

	printf("%30s: %10d evts [%10d-%10d] [out of order: %d/%d]\n", x.fn.c_str(), x.n_evts, x.firstEvent, x.lastEvent, oo, oos);
	delete rdr;
    }


    if(nowrite) exit(0);

    uint32_t current_event = 0;
    uint32_t outputFileIndex = 1;
    uint64_t outputFileSize = 0;
    uint64_t maxFileSize = 10ll*1024ll*1024ll*1024ll;

    char outputFile[200];
    sprintf(outputFile, "st_%s_%07d.daq", outputBase, outputFileIndex);

    
    int output_fd = open(outputFile, O_CREAT | O_WRONLY, 0666);
    if(output_fd < 0) {
	printf("Error opening output file: %s", outputFile);
	exit(0);
    }
	
    int alldone = 0;
    while(!alldone) {
	// open appropriate files
	for(auto &x : inputFiles) {
	    //printf("x.first %d %d 0x%p\n", x.firstEvent, x.lastEvent, x.rdr);

	    if(current_event >= x.firstEvent) {
		if(x.rdr == NULL) {
		    x.rdr = new daqReader(x.fn.c_str());
		    if(getGoodEvent(x.rdr) != 0) {
			delete x.rdr;
			x.rdr = NULL;
		    }
		}
	    }

	    if(current_event >= x.lastEvent) {
		if(x.rdr != NULL) {
		    delete x.rdr;
		    x.rdr = NULL;
		}
	    }
	    
	    if(x.rdr && current_event >= x.rdr->seq) {
		//printf("write Event %d\n", x.rdr->seq);
		int ret = write(output_fd, x.rdr->memmap->mem, x.rdr->event_size);
		if(ret < 0) {
		    printf("Error writing to file %s\n", outputFile);
		}
		if(getGoodEvent(x.rdr) != 0) {
		    delete x.rdr;
		    x.rdr = NULL;
		}

		outputFileSize += x.rdr->event_size;
		if(outputFileSize > maxFileSize) {
		    printf("file %s closed (%5.2f GB)\n", outputFile, ((float)outputFileSize) / (1024.0*1024.0*1024.0));
		    close(output_fd);
		    
		    outputFileSize = 0;
		    outputFileIndex++;
		    sprintf(outputFile, "st_%s_%07d.daq", outputBase, outputFileIndex);
		    int output_fd = open(outputFile, O_CREAT | O_WRONLY, 0666);
		    if(output_fd < 0) {
			printf("Error opening output file: %s", outputFile);
			exit(0);
		    }	    

		    printf("opened file %s\n", outputFile);
		}
	    }
	}

	//printf("current event = %d\n", current_event);
	current_event++;

	alldone = 1;
	for(auto &x : inputFiles) {
	    if(current_event <= x.lastEvent) alldone = 0;
	}
    }
     
    printf("file %s closed (%5.2f GB)\n", outputFile, ((float)outputFileSize) / (1024.0*1024.0*1024.0));
    close(output_fd);	
		      
}

