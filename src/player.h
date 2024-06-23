#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include "tile.h"

class Player {
    public:
        Player(float speed, sf::Color color, sf::Vector2f size, sf::Vector2f pos);

        void update(sf::RenderWindow &window, float deltaTime, std::vector<Tile> &tileGroup);

        void draw(sf::RenderWindow &window);

        private:
        float speed;

        sf::Vector2f direction;
        sf::RectangleShape rect;

        void horizontalMovement(float deltaTime);

        void horizontalCollisions(std::vector<Tile> &tileGroup);

        void verticalMovement(float deltaTime);

        void verticalCollisions(std::vector<Tile> &tileGroup);

        void camera(sf::RenderWindow &window);
};
#endif
