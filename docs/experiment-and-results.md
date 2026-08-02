# Experiment and Results

## Procedure (as described in the report)

1. The plate was coated in a light, uniform layer of salt.
2. The Arduino was used to set the AD9850 to a chosen frequency.
3. The oscilloscope was used to confirm waveform presence, approximate amplitude, and general signal quality at the amplifier stage.
4. The frequency was swept/adjusted manually while observing the salt on the plate.
5. At non-resonant frequencies, the salt distribution appeared irregular and unstable. At resonant frequencies, a sharply defined, repeatable pattern formed within seconds.

This was a **qualitative, visual validation process** — frequencies were located by ear/eye (watching the plate) rather than by an automated or instrumented resonance search, and no vibration amplitude, quality factor, or modal frequency was ever numerically measured.

## What the oscilloscope evidence shows

| Frequency | Oscilloscope reading | Vpp | Vrms | Source |
|---|---|---|---|---|
| 100 Hz | `Freq2: 100 Hz` | 18.5 V | 6.45 V | [`images/oscilloscope_100hz.png`](../images/oscilloscope_100hz.png) |
| 780 Hz | `Freq2: 780 Hz` | 19.9 V | 6.95 V | [`images/oscilloscope_780hz.png`](../images/oscilloscope_780hz.png) |

Both captures show a clean, continuous sine wave with no visible clipping, at the two frequencies the report discusses in detail.

## What the pattern photos show

- **100 Hz** ([`images/pattern_100hz.png`](../images/pattern_100hz.png)): a ring-shaped nodal boundary close to the plate's edges, consistent with the report's description of "a nearly perfect circular nodal boundary, indicating a fundamental symmetric mode."
- **780 Hz** ([`images/pattern_780hz.png`](../images/pattern_780hz.png)): a four-lobed pattern with distinct curved nodal lines converging toward the center, consistent with the report's description of "a higher-order resonance mode."

The visible difference between these two patterns is the core demonstrated result of the project: changing excitation frequency changes which vibration mode dominates, and therefore changes the nodal geometry.

## Validation performed

- Waveform frequency, amplitude, and shape confirmed on the oscilloscope before and during pattern capture.
- Distinct, repeatable patterns observed at the two documented frequencies.
- The retained second LM3875 package and surrounding connections (see [hardware-design.md](hardware-design.md)) were checked for unintended shorts or interference before the system was powered and tested.

## Observed behavior

- Lower frequencies produced simpler, radially symmetric patterns with fewer nodal divisions.
- Higher frequencies produced more complex figures with more nodal lines.
- Transitions between modes were visually apparent when sweeping frequency slowly — patterns formed and stabilized within seconds at resonance, and looked irregular off-resonance.

## Project scope

This system was built and evaluated as a **functional demonstration**, not a calibrated measurement instrument. The report states directly: *"no quantitative measurements were recorded... performance was assessed qualitatively through oscilloscope observation and visual inspection."* Treat all frequency/pattern claims in this repository accordingly — they describe what was observed, not what was measured with traceable instrumentation.

## What was outside the original scope

- No automated frequency-sweep logging.
- No quantified vibration amplitude (no accelerometer, laser vibrometer, or microphone-based measurement).
- No modal simulation or FEA comparison against the demonstrated patterns.
- No repeatability study across multiple plates, mountings, or particle types.
- No PCB revision of the amplifier/conditioning circuit — built on perfboard/breadboard.

## Next engineering iteration

See [project-scope-and-next-steps.md](project-scope-and-next-steps.md) for planned/possible follow-on work.
