//Modul:    Programmieren 2 - Praktikum
//Datum:    16.05.24 - 16:12:25
//Name:     Lars Ebbeke
//Aufgabe:  P15_SFML_Stopwatch
//Todo:
//-

#include "stopwatch.h"
#include <SFML/Graphics.hpp>
#include <iomanip>
#include <iostream>


float getHandAngle(unsigned int elapsedTime, float msPerRotation){
    return (elapsedTime / (msPerRotation)) * 360.0f;
}

void showTime(unsigned int elapsedTime, sf::Vector2f position, sf::RenderWindow& window, sf::Font font, int fontSize){

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
    return ((position.x > bPos.x && position.x < bPos.x + bSize.x) &&
            (position.y > bPos.y && position.y < bPos.y + bSize.y));
};

void button::paint(sf::RenderWindow& window){
    sf::RectangleShape rect(bSize);
    rect.setPosition(bPos);
    rect.setFillColor(bColour);
    window.draw(rect);
}


//Stuff for the clock hands
void clockHand::setPos(sf::Vector2f n_hPos) {
    hPos = n_hPos;
}

void clockHand::setSize(sf::Vector2f n_hSize) {
    hSize = n_hSize;
}

void clockHand::setColour(sf::Color n_hColour) {
    hColour = n_hColour;
}

void clockHand::paint(unsigned int elapsedTime, sf::RenderWindow &window) {
    sf::RectangleShape clockHand(hSize);
    clockHand.setOrigin(clockHand.getSize().x / 2, clockHand.getSize().y);
    clockHand.setPosition(hPos);
    clockHand.setFillColor(hColour);

    float handAngle = getHandAngle(elapsedTime, msPerRev);

    clockHand.setRotation(handAngle);
    window.draw(clockHand);
}


//main stopwatch things
void stopwatch::start(){
    if (!stopwatchActive) {
        stopwatchActive = true;
        startTime = std::chrono::high_resolution_clock::now();
        std::cout << "Start" << std::endl;
    }
}

void stopwatch::stop() {
    if (stopwatchActive) {
        savedTime = elapsedTime;
        stopwatchActive = false;
        std::cout << "Stop. Time (ms): " << elapsedTime << std::endl;
    }
}

void stopwatch::reset() {
    if (!stopwatchActive) {
        elapsedTime = 0;
        savedTime = 0;
        std::cout << "Reset" << std::endl;
    }
}

void stopwatch::update() {
    if (stopwatchActive){
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime);
        elapsedTime = duration.count();
        elapsedTime += savedTime;
    }
}

bool stopwatch::isActive() {
    return stopwatchActive;
}

int stopwatch::getElapsedTime() {
    return elapsedTime;
}