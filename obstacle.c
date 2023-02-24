//
// Created by 2567499168 on 2023/1/24.
//

#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "obstacle.h"
#include "resource.h"
#include "camera.h"
#include "player.h"

#define maxn 15
#define WINDOW_WIDTH 1600

obstacle *list[20];

void obstacle_create(int type){
    int target=1;
    while(list[target]!=NULL) target++;
    obstacle *self= malloc(sizeof(obstacle));
    list[target]=self;
    self->type=type;
    self->texture= get_obstacle(self->type);
    self->w= get_obstacle_w(self->type);
    self->h= get_obstacle_h(self->type);

    self->posx=rand()%WINDOW_WIDTH+WINDOW_WIDTH;
    self->px=self->posx+ self->w/2;

    if(type<=3) self->speed=0;//静态物体记得改
    else self->speed=rand()%50/10.0+2;

    self->radius=self->w/3;
    if(self->type==8) self->radius=self->h/4;
    self->frame=0;
}
void obstacle_update(int index){
    float vel=getvel();
    obstacle *p=list[index];

    p->posx-=vel;p->px-=vel;
    p->posx+=p->speed;p->px+=p->speed;
    //先处理x方向
    p->py= wave_height(p->px,1)+10;
    p->posy=p->py- get_obstacle_h(p->type);
    //处理y方向
    p->degree= wave_degree(p->px, get_obstacle_w(p->type)/2);
    //处理角度

    if(p->type>=5&&p->type<=7){
        p->frame++;
        int dura=10;
        if(p->frame>dura&&p->frame<=2*dura){
            p->type=6;
            p->texture= get_obstacle(p->type);
        }
        if(p->frame>2*dura&&p->frame<=3*dura){
            p->type=7;
            p->texture= get_obstacle(p->type);
        }
        if(p->frame>3*dura&&p->frame<=4*dura){
            p->type=6;
            p->texture= get_obstacle(p->type);
        }
        if(p->frame>4*dura){
            p->frame=0;
            p->type=5;
            p->texture= get_obstacle(p->type);
        }
    }
    //处理动画
}
void obstacle_show(SDL_Renderer *renderer){
    for(int i=1;i<=maxn;i++){
        if(list[i]==NULL) continue;
        if(list[i]->posx<-WINDOW_WIDTH||list[i]->posx>2*WINDOW_WIDTH){
            obstacle_destory(i);
            continue;
        }//把不合法的障碍物除掉
        obstacle *p=list[i];
        obstacle_update(i);
        SDL_FRect rdst={p->posx,p->posy,p->w,p->h};
        SDL_FPoint cent={get_obstacle_w(p->type)/2, get_obstacle_h(p->type)};
        my_rendercopyExF(renderer,list[i]->texture,NULL,&rdst,p->degree,&cent,SDL_FLIP_NONE);
    }
}
void obstacle_destory(int index){
    free(list[index]);
    list[index]=NULL;
}

void obstacle_test_collision(float x,float y,int player_r){
    for(int i=1;i<=maxn;i++){
        obstacle *p=list[i];
        if(p==NULL) continue;
        if(p->type==2) continue;//无须检测碰撞的obstacle
        float centx=p->px;
        float centy=p->py;
        int radius=p->radius;
        float dis=(x-centx)*(x-centx)+(y-centy)*(y-centy);
        if(dis<=(radius+player_r)*(radius+player_r)){//检测到碰撞
            obstacle_overlap(i);
            return;
        }
    }
}
void obstacle_overlap(int index){
    obstacle *p=list[index];
    int type=list[index]->type;
    if(type==1){//创到石头
        p->type=2;//变成碎石头
        p->texture= get_obstacle(p->type);
        player_destat();
    }
    if(type==3){//喷气背包
        bool success=player_upstat(5);
        if(success) obstacle_destory(index);
    }
    if(type==4){//闪⚡电⚡蜗⚡牛
        bool success= player_upstat(7);
        if(success) obstacle_destory(index);
    }
    if(type>=5&&type<=7){//Papyrus
        bool success= player_upstat(8);
        if(success) obstacle_destory(index);
    }
    if(type==8){//ship
        bool success= player_upstat(13);
        if(success) obstacle_destory(index);
    }
}

int obstacle_rand(){
    int tmp=rand()%27+1;
    if(tmp<=15) return 1;//stone-15
    if(tmp>15&&tmp<=19) return 4;//snail-4
    if(tmp>19&&tmp<=23) return 5;//papyrus-4
    if(tmp==24||tmp==26) return 3;//jetpack-2
    if(tmp==25||tmp==27) return 8;//ship-2
    return 0;
}

