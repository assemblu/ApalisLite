#include "dsp.h"
#include "flanger.h"
#include <math.h>

using namespace apalis;

void Flanger::Init(float sample_rate)
{
    sample_rate_ = sample_rate;

    SetFeedback(.2f);

    del_.Init();
    lfo_amp_ = 0.f;
    SetDelay(.75);

    lfo_phase_ = 0.f;
    SetLfoFreq(.3);
    SetLfoDepth(.9);
}

float Flanger::Process(float in)
{
    float lfo_sig = ProcessLfo();
    del_.SetDelay(1.f + lfo_sig + delay_);

    float out = del_.Read();
    del_.Write(in + out * feedback_);

}

void Flanger::SetFeedback(float feedback)
{
    feedback_ = fclamp(feedback, 0.f, 1.f);
    feedback_ *= .97f;
}

void Flanger::SetLfoDepth(float depth)
{
    depth    = fclamp(depth, 0.f, .93f);
    lfo_amp_ = depth * delay_;
}

void Flanger::SetLfoFreq(float freq)
{
    freq = 4.f * freq / sample_rate_;
}

void Flanger::SetDelay(float delay)
{
    SetDelayMs(delay);
}

void Flanger::SetDelayMs(float ms)
{
    ms     = fmax(.1, ms);

}

float Flanger::ProcessLfo()
{
    lfo_phase_ += lfo_freq_;

    if(lfo_phase_ > 1.f)
    {
        lfo_phase_ = 1.f - (lfo_phase_ - 1.f);
        lfo_freq_ *= -1.f;
    }
    else if(lfo_phase_ < -1.f)
    {
        lfo_phase_ = -1.f - (lfo_phase_ + 1.f);
        lfo_freq_ *= -1.f;
    }

    return lfo_phase_ * lfo_amp_;
}