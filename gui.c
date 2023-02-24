//
// Created by 2567499168 on 2023/1/31.
//

#include <stdio.h>
#include <windows.h>

#include "gui.h"
#include "wave.h"
#include "resource.h"
#include "camera.h"
#include "player.h"
#include "flowey.h"

#define num_h 18
#define num_w 16
#define acc 0.03f

SDL_Texture *num;
SDL_FRect dst_HI;
SDL_FRect dst_warning;
SDL_Rect src_fuel;
SDL_FRect dst_fuel;

float score;
int hiscore;
FILE *fp;

void gui_menu_init(){
    score=0;
    fp= fopen("Resources/hiscore.cfg", "rb");
    fread(&hiscore, sizeof(int), 1, fp);

    num=get_number();

    dst_HI.x=1260;dst_HI.y=20;dst_HI.w=33;dst_HI.h=20;//HI.dst
    dst_warning.x=20;dst_warning.y=20;dst_warning.w=76;dst_warning.h=62;//warning.dst
    dst_fuel.x=1400;dst_fuel.y=100;dst_fuel.w=30;dst_fuel.h=300;//fuel.dst
    src_fuel.x=0;src_fuel.y=0;src_fuel.w=14;src_fuel.h=137;
    fclose(fp);
}//记得fclose
void gui_ingame_init(){
    score=0;
}
bool iswarned;
void gui_ingame_update(SDL_Renderer *renderer){
    score+=getvel();
    if((int)score>hiscore) hiscore=(int)score;
    //更新分数


    my_rendercopyF_static(renderer, get_ingame(1),NULL,&dst_HI);

    if(player_jetpackfuel()){//喷气背包燃料显示
        my_rendercopyF_static(renderer, get_ingame(3),NULL,&dst_fuel);
        SDL_FRect dst_fuel_=dst_fuel;
        float percent=1-player_jetpackfuel()/300.0;
        dst_fuel_.y=dst_fuel.y+dst_fuel.h*percent;
        dst_fuel_.h=dst_fuel.y+dst_fuel.h-dst_fuel_.y;
        src_fuel.y=(int)(src_fuel.h*percent);
        my_rendercopyF_static(renderer, get_ingame(4),&src_fuel,&dst_fuel_);
    }
    if(flowey_dist()<1200){//flowey警告
        if(iswarned==false){
            mciSendString("play Resources/Audio/flowey.mp3",NULL,0,NULL);
            iswarned=true;
        }
        my_rendercopyF_static(renderer, get_ingame(2),NULL,&dst_warning);
    }
    else iswarned=false;
}
float get_score(){
    return score;
}
void draw_number(SDL_Renderer *renderer, float x, float y, float h, int figure){
    if(figure==114514) figure=hiscore/100;//传入的figure是114514就表示要绘制最高分
    if(figure==1919810) figure=(int)score/100;//传入的figure是1919810就表示要绘制分
    figure%=100000;//防止爆炸
    float w=num_w*h/num_h;
    int div=10000;
    SDL_FRect dst={x,y,w,h};
    SDL_Rect src={0,0,num_w,num_h};
    for(int i=0;i<5;i++){
        int cur=figure/div;
        figure%=div;div/=10;
        src.x=cur*num_w;
        my_rendercopyF_static(renderer,num,&src,&dst);
        dst.x+=w;
    }
}

soul frag[6];
int frame_;
int timer;
void gui_gameover_init(){
    for(int i=0;i<6;i++){
        frag[i].x=player_x()-250;
        frag[i].y=player_y()-200;
        frag[i].vx=(rand()%50-25)/10.0;
        frag[i].vy=(rand()%40-25)/10.0;
    }
    frame_=0;
    timer=-500;
}
void gui_gameover(SDL_Renderer *renderer,int part){

    if(part==1){//soul_1
        int x=player_x()-250,y=player_y()-200;
        SDL_FRect dst={x,y,20,16};
        my_rendercopyF_static(renderer, get_gameover(4),NULL,&dst);
    }
    if(part==2){//soul_2
        int x=player_x()-250,y=player_y()-200;
        SDL_FRect dst={x,y,20,16};
        my_rendercopyF_static(renderer, get_gameover(5),NULL,&dst);
    }
    if(part==3){//frag
        for(int i=0;i<6;i++){
            frag[i].x+=frag[i].vx;
            frag[i].y+=frag[i].vy;
            frag[i].vy+=acc;
            SDL_Rect src={frame_/10*8,0,8,8};
            SDL_FRect dst={frag[i].x,frag[i].y,8,8};
            my_rendercopyF_static(renderer, get_gameover(6),&src,&dst);
        }
        frame_++;
        if(frame_>40) frame_=0;
    }
    if(part==4){//gameover
        if(timer<0) timer+=3;
        SDL_FRect dst={0,timer,1440,900};
        my_rendercopyF_static(renderer, get_gameover(1),NULL,&dst);
    }
    if(part==5){//info_1
        SDL_FRect dst={0,0,1440,900};
        my_rendercopyF_static(renderer, get_gameover(2),NULL,&dst);
    }
    if(part==6){//info_2
        SDL_FRect dst={0,0,1440,900};
        my_rendercopyF_static(renderer, get_gameover(3),NULL,&dst);
    }
}
void gui_cg_init(){
    frame_=0;
    timer=0;
}
void gui_cg(SDL_Renderer *renderer,int part){
    if(part==1){//firsk
        int x=200,y=400;
        SDL_Rect dst={x,y,60,60};
        SDL_RenderCopy(renderer, get_cg(2),NULL,&dst);
    }
    if(part==2){//firsk_2
        int x=200,y=400;
        if(frame_>80&&frame_<=120) x = (frame_ - 80) * 20 + 200;
        if(frame_>120) x=1000;
        if(frame_>140&&frame_<=170) y = (frame_ - 140) * 20 + 400;
        if(frame_>170) y=1000;
        SDL_Rect dst={x,y+20,80,80};
        SDL_RenderCopy(renderer, get_cg(2),NULL,&dst);
    }
    if(part==3){//sans_1
        SDL_Rect src={0,0,80,80};
        SDL_Rect dst={600,400,100,100};
        SDL_RenderCopy(renderer, get_cg(3),&src,&dst);
    }
    if(part==4){//sans_2
        SDL_Rect src={0,0,80,80};
        SDL_Rect dst={600,400,100,100};
        frame_++;
        if(frame_>0&&frame_<=25) src.x=0;
        if(frame_>25&&frame_<=60) src.x=80;
        if(frame_>60&&frame_<=70) src.x=160;
        if(frame_>70&&frame_<=80) src.x=240;
        if(frame_>80&&frame_<=120) src.x=320;
        if(frame_>120&&frame_<=130) src.x=400;
        if(frame_>130&&frame_<=140) src.x=480;
        if(frame_>140) src.x=560;
        SDL_RenderCopy(renderer, get_cg(3),&src,&dst);
    }
    if(part==5){//background
        SDL_Rect dst={0,0,1440,900};
        SDL_RenderCopy(renderer, get_cg(0),NULL,&dst);
    }
    if(part==6){//bubble
        SDL_Rect dst={220,30,1000,240};
        SDL_RenderCopy(renderer, get_cg(1),NULL,&dst);
    }
}

void record(){
    if(hiscore<(int)score) return;
    fp= fopen("Resources/hiscore.cfg", "wb");
    fwrite(&hiscore, sizeof(int), 1, fp);
    fclose(fp);
}

void gui_destory(){
    SDL_DestroyTexture(num);
}