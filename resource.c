//
// Created by 2567499168 on 2023/1/8.
//

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "resource.h"

#define text SDL_Texture

//背景
text *t_ground;
text *t_mount;
text *t_bgo[15];
//玩家
text *t_frisk[25];
//障碍物
text *t_obstacle[25];
//flowey
text *t_flowey[5];

//number
text *t_number;
//menu
text *t_menu_logo;
text *t_menu_save;
//ingame
text *t_HI;
text *t_warning;
text *t_fuel_e;
text *t_fuel_f;
//gameover
text *t_gameover;
text *t_info_1;
text *t_info_2;
text *t_soul_1;
text *t_soul_2;
text *t_soul_3;
text *t_black;
//cg
text *t_background;
text *t_bubble;
text *t_frisk_;
text *t_sans;



void resource_load(SDL_Renderer *renderer){
    //背景
    t_ground= IMG_LoadTexture(renderer,"Resources/Ski_Scene/ground.png");
    t_mount= IMG_LoadTexture(renderer,"Resources/Ski_Scene/mount.png");
    t_bgo[0]= IMG_LoadTexture(renderer,"Resources/Background_object/tree.png");
    t_bgo[1]= IMG_LoadTexture(renderer,"Resources/Background_object/house_1.png");
    t_bgo[2]= IMG_LoadTexture(renderer,"Resources/Background_object/house_2.png");
    t_bgo[3]= IMG_LoadTexture(renderer,"Resources/Background_object/house_2.png");
    t_bgo[4]= IMG_LoadTexture(renderer,"Resources/Background_object/house_4.png");
    t_bgo[5]= IMG_LoadTexture(renderer,"Resources/Background_object/house_5.png");
    t_bgo[6]= IMG_LoadTexture(renderer,"Resources/Background_object/house_6.png");
    t_bgo[7]= IMG_LoadTexture(renderer,"Resources/Background_object/house_7.png");
    t_bgo[8]= IMG_LoadTexture(renderer,"Resources/Background_object/snowman_1.png");
    t_bgo[9]= IMG_LoadTexture(renderer,"Resources/Background_object/snowman_2.png");
    t_bgo[10]= IMG_LoadTexture(renderer,"Resources/Background_object/microwave.png");
    t_bgo[11]= IMG_LoadTexture(renderer,"Resources/Background_object/nicecreamguy.png");
    //玩家
    t_frisk[0]= IMG_LoadTexture(renderer, "Resources/Player/frisk_fallen_1.png");
    t_frisk[1]= IMG_LoadTexture(renderer, "Resources/Player/frisk_fallen_2.png");
    t_frisk[2]= IMG_LoadTexture(renderer, "Resources/Player/frisk_fallen_3.png");
    t_frisk[3]= IMG_LoadTexture(renderer, "Resources/Player/frisk_fallen_2.png");
    t_frisk[4]= IMG_LoadTexture(renderer, "Resources/Player/frisk_sking.png");
    t_frisk[5]= IMG_LoadTexture(renderer, "Resources/Player/frisk_jetpack_1.png");
    t_frisk[6]= IMG_LoadTexture(renderer, "Resources/Player/frisk_jetpack_2.png");
    t_frisk[7]= IMG_LoadTexture(renderer, "Resources/Player/frisk_snail.png");
    t_frisk[8]= IMG_LoadTexture(renderer, "Resources/Player/frisk_pap_sprint_1.png");
    t_frisk[9]= IMG_LoadTexture(renderer, "Resources/Player/frisk_pap_sprint_2.png");
    t_frisk[10]= IMG_LoadTexture(renderer, "Resources/Player/frisk_pap_sprint_3.png");
    t_frisk[11]= IMG_LoadTexture(renderer,"Resources/Player/frisk_pap_dive.png");
    t_frisk[12]= IMG_LoadTexture(renderer,"Resources/Player/frisk_pap_snail.png");
    t_frisk[13]= IMG_LoadTexture(renderer,"Resources/Player/frisk_ship.png");
    t_frisk[14]= IMG_LoadTexture(renderer,"Resources/Player/frisk_ship_snail.png");
    t_frisk[15]= IMG_LoadTexture(renderer,"Resources/Player/frisk_ship_snail_snail.png");
    t_frisk[16]= IMG_LoadTexture(renderer,"Resources/Player/frisk_ship_pap.png");
    t_frisk[17]= IMG_LoadTexture(renderer,"Resources/Player/frisk_ship_pap_snail.png");
    //障碍物
    t_obstacle[1]= IMG_LoadTexture(renderer,"Resources/Obstacle/stone_1.png");
    t_obstacle[2]= IMG_LoadTexture(renderer,"Resources/Obstacle/stone_2.png");
    t_obstacle[3]= IMG_LoadTexture(renderer,"Resources/Obstacle/jetpack.png");
    t_obstacle[4]= IMG_LoadTexture(renderer,"Resources/Obstacle/snail.png");
    t_obstacle[5]= IMG_LoadTexture(renderer,"Resources/Obstacle/papyrus_1.png");
    t_obstacle[6]= IMG_LoadTexture(renderer,"Resources/Obstacle/papyrus_2.png");
    t_obstacle[7]= IMG_LoadTexture(renderer,"Resources/Obstacle/papyrus_3.png");
    t_obstacle[8]= IMG_LoadTexture(renderer,"Resources/Obstacle/ship.png");
    //flowey
    t_flowey[1]= IMG_LoadTexture(renderer,"Resources/Flowey/flowey_1.png");
    t_flowey[2]= IMG_LoadTexture(renderer,"Resources/Flowey/flowey_2.png");
    t_flowey[3]= IMG_LoadTexture(renderer,"Resources/Flowey/flowey_3.png");

    //number
    t_number= IMG_LoadTexture(renderer,"Resources/Menu/number.png");
    //menu
    t_menu_logo= IMG_LoadTexture(renderer,"Resources/Menu/menu_logo.png");
    t_menu_save= IMG_LoadTexture(renderer,"Resources/Menu/menu_save.png");
    //ingame
    t_HI= IMG_LoadTexture(renderer,"Resources/Ingame/HI.png");
    t_warning= IMG_LoadTexture(renderer,"Resources/Ingame/warning.png");
    t_fuel_e= IMG_LoadTexture(renderer,"Resources/Ingame/fuel_e.png");
    t_fuel_f= IMG_LoadTexture(renderer,"Resources/Ingame/fuel_f.png");
    //gameover
    t_gameover= IMG_LoadTexture(renderer,"Resources/Gameover/gameover.png");
    t_info_1= IMG_LoadTexture(renderer,"Resources/Gameover/info_1.png");
    t_info_2= IMG_LoadTexture(renderer,"Resources/Gameover/info_2.png");
    t_soul_1= IMG_LoadTexture(renderer,"Resources/Gameover/soul_1.png");
    t_soul_2= IMG_LoadTexture(renderer,"Resources/Gameover/soul_2.png");
    t_soul_3= IMG_LoadTexture(renderer,"Resources/Gameover/soul_3.png");
    t_black= IMG_LoadTexture(renderer,"Resources/Gameover/black.png");
    //cg
    t_background= IMG_LoadTexture(renderer,"Resources/CG/background.png");
    t_bubble= IMG_LoadTexture(renderer,"Resources/CG/bubble.png");
    t_frisk_= IMG_LoadTexture(renderer,"Resources/CG/frisk.png");
    t_sans= IMG_LoadTexture(renderer,"Resources/CG/sans.png");
}

void resource_unload(){
    //背景
    SDL_DestroyTexture(t_ground);
    SDL_DestroyTexture(t_mount);
    for(int i=0;i<15;i++) SDL_DestroyTexture(t_bgo[i]);
    for(int i=0;i<25;i++) SDL_DestroyTexture(t_frisk[i]);
    for(int i=0;i<25;i++) SDL_DestroyTexture(t_obstacle[i]);
    for(int i=0;i<5;i++) SDL_DestroyTexture(t_flowey[i]);
    SDL_DestroyTexture(t_number);
    SDL_DestroyTexture(t_menu_logo);
    SDL_DestroyTexture(t_menu_save);
    SDL_DestroyTexture(t_HI);
    SDL_DestroyTexture(t_warning);
    SDL_DestroyTexture(t_fuel_e);
    SDL_DestroyTexture(t_fuel_f);
    SDL_DestroyTexture(t_gameover);
    SDL_DestroyTexture(t_info_1);
    SDL_DestroyTexture(t_info_2);
    SDL_DestroyTexture(t_soul_1);
    SDL_DestroyTexture(t_soul_2);
    SDL_DestroyTexture(t_soul_3);
    SDL_DestroyTexture(t_black);
    SDL_DestroyTexture(t_background);
    SDL_DestroyTexture(t_bubble);
    SDL_DestroyTexture(t_frisk_);
    SDL_DestroyTexture(t_sans);
}

//===========================================以下为调用texture函数============================================

text *get_mount(){
    return t_mount;
}
//背景山

text *get_tree(){
    return t_bgo[0];
}

text *get_bgo(int index){//house: 1~7    snowman:8~9    microwave:10     nicecream:11
    if(index<=11) return t_bgo[index];
    return NULL;
}
int get_bgo_w(int index){
    if(index==0){return 60;}
    if(index==1){return 111;}
    if(index==2){return 212;}
    if(index==3){return 212;}
    if(index==4){return 214;}
    if(index==5){return 128;}
    if(index==6){return 57;}
    if(index==7){return 59;}
    if(index==8){return 19;}
    if(index==9){return 66;}
    if(index==10){return 75;}
    if(index==11){return 74;}
    return 0;
}
int get_bgo_h(int index){
    if(index==0){return 60;}
    if(index==1){return 112;}
    if(index==2){return 203;}
    if(index==3){return 203;}
    if(index==4){return 168;}
    if(index==5){return 118;}
    if(index==6){return 70;}
    if(index==7){return 79;}
    if(index==8){return 30;}
    if(index==9){return 37;}
    if(index==10){return 34;}
    if(index==11){return 60;}
    return 0;
}

text *get_ground(){
    return t_ground;
}
//地形

text *get_frisk(int index){
    /*
     *      Fall-0 1 2 3      Idle-4
     *      Jetpack-5 6
     *      Snail-7
     *      Pap_Sprint-8 9 10    Pap_Halt-
     *      Ship-  Ship_Snail-  Ship_Snail_Snail- Ship_Pap_Snail-  Ship_Pap-
    */
    if(index<=17) return t_frisk[index];//记得改
    return NULL;
}
//玩家

text *get_obstacle(int index){
    /*
    * type:
    *      1.stone_1    2.stone_2   3.jetpack
    *      4.snail
     *     5 6 7.papyrus
     *     8.ship
    */
    if(index<=15) return t_obstacle[index];//记得改
    return NULL;
}
int get_obstacle_w(int index){
    if(index==1||index==2) return 40;
    if(index==3) return 26;
    if(index==4) return 28;
    if(index>=5&&index<=7) return 34;
    if(index==8) return 90;
    return 0;
}
int get_obstacle_h(int index){
    if(index==1||index==2) return 36;
    if(index==3) return 28;
    if(index==4) return 16;
    if(index>=5&&index<=7) return 45;
    if(index==8) return 45;
    return 0;
}
//障碍物和物品
text *get_flowey(int index){//23*33
    return t_flowey[index];
}

//numbers
text *get_number(){
    return t_number;
}

//menu
text *get_menu(int index){
    if(index==1) return t_menu_logo;
    return t_menu_save;
}//401*129

//ingame
text *get_ingame(int index){
    if(index==1) return t_HI;
    if(index==2) return t_warning;
    if(index==3) return t_fuel_e;
    if(index==4) return t_fuel_f;
}

//gameover
text *get_gameover(int index){
    if(index==0) return t_black;
    if(index==1) return t_gameover;
    if(index==2) return t_info_1;
    if(index==3) return t_info_2;
    if(index==4) return t_soul_1;
    if(index==5) return t_soul_2;
    if(index==6) return t_soul_3;
}

//cg
text *get_cg(int index){
    if(index==0) return t_background;
    if(index==1) return t_bubble;
    if(index==2) return t_frisk_;
    if(index==3) return t_sans;
}