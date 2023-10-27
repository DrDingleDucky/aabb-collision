#include "tile.h"

Tile::Tile(sf::Color color, sf::Vector2f size, sf::Vector2f pos) {
    rect.setFillColor(color);
    rect.setSize(size);
    rect.setPosition(pos);
}

void Tile::draw(sf::RenderWindow &window) {
    window.draw(rect);
}
