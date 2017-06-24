# cvrp
This is a solution for Capacitated Vehicle Routing Problem

## How to build
clone this repository and run "make" command in the project/src directory.
Then run 'cvrp.exe \<inputFile\>'

## How to build unit tests

### Requirements
1. you will need to download the latest googletest source from https://github.com/google/googletest
2. you will need 'pthread' library installed on your computer

Once you are ready with the requirements, only thing you need to do is update "GTEST_DIR" and "GMOCK_DIR" variables in Makefile with the path of googletest and googlemock directories where you have downloaded it on your computer.

Now you can run 'make' command in unitTest directory and run 'cvrpUnittest.exe'