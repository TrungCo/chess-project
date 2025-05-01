#ifndef CHESS_CONVERT_COMMEND_H_INCLUDED
#define CHESS_CONVERT_COMMEND_H_INCLUDED


#include "Start_prog.h"



std::string covert_commend_in(int x, int y, int x_b, int y_b){
    std::string input_ratio="xxxx";
    input_ratio[1]=char (7-x+49);
    input_ratio[3]=char (7-x_b+49);

    input_ratio[0]=char(y+97);
    input_ratio[2]=char(y_b+97);

    return input_ratio;
}
void covert_commend_out(int &x, int &y, int &x_b, int &y_b, std::string input_ratio){
    y = int( input_ratio[0])-97;
    y_b = int( input_ratio[2])-97;

    x = 7-(int( input_ratio[1])-49);
    x_b = 7-(int( input_ratio[3])-49);
}

#endif // CHESS_CONVERT_COMMEND_H_INCLUDED
