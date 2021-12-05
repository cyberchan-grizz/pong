//
//  game.hpp
//  pong
//
//  Created by Channing Christian on 5/3/21.
//  Copyright © 2021 Channing Christian. All rights reserved.
//

#ifndef game_hpp
#define game_hpp

#include <stdio.h>

enum game_state{
    PLAYING,
    MULTIPLAYER_MENU,
    START_SCREEN,
    SINGLE_PLAYER,
    ONE_COMP_MULTI_PLAYER,
    LOCAL_MULTIPLAYER,
    ONLINE_MULTIPLAYER,
    CLOSE_WINDOW
};

#endif /* game_hpp */
