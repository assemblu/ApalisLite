
#pragma once
#ifndef DSY_PORT_H
#define DSY_PORT_H
#ifdef __cplusplus

namespace apalis
{

class Port
{
  public:
    Port() {}
    ~Port() {}
    /** Initializes Port module

        \param sample_rate: sample rate of audio engine
        \param htime: half-time of the function, in seconds.
    */

    void Init(float sample_rate, float htime);

    /** Applies portamento to input signal and returns processed signal. 
        \return slewed output signal
    */
    float Process(float in);


    /** Sets htime
    */
    inline void SetHtime(float htime) { htime_ = htime; }
    /** returns current value of htime
    */
    inline float GetHtime() { return htime_; }

  private:
    float htime_;
    float c1_, c2_, yt1_, prvhtim_;
    float sample_rate_, onedsr_;
};
#endif
#endif
