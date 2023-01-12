#include "game.hpp"

Game::Game(SDL_Renderer* renderer)
{
    this->renderer = renderer;
    state = GAME_START;
    score = 0;

    load_numbers_sprite();
}

void Game::load_numbers_sprite()
{
    SDL_Surface* temp = IMG_Load(std::string(IMG_NUMBERS).c_str());

    numbers_sprite = SDL_CreateTextureFromSurface(renderer, temp);
    numbers_sprite_dimensions = { WINDOW_WIDTH - IMG_NUMBER_WIDTH, SCORE_TOP_MARGIN, IMG_NUMBER_WIDTH, temp->h };
    SDL_FreeSurface(temp);
}

void Game::load_objects_scene()
{
    game_objects.push_back(new GameObject(renderer, IMG_BG, { 0, 0 }, BG_VELOCITY));
    game_objects.push_back(new GameObject(renderer, IMG_BG, { BG_WIDTH, 0 }, BG_VELOCITY));

    for (int count = 0; count < PIPE_COUNT; count++)
    {
        int pipe_x_position = WINDOW_WIDTH + count * PIPE_SPACE_HORIZONTAL;
        game_objects.push_back( new PipeObject(renderer, IMG_PIPE, { pipe_x_position, 0 }) );
    }

    game_objects.push_back(new GameObject(renderer, IMG_FLOOR, { 0, WINDOW_HEIGHT - FLOOR_HEIGHT / 2 }, FLOOR_VELOCITY));
    game_objects.push_back(new GameObject(renderer, IMG_FLOOR, { FLOOR_WIDTH, WINDOW_HEIGHT - FLOOR_HEIGHT / 2 }, FLOOR_VELOCITY));

    player = new PlayerObject(renderer, IMG_BIRD, { BIRD_POS_X, BIRD_POS_Y }, BIRD_MAX_ANGLE);
    game_objects.push_back(player);
}


void Game::update()
{
    for (GameObject* object : game_objects)
    {
        object->update(&score);

        if (is_collide_pipe(player, object))
            state = GAME_OVER;
    }

    if (is_collide_top_or_floor(player))
        state = GAME_OVER;
}

void Game::events(bool* global_running) 
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                *global_running = false;
                state = GAME_EXIT;
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym)
                    player->jump();
                break;
        }

    }
}

void Game::draw_score()
{
    int temp_score = score;
    SDL_Rect clip;
    int offset_x = 0; // deslocamento quando o placar é maior que 10
    numbers_sprite_dimensions.x = WINDOW_WIDTH - IMG_NUMBER_WIDTH * 2;

    clip = { IMG_NUMBER_WIDTH * 1, 0, IMG_NUMBER_WIDTH, numbers_sprite_dimensions.h };

    do {
        clip.x = temp_score % 10 * IMG_NUMBER_WIDTH;
        temp_score /= 10;
        numbers_sprite_dimensions.x -= IMG_NUMBER_WIDTH;

        SDL_RenderCopy(renderer, numbers_sprite, &clip, &numbers_sprite_dimensions);
    } while (temp_score != 0);
}

void Game::render() 
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    for (GameObject* object : game_objects) 
        object->draw();

    draw_score();

    SDL_RenderPresent(renderer);
}


bool Game::is_running()
{
    return state == GAME_RUNNING;
}

GameState Game::get_game_state()
{
    return state;
}

void Game::set_game_state(GameState state)
{
    this->state = state;
}


void Game::reset()
{
    game_objects.clear();
    load_objects_scene();
    score = 0;
}
