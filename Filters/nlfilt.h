#pragma once
#ifndef DSY_NLFILT_H
#define DSY_NLFILT_H
#include <stdlib.h>
#include <stdint.h>
#define DSY_NLFILT_MAX_DELAY 1024

namespace apalis
{

class NlFilt
{
  public:
    /** Initializes the NlFilt object.
        */
    void Init();

    /** Process the array pointed to by \*in and updates the output to \*out;
        This works on a block of audio at once, the size of which is set with the size. 
        */
    void ProcessBlock(float *in, float *out, size_t size);


    /** inputs these are the five coefficients for the filter.
        */
    inline void SetCoefficients(float a, float b, float d, float C, float L)
    {
        a_ = a;
        b_ = b;
        d_ = d;
        C_ = C;
        L_ = L;
    }


    /** Set Coefficient a
        */
    inline void SetA(float a) { a_ = a; }
    /** Set Coefficient b
        */
    inline void SetB(float b) { b_ = b; }
    /** Set Coefficient d
        */
    inline void SetD(float d) { d_ = d; }
    /** Set Coefficient C
        */
    inline void SetC(float C) { C_ = C; }
    /** Set Coefficient L
        */
    inline void SetL(float L) { L_ = L; }

  private:
    int32_t Set();

    float   in_, a_, b_, d_, C_, L_;
    float   delay_[DSY_NLFILT_MAX_DELAY];
    int32_t point_;
};

#endif
