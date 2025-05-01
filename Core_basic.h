#ifndef CORE_BASIC_H_INCLUDED
#define CORE_BASIC_H_INCLUDED

#include "Start_prog.h"


class Piece_text{
public:
    Piece_text(char piece_type);
    bool is_blocking_piece(int x, int y, int x_b, int y_b, char board[8][8]);
    bool moving_piece_text_check(int x, int y, int x_b, int y_b, char board[8][8], int nhap_thanh_check[]);
    bool tot_di_chuyen(int x, int y, int x_b, int y_b, char board[8][8]);
    int moving_piece_text(char board[8][8],int x, int y, int x_b, int y_b, bool &turn, int nhap_thanh_check[]);
    bool nhap_thanh(char board[8][8],int x, int y, int x_b, int y_b, int nhap_thanh_check[]);

    char Piece_type;
    int nhap_thanh_checker_viet=10;
    bool nhap_thanh_alert=false;

};


#endif // CORE_BASIC_H_INCLUDED
