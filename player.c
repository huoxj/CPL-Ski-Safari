//
// Created by 2567499168 on 2023/1/7.
//

#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <windows.h>

#include "player.h"
#include "wave.h"
#include "resource.h"
#include "camera.h"
#include "obstacle.h"

#define gravity 0.12
#define rotate_omega 0.8f

#define x_max 550
#define x_min 350

float vert_vel;//仅处理和地形相关的竖直速度
int frisk_w=30;
int frisk_h=30;

//运动相关
float pos_x;
float pos_y;
float p_x;
float p_y;//碰撞检测点 底端居中
double degree;
int air_rotate_delay;//空中重力翻滚延迟
int fallen_timer;//摔倒动画timer

//状态相关
bool inair;
bool ispressed;
int status;
int frame;
int godtime;
int fuel;

void clac_godtime(){
    if(godtime==0) return;
    godtime--;
}

void clac_anime(){
    if(status<8||status>10) return;
    int dura=10;
    frame++;
    if(frame>dura&&frame<=2*dura){
        status=9;
    }
    if(frame>2*dura&&frame<=3*dura){
        status=10;
    }
    if(frame>3*dura&&frame<=4*dura){
        status=9;
    }
    if(frame>4*dura){
        status=8;
        frame=0;
    }
}

void clac_pos(){

    float gh=player_groundheight();
    if(degree>360) degree-=360;
    if(degree<-360) degree+=360;
    if(gh<6){
        //以下处理角度带来的摔倒和减速
        int delta_angle=abs(degree- wave_degree(p_x,25));
        if(delta_angle>360) delta_angle-=360;
        if(delta_angle>60&&delta_angle<300) {//该摔倒了
            player_destat();
            fallen_timer=0;
        }
        if(delta_angle>30&&delta_angle<270&&getvel()>5){
            change_velo(-2);//减速
        }
        //以下更新贴地角度
        air_rotate_delay=0;
        degree= wave_degree(p_x,25);

        //以下处理雪地上滑行的速度
        if(degree>30&&getvel()<15&&status>=4){//坡角大于30度并且速度小于15才加速
            change_velo(degree/1500);
        }
        if(degree<15&&getvel()>10&&status>=4){//坡角小于15度并且速度大于10才减速
            change_velo((degree-20)/200);
        }
        if(getvel()<6&&status>=4) change_velo(0.05);
    }//在地上就算地面切线角度
    else{
        if(ispressed&&degree<95&&gh>40) degree-=rotate_omega*3;
        if(air_rotate_delay<60) air_rotate_delay++;
        else {
            if (degree < 89) degree += rotate_omega;
        }
        //change_velo(0.01);

    }//不在就顺时针旋转 但注意不能转到90度以后
    //--------------以上处理旋转--------------------
    if(status<4){
        fallen_timer++;
        if(fallen_timer>120){//恢复状态
            change_velo(0.5);
            status=4;
        }
        else{
            status=fallen_timer/10%4;
        }
        return;
    }
    //--------------以上处理摔倒--------------------

    //printf("%f\n",getvel());
    if(gh>6){//在空中
        vert_vel+=gravity;
        inair=true;
    }
    else{
        if(gh<0){
            p_y+=gh;
            pos_y+=gh;
        }
        vert_vel=0;
        inair=false;
        if(p_x>x_min){//不用player_offset_trigger, 直接改
            p_x-=0.8;
            pos_x-=0.8;
        }
    }
    if(ispressed&&!inair){//跳跃

        player_xoffset_trigger(1,30);//跳跃之后给玩家个横向速度
        player_yoffset_trigger(6);
        inair=true;
    }
    p_y+=vert_vel;
    pos_y+=vert_vel;
    if(pos_y<100){//防止飞出窗口了
        p_y-=pos_y-100;
        pos_y=100;
        vert_vel=0;
    }
    //-----------以上处理y方向上的位移---------------
    player_xoffset_update();
    player_yoffset_update();
    //-----------以上处理x方向上的偏移---------------

}

int xoffset_timer;
float xoffset_velo;
void player_xoffset_update(){
    if(xoffset_velo<=0) return;
    if(xoffset_velo>0&&p_x>x_max) return;
    if(xoffset_velo<0&&p_x<x_min) return;
    if(xoffset_timer>0){
        p_x+=xoffset_velo;
        pos_x+=xoffset_velo;
        xoffset_timer--;
    }
}

float yoffset_velo;//处理和跳跃相关的竖直速度
void player_yoffset_update(){
    if(yoffset_velo<=0) return;
    p_y-=yoffset_velo;
    pos_y-=yoffset_velo;
    yoffset_velo-=gravity;
}

bool jet_music;

void player_jetpack(){
    //printf("%lf\n",degree);
    if(status!=5&&status!=6) return;
    if(ispressed){
        if(jet_music==false){
            PlaySound(TEXT("Resources/Audio/jet.wav"),NULL,SND_FILENAME|SND_ASYNC);
            jet_music=true;
        }
        status=6;
        vert_vel-=0.3;
        fuel--;
        if(getvel()<15) change_velo(0.1);
        if(degree<-45) degree=-45;
        if(fuel<=0) player_destat();
    }
    else{
        status=5;
        if(jet_music==true) PlaySound(NULL,NULL,SND_FILENAME|SND_ASYNC);
        jet_music=false;
    }
}

void player_resize(int w,int h){
    frisk_w=w;frisk_h=h;
    pos_x=p_x-w/2;
    pos_y=p_y-h;
}

//============================外部会调用的函数============================
void player_show(SDL_Renderer *renderer){
    clac_pos();
    clac_anime();
    clac_godtime();
    player_jetpack();
    obstacle_test_collision(pos_x+frisk_w/2,pos_y+frisk_h/2,frisk_w);
    SDL_FRect dstr={pos_x,pos_y,frisk_w,frisk_h};
    SDL_FPoint rotp={p_x,p_y};
    my_rendercopyExF(renderer,get_frisk(status),NULL,&dstr,degree,NULL,SDL_FLIP_NONE);
    if(player_groundheight()<5||!inair) wave_drawtrack(pos_x-getvel(),pos_x);
}

void player_input(bool input){
    ispressed=input;
}

void player_xoffset_trigger(float velo,int frames){
    xoffset_timer=frames;
    xoffset_velo=velo;
}

void player_yoffset_trigger(float velo){
    yoffset_velo=velo;
}


float player_groundheight(){
    return -(p_y- wave_height(p_x,1));
}

int player_y(){
    return p_y;
}

int player_x(){
    return p_x;
}

int player_jetpackfuel(){
    return status==5||status==6?fuel:0;
}

void player_destat(){
    if(godtime) return;
    PlaySound(TEXT("Resources/Audio/destat.wav"),NULL,SND_FILENAME|SND_ASYNC);
    if(status==4){//idle->fall
        status=0;
        change_velo(-99999);
        fallen_timer=0;
        float gotoground= player_groundheight();
        p_y+=gotoground;
        pos_y+=gotoground;
    }
    else
    if(status==5||status==6){//jetpack->idle
        status=4;
    }
    else
    if(status==7){//snail->idle
        player_resize(30,30);
        status=4;
    }
    else
    if(status>=8&&status<=10){//pap_sprint->pap_dive
        player_resize(38,34);
        status=11;
    }
    else
    if(status==11){//pap_dive->idle
        player_resize(30,30);
        status=4;
    }
    else
    if(status==12){//pap_snail->pap_dive
        status=11;
    }
    else
    if(status==13){//ship->idle
        player_resize(30,30);
        status=4;
    }
    else
    if(status==14){//ship_snail->ship
        status=13;
    }
    else
    if(status==15){//ship_snail_snail->ship_snail
        status=14;
    }
    else
    if(status==16){//ship_pap->ship
        status=13;
    }
    else
    if(status==17){//ship_pap_snail->ship_pap
        status=16;
    }
    godtime=30;
}

#define upsound PlaySound(TEXT("Resources/Audio/upstat.wav"),NULL,SND_FILENAME|SND_ASYNC);
bool player_upstat(int target){
    if(target==5&&status==4){//idle->jetpack
        upsound;
        fuel=300;
        status=5;
        godtime=30;return true;
    }
    if(target==7&&status==4){//idle->snail
        upsound;
        player_resize(30,38);
        change_velo(2);
        status=7;
        godtime=30;return true;
    }
    if(target==8&&status==4){//idle->pap_sprint
        upsound;
        player_resize(38,45);
        frame=0;
        change_velo(2);
        status=8;
        godtime=30;return true;
    }
    if(target==8&&status==7){//snail->pap_sprint
        upsound;
        player_resize(38,45);
        frame=0;
        change_velo(2);
        status=8;
        godtime=30;return true;
    }
    if(target==7&&status==11){//pap_dive->pap_snail
        upsound;
        player_resize(38,34);
        change_velo(2);
        status=12;
        godtime=30;return true;
    }
    if(target==13&&status==4){//idle->ship
        upsound;
        player_resize(90,45);
        change_velo(2);
        status=13;
        godtime=30;return true;
    }
    if(target==7&&status==13){//ship->ship_snail
        upsound;
        status=14;
        godtime=30;return true;
    }
    if(target==7&&status==14){//ship_snail->ship_snail_snail
        upsound;
        status=15;
        godtime=30;return true;
    }
    if(target==8&&status==14){//ship_snail->ship_pap_snail
        upsound;
        status=17;
        godtime=30;return true;
    }
    if(target==8&&status==13){//ship->ship_pap
        upsound;
        status=16;
        godtime=30;return true;
    }
    if(target==7&&status==16){//ship_pap->ship_pap_snail
        upsound;
        status=17;
        godtime=30;return true;
    }
    if(target==13&&status==7){//snail->ship_snail
        upsound;
        player_resize(90,45);
        change_velo(2);
        status=14;
        godtime=30;return true;
    }
    if(target==13&&status>=8&&status<=10){//pap_sprint->ship_pap
        upsound;
        player_resize(90,45);
        change_velo(2);
        status=16;
        godtime=30;return true;
    }
    if(target==13&&status==11){//pap_dive->ship_pap
        upsound;
        player_resize(90,45);
        change_velo(2);
        status=16;
        godtime=30;return true;
    }
    if(target==13&&status==12){//pap_snail->ship_pap_snail
        upsound;
        player_resize(90,45);
        change_velo(2);
        status=17;
        godtime=30;return true;
    }
    return false;
}

void player_init(){

    vert_vel=0;
    frisk_w=30;
    frisk_h=30;

    pos_x=400;pos_y=0;//更新玩家最初位置
    p_x=pos_x+frisk_w/2;
    p_y=pos_y+frisk_h;
    degree=0;
    air_rotate_delay=0;

    inair=false;

    status=4;
    godtime=0;

    xoffset_timer=0;
}
