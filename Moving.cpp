 #include "Moving.h"

void piece_check(bool &input_var, SDL_Event event){
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT){
                input_var=true;
            }
    else if(event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT){
                input_var=false;
            }
}

void moving_piece(bool check, int &x, int &y,int mouse_x, int mouse_y,int &old_x,int &old_y, bool correct_move ){

    if(check){
        x=mouse_x-50;
        y=mouse_y-50;
    }
    if (!check && !correct_move){
        x=old_x;
        y=old_y;
    }
    else if(correct_move){
        old_x=x;
        old_y=y;
    }
}

void phong_cap(Render_image chess_mana[8][8], SDL_Renderer* renderer, char board_text[8][8], int x, int y, int x_b, int y_b, char phong_gi){
    Render_image render_temp;
    chess_mana[x][y]=render_temp;
    board_text[x][y]='.';
    switch (phong_gi){
    case 'n':
        board_text[x_b][y_b]='n';
        render_temp.Render_image_start(29+(105*y_b),(105*x_b)+29, "image/piece/2.png",renderer);
        chess_mana[x_b][y_b]=render_temp;
        break;
    case 'N':
        board_text[x_b][y_b]='N';
        render_temp.Render_image_start(29+(105*y_b),(105*x_b)+29, "image/piece/8.png",renderer);
        chess_mana[x_b][y_b]=render_temp;
        break;
    case 'q':
        board_text[x_b][y_b]='q';
        render_temp.Render_image_start(29+(105*y_b),(105*x_b)+29, "image/piece/4.png",renderer);
        chess_mana[x_b][y_b]=render_temp;
        break;
    case 'Q':
        board_text[x_b][y_b]='Q';
        render_temp.Render_image_start(29+(105*y_b),(105*x_b)+29, "image/piece/10.png",renderer);
        chess_mana[x_b][y_b]=render_temp;
        break;
    case 'r':
        board_text[x_b][y_b]='r';
        render_temp.Render_image_start(29+(105*y_b),(105*x_b)+29, "image/piece/1.png",renderer);
        chess_mana[x_b][y_b]=render_temp;
        break;
    case 'R':
        board_text[x_b][y_b]='R';
        render_temp.Render_image_start(29+(105*y_b),(105*x_b)+29, "image/piece/7.png",renderer);
        chess_mana[x_b][y_b]=render_temp;
        break;
    case 'b':
        board_text[x_b][y_b]='b';
        render_temp.Render_image_start(29+(105*y_b),(105*x_b)+29, "image/piece/3.png",renderer);
        chess_mana[x_b][y_b]=render_temp;
        break;
    case 'B':
        board_text[x_b][y_b]='B';
        render_temp.Render_image_start(29+(105*y_b),(105*x_b)+29, "image/piece/9.png",renderer);
        chess_mana[x_b][y_b]=render_temp;
        break;

    }
}
