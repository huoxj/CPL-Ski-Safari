//
// Created by 2567499168 on 2023/1/31.
//

#ifndef SKI_SAFARI_FLOWEY_H
#define SKI_SAFARI_FLOWEY_H

#endif //SKI_SAFARI_FLOWEY_H

#include <SDL2/SDL.h>
#include <stdbool.h>

void flowey_init();
void flowey_update();
bool flowey_show(SDL_Renderer *renderer);
float flowey_dist();
void flowey_destory();