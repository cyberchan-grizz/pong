//
//  multiPlayerMenu.hpp
//  pong
//
//  Created by Channing Christian on 5/10/21.
//  Copyright © 2021 Channing Christian. All rights reserved.
//

#ifndef multiPlayerMenu_hpp
#define multiPlayerMenu_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

#include "game.hpp"
#include "textBox.hpp"

void transition_in_mpm(sf::RenderWindow & window, std::vector<text_box*> textBoxes){
    int count = 0;
    double yPos = 300;
    
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
                yPos = yPos + 100;
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

void transition_out_mpm(sf::RenderWindow & window, std::vector<text_box*> textBoxes){
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

void multiPlayerMenu(sf::RenderWindow & window, game_state & gameState){
    std::vector<text_box*> textBoxes;
    text_box oneComp("one computer");
    oneComp.set_size(100);
    oneComp.update();
    oneComp.set_pos(1000, -200);
    textBoxes.push_back(&oneComp);
    
    text_box local("local");
    local.set_size(100);
    local.update();
    local.set_pos(1000, -200);
    textBoxes.push_back(&local);
    
    text_box online("online");
    online.set_size(100);
    online.update();
    online.set_pos(1000, -200);
    textBoxes.push_back(&online);
    
    text_box back("back");
    back.set_size(100);
    back.update();
    back.set_pos(1000, -200);
    textBoxes.push_back(&back);
    
    transition_in_mpm(window, textBoxes);
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
        
        if(breakLoop == true){
            break;
        }
        
        if(oneComp.getText().getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
            gameState = ONE_COMP_MULTI_PLAYER;
            breakLoop = true;
            break;
        }
        
        if(local.getText().getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
            gameState = LOCAL_MULTIPLAYER;
            breakLoop = true;
            break;
        }
        
        if(online.getText().getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
            gameState = ONLINE_MULTIPLAYER;
            breakLoop = true;
            break;
        }
        
        if(back.getText().getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
            gameState = START_SCREEN;
            breakLoop = true;
            break;
        }
        
        window.clear();
        for(text_box * tb : textBoxes){
            if(tb->getText().getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
                if(tb->getText().getCharacterSize() < 110){
                    tb->reset_size(110);
                }
            } else {
                if(tb->getText().getCharacterSize() > 100){
                    tb->reset_size(100);
                }
            }
            tb->set_rate(time);
            tb->update();
            window.draw(tb->getText());
        }
        window.display();
    }
    transition_out_mpm(window, textBoxes);
}

#endif /* multiPlayerMenu_hpp */
