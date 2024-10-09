#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include "CTimeKeeper.h" 

int main()
{
    // -- Font
    sf::Font UIFont;
    UIFont.loadFromFile("Fonts/LEMONMILK-Regular.otf");

    // -- Main Window -- //
    sf::RenderWindow MainWindow(sf::VideoMode(1280, 720), "2D Platformer");
    MainWindow.setFramerateLimit(60);
    // -- Main Window -- //

    // -- Game View -- //
    sf::View MainCamera(sf::FloatRect(0.0f, 0.0f, 1280.0f, 720.0f));
    MainWindow.setView(MainCamera);
    MainCamera.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
    MainWindow.setView(MainWindow.getDefaultView());
    float fCameraMoveX = 0.0f;
    // -- Game View -- //

    while (MainWindow.isOpen())
    {
        sf::Event event;
        while (MainWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                MainWindow.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    MainWindow.close();
                }
            }
            if (event.type == sf::Event::Resized)//if the Window is resized
            {
                // update the Camera to the new size of the window
                sf::FloatRect VisibleArea(0.f, 0.f, event.size.width, event.size.height);
                MainWindow.setView(sf::View(VisibleArea));
            }
        }
        CTimeKeeper::getInstance().CTimeKeeperUpdate();

        //Reset Main Window
        MainWindow.clear();

        //Set camera to be drawn too.
        MainWindow.setView(MainCamera);

        //Draw Window
        MainWindow.display();
    }

    system("pause");
    return 0;
}
