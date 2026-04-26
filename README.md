# QSPICE
Some C++ simulation models for Digital Signal Processing with QSPICE

## fir_test.qsch
Load this file using [Qorvo's/Mike Engelhardt's wonderful QSPICE simulator](https://www.qorvo.com/design-hub/design-tools/interactive/qspice)

In addition you need

## fir.cpp

and

## fir59.h

Right click on the grey box and select "C++ Interface" -> "Open C++ Source"

A text editor opens

In the text editor, right click somewhere on the page and select "Compile DLL"

In the bottom line of the text editor window you will see the message ""fir.dll" created successfully"

Go back to the simulator and press the green ON switch symbol

This starts the simulation

After some seconds (depending on the speed of your PC), a diagram window pops up and shows the simulation results

## biquad_test.qsch

An example simulation file demonstrating the C-Block biquad.cpp.

The [BiQuadDesigner](https://arachnoid.com/BiQuadDesigner/index.html) written by P. Lutus was used for calculating the coefficients.

## biquad.cpp

simple biquad filter implementation

## circulator_test.qsch

This is an example simulation demonstrating the circulator subcircuit

## circulator.qsch

This isn't actually a digital circuit, but I was too lazy at the moment to add another QSpice repository just for this one analog model.

This is primitive behavioral model of a circulator. It uses only voltage controlled voltage sources and some resistors. The circuit is described in the entry [Zirkluator](https://de.wikipedia.org/wiki/Zirkulator) of the German Wikipedia.

