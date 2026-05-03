// Automatically generated C++ file on Sun Feb  9 19:33:34 2025
//
// To build with Digital Mars C++ Compiler:
//
//    dmc -mn -WD biquad.cpp kernel32.lib

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

struct sBIQUAD
{
  // declare the structure here
  double x1;
  double x2;
  double y1;
  double y2;
  bool last_clk;
};

extern "C" __declspec(dllexport) void biquad(struct sBIQUAD **opaque, double t, union uData *data)
{
   double  IN  = data[0].d; // input
   bool    CLK = data[1].b; // input
   double  a1  = data[2].d; // input parameter
   double  a2  = data[3].d; // input parameter
   double  b0  = data[4].d; // input parameter
   double  b1  = data[5].d; // input parameter
   double  b2  = data[6].d; // input parameter
   double &OUT = data[7].d; // output

   if(!*opaque)
   {
      *opaque = (struct sBIQUAD *) malloc(sizeof(struct sBIQUAD));
      bzero(*opaque, sizeof(struct sBIQUAD));
   }
   struct sBIQUAD *inst = *opaque;

// Implement module evaluation code here:

   if( CLK == 1 && inst->last_clk == 0 ) // Detect the rising edge of the clock input
   {
      OUT = b0 * IN + b1 * inst->x1 + b2 * inst->x2 - a1 * inst->y1 - a2 * inst->y2;
      inst->x2 = inst->x1;
      inst->x1 = IN;
      inst->y2 = inst->y1;
      inst->y1 = OUT;
   }

   inst->last_clk = CLK;

}

extern "C" __declspec(dllexport) void Destroy(struct sBIQUAD *inst)
{
   free(inst);
}
