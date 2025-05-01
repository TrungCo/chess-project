#ifndef MOVING_H_INCLUDED
#define MOVING_H_INCLUDED

#include "Start_prog.h"

#include "Render_image.h"


void piece_check(bool &input_var, SDL_Event event);

void moving_piece(bool check, int &x, int &y,int mouse_x, int mouse_y,int &old_x,int &old_y, bool correct_move );

void phong_cap(Render_image chess_mana[8][8], SDL_Renderer* renderer, char board_text[8][8], int x, int y, int x_b, int y_b, char phong_gi);

#endif // MOVING_H_INCLUDED
