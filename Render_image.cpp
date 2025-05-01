#include "Render_image.h"
Render_image::Render_image(){
}

void Render_image::Render_image_start(int a, int b, std::string path1, SDL_Renderer* renderer){
    texture_=NULL;
    path=path1;
    rect_.h=0;
    rect_.w=0;

    rect_.x=a;
    rect_.y=b;

    x_const=rect_.x;
    y_const=rect_.y;


    SDL_Surface* surface = IMG_Load(path.c_str());
    texture_ = SDL_CreateTextureFromSurface(renderer, surface);
    rect_.w = surface->w;
    rect_.h = surface->h;
    SDL_FreeSurface(surface);
}


void Render_image::Load_image(SDL_Renderer* renderer, int w, int h){
    rect_.w=w;
    rect_.h=h;
    SDL_RenderCopy(renderer, texture_, NULL, &rect_);

}

//void Render_image::render(SDL_Renderer* renderer){
//
//    SDL_RenderCopy(renderer, texture_, NULL, &rect_);
//
//}
