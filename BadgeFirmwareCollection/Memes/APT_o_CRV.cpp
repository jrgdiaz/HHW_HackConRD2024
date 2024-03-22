void setup() {
  Serial.begin(9600); // Initialize serial communication
}

void loop() {

  Serial.println(F("\033[2J")); // Clear the screen
  Serial.println(F("\u001b[34m      (K TU QUIEREEE, UN APARTAMENTO......)"));
  Serial.println(F("\u001b[34m     / "));
  Serial.println(F("\u001b[34m   O   "));
  Serial.println(F("\u001b[34m  /|\\  "));
  Serial.println(F("\u001b[34m  / \\  "));
  delay(2500);
  Serial.println(F("\033[2J")); // Clear the screen
  Serial.println(F("      (O UNAAA CRV....))"));
  Serial.println(F("     / "));
  Serial.println(F("   O   "));
  Serial.println(F("  /|\\  "));
  Serial.println(F("  / \\  "));
  delay(3500);
  Serial.println(F("\033[2J")); // Clear the screen
  Serial.println(F("\x1b[35m ( UN APARTAMEEEEEENTOOOO! :3 <3 <3 ^.^ )"));
  Serial.println(F("\x1b[35m                                   \\ "));
  Serial.println(F("\x1b[35m                                  \\  O /"));
  Serial.println(F("\x1b[35m                                     |"));
  Serial.println(F("\x1b[35m                                    / \\"));
  Serial.println(F("\x1b[35m                                   /   \\"));
  Serial.println(F("\x1b[35m                                  /_____\\"));
  delay(2500);

}
