#include <SFML/Graphics.hpp>
#include <iostream>

#include "components/tile.hpp"
#include "utils/poppins.hpp"

using namespace sf;
using namespace std;

void tileClickCallback(int index);
void checkWinner();
void onClickButtonReset();

vector<Tile> vectorTile;
bool isX = true;
string winner = "-";

int main()
{
  RenderWindow window(VideoMode(1280, 720), "SFML | Starter Template", Style::Close);

  window.setFramerateLimit(60);

  double windowX = window.getSize().x;
  double windowY = window.getSize().y;
  double tileHeight = (windowY / 5);
  double tileMargin = 4;
  Vector2f tileSize(tileHeight, tileHeight);

  RectangleShape rectGameTile{};
  rectGameTile.setFillColor(Color::Black);

  double gameTileWidth = (tileSize.x * 3 + tileMargin * 2);

  rectGameTile.setSize(Vector2f(gameTileWidth, gameTileWidth));
  rectGameTile.setPosition(Vector2f(
      window.getView().getCenter().x - gameTileWidth / 2,
      window.getView().getCenter().y - gameTileWidth / 2));

generate_vector_tile:
  double positionX = 0;
  double positionY = window.getView().getCenter().y - (gameTileWidth / 2);

  int tileIndex = 0;
  for (int r = 0; r < 3; r++)
  {
    positionX = window.getView().getCenter().x - (gameTileWidth / 2);
    for (int c = 0; c < 3; c++)
    {
      Tile newTile{};
      newTile.setIndex(tileIndex);
      newTile.setSize(tileSize);
      newTile.setPositon(Vector2f(positionX, positionY));

      vectorTile.push_back(newTile);
      tileIndex++;

      positionX += (tileHeight + tileMargin);
    }

    positionY += (tileHeight + tileMargin);
  }

  // title
  Font font{};
  Poppins::regular(font);

  Text text{};
  text.setString("Tic Tac Toe");
  text.setFont(font);
  text.setCharacterSize(48);
  text.setStyle(Text::Bold);
  text.setFillColor(Color::Black);
  text.setPosition(Vector2f(window.getView().getCenter().x - text.getGlobalBounds().width / 2, 32));

  // text reset
  Text textReset{};
  textReset.setString("Press enter to reset the game...");
  textReset.setCharacterSize(24);
  textReset.setFillColor(Color::Black);
  textReset.setFont(font);
  textReset.setPosition(Vector2f(window.getView().getCenter().x - textReset.getLocalBounds().width / 2, window.getSize().y - textReset.getLocalBounds().height * 2));

  // text winner
  Text textWinner{};
  textWinner.setString("X WIN!");
  textWinner.setStyle(Text::Bold);
  textWinner.setFont(font);
  textWinner.setCharacterSize(72);
  textWinner.setFillColor(Color::Black);
  textWinner.setPosition(Vector2f(
      window.getView().getCenter().x - textWinner.getLocalBounds().width / 2, window.getView().getCenter().y - textWinner.getLocalBounds().height / 2 - 28));

  // text creator
  Text textCreator{};
  textCreator.setString("by. anggoro\n11/12/22");
  textCreator.setFillColor(Color(0, 0, 0, 150));
  textCreator.setFont(font);
  textCreator.setCharacterSize(12);
  textCreator.setPosition(Vector2f(16, 16));

  while (window.isOpen())
  {
    Event event{};
    while (window.pollEvent(event))
    {
      if (winner == "-")
      {
        for (int a = 0; a < vectorTile.size(); a++)
          vectorTile.at(a).handleClicked(event, window, &tileClickCallback);
      }
      else
      {
        if (event.type == Event::KeyPressed)
          if (event.key.code == Keyboard::Enter)
          {
            vectorTile.clear();
            isX = true;
            winner = "-";
            goto generate_vector_tile;
          }
      }

      if (event.type == Event::Closed)
        window.close();
    }

    window.clear(Color::White);

    window.draw(textCreator);

    if (winner == "-")
    {
      window.draw(text);
      window.draw(rectGameTile);

      for (int a = 0; a < vectorTile.size(); a++)
        vectorTile.at(a).draw(window);
    }
    else
    {
      textWinner.setString(winner == "x" ? "X WIN!" : "O WIN!");
      window.draw(textWinner);
      window.draw(textReset);
    }

    window.display();
  }

  return 0;
}

void onClickButtonReset()
{
  cout << "reset called" << endl;
}

void tileClickCallback(int index)
{
  if (vectorTile.at(index).getState().length() == 0)
  {
    vectorTile.at(index).changeState(isX ? "x" : "o");
    isX = !isX;

    checkWinner();
  }
}

void checkWinner()
{
  int checkIndexes[][3] = {
      {0, 1, 2},
      {3, 4, 5},
      {6, 7, 8},
      {0, 4, 8},
      {2, 4, 6},
  };

  string data = "";
  for (int a = 0; a < 5; a++)
  {
    data = "";
    for (int b = 0; b < 3; b++)
      data += vectorTile.at(checkIndexes[a][b]).getState();

    if (data.length() > 0)
    {
      if (data == "xxx")
      {
        cout << "X win!" << endl;
        winner = "x";
      }
      else if (data == "ooo")
      {
        cout << "O win!" << endl;
        winner = "o";
      }
    }
  }
}