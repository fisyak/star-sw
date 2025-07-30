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
#include <bits/stdc++.h>

// this needs to be always included
#include <DAQ_READER/daqReader.h>
#include <DAQ_READER/daq_dta.h>

void displayHelp()
{
    printf("Usage:  daqFileSorter filename\n");
}


char fn[256];
char fn_out[256];
std::vector<int> seq;

	
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
	
bool comp(int a, int b) {
    return a<b;
}

int main(int argc, char *argv[])
{
    rtsLogOutput(RTS_LOG_STDERR) ;
    rtsLogLevel((char *)WARN) ;

    if(argc != 3) {displayHelp(); exit(0); }

    daqReader *rdr = new daqReader(argv[1]);
    while(getGoodEvent(rdr) == 0) { 
	seq.push_back(rdr->seq);
    }
    delete rdr;
        
    printf("test oo\n");
    {
	int oo = 0;
	int oos = 0;
	int px = 0;
	for(auto x : seq) {
	    if(px > x) { oo++;  oos += px-x; }
	    px = x;
	}
	printf("Out of order first: %d/%d\n",oo,oos);

	if(oo == 0) {
	    printf("Nothing to do!\n");
	    exit(0);
	}
    }

    std::sort(seq.begin(), seq.end(), comp);

    {
	int oo = 0;
	int oos = 0;
	int px = 0;
	for(auto x : seq) {
	    if(px > x) { oo++;  oos += px-x; }
	    px = x;
	}
	printf("Out of order second: %d/%d\n",oo,oos);
    }
       
    rdr = new daqReader(argv[1]);
    int fd = open(argv[2], O_CREAT | O_WRONLY, 0666);
    if(fd < 0) {
	printf("Error opening file: %s\n", argv[2]);
	exit(0);
    }
    
    for(auto x : seq) {
	while(x != (int)rdr->seq) {
	    int ret = getGoodEvent(rdr);
	    if(ret != 0) {
		//printf("Have to delete reader looking for %d\n", x);
		delete rdr;
		rdr = new daqReader(argv[1]);
	    }
	}
	
	int ret = write(fd, rdr->memmap->mem, rdr->event_size);
	if(ret < 0) {
	    printf("Error writing to file %s (%s)\n", argv[2], strerror(errno));
	}
	
    }
    
    delete rdr;	      
}

