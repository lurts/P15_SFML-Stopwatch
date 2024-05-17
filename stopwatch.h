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

void showTime(unsigned int elapsedTime,
              sf::Vector2f position,
              sf::RenderWindow& window,
              sf::Font font,
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



class clockHand {
private:
    int             msPerRev;
    sf::Vector2f    hPos;
    sf::Vector2f    hSize;
    sf::Color       hColour;

public:
    clockHand(int n_msPerRev, sf::Vector2f n_hPos, sf::Vector2f n_hSize, sf::Color n_hColour = sf::Color::Black)
            : msPerRev(n_msPerRev), hPos(n_hPos), hSize(n_hSize), hColour(n_hColour) {}

    void setPos(sf::Vector2f n_hPos);
    void setSize(sf::Vector2f n_hSize);
    void setColour(sf::Color n_hColour);

    void paint(unsigned int elapsedTime, sf::RenderWindow& window);
};



class stopwatch {
private:
    unsigned int elapsedTime;
    unsigned int savedTime;
    std::chrono::high_resolution_clock ::time_point startTime;

    bool stopwatchActive;

public:
    stopwatch() : stopwatchActive(false), elapsedTime(0), savedTime(0) {}

    void start();
    void stop();
    void reset();

    void update();

    bool isActive();
    int getElapsedTime();
};