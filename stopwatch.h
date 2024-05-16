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
#include <chrono>

float getHandAngle(unsigned int elapsedTime, float secondsPerRotation);

void drawHand(unsigned int elapsedTime,
              sf::Vector2f position,
              sf::RenderWindow& window,
              sf::Vector2f size = sf::Vector2f(10, 200),
              sf::Color colour = sf::Color::Black,
              float secondsPerRotation = 60.0f);

void showTime(unsigned int elapsedTime,
              sf::Vector2f position,
              sf::RenderWindow& window,
              int fontSize = 24);


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

    bool isMe(sf::Vector2i position);

    void paint(sf::RenderWindow& window);
};