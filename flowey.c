//
// Created by 2567499168 on 2023/1/31.
//

#include "flowey.h"
#include "camera.h"
#include "gui.h"
#include "player.h"
#include "resource.h"

#define flowey_w 23
#define flowey_h 33

int flowey_frame;
float dist;
float flowey_velo;//2~20
SDL_Texture *t_flowey_;

void flowey_init(){
    flowey_frame=0;
    dist=0;
    flowey_velo=5;
    t_flowey_= get_flowey(1);
}
void flowey_update(){
    dist+=flowey_velo;

    float cursc=get_score();
    if(cursc-dist>10000) dist=cursc-10000;//flowey太远了 给frisk上点难度

    if(cursc>20000){
        flowey_velo=5+(cursc-20000)/20000;//每20000分flowey速度+1
    }

    flowey_frame++;
    int dura=10;
    if(flowey_frame<dura){
        t_flowey_= get_flowey(1);
    }
    if(flowey_frame>=dura&&flowey_frame<2*dura){
        t_flowey_= get_flowey(2);
    }
    if(flowey_frame>=2*dura&&flowey_frame<3*dura){
        t_flowey_= get_flowey(3);
    }
    if(flowey_frame>=3*dura&&flowey_frame<4*dura){
        t_flowey_= get_flowey(2);
    }
    if(flowey_frame>=4*dura) flowey_frame=0;
}
bool flowey_show(SDL_Renderer *renderer){
    flowey_update();
    float cursc=get_score();

    if(cursc+5-dist<0) return true;//gameover了

    if(cursc-dist<700){//flowey需要渲染了
        float dstx=player_x()-(cursc-dist);
        SDL_FRect dst={dstx, wave_height(dstx,1)-30,flowey_w,flowey_h};
        while(dst.x>0){
            my_rendercopyExF(renderer,t_flowey_,NULL,&dst, wave_degree(dstx,10),NULL,SDL_FLIP_NONE);
            dst.x-=flowey_w+10;
            dst.y=wave_height(dst.x,1)-30;
        }
    }
    return false;
}
float flowey_dist(){
    return get_score()-dist;
}
void flowey_destory(){
    SDL_DestroyTexture(t_flowey_);
}
