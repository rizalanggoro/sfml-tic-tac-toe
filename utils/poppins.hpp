#ifndef poppins_hpp
#define poppins_hpp

#include <SFML/Graphics.hpp>
#include <iostream>

class Poppins
{
public:
  static void regular(sf::Font &font)
  {
    if (!font.loadFromFile("assets/fonts/Poppins-Regular.ttf"))
      std::cout << "poppins: failed to load regular" << std::endl;
  }
};

#endif