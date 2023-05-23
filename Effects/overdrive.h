#pragma once
#ifndef DSY_OVERDRIVE_H
#define DSY_OVERDRIVE_H

#include <stdint.h>
#ifdef __cplusplus

/** @file overdrive.h */

namespace apalis
{

class Overdrive
{
  public:
    Overdrive() {}
    ~Overdrive() {}

    /** Initializes the module with 0 gain */
    void Init();

    /** Get the next sample
      \param in Input to be overdriven
    */
    float Process(float in);

    /** Set the amount of drive
          \param drive Works from 0-1
      */
    void SetDrive(float drive);

  private:
    float drive_;
    float pre_gain_;
    float post_gain_;
};
#endif
#endif