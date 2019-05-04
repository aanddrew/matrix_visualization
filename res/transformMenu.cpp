

#include "../include/transformMenu.h"

#include <iostream>
#include <string>

TransformMenu::TransformMenu(const sf::RenderWindow& window, const std::string& fileName)
:
dimensions(150,150),
pos(window.getSize().x - 200, window.getSize().y-200)
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
  topText.setString("transformation:");
  topText.setCharacterSize(18);
  topText.setPosition(pos.x + 2, pos.y+2);
  topText.setFillColor(sf::Color::Black);

  applyText.setFont(font);
  applyText.setString("APPLY");
  applyText.setCharacterSize(32);
  applyText.setPosition(pos.x + 24, pos.y+dimensions.y - 42);
  applyText.setFillColor(sf::Color::Black);

  //apply box (button)
  applyBox.setPosition(pos.x + 24, pos.y+dimensions.y - 40);
  applyBox.setSize(sf::Vector2f(100, 38));
  applyBox.setFillColor(sf::Color(255, 155, 155));

  //INPUT BOXES
  for(int i = 0; i < 4; i++)
  {
    inputBoxes[i].setPosition(pos.x + 20 + (60*(i%2)), xInputY + 2 + (36*(i/2)));
    inputBoxes[i].setSize(sf::Vector2f(48,24));
    inputBoxes[i].setFillColor(sf::Color::White);
    inputBoxes[i].setOutlineColor(sf::Color::Black);
    inputBoxes[i].setOutlineThickness(2);
  }

  for(int i = 0; i < 4; i++)
  {
    inputTexts[i].setPosition(inputBoxes[i].getPosition() + sf::Vector2f(2,-1));
    inputTexts[i].setFont(font);
    inputTexts[i].setCharacterSize(22);
    inputTexts[i].setFillColor(sf::Color::Black);
    inputTexts[i].setString((i == 0 || i == 3) ? "1" : "0");
  }
}

sf::Text* TransformMenu::selectTextBox(sf::Vector2i mousePos)
{
  // sf::FloatRect xBounds = xInputBox.getGlobalBounds();
  for(int i = 0; i < 4; i++)
  {
    sf::FloatRect bounds = inputBoxes[i].getGlobalBounds();
    if (bounds.contains((sf::Vector2f)mousePos))
    {
      inputBoxes[i].setFillColor(sf::Color::Cyan);
      return &inputTexts[i];
    }
  }
  // if (xBounds.contains((sf::Vector2f)mousePos))
  // {
  //   xInputBox.setFillColor(sf::Color::Cyan);
  //   yInputBox.setFillColor(sf::Color::White);
  //   return &xInput;
  // }

  // if (yBounds.contains((sf::Vector2f)mousePos))
  // {
  //   yInputBox.setFillColor(sf::Color::Cyan);
  //   xInputBox.setFillColor(sf::Color::White);
  //   return &yInput;
  // }

  // xInputBox.setFillColor(sf::Color::White);
  // yInputBox.setFillColor(sf::Color::White);

  // return nullptr;
}

std::string TransformMenu::getTextBoxProperty(sf::Text* textBox)
{
  for(int i = 0; i < 4; i++)
  {
    std::string returned = "";
    if (textBox == &inputTexts[i])
    {
      returned += std::to_string(i/2);
      returned += std::to_string(i%2);
      return returned;
    }
  }

  return "null";
}


void TransformMenu::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
  window.draw(bg);

  window.draw(topText);

  window.draw(applyBox);
  window.draw(applyText);

  for(int i = 0; i < 4; i++)
  {
    window.draw(inputBoxes[i]);
    window.draw(inputTexts[i]);
  }
}