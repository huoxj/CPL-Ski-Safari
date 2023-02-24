//
// Created by 2567499168 on 2023/1/8.
//

#ifndef SKI_SAFARI_RESOURCE_H
#define SKI_SAFARI_RESOURCE_H

#endif //SKI_SAFARI_RESOURCE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define text SDL_Texture

void resource_load(SDL_Renderer *renderer);
void resource_unload();

text *get_mount();
text *get_tree();
text *get_bgo(int index);
int get_bgo_w(int index);
int get_bgo_h(int index);
text *get_ground();
text *get_frisk(int index);
text *get_obstacle(int index);
int get_obstacle_w(int index);
int get_obstacle_h(int index);
text *get_flowey(int index);

text *get_number();
text *get_menu(int index);
text *get_ingame(int index);
text *get_gameover(int index);
text *get_cg(int index);