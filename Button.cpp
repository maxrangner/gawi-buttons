#include "Button.h"

Button::Button(uint8_t buttonPin, unsigned long setDebounce, unsigned long holdTime, bool hasPullup)
  : pin(buttonPin), debounceTiming(setDebounce), holdThreashold(holdTime) {

  // BUTTON INITIALIZATION
  if (hasPullup) pinMode(pin, INPUT_PULLUP);
  else pinMode(pin, INPUT);
  buttonState = digitalRead(pin);
  prevButtonState = buttonState;

  // DEBOUNCE
  now = millis();
  nextDebounce = 0;
  // LOGIC
  buttonHeldTimer = 0;
  pushedFlag = false;
  heldFlag = false;
}

bool Button::isDebounced() {
  if (buttonState != prevButtonState) {
    if (now >= nextDebounce) {
      nextDebounce = now + debounceTiming;
      return true;
    }
  }
  return false;
}

void Button::update() {
  pushedFlag = false;
  heldFlag = false;
  now = millis();
  buttonState = digitalRead(pin);
  if (isDebounced()) {
    if (buttonState == LOW && prevButtonState == HIGH) buttonHeldTimer = now;
    if (buttonState == HIGH && prevButtonState == LOW) {
      if (now - buttonHeldTimer >= holdThreashold) heldFlag = true;
      else pushedFlag = true;
    }
  }
  prevButtonState = buttonState;
}

bool Button::wasPressed() {
  return pushedFlag;
}

bool Button::wasHeld() {
  return heldFlag;
}
