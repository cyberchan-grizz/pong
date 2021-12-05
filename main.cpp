
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Misc./ResourcePath.hpp"
#include "startScreen.hpp"
#include "multiPlayerMenu.hpp"
#include "singlePlayer.hpp"
#include "oneCompMultiPlayer.hpp"
#include "game.hpp"
#include "ball.hpp"

int main(){
    game_state gameState = START_SCREEN;
    
    sf::RenderWindow window(sf::VideoMode(2000, 1000), "Pong");
    window.setFramerateLimit(120);
    
    sf::Clock c;
    double time;
    
    while(window.isOpen()){
        time = c.getElapsedTime().asMilliseconds();
        c.restart();
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                gameState = CLOSE_WINDOW;
            }
        }
        switch(gameState){
            case(CLOSE_WINDOW):
                window.close();
                break;
            case(START_SCREEN):
                start_screen(window, gameState);
                break;
            case(MULTIPLAYER_MENU):
                multiPlayerMenu(window, gameState);
                break;
            case(SINGLE_PLAYER):
                sp_game(window, gameState);
                break;
            case(ONE_COMP_MULTI_PLAYER):
                one_comp_multi_player(window, gameState);
                break;
        }
    }
}
