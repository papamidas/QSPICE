// Automatically generated C++ file on Sun May  3 15:14:49 2026
//
// To build with Digital Mars C++ Compiler:
//
//    dmc -mn -WD -o dds.cpp kernel32.lib

#include <malloc.h>
#define _USE_MATH_DEFINES // to enable M_PI
#include <math.h>

extern "C" __declspec(dllexport) void (*bzero)(void *ptr, unsigned int count)   = 0;

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

// #undef pin names lest they collide with names in any header file(s) you might include.
#undef clk
#undef fset
#undef ref
#undef out
#undef ph
#undef amp

struct sDDS
{
  // declare the structure here
  bool last_clk;
  unsigned long long int acc;
};

extern "C" __declspec(dllexport) void dds(struct sDDS **opaque, double t, union uData *data)
{
   bool    clk           = data[ 0].b; // input
   double  fset          = data[ 1].d; // input
   double  ref           = data[ 2].d; // input
   double  ph            = data[ 3].d; // input
   double  amp           = data[ 4].d; // input
   int     accubits      = data[ 5].i; // input parameter
   int     phoffsetbits  = data[ 6].i; // input parameter
   int     sinetabbits   = data[ 7].i; // input parameter
   int     amplitudebits = data[ 8].i; // input parameter
   int     dacbits       = data[ 9].i; // input parameter
   double &out           = data[10].d; // output

   if(!*opaque)
   {
      *opaque = (struct sDDS *) malloc(sizeof(struct sDDS));
      bzero(*opaque, sizeof(struct sDDS));
   }
   struct sDDS *inst = *opaque;

// Implement module evaluation code here:
   unsigned long long int accmod = 1ULL << accubits;
   unsigned int tw = (unsigned int)(fset * accmod);
   unsigned long long int phase_tmp, phase_sum;
   unsigned int iarg;
   double cosval;

   if (clk == true && inst->last_clk == false)
   {
       // perform a modulus addition on the phase accumulator to wrap around on overflow:
      inst->acc = (inst->acc + tw) % accmod;
      // note: the phase offset is added to the accumulator value before taking the top argbits
      // bits as the argument of the cosine function, which effectively shifts the phase
      // of the output cosine wave by the specified amount.
      // first convert phase offset from [0, 2pi) to an integer in [0, 2^phoffsetbits):
      phase_tmp = (unsigned long long int)(ph/M_PI * (1 << phoffsetbits));

      // scale phase_tmp correctly for addition to the accumulator value:
      phase_tmp <<= (accubits - phoffsetbits);

      // add the phase offset to the accumulator value and wrap around on overflow:
      phase_sum = (inst->acc + phase_tmp) % accmod;

      // take the top sinetabbits bits of the phase sum as the integer argument of the cosine function:
      iarg = phase_sum >> (accubits - sinetabbits);

      // compute the cosine value for the given integer argument:
      cosval = cos(2.0 * M_PI * iarg / (1 << sinetabbits));

      // discretize the amp input value to the specified number of amplitude bits:
      double amp_disc = floor(amp * ((1 << amplitudebits) - 1) + 0.5) / ((1 << amplitudebits) - 1);

      // apply the discretized amplitude to the cosine value:
      cosval *= amp_disc;

      // Scale and quantize/discretize cosval from [-1, 1] to the DAC output voltage [0, ref]:

      // first scale out_tmp to [0, dacmax]
      double out_tmp = (cosval + 1.0) / 2.0 * ((1 << dacbits) - 1);
      // round to nearest integer and apply reference voltage in one step to minimize rounding errors:
      out = ref * floor(out_tmp + 0.5) / ((1 << dacbits) - 1);
   }
   inst->last_clk = clk;

}

extern "C" __declspec(dllexport) void Destroy(struct sDDS *inst)
{
   free(inst);
}
