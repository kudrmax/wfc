#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <execution>

const int W = 960;
const int H = 540;


int main() {

//    sf::Image image;
//    image.create(W, H);
//    sf::Texture texture;
//    sf::Sprite sprite;

    sf::RenderWindow window(sf::VideoMode(W, H), "Title");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}