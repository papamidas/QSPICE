# QSPICE
Some C++ simulation models for Digital Signal Processing with QSPICE

## FIR

Simulating a finite impulse response (FIR) filter

### fir_test.qsch
Load this file using [Qorvo's/Mike Engelhardt's wonderful QSPICE simulator](https://www.qorvo.com/design-hub/design-tools/interactive/qspice)

In addition you need

### fir.cpp

and

### fir59.h

Right click on the grey box and select "C++ Interface" -> "Open C++ Source"

A text editor opens

In the text editor, right click somewhere on the page and select "Compile DLL"

In the bottom line of the text editor window you will see the message ""fir.dll" created successfully"

Go back to the simulator and press the green ON switch symbol

This starts the simulation

After some seconds (depending on the speed of your PC), a diagram window pops up and shows the simulation results

## Biquad

Simulating a [digital biquad filter](https://en.wikipedia.org/wiki/Digital_biquad_filter)

### biquad_test.qsch

An example simulation file demonstrating the C-Block biquad.cpp.

The [BiQuadDesigner](https://arachnoid.com/BiQuadDesigner/index.html) written by P. Lutus was used for calculating the coefficients.

### biquad.cpp

C-Block simple biquad filter implementation

## Circulator

Simple simulation model of a [circulator](https://en.wikipedia.org/wiki/Circulator)

### circulator_test.qsch

This is an example simulation demonstrating the circulator subcircuit

### circulator.qsch

This isn't actually a digital circuit (sorry), but I was too lazy at the moment to add another QSpice repository just for this one analog model.

This is primitive behavioral model of a circulator. It uses only voltage controlled voltage sources and some resistors. The circuit is described in the entry [Zirkulator](https://de.wikipedia.org/wiki/Zirkulator) of the German Wikipedia.

## DDS

Simulation of a [direct digital synthesizer](https://de.wikipedia.org/wiki/Direct_Digital_Synthesis)

### dds_test_bare.qsch

DDS test circuit with the bare necessities

### dds.cpp

C-Block DDS implementation

### 9850_42M_fil.qsch

Reconstruction filter used on the AD9850 evaluation board

### dds_test_42M_fil.qsch

DDS test circuit with 42 MHz reconstruction filter
