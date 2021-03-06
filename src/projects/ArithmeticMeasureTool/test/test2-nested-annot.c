// nested loops
#include <stdio.h>
#include <assert.h>

float A[256][256], B[256][256];
// Instrumentation 1: add a few global variables
unsigned long int chiterations = 0;
unsigned long int chloads = 0;
unsigned long int chstores = 0;
unsigned long int chflops = 0;
int main()
{
  int i, j, k; 
  chiterations =10;
  for (k=0; k<10; k++)
  {
    B[0][k]=0.0;
    //Instrumentation 2: in loop iteration count for the loop to be counted 
    chiterations =256*256;
    for (i=0; i<256; i++)
      for (j=0; j<256; j++)
        A[i][j] = B[i][j] + B[i][j+1];
  }  
  //Instrumentation 4: print out results
  printf ("chflops =%lu chloads =%lu chstores=%lu\n", chflops, chloads, chstores);
  assert (chflops==655360);
  assert (chloads==2621440);
  assert (chstores==2621480);
  return 0;
}
