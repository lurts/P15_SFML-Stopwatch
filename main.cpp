//Modul:    Programmieren 2 - Praktikum
//Datum:    16.05.24 - 15:38:33
//Name:     Lars Ebbeke
//Aufgabe:  P15_SFML-Stopwatch
//Todo:
//-

#include <iostream>
#include <SFML/Graphics.hpp>

//Konstanten
const unsigned int width = 500;
const unsigned int height = 500;

int main() {
    sf::RenderWindow window(sf::VideoMode(width, height), "FENSTER!");
    window.setFramerateLimit(50);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        /* --Loesche Bildschirminhalt. */
        window.clear(sf::Color(255,255,255));

        /* --Aktualisiere Inhalt im Fenster. */
        window.display();
    }
}