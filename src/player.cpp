#include "player.h"

Player::Player(float speed, sf::Color color, sf::Vector2f size, sf::Vector2f pos)
    : speed(speed), direction(sf::Vector2f(0.0f, 0.0f)) {
    rect.setFillColor(color);
    rect.setSize(size);
    rect.setPosition(pos);
}

void Player::update(sf::RenderWindow &window, float deltaTime, std::vector<Tile> &tileGroup) {
    horizontalMovement(deltaTime);
    horizontalCollisions(tileGroup);
    verticalMovement(deltaTime);
    verticalCollisions(tileGroup);
    camera(window);
}

void Player::draw(sf::RenderWindow &window) {
    window.draw(rect);
}

void Player::horizontalMovement(float deltaTime) {
    direction.x = 0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        direction.x = -1.0f;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        direction.x = 1.0f;
    }
    rect.move(sf::Vector2f(direction.x * deltaTime * speed, 0.0f));
}

void Player::horizontalCollisions(std::vector<Tile> &tileGroup) {
    for (auto &tile : tileGroup) {
        if (rect.getGlobalBounds().intersects(tile.rect.getGlobalBounds())) {
            if (direction.x > 0.0f) {
                rect.setPosition(sf::Vector2f(tile.rect.getGlobalBounds().left - rect.getSize().x, rect.getPosition().y));
            } else if (direction.x < 0.0f) {
                rect.setPosition(sf::Vector2f(tile.rect.getGlobalBounds().left + tile.rect.getSize().x, rect.getPosition().y));
            }
        }
    }
}

void Player::verticalMovement(float deltaTime) {
    direction.y = 0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        direction.y = -1.0f;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        direction.y = 1.0f;
    }
    rect.move(sf::Vector2f(0.0f, direction.y * deltaTime * speed));
}

void Player::verticalCollisions(std::vector<Tile> &tileGroup) {
    for (auto &tile : tileGroup) {
        if (rect.getGlobalBounds().intersects(tile.rect.getGlobalBounds())) {
            if (direction.y > 0.0f) {
                rect.setPosition(sf::Vector2f(rect.getPosition().x, tile.rect.getGlobalBounds().top - rect.getSize().y));
            } else if (direction.y < 0.0f) {
                rect.setPosition(sf::Vector2f(rect.getPosition().x, tile.rect.getGlobalBounds().top + tile.rect.getSize().y));
            }
        }
    }
}

void Player::camera(sf::RenderWindow &window) {
    if (rect.getPosition().x + rect.getSize().x / 2.0f < window.getView().getCenter().x - window.getSize().x / 2.0f) {
        window.setView(sf::View(sf::FloatRect(window.getView().getCenter().x - window.getSize().x / 2.0f * 3.0f,
                                              window.getView().getCenter().y - window.getSize().y / 2.0f, window.getSize().x, window.getSize().y)));
    } else if (rect.getPosition().x + rect.getSize().x / 2.0f > window.getView().getCenter().x + window.getSize().x / 2.0f) {
        window.setView(sf::View(sf::FloatRect(window.getView().getCenter().x + window.getSize().x / 2.0f * 3.0f,
                                              window.getView().getCenter().y + window.getSize().y / 2.0f, window.getSize().x, window.getSize().y)));
    } else if (rect.getPosition().y + rect.getSize().y / 2.0f < window.getView().getCenter().y - window.getSize().y / 2.0f) {
        window.setView(sf::View(sf::FloatRect(window.getView().getCenter().x + window.getSize().x / 2.0f,
                                              window.getView().getCenter().y - window.getSize().y / 2.0f * 3.0f, window.getSize().x, window.getSize().y)));
    } else if (rect.getPosition().y + rect.getSize().y / 2.0f > window.getView().getCenter().y + window.getSize().y / 2.0f) {
        window.setView(sf::View(sf::FloatRect(window.getView().getCenter().x - window.getSize().x / 2.0f,
                                              window.getView().getCenter().y + window.getSize().y / 2.0f * 3.0f, window.getSize().x, window.getSize().y)));
    }
}
