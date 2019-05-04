#ifndef TRANSFORMMENU_H
#define TRANSFORMMENU_H

#include <SFML/Graphics.hpp>
#include <string>

class TransformMenu : public sf::Drawable
{
private:
  sf::Vector2f dimensions;
  sf::Vector2f pos;

  sf::RectangleShape bg;
  sf::RectangleShape applyBox;
  sf::RectangleShape inputBoxes[4];

  sf::Font font;

  sf::Text topText;
  sf::Text inputTexts[4];
  sf::Text applyText;
public:
  TransformMenu(const sf::RenderWindow&, const std::string&);

  sf::Text* selectTextBox(sf::Vector2i);
  std::string getTextBoxProperty(sf::Text*);

  virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;
};

#endif