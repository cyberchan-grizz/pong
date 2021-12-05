//
//  bot.hpp
//  pong
//
//  Created by Channing Christian on 5/6/21.
//  Copyright © 2021 Channing Christian. All rights reserved.
//

#ifndef bot_hpp
#define bot_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

#include "player.hpp"
#include "ball.hpp"

class bot : public player {
private:
    std::pair<double, double> windowSize;
public:
    bot(sf::RenderWindow &window);
    void update(std::pair<double, double> ballPos);
};

#endif /* bot_hpp */
