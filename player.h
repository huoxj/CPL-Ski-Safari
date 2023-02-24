//
// Created by 2567499168 on 2023/1/7.
//

#ifndef SKI_SAFARI_PLAYER_H
#define SKI_SAFARI_PLAYER_H

#endif //SKI_SAFARI_PLAYER_H

#include <stdbool.h>

//==============================内部函数=================================
void clac_pos();
void player_jetpack();

//============================外部会调用的函数============================
void player_show(SDL_Renderer *renderer);
void player_input(bool input);
float player_groundheight();
void player_xoffset_trigger(float velo,int frames);
void player_xoffset_update();
void player_yoffset_trigger(float velo);
void player_yoffset_update();
int player_y();
int player_x();
int player_jetpackfuel();
void player_destat();
bool player_upstat(int target);
void player_init();