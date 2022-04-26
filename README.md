# README #

This is a collection of C++ classes useful when working on older 
compilers with no STL support.


## Content ##
* **Array** : growing Array implemented as a template class.
* **ErrorCollector** : Allows to add error messages subsequently and can
                       print a composed error message
* **LinkedList** : linear list implementation
* **SimpleString** : basic string class

## Development environment
### Dependencies
To build the project a Linux system and the following tools are needed:
- gcc >= 6 (e.g. on Debian install the package 'build-essential')
- *Boost developer libs* : (e.g. on Debian libboost-all-dev)
- cmake >= 2.8

### Setup
The project can be build using cmake:

First create a directory *build* parallel to the *src* directory and 
enter it.

Then call cmake to let cmake create the Makefile

    cmake ..

**NOTE:** If you want to debug with e.g. VisualStudioCode type instead:

    cmake -DCMAKE_BUILD_TYPE=Debug ..

After this the project can be compiled from within the build directory 
by calling

    make

### Build with VisualStudioCode

The included .vscode/tasks.json is set up to build automatically if you
hit *Ctrl + Shift + b* in VSCode. After the successful build the binary 
is copied to the project root dir.

### Debug with VisualStudioCode

The included .vscode/launch.json is set up to start debugging the binary
in the project root dir by hitting *F5* from inside VSCode.
