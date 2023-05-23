#include "dsp.h"
#include "sampleratereducer.h"
#include <math.h>

using namespace apalis;
void SampleRateReducer::Init()
{
    frequency_       = .2f;
    phase_           = 0.0f;
    sample_          = 0.0f;
    next_sample_     = 0.0f;
    previous_sample_ = 0.0f;
}

float SampleRateReducer::Process(float in)
{
    float this_sample = next_sample_;
    next_sample_      = 0.f;
    phase_ += frequency_;
    if(phase_ >= 1.0f)
    {
        phase_ -= 1.0f;
        float t = phase_ / frequency_;
        float new_sample
            = previous_sample_ + (in - previous_sample_) * (1.0f - t);
        float discontinuity = new_sample - sample_;
        this_sample += discontinuity * ThisBlepSample(t);
        next_sample_ = discontinuity * NextBlepSample(t);
        sample_      = new_sample;
    }
    next_sample_ += sample_;
    previous_sample_ = in;

    return this_sample;
}

void SampleRateReducer::SetFreq(float frequency)
{
    frequency_ = fclamp(frequency, 0.f, 1.f);
}
