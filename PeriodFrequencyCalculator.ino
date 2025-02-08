// PROJECT    : Period & Frequency Calculator
// PURPOSE    : Calculate the period and frequency of the SAR ADC clock.
// AUTHOR     : Harshavardan Gunasegaran
// COURSE     : ICS3U-E
// DATE       : 2025 02 08
// MCU        : 328P (Nano)
// STATUS     : Working

const int ledPin = 2;                 // Pin connected to the oscillating LED
volatile unsigned long lastTime = 0;  // Stores the last recorded time in microseconds
volatile unsigned long period = 0;    // Stores the calculated period in microseconds

// Interrupt Service Routine (ISR) for detecting rising edge
void detectRisingEdge() {
  unsigned long currentTime = micros();  // Get current time in microseconds
  period = currentTime - lastTime;       // Calculate time difference between edges
  lastTime = currentTime;                // Update last time
}

void setup() {
  pinMode(ledPin, INPUT);                                                    // Set the pin as input
  Serial.begin(9600);                                                        // Start serial communication
  attachInterrupt(digitalPinToInterrupt(ledPin), detectRisingEdge, RISING);  // Attach interrupt to detect rising edge
}

void loop() {
  if (period > 0) {
    float frequency = 1000000.0 / period;  // Convert period from microseconds to frequency in Hz
    Serial.print("Period: ");
    Serial.print(period);
    Serial.print(" µs, Frequency: ");
    Serial.print(frequency);
    Serial.println(" Hz");
    delay(500);  // Delay to prevent excessive serial printing
  }
}
