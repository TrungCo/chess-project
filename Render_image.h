#ifndef RENDER_IMAGE_H_INCLUDED
#define RENDER_IMAGE_H_INCLUDED
#include "Start_prog.h"



class Render_image{
public:

    Render_image();

    void Render_image_start(int a, int b, std::string path1, SDL_Renderer* renderer);


    void Load_image(SDL_Renderer* renderer, int w, int h);
//    void render(SDL_Renderer* renderer);

    SDL_Texture* texture_;
    SDL_Rect rect_;


    int x_const;
    int y_const;
    std::string path;




};

#endif // RENDER_IMAGE_H_INCLUDED
