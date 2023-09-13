import("stdfaust.lib");

N = 16;
NB = 2;
BBSO = 3;


MAXDELAY = 8192; // sync w delays and prime_power_delays above
defdurs = (3.4,0.1,5.0,3.8,2.7); // NB default durations (sec), decay T60 of each channel
deffreqs = (7000,1000,2000,4000); // NB-1 default crossover frequencies (Hz)
deflens = (56.3,63.0); // 2 default min and max path lengths
defdelays = ( 1722, 1859, 690, 1870, 1449, 646, 918, 1320, 1937, 1948, 736, 1956, 1936, 1228, 1701, 712); // initial delay line lengths

loopgainmax = 1.0;

nonl = hslider("nonl [style:knob] [tooltip: nonlinear mode coupling]",
	    0, -0.999, 0.999, 0.001);

// ba.take take index starting from 1
durs = par(i, NB, ba.take(NB - i, defdurs));
freqs = par(i, NB-1, ba.take(i + 1, deffreqs));

mod_width = hslider("mod_width", 0.02, 0, 0.5, 0.01);
mod_freq = hslider("mod_freq", 5, 0, 10, 0.1);

delays = par(i,N,(2 + mod_width * os.oscrs(mod_freq)) * ba.take(i+1, defdelays));

gain = hslider("gain [unit:dB]",
		-40, -70, 20, 0.1) : ba.db2linear;

wet = hslider("wet", 0.5, 0, 1, 0.01);

rev = _ <: re.fdnrev0(MAXDELAY,delays,BBSO,freqs,durs,loopgainmax,nonl) :> _;

process = _ <: rev * wet, _ * (1 - wet) :> *(gain);
