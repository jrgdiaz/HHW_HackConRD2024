void setup() {
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  // Frame 1
  Serial.println("\033[2J"); // Clear the screen
  Serial.println("\033[1;34m"); // Set color to blue
  Serial.println("   O   ");
  Serial.println("  /|\\  ");
  Serial.println("  / \\  ");
  delay(500);

  // Frame 2
  Serial.println("\033[2J"); // Clear the screen
  Serial.println("\033[1;34m"); // Set color to blue
  Serial.println("  \\O/  ");
  Serial.println("   |   ");
  Serial.println("  / \\  ");
  delay(500);
  Serial.println("\033[2J"); // Clear the screen
  Serial.println("\033[1;34m"); // Set color to blue
  Serial.println("      (Mientras no AFECTE el precio de la yuca...)");
  Serial.println("     / ");
  Serial.println("   O   ");
  Serial.println("  /|\\  ");
  Serial.println("  / \\  ");
  delay(2500);
  Serial.println("\e[0;32m");
  Serial.println("      (Ni el de la pipiota!!)");
  Serial.println("     / ");
  Serial.println("  \\O/  ");
  Serial.println("   |  ");
  Serial.println("  / \\  ");
  delay(2500);
}
