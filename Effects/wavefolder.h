#pragma once
#ifndef DSY_WAVEFOFOLDER_H
#define DSY_WAVEFOFOLDER_H

#include <stdint.h>
#include "Utility/dcblock.h"
#ifdef __cplusplus

namespace apalis
{

class Wavefolder
{
  public:
    Wavefolder() {}
    ~Wavefolder() {}
    /** Initializes the wavefolder module.
    */
    void Init();
    /** applies wavefolding to input 
    */
    float Process(float in);
    /** 
        \param gain Set input gain.
        Supports negative values for thru-zero
    */
    inline void SetGain(float gain) { gain_ = gain; }
    /** 
        \param offset Offset odded to input (pre-gain) for asymmetrical folding.
    */
    inline void SetOffset(float offset) { offset_ = offset; }

  private:
    float gain_, offset_;
};
#endif
#endif
