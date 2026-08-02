# Firmware

## Status of this code

The firmware in [`code/arduino_frequency_controller.ino`](../code/arduino_frequency_controller.ino) is explicitly labeled in its own header comment as **a clean reconstruction written for documentation purposes**, not the original code that ran on the Arduino during the demonstration. The original experimental firmware was not preserved in this repository. This file documents the AD9850 control protocol and reproduces the same serial-input workflow described in the report, but it should be read as an accurate *explanation* of how the system's frequency control worked, not as an artifact recovered from the original build.

## Serial-input workflow

1. The Arduino opens a serial connection at 115200 baud.
2. The user types a frequency in Hz into the Serial Monitor and presses Enter.
3. `handleSerialInput()` reads characters until a newline, trims the buffer, and converts it to a `double` with `toFloat()`.
4. If the value is within `[MIN_FREQ_HZ, MAX_FREQ_HZ]` (1 Hz to 40 MHz in this reconstruction — a conservative practical bound, not a value taken from the report), `setAD9850Frequency()` is called and the new frequency is echoed back over serial.
5. Values outside that range are rejected with an error message; no frequency is sent to the DDS.

## Pin assignments

| Signal | Arduino pin | Matches schematic? |
|---|---|---|
| `W_CLK` | 8 | Yes — [`schematics/arduino_ad9850_wiring.jpeg`](../schematics/arduino_ad9850_wiring.jpeg) |
| `FQ_UD` | 9 | Yes |
| `DATA` | 10 | Yes |
| `RESET` | 11 | Yes |

## AD9850 control protocol

The AD9850 is controlled with a 40-bit serial word: a 32-bit frequency tuning word (FTW) followed by an 8-bit control byte, clocked in **LSB-first** on `W_CLK`, then latched with a pulse on `FQ_UD`.

```
sendByteLSB(FTW & 0xFF)          // bits 0–7
sendByteLSB((FTW >> 8) & 0xFF)   // bits 8–15
sendByteLSB((FTW >> 16) & 0xFF)  // bits 16–23
sendByteLSB((FTW >> 24) & 0xFF)  // bits 24–31
sendByteLSB(0x00)                // control byte — 0x00 selects normal sine output
pulsePin(FQ_UD)                  // latch
```

### Frequency tuning word equation

```
FTW = round(f_out × 2^32 / f_clk)
```

where:

- `FTW` — the 32-bit value written to the AD9850, unitless (a fraction of the full 2^32 phase range)
- `f_out` — the desired output frequency, in Hz
- `f_clk` — the AD9850's reference clock frequency, in Hz

The reconstruction uses `f_clk = 125,000,000 Hz`, noted in the code as the value used by common AD9850 breakout modules. **This is a documented assumption carried over from typical AD9850 module datasheets/tutorials, not a value independently measured from this project's specific module's crystal.** If the module's actual reference clock differs even slightly, every commanded frequency will be off by the same proportional error — a real calibration consideration for anyone extending this firmware.

### Reset sequence

`resetAD9850()` pulses `RESET`, then `W_CLK`, then `FQ_UD`, following the AD9850 datasheet's power-up initialization sequence, before the first frequency is loaded.

## Validation behavior

- Input frequency is clamped to `[MIN_FREQ_HZ, MAX_FREQ_HZ]` before being converted to a tuning word.
- Malformed or empty serial lines are ignored (no tuning word is sent).
- There is no validation that the AD9850 module actually received or latched the word correctly — the protocol is open-loop; the only external confirmation used during the project was the oscilloscope.

## Known limitations of this reconstruction

- Uses Arduino's `String` class for the input buffer, which allocates/reallocates memory on the heap — a well-known source of memory fragmentation on 8-bit AVR boards (2 KB of RAM on the Uno) in longer-running programs. Not a problem at this program's scale, but worth naming as a limitation rather than presenting the code as production-grade firmware.
- No automated sweep mode — every frequency change requires a manual serial entry, matching what the report describes ("rapid exploration of different resonance modes" via manual entry).
- No display of the currently active frequency other than the serial echo.
- No closed-loop confirmation that the DDS accepted the tuning word.

## Possible improvements

- Replace `String` buffering with a fixed-size `char` array and manual parsing to remove heap allocation.
- Add an automated frequency-sweep mode that steps through a range and pauses briefly at each point, so resonances can be located without manual entry.
- Add a small OLED/LCD display for the current frequency instead of relying on the Serial Monitor.
- Store a small set of known-resonance frequencies as presets.
