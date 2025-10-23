# Garfield++

Garfield++ is a toolkit for the detailed simulation of detectors which use gases or semi-conductors as sensitive medium. The main area of application is currently in micropattern gaseous detectors.

Garfield++ shares functionality with [Garfield](http://cern.ch/garfield). The main differences are the more up-to-date treatment of electron transport in gases, the inclusion of semiconductor detectors and the user interface, which is derived from ROOT.

[More...](http://garfieldpp.docs.cern.ch/)

## Building the project

### Options

`GARFIELD_WITH_CUDA`: Build CUDA code if possible `OFF` by default

`GARFIELD_CUDA_USE_FLOAT`: Use float with CUDA code (for some performances issues on some hardware)" `double` by default

`GARFIELD_WITH_DEGRADE`: Build Degrade `ON` by default

`GARFIELD_WITH_EXAMPLES`: Build Garfield++ examples `ON` by default

`GARFIELD_WITH_TESTS`: Build Garfield++ tests `ON` by default

For simplicity, we define an environment variable `$GARFIELD_HOME` 
pointing to the directory to which we cloned the repository. 
Assuming that `$GARFIELD_HOME` is your current working directory,
you can build and install Garfield++ as follows:

```bash
    mkdir build
    cd build
    cmake [-DCMAKE_INSTALL_PREFIX=<installdir>] [-DGARFIELD_WITH_DOC=ON] [-DGARFIELD_WITH_EXAMPLES=ON] <path to sources>
    make -j<number of cores on your machine>
    make install
```

If `CMAKE_INSTALL_PREFIX` is not provided in the configuration command, `$GARFIELD_HOME/install` will be used as installation prefix. The `GARFIELD_WITH_DOC` variable is optional, and should be passed if you wish to
build the Doxygen based API documentation. Please note that this requires an existing
installation of [Doxygen](http://www.doxygen.org/index.html). If CMake cannot locate
Doxygen, its install location should be added into `CMAKE_PREFIX_PATH`.
For further details please have a look at [the CMake tutorial](http://www.cmake.org/cmake-tutorial/).

## Building the documentation

The documentation of the project is based on doxygen. To build the documentation,
the project must have been configured with `GARFIELD_WITH_DOC` enabled, as
described earlier. It can then be built and installed:

```bash
    make doc
    make install
```

By default, this installs the documentation into `<installdir>/share/doc/HSFTEMPLATE/share/doc`.

## Running the examples

You can run the examples from the build directory (if WITH_EXAMPLES has been turned on) but you need to setup a running environment defining some variables, in particular for the HEED database.

In the following lines we use the GEM example (assuming that the build folder is our current working directory):

```bash
source setupGarfield.sh
cd Examples/Gem
./gem
```

Alternatively, thanks to PyROOT, you can use the Garfield++ classes from Python`. Assuming again that the build folder is our current working directory we can run the GEM example like this:

```bash
source setupGarfield.sh
cd Examples/Gem
python3 -i gem.py
```

## Building and running examples using an installed version of Garfield

Make sure that all required environment variables are set by sourcing the script `setupGarfield.sh`:

```bash
source $GARFIELD_HOME/install/share/Garfield/setupGarfield.sh
```

To get started, it can be useful to copy one of the examples to 
a local directory, modify it, build it against an installed version of Garfield and run it.

```bash
cp -r $GARFIELD_HOME/Examples/Gem .
mkdir Gem/build; cd Gem/build
cmake ..
make
./gem
```  

## Inclusion into other projects

If you want to build your own project against Garfield, CMake may be the best option for you. Just add its location to _CMAKE_PREFIX_PATH_ and call _find_package(Garfield)_ within your CMakeLists.txt.

```cmake
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(test)

if(NOT TARGET Garfield::Garfield)
  find_package(Garfield REQUIRED)
endif()

add_executable(test test.C)
target_link_libraries(test Garfield::Garfield)
```
