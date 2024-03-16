#include <Adafruit_NeoPixel.h>
#include <avr/pgmspace.h>
#define BUZZER_PIN 4
#define LED_PIN    3 // Pin connected to the NeoPixels
#define NUM_LEDS   9 // Number of NeoPixels
#define BRIGHTNESS 200 // Increased brightness level (0-255)
#define ANIMATION_DELAY 10 // Decreased delay between frames


Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Define the character set for password generation in PROGMEM
const char charset[] PROGMEM = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_=+";

// Define the length of the password
const int passwordLength = 12;

const uint16_t PROGMEM melody[] = {
 659, 587, 740, 830, // E5, D5, F#4, G#4
  554, 494, 587, 659, // C#5, B4, D4, E4
  494, 440, 277, 325,440  // B4, A4, C#4, E4, A4
};

const uint8_t PROGMEM durations[] = {
  8, 8, 4, 4,
  8, 8, 4, 4,
  8, 8, 4, 4,
  2
};

void setup() {
  Serial.begin(9600); // Initialize serial communication
  // Wait for a short duration to allow for more variation in analogRead values
  Serial.print("[+] Generating Password .. \n");
 delay(random(600, 10000)); // Adjust delay duration as needed
 randomSeed(random(0,131070) + analogRead(A1) + (analogRead(A0)*7)); // Seed the random number generator
    // Wait for a short duration to allow for more variation in analogRead values
  delay(random(100, 10000)); // Adjust delay duration as needed
  pinMode(BUZZER_PIN, OUTPUT);
  strip.begin();           // Initialize the NeoPixel strip
  strip.setBrightness(BRIGHTNESS); // Set brightness
  strip.show();            // Initialize all pixels to 'off'

  generateAndSendPassword(passwordLength);
  
  int size = sizeof(durations) / sizeof(uint8_t);

  for (int note = 0; note < size; note++) {
    // Calculate the note duration
    int duration = 1000 / pgm_read_byte(&durations[note]);
    tone(BUZZER_PIN, pgm_read_word(&melody[note]), duration);

    // Add a pause between notes
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);
    
    // Stop the tone playing
    noTone(BUZZER_PIN);
}


}

void loop() {
  // Rainbow Chase Animation for pink LEDs (D2, D4, D7, D8)
  static uint16_t startIndex = 0;
  startIndex += 6; // Increase animation speed even further
  for (int i = 0; i < 4; i++) {
    int pixelIndex = (i == 0) ? 1 : (i == 1) ? 3 : (i == 2) ? 6 : 7;
    strip.setPixelColor(pixelIndex, Wheel((i * 256 / 4 + startIndex) & 255));
  }

  // Light up D1, D5, D6, and D9 with dimming effect
  static uint8_t dimValue = 0;
  dimValue += 5; // Increase dimming speed
  strip.setPixelColor(0, dimValue, 0, dimValue); // D1
  strip.setPixelColor(4, dimValue, 0, dimValue); // D5
  strip.setPixelColor(5, dimValue, 0, dimValue); // D6
  strip.setPixelColor(8, dimValue, 0, dimValue); // D9

  // Turn off previously lit LEDs
  if (dimValue > 0) {
    strip.setPixelColor(2, 0, 255, 0); // D3 (Green color)
  }

  strip.show();
  delay(ANIMATION_DELAY);
}

// Input a value 0 to 255 to get a color value.
// The colors are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void generateAndSendPassword(int length) {
  Serial.print("[+] Generated Password: "); 
  for (int i = 0; i < length; ++i) {
    char character;
    memcpy_P(&character, &charset[random(0, sizeof(charset) - 1)], sizeof(char)); // Read character from PROGMEM
    Serial.print(character);
  }
  Serial.println(); // End of password
}
