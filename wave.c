//
// Created by 2567499168 on 2023/1/6.
//

#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

#include "wave.h"
#include "resource.h"
#include "camera.h"
#include "obstacle.h"

#define wave_h 900
#define WINDOW_WIDTH 1600
#define ground_w 200

float velocity=5;
float velo_list[5]={0,10,20,30};

float wave_y[3250];
float key_y[5]={400,400,400,400,300};
int key_x[5]={0,800,1600,2400,3200};
float head;

bool has_track[3250];//是否有划过的轨迹
int has_bg_object[3250];//save type(%100) and y offset(/100%100) and side (/10000%10) and angle (/100000) of background objects
//house: 1~7    snowman:8~9    microwave:10     nicecream:11
int has_tree[3250];//save existence(%10) and side(/10%10) and degree(/100%1000) and y offset(/100000) of tree

SDL_Rect rdst_ground;
SDL_Rect rsrc_ground;

float y_offset,y_offset_vel;

float wave_height(int index,int layer){//layer指2.5d图层, 最前0 雪地1 最后2
    if(layer==0) return wave_y[index+(int)head]-y_offset+180;
    if(layer==1) return wave_y[index+(int)head]-y_offset+140;
    if(layer==2) return wave_y[index+(int)head]-y_offset+20;
    return 0;
}

float wave_degree(int index,int lenth){//返回角度 下坡角为正值
    if(index>2*WINDOW_WIDTH) return 0;
    if(index+lenth>2*WINDOW_WIDTH) lenth=2*WINDOW_WIDTH-index-1;
    double k= (wave_height(index+lenth-1,0)- wave_height(index,0))*1.0/lenth;
    return 57.29578*atan(k);//弧度制转角度制
}

float getvel(){
    return velocity;
}

void change_velo(float s){
    velocity+=s;
    if(velocity<0) velocity=0;
}

void wave_init(){
    head=0;
    y_offset=0;y_offset_vel=0;
    velocity=10;
    key_y[0]=300;key_y[1]=300;key_y[2]=300;key_y[3]=300;key_y[4]=300;
    key_x[0]=0;key_x[1]=800;key_x[2]=1600;key_x[3]=2400;key_x[4]=3200;
    for (int i = 0; i < 1600; ++i) {
        wave_y[i]=300;
    }
    //初始平地高度为y=400
    memset(has_track,0,sizeof(has_track));
    memset(has_tree,0,sizeof(has_tree));
    memset(has_bg_object,0, sizeof(has_bg_object));
    bezier(0);
    bezier(2);

    rdst_ground.x=0;rdst_ground.y=0;rdst_ground.w=1;rdst_ground.h=800;
    rsrc_ground.x=0;rsrc_ground.y=0;rsrc_ground.w=1;rsrc_ground.h=400;
}

void bezier(int s){//贝塞尔曲线, 我滴超人!
    float dy1=key_y[s+1]-key_y[s],dy2=key_y[s+2]-key_y[s+1];
    for(int t=0;t<WINDOW_WIDTH;t++){
        double scale=t*1.0/WINDOW_WIDTH;
        float y1=key_y[s]+dy1*scale,y2=key_y[s+1]+dy2*scale;
        wave_y[WINDOW_WIDTH+t]=y1+scale*(y2-y1);
    }
}

void new_wave(){

    for(int i=1;i<3;i++) key_y[i]=key_y[i+2]-y_offset;
    key_y[3]=2*key_y[2]-key_y[1];
    key_y[4]=key_y[3]+rand()%750-50;
    //生成新关键点
    y_offset_vel=(key_y[2]-key_y[0])*velocity/WINDOW_WIDTH;
    //更新y方向速度
    for(int t=0;t<WINDOW_WIDTH;t++){
        wave_y[t]=wave_y[t+WINDOW_WIDTH]-y_offset;

        has_track[t]=has_track[t+WINDOW_WIDTH];
        has_track[t+WINDOW_WIDTH]=false;

        has_bg_object[t]=has_bg_object[t+WINDOW_WIDTH];
        has_bg_object[t+WINDOW_WIDTH]=false;

        has_tree[t]=has_tree[t+WINDOW_WIDTH];
        has_tree[t+WINDOW_WIDTH]=false;
    }
    //update array information
    bezier(2);
    //输出贝塞尔点集

    summon_bg_obj();
    summon_tree();
}

void wave_update(){
    head+=velocity;
    y_offset_vel=(key_y[2]-key_y[0])*velocity/WINDOW_WIDTH;
    y_offset+=y_offset_vel;
    if(head>=WINDOW_WIDTH){
        head=0;
        new_wave();
        y_offset=0;
    }
}

void wave_show(SDL_Renderer *renderer){
    float wave_w=1;
    for(int x=0;x<WINDOW_WIDTH;x++){
        rdst_ground.x=x;rdst_ground.y=wave_y[x + (int)head] - y_offset;
        rsrc_ground.x=(x+(int)head)%800;
        my_rendercopy(renderer,get_ground(),& rsrc_ground,& rdst_ground);
        //画地面
        if(has_track[x+(int)head]){
            SDL_SetRenderDrawColor(renderer,88,93,93,255);
            float temp_height=wave_height(x,1);
            my_renderdrawpoint(renderer,x,temp_height-1);
            my_renderdrawpoint(renderer,x,temp_height);
            my_renderdrawpoint(renderer,x,temp_height-4);
            my_renderdrawpoint(renderer,x,temp_height-3);

        }
        //画轨迹
    }
    for(int x=0;x<WINDOW_WIDTH;x++){
        if(has_bg_object[x+(int)head]){
            int type=has_bg_object[x+(int)head]%100;
            int layer=has_bg_object[x+(int)head]/10000%10;
            float degree=has_bg_object[x+(int)head]/100000;
            float temp_height;
            if(type<=7&&type){//adjust layer of house
                temp_height= wave_height(x,2)- get_bgo_h(type)+30;
            }
            else{
                temp_height= wave_height(x,layer)+(has_bg_object[x+(int)head]/100)%100;
            }
            SDL_FRect fr_dst={x,temp_height,get_bgo_w(type),get_bgo_h(type)};
            SDL_FPoint center={0,0};
            my_rendercopyExF(renderer,get_bgo(type),NULL,&fr_dst, degree,&center,SDL_FLIP_NONE);
        }
    }
    //画背景物
    for(int x=0;x<WINDOW_WIDTH;x++){
        if(has_tree[x+(int)head]){
            int layer=0;
            int degree=has_tree[x+(int)head]/100%1000;
            if(has_tree[x+(int)head]/10%10==1) layer=2;
            int y_offset_=has_tree[x+(int)head]/100000;
            float temp_height= wave_height(x,layer)+y_offset_;
            SDL_FRect fr_dst={x,temp_height,get_bgo_w(0),get_bgo_h(0)};
            SDL_FPoint center={0,0};
            my_rendercopyExF(renderer, get_bgo(0),NULL,&fr_dst,degree,&center,SDL_FLIP_NONE);
        }
    }
    //画树
}

void wave_drawtrack(int left, int right){
    for(int i=left; i <= right; i++) has_track[i + (int)head]=true;
}

void summon_bg_obj(){//summon new background object
    int bgocount=rand()%4+1;
    for(int cur_pos=WINDOW_WIDTH;cur_pos<=2*WINDOW_WIDTH-10;){
        int type=rand()%11+1;
        int y_offset_=rand()%20;y_offset_*=100;
        int layer=rand()%2;
        int degree= wave_degree(cur_pos, get_bgo_w(type))+360;
        degree*=100000;
        layer+=(layer==1);
        if(type<=7) layer=2;
        layer*=10000;
        has_bg_object[cur_pos]=layer+type+y_offset_+degree;
        cur_pos+=WINDOW_WIDTH/bgocount+rand()%400-200;
    }
}

void summon_tree(){
    int treecount=rand()%15+5;
    for(int cur_pos=WINDOW_WIDTH;cur_pos<=2*WINDOW_WIDTH-10;){
        int side=rand()%2;
        int degree= wave_degree(cur_pos, 30)+360;
        int y_offset=rand()%20;
        has_tree[cur_pos]=y_offset*100000+degree*100+side*10+1;
        cur_pos+=WINDOW_WIDTH/treecount+rand()%100-50;
    }
}