# Project Scope and Next Steps

## What this project is

A functional engineering demonstration: a system that takes a digitally selected frequency and turns it into a visible Chladni pattern on a metal plate, built to show how excitation frequency determines vibration mode shape and why signal conditioning matters when interfacing a digital signal source to a single-supply power amplifier.

## What this project is not

Not a calibrated measurement instrument, not a modal-analysis platform, and not a finished consumer product. No frequency-response curve, quality factor, or vibration amplitude was ever numerically measured — see [experiment-and-results.md](experiment-and-results.md) for exactly what evidence exists and what it supports.

## Current limitations

- Prototype circuit on perfboard/breadboard, not a PCB.
- No automated frequency sweep or resonance search — frequencies are entered manually.
- No quantified vibration amplitude, frequency-response, or Q measurements.
- No modal simulation (e.g., FEA) comparison against the observed patterns.
- Firmware in this repository is a reconstruction for documentation, not the exact code that ran during the original demonstration (see [firmware.md](firmware.md)).
- No schematic capture of the as-built single-supply biasing circuit — only the report's equations and a redrawn explanatory diagram exist (see [hardware-design.md](hardware-design.md)).
- DDS module identity has a documentation inconsistency (one photo annotation says AD9833 against AD9850 everywhere else) — see [hardware-design.md](hardware-design.md).

## Next engineering iteration

- Add a display (OLED/LCD) showing the currently active frequency instead of relying on the Serial Monitor.
- Implement an automated sweep mode to locate resonances instead of manual entry.
- Store a set of known-resonance frequencies as presets.
- Redesign the conditioning + amplifier stage on a PCB.
- Add sensor-based measurement (accelerometer, microphone, or laser vibrometer) to get quantitative amplitude and frequency-response data instead of relying on visual pattern inspection.
- Compare different plate geometries and mounting conditions and build a small catalog of observed modes.
- Draw and publish an as-built schematic of the single-supply biasing network, rather than relying on the datasheet's split-supply reference circuit plus text description.
