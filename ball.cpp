//
//  ball.cpp
//  pong
//
//  Created by Channing Christian on 4/30/21.
//  Copyright © 2021 Channing Christian. All rights reserved.
//

#include "ball.hpp"


ball::ball(sf::RenderWindow * window, player * p1, player * p2){
    this->ballTexture.loadFromFile(resourcePath() + "ball.png");
    this->ballSprite.setTexture(this->ballTexture);
    this->ballSprite.setPosition(window->getSize().x/2, window->getSize().y/2);
    this->ballSprite.setOrigin(100, 100);
    this->ballSprite.setScale(0.2, 0.2);
    
    this->movementVector = sf::Vector2f(0, 0);
    
    this->bs.position = std::pair<double, double>(this->ballSprite.getPosition().x, this->ballSprite.getPosition().y);

    this->bs.movementVector = this->movementVector;
    this->windowHeight = window->getSize().y;
    this->windowLength = window->getSize().x;
    
    this->p1 = p1;
    this->p2 = p2;
}

void ball::set_rate(double rate){
    this->rate = rate;
}

void ball::update(){
    if(this->ballSprite.getGlobalBounds().top < 0 || this->ballSprite.getGlobalBounds().top + this->ballSprite.getGlobalBounds().height > this->windowHeight){
        this->movementVector = sf::Vector2f(this->movementVector.x, this->movementVector.y * -1);
        if(this->ballSprite.getGlobalBounds().top < 0){
            this->ballSprite.setPosition(this->ballSprite.getPosition().x, this->ballSprite.getGlobalBounds().height/2);
        } else if (this->ballSprite.getGlobalBounds().top + this->ballSprite.getGlobalBounds().height > this->windowHeight){
            this->ballSprite.setPosition(this->ballSprite.getPosition().x, (this->windowHeight - this->ballSprite.getGlobalBounds().height/2));
        }
    }
    if(this->ballSprite.getGlobalBounds().intersects(p1->get_sprite().getGlobalBounds())){
        double dist = this->ballSprite.getPosition().y - this->p1->get_sprite().getPosition().y;
        
        this->ballSprite.setPosition(p1->get_sprite().getPosition().x - (p1->get_sprite().getGlobalBounds().width/2) - (this->ballSprite.getGlobalBounds().width/2), this->ballSprite.getPosition().y);
        
        double theta = dist/2;
        theta = (theta * M_PI)/180;
        int posNeg = 1;
        if(theta < 0){
            theta = -theta;
            posNeg = -1;
        }
        
        double xMovement = -((sqrt(2) * cos(theta)));
        double yMovement = (sqrt(2) * sin(theta)) * posNeg;
        
        if(dist != 0){
            this->movementVector = sf::Vector2f(xMovement, yMovement);
        } else {
            this->movementVector = sf::Vector2f(-(sqrt(2)), 0);
        }
    }
    if(this->ballSprite.getGlobalBounds().intersects(p2->get_sprite().getGlobalBounds())){
        double dist = this->ballSprite.getPosition().y - this->p2->get_sprite().getPosition().y;
        
        this->ballSprite.setPosition(p2->get_sprite().getPosition().x + (p2->get_sprite().getGlobalBounds().width/2) + (this->ballSprite.getGlobalBounds().width/2), this->ballSprite.getPosition().y);
        
        double theta = dist/2;
        theta = (theta * M_PI)/180;
        int posNeg = 1;
        if(theta < 0){
            theta = -theta;
            posNeg = -1;
        }
        
        double xMovement = (sqrt(2) * cos(theta));
        double yMovement = (sqrt(2) * sin(theta)) * posNeg;
        
        
        if(dist != 0){
            this->movementVector = sf::Vector2f(xMovement, yMovement);
        } else {
            this->movementVector = sf::Vector2f((sqrt(2)), 0);
        }
    }
                              
    this->ballSprite.move(sf::Vector2f(this->movementVector.x * rate, this->movementVector.y * rate));
    this->bs.movementVector = this->movementVector;
    this->bs.position = std::pair<double, double>(this->get_sprite().getPosition().x, this->get_sprite().getPosition().y);
}

void ball::set_movement(sf::Vector2f movementVector){
    this->movementVector = movementVector;
}

ball_snapshot ball::get_ball_snapshot(){
    return this->get_ball_snapshot();
}

sf::Sprite ball::get_sprite(){
    return this->ballSprite;
}
