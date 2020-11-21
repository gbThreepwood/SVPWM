# SVPWM
Space vector pulse width modulator for microcontroller.

This project is intended to demonstrate various ways of generating three phase sinusoidal waveforms using PWM on a microcontroller. The Atmega 328 on the Arduino UNO is chosen for the reference implementation, although the implementation requires direct register manipulation, and not much of the drivers from the Arduino ecosystem will be used.

## Sine-PWM

The Sine-PWM modulation technique is based on comparing a sine wave to a higher frequency triangular carrier wave, and swiching off the output signal whenever the triangular wave is higher than the modulating sine wave.

## SV-PWM

Space vector PWM has some advantages over Sine-PWM. It has better utilization of the available DC-link voltage, and it directly supports commands for generating a given voltage vector, with a given phase angle.

## Square wave switching

Square wave switching provides absolute maximum utilization of the available DC-link voltage.
