//Modul:    Programmieren 2 - Praktikum
//Datum:    16.05.24 - 16:12:25
//Name:     Lars Ebbeke
//Aufgabe:  P15_SFML_Stopwatch
//Todo:
//-

#ifndef P15_SFML_STOPWATCH_STOPWATCH_H
#define P15_SFML_STOPWATCH_STOPWATCH_H

#endif //P15_SFML_STOPWATCH_STOPWATCH_H

#include <SFML/Graphics.hpp>

class button {
private:
    sf::Vector2f bPos;
    sf::Vector2f bSize;
    sf::Color bColour;
public:
    button(sf::Vector2f size, sf::Vector2f position = sf::Vector2f(0, 0), sf::Color n_colour = sf::Color(0xFFFFFFFF))
        :bSize(size), bPos(position), bColour(n_colour){};

    void setPos(sf::Vector2f n_pos);
    void setSize(sf::Vector2f n_size);
    void setColour(sf::Color n_colour);

    void paint(sf::RenderWindow& window);
};