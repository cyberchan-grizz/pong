//
//  textBox.hpp
//  theMotherFuckers
//
//  Created by Channing Christian on 12/22/19.
//  Copyright © 2019 Channing Christian. All rights reserved.
//

#ifndef textBox_hpp
#define textBox_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "ResourcePath.hpp"

using namespace std;

class text_box{
private:
    sf::Text text;
    sf::Font font;
    sf::Vector2f movementVector;
    double size;
    double rate;
public:
    text_box(std::string msg);
    void set_rate(double rate);
    void set_string(std::string string);
    void reset_size(double size);
    void set_pos(double x, double y);
    void set_size(double size);
    void update();
    void set_movement(sf::Vector2f movement);
    sf::Vector2f get_movement();
    sf::Text getText();
};

#endif /* textBox_hpp */
