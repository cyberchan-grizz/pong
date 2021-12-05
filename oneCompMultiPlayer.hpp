//
//  oneCompMultiPlayer.hpp
//  pong
//
//  Created by Channing Christian on 5/10/21.
//  Copyright © 2021 Channing Christian. All rights reserved.
//

#ifndef oneCompMultiPlayer_hpp
#define oneCompMultiPlayer_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

#include "game.hpp"

void one_comp_multi_player(sf::RenderWindow & window, game_state & gameState){
    std::vector<text_box*> textBoxes;
    class player player(0, window);
    text_box pScore("0");
    pScore.set_size(200);
    pScore.update();
    pScore.set_pos(window.getSize().x/2 + (pScore.getText().getGlobalBounds().width/2 + 50), 0);
    textBoxes.push_back(&pScore);
    
    class player player2(1, window);
    text_box bScore("0");
    bScore.set_size(200);
    bScore.update();
    bScore.set_pos(window.getSize().x/2 - (bScore.getText().getGlobalBounds().width/2 + 50), 0);
    textBoxes.push_back(&bScore);
    
    ball * b = new ball(&window, &player, &player2);
    
    bool breakLoop = false;
    
    sf::Clock clock;
    double time;
    
    sf::Clock startClock;
    double startTime;
    while(breakLoop == false){
        time = clock.getElapsedTime().asMilliseconds();
        clock.restart();
        
        startTime = startClock.getElapsedTime().asSeconds();
        if(startTime > 3 && startTime < 3.2){
            b->set_movement(sf::Vector2f(1, 1));
        }
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                gameState = CLOSE_WINDOW;
                breakLoop = true;
                break;
            } else if(event.type == sf::Event::KeyPressed){
                switch(event.key.code){
                    case sf::Keyboard::W:
                        player2.move_up();
                        break;
                    case sf::Keyboard::S:
                        player2.move_down();
                        break;
                    case sf::Keyboard::Up:
                        player.move_up();
                        break;
                    case sf::Keyboard::Down:
                        player.move_down();
                        break;
                    default:
                        NULL;
                        break;
                }
            } else if(event.type == sf::Event::KeyReleased){
                switch(event.key.code){
                    case sf::Keyboard::W:
                        player2.stop_moving();
                        break;
                    case sf::Keyboard::S:
                        player2.stop_moving();
                        break;
                    case sf::Keyboard::Up:
                        player.stop_moving();
                        break;
                    case sf::Keyboard::Down:
                        player.stop_moving();
                        break;
                    default:
                        NULL;
                        break;
                }
            }
        }
        
        if(breakLoop == true){
            break;
        }
        
        if(b->get_sprite().getPosition().x <= 0){
            player.inc_score();
            delete b;
            b = new ball(&window, &player, &player2);
            pScore.set_string(std::to_string(player.get_score()));
            pScore.update();
            startClock.restart();
        } else if(b->get_sprite().getPosition().x >= window.getSize().x){
            player2.inc_score();
            delete b;
            b = new ball(&window, &player, &player2);
            bScore.set_string(std::to_string(player2.get_score()));
            bScore.update();
            startClock.restart();
        }
        
        if(player.get_score() >= 10 || player2.get_score() >= 10){
            breakLoop = true;
        }
        
        b->set_rate(time);
        b->update();
        player.set_rate(time);
        player.update();
        player2.set_rate(time);
        player2.update();
        
        window.clear();
        window.draw(b->get_sprite());
        window.draw(player.get_sprite());
        window.draw(player2.get_sprite());
        for(text_box * tb : textBoxes){
            tb->set_rate(time);
            tb->update();
            window.draw(tb->getText());
        }
        window.display();
    }
}

#endif /* oneCompMultiPlayer_hpp */
