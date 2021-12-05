//
//  startScreen.hpp
//  pong
//
//  Created by Channing Christian on 5/3/21.
//  Copyright © 2021 Channing Christian. All rights reserved.
//

#ifndef startScreen_hpp
#define startScreen_hpp

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "game.hpp"
#include "textBox.hpp"
#include "ball.hpp"

void transistion_in_ss(sf::RenderWindow & window, std::vector<text_box*> textBoxes){
    int count = 0;
    double yPos = 200;
    
    sf::Clock clock;
    double time;
    
    bool anamationOver = false;
    while(anamationOver == false){
        time = clock.getElapsedTime().asMilliseconds();
        clock.restart();
        if(textBoxes[count]->getText().getPosition().y <= yPos){
            textBoxes[count]->set_movement(sf::Vector2f(0, 3));
        } else {
            textBoxes[count]->set_movement(sf::Vector2f(0, 0));
            textBoxes[count]->set_pos(textBoxes[count]->getText().getPosition().x, yPos);
            if(count + 1 < textBoxes.size()){
                count++;
                if(count == 1){
                    yPos = yPos + 200;
                } else {
                    yPos = yPos + 100;
                }
                
            } else {
                anamationOver = true;
                break;
            }
        }
        
        window.clear();
        for(text_box * tb : textBoxes){
            tb->set_rate(time);
            tb->update();
            window.draw(tb->getText());
        }
        window.display();
    }
}

void transition_out_ss(sf::RenderWindow & window, std::vector<text_box*> textBoxes){
    int count = 0;
    double yPos = -200;
    
    sf::Clock clock;
    double time;
    
    bool anamationOver = false;
    while(anamationOver == false){
        time = clock.getElapsedTime().asMilliseconds();
        clock.restart();
        if(textBoxes[count]->getText().getPosition().y >= yPos){
            textBoxes[count]->set_movement(sf::Vector2f(0, -3));
        } else {
            textBoxes[count]->set_movement(sf::Vector2f(0, 0));
            textBoxes[count]->set_pos(textBoxes[count]->getText().getPosition().x, yPos);
            if(count + 1 < textBoxes.size()){
                count++;
            } else {
                anamationOver = true;
                break;
            }
        }
        
        window.clear();
        for(text_box * tb : textBoxes){
            tb->set_rate(time);
            tb->update();
            window.draw(tb->getText());
        }
        window.display();
    }
}

void start_screen(sf::RenderWindow &window, game_state &gameState){
    std::vector<text_box*> textBoxes;
    text_box title("pong");
    title.set_size(150);
    title.update();
    title.set_pos(1000, -200);
    textBoxes.push_back(&title);
    
    text_box sp("Single Player");
    sp.set_size(100);
    sp.update();
    sp.set_pos(1000, -200);
    textBoxes.push_back(&sp);
    
    text_box mp("Multiplayer");
    mp.set_size(100);
    mp.update();
    mp.set_pos(1000, -200);
    textBoxes.push_back(&mp);
    
    transistion_in_ss(window, textBoxes);
    
    sf::Clock clock;
    double time;
    
    bool breakLoop = false;
    while(breakLoop == false){
        if(breakLoop == true){
            break;
        }
        time = clock.getElapsedTime().asMilliseconds();
        clock.restart();
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                gameState = CLOSE_WINDOW;
                breakLoop = true;
                break;
            }
        }
        
        if(sp.getText().getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
            gameState = SINGLE_PLAYER;
            breakLoop = true;
            break;
        }
        
        if(mp.getText().getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
            gameState = MULTIPLAYER_MENU;
            breakLoop = true;
            break;
        }
        
        if(breakLoop == true){
            break;
        }
        
        window.clear();
        for(int i = 0; i < textBoxes.size(); i++){
            text_box * tb = textBoxes[i];
            if(i != 0){
                if(tb->getText().getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
                    if(tb->getText().getCharacterSize() < 110){
                        tb->reset_size(110);
                    }
                } else {
                    if(tb->getText().getCharacterSize() > 100){
                        tb->reset_size(100);
                    }
                }
            }
            tb->set_rate(time);
            tb->update();
            window.draw(tb->getText());
        }
        window.display();
    }
    transition_out_ss(window, textBoxes);
}

#endif /* startScreen_hpp */
