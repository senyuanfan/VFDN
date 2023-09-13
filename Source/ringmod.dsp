import("stdfaust.lib");

// Linearly interpolates between "wet" and "dry" signals:
mixer = (_*wet + _*(1 - wet))/2
with
{
      wet = hslider(/* label */ "Wet", /* default */ 0.5, /* min */ 0, /* max */ 1, /* increment */ 0.01);
};
      
// Ring modulation effect modulating the absolute value of the input signal with a sinusoid:
ringmod = _<: abs(_)*os.osc(freq), _  : mixer
with
{
    freq = hslider("Freq", 1000, 20, 4000, 1);
};

// Main process
process = ringmod;
