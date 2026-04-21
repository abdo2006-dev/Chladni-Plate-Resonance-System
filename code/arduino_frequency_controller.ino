/*
  Arduino Frequency Controller for AD9850 DDS
  -------------------------------------------
  Purpose:
    Allows the user to enter a frequency through the Serial Monitor
    and outputs a sine wave from the AD9850 module at that frequency.

  Notes:
    - This code is a clean reconstruction suitable for documentation/GitHub.
    - The AD9850 is controlled by sending a 40-bit serial word:
        32-bit frequency tuning word + 8-bit control byte.
    - Default waveform is sine output from the AD9850 module.
    - Open Serial Monitor at 115200 baud.
    - Type a frequency in Hz, for example:
        100
        440
        780
        1000

  Typical AD9850 connections:
    W_CLK  -> Arduino pin 8
    FQ_UD  -> Arduino pin 9
    DATA   -> Arduino pin 10
    RESET  -> Arduino pin 11

  Author:
    Reconstructed for project documentation
*/

#include <Arduino.h>

// ------------------------
// Pin definitions
// ------------------------
constexpr uint8_t PIN_W_CLK = 8;
constexpr uint8_t PIN_FQ_UD = 9;
constexpr uint8_t PIN_DATA  = 10;
constexpr uint8_t PIN_RESET = 11;

// ------------------------
// AD9850 reference clock
// ------------------------
// Common AD9850 modules use a 125 MHz reference clock.
constexpr double AD9850_REF_CLOCK_HZ = 125000000.0;

// ------------------------
// Limits
// ------------------------
constexpr double MIN_FREQ_HZ = 1.0;
constexpr double MAX_FREQ_HZ = 40000000.0; // conservative practical upper bound

// ------------------------
// State
// ------------------------
double currentFrequencyHz = 100.0;
String inputBuffer;

// ------------------------
// Helper: pulse a pin HIGH->LOW
// ------------------------
void pulsePin(uint8_t pin) {
  digitalWrite(pin, HIGH);
  delayMicroseconds(1);
  digitalWrite(pin, LOW);
  delayMicroseconds(1);
}

// ------------------------
// Reset AD9850
// ------------------------
void resetAD9850() {
  digitalWrite(PIN_RESET, LOW);
  digitalWrite(PIN_W_CLK, LOW);
  digitalWrite(PIN_FQ_UD, LOW);

  pulsePin(PIN_RESET);
  pulsePin(PIN_W_CLK);
  pulsePin(PIN_FQ_UD);
}

// ------------------------
// Send one byte LSB first
// ------------------------
void sendByteLSB(uint8_t value) {
  for (uint8_t i = 0; i < 8; i++) {
    digitalWrite(PIN_DATA, (value >> i) & 0x01);
    pulsePin(PIN_W_CLK);
  }
}

// ------------------------
// Set AD9850 output frequency
// ------------------------
void setAD9850Frequency(double frequencyHz) {
  // Clamp input
  if (frequencyHz < MIN_FREQ_HZ) {
    frequencyHz = MIN_FREQ_HZ;
  } else if (frequencyHz > MAX_FREQ_HZ) {
    frequencyHz = MAX_FREQ_HZ;
  }

  // Frequency tuning word:
  // FTW = frequency * 2^32 / reference_clock
  const uint32_t tuningWord =
      static_cast<uint32_t>((frequencyHz * 4294967296.0) / AD9850_REF_CLOCK_HZ);

  // Begin update
  digitalWrite(PIN_FQ_UD, LOW);

  // Send 32-bit tuning word, LSB first
  sendByteLSB(static_cast<uint8_t>( tuningWord        & 0xFF));
  sendByteLSB(static_cast<uint8_t>((tuningWord >> 8)  & 0xFF));
  sendByteLSB(static_cast<uint8_t>((tuningWord >> 16) & 0xFF));
  sendByteLSB(static_cast<uint8_t>((tuningWord >> 24) & 0xFF));

  // Control byte = 0x00 for normal sine output
  sendByteLSB(0x00);

  // Latch the new frequency into the DDS
  pulsePin(PIN_FQ_UD);

  currentFrequencyHz = frequencyHz;
}

// ------------------------
// Print instructions
// ------------------------
void printInstructions() {
  Serial.println(F("AD9850 Frequency Controller Ready"));
  Serial.println(F("--------------------------------"));
  Serial.println(F("Enter a frequency in Hz and press Enter."));
  Serial.println(F("Examples: 100, 440, 780, 1000"));
  Serial.println(F("Current output is sine wave."));
  Serial.println();
}

// ------------------------
// Parse and apply frequency from serial input
// ------------------------
void handleSerialInput() {
  while (Serial.available() > 0) {
    char c = static_cast<char>(Serial.read());

    if (c == '\r') {
      continue; // ignore carriage return
    }

    if (c == '\n') {
      inputBuffer.trim();

      if (inputBuffer.length() > 0) {
        double requestedFrequency = inputBuffer.toFloat();

        if (requestedFrequency >= MIN_FREQ_HZ && requestedFrequency <= MAX_FREQ_HZ) {
          setAD9850Frequency(requestedFrequency);

          Serial.print(F("Frequency set to: "));
          Serial.print(currentFrequencyHz, 2);
          Serial.println(F(" Hz"));
        } else {
          Serial.print(F("Invalid frequency. Enter a value between "));
          Serial.print(MIN_FREQ_HZ, 0);
          Serial.print(F(" Hz and "));
          Serial.print(MAX_FREQ_HZ, 0);
          Serial.println(F(" Hz"));
        }
      }

      inputBuffer = "";
    } else {
      inputBuffer += c;
    }
  }
}

// ------------------------
// Arduino setup
// ------------------------
void setup() {
  pinMode(PIN_W_CLK, OUTPUT);
  pinMode(PIN_FQ_UD, OUTPUT);
  pinMode(PIN_DATA, OUTPUT);
  pinMode(PIN_RESET, OUTPUT);

  digitalWrite(PIN_W_CLK, LOW);
  digitalWrite(PIN_FQ_UD, LOW);
  digitalWrite(PIN_DATA, LOW);
  digitalWrite(PIN_RESET, LOW);

  Serial.begin(115200);
  delay(500);

  resetAD9850();
  setAD9850Frequency(currentFrequencyHz);
  printInstructions();

  Serial.print(F("Default frequency: "));
  Serial.print(currentFrequencyHz, 2);
  Serial.println(F(" Hz"));
}

// ------------------------
// Arduino main loop
// ------------------------
void loop() {
  handleSerialInput();
}