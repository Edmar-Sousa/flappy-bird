#ifndef __COLLIDE_HPP__
#define __COLLIDE_HPP__

#include "scene.hpp"

bool is_collide_top_or_floor(GameObject* object1);
bool is_collide_pipe(GameObject* object1, GameObject* object2);

#endif