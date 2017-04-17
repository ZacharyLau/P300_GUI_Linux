#include "mex.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){

  mexPrintf("hello world\n");
  mexPrintf("I have %d inputs and %d outputs\n", nrhs, nlhs);
}
