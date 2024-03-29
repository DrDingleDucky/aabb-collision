#include "player.h"
#include <fstream>
#include <sfml/Graphics.hpp>
#include <vector>

void loadLevel(std::string map, std::vector<Player> &playerGroup, std::vector<Tile> &tileGroup) {
    std::ifstream file(map);
    std::string line;

    float x;
    float y;

    unsigned int column_index = 0;

    while (std::getline(file, line)) {
        for (unsigned int row_index = 0; row_index < line.length(); row_index++) {
            x = row_index * 48.0f;
            y = column_index * 48.0f;

            if (line[row_index] == 't') { // t - tile
                tileGroup.push_back(Tile(sf::Color(0, 0, 0), sf::Vector2f(48.0f, 48.0f), sf::Vector2f(x, y)));
            } else if (line[row_index] == 'p') { // p - player
                playerGroup.push_back(Player(
                    255.0f,                     // player speed
                    sf::Color(255, 255, 255),   // player colour
                    sf::Vector2f(48.0f, 48.0f), // player size
                    sf::Vector2f(x, y)));       // player position
            }
        }
        column_index++;
    }
}

int main() {
    std::string winTitle = "sfml aabb collision";
    int winWidth = 1200;
    int winHeight = 816;

    sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), winTitle, sf::Style::Close);
    window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - winWidth / 2, sf::VideoMode::getDesktopMode().height / 2 - winHeight / 2));

    std::vector<Player> playerGroup;
    std::vector<Tile> tileGroup;

    loadLevel(std::string("map.txt"), playerGroup, tileGroup);

    sf::Clock clock;
    float deltaTime;

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }

        deltaTime = clock.restart().asSeconds();

        for (auto &player : playerGroup) {
            player.update(window, deltaTime, tileGroup);
        }

        window.clear(sf::Color(64, 64, 64));

        for (auto &tile : tileGroup) {
            tile.draw(window);
        }

        for (auto &player : playerGroup) {
            player.draw(window);
        }

        window.display();
    }
    return 0;
}
