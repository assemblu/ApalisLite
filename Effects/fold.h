#pragma once
#ifndef DSY_FOLD_H
#define DSY_FOLD_H

#include <stdint.h>
#ifdef __cplusplus

namespace apalis
{

class Fold
{
  public:
    Fold() {}
    ~Fold() {}
    /** Initializes the fold module.
    */
    void Init();


    /** applies foldover distortion to input 
    */
    float Process(float in);


    /** 
        \param incr : set fold increment
    */
    inline void SetIncrement(float incr) { incr_ = incr; }

  private:
    float incr_, index_, value_;
    int   sample_index_;
};
#endif
#endif
