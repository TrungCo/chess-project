#include "Core_basic.h"

Piece_text::Piece_text(char a){
    Piece_type=a;
};


bool Piece_text::is_blocking_piece(int x, int y, int x_b, int y_b, char board[8][8]){
    if (board[x_b][y_b]!='.'){
        if (isupper(board[x_b][y_b])==isupper(board[x][y])){
            return false;
        }
    }

    if (Piece_type=='n'|| Piece_type=='N'){
        return true;
    }

    int dx=x_b-x;
    int dy=y_b-y;
    if (dx>0){
        dx=1;
    }
    else if(dx<0){
        dx=-1;
    }
    if (dy>0){
        dy=1;
    }
    else if(dy<0){
        dy=-1;
    }

    int x_check=x+dx;
    int y_check=y+dy;

    while (x_check != x_b || y_check != y_b){
        if (board[x_check][y_check]!='.'){
            return false;
        }
        x_check+=dx;
        y_check+=dy;
    }
    return true;

}


bool Piece_text::tot_di_chuyen(int x, int y, int x_b, int y_b, char board[8][8]){
    if (((x==1 && board[x][y]=='p' && (y-y_b)==0) || (x==6 && board[x][y]=='P' && (y-y_b)==0))&&(abs(x-x_b)==2)){
            if((board[x][y]=='p' && board[x+1][y]=='.' && board[x+2][y]=='.')||(board[x][y]=='P' && board[x-1][y]=='.' && board[x-2][y]=='.')){
                std::cout << "1";
                return true;
            }
    }
    else if (abs(x-x_b)>1 || abs(y-y_b)>1){
            std::cout << "2";
        return false;
    }
    if (abs(x-x_b)==abs(y-y_b)){
        if (isupper(board[x_b][y_b])==isupper(board[x][y]) || board[x_b][y_b]=='.'){
            std::cout << "3";
            return false;
        }
        return true;
    }
    if (board[x_b][y_b]!='.'){
        return false;
    }
    if ((board[x][y]=='p' && (x_b-x)==1 && (y-y_b)==0)||(board[x][y]=='P' && (x-x_b)==1 && (y-y_b)==0) ){
        return true;
    }




};

bool Piece_text::nhap_thanh(char board[8][8],int x, int y, int x_b, int y_b, int nhap_thanh_check[]){
    int y_temp = y_b;
    if (y_b==0){
        y_temp++;
    }
    else{
        y_temp--;
    }



    if (is_blocking_piece(x,y,x_b,y_temp,board) && (nhap_thanh_check[0]==0 || nhap_thanh_check[1]==0) && isupper(board[x][y]) && (board[x_b][y_b]=='R' ||(x_b==7 && y_b==2) ||(x_b==7 && y_b==6) ) ){
        nhap_thanh_alert=true;
        nhap_thanh_checker_viet=0;
        return true;
    }
    else if(is_blocking_piece(x,y,x_b,y_temp,board) && (nhap_thanh_check[2]==0 || nhap_thanh_check[3]==0) && !isupper(board[x][y])&& (board[x_b][y_b]=='r' ||(x_b==0 && y_b==2) ||(x_b==0 && y_b==6) )){
        nhap_thanh_alert=true;
        nhap_thanh_checker_viet=2;
        return true;
    }
    return false;
}

bool Piece_text::moving_piece_text_check(int x, int y, int x_b, int y_b, char board[8][8], int nhap_thanh_check[]){
    int dx= abs(x-x_b);
    int dy= abs(y-y_b);
    switch (Piece_type){
    case 'p':
        return tot_di_chuyen(x,y,x_b,y_b,board);
        break;

    case 'P':
        return tot_di_chuyen(x,y,x_b,y_b,board);
        break;

    case 'n':
        return (dx*dy==2)&& is_blocking_piece(x,y,x_b,y_b,board);
        break;

    case 'N':
        return (dx*dy==2)&& is_blocking_piece(x,y,x_b,y_b,board);
        break;

    case 'b':
        return (dx == dy && is_blocking_piece(x,y,x_b,y_b,board));
        break;
    case 'B':
        return (dx == dy && is_blocking_piece(x,y,x_b,y_b,board));
        break;
    case 'r':
        return ((dx==0 || dy==0) && is_blocking_piece(x,y,x_b,y_b,board));
        break;
    case 'R':
        return ((dx==0 || dy==0)&&is_blocking_piece(x,y,x_b,y_b,board));
        break;
    case 'q':
        return ((dx==0 || dy ==0 || dx == dy)&&is_blocking_piece(x,y,x_b,y_b,board));
        break;
    case 'Q':
        return ((dx==0 || dy ==0 || dx == dy)&&is_blocking_piece(x,y,x_b,y_b,board));
        break;
    case 'k':
        return (dx <= 1 && dy <= 1 &&is_blocking_piece(x,y,x_b,y_b,board)) || nhap_thanh(board,x,y,x_b,y_b, nhap_thanh_check);
        break;
    case 'K':
        return ((dx <= 1 && dy <= 1 &&is_blocking_piece(x,y,x_b,y_b,board)) || nhap_thanh(board,x,y,x_b,y_b, nhap_thanh_check));
        break;
    case 's':
        return false;
        break;
    }



};

int Piece_text::moving_piece_text(char board[8][8],int x, int y, int x_b, int y_b, bool &turn, int nhap_thanh_check[]){
    // tra ve 0 neu nuoc di khong hop le, tra ve 1 neu nươc di dung, tra ve 0 neu nh
    bool check=false;
    if(turn && isupper(Piece_type)){
        check = true;
    }
    else if (!turn && !isupper(Piece_type)){
        check = true;
    }
    else{
        check= false;
    }


    if (check){
        if (moving_piece_text_check(x,y,x_b,y_b, board, nhap_thanh_check)){
            if(board[x_b][y_b]=='k'){
                return 9;
            }
            if(nhap_thanh_alert){
                if(((y_b-y)<0) && nhap_thanh_check[nhap_thanh_checker_viet]==0){
                    if (y_b==2){
                        y_b=0;
                    }
                    board[x][y-2]=board[x][y];
                    board[x][y]='.';
                    board[x][y_b+abs(y_b-y)-1]=board[x][y_b];
                    board[x][y_b]='.';
                    nhap_thanh_check[0+nhap_thanh_checker_viet]=1;
                    nhap_thanh_check[1+nhap_thanh_checker_viet]=1;
                    turn=!turn;
                    return 2;

                }
                else if((y_b-y)>0 && nhap_thanh_check[nhap_thanh_checker_viet+1]==0){
                    if (y_b==6){
                        y_b=7;
                    }
                    board[x][y+2]=board[x][y];
                    board[x][y]='.';
                    board[x][y_b-abs(y_b-y)+1]=board[x][y_b];
                    board[x][y_b]='.';
                    nhap_thanh_check[0+nhap_thanh_checker_viet]=1;
                    nhap_thanh_check[1+nhap_thanh_checker_viet]=1;
                    turn=!turn;
                    return 3;
                        }
                else{

                    return 0;
                }

                    }
            else{
            if (board[x][y]=='K' || board[x][y]=='R'){
                if (board[x][y]=='R'){
                    if(y==0){
                        nhap_thanh_check[0]=1;

                    }
                    else if (y==7){
                        nhap_thanh_check[1]=1;

                    }
                }
               else{
                    nhap_thanh_check[0]=1;
                    nhap_thanh_check[1]=1;
               }
            }
            else if(board[x][y]=='k' || board[x][y]=='r'){
                if (board[x][y]=='r'){
                    if(y==0){
                        nhap_thanh_check[2]=1;
                    }
                    else if (y==7){
                        nhap_thanh_check[3]=1;
                    }
                }
               else{
                    nhap_thanh_check[2]=1;
                    nhap_thanh_check[3]=1;
               }
            }
            if(board[x][y]=='p' && x_b==7){
                return -5;
            }
            if(board[x][y]=='P' && x_b==0){
                return 5;
            }

            board[x][y]='.';
            board[x_b][y_b]=Piece_type;
            turn=!turn;
            return 1;

        }
        }
        else{
            std::cout << "nuoc di sai";
            return 0;
        }
    }
    else{
        std::cout << "chua den luot";
        return 0;
    }
};


