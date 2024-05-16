//Modul:    Programmieren 2 - Praktikum
//Datum:    16.05.24 - 16:12:25
//Name:     Lars Ebbeke
//Aufgabe:  P15_SFML_Stopwatch
//Todo:
//-

#include "stopwatch.h"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <iomanip>
#include <iostream>


#ifdef _WIN32
const std::string fontPath = "C:/Windows/Fonts/arial.ttf";
#elif __linux__
const std::string fontPath = "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"; // Example path on Linux
#endif

float getHandAngle(unsigned int elapsedTime, float secondsPerRotation){
    return (elapsedTime / (secondsPerRotation * 1000.0f)) * 360.0f;
}

void drawHand(unsigned int elapsedTime, sf::Vector2f position, sf::RenderWindow& window, sf::Vector2f size, sf::Color colour, float secondsPerRotation){
    sf::RectangleShape clockHand(size);
    clockHand.setOrigin(clockHand.getSize().x / 2, clockHand.getSize().y);
    clockHand.setPosition(position);
    clockHand.setFillColor(colour);

    float handAngle = getHandAngle(elapsedTime, secondsPerRotation);

    clockHand.setRotation(handAngle);
    window.draw(clockHand);
}

void showTime(unsigned int elapsedTime, sf::Vector2f position, sf::RenderWindow& window, int fontSize){
    // Create a font for text
    sf::Font font;
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Failed to load font" << std::endl;
        return;
    }

    sf::Text timeDisplay("", font, fontSize);
    timeDisplay.setFillColor(sf::Color::Black);
    timeDisplay.setPosition(position);
    timeDisplay.setString("00:00:00:000");

    // Calculate hours, minutes, seconds, and milliseconds
    unsigned int hours = elapsedTime / (1000 * 60 * 60);
    unsigned int minutes = (elapsedTime % (1000 * 60 * 60)) / (1000 * 60);
    unsigned int seconds = ((elapsedTime % (1000 * 60 * 60)) % (1000 * 60)) / 1000;
    unsigned int milliseconds = elapsedTime % 1000;

    std::stringstream timeString;
    timeString << std::setfill('0') << std::setw(2) << hours << ":"
               << std::setfill('0') << std::setw(2) << minutes << ":"
               << std::setfill('0') << std::setw(2) << seconds << ":"
               << std::setfill('0') << std::setw(3) << milliseconds;

    timeDisplay.setString(timeString.str());

    window.draw(timeDisplay);
}


//Functions for the button class
void button::setPos(sf::Vector2f nPosition){
    bPos = nPosition;
}

void button::setSize(sf::Vector2f nSize){
    bSize = nSize;
}

void button::setColour(sf::Color nColour){
    bColour = nColour;
}

bool button::isMe(sf::Vector2i position){
    return ((position.x > bPos.x) && (bPos.y < position.y && position.y < bPos.y + bSize.y));
};

void button::paint(sf::RenderWindow& window){
    sf::RectangleShape rect(bSize);
    rect.setPosition(bPos);
    rect.setFillColor(bColour);
    window.draw(rect);
}
