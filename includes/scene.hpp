#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include "global.hpp"

class GameObject {
    protected:
        SDL_Renderer* renderer;
        SDL_Texture* texture;

        SDL_Rect dimensions;
        int velocity;

    public:
        GameObject(SDL_Renderer* renderer, std::string path, SDL_Point pos, int velocity);
        virtual void draw();
        virtual void update(int* score);

        SDL_Rect get_dimenssions();
};


class PipeObject : public GameObject {
    SDL_RendererFlip flip;
    SDL_Rect bottom_pipe;

    void calc_pipe_position();

    public:
        PipeObject(SDL_Renderer* renderer, std::string path, SDL_Point pos) 
        : GameObject(renderer, path, pos, PIPE_VELOCITY)
        {
            this->flip = flip;
            calc_pipe_position();
        }
        void update(int* score) override;
        void draw() override;
        SDL_Rect get_bottom_pipe();
};


class PlayerObject : public GameObject {
    SDL_Rect clip_sprite;
    int angle_velocity = 0;
    int frame;

    public:
        PlayerObject(SDL_Renderer* renderer, std::string path, SDL_Point pos, int angle) 
        : GameObject(renderer, path, pos, GRAVITY)
        {
            frame = 0;
            angle_velocity = angle;

            clip_sprite = { 0, 0, dimensions.w = dimensions.w * 1.3, BIRD_HEIGHT_CLIP_SPRITE };
            dimensions.h = BIRD_HEIGHT_CLIP_SPRITE * 1.3;
        }

        void animation();
        void jump();
        void update(int* score) override;
        void draw() override;
};

#endif