//
// Created by 2567499168 on 2023/1/24.
//

#ifndef SKI_SAFARI_OBSTACLE_H
#define SKI_SAFARI_OBSTACLE_H

#endif //SKI_SAFARI_OBSTACLE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct {
    //基本信息
    int type;
    SDL_Texture *texture;
    int w,h;

    //位置相关
    float posx,posy;
    float px,py;
    double degree;

    //运动相关
    float speed;

    //碰撞箱
    int radius;

    //动画
    int frame;

}obstacle;

void obstacle_create(int type);
void obstacle_update(int index);
void obstacle_show(SDL_Renderer *renderer);
void obstacle_destory(int index);

void obstacle_test_collision(float x,float y,int player_r);
void obstacle_overlap(int index);

int obstacle_rand();