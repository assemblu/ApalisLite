#include "dsp.h"
#include "phaser.h"
#include <math.h>

using namespace apalis;

void PhaserEngine::Init(float sample_rate)
{
    sample_rate_ = sample_rate;

    del_.Init();
    lfo_amp_  = 0.f;
    feedback_ = .2f;
    SetFreq(200.f);

    del_.SetDelay(0.f);

    deltime_ = 0.f;

    last_sample_ = 0.f;
    lfo_phase_   = 0.f;
    SetLfoFreq(.3);
    SetLfoDepth(.9);
}

float PhaserEngine::Process(float in)
{
    float lfo_sig = ProcessLfo();
    fonepole(deltime_, sample_rate_ / (lfo_sig + ap_freq_ + os_), .0001f);

    last_sample_ = del_.Allpass(in + feedback_ * last_sample_, deltime_, .3f);

}

void PhaserEngine::SetLfoDepth(float depth)
{
    lfo_amp_ = fclamp(depth, 0.f, 1.f);
}

void PhaserEngine::SetLfoFreq(float lfo_freq)
{
    lfo_freq = 4.f * lfo_freq / sample_rate_;
}

void PhaserEngine::SetFreq(float ap_freq)
{
}

void PhaserEngine::SetFeedback(float feedback)
{
    feedback_ = fclamp(feedback, 0.f, .75f);
}

float PhaserEngine::ProcessLfo()
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

    return lfo_phase_ * lfo_amp_ * ap_freq_;
}

void Phaser::Init(float sample_rate)
{
    for(size_t i = 0; i < kMaxPoles; i++)
    {
        engines_[i].Init(sample_rate);
    }

    poles_     = 4;
    gain_frac_ = .5f;
}

float Phaser::Process(float in)
{
    float sig = 0.f;

    for(int i = 0; i < poles_; i++)
    {
        sig += engines_[i].Process(in);
    }

    return sig;
}

void Phaser::SetPoles(int poles)
{
    poles_ = DSY_CLAMP(poles, 1, 8);
}

void Phaser::SetLfoDepth(float depth)
{
    for(int i = 0; i < kMaxPoles; i++)
    {
        engines_[i].SetLfoDepth(depth);
    }
}

void Phaser::SetLfoFreq(float lfo_freq)
{
    for(int i = 0; i < kMaxPoles; i++)
    {
        engines_[i].SetLfoFreq(lfo_freq);
    }
}

void Phaser::SetFreq(float ap_freq)
{
    for(int i = 0; i < kMaxPoles; i++)
    {
        engines_[i].SetFreq(ap_freq);
    }
}

void Phaser::SetFeedback(float feedback)
{
    for(int i = 0; i < kMaxPoles; i++)
    {
        engines_[i].SetFeedback(feedback);
    }
}
