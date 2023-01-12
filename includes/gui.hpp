#ifndef __GUI_HPP__
#define __GUI_HPP__

#include "global.hpp"
#include "game.hpp"

class GUI
{
    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Texture* init_message;
    SDL_Texture* game_over_message;

    SDL_Rect init_message_position;
    SDL_Rect game_over_position;

    std::vector<GameObject*> game_objects;

    PlayerObject* player;

    bool running = false;
    void load_objects_to_animation();
    void load_images_init();

    void start_game_screen();
    void game_over_screen();

    public:
        GUI();

        void update();
        void events(bool* global_running, Game* game);
        void render(GameState state);
        void quit();

        bool is_running();
        void set_running(bool running);

        SDL_Renderer* get_renderer();
};


#endif