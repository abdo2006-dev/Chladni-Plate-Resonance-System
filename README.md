# Chladni Plate Resonance Demonstration System

## Overview

This repository documents the design and implementation of a Chladni plate resonance demonstration system developed as an undergraduate engineering project. The system was built to visualize standing-wave mode shapes on a metal plate by converting a digitally selected electrical excitation frequency into controlled mechanical vibration.

Fine particles placed on the plate migrate toward regions of minimal motion during resonance, forming geometric nodal patterns commonly known as Chladni figures.

The project combines embedded control, waveform generation, analog signal conditioning, power amplification, and mechanical resonance in a single interdisciplinary system.

## Authors

Experiment Conducted By:

- Aly Assaf
- Alexey Landin
- Abdulrahman Ahmed

## Project Objective

To demonstrate the relationship between excitation frequency and vibration mode shape on a Chladni plate using a digitally generated sine wave, signal-conditioning circuitry, and audio power amplification.

## System Architecture

The functional signal path is:

    Arduino Uno
    -> AD9850 DDS Generator
    -> Signal Conditioning Stage
    -> LM3875 Audio Power Amplifier
    -> Mechanical Exciter / Speaker
    -> Metal Chladni Plate

The Arduino was used to set user-selected frequencies.  
The AD9850 generated a sinusoidal waveform.  
The signal was conditioned for compatibility with the amplifier stage.  
The LM3875 provided sufficient output power to drive the transducer attached to the plate.

## Engineering Significance

Although visually simple, the project required several practical engineering decisions.

### 1. Stable Frequency Generation

Resonance behavior is highly sensitive to excitation frequency. The DDS stage provided repeatable digital control over output frequency.

### 2. Signal Conditioning

The source waveform required interface conditioning before amplification:

- DC blocking through AC coupling
- midpoint biasing for single-supply operation
- clean transfer into the amplifier input stage

### 3. Power Delivery

The low-level DDS output could not directly excite the plate. A dedicated power amplifier was required to convert the signal into useful mechanical energy.

### 4. Electromechanical Integration

The final visible result depended not only on electronics, but also on plate geometry, mounting method, exciter coupling, and particle distribution.

## Chladni Plate Theory

When a plate is driven near one of its natural frequencies, standing-wave modes are formed.

These modes contain:

- **Nodes**: regions of minimal displacement
- **Antinodes**: regions of maximum displacement

Particles move away from vibrating antinodal regions and settle along nodal lines, revealing the mode shape.

Different frequencies excite different patterns.

## Hardware Used

- Arduino Uno
- AD9850 DDS signal generator module
- LM3875 audio power amplifier
- Bench DC power supply
- Oscilloscope
- Perfboard prototype circuit
- Mechanical exciter or speaker
- Metal plate
- Sand or fine particles for visualization

## Repository Structure

    chladni-plate-resonance-system/
    ├── README.md
    ├── report/
    │   └── Chladni Plate Report.pdf
    ├── code/
    │   └── arduino_frequency_controller.ino
    ├── images/
    │   ├── final_setup.jpg
    │   ├── pattern_100hz.jpg
    │   ├── pattern_780hz.jpg
    │   ├── oscilloscope_100hz.jpg
    │   └── oscilloscope_780hz.jpg
    ├── schematics/
    │   ├── lm3875_typical_application.png
    │   ├── lm3875_single_supply_biasing.png
    │   └── arduino_ad9850_wiring.png
    └── docs/
        └── design_notes.md

## Included Documentation

### Full Technical Report

Located in the `report/` folder.

This document contains:

- project motivation
- theory of resonance and Chladni figures
- circuit design explanation
- signal-conditioning calculations
- implementation notes
- demonstration results

### Arduino Control Code

Located in the `code/` folder.

This file contains the Arduino program used to control the AD9850 and set user-selected frequencies.

### Design Notes

Located in the `docs/` folder.

This file explains the engineering reasoning behind the architecture, with emphasis on frequency generation, single-supply biasing, signal conditioning, and system-level design choices.

## Results

The completed system successfully generated visible Chladni patterns when operated near resonant frequencies of the plate.

Observed behavior included:

- distinct nodal line formation
- changing pattern geometry with frequency
- stable excitation using sinusoidal drive
- successful interaction between digital control and analog power stages

This project was conducted as a demonstration build rather than a precision measurement experiment. No formal modal analysis or calibrated vibration data were recorded.

## Limitations

The prototype did not include:

- automated frequency sweep logging
- quantified vibration amplitude measurements
- PCB-based final hardware design
- closed-loop resonance detection
- modal simulation software comparison

## Future Improvements

Potential future developments include:

- digital frequency display
- automated sweep mode
- PCB redesign of amplifier stage
- preset resonance frequencies
- comparison of different plate geometries
- structured catalog of measured mode patterns

## Academic Value

This project demonstrates the integration of multiple engineering domains:

- Embedded Systems
- Signal Processing
- Analog Electronics
- Power Amplification
- Mechanical Vibrations
- Experimental Demonstration Methods

It serves as a practical example of how electronic systems can be used to make abstract physical phenomena directly observable.

## License

This repository is shared for educational and documentation purposes.