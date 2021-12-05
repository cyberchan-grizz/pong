//
//  ball.hpp
//  pong
//
//  Created by Channing Christian on 4/30/21.
//  Copyright © 2021 Channing Christian. All rights reserved.
//

#ifndef ball_hpp
#define ball_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

#include "ResourcePath.hpp"
#include "player.hpp"

struct ball_snapshot{
    std::pair<double, double> position;
    sf::Vector2f movementVector;
};

class ball{
private:
    sf::Sprite ballSprite;
    sf::Texture ballTexture;
    ball_snapshot bs;
    
    sf::Vector2f movementVector;
    double rate;
    
    double windowHeight;
    double windowLength;
    
    player * p1;
    player * p2;
    
public:
    ball(sf::RenderWindow * window, player * p1, player * p2);
    void set_rate(double rate);
    void update();
    void set_movement(sf::Vector2f movementVector);
    ball_snapshot get_ball_snapshot();
    sf::Sprite get_sprite();
};



#endif /* ball_hpp */
