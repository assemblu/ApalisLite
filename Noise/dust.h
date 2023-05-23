#pragma once
#ifndef DSY_DUST_H
#define DSY_DUST_H
#include <cstdlib>
#include <random>
#include "Utility/dsp.h"
#ifdef __cplusplus

/** @file dust.h */

namespace apalis
{

class Dust
{
  public:
    Dust() {}
    ~Dust() {}

    void Init() { SetDensity(.5f); }

    float Process()
    {
        float inv_density = 1.0f / density_;
        float u           = rand() * kRandFrac;
        if(u < density_)
        {
            return u * inv_density;
        }
        return 0.0f;
    }

    void SetDensity(float density)
    {
        density_ = fclamp(density, 0.f, 1.f);
        density_ = density_ * .3f;
    }

  private:
    float                  density_;
    static constexpr float kRandFrac = 1.f / (float)RAND_MAX;
};
#endif
#endif
