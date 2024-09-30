#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "CUIManager.h"
#include "CLevel.h"
#include "CButton.h"

int main()
{
    //Font
    sf::Font UIFont;
    UIFont.loadFromFile("Fonts/LEMONMILK-Regular.otf");

    // -- create Main Window -- //
    sf::RenderWindow MainWindow(sf::VideoMode(1280, 720), "2D Platformer");
    MainWindow.setFramerateLimit(60);
    // -- Main Window -- //

    // -- Debug Window -- //
    sf::RenderWindow DebugWindow(sf::VideoMode(400, 400), "Debug Picker");
    DebugWindow.setFramerateLimit(60);
    sf::RectangleShape DebugShape;
    DebugShape.setFillColor(sf::Color(128, 128, 128));
    DebugShape.setSize(sf::Vector2f(400, 400));

    CButton BtnHealth(sf::Vector2f(100, 100), &UIFont, sf::Vector2f(114, 40), "Refill Health");
    CButton BtnArrows(sf::Vector2f(100, 150), &UIFont, sf::Vector2f(114, 40), "Refill Arrows");
    CButton BtnDynamic(sf::Vector2f(100, 200), &UIFont, sf::Vector2f(114, 40), "Disable Gravity");
    CButton BtnInvul(sf::Vector2f(100, 250), &UIFont, sf::Vector2f(114, 40), "Toggle Invulnerability");
    // -- Debug Window -- //


    //create level
    CLevel newLevel;
    
    //music setup
    sf::Music bgm;
    if (!bgm.openFromFile("Sound/Diesel.mp3"))
    {
        printf("error Loading BGM");
    }
    bgm.setLoop(true);
    bgm.setVolume(100.0f);
    
    //create player
    CPlayer g_Player(sf::Vector2f(44, 64), sf::Vector2f(100, 200), Player, true);
    newLevel.m_Objects.push_back(&g_Player);
    newLevel.m_PlayerRef = &g_Player;
    newLevel.g_PhysicsHandler.SetTrackedPlayer(&g_Player);
    CUIManager g_UIManager(&g_Player);


    //play background music
    //bgm.play();

    //load level 1
    newLevel.Loadlevel("Levels/Level1.txt");
    g_Player.ReSpawn();

    while (MainWindow.isOpen())
    {
        sf::Event event;
        while (MainWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                MainWindow.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Tab)
                {
                    g_Player.ToggleDynamic();
                }

                if (event.key.code == sf::Keyboard::Escape)
                {
                    MainWindow.close();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) //shoot arrow
                {
                    if (g_Player.GetArrowCount() > 0)//if player has arrows
                    {
                        CArrow* newArrow = g_Player.Shoot();
                        newLevel.m_Objects.push_back(newArrow);
                        g_Player.SetArrowCount(g_Player.GetArrowCount() - 1);//deincriment player arrows
                    }
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tilde)) //Open Debug Window
                {
                    DebugWindow.create(sf::VideoMode(400, 400), "Debug Window");
                    DebugWindow.setPosition(sf::Vector2i(((sf::VideoMode::getDesktopMode().width / 2) - 912), 25));
                }
                if (event.key.code == sf::Keyboard::Enter)
                {
                    newLevel.UnloadLevel();
                    newLevel.Loadlevel("Levels/level2.txt");
                }
            }
        }
        sf::Event DebugEvent;
        while (DebugWindow.pollEvent(DebugEvent))
        {
            if (DebugEvent.type == sf::Event::Closed)
            {
                DebugWindow.close();
            }
            if (DebugEvent.type == sf::Event::MouseButtonPressed)
            {
                if (DebugEvent.mouseButton.button == sf::Mouse::Left)
                {
                    if (BtnHealth.GetShapeElement().getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(DebugWindow))))
                    {
                        newLevel.m_PlayerRef->SetPlayerLives(3);
                    }
                    if (BtnArrows.GetShapeElement().getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(DebugWindow))))
                    {
                        newLevel.m_PlayerRef->SetArrowCount(3);
                    }
                    if (BtnDynamic.GetShapeElement().getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(DebugWindow))))
                    {
                        newLevel.m_PlayerRef->ToggleDynamic();
                    }
                    if (BtnInvul.GetShapeElement().getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(DebugWindow))))
                    {
                        newLevel.m_PlayerRef->ToggleInvul();
                    }
                }
            }
        }

        CHelper::getInstance().CHelperUpdate();
        MainWindow.clear();

        newLevel.g_PhysicsHandler.MovementIntergration(newLevel.m_Objects);

        newLevel.g_PhysicsHandler.CollisionIntergration(newLevel.m_Objects);

        for (int i = 0; i < newLevel.m_Objects.size(); i++)
        {
            if(newLevel.m_Objects[i]->m_Dynamic)
            {
                newLevel.m_Objects[i]->ApplyGravity(); //Apply gravity to all Dynamic Physics objects
            }
        }

        for (int i = 0; i < newLevel.m_Objects.size(); i++)
        {
            newLevel.m_Objects[i]->Update(&MainWindow); //call update on all objects
        }

        newLevel.RenderBackground(&MainWindow);//render things behind
        newLevel.RenderForground(&MainWindow);//render things infront

        g_UIManager.DrawPlayerHealth(&MainWindow);
        g_UIManager.DrawPlayerArrowStock(&MainWindow);

        MainWindow.display();
    }
    return 0;
}