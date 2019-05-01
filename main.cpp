#include <SFML/Graphics.hpp>
#include <iostream>

#include "include/mat2.h"
#include "include/vec2.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

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
    std::cout << "Triangle vertex " << i << ": " << "(" << triangle[i].at(0) << ", " << triangle[i].at(1) << ")" << std::endl;
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

void renderGrid(sf::RenderWindow& window, float scale)
{
  //scale is how big 1 unit is - ie if it is 300, 1 unit of the graph is 300 px

  int numVertLines = window.getSize().x/2 /scale;
  int numHorLines = window.getSize().y/2/scale;

  sf::Color lineColor = sf::Color(135,206,255);

  //draw vertical grid lines
  for(int i = 0; i < numVertLines; i++)
  {
    //we draw one to the right of the y axis
    sf::Vertex line[] = {sf::Vertex(sf::Vector2f(window.getSize().x/2 + i*scale, 0)), 
                          sf::Vertex(sf::Vector2f(window.getSize().x/2 + i*scale, window.getSize().y))};
    line[0].color = lineColor;
    line[1].color = lineColor;

    window.draw(line, 2, sf::Lines);

    //and one to the left
    sf::Vertex line2[] = {sf::Vertex(sf::Vector2f(window.getSize().x/2 - i*scale, 0)), 
                          sf::Vertex(sf::Vector2f(window.getSize().x/2 - i*scale, window.getSize().y))};
    line2[0].color = lineColor;
    line2[1].color = lineColor;

    window.draw(line2, 2, sf::Lines);
  }

  for(int i = 0; i < numHorLines; i++)
  {
    sf::Vertex line[] = {sf::Vertex(sf::Vector2f(0,window.getSize().y/2 + i*scale)), 
                       sf::Vertex(sf::Vector2f(window.getSize().x, window.getSize().y/2+i*scale))};
    line[0].color = lineColor;
    line[1].color = lineColor;

    window.draw(line, 2, sf::Lines);

    sf::Vertex line2[] = {sf::Vertex(sf::Vector2f(0,window.getSize().y/2 - i*scale)), 
                       sf::Vertex(sf::Vector2f(window.getSize().x, window.getSize().y/2-i*scale))};
    line2[0].color = lineColor;
    line2[1].color = lineColor;

    window.draw(line2, 2, sf::Lines);
  }


  //vertical line through origin
  sf::Vertex yAxis[] = {sf::Vertex(sf::Vector2f(window.getSize().x/2, 0)), 
                       sf::Vertex(sf::Vector2f(window.getSize().x/2, window.getSize().y))};
  yAxis[0].color = sf::Color::White;
  yAxis[1].color = sf::Color::White;

  window.draw(yAxis, 2, sf::Lines);

  //horizontal line through origin
  sf::Vertex xAxis[] = {sf::Vertex(sf::Vector2f(0,window.getSize().y/2)), 
                       sf::Vertex(sf::Vector2f(window.getSize().x, window.getSize().y/2))};
  xAxis[0].color = sf::Color::White;
  xAxis[1].color = sf::Color::White;

  window.draw(xAxis, 2, sf::Lines);
}

int main()
{
  sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT), "Vector Visualization");

  sf::Event e;

  Vec2 vec(1,2);

  while(window.isOpen())
  {
    while(window.pollEvent(e))
    {
      switch(e.type)
      {
        case sf::Event::Closed:
          window.close();
        break;
      }
    }

    window.clear();
    renderGrid(window, 100);
    renderVector(window, vec, sf::Color::Yellow, 100);
    window.display();
  }
}
