//Modul:    Programmieren 2 - Praktikum
//Datum:    16.05.24 - 15:38:33
//Name:     Lars Ebbeke
//Aufgabe:  P15_SFML-Stopwatch
//Todo:
//-

#include <iostream>
#include <SFML/Graphics.hpp>
#include "stopwatch.h"

//Konstanten
const unsigned int      width           = 900;
const unsigned int      height          = 600;
const unsigned int      buttonWidth     = 300;
const unsigned int      buttonHeight    = 200;


int main() {
    sf::RenderWindow window(sf::VideoMode(width, height), "FENSTER!");
    window.setFramerateLimit(60);

    button* startButton     = new button(sf::Vector2f(buttonWidth, buttonHeight), sf::Vector2f(width-buttonWidth, 0),               sf::Color::Green);
    button* stopButton      = new button(sf::Vector2f(buttonWidth, buttonHeight), sf::Vector2f(width-buttonWidth, buttonHeight),    sf::Color::Red);
    button* resetButton     = new button(sf::Vector2f(buttonWidth, buttonHeight), sf::Vector2f(width-buttonWidth, 2*buttonHeight),  sf::Color::Blue);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        /* --Loesche Bildschirminhalt. */
        window.clear(sf::Color(0x6e6e6eff));

        //Circle mit Farbe #B00B69 in der Mitte anzeigen
        unsigned int radius = 255;
        sf::CircleShape circle(radius);
        circle.setPosition((width-buttonWidth)/2-radius, height/2-radius);
        circle.setFillColor(sf::Color::White);
        window.draw(circle);

        startButton->paint(window);
        stopButton->paint(window);
        resetButton->paint(window);

        /* --Aktualisiere Inhalt im Fenster. */
        window.display();
    }

    delete startButton;
    delete stopButton;
    delete resetButton;

    return 1;
}