//
// Created by 2567499168 on 2023/1/9.
//

//魔改原SDL_RenderCopy函数 实现全局位移 (Camera Scrolling)
//配合SDL_SetRenderScale函数 实现画面缩放

#include "camera.h"

#include <SDL2/SDL.h>
#include "player.h"

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

#define scale_v 0.002f

SDL_Rect r_cam;
SDL_FRect fr_cam;
int cam_x,cam_y;
float scale;//0.6~1

void camera_init(){
    cam_x=0;cam_y=0;
    scale=1;
}

void camera_update(SDL_Renderer *renderer){
    float tar_scale;
    float gh=player_groundheight();
    float v=getvel();
    tar_scale=0.6+(v-10)/5*0.4;
    float scale_=gh/500*0.4+0.6;
    if(scale_>1) scale_=1;
    tar_scale=scale_>tar_scale?scale_:tar_scale;
    if(tar_scale>1) tar_scale=1;

    //以下进行插值,保证镜头丝滑移动
    float delta_scale=tar_scale-scale;
    if(delta_scale>0){
        if(delta_scale<=scale_v) scale+=delta_scale;
        else scale+=scale_v;
    }
    else{
        if(delta_scale>=-scale_v) scale+=delta_scale;
        else scale+=-scale_v;
    }

    cam_x=(1-scale)*player_x()+160;
    cam_y= (1-scale) * player_y()+100;
    SDL_RenderSetScale(renderer,1.0/scale,1.0/scale);
}

void my_rendercopy(SDL_Renderer *renderer,SDL_Texture *texture,SDL_Rect *srcrect,SDL_Rect *dstrect){
    r_cam=*dstrect;
    r_cam.x-=cam_x;
    r_cam.y-=cam_y;
    SDL_RenderCopy(renderer,texture,srcrect,&r_cam);
}

void my_rendercopyF_static(SDL_Renderer *renderer, SDL_Texture *texture, const SDL_Rect *srcrect, const SDL_FRect *dstrect){
    fr_cam=*dstrect;
    fr_cam.w*=scale;
    fr_cam.h*=scale;
    //fr_cam.x=player_x()-250;
    //fr_cam.y=player_y()-200;
    fr_cam.x*=scale;
    fr_cam.y*=scale;

    SDL_RenderCopyF(renderer,texture,srcrect,&fr_cam);
}
//专为ui设计的摄像机坐标系渲染函数

void my_rendercopyExF(SDL_Renderer *renderer,SDL_Texture *texture,const SDL_Rect *srcrect,const SDL_FRect *dstrect,const double angle,const SDL_FPoint *center,const SDL_RendererFlip flip){
    fr_cam=*dstrect;
    fr_cam.x-=cam_x;
    fr_cam.y-=cam_y;
    SDL_RenderCopyExF(renderer,texture,srcrect,&fr_cam,angle,center,flip);
}

void my_renderdrawpoint(SDL_Renderer *renderer,int x,int y){
    x-=cam_x;
    y-=cam_y;
    SDL_RenderDrawPoint(renderer,x,y);
}

float get_scale(){
    return scale;
}