#include <SFML/Graphics.hpp>
#include <iostream>

#include "include/mat2.h"
#include "include/vec2.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

void renderVector(sf::RenderWindow& window, Vec2& vec, sf::Color color, float scale)
{
  //this line is the vector that we are currently drawing
  sf::Vertex line[] = {sf::Vertex(sf::Vector2f(window.getSize().x/2, window.getSize().y/2)), 
                       sf::Vertex(sf::Vector2f(window.getSize().x/2 + vec.at(0)*scale, window.getSize().y/2 - vec.at(1)*scale))};
  line[0].color = color;
  line[1].color = color;

  window.draw(line, 2, sf::Lines);

  //this is our triangle, originally pointing on the x axis -->
  Vec2 triangle[] = {Vec2(1,0), Vec2(0.9, 0.04), Vec2(0.9,-0.04)};

  //now we create a transformation matrix out of the Vector that we are drawing
  //and multiply all the vertices in the triangle by this transformation matrix

  // Mat2 transform(vec.at(0), -1*vec.at(1), vec.at(1), vec.at(0));
  Mat2 transform(vec.at(0), -1*vec.at(1), 
                 vec.at(1), vec.at(0));

  for(int i = 0; i < 3; i++)
  {
    triangle[i] = triangle[i]*scale;
    triangle[i] = transform*triangle[i];
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

  std::cout << "origin x: " << origin.x << " y: " << origin.y << std::endl;

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

int main()
{
  sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT), "Vector Visualization");
  window.setVerticalSyncEnabled(false);

  sf::Event e;

  Vec2 vec(1,2);

  sf::Clock clock;
  sf::Time dt;

  float scale = 100;

  sf::Vector2i mousePos;
  sf::Vector2i origin = sf::Vector2i(window.getSize().x/2, window.getSize().y/2);

  bool viewMoving = false;

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
        case sf::Event::MouseButtonPressed:
        {
          if (!viewMoving)
            mousePos = sf::Mouse::getPosition();
          viewMoving = true;
          // origin += (mousePos - sf::Mouse::getPosition());
        }break;
        case sf::Event::MouseButtonReleased:
        {
          viewMoving = false;
          origin += (mousePos - sf::Mouse::getPosition());
        }break;
        case sf::Event::TextEntered:
        {

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
    vec.rotate(34*dt.asSeconds());

    //rendering sequence
    window.clear();
    sf::Vector2i tempOrigin = origin;
    if (viewMoving)
      tempOrigin += deltaMove;
    renderGrid(window, scale, tempOrigin);
    renderVector(window, vec, sf::Color::Yellow, scale);
    window.display();
  }
}
