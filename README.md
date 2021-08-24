# VSPP
This repository contains the instances and code used in our paper "Vessel Service Planning in Seaports".
## INTRODUCTION:
- Code supplement for the paper "Vessel Service Planning in Seaports" by Lingxiao Wu, Yossiri Adulyasak, Jean-François Cordeau, and Shuaian Wang.
- If you need help using the code, please send an email to lingxiaowu513[at]gmail[dot]com.

## REQUIREMENTS:
- Visual Studio 10.0 or higher (https://visualstudio.microsoft.com).
- CPLEX 12.6 or higher (https://www.ibm.com/analytics/cplex-optimizer).
- See how to write C++ applications using CPLEX with Concert Technology (https://www.ibm.com/docs/en/icos/12.7.1.0?topic=tutorials-tutorial). 

## DATASETS:
- The instance data are provided in the folder "data". 
- For a detailed explanation of the instance data, find the "README" file in the folder "data". 

## CODE:
- Code of all algorithms used in our computational experiments is provided in the folder "sourcecode". 
- List of .cpp files in the subfolder "src":
  1. BPBC_ALL：   the BPBC approach with all enhancements
  2. BPBC_DCG：   the BPBC approach with dynamic constraint generation but without all the other enhancements
  3. BPBC_NODCG: the BPBC approach without dynamic constraint generation but with all the other enhancements
  4. BPBC_NOLBL: the BPBC approach without LBL cuts but with all the other enhancements
  5. BPBC_NONE：  the BPBC approach with no enhancements
  6. BPBC_NOPH：  the BPBC approach without primal heuristics but with all the other enhancements
  7. BPBC_NOVF:  the BPBC approach without variable fixing but with all the other enhancements
  8. BPBC_NOWS:  the BPBC approach without warm start but with all the other enhancements
  9. CPLEX_M1:   CPLEX on model M1 
  10.CPLEX_SM1:  CPLEX on model SM1
  11.SEQOPT:     the sequential optimization method
  12.TPBC:       the TPBC approach

- List of .h files in the subfolder "inc":
  1. Selfmath.h:         user-defined c++ library header file for two functions

## USAGE:
- To run an algorithm for solving an instance:
  1. Create a C++ project in Visual Studio;
  2. Compile C++ project with CPLEX in Concert Technology;
  3. Load Selfmath.h and the .cpp file of the algorithm into the project;
  4. Copy the instance data from the "data" folder;
  5. Load the data into the code for the algorithm between lines "//input data starts here" and "//input data ends here";
  6. Build and run the code;
  7. Obtain the results from the console window.
