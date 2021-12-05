//
//  bot.cpp
//  pong
//
//  Created by Channing Christian on 5/6/21.
//  Copyright © 2021 Channing Christian. All rights reserved.
//

#include "bot.hpp"

bot::bot(sf::RenderWindow &window) : player(1, window){
    this->windowSize = std::pair<double, double>(window.getSize().x, window.getSize().y);
}

void bot::update(std::pair<double, double> ballPos){
    if(ballPos.first < this->windowSize.first/2){
        if(ballPos.second <= this->get_sprite().getPosition().y){
            this->move_up();
        } else if(ballPos.second >= this->get_sprite().getPosition().y){
            this->move_down();
        } 
    } else {
        this->stop_moving();
    }
    this->player::update();
}

