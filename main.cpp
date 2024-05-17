//Modul:    Programmieren 2 - Praktikum
//Datum:    16.05.24 - 15:38:33
//Name:     Lars Ebbeke
//Aufgabe:  P15_SFML-Stopwatch
//Todo:
//-

#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>
#include "stopwatch.h"

#ifdef _WIN32
    const std::string fontPath = "C:/Windows/Fonts/arial.ttf";
#elif __linux__
    const std::string fontPath = "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"; // Example path on Linux
#endif

//Konstanten
const int width     = 900;
const int height    = 600;

const int buttonWidth = width/3;
const int buttonHeight = height/3;

const int radius    = std::min((height - 100) / 2, (width - buttonWidth - 100) / 2);

int main() {
    bool stopwatchActive = false;
    std::chrono::time_point startTime = std::chrono::high_resolution_clock::now();
    unsigned int elapsedTime = 0;
    unsigned int savedTime = 0;

    // Create a font for text
    sf::Font font;
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Failed to load font" << std::endl;
        return 1;
    }

    button* startButton     = new button(sf::Vector2f(buttonWidth, buttonHeight), sf::Vector2f(width-buttonWidth, 0),               sf::Color::Green);
    button* stopButton      = new button(sf::Vector2f(buttonWidth, buttonHeight), sf::Vector2f(width-buttonWidth, buttonHeight),    sf::Color::Red);
    button* resetButton     = new button(sf::Vector2f(buttonWidth, buttonHeight), sf::Vector2f(width-buttonWidth, 2*buttonHeight),  sf::Color::Blue);

    //Circle mit Farbe #B00B69 in der Mitte anzeigen
    sf::CircleShape circle(radius, 50);
    circle.setPosition((width-buttonWidth)/2-radius, height/2-radius);
    circle.setFillColor(sf::Color::White);

    int smallRadius = radius / 25;
    sf::CircleShape smallCircle(smallRadius, 50);
    smallCircle.setPosition((width - buttonWidth) / 2 - smallRadius, height / 2 - smallRadius);
    smallCircle.setFillColor(sf::Color::Black);


    sf::RenderWindow window(sf::VideoMode(width, height), "Dies ist eine Stoppuhr, wer was anderes sagt der lugt!", sf::Style::Close);
    window.setFramerateLimit(60);

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
                if (startButton->isMe(mousePos) && !stopwatchActive){
                    //enable stopwatch and mark start time
                    stopwatchActive = true;
                    startTime = std::chrono::high_resolution_clock::now();

                    std::cout << "start" << std::endl;
                }

                //stop button event
                if (stopButton->isMe(mousePos) && stopwatchActive){
                    //save time in case we want to resume
                    savedTime = elapsedTime;
                    std::cout << "Time (ms): " << elapsedTime << std::endl;

                    stopwatchActive = false;

                    std::cout << "stop" << std::endl;
                }

                //reset button event, but only when the stopwatch is stopped
                if (resetButton->isMe(mousePos) && !stopwatchActive){
                    elapsedTime = 0;
                    savedTime = 0;

                    std::cout << "reset" << std::endl;
                }
            }
        }

        //as long as the stopwatch is allowed to do stopwatch things we keep updating the elapsedTime with the current time
        if (stopwatchActive){
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime);
            elapsedTime = duration.count();
            elapsedTime += savedTime;
        }


        //Clear the screen with a solid colour, so we can draw new and exciting things
        window.clear(sf::Color(0x6e6e6eff));

        //draw the first circle, how exciting
        window.draw(circle);

        //this function is responsible for the digital readout at the bottom of the window
        showTime(elapsedTime,
                 sf::Vector2f(50, height - 50),
                 window);

        //Rotate once a second
        drawHand(elapsedTime,
                 sf::Vector2f((width - buttonWidth) / 2, height / 2),
                 window,
                 sf::Vector2f(10,radius - 50),
                 sf::Color::Red,
                 1.0f);

        //rotate once a minute
        drawHand(elapsedTime,
                 sf::Vector2f((width - buttonWidth) / 2, height / 2),
                 window,
                 sf::Vector2f(10,radius - 50),
                 sf::Color::Black,
                 60.0f);

        //rotate once a hour
        drawHand(elapsedTime,
                 sf::Vector2f((width - buttonWidth) / 2, height / 2),
                 window,
                 sf::Vector2f(10,radius - 50),
                 sf::Color::Green,
                 60.0f*60.0f);

        //make the buttons show up
        startButton->paint(window);
        stopButton->paint(window);
        resetButton->paint(window);

        //add a small circle to cover up where all the hands meet because without it it looks UGLY
        window.draw(smallCircle);

        //refresh the window and finally display everything
        window.display();
    }

    //gotta get rid of those objects
    delete startButton;
    delete stopButton;
    delete resetButton;

    return 1;
}