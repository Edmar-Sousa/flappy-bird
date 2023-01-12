#include "gui.hpp"

int main(int argc, char** argv)
{
    std::srand(std::time(0));

    bool running = true;

    GUI gui;
    Game game(gui.get_renderer()); 


    while (running) 
    {
        while (gui.is_running())
        {
            gui.events(&running, &game);
            gui.update();
            gui.render(game.get_game_state());
            SDL_Delay(DELTA_TIME);
        }

        while (game.is_running())
        {
            game.events(&running);
            game.update();
            game.render();

            SDL_Delay(DELTA_TIME);
        }

        gui.set_running(true);
    }

    
    gui.quit();
    return 0;
} 
