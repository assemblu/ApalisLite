# Apalis
Lite version. Cross-platform (x86-64, ARM Cortex-M and A, and RISC-V) digital signal processing library. <br><br>
Full version of Apalis detects platform on compile time, and comes with native assembly instructions for specific platforms to increase efficiency and latency. Also, has dynammic adaptation to floating point and fixed point calculations as well as ability of mixing them (although latter does not seem to be handy).<br><br>
Some examples: https://soundcloud.com/polseq <br>
## How To Use
Simply add ApalisLite to your project and include each sub path as includes and source path. ApalisLite path itself contains a single header file which also should be included in the project.<br>
```cpp
#define SAMPLNG_FREQUENCY 48000
apalis::Oscillator vco;
float out = 0;

// Triggers according to sampling frequency
int InterruptCallback(void)
{
    out = vco.Process();
}

int main(void)
{
    vco.Init(SAMPLING_FREQUENCY);
    vco.SetAmp(0.0f);
    vco.SetWave(vco.WAVE_POLYBLEP_SAW);
    vco.SetFreq(440.0f);
    vco.SetAmp(1.0)f
    
    // ... setup and initialize threads and/or interrupts here
    
    while (true) {
        
    }
    
    return 0;
}
```
## Engine Modules
<ul>
    <li>Advanced envelope controller</li>
    <li>ADSR hypervisor</li>
    <li>Line segment generator</li>
    <li>Phasor controller</li>
    <li>Analog bass drum model generator</li>
    <li>Analog snare drum model generator</li>
    <li>Hihat model generator</li>
    <li>Digital bass drum model generator</li>
    <li>Digital snare drum model generator</li>
    <li>Dynamics balance engine</li>
    <li>Dynamics compressor</li>
    <li>Crossfade engine</li>
    <li>Peak limiter</li>
    <li>Auto wah</li>
    <li>Bitcrusher</li>
    <li>Chorus</li>
    <li>Decimator</li>
    <li>Flanger</li>
    <li>Signal folding</li>
    <li>Overdrive controller</li>
    <li>Phaser</li>
    <li>Pitch shift</li>
    <li>Reverberation engine and physical modeler</li>
    <li>Sample rate reducer</li>
    <li>Tremolo simulation</li>
    <li>Wave folder</li>
    <li>All-pass</li>
    <li>Biquad engine</li>
    <li>Comb filter generator</li>
    <li>FIR designer</li>
    <li>Ladder modeler</li>
    <li>Tone generator</li>
    <li>Clocked noise generator</li>
    <li>Dust particle simulator</li>
    <li>Fractal noise engine</li>
    <li>Grain engine and physical modeler</li>
    <li>Particle model simulator</li>
    <li>White noise generator</li>
    <li>Karplus string physical simulator</li>
    <li>Polyphonic pluck engine</li>
    <li>Drip generator</li>
    <li>Modal voices</li>
    <li>Pluck modeler</li>
    <li>Resonator engine</li>
    <li>String voice engine</li>
</ul>
