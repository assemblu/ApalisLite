#pragma once
#ifndef DSY_CLOCKEDNOISE_H
#define DSY_CLOCKEDNOISE_H

#include <stdint.h>
#ifdef __cplusplus

/** @file clockednoise.h */

namespace apalis
{

class ClockedNoise
{
  public:
    ClockedNoise() {}
    ~ClockedNoise() {}

    /** Initialize module    
        \param sample_rate Audio engine sample rate
    */
    void Init(float sample_rate);

    /** Get the next floating point sample */
    float Process();

    /** Set the frequency at which the next sample is generated.
        \param freq Frequency in Hz
    */
    void SetFreq(float freq);

    /** Calling this forces another random float to be generated */
    void Sync();

  private:
    float phase_;
    float sample_;
    float next_sample_;

    float frequency_;

    float sample_rate_;

    static constexpr float kRandFrac = 1.f / (float)RAND_MAX;
};
#endif
#endif
