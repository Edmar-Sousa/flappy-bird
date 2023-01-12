#include "scene.hpp"

GameObject::GameObject(SDL_Renderer* renderer, std::string path, SDL_Point pos, int velocity) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    this->renderer = renderer;

    dimensions = { pos.x, pos.y, surface->w, surface->h };
    this->velocity = velocity;

    SDL_FreeSurface(surface);
}

void GameObject::draw()
{
    SDL_RenderCopy(renderer, texture, nullptr, &dimensions);
}

void GameObject::update(int* score)
{
    dimensions.x -= velocity;

    if (dimensions.x < -dimensions.w)
        dimensions.x = WINDOW_WIDTH;
}
SDL_Rect GameObject::get_dimenssions()
{
    return dimensions;
}

// ************ PIPE Object ************
void PipeObject::calc_pipe_position()
{
    int al = 1 + std::rand() % PIPE_TOP_LIMIT;
    dimensions.y = -al;

    bottom_pipe = get_dimenssions();
    bottom_pipe.y = dimensions.y + dimensions.h + PIPE_SPACE_VERTICAL;
}

void PipeObject::update(int* score)
{
    dimensions.x -= velocity;
    bottom_pipe.x -= velocity;

    if (dimensions.x < -dimensions.w)
    {
        dimensions.x = WINDOW_WIDTH;
        calc_pipe_position();
        *score += 1;
    }
}

void PipeObject::draw()
{
    SDL_RenderCopyEx(renderer, texture, nullptr, &dimensions, 0, nullptr, SDL_FLIP_VERTICAL);
    SDL_RenderCopyEx(renderer, texture, nullptr, &bottom_pipe, 0, nullptr, SDL_FLIP_NONE);
}

SDL_Rect PipeObject::get_bottom_pipe()
{
    return bottom_pipe;
}

// ************ Player Object ************

void PlayerObject::animation()
{
    frame = (frame + 1) % BIRD_SPRITE_COUNT;
    clip_sprite.y = BIRD_HEIGHT_CLIP_SPRITE * frame;
}

void PlayerObject::update(int* score)
{
    animation();

    velocity += ACELERATION * (float) DELTA_TIME / 1000;
    dimensions.y += velocity * ((float) DELTA_TIME / 1000);

    angle_velocity = angle_velocity >= BIRD_MAX_ANGLE ? BIRD_MAX_ANGLE : angle_velocity + BIRD_ANGLE_VELOCITY * (float) DELTA_TIME / 1000;
}

void PlayerObject::draw() 
{
    SDL_RenderCopyEx(renderer, texture, &clip_sprite, &dimensions, angle_velocity, nullptr, SDL_FLIP_NONE);
}


void PlayerObject::jump()
{
    angle_velocity = -BIRD_MAX_ANGLE;
    velocity = -JUMP_FORCE;
}
