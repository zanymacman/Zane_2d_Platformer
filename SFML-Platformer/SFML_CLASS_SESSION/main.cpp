#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include "CUIManager.h"
#include "CLevel.h"
#include "CButton.h"

int main()
{
    // -- Font
    sf::Font UIFont;
    UIFont.loadFromFile("Fonts/LEMONMILK-Regular.otf");

    // -- create Main Window -- //
    sf::RenderWindow MainWindow(sf::VideoMode(1280, 720), "2D Platformer");
    MainWindow.setFramerateLimit(60);
    // -- Main Window -- //

    // -- create Game View -- //
    sf::View MainCamera(sf::FloatRect(0.0f, 0.0f, 1280.0f, 720.0f));
    MainWindow.setView(MainCamera);
    MainCamera.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
    MainWindow.setView(MainWindow.getDefaultView());
    float fCameraMoveX = 0.0f;
    // -- Game View -- //

    // -- Initialize Debug Window -- //
    sf::RenderWindow DebugWindow;
    DebugWindow.setFramerateLimit(60);
    sf::RectangleShape DebugShape;
    DebugShape.setFillColor(sf::Color::Black);
    DebugShape.setSize(sf::Vector2f(400, 400));

    //create buttons for Debug
    CButton BtnHealth(sf::Vector2f(50, 100), &UIFont, sf::Vector2f(350, 40), "Refill Health");
    CButton BtnArrows(sf::Vector2f(50, 150), &UIFont, sf::Vector2f(350, 40), "Refill Arrows");
    CButton BtnDynamic(sf::Vector2f(50, 200), &UIFont, sf::Vector2f(350, 40), "Disable Gravity");
    CButton BtnInvul(sf::Vector2f(50, 250), &UIFont, sf::Vector2f(350, 40), "Toggle Invulnerability");
    CButton BtnRespawn(sf::Vector2f(50, 300), &UIFont, sf::Vector2f(350, 40), "Respawn Player");
    // -- Initialize Debug Window -- //

    //create level
    CLevel MainLevel;

    //music setup
    sf::Music bgm;
    if (!bgm.openFromFile("Sound/Diesel.mp3"))
    {
        printf("error Loading BGM");
    }
    bgm.setLoop(true);
    bgm.setVolume(20.0f);

    //create player
    CPlayer g_Player(sf::Vector2f(44, 64), sf::Vector2f(100, 200), Player, true);
    MainLevel.m_Objects.push_back(&g_Player);
    MainLevel.m_PlayerRef = &g_Player;
    CUIManager g_UIManager(&g_Player);

    //play background music
    //bgm.play(); --------------------------Disabled for Testing

    //load level 1
    MainLevel.Loadlevel("Levels/Level1.txt");

    //Main Game Window Loop
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
                        MainLevel.m_Objects.push_back(newArrow);
                        g_Player.SetArrowCount(g_Player.GetArrowCount() - 1);//deincriment player arrows
                    }
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tilde)) //Open Debug Window
                {
                    // -- Create Debug Window -- //
                    DebugWindow.create(sf::VideoMode(400, 400), "Debug Picker");
                    // -- Debug Window -- //
                }
                if (event.type == sf::Event::Resized)//if the Window is resized
                {
                    // update the Camera to the new size of the window
                    sf::FloatRect VisibleArea(0.f, 0.f, event.size.width, event.size.height);
                    MainWindow.setView(sf::View(VisibleArea));
                }
            }
        }

        //Debug Window Event loop
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
                    //Healths reset button
                    if (BtnHealth.GetShapeElement().getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(DebugWindow))))
                    {
                        MainLevel.m_PlayerRef->SetPlayerLives(3);
                    }
                    //Arrow Reset Button
                    if (BtnArrows.GetShapeElement().getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(DebugWindow))))
                    {
                        MainLevel.m_PlayerRef->SetArrowCount(3);
                    }
                    //Flying player Toggle Button
                    if (BtnDynamic.GetShapeElement().getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(DebugWindow))))
                    {
                        MainLevel.m_PlayerRef->ToggleDynamic();
                    }
                    //Invulurable Player Toggle Button
                    if (BtnInvul.GetShapeElement().getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(DebugWindow))))
                    {
                        MainLevel.m_PlayerRef->ToggleInvul();
                    }
                    if (BtnRespawn.GetShapeElement().getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(DebugWindow))))
                    {
                        MainLevel.m_PlayerRef->ReSpawn();
                    }
                }
            }
        }
        //Loop Helper Update
        CHelper::getInstance().CHelperUpdate();

        //Reset Main Window
        MainWindow.clear();

        //Move Objects that should move
        MainLevel.MovementIntergration(MainLevel.m_Objects);

        if (g_Player.m_ObjectShape.getPosition().y > 800.0f)
        {
            MainLevel.ResetLevel();
        }

        //Calculate collisions and move things away from each other
        MainLevel.CollisionIntergration(MainLevel.m_Objects);

        //Apply gravity to all Dynamic Physics objects
        for (int i = 0; i < MainLevel.m_Objects.size(); i++)
        {
            if(MainLevel.m_Objects[i]->m_Dynamic)
            {
                MainLevel.m_Objects[i]->ApplyGravity();
            }
        }

        //call update on all objects
        for (int i = 0; i < MainLevel.m_Objects.size(); i++)
        {
            MainLevel.m_Objects[i]->Update(&MainWindow);
        }

        fCameraMoveX = (g_Player.m_ObjectShape.getPosition().x - MainCamera.getCenter().x)* CHelper::getInstance().m_DeltaTme;
        //Camera Move Smoothly to Player
        MainCamera.move(sf::Vector2f(fCameraMoveX, 0));

        //Move UI with camera
        g_UIManager.MoveUI(sf::Vector2f(fCameraMoveX, 0));

        //Set camera to be drawn too.
        MainWindow.setView(MainCamera);

        //render things in the back layer
        MainLevel.RenderBackground(&MainWindow);
        //render things in the front layer
        MainLevel.RenderForground(&MainWindow);

        //Draw UI
        g_UIManager.DrawPlayerHealth(&MainWindow);
        g_UIManager.DrawPlayerArrowStock(&MainWindow);

        //Draw Debug Buttons
        BtnHealth.Draw(&DebugWindow);
        BtnArrows.Draw(&DebugWindow);
        BtnDynamic.Draw(&DebugWindow);
        BtnInvul.Draw(&DebugWindow);
        BtnRespawn.Draw(&DebugWindow);

        //Draw Window
        MainWindow.display();
        DebugWindow.display();
    }
    return 0;
}
