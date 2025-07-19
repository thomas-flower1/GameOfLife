#include <iostream>

#include <SFML/Graphics.hpp>

int main() {

    const int pixel_size{16};
    const int height{pixel_size * 40};
    const int width{pixel_size * 60};


    sf::RenderWindow window(sf::VideoMode({width, height}), "Game of Life");


    sf::CircleShape circle{5};
    circle.setPosition(100, 100);


    while(window.isOpen()) {

        sf::Event event;
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        

        window.draw(circle);

        sf::Color white = sf::Color::White;
        window.clear(white);

        window.display();
    }


    return 0;
    
}