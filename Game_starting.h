#ifndef GAME_STARTING_H_INCLUDED
#define GAME_STARTING_H_INCLUDED

#include "Start_prog.h"
#include "Render_image.h"


void new_game(Render_image chess_mana[8][8], SDL_Renderer* renderer, char board_text[8][8], Render_image null_render_image,std::string &board_data_now,bool &check_turn,int nhap_thanh_check[4]){
    check_turn=true;
    board_data_now="position startpos moves ";
    char board_text_new[8][8]={
    {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
    {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
    };




    memcpy(board_text, board_text_new, sizeof(board_text_new));
    int nhap_thanh_check_cop[4]={0,0,0,0};
    memcpy(nhap_thanh_check, nhap_thanh_check_cop, sizeof(nhap_thanh_check_cop));


    for (int i=0; i<8; i++){
            for (int j=0; j<8; j++){

                chess_mana[i][j]=null_render_image;
            }
        }


    chess_mana[0][0].Render_image_start(29+(105*0),(105*0)+29, "image/piece/1.png",renderer);
    chess_mana[0][1].Render_image_start(29+(105*1),(105*0)+29, "image/piece/2.png",renderer);
    chess_mana[0][2].Render_image_start(29+(105*2),(105*0)+29, "image/piece/3.png",renderer);
    chess_mana[0][3].Render_image_start(29+(105*3),(105*0)+29, "image/piece/4.png",renderer);
    chess_mana[0][4].Render_image_start(29+(105*4),(105*0)+29, "image/piece/5.png",renderer);
    chess_mana[0][5].Render_image_start(29+(105*5),(105*0)+29, "image/piece/3.png",renderer);
    chess_mana[0][6].Render_image_start(29+(105*6),(105*0)+29, "image/piece/2.png",renderer);
    chess_mana[0][7].Render_image_start(29+(105*7),(105*0)+29, "image/piece/1.png",renderer);
    for (int i=0; i <8; i++){
        chess_mana[1][i].Render_image_start(29+(105*i),(105*1)+29, "image/piece/6.png",renderer);
    }


    chess_mana[7][0].Render_image_start(29+(105*0),(105*7)+29, "image/piece/7.png",renderer);
    chess_mana[7][1].Render_image_start(29+(105*1),(105*7)+29, "image/piece/8.png",renderer);
    chess_mana[7][2].Render_image_start(29+(105*2),(105*7)+29, "image/piece/9.png",renderer);
    chess_mana[7][3].Render_image_start(29+(105*3),(105*7)+29, "image/piece/10.png",renderer);
    chess_mana[7][4].Render_image_start(29+(105*4),(105*7)+29, "image/piece/11.png",renderer);
    chess_mana[7][5].Render_image_start(29+(105*5),(105*7)+29, "image/piece/9.png",renderer);
    chess_mana[7][6].Render_image_start(29+(105*6),(105*7)+29, "image/piece/8.png",renderer);
    chess_mana[7][7].Render_image_start(29+(105*7),(105*7)+29, "image/piece/7.png",renderer);

    for (int i=0; i <8; i++){
        chess_mana[6][i].Render_image_start(29+(105*i),(105*6)+29, "image/piece/12.png",renderer);
    }

}



#endif // GAME_STARTING_H_INCLUDED
