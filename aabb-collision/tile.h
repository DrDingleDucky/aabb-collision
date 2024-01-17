#ifndef TILE_H
#define TILE_H

#include <sfml/Graphics.hpp>

class Tile {
  public:
    sf::RectangleShape rect;

    Tile(sf::Color color, sf::Vector2f size, sf::Vector2f pos);

    void draw(sf::RenderWindow &window);
};
#endif
