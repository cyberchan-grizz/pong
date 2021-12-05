//
//  singlePlayer.hpp
//  pong
//
//  Created by Channing Christian on 5/3/21.
//  Copyright © 2021 Channing Christian. All rights reserved.
//

#ifndef singlePlayer_hpp
#define singlePlayer_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

#include "game.hpp"
#include "player.hpp"
#include "bot.hpp"

void transition_in_spg(sf::RenderWindow & window){
    return;
}

void transition_out_spg(sf::RenderWindow & window){
    return;
}

void sp_game(sf::RenderWindow & window, game_state & gameState){
    std::vector<text_box*> textBoxes;
    player player(0, window);
    text_box pScore("0");
    pScore.set_size(200);
    pScore.update();
    pScore.set_pos(window.getSize().x/2 + (pScore.getText().getGlobalBounds().width/2 + 50), 0);
    textBoxes.push_back(&pScore);
    
    bot bot(window);
    text_box bScore("0");
    bScore.set_size(200);
    bScore.update();
    bScore.set_pos(window.getSize().x/2 - (bScore.getText().getGlobalBounds().width/2 + 50), 0);
    textBoxes.push_back(&bScore);
    
    ball * b = new ball(&window, &player, &bot);
    
    bool breakLoop = false;
    
    transition_in_spg(window);
    
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
                        player.move_up();
                        break;
                    case sf::Keyboard::S:
                        player.move_down();
                        break;
                    default:
                        NULL;
                        break;
                }
            } else if(event.type == sf::Event::KeyReleased){
                switch(event.key.code){
                    case sf::Keyboard::W:
                        player.stop_moving();
                        break;
                    case sf::Keyboard::S:
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
            b = new ball(&window, &player, &bot);
            pScore.set_string(std::to_string(player.get_score()));
            pScore.update();
            startClock.restart();
        } else if(b->get_sprite().getPosition().x >= window.getSize().x){
            bot.inc_score();
            delete b;
            b = new ball(&window, &player, &bot);
            bScore.set_string(std::to_string(bot.get_score()));
            bScore.update();
            startClock.restart();
        }
        
        if(player.get_score() >= 10 || bot.get_score() >= 10){
            breakLoop = true;
        }
        
        b->set_rate(time);
        b->update();
        player.set_rate(time);
        player.update();
        bot.set_rate(time);
        bot.update(std::pair<double, double>(b->get_sprite().getPosition().x, b->get_sprite().getPosition().y));
        
        window.clear();
        window.draw(b->get_sprite());
        window.draw(player.get_sprite());
        window.draw(bot.get_sprite());
        for(text_box * tb : textBoxes){
            tb->set_rate(time);
            tb->update();
            window.draw(tb->getText());
        }
        window.display();
    }
}

#endif /* singlePlayer_hpp */
