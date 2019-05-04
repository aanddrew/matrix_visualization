#include <SFML/Graphics.hpp>
#include <iostream>

#include "include/mat2.h"
#include "include/vec2.h"
#include "include/menu.h"
#include "include/transformMenu.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

void renderVector(sf::RenderWindow& window, Mat2& mat, Vec2 vec, sf::Color color, float scale);
void renderGrid(sf::RenderWindow& window, float scale, sf::Vector2i origin);

int main()
{
  sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT), "Vector Visualization");
  window.setVerticalSyncEnabled(false);

  sf::ContextSettings settings;
  settings.antialiasingLevel = 4;

  sf::Event e;

  Vec2 vec(3,1);
  Mat2 mat(1,0,0,1);

  sf::Clock clock;
  sf::Time dt;

  float scale = 100;

  sf::Vector2i mousePos;
  sf::Vector2i origin = sf::Vector2i(window.getSize().x/2, window.getSize().y/2);

  bool viewMoving = false;

  Menu menu(window, "resources/arial.ttf");
  TransformMenu transformMenu(window, "resources/arial.ttf");

  sf::Text* selectedTextBox = nullptr;

  while(window.isOpen())
  {
    dt = clock.restart();
    // std::cout << "fps: " << (1.0/(dt.asSeconds())) << std::endl;

    while(window.pollEvent(e))
    {
      switch(e.type)
      {
        case sf::Event::Closed:
          window.close();
        break;
        //resize the window
        case sf::Event::Resized:
        {
            // update the view to the new size of the window
            sf::FloatRect visibleArea(0, 0, e.size.width, e.size.height);
            window.setView(sf::View(visibleArea));
        } break;
        
        case sf::Event::MouseWheelMoved:
        {
            // display number of ticks mouse wheel has moved
            // std::cout << e.mouseWheel.delta << '\n';
            scale += e.mouseWheel.delta*10;
            if (scale <= 10) scale = 10;
        }break;
        //GRID MOVING LOGIC
        case sf::Event::MouseButtonPressed:
        {
          selectedTextBox = menu.selectTextBox(sf::Mouse::getPosition(window));
          if (selectedTextBox == nullptr)
            selectedTextBox = transformMenu.selectTextBox(sf::Mouse::getPosition(window));
          if (selectedTextBox != nullptr)
          {
          }
          else
          {
            if (!viewMoving)
              mousePos = sf::Mouse::getPosition();
            viewMoving = true;
          }
          // origin += (mousePos - sf::Mouse::getPosition());
        }break;
        case sf::Event::MouseButtonReleased:
        {
          if (viewMoving)
          {
            viewMoving = false;
            origin += (mousePos - sf::Mouse::getPosition());
          }
        }break;
        //END GRID MOVING
        case sf::Event::TextEntered:
        {
          //TEXT BOX LOGIC
          if (selectedTextBox != nullptr)
          {
            if (e.text.unicode == '\b')
            {
              selectedTextBox->setString(selectedTextBox->getString().substring(0, selectedTextBox->getString().getSize()-1));
            }
            else if (e.text.unicode == '\r')
            {
              float num;
              bool valid = true;
              try
              {
                num = std::stof(selectedTextBox->getString().toAnsiString());
              }
              catch(const std::exception& e)
              {
                valid = false;
              }

              bool resetBox = false;
              if (valid)
              {
                if (menu.getTextBoxProperty(selectedTextBox) == "x")
                {
                  vec.at(0) = num;
                  resetBox = true;
                }
                if (menu.getTextBoxProperty(selectedTextBox) == "y")
                {
                  vec.at(1) = num;
                  resetBox = true;
                }
                std::string val = transformMenu.getTextBoxProperty(selectedTextBox);
                if (val != "null")
                {
                  int row = val[0] - '0';
                  int col = val[1] - '0';
                  printf("row: %d, col: %d\n", row, col);
                  mat.at(row, col) = num;
                }
              }
              if (resetBox)
                selectedTextBox->setString("");
            }
            else
            {
              selectedTextBox->setString(selectedTextBox->getString() + e.text.unicode);
            }
          }
          //END TEXT BOX LOGIC
        }break;
      }
    }
    sf::Vector2i deltaMove = mousePos - sf::Mouse::getPosition();
    //this is so that we can move around the world view
    sf::View tempView = window.getView();
    tempView.setCenter((float)origin.x, (float)origin.y);
    if (viewMoving)
    {
      tempView.move((sf::Vector2f) deltaMove);
    }
    window.setView(tempView);

    //animation of vector rotating
    // vec.rotate(64*dt.asSeconds());

    //rendering sequence
    window.clear();
    sf::Vector2i tempOrigin = origin;
    if (viewMoving)
      tempOrigin += deltaMove;
    //grid
    renderGrid(window, scale, tempOrigin);
    //then vector
    renderVector(window, mat, vec, sf::Color::Yellow, scale);
    //then menu/hud
    window.setView(window.getDefaultView());
    window.draw(menu);
    window.draw(transformMenu);
    window.display();
  }
}

void renderVector(sf::RenderWindow& window, Mat2& mat, Vec2 vec, sf::Color color, float scale)
{
  vec = mat*vec;
  //this line is the vector that we are currently drawing
  sf::Vertex line[] = {sf::Vertex(sf::Vector2f(window.getSize().x/2, window.getSize().y/2)), 
                       sf::Vertex(sf::Vector2f(window.getSize().x/2 + vec.at(0)*scale, window.getSize().y/2 - vec.at(1)*scale))};
  line[0].color = color;
  line[1].color = color;

  window.draw(line, 2, sf::Lines);

  //this is our triangle, originally pointing on the x axis -->
  Vec2 triangle[] = {Vec2(1,0), Vec2(0.9, 0.03), Vec2(0.9,-0.03)};

  //now we create a transformation matrix out of the Vector that we are drawing
  //and multiply all the vertices in the triangle by this transformation matrix

  // Mat2 transform(vec.at(0), -1*vec.at(1), vec.at(1), vec.at(0));
  Mat2 transform(vec.at(0), -1*vec.at(1), 
                 vec.at(1), vec.at(0));

  for(int i = 0; i < 3; i++)
  {
    triangle[i] = triangle[i]*scale;
    triangle[i] = transform*triangle[i];
    // triangle[i] = mat*triangle[i];
    // std::cout << "Triangle vertex " << i << ": " << "(" << triangle[i].at(0) << ", " << triangle[i].at(1) << ")" << std::endl;
  }

  sf::Vertex triangleVertices[] = {sf::Vertex(sf::Vector2f(triangle[0].at(0) + window.getSize().x/2, -1*triangle[0].at(1) + window.getSize().y/2)),
                                   sf::Vertex(sf::Vector2f(triangle[1].at(0) + window.getSize().x/2, -1*triangle[1].at(1) + window.getSize().y/2)),
                                   sf::Vertex(sf::Vector2f(triangle[2].at(0) + window.getSize().x/2, -1*triangle[2].at(1) + window.getSize().y/2))};
  for(int i = 0; i < 3; i++)
  {
    triangleVertices[i].color = color;
  }

  window.draw(triangleVertices, 3, sf::Triangles);
}

void renderGrid(sf::RenderWindow& window, float scale, sf::Vector2i origin)
{
  sf::Vector2f center = window.getView().getCenter();
  float halfHeight = window.getSize().y/2;
  float halfWidth = window.getSize().x/2;
  origin.x -= halfWidth; origin.y -= halfHeight;

  //scale is how big 1 unit is - ie if it is 300, 1 unit of the graph is 300 px
  int numVertLines = (window.getSize().x/2 + abs(origin.x)) /scale + 1;
  int numHorLines = (window.getSize().y/2 + abs(origin.y))/scale + 1;

  sf::Color lineColor = sf::Color(135,206,255);

  // draw vertical grid lines
  for(int i = 0; i < numVertLines; i++)
  {
    //we draw one to the right of the y axis
    sf::Vertex line[] = {sf::Vertex(sf::Vector2f(window.getSize().x/2 + i*scale, 0 + origin.y)), 
                          sf::Vertex(sf::Vector2f(window.getSize().x/2 + i*scale, window.getSize().y + origin.y))};
    line[0].color = lineColor;
    line[1].color = lineColor;

    window.draw(line, 2, sf::Lines);

    //and one to the left
    sf::Vertex line2[] = {sf::Vertex(sf::Vector2f(window.getSize().x/2 - i*scale, 0 + origin.y)), 
                          sf::Vertex(sf::Vector2f(window.getSize().x/2 - i*scale, window.getSize().y + origin.y))};
    line2[0].color = lineColor;
    line2[1].color = lineColor;

    window.draw(line2, 2, sf::Lines);
  }

  //horizontal grid lines
  for(int i = 0; i < numHorLines; i++)
  {
    //order of above/below reversed because y coordinates are reversed
    //below
    sf::Vertex line[] = {sf::Vertex(sf::Vector2f(0 + origin.x,window.getSize().y/2 + i*scale)), 
                       sf::Vertex(sf::Vector2f(window.getSize().x +origin.x, window.getSize().y/2+i*scale))};
    line[0].color = lineColor;
    line[1].color = lineColor;

    window.draw(line, 2, sf::Lines);

    //above
    sf::Vertex line2[] = {sf::Vertex(sf::Vector2f(0 + origin.x, window.getSize().y/2 - i*scale)), 
                       sf::Vertex(sf::Vector2f(window.getSize().x + origin.x, window.getSize().y/2-i*scale))};
    line2[0].color = lineColor;
    line2[1].color = lineColor;

    window.draw(line2, 2, sf::Lines);
  }

  // std::cout << "Viewport: " << "top: " << viewport.top << " left: " << viewport.left << " width: " << viewport.width << " height: " << viewport.height << std::endl; 

  //vertical line through origin
  sf::Vertex yAxis[] = {sf::Vertex(sf::Vector2f(halfWidth, 0 + origin.y)), 
                       sf::Vertex(sf::Vector2f(halfWidth, window.getSize().y + origin.y))};
  yAxis[0].color = sf::Color::White;
  yAxis[1].color = sf::Color::White;

  window.draw(yAxis, 2, sf::Lines);

  //horizontal line through origin
  sf::Vertex xAxis[] = {sf::Vertex(sf::Vector2f(0 + origin.x ,window.getSize().y/2)), 
                       sf::Vertex(sf::Vector2f(window.getSize().x + origin.x , window.getSize().y/2))};
  xAxis[0].color = sf::Color::White;
  xAxis[1].color = sf::Color::White;

  window.draw(xAxis, 2, sf::Lines);
}

