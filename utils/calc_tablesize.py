#!/usr/bin/python3

from math import sin,floor

virtual_bits = 48
bitrange = pow(2,48)
low_hz = 30
sample_rate = 96000

inputs = {};

for x in range(0,sample_rate*low_hz):
    val = floor(bitrange*((sin( x/sample_rate * low_hz )+1)/2))
    inputs[val] = 1;

print(len(inputs.keys()))


