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
const int width     = 1200;
const int height    = 800;

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

    button* framerateToggle = new button(sf::Vector2f(50.0f, 50.0f), sf::Vector2f(0, 0), sf::Color(0xb0849dff));

    clockHand* secondsHand  = new clockHand(1000.0f,    sf::Vector2f((width - buttonWidth) / 2, height / 2), sf::Vector2f(10,radius - 75), sf::Color::Red);
    clockHand* minuteHand   = new clockHand(60000.0f,   sf::Vector2f((width - buttonWidth) / 2, height / 2), sf::Vector2f(10,radius - 50), sf::Color::Black);

    stopwatch* sw           = new stopwatch();

    //Circle mit Farbe #B00B69 in der Mitte anzeigen
    sf::CircleShape circle(radius, 50);
    circle.setPosition((width-buttonWidth)/2-radius, height/2-radius);
    circle.setFillColor(sf::Color::White);

    int smallRadius = radius / 25;
    sf::CircleShape smallCircle(smallRadius, 50);
    smallCircle.setPosition((width - buttonWidth) / 2 - smallRadius, height / 2 - smallRadius);
    smallCircle.setFillColor(sf::Color::Black);

    sf::Text fpsDisplay("60", font, 24);
    fpsDisplay.setFillColor(sf::Color::Black);
    fpsDisplay.setPosition(sf::Vector2f(5, 5));



    int framerateLimit          = 60;
    sf::RenderWindow window(sf::VideoMode(width, height), "Dies ist eine Stoppuhr, wer was anderes sagt der lugt!", sf::Style::Close);
    window.setFramerateLimit(framerateLimit);

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
                if (startButton->isMe(mousePos)){
                    sw->start();
                }

                //stop button event
                if (stopButton->isMe(mousePos)){
                    sw->stop();

                }

                //reset button event, but only when the stopwatch is stopped
                if (resetButton->isMe(mousePos)){
                    sw->reset();
                }

                //framerate toggle button event
                if (framerateToggle->isMe(mousePos)){
                    if (framerateLimit == 60) {
                        framerateLimit = 144;
                        framerateToggle->setColour(sf::Color(0xb00b69ff));
                        fpsDisplay.setString("144");
                    }
                    else {
                        framerateLimit = 60;
                        framerateToggle->setColour(sf::Color(0xb0849dff));
                        fpsDisplay.setString("60");
                    }

                    window.setFramerateLimit(framerateLimit);
                }
            }
        }


        sw->update();
        elapsedTime = sw->getElapsedTime();


        //Clear the screen with a solid colour, so we can draw new and exciting things
        window.clear(sf::Color(0x6e6e6eff));

        //draw the first circle, how exciting
        window.draw(circle);

        //this function is responsible for the digital readout at the bottom of the window
        showTime(elapsedTime,
                 sf::Vector2f(50, height - 50 - 24),
                 window,
                 font);

        //update the clock hands
        secondsHand->paint(elapsedTime, window);
        minuteHand->paint(elapsedTime, window);

        //make the buttons show up
        startButton->paint(window);
        stopButton->paint(window);
        resetButton->paint(window);

        framerateToggle->paint(window);

        //add a small circle to cover up where all the hands meet because without it it looks UGLY
        window.draw(smallCircle);

        window.draw(fpsDisplay);

        //refresh the window and finally display everything
        window.display();
    }

    //gotta get rid of those objects
    delete startButton;
    delete stopButton;
    delete resetButton;

    delete secondsHand;
    delete minuteHand;

    delete sw;

    return 1;
}