# Engineering Decisions

This document lays out the alternatives that existed at each major design point. Some comparisons were decisions actually made during the build (documented in the [project report](../report/Chladni%20Plate%20Report.pdf)); others are retrospective — comparisons that make sense to think through now, but were not necessarily weighed against real alternatives at the time. Each entry is labeled accordingly. For the day-to-day reasoning behind the choices that were made, see [`docs/design_notes.md`](design_notes.md).

## Decisions documented in the build

### DDS (AD9850) vs. an analog oscillator — *documented*
An analog oscillator (e.g., a Wien-bridge or function-generator IC) can also produce a sine wave, but tuning it precisely and repeatably to an arbitrary frequency generally requires more manual trimming and drifts more with temperature. The report states the AD9850 was chosen specifically because it "can generate stable sinusoidal waveforms over a wide frequency range with good frequency resolution," and because digital control let the team explore resonance modes quickly by entering exact frequencies.

### Sine wave vs. square wave — *documented*
A square wave is easier to generate (e.g., directly from a microcontroller pin or PWM) but contains strong harmonics, which can excite multiple vibration modes at once and blur the resulting pattern. The report is explicit that "a sine wave concentrates energy at one frequency, allowing a single vibration mode to dominate," which is why the AD9850's sine output — not its square-wave output, which the wiring schematic shows is also broken out — was used to drive the amplifier.

### Single supply vs. split supply — *documented*
The LM3875 amplifier's datasheet reference design (reproduced in this repo as `schematics/lm3875_typical_application.png`) assumes a split (±) supply. The project only had a single 24 V rail available, so the team added an AC-coupling capacitor and a resistor-divider midpoint bias to make the single-supply signal compatible with the amplifier's input range, instead of sourcing a second, negative rail. This is described as "one of the most important practical design decisions in the project" in the design notes.

## Retrospective comparisons (not decisions made during the build)

### DDS vs. PWM-generated audio
A microcontroller can synthesize an approximate sine wave using PWM plus a low-pass filter, avoiding a separate DDS module entirely. This wasn't evaluated during the build; a DDS module was used directly. In retrospect, PWM synthesis would have removed a component but likely produced a noisier, lower-fidelity waveform without careful filter design — relevant to weigh in a future revision, not a choice this project made.

### AD9850 vs. other DDS ICs (e.g., AD9833)
The AD9833 is a smaller, SPI-controlled DDS IC commonly used in low-power synthesis projects, with a simpler control interface than the AD9850's 40-bit parallel-style word. This project's documentation identifies the module used as an AD9850 throughout (see [hardware-design.md](hardware-design.md) for a note on a conflicting photo annotation); an AD9833-based redesign would need a different control protocol in firmware but is a reasonable lower-part-count alternative to consider for a future revision.

### Perfboard vs. PCB
The conditioning and amplifier circuit was built on perfboard, which is fast to prototype on but has looser tolerances and a higher risk of solder-bridge shorts than a PCB. No PCB revision exists for this project. A PCB would reduce wiring risk and make the build reproducible, at the cost of a design/fabrication cycle.

### Manual serial tuning vs. an automated sweep
The firmware requires the operator to type each frequency manually. An automated sweep mode (stepping through a frequency range and pausing at each point) would make resonance-hunting faster and more systematic, but was not implemented in this project — manual entry was sufficient for exploring modes at the demonstration's scale.

### Open-loop manual tuning vs. closed-loop resonance tracking
The system has no feedback mechanism to detect when it has found a resonance — the operator visually judges pattern stability. A closed-loop system (e.g., using a vibration or current sensor to detect a peak-amplitude condition and lock onto it) is a meaningfully more advanced project and was outside this build's scope.

### Visual pattern observation vs. sensor-based modal analysis
This project validated resonance purely by watching particle migration and reading the oscilloscope — no accelerometer, microphone, or laser vibrometer was used to quantify vibration amplitude or frequency response. A sensor-instrumented version would allow real frequency-response curves and quality-factor (Q) estimates instead of qualitative pattern description; see [experiment-and-results.md](experiment-and-results.md) for exactly what was and wasn't measured.

### Speaker/transducer coupling
The exciter/speaker was mechanically coupled to the plate to transmit vibration. The report and repository do not document alternative coupling methods that were considered (e.g., piezoelectric transducers, different mounting stiffness), so no comparison is made here beyond noting that coupling method directly affects how much of the amplifier's output power actually reaches the plate as usable vibration.
