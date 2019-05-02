#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <string>

class Menu : public sf::Drawable
{
private:
  sf::Vector2f dimensions;
  sf::Vector2f pos;

  sf::RectangleShape bg;
  sf::RectangleShape xInputBox;
  sf::RectangleShape yInputBox;

  sf::Font font;

  sf::Text topText;
  sf::Text xText;
  sf::Text yText;

  sf::Text xInput;
  sf::Text yInput;
public:
  Menu(const sf::RenderWindow&, const std::string&);

  sf::Text* selectTextBox(sf::Vector2i);
  std::string getTextBoxProperty(sf::Text*);

  virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
};

#endif