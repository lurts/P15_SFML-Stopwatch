//Modul:    Programmieren 2 - Praktikum
//Datum:    16.05.24 - 16:12:25
//Name:     Lars Ebbeke
//Aufgabe:  P15_SFML_Stopwatch
//Todo:
//-

#include "stopwatch.h"

void button::setPos(sf::Vector2f nPosition){
    bPos = nPosition;
}

void button::setSize(sf::Vector2f nSize){
    bSize = nSize;
}

void button::setColour(sf::Color nColour){
    bColour = nColour;
}

void button::paint(sf::RenderWindow& window){
    sf::RectangleShape rect(bSize);
    rect.setPosition(bPos);
    rect.setFillColor(bColour);
    window.draw(rect);
}
