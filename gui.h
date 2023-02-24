//
// Created by 2567499168 on 2023/1/31.
//

#ifndef SKI_SAFARI_GUI_H
#define SKI_SAFARI_GUI_H

#endif //SKI_SAFARI_GUI_H

#include <SDL2/SDL.h>

typedef struct{
    float x,y;
    float vx,vy;
}soul;

void gui_menu_init();
void gui_ingame_init();
void gui_ingame_update(SDL_Renderer *renderer);
float get_score();
void draw_number(SDL_Renderer *renderer, float x, float y, float h, int figure);

void gui_gameover_init();
void gui_gameover(SDL_Renderer *renderer,int part);
void gui_cg_init();
void gui_cg(SDL_Renderer *renderer,int part);
void record();
void gui_destory();