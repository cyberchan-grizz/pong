//
//  player.cpp
//  pong
//
//  Created by Channing Christian on 4/30/21.
//  Copyright © 2021 Channing Christian. All rights reserved.
//

#include "player.hpp"

player::player(int num, sf::RenderWindow &window){
    this->paddleTexture.loadFromFile(resourcePath() + "paddle.png");
    this->paddle.setTexture(paddleTexture);
    this->paddle.setOrigin(this->paddleTexture.getSize().x/2, this->paddleTexture.getSize().y/2);
    this->paddle.setScale(8, 8);
    if(num == 0){ // if the user is player 1
        this->paddle.setPosition(window.getSize().x - 30, window.getSize().y/2);
        this->paddle.setColor(sf::Color(0, 0, 255));
    } else if(num == 1){ // if the user is player 2
        this->paddle.setPosition(30, window.getSize().y/2);
        this->paddle.setColor(sf::Color(255, 0, 0));
    }
    
    windowSize.first = window.getSize().x;
    windowSize.second = window.getSize().y;
    
    this->movementVector = sf::Vector2f(0, 0);
    
    this->ps.position = std::pair<double, double>(this->paddle.getPosition().x, this->paddle.getPosition().y);
    this->ps.movementVector = this->movementVector;
    this->score = 0;
    
    this->moveDir = NO_MOVE;
}

void player::set_rate(double rate){
    this->rate = rate;
}

void player::update(){
    if(this->paddle.getGlobalBounds().top < 0 || this->paddle.getGlobalBounds().top + this->paddle.getGlobalBounds().height > windowSize.second){
        this->moveDir = NO_MOVE;
        if(this->paddle.getGlobalBounds().top <= 0){
            this->paddle.setPosition(this->paddle.getPosition().x, this->paddle.getGlobalBounds().height/2);
        }
        if(this->paddle.getGlobalBounds().top + this->paddle.getGlobalBounds().height >= windowSize.second){
            this->paddle.setPosition(this->paddle.getPosition().x, this->windowSize.second - this->paddle.getGlobalBounds().height/2);
        }
    }
    
    switch(moveDir){
        case MOVE_UP:
            this->movementVector = sf::Vector2f(0, -0.8 * this->rate);
            break;
        case MOVE_DOWN:
            this->movementVector = sf::Vector2f(0, 0.8 * this->rate);
            break;
        case NO_MOVE:
            this->movementVector = sf::Vector2f(0, 0);
            break;
    }
    
    this->paddle.move(this->movementVector);
}

void player::move_up(){
    this->moveDir = MOVE_UP;
}

void player::move_down(){
    this->moveDir = MOVE_DOWN;
}

void player::stop_moving(){
    this->moveDir = NO_MOVE;
}

void player::inc_score(){
    this->score = this->score + 1;
}

void player::reset_score(){
    this->score = 0;
}

int player::get_score(){
    return this->score;
}

sf::Sprite player::get_sprite(){
    return this->paddle;
}
