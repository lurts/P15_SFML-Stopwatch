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
    int xPos;
    int yPos;
    int buttonWidth;
    int buttonHeight;
    sf::Color colour;
public:
    button(int n_buttonWidth, int n_buttonHeight, int n_xPos=0, int n_yPos=0, sf::Color n_colour=sf::Color(0xFFFFFFFF))
        :xPos(n_xPos), yPos(n_yPos), buttonWidth(n_buttonWidth), buttonHeight(n_buttonHeight), colour(n_colour){};

    void setPos(sf::Vector2f n_pos);
    void setSize(sf::Vector2f n_size);
    void setColour(sf::Color n_colour);

    void paint(sf::RenderWindow& window);

};