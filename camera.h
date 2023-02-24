//
// Created by 2567499168 on 2023/1/9.
//

#ifndef SKI_SAFARI_CAMERA_H
#define SKI_SAFARI_CAMERA_H

#endif //SKI_SAFARI_CAMERA_H

#include <SDL2/SDL.h>
#include "wave.h"

void camera_init();
void camera_update(SDL_Renderer *renderer);
void my_rendercopy(SDL_Renderer *renderer,SDL_Texture *texture,SDL_Rect *srcrect,SDL_Rect *dstrect);
void my_rendercopyF_static(SDL_Renderer *renderer, SDL_Texture *texture, const SDL_Rect *srcrect, const SDL_FRect *dstrect);
void my_rendercopyExF(SDL_Renderer *renderer,
                      SDL_Texture *texture,
                      const SDL_Rect *srcrect,
                      const SDL_FRect *dstrect,
                      const double angle,
                      const SDL_FPoint *center,
                      const SDL_RendererFlip flip);
void my_renderdrawpoint(SDL_Renderer *renderer,int x,int y);
float get_scale();