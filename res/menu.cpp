#include "../include/menu.h"

#include <iostream>
#include <string>

Menu::Menu(const sf::RenderWindow& window, const std::string& fileName)
:
dimensions(110,150),
pos(50, window.getSize().y-200),
font(),
topText(),
xText(),
yText(),
xInput(),
yInput()
{
  //INITIALIZE BG
  bg.setPosition(pos);
  bg.setSize(dimensions);
  bg.setFillColor(sf::Color::White);

  if (!font.loadFromFile(fileName))
  {
    std::cerr << "Error loading font file " << fileName << std::endl; 
  }

  float xInputY = pos.y + 36;
  float yInputY = pos.y + 72;

  //INITIALIZE TEXT BOXES
  topText.setFont(font);
  topText.setString("edit vector:");
  topText.setCharacterSize(18);
  topText.setPosition(pos.x + 2, pos.y+2);
  topText.setFillColor(sf::Color::Black);

  xText.setFont(font);
  xText.setString("x:");
  xText.setCharacterSize(24);
  xText.setPosition(pos.x + 4, xInputY);
  xText.setFillColor(sf::Color::Black);

  yText.setFont(font);
  yText.setString("y:");
  yText.setCharacterSize(24);
  yText.setPosition(pos.x + 4, yInputY);
  yText.setFillColor(sf::Color::Black);

  //INPUT BOXES
  xInputBox.setPosition(pos.x + 24, xInputY + 2);
  xInputBox.setSize(sf::Vector2f(72,24));
  xInputBox.setFillColor(sf::Color::White);
  xInputBox.setOutlineColor(sf::Color::Black);
  xInputBox.setOutlineThickness(2);

  yInputBox.setPosition(pos.x + 24, yInputY + 2);
  yInputBox.setSize(sf::Vector2f(72,24));
  yInputBox.setFillColor(sf::Color::White);
  yInputBox.setOutlineColor(sf::Color::Black);
  yInputBox.setOutlineThickness(2);

  xInput.setPosition(xInputBox.getPosition());
  xInput.setFont(font);
  xInput.setCharacterSize(22);
  xInput.setFillColor(sf::Color::Black);

  yInput.setPosition(yInputBox.getPosition());
  yInput.setFont(font);
  yInput.setCharacterSize(22);
  yInput.setFillColor(sf::Color::Black);
}

sf::Text* Menu::selectTextBox(sf::Vector2i mousePos)
{
  sf::FloatRect xBounds = xInputBox.getGlobalBounds();
  sf::FloatRect yBounds = yInputBox.getGlobalBounds();

  if (xBounds.contains((sf::Vector2f)mousePos))
  {
    xInputBox.setFillColor(sf::Color::Cyan);
    yInputBox.setFillColor(sf::Color::White);
    return &xInput;
  }

  if (yBounds.contains((sf::Vector2f)mousePos))
  {
    yInputBox.setFillColor(sf::Color::Cyan);
    xInputBox.setFillColor(sf::Color::White);
    return &yInput;
  }

  xInputBox.setFillColor(sf::Color::White);
  yInputBox.setFillColor(sf::Color::White);

  return nullptr;
}

std::string Menu::getTextBoxProperty(sf::Text* textBox)
{
  if (textBox == &xInput)
    return "x";
  if (textBox == &yInput)
    return "y";

  return "null";
}


void Menu::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
  window.draw(bg);

  window.draw(topText);
  window.draw(xText);
  window.draw(yText);

  window.draw(xInputBox);
  window.draw(yInputBox);

  window.draw(xInput);
  window.draw(yInput);
}