#include "gui.hpp"


GUI::GUI() 
{
     if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Game::Init(): Error init SDL. " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    if (!window)
    {
        std::cout << "Game::Init(): Error init window. " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    if (!renderer)
    {
        std::cout << "Game::Init(): Error init Renderer. " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    running = true;
    load_objects_to_animation();
    load_images_init();
}

void GUI::load_images_init()
{
    SDL_Surface* temp = IMG_Load(std::string(GUI_INITIAL_IMG).c_str());
    init_message = SDL_CreateTextureFromSurface(renderer, temp);
    init_message_position = { WINDOW_WIDTH / 2 - temp->w / 2, GUI_INITIAL_IMG_MARGIN, temp->w, temp->h };

    temp = IMG_Load(std::string(GUI_GAME_OVER_IMG).c_str());
    game_over_message = SDL_CreateTextureFromSurface(renderer, temp);
    game_over_position = { WINDOW_WIDTH / 2 - temp->w / 2, GUI_GAME_OVER_MARGIN, temp->w, temp->h };

    SDL_FreeSurface(temp);
}

void GUI::load_objects_to_animation()
{
    game_objects.push_back(new GameObject(renderer, IMG_BG, { 0, 0 }, BG_VELOCITY));
    game_objects.push_back(new GameObject(renderer, IMG_BG, { BG_WIDTH, 0 }, BG_VELOCITY));

    game_objects.push_back(new GameObject(renderer, IMG_FLOOR, { 0, WINDOW_HEIGHT - FLOOR_HEIGHT / 2 }, FLOOR_VELOCITY));
    game_objects.push_back(new GameObject(renderer, IMG_FLOOR, { FLOOR_WIDTH, WINDOW_HEIGHT - FLOOR_HEIGHT / 2 }, FLOOR_VELOCITY));

    player = new PlayerObject(renderer, IMG_BIRD, { BIRD_POS_X, BIRD_POS_Y }, 0);
}


void GUI::update()
{
    player->animation();

    for (GameObject* object : game_objects)
        object->update(nullptr);
    
}

void GUI::events(bool* global_running, Game* game)
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                *global_running = false;
                running = false;
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym)
                {
                    if (game->get_game_state() == GAME_START)
                    {
                        running = false;
                        game->reset();
                        game->set_game_state(GAME_RUNNING);
                    }

                    else // game_over -> game_start
                        game->set_game_state(GAME_START);
                }
                break;

            default:
                break;
        }
    }
}


void GUI::start_game_screen()
{
    player->draw();
    SDL_RenderCopy(renderer, init_message, nullptr, &init_message_position);
}

void GUI::game_over_screen()
{
    SDL_RenderCopy(renderer, game_over_message, nullptr, &game_over_position);
}

void GUI::render(GameState state) 
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    for (GameObject* object : game_objects) 
        object->draw();
    
    if (state == GAME_START)
        start_game_screen();
    
    else if (state == GAME_OVER) // game_over
        game_over_screen();

    SDL_RenderPresent(renderer);
}

void GUI::quit()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

bool GUI::is_running()
{
    return running;
}

void GUI::set_running(bool running)
{
    this->running = running;
}

SDL_Renderer* GUI::get_renderer()
{
    return renderer;
}

