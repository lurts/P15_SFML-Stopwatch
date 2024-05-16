//Modul:    Programmieren 2 - Praktikum
//Datum:    16.05.24 - 15:38:33
//Name:     Lars Ebbeke
//Aufgabe:  P15_SFML-Stopwatch
//Todo:
//-

#include <iostream>
#include <SFML/Graphics.hpp>

//Konstanten
const unsigned int width = 900;
const unsigned int height = 600;

const int pink = 0xB00B69FF;

int main() {
    sf::RenderWindow window(sf::VideoMode(width, height), "FENSTER!");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        /* --Loesche Bildschirminhalt. */
        window.clear(sf::Color(0xFFFFFFFF));

        //Circle mit Farbe #B00B69 in der Mitte anzeigen
        unsigned int radius = 255;
        sf::CircleShape circle(radius);
        circle.setPosition(width/2-radius, height/2-radius);
        circle.setFillColor(sf::Color(pink));
        window.draw(circle);

        unsigned int buttonWidth = 300;
        unsigned int buttonHeight = 200;
        sf::RectangleShape buttonStart(sf::Vector2f(buttonWidth, buttonHeight));
        buttonStart.setPosition(width-buttonWidth, 0);
        buttonStart.setFillColor(sf::Color::Green);
        window.draw(buttonStart);


        /* --Aktualisiere Inhalt im Fenster. */
        window.display();
    }

    return 1;
}