//Modul:    Programmieren 2 - Praktikum
//Datum:    16.05.24 - 15:38:33
//Name:     Lars Ebbeke
//Aufgabe:  P15_SFML-Stopwatch
//Todo:
//-

#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <iomanip>
#include "stopwatch.h"

#ifdef _WIN32
    const std::string fontPath = "C:/Windows/Fonts/arial.ttf";
#elif __linux__
    const std::string fontPath = "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"; // Example path on Linux
#endif

//Konstanten
const unsigned int      width           = 900;
const unsigned int      height          = 600;
const unsigned int      buttonWidth     = 300;
//const unsigned int      buttonHeight    = 200;

const unsigned int buttonHeight = height/3;

int main() {
    sf::RenderWindow window(sf::VideoMode(width, height), "Dies ist eine Stoppuhr, wer was anderes sagt der lugt!");
    window.setFramerateLimit(60);

    button* startButton     = new button(sf::Vector2f(buttonWidth, buttonHeight), sf::Vector2f(width-buttonWidth, 0),               sf::Color::Green);
    button* stopButton      = new button(sf::Vector2f(buttonWidth, buttonHeight), sf::Vector2f(width-buttonWidth, buttonHeight),    sf::Color::Red);
    button* resetButton     = new button(sf::Vector2f(buttonWidth, buttonHeight), sf::Vector2f(width-buttonWidth, 2*buttonHeight),  sf::Color::Blue);

    bool stopwatchActive = false;
    float handAngle = 0.;
    std::chrono::time_point startTime = std::chrono::high_resolution_clock::now();

    // Create a font for text
    sf::Font font;
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Failed to load font" << std::endl;
        return 1;
    }

    //Circle mit Farbe #B00B69 in der Mitte anzeigen
    unsigned int radius = 255;
    sf::CircleShape circle(radius, 50);
    circle.setPosition((width-buttonWidth)/2-radius, height/2-radius);
    circle.setFillColor(sf::Color::White);

    sf::RectangleShape clockHand(sf::Vector2f(10,250));
    clockHand.setOrigin(clockHand.getSize().x / 2, clockHand.getSize().y);
    clockHand.setPosition((width - buttonWidth) / 2, height / 2);
    clockHand.setFillColor(sf::Color::Black);

    sf::Text timeDisplay("", font, 24);
    timeDisplay.setFillColor(sf::Color::Black);
    timeDisplay.setPosition(50, height - 50);
    timeDisplay.setString("00:00:00:000");

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left)) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                //Start button event
                if ((mousePos.x > width-buttonWidth) && (0 < mousePos.y && mousePos.y < buttonHeight)) {
                    //enable stopwatch and mark start time
                    stopwatchActive = true;
                    startTime = std::chrono::high_resolution_clock::now();

                    std::cout << "start" << std::endl;
                }

                //stop button event
                if ((mousePos.x > width-buttonWidth) && (buttonHeight < mousePos.y && mousePos.y < 2*buttonHeight)){
                    //disable stopwatch
                    stopwatchActive = false;

                    std::cout << "stop" << std::endl;
                }

                //reset button event, but only when the stopwatch is stopped
                if ((mousePos.x > width-buttonWidth) && (2*buttonHeight < mousePos.y) && !stopwatchActive){
                    handAngle = 0;

                    std::cout << "reset" << std::endl;
                }
            }
        }

        if (stopwatchActive){
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime);
            unsigned int elapsedTime = duration.count();

            handAngle = getHandAngle(elapsedTime);

            std::cout << elapsedTime << "\t" << handAngle << std::endl;

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
        }


        /* --Loesche Bildschirminhalt. */
        window.clear(sf::Color(0x6e6e6eff));

        window.draw(circle);

        clockHand.setRotation(handAngle);
        window.draw(clockHand);

        window.draw(timeDisplay);

        startButton->paint(window);
        stopButton->paint(window);
        resetButton->paint(window);

        /* --Aktualisiere Inhalt im Fenster. */
        window.display();

        //std::cout << handAngle << "\t\t" << stopwatchActive << std::endl;
    }

    delete startButton;
    delete stopButton;
    delete resetButton;

    return 1;
}