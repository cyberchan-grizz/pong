//
//  player.hpp
//  pong
//
//  Created by Channing Christian on 4/30/21.
//  Copyright © 2021 Channing Christian. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

#include "ResourcePath.hpp"

struct player_snapshot{
    std::pair<double, double> position;
    sf::Vector2f movementVector;
};

class player{
private:
    sf::Sprite paddle;
    sf::Texture paddleTexture;
    player_snapshot ps;
    
    sf::Vector2f movementVector;
    double rate;
    
    int score;
    
    std::pair<double, double> windowSize;
    
    enum moveDir{
        MOVE_UP,
        MOVE_DOWN,
        NO_MOVE
    } moveDir;
    
public:
    player(int num, sf::RenderWindow &window);
    void set_rate(double rate);
    void update();
    void move_up();
    void move_down();
    void stop_moving();
    void inc_score();
    void reset_score();
    int get_score();
    sf::Sprite get_sprite();
};

#endif /* player_hpp */
