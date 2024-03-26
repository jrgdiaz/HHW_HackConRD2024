#include <Adafruit_NeoPixel.h>
#include <avr/pgmspace.h>

#define LED_PIN 3 // =3lt1oT0m4t3= can run on any device with aRGBs
#define BUZZER_PIN 4 //Buzzers are also supported
#define NUM_LEDS    9   // Number of Neopixels
#define WORK_COLOR  0xFF0000  // Red color for work period
#define BREAK_COLOR 0x00FF00  // Green color for break period


#define WORK_DURATION 25UL * 60 * 1000  // 25 minutes in milliseconds (UL for unsigned long)
#define SHORT_BREAK_DURATION 5UL * 60 * 1000  // 5 minutes in milliseconds
#define LONG_BREAK_DURATION 30UL * 60 * 1000  // 30 minutes in milliseconds
#define LONG_BREAK_FREQUENCY 4  // After every fourth break, take a long break
#define STATE_WORK 0
#define STATE_SHORT_BREAK 1
#define STATE_LONG_BREAK 2

// Define the frequency of notes (in Hz)
const int NOTE_C4 = 261;
const int NOTE_D4 = 294;
const int NOTE_E4 = 330;
const int NOTE_F4 = 349;
const int NOTE_G4 = 392;
const int NOTE_A4 = 440;
const int NOTE_B4 = 494;
const int NOTE_C5 = 523;

// Define the durations of notes (in milliseconds)
const int whole = 1000;
const int half = 500;
const int quarter = 250;
const int eighth = 125;

// Define the melody (notes and durations)
const int melody[] PROGMEM = {
  NOTE_E4, quarter,
  NOTE_D4, eighth,
  NOTE_C4, eighth,
  NOTE_D4, eighth,
  NOTE_E4, eighth,
  NOTE_E4, eighth,
  NOTE_E4, half,
  NOTE_D4, quarter,
  NOTE_D4, eighth,
  NOTE_D4, half,
  NOTE_E4, quarter
};



Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

unsigned long startTime = 0UL;
unsigned long elapsedTime = 0UL;
unsigned long totalWorkTime = 0UL;
unsigned long totalRestTime = 0UL;
unsigned int breakCount = 0;
int currentState = STATE_WORK;


void setup(){
  Serial.begin(9600);
  delay(5000);
  pinMode(BUZZER_PIN, OUTPUT);
  strip.begin();
  strip.show();  // Initialize all pixels to 'off'


  // Set color to green
  Serial.println(F("\033[2J"));
  Serial.println(F("\033[32m"));
  Serial.println(F("Podomoro Timer =3lt1oT0m4t3= v.0.1\r\n      \ncoded X ddiax March 2024\n"));
  Serial.println(F("This timer aims to help you work better\r\nby incorporating Pomodoro sessions to your\r\nwork structure in a portable device."));

  Serial.println(F("                   ,"));
  Serial.println(F("                  /.\\"));
  Serial.println(F("                 //_\`\\"));
  Serial.println(F("            _.-`| \\ ``._"));
  Serial.println(F("        .-''`-.       _.'`."));
  Serial.println(F("      .'      / /'\\/`.\    `."));
  Serial.println(F("     /   .    |/         `.  \\"));
  Serial.println(F("\033[31m    '   /                  \\  ;"));
  Serial.println(F("   :   '            \\       : :"));
  Serial.println(F("   ;  ;             ;      /  ."));
  Serial.println(F("    ' :             .     '  /"));
  Serial.println(F("     \\ \\           /       .'"));
  Serial.println(F("      `.`        .'      .'"));
  Serial.println(F("        `-..___....----`"));
  Serial.println(F("\r\nLGB"));
  Serial.println(F("\033[0m"));
  delay(1000);
  startTime = millis();
  
  Serial.println(F("\n[+] Work Time"));
  Serial.print(F("\033[34m")); // Set text color to blue
  Serial.println(F("       T                                    \\`.    T"));
  Serial.println(F("       |    T     .--------------.___________) \\   |    T"));
  Serial.println(F("       !    |     |//////////////|___________[ ]   !  T |"));
  Serial.println(F("            !     `--------------'           ) (      | !"));
  Serial.println(F("                                         mn  '-'      !"));
  Serial.print(F("\033[0m"));
  }

void loop() {
  unsigned long currentTime = millis();
  elapsedTime = currentTime - startTime;

  // Check current state and duration
  if (currentState == STATE_WORK && elapsedTime >= WORK_DURATION) {
    totalWorkTime += WORK_DURATION;
    breakCount++;
    if (breakCount % LONG_BREAK_FREQUENCY == 0) {
      currentState = STATE_LONG_BREAK;
      breakCount = 0;  // Reset break count for long break
      Serial.println(F("\n[+] Long Break"));
         int numNotes = sizeof(melody) / (sizeof(int) * 2);
 
      Serial.println(F("\033[32m"));
      Serial.println(F("                   ,"));
      Serial.println(F("                  /.\\"));
      Serial.println(F("                 //_\`\\"));
      Serial.println(F("            _.-`| \\ ``._"));
      Serial.println(F("        .-''`-.       _.'`."));
      Serial.println(F("      .'      / /'\\/`.\    `."));
      Serial.println(F("     /   .    |/         `.  \\"));
      Serial.println(F("\033[31m    '   /                  \\  ;"));
      Serial.println(F("   :   '            \\       : :"));
      Serial.println(F("   ;  ;             ;      /  ."));
      Serial.println(F("    ' :             .     '  /"));
      Serial.println(F("     \\ \\           /       .'"));
      Serial.println(F("      `.`        .'      .'"));
      Serial.println(F("        `-..___....----`"));
      Serial.println(F("\r\nLGB"));
      Serial.println(F("\033[0m"));
        
  for (int i = 0; i < numNotes; i++) {
    int noteFrequency = pgm_read_word_near(melody + i * 2);
    int noteDuration = pgm_read_word_near(melody + i * 2 + 1);
    tone(BUZZER_PIN, noteFrequency, noteDuration);
    delay(noteDuration);
    noTone(BUZZER_PIN);
    delay(50); // Add a short pause between each note
  }
    } else {

         int numNotes = sizeof(melody) / (sizeof(int) * 2);
  for (int i = 0; i < numNotes; i++) {
    int noteFrequency = pgm_read_word_near(melody + i * 2);
    int noteDuration = pgm_read_word_near(melody + i * 2 + 1);
    tone(BUZZER_PIN, noteFrequency, noteDuration);
    delay(noteDuration);
    noTone(BUZZER_PIN);
    delay(50); // Add a short pause between each note
  }
      currentState = STATE_SHORT_BREAK;
      Serial.println(F("\n[+] Short Break"));
      Serial.println(F("\033[33m")); // Set text color to yellow
     Serial.println(F("         (  )   (   )  )"));
     
  Serial.println(F("     ) (   )  (  ("));
  Serial.println(F("     ( )  (    ) )"));
  Serial.println(F("     _____________"));
  Serial.println(F("    <_____________> ___"));
  Serial.println(F("    |             |/ _ \\"));
  Serial.println(F("    |               | | |"));
  Serial.println(F("    |               |_| |"));
  Serial.println(F(" ___|             |\\___/"));
  Serial.println(F("/    \\___________/    \\"));
  Serial.println(F("\\_____________________/"));

    Serial.println("\r\nElisa Potier");
    Serial.print(F("\033[0m"));
    }
    startTime = currentTime;  // Reset start time for break
  } else if ((currentState == STATE_SHORT_BREAK) && elapsedTime >= SHORT_BREAK_DURATION) {
    totalRestTime += SHORT_BREAK_DURATION;
    currentState = STATE_WORK;
    startTime = currentTime;  // Reset start time for work
    Serial.println(F("\n[+] Work Time"));
        Serial.print(F("\033[34m")); // Set text color to blue
      Serial.println(F("       T                                    \\`.    T"));
  Serial.println(F("       |    T     .--------------.___________) \\   |    T"));
  Serial.println(F("       !    |     |//////////////|___________[ ]   !  T |"));
  Serial.println(F("            !     `--------------'           ) (      | !"));
  Serial.println(F("                                         mn  '-'      !"));
  Serial.print(F("\033[0m"));
  } else if (currentState == STATE_LONG_BREAK && elapsedTime >= LONG_BREAK_DURATION) {
    totalRestTime += LONG_BREAK_DURATION;
    currentState = STATE_WORK;
    startTime = currentTime;  // Reset start time for work
    Serial.println(F("\n[+] Work Time"));
    Serial.print(F("\033[34m")); // Set text color to blue
      Serial.println(F("       T                                    \\`.    T"));
  Serial.println(F("       |    T     .--------------.___________) \\   |    T"));
  Serial.println(F("       !    |     |//////////////|___________[ ]   !  T |"));
  Serial.println(F("            !     `--------------'           ) (      | !"));
  Serial.println(F("                                         mn  '-'      !"));
  Serial.print(F("\033[0m"));
  }

  // Update Neopixel colors based on state
  if (currentState == STATE_WORK) {
    clearLEDs();
     Serial.print(F("\r\033[K")); // Move cursor to beginning of line and clear line
    Serial.print(F("[+] Total Rest Time in this Pomodoro Session, in Minutes: "));
    Serial.print((totalRestTime/1000)/60);
    Serial.flush(); // Flush the Serial buffer to ensure immediate output
    Serial.print("\r"); // Move cursor to beginning of line for the next print
  } else {
    setColor(BREAK_COLOR);
 Serial.print(F("\r\033[K")); // Move cursor to beginning of line and clear line
    Serial.print(F("[+] Total Work Time in this Pomodoro Session, in Minutes: "));
    Serial.print((totalWorkTime/1000)/60);
    Serial.flush(); // Flush the Serial buffer to ensure immediate output
    Serial.print("\r"); // Move cursor to beginning of line for the next print
  }

  delay(1000); // Delay for stability
}

void setColor(uint32_t color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
}

// Function to clear all LEDs
void clearLEDs() {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, 0); // Set color of each pixel to 'off' (0,0,0)
  }
  strip.show(); // Update the strip to reflect the changes
}
