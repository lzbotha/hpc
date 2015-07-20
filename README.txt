===========================================================================================================================================
Project Directory
===========================================================================================================================================
The root directory contains a sub folder for both the sequential and parallel implementations. Within each of these directories
are all of the source files and testing directories for the respective implementation.

===========================================================================================================================================
Compiling
===========================================================================================================================================
In order to compile either the sequential or parallel version navigate to the appropriate directory and run "make" from the terminal.
In order to compile test cases navigate to either sequential/tests or parallel/tests and run "make" from the terminal.

===========================================================================================================================================
Running Code
===========================================================================================================================================
After navigating to the appropriate directory and compiling the code the median filter and binning can be run by entering the following
command:
    ./tool path/to/point/data/file output.csv GridDim FilterDim
The result will be stored in the output.csv file in the directory the code is run from.

===========================================================================================================================================
Other Makefile Commands
===========================================================================================================================================
make clean - remove all *.o files
make dist-clean - remove all *.o files and binaries

===========================================================================================================================================
Test Cases
===========================================================================================================================================
After compiling the test cases by navigating to the appropriate directory and running "make" the tests can be run by:
    ./tests


===========================================================================================================================================
Other
===========================================================================================================================================
Data for all graphs in the report can be found in the results folder in the respective .ods file. The shell scripts used to generate this 
information can be found in the root directory. Further more all text output for these tests can be found in the .txt files in the results
directory.