#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "global.hpp"
#include "scene.hpp"
#include "collide.hpp"


class Game {
    SDL_Renderer* renderer;
    SDL_Texture* numbers_sprite;

    std::vector<GameObject*> game_objects;
    PlayerObject* player;

    GameState state;
    SDL_Rect numbers_sprite_dimensions;
    int score;

    void load_objects_scene();
    void load_numbers_sprite();
    void draw_score();

    public:
        Game(SDL_Renderer* renderer);
        void update();
        void events(bool* global_running);
        void render();

        bool is_running();

        GameState get_game_state();
        void set_game_state(GameState state);

        void reset();
};

#endif