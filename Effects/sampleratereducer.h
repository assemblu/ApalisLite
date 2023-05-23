#pragma once
#ifndef DSY_SR_REDUCER_H
#define DSY_SR_REDUCER_H

#include <stdint.h>
#ifdef __cplusplus

/** @file sampleratereducer.h */

namespace apalis
{

class SampleRateReducer
{
  public:
    SampleRateReducer() {}
    ~SampleRateReducer() {}

    /** Initialize the module */
    void Init();

    /** Get the next floating point sample 
        \param in Sample to be processed.
    */
    float Process(float in);

    /** Set the new sample rate.
        \param Works over 0-1. 1 is full quality, .5 is half sample rate, etc.
    */
    void SetFreq(float frequency);

  private:
    float frequency_;
    float phase_;
    float sample_;
    float previous_sample_;
    float next_sample_;
};
#endif
#endif