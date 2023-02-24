#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <windows.h>
#include <mmsystem.h>

#include "wave.h"
#include "resource.h"
#include "background.h"
#include "player.h"
#include "camera.h"
#include "obstacle.h"
#include "flowey.h"
#include "gui.h"

#pragma comment(lib, "winmm.lib")
#undef main

#define WINDOW_WIDTH 1440
#define WINDOW_HEIGHT 900

SDL_Window *window;
SDL_Renderer *renderer;

bool pressed;
bool click;

int game_status;//0:menu 1:CG 2:gameplay 3:gameover

void init_cg();
void init_menu();
void init_ingame();

int input();

void framerate(int begin_tick);

void loop_menu();
void loop_cg();
void loop_gameplay();
void loop_gameover();

void destory_everything();

int main(){//你是一个一个一个main啊啊啊啊啊啊啊啊啊
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("SKINGTALE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT,
                              SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    game_status=0;
    init_menu();//menu
    loop_menu();

    init_cg();//cg
    loop_cg();

    while(1){
        init_ingame();//ingame
        loop_gameplay();

        loop_gameover();//gameover
    }

    destory_everything();
    return 0;
}

void loop_cg(){
    int timer=-450;
    SDL_Rect r_black={310,90,700,100};
    mciSendString("play Resources/Audio/wind.mp3",NULL,0,NULL);
    while(game_status==1) {//cg
        int begin_tick = SDL_GetTicks();
        SDL_RenderClear(renderer);
        SDL_FRect r;
        if(timer==-330) PlaySound(TEXT("Resources/Audio/bell.wav"),NULL,SND_FILENAME|SND_ASYNC);

        if(timer<=90){
            gui_cg(renderer,5);
            gui_cg(renderer,3);
            gui_cg(renderer,2);
        }
        if(timer>90&&timer<=350){
            gui_cg(renderer,5);
            gui_cg(renderer,3);
            gui_cg(renderer,2);
            gui_cg(renderer,6);
            SDL_RenderCopy(renderer, get_gameover(0),NULL,&r_black);
            if(timer==91) PlaySound(TEXT("Resources/Audio/sans_du.wav"),NULL,SND_FILENAME|SND_ASYNC);
            if((timer-90)%10==0&&timer<=200){
                if(timer!=200) PlaySound(TEXT("Resources/Audio/sans_du.wav"),NULL,SND_FILENAME|SND_ASYNC);
                r_black.x+=60;
                r_black.w-=60;
            }
        }
        if(timer>350){
            if(timer==420||timer==480) PlaySound(TEXT("Resources/Audio/sans_move.wav"),NULL,SND_FILENAME|SND_ASYNC);
            gui_cg(renderer,5);
            gui_cg(renderer,4);
            gui_cg(renderer,2);
        }

        if(timer>600||click){
            mciSendString("close Resources/Audio/wind.mp3",NULL,0,NULL);
            game_status=2;
            return;
        }

        SDL_SetRenderDrawColor(renderer,0, 0, 0, 255);
        SDL_RenderPresent(renderer);

        click=false;
        input();
        timer++;
        framerate(begin_tick);
    }
}

void loop_menu(){
    int timer=0;
    int click_count=0;
    bool music=false;

    SDL_Delay(1000);
    PlaySound(TEXT("Resources/Audio/logo.wav"),NULL,SND_FILENAME|SND_ASYNC);
    while(game_status==0) {
        timer++;
        int begin_tick = SDL_GetTicks();
        SDL_RenderClear(renderer);

        if(click==true&&timer>60) click_count++;
        if(click_count==1){
            SDL_RenderCopy(renderer, get_menu(2),NULL,NULL);
            draw_number(renderer,902,290,41,114514);
            if(!music) {
                music=true;
                PlaySound(TEXT("Resources/Audio/menu.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
            }
        }
        if(click_count==0){
            SDL_RenderCopy(renderer, get_menu(1),NULL,NULL);
        }
        if(click_count==2){
            game_status=1;
            PlaySound(TEXT("Resources/Audio/menu_click.wav"),NULL,SND_FILENAME|SND_ASYNC);
        }

        SDL_SetRenderDrawColor(renderer,0, 0, 0, 255);
        SDL_RenderPresent(renderer);

        click=false;
        input();

        framerate(begin_tick);
    }
}

void loop_gameplay() {
    int nxtobs=rand()%100;
    mciSendString("play Resources/Audio/ingame.mp3 repeat",NULL,0,NULL);
    while (game_status==2) {//Game Running
        int begin_tick = SDL_GetTicks();//获取当前帧开始tick
        SDL_RenderClear(renderer);

        camera_update(renderer);
        //更新相机位置

        background_mount(renderer);
        //更新背景

        wave_show(renderer);
        wave_update();
        //更新并渲染脚底下地形

        float cur_score=get_score();
        if(cur_score>=nxtobs){
            obstacle_create(obstacle_rand());
            nxtobs=cur_score+rand()%600+600;
        }
        obstacle_show(renderer);
        //渲染障碍物

        player_input(pressed);
        player_show(renderer);
        //更新并渲染玩家

        bool fail=flowey_show(renderer);
        //小花花

        gui_ingame_update(renderer);
        draw_number(renderer,1300,20,20,114514);
        draw_number(renderer,1150,20,20,1919810);
        //UI
        SDL_SetRenderDrawColor(renderer,0, 0, 0, 255);
        SDL_RenderPresent(renderer);

        if(fail){//判断gameover
            mciSendString("close Resources/Audio/ingame.mp3",NULL,0,NULL);
            game_status=3;
            break;
        }

        input();

        framerate(begin_tick);//同步每帧时间
    }

}

void loop_gameover(){
    record();
    int timer=0;
    SDL_FRect r_black={310,550,1500,500};
    while (game_status==3){
        int begin_tick = SDL_GetTicks();
        SDL_RenderClear(renderer);

        if(timer<80) gui_gameover(renderer,1);//soul_1
        if(timer==80) PlaySound(TEXT("Resources/Audio/soul_apart.wav"),NULL,SND_FILENAME|SND_ASYNC);
        if(timer>=80&&timer<160) gui_gameover(renderer,2);//soul_2
        if(timer==160){
            PlaySound(TEXT("Resources/Audio/soul_break.wav"),NULL,SND_FILENAME|SND_ASYNC);
            gui_gameover_init();
        }
        if(timer>160&&timer<500) gui_gameover(renderer,3);//soul_3
        if(timer==250) mciSendString("play Resources/Audio/gameover.mp3 repeat",NULL,0,NULL);
        if(timer>250) gui_gameover(renderer,4);//gameover
        if(timer>470&&timer<645) {//info_1
            gui_gameover(renderer, 5);
            my_rendercopyF_static(renderer, get_gameover(0),NULL,&r_black);
            if((timer-470)%20==0){
                PlaySound(TEXT("Resources/Audio/gameover_du.wav"),NULL,SND_FILENAME|SND_ASYNC);
                r_black.x+=77;
            }
        }
        if(timer==645){
            r_black.x=233;
            r_black.y=650;
        }
        if(timer>645) {//info_2
            gui_gameover(renderer, 6);
            my_rendercopyF_static(renderer, get_gameover(0),NULL,&r_black);

            if((timer-645)%30==0){

                if(timer<=825){
                    PlaySound(TEXT("Resources/Audio/gameover_du.wav"),NULL,SND_FILENAME|SND_ASYNC);
                    r_black.x += 77;
                }
                if(timer>825&&timer<=915){
                    PlaySound(TEXT("Resources/Audio/gameover_du.wav"),NULL,SND_FILENAME|SND_ASYNC);
                    r_black.x+=50;
                }
                if(timer>945) r_black.x=1500;
            }
        }
        if(timer>250&&pressed){
            mciSendString("close Resources/Audio/gameover.mp3",NULL,0,NULL);
            game_status=2;
            return;
        }

        SDL_SetRenderDrawColor(renderer,0, 0, 0, 255);
        SDL_RenderPresent(renderer);

        click=false;
        input();
        timer++;
        framerate(begin_tick);
    }

}

void init_cg(){
    gui_cg_init();
}

void init_menu(){
    srand(time(NULL));
    pressed=false;
    resource_load(renderer);
    camera_init();
    gui_menu_init();
}

void init_ingame(){
    pressed=false;
    wave_init();
    background_init();
    player_init();
    flowey_init();
    gui_ingame_init();
    camera_init();
    for(int i=1;i<=20;i++) obstacle_destory(i);
}

int input() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        SDL_KeyCode INPUT = event.key.keysym.sym;
        switch (event.type) {
            case SDL_KEYDOWN:
                if(INPUT== SDLK_SPACE){
                    click=true;
                    pressed=true;
                }
                break;
            case SDL_KEYUP:
                if(INPUT== SDLK_SPACE){
                    pressed=false;
                }
                break;
            case SDL_QUIT:
                destory_everything();
                exit(0);
                return 0;
                break;
            default:
                break;
        }
    }
    return 0;
}

void framerate(int begin_tick) {
    int end_tick = SDL_GetTicks();
    int frame_update_duration=end_tick-begin_tick;
    int delay_time = 1000 / 60 - frame_update_duration;
    if (delay_time < 0) delay_time = 0;
    SDL_Delay(delay_time);
}

void destory_everything() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    resource_unload();
    gui_destory();
    flowey_destory();
    for(int i=0;i<20;i++) obstacle_destory(i);
}