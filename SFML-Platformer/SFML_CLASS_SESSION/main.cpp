#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "CPlayer.h"
#include "CUIManager.h"
#include "CTile.h"
#include "CLevel.h"
#include "CEnemy.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "2D Platformer");
    window.setFramerateLimit(60);

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
    CPlayer g_Player(sf::Vector2f(44, 64), sf::Vector2f(100, 200), Player, false);
    newLevel.g_Objects.push_back(&g_Player);
    newLevel.g_PhysicsHandler.m_PhysicsObjects.push_back(&g_Player);
    newLevel.g_PhysicsHandler.SetTrackedPlayer(&g_Player);
    CUIManager g_UIManager(&g_Player);

    
    //create an Enemy
    CEnemy g_Enemy(sf::Vector2f(32, 32), sf::Vector2f(300, 200), EWalker, true);
    g_Enemy.SetTrackedPlayer(&g_Player);
    newLevel.g_Objects.push_back(&g_Enemy); 
    newLevel.g_PhysicsHandler.m_PhysicsObjects.push_back(&g_Enemy);
 

    //play background music
    //bgm.play();


    //load level 1
    newLevel.Loadlevel("Levels/Level1.txt");
    for (int i = 0; i < newLevel.m_LevelCollisionTiles.size(); i++)
    {
        newLevel.g_Objects.push_back(newLevel.m_LevelCollisionTiles[i]);//add the level tiles to the collision object list
        if (newLevel.m_LevelCollisionTiles[i]->m_Dynamic)
        {
            newLevel.g_PhysicsHandler.m_PhysicsObjects.push_back(newLevel.m_LevelCollisionTiles[i]);
        }
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Tab)
                {
                    g_Player.ToggleDynamic();
                }

                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) //shoot arrow
                {
                    if (g_Player.GetArrowCount() > 0)//if player has arrows
                    {
                        CArrow* newArrow = g_Player.Shoot();
                        newLevel.g_Objects.push_back(newArrow);
                        newLevel.g_PhysicsHandler.m_PhysicsObjects.push_back(newArrow);
                        g_Player.SetArrowCount(g_Player.GetArrowCount() - 1);//deincriment player arrows
                    }
                }
                if (event.key.code == sf::Keyboard::Enter)
                {
                    newLevel.UnloadLevel();
                    newLevel.Loadlevel("Levels/level2.txt");
                }
            }
        }
        CHelper::getInstance().CHelperUpdate();
        window.clear();

        newLevel.g_PhysicsHandler.MovementIntergration(newLevel.g_Objects);

        newLevel.g_PhysicsHandler.CollisionIntergration(newLevel.g_Objects);

        for (int i = 0; i < newLevel.g_PhysicsHandler.m_PhysicsObjects.size(); i++)
        {
            newLevel.g_PhysicsHandler.m_PhysicsObjects[i]->ApplyGravity(); //Apply gravity to all Dynamic Physics objects
        }

        for (int i = 0; i < newLevel.g_PhysicsHandler.m_PhysicsObjects.size(); i++)
        {
            newLevel.g_PhysicsHandler.m_PhysicsObjects[i]->Update(&window); //call update on all objects
        }

        newLevel.RenderBackground(&window);

        for (int i = 0; i < newLevel.g_Objects.size(); i++)
        {
            newLevel.g_Objects[i]->Render(&window);
        }

        newLevel.RenderForground(&window);

        g_UIManager.DrawPlayerHealth(&window);
        g_UIManager.DrawPlayerArrowStock(&window);

        window.display();
    }
    return 0;
}