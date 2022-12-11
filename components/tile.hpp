#ifndef tile_hpp
#define tile_hpp

#include <iostream>
#include <SFML/Graphics.hpp>

#include "../utils/poppins.hpp"

using namespace std;
using namespace sf;

class Tile
{
private:
  RectangleShape rect{};
  string state = "";
  int index = -1;
  Text text{};
  Font font{};

public:
  Tile()
  {
    Poppins::regular(font);

    text.setFillColor(Color::Black);
    // text.setStyle(Text::Bold);
    // text.setString("O");

    rect.setFillColor(Color::White);
    // rect.setOutlineColor(Color::Black);
    // rect.setOutlineThickness(1.32);
  }

  string getState() { return this->state; }

  void changeState(string state) { this->state = state; }

  void setIndex(int index) { this->index = index; }

  void setSize(Vector2f size) { this->rect.setSize(size); }

  void setPositon(Vector2f position)
  {
    this->rect.setPosition(position);
  }

  void handleClicked(Event &event, RenderWindow &window, void (*callback)(int index))
  {
    if (event.type == Event::MouseButtonPressed)
    {
      double mX = Mouse::getPosition(window).x;
      double mY = Mouse::getPosition(window).y;
      if (rect.getGlobalBounds().contains(mX, mY))
        callback(this->index);
    }
  }

  void handleEvent(Event &event, RenderWindow &window)
  {
    if (event.type == Event::MouseButtonPressed)
    {
      double mX = Mouse::getPosition(window).x;
      double mY = Mouse::getPosition(window).y;
      if (rect.getGlobalBounds().contains(mX, mY))
        cout << "clicked! index: " << this->index << endl;
    }
  }

  void draw(RenderWindow &window)
  {
    text.setFont(font);
    text.setCharacterSize(48);

    double rectPosX = this->rect.getPosition().x;
    double rectPosY = this->rect.getPosition().y;

    double textW = this->text.getGlobalBounds().width;
    double textH = this->text.getLocalBounds().height;

    double marginX = (this->rect.getSize().x - textW) / 2;
    double marginY = (this->rect.getSize().y - textH) / 2;

    Vector2f textPos(rectPosX + marginX, rectPosY + marginY - 12);
    text.setPosition(textPos);

    if (this->state == "x")
    {
      text.setString("X");
    }
    else if (this->state == "o")
    {
      text.setString("O");
    }

    window.draw(rect);
    window.draw(text);
  }
};

#endif