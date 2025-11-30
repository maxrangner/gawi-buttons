#include "ButtonManager.h"

ButtonManager::ButtonManager() : numButtons(0) {}

uint8_t ButtonManager::getNumButtons() const {
  return numButtons;
}

Button* ButtonManager::addButton(uint8_t pin) {
  return addButton(pin, Button::DefaultDebounce, Button::DefaultHold, Button::DefaultPullup);
} 
Button* ButtonManager::addButton(uint8_t pin, uint16_t setDebounce) {
  return addButton(pin, setDebounce, Button::DefaultHold, Button::DefaultPullup);
}
Button* ButtonManager::addButton(uint8_t pin, uint16_t setDebounce, unsigned long holdTime) {
  return addButton(pin, setDebounce, holdTime, Button::DefaultPullup);
}
Button* ButtonManager::addButton(uint8_t pin, uint16_t setDebounce, unsigned long holdTime, bool hasPullup) {
  m_activeButtons.emplace_back(std::make_unique<Button>(pin, setDebounce, holdTime, hasPullup));
  Serial.println("Button added.");
  this->numButtons++;
  return m_activeButtons.back().get();
}

void ButtonManager::updateAll() {
  for (auto& b : m_activeButtons) {
    b->update();
  }
}

