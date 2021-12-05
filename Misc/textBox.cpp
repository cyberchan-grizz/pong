//
//  textBox.cpp
//  theMotherFuckers
//
//  Created by Channing Christian on 12/22/19.
//  Copyright © 2019 Channing Christian. All rights reserved.
//

#include "textBox.hpp"

text_box::text_box(std::string msg){
    font.loadFromFile(resourcePath() + "upheavtt.ttf");
    this->text.setFont(font);
    this->text.setString(msg);
    this->text.setColor(sf::Color::White);
}

void text_box::set_rate(double rate){
    this->rate = rate;
}

void text_box::set_string(std::string string){
    this->text.setString(string);
}

void text_box::set_pos(double x, double y){
    this->text.setPosition(x, y);
}

void text_box::set_size(double size){
    this->text.setCharacterSize(size);
    this->size = size;
}

void text_box::set_movement(sf::Vector2f movement){
    this->movementVector = movement;
}

sf::Vector2f text_box::get_movement(){
    return this->movementVector;
}

sf::Text text_box::getText(){
    return this->text;
}

void text_box::update(){
    if(this->size < this->text.getCharacterSize()){
        this->text.setCharacterSize(this->text.getCharacterSize() - (0.5 * rate));
        if(this->text.getCharacterSize() < this->size){
            this->text.setCharacterSize(this->size);
        }
    } else if(this->size > this->text.getCharacterSize()){
        this->text.setCharacterSize(this->text.getCharacterSize() + (0.5 * rate));
        if(this->text.getCharacterSize() > this->size){
            this->text.setCharacterSize(this->size);
        }
    }
    this->text.setOrigin(this->text.getLocalBounds().width / 2, this->text.getLocalBounds().height /2);
    this->text.move(sf::Vector2f(this->movementVector.x * this->rate, this->movementVector.y * this->rate));
}

void text_box::reset_size(double size){
    this->size = size;
}
