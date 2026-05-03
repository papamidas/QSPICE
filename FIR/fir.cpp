// Automatically generated C++ file on Sat Jan 11 17:05:40 2025
//
// To build with Digital Mars C++ Compiler:
//
//    dmc -mn -WD fir.cpp kernel32.lib

#include <malloc.h>

union uData
{
   bool b;
   char c;
   unsigned char uc;
   short s;
   unsigned short us;
   int i;
   unsigned int ui;
   float f;
   double d;
   long long int i64;
   unsigned long long int ui64;
   char *str;
   unsigned char *bytes;
};

// int DllMain() must exist and return 1 for a process to load the .DLL
// See https://docs.microsoft.com/en-us/windows/win32/dlls/dllmain for more information.
int __stdcall DllMain(void *module, unsigned int reason, void *reserved) { return 1; }

void bzero(void *ptr, unsigned int count)
{
   unsigned char *first = (unsigned char *) ptr;
   unsigned char *last  = first + count;
   while(first < last)
      *first++ = '\0';
}

// #undef pin names lest they collide with names in any header file(s) you might include.
#undef IN
#undef CLK
#undef OUT

// read in the filter coefficients:
#include "fir59.h"

struct sFIR
{
  // declare the structure here
  double last_data[NTAPS];
  int last_data_ptr;
  bool last_clk;
};

extern "C" __declspec(dllexport) void fir(struct sFIR **opaque, double t, union uData *data)
{
   double  IN  = data[0].d; // input
   bool    CLK = data[1].b; // input
   double &OUT = data[2].d; // output

   if(!*opaque)
   {
      *opaque = (struct sFIR *) malloc(sizeof(struct sFIR));
      bzero(*opaque, sizeof(struct sFIR));
   }
   struct sFIR *inst = *opaque;

// Implement module evaluation code here:

   // FIR filter for QSPICE
   // DM1CR Jan 12, 2025
   // credits to Robert Lacoste's Darker Side book!

   if( CLK == 1 && inst->last_clk == 0 ) // Detect the rising edge of the clock input
   {
      // Store input value in the circular buffer:
      inst->last_data_ptr = (inst->last_data_ptr+1) % NTAPS;
      inst->last_data[inst->last_data_ptr] = IN;
      // Calculate the convolution:
      double sum = 0;
      for(int i=0; i<NTAPS; i++)
      {
         int index = inst->last_data_ptr - i;
         if(index < 0)
         {
            index += NTAPS;
         }
         sum += COEFF[i]*inst->last_data[index];
      }
      // output the convolution result:
      OUT = sum;
   }

   inst->last_clk = CLK;

}

extern "C" __declspec(dllexport) void Destroy(struct sFIR *inst)
{
   free(inst);
}
