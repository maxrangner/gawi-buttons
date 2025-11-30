#include "src/Button.h"
#include "src/ButtonManager.h"

ButtonManager buttonManager; // Create manager object to controll the buttons
Button* buttonBuiltIn; // Create Button pointer

constexpr uint8_t ledPin = 8;
bool stateLED = false;

void setup() {
  Serial.begin(9600);
  delay(100);

  buttonBuiltIn = buttonManager.addButton(9); // Create Button object Button(uint8_t buttonPin, unsigned long setDebounce = 50, unsigned long holdTime = 300, bool hasPullup = false)

  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);

  Serial.print("BOOT! ");
  Serial.print(buttonManager.getNumButtons()); // Getter returns number of created Button objects
  Serial.print("buttons found.");
}

void loop() {
  buttonManager.updateAll(); // Manager updates all registered buttons

  // Pressed logic:
  if (buttonBuiltIn->wasPressed()) {
    digitalWrite(8, stateLED);
    stateLED = !stateLED;
    Serial.println("Button was pressed.");
  }

  // Held logic:
  if (buttonBuiltIn->wasHeld()) {
    Serial.println("Button was held.");
  }
}
