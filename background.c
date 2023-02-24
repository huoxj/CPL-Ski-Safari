//
// Created by 2567499168 on 2023/1/8.
//

#include <SDL2/SDL.h>
#include <stdio.h>
#include <time.h>

#include "background.h"
#include "resource.h"
#include "camera.h"

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

SDL_Rect rdst_mount;
SDL_Rect rsrc_mount;
int mount_delay;

void background_mount(SDL_Renderer *renderer){
    float curx=rsrc_mount.x,velo=getvel();
    mount_delay++;
    if(mount_delay > velo/4) curx+=velo/4, mount_delay=0;
    if(curx>2560) curx-=2560;
    rsrc_mount.x=curx;
    //循环播放背景山, 960是背景图片的横长像素数
    my_rendercopy(renderer, get_mount(),&rsrc_mount,&rdst_mount);//先画背景山
}


void background_init(){
    mount_delay=0;
    rdst_mount.x=0;rdst_mount.y=100;
    rdst_mount.w=WINDOW_WIDTH;rdst_mount.h=WINDOW_HEIGHT;
    rsrc_mount.x=0;rsrc_mount.y=0;
    rsrc_mount.w=1280;rsrc_mount.h=720;
    //和背景山有关的东西

}