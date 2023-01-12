#include "collide.hpp"


bool is_collide_top_or_floor(GameObject* object1)
{
    SDL_Rect rect_object1 = object1->get_dimenssions();
    bool colide_top_or_floor = rect_object1.y < 0 || rect_object1.y + rect_object1.h > WINDOW_HEIGHT - (FLOOR_HEIGHT / 2);

    return colide_top_or_floor;
}


bool is_collide_pipe(GameObject* object1, GameObject* object2)
{
    SDL_Rect rect_object1 = object1->get_dimenssions();
    SDL_Rect rect_object2 = object2->get_dimenssions();

    bool colide_pipe = false;

    PipeObject* pipe = dynamic_cast<PipeObject*>(object2);
    if (pipe)
    {
        SDL_Rect rect_pipe_bottom = pipe->get_bottom_pipe();

        bool x_collide = rect_object1.x + rect_object1.w >= rect_object2.x && rect_object1.x < rect_object2.x + rect_object2.w;
        colide_pipe = x_collide && (rect_object1.y < rect_object2.y + rect_object2.h || rect_object1.y + rect_object1.h > rect_pipe_bottom.y);
    }

    return colide_pipe;
}
