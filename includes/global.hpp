#ifndef __GLOBAL_HPP__
#define __GLOBAL_HPP__

#include <iostream>
#include <stdlib.h>   // exit function
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

#define __DIR                   std::string(SDL_GetBasePath())

#define WINDOW_WIDTH            333
#define WINDOW_HEIGHT           597


#define GRAVITY                 100
#define DELTA_TIME              70
#define JUMP_FORCE              100
#define ACELERATION             100

#define IMG_NUMBERS             __DIR + std::string("sprites/numbers.png")
#define IMG_NUMBER_WIDTH        24
#define SCORE_TOP_MARGIN        20


#define IMG_FLOOR               __DIR + std::string("sprites/base.png")
#define FLOOR_VELOCITY          2
#define FLOOR_WIDTH             336
#define FLOOR_HEIGHT            112

#define IMG_BG                  __DIR + std::string("sprites/background.png")
#define BG_VELOCITY             1
#define BG_WIDTH                336

#define IMG_PIPE                __DIR + std::string("sprites/pipe.png")
#define PIPE_WIDTH              52
#define PIPE_VELOCITY           2
#define PIPE_COUNT              3
#define PIPE_SPACE_VERTICAL     110
#define PIPE_SPACE_HORIZONTAL   (WINDOW_WIDTH + PIPE_WIDTH) / PIPE_COUNT
#define PIPE_TOP_LIMIT          100

#define IMG_BIRD                __DIR + std::string("sprites/bird.png")
#define BIRD_HEIGHT_CLIP_SPRITE 24
#define BIRD_SPRITE_COUNT       3
#define BIRD_POS_X              50
#define BIRD_POS_Y              WINDOW_HEIGHT / 2
#define BIRD_ANGLE_VELOCITY     30
#define BIRD_MAX_ANGLE          50


#define GUI_GAME_OVER_IMG       __DIR + std::string("sprites/gameover.png")
#define GUI_INITIAL_IMG         __DIR + std::string("sprites/message.png")

#define GUI_GAME_OVER_MARGIN    130
#define GUI_INITIAL_IMG_MARGIN  140


enum GameState {
    GAME_OVER, GAME_START, GAME_RUNNING, GAME_EXIT
};

#endif