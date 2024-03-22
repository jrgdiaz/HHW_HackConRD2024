#include <Adafruit_NeoPixel.h>

#define SIZE 10
#define LED_PIN    3 // Pin connected to the NeoPixels
#define NUM_LEDS   9 // Number of NeoPixels
#define BRIGHTNESS 50 // Dimmed brightness level (0-255)

uint8_t grid[SIZE][SIZE], old_grid[SIZE][SIZE];
Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Rainbow color generation
const uint8_t PROGMEM rainbowColors[7][3] = {
  {255, 0, 0},    // Red
  {255, 127, 0},  // Orange
  {255, 255, 0},  // Yellow
  {0, 255, 0},    // Green
  {0, 0, 255},    // Blue
  {75, 0, 130},   // Indigo
  {143, 0, 255}   // Violet
};

void pr() {
  static uint8_t colorIndex = 0; // Index to cycle through rainbow colors
  for (uint8_t i = 0; i < SIZE; i++) {
    for (uint8_t j = 0; j < SIZE; j++) {
      if (grid[i][j] == 1) {
        // Select rainbow color for alive cells
        Serial.print("\033[48;2;");
        Serial.print(pgm_read_byte(&rainbowColors[colorIndex][0]));
        Serial.print(";");
        Serial.print(pgm_read_byte(&rainbowColors[colorIndex][1]));
        Serial.print(";");
        Serial.print(pgm_read_byte(&rainbowColors[colorIndex][2]));
        Serial.print("m@\033[0m "); // Reset color after cell
        // Set NeoPixel color with dimmed brightness
        strip.setPixelColor(i * SIZE + j, strip.Color(
          pgm_read_byte(&rainbowColors[colorIndex][0]) * BRIGHTNESS / 255,
          pgm_read_byte(&rainbowColors[colorIndex][1]) * BRIGHTNESS / 255,
          pgm_read_byte(&rainbowColors[colorIndex][2]) * BRIGHTNESS / 255
        ));
      } else {
        // Red color for dead cells
        Serial.print("\033[1;31m+\033[0m "); // Red
        strip.setPixelColor(i * SIZE + j, strip.Color(0, 0, 0)); // Turn off LED
      }
    }
    Serial.println(); // Newline after each row
  }
  // Cycle through colors
  colorIndex = (colorIndex + 1) % 7;
}

uint8_t check_cell(uint8_t k, uint8_t l) {
  uint8_t neigh = 0;
  for (int8_t i = -1; i < 2; i++) {
    for (int8_t j = -1; j < 2; j++) {
      uint8_t o = (k + i + SIZE) % SIZE, p = (l + j + SIZE) % SIZE;
      neigh += old_grid[o][p];
    }
  }
  neigh -= old_grid[k][l];
  return neigh;
}

void up_grid() {
  for (uint8_t i = 0; i < SIZE; i++) {
    for (uint8_t j = 0; j < SIZE; j++) {
      old_grid[i][j] = grid[i][j];
    }
  }
  for (uint8_t i = 0; i < SIZE; i++) {
    for (uint8_t j = 0; j < SIZE; j++) {
      uint8_t neighbors = check_cell(i, j);
      if (neighbors == 3) {
        grid[i][j] = 1;
      } else if (neighbors < 2 || neighbors > 3) {
        grid[i][j] = 0;
      }
    }
  }
}

void setup() {
  strip.begin();           // Initialize the NeoPixel strip
  strip.setBrightness(BRIGHTNESS); // Set brightness
  strip.show();            // Initialize all pixels to 'off'

  randomSeed(analogRead(0));
  Serial.begin(9600); // Set baud rate to 9600
  for (uint8_t i = 0; i < SIZE; i++) {
    for (uint8_t j = 0; j < SIZE; j++) {
      grid[i][j] = random(0, 2);
    }
  }
}

void loop() {
  pr();
  strip.show(); // Show the updated NeoPixel colors
  delay(10); // Adjust the delay time for animation speed
  up_grid();
}
