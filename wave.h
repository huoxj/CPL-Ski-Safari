//
// Created by 2567499168 on 2023/1/6.
//

#ifndef SKI_SAFARI_WAVE_H
#define SKI_SAFARI_WAVE_H

#endif //SKI_SAFARI_WAVE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

float wave_height(int index,int layer);
float wave_degree(int index,int lenth);
float getvel();
void change_velo(float s);
void wave_init();
void bezier(int s);
void new_wave();
void wave_update();
void wave_show(SDL_Renderer *renderer);
void wave_drawtrack(int left, int right);
void summon_bg_obj();
void summon_tree();