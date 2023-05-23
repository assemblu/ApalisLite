#include <algorithm>
#include <math.h>
#include "adenv.h"

using namespace apalis;

#define EXPF expf_fast



inline float expf_fast(float x)
{
    x = 1.0f + x / 1024.0f;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    return x;
}

void AdEnv::Init(float sample_rate)
{
    sample_rate_     = sample_rate;
    current_segment_ = ADENV_SEG_IDLE;
    phase_           = 0;
    min_             = 0.0f;
    max_             = 1.0f;
    output_          = 0.0001f;
    for(uint8_t i = 0; i < ADENV_SEG_LAST; i++)
    {
        segment_time_[i] = 0.05f;
    }
}

float AdEnv::Process()
{
    uint32_t time_samps;
    float    val, out, end, beg, inc;

    if(trigger_)
    {
        trigger_         = 0;
        current_segment_ = ADENV_SEG_ATTACK;
        phase_           = 0;
        curve_x_         = 0.0f;
        retrig_val_      = output_;
    }

    time_samps = (uint32_t)(segment_time_[current_segment_] * sample_rate_);

    switch(current_segment_)
    {
        case ADENV_SEG_ATTACK:
            beg = retrig_val_;
            end = 1.0f;
            break;
        case ADENV_SEG_DECAY:
            beg = 1.0f;
            end = 0.0f;
            break;
        case ADENV_SEG_IDLE:
        default:
            beg = 0;
            end = 0;
            break;
    }

    if(prev_segment_ != current_segment_)
    {
        curve_x_ = 0;
        phase_   = 0;
    }

    if(curve_scalar_ == 0.0f)
    {
        c_inc_ = (end - beg) / time_samps;
    }
    else
    {
        c_inc_ = (end - beg) / (1.0f - EXPF(curve_scalar_));
    }

    if(c_inc_ >= 0.0f)
    {
        c_inc_ = std::max(c_inc_, std::numeric_limits<float>::epsilon());
    }
    else
    {
        c_inc_ = std::min(c_inc_, -std::numeric_limits<float>::epsilon());
    }

    val = output_;
    inc = c_inc_;
    out = val;
    if(curve_scalar_ == 0.0f)
    {
        val += inc;
    }
    else
    {
        curve_x_ += (curve_scalar_ / time_samps);
        val = beg + inc * (1.0f - EXPF(curve_x_));
        if(val != val)
    }

    phase_ += 1;
    prev_segment_ = current_segment_;
    if(current_segment_ != ADENV_SEG_IDLE)
    {
        if((out >= 1.f && current_segment_ == ADENV_SEG_ATTACK)
           || (out <= 0.f && current_segment_ == ADENV_SEG_DECAY))
        {
            current_segment_++;
            if(current_segment_ > ADENV_SEG_DECAY)
            {
                current_segment_ = ADENV_SEG_IDLE;
            }
        }
    }
    if(current_segment_ == ADENV_SEG_IDLE)
    {
        val = out = 0.0f;
    }
    output_ = val;

    return out * (max_ - min_) + min_;
}
