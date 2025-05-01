#include "Render_image.h"
#include "Moving.h"
#include "Core_basic.h"
#include "Chess_Convert_Commend.h"
#include "Stock_Fish_Connector.h"
#include "Game_starting.h"

bool start_sdl(){
     if (SDL_Init(SDL_INIT_EVERYTHING)==0){
        return true;
     }
     return false;

}

bool initAudio() {
    // Khởi tạo SDL (âm thanh)
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        SDL_Log("Không thể khởi tạo SDL Audio: %s", SDL_GetError());
        return false;
    }

    // Khởi tạo SDL_mixer với định dạng âm thanh
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        SDL_Log("Không thể khởi tạo SDL_mixer: %s", Mix_GetError());
        return false;
    }

    return true;
}

SDL_Window* window= NULL;
SDL_Event window_event;
SDL_Renderer* renderer= NULL;
Render_image null_render_image;


const int H_window=900;
const int W_window=900;
const std::string Win_title="chess platium";
bool is_game_running=true;
bool is_hold =false;
bool correct_move=false;
int x_mouse_convert = 0;
int y_mouse_convert = 0;
int game_status=-1;

int phong_cap_x=0;
int phong_cap_y=0;
int phong_cap_x_b=0;
int phong_cap_y_b=0;
bool phong_cap_check=false;
bool type_play=false;

char board_text[8][8];
Render_image chess_mana[8][8];
Render_image chess_board;
Render_image reset_button;
Render_image win_game;
Render_image lose_game;
Render_image game_menu;
Render_image game_choose;
Render_image phong_cap_img;


bool check_turn;
std::string board_data_now;
std::string in_dat;

int nhap_thanh_check[4]={0,0,0,0};







int mouse_x, mouse_y;




int main( int argc, char* args[] ){


    std::string stockfishPath = "stockfish.exe";
    Stock_fish_engine engine(stockfishPath);
    engine.sendCommand("uci");
    engine.sendCommand("ucinewgame");
    engine.sendCommand("setoption name UCI_LimitStrength value true");

    engine.sendCommand("position startpos moves f2f3 e7e5 g2g4 d8h4");
    engine.sendCommand("go depth 10");
    std::string trungdeptrai=engine.readResponse();







    if (!start_sdl()){
        std::cout << "cannot start sdl";
    }
    if (!initAudio()){
        std::cout << "cannot start audio";
    }
    Mix_Music* bg_music = Mix_LoadMUS("music/background.mp3");
    Mix_Chunk* click_sound = Mix_LoadWAV("music/click.wav");
    Mix_Chunk* move_sound = Mix_LoadWAV("music/move.wav");
    Mix_VolumeChunk(click_sound, 60);
    Mix_VolumeChunk(move_sound, 60);
    Mix_VolumeMusic(10);



    window = SDL_CreateWindow(Win_title.c_str(), SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, W_window, H_window, SDL_WINDOW_SHOWN);
    renderer= SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Render_image piece_image_mana[8][8];

    for (int i=0; i<8;i++){
        for (int j =0; j<8; j++){

        }
    }

    chess_board.Render_image_start(0,0,"image/chess_board.png",renderer);
    reset_button.Render_image_start(3,3,"image/reload.png",renderer);
    win_game.Render_image_start(0,0,"image/win.png",renderer);
    lose_game.Render_image_start(0,0,"image/lose.png",renderer);
    game_menu.Render_image_start(0,0,"image/menu.png",renderer);
    game_choose.Render_image_start(0,0,"image/choose.png",renderer);
    phong_cap_img.Render_image_start(0,0,"image/phong_cap.png",renderer);

    Mix_PlayMusic(bg_music, -1);


    while (bool menu_status=true){
            bool out=false;
            std::cout << mouse_x << " " << mouse_y << std::endl;

            while(SDL_PollEvent(&window_event)!=0 ){

                if (window_event.type == SDL_QUIT){

                    return(1);
                }
                SDL_GetMouseState(&mouse_x,&mouse_y);

                if(window_event.type == SDL_MOUSEBUTTONUP && mouse_x>350 && mouse_y>160 && mouse_x<535 && mouse_y<210){
                        type_play=true;

                    }
                if(window_event.type == SDL_MOUSEBUTTONUP && mouse_x>350 && mouse_y>295 && mouse_x<510 && mouse_y<340){
                        return 1;

                    }
                SDL_RenderClear(renderer);
                game_menu.Load_image(renderer,900,900);
                if (type_play){
                    game_choose.Load_image(renderer,900,900);
                }
                if(type_play && window_event.type == SDL_MOUSEBUTTONDOWN && mouse_x>350 && mouse_y>175 && mouse_x<490 && mouse_y<210){
                        engine.sendCommand("setoption name UCI_Elo value 500");
                        std::cout << "ga";
                        out=true;
                    }

                if(type_play && window_event.type == SDL_MOUSEBUTTONDOWN && mouse_x>320 && mouse_y>270 && mouse_x<530 && mouse_y<310){
                        engine.sendCommand("setoption name UCI_Elo value 1300");
                        out=true;
                    }
                if(type_play && window_event.type == SDL_MOUSEBUTTONDOWN && mouse_x>340 && mouse_y>365 && mouse_x<490 && mouse_y<400){
                        engine.sendCommand("setoption name UCI_Elo value 2500");
                        out=true;
                    }
                SDL_RenderPresent(renderer);
                SDL_Delay(1);
            }
            if(out){
                break;
            }




    }






    new_game(chess_mana, renderer,board_text,null_render_image, board_data_now,check_turn,nhap_thanh_check);






    while(is_game_running){





        while(SDL_PollEvent(&window_event)!=0 ){
            if (window_event.type == SDL_QUIT){





                is_game_running=false;
            }



            SDL_GetMouseState(&mouse_x,&mouse_y);


            piece_check(is_hold,window_event);
            if ((window_event.type == SDL_MOUSEBUTTONDOWN ) && window_event.button.button == SDL_BUTTON_LEFT){
                Mix_PlayChannel(-1, click_sound, 0);
                x_mouse_convert = (mouse_x-29)/105;
                y_mouse_convert = (mouse_y-29)/105;
            }

            if(is_hold){
                chess_mana[y_mouse_convert][x_mouse_convert].rect_.x=mouse_x-50;
                chess_mana[y_mouse_convert][x_mouse_convert].rect_.y=mouse_y-50;
            }
            if(window_event.type == SDL_MOUSEBUTTONDOWN && mouse_x<30 && mouse_y<30){
                new_game(chess_mana, renderer,board_text,null_render_image, board_data_now,check_turn,nhap_thanh_check);
            }



            if (window_event.type == SDL_MOUSEBUTTONUP && window_event.button.button == SDL_BUTTON_LEFT && check_turn){
                int x_temp = (mouse_x-29)/105;
                int y_temp = (mouse_y-29)/105;
                int kiem_tra_nuoc_di_cuoi=100;

                Piece_text temp(board_text[y_mouse_convert][x_mouse_convert]);
                kiem_tra_nuoc_di_cuoi=temp.moving_piece_text(board_text,y_mouse_convert,x_mouse_convert,y_temp,x_temp,check_turn,nhap_thanh_check);


                if(kiem_tra_nuoc_di_cuoi==1){
                    in_dat=covert_commend_in(y_mouse_convert,x_mouse_convert,y_temp,x_temp);
                    std::cout << in_dat;
                    board_data_now=board_data_now+in_dat+' ';


                    chess_mana[y_mouse_convert][x_mouse_convert].rect_.x=x_temp*105+29;
                    chess_mana[y_mouse_convert][x_mouse_convert].rect_.y=y_temp*105+29;
                    chess_mana[y_temp][x_temp]=chess_mana[y_mouse_convert][x_mouse_convert];
                    chess_mana[y_mouse_convert][x_mouse_convert]=null_render_image;
                    Mix_PlayChannel(-1, move_sound, 0);

                }
                else if (kiem_tra_nuoc_di_cuoi==2){
                    std::cout << "nhap thanh xa";
                    if (x_temp==2){
                        x_temp=0;
                    }
                    chess_mana[y_mouse_convert][x_mouse_convert].rect_.x=(x_mouse_convert-2)*105+29;
                    chess_mana[y_mouse_convert][x_mouse_convert].rect_.y=y_mouse_convert*105+29;
                    chess_mana[y_mouse_convert][x_mouse_convert-2]=chess_mana[y_mouse_convert][x_mouse_convert];
                    chess_mana[y_mouse_convert][x_mouse_convert]=null_render_image;
                    chess_mana[y_mouse_convert][x_temp].rect_.x=(x_temp+abs(x_temp-x_mouse_convert)-1)*105+29;
                    chess_mana[y_mouse_convert][x_temp+abs(x_temp-x_mouse_convert)-1]=chess_mana[y_mouse_convert][x_temp];
                    chess_mana[y_mouse_convert][x_temp]=null_render_image;
                    in_dat=covert_commend_in(y_mouse_convert,x_mouse_convert,y_mouse_convert,x_mouse_convert-2);
                    std::cout << in_dat;
                    board_data_now=board_data_now+in_dat+' ';
                    Mix_PlayChannel(-1, move_sound, 0);

                }
                else if (kiem_tra_nuoc_di_cuoi==3){
                    std::cout << "nhap thanh gan";
                    if (x_temp==6){
                        x_temp=7;
                    }
                    chess_mana[y_mouse_convert][x_mouse_convert].rect_.x=(x_mouse_convert+2)*105+29;
                    chess_mana[y_mouse_convert][x_mouse_convert+2]=chess_mana[y_mouse_convert][x_mouse_convert];
                    chess_mana[y_mouse_convert][x_mouse_convert]=null_render_image;
                    chess_mana[y_mouse_convert][x_temp].rect_.x=(x_temp-abs(x_temp-x_mouse_convert)+1)*105+29;
                    chess_mana[y_mouse_convert][x_temp-abs(x_temp-x_mouse_convert)+1]=chess_mana[y_mouse_convert][x_temp];
                    chess_mana[y_mouse_convert][x_temp]=null_render_image;
                    in_dat=covert_commend_in(y_mouse_convert,x_mouse_convert,y_mouse_convert,x_mouse_convert+2);
                    std::cout << in_dat;
                    board_data_now=board_data_now+in_dat+' ';
                    Mix_PlayChannel(-1, move_sound, 0);

                }
                else if (kiem_tra_nuoc_di_cuoi==5){
                    phong_cap_x=y_mouse_convert;
                    phong_cap_y=x_mouse_convert;
                    phong_cap_x_b=y_temp;
                    phong_cap_y_b=x_temp;
                    phong_cap_check=true;
//                    check_turn=!check_turn;
                    std::cout << "siuuuuuuuu";
                    Mix_PlayChannel(-1, move_sound, 0);
                    continue;
                }
                else if(kiem_tra_nuoc_di_cuoi==0){
                    chess_mana[y_mouse_convert][x_mouse_convert].rect_.x=x_mouse_convert*105+29;
                    chess_mana[y_mouse_convert][x_mouse_convert].rect_.y=y_mouse_convert*105+29;
                }


            }
            if(!check_turn){

                int a,b,c,d;
                int test_check;
                engine.sendCommand(board_data_now);
                engine.sendCommand("go depth 10");
                in_dat = engine.readResponse();
                if (in_dat==trungdeptrai){
                    game_status=1;
                    check_turn=!check_turn;
                    std::cout << "w1";
                    std::cout << board_data_now;
                    continue;
                    //nguoi thang
                }
                std::cout << in_dat << std::endl;
                board_data_now=board_data_now+in_dat+' ';
                //ddddddddddd
                engine.sendCommand(board_data_now);
                engine.sendCommand("go depth 10");
                if (engine.readResponse()==trungdeptrai){
                    game_status=0;
                    check_turn=!check_turn;
                    std::cout << "w2";
                    std::cout << board_data_now;
                    continue;
                    //may thang
                }
                std::cout << "pass 1";
                //ddddddddddddd
                covert_commend_out(a,b,c,d,in_dat);
                Piece_text temp(board_text[a][b]);
                test_check=temp.moving_piece_text(board_text,a,b,c,d,check_turn,nhap_thanh_check);
                std::cout << "pass 2";
                if (test_check==0){
                    check_turn=!check_turn;
                    game_status=0;
                    std::cout << "w3";
                    std::cout << board_data_now;
                    continue;
                    // may end game
                }
                std::cout <<a <<b << c << d;
                if (test_check==2){
                    std::cout << "nhap thanh xa";
                    if (d==2){
                        d=0;
                    }
                    chess_mana[a][b].rect_.x=(b-2)*105+29;
                    chess_mana[a][b].rect_.y=a*105+29;
                    chess_mana[a][b-2]=chess_mana[a][b];
                    chess_mana[a][b]=null_render_image;
                    chess_mana[a][d].rect_.x=(d+abs(d-b)-1)*105+29;
                    chess_mana[a][d+abs(d-b)-1]=chess_mana[a][d];
                    chess_mana[a][d]=null_render_image;
                    in_dat=covert_commend_in(a,b,a,b-2);
                    Mix_PlayChannel(-1, move_sound, 0);
                    std::cout << in_dat;


                }
                else if (test_check==3){
                    std::cout << "nhap thanh gan";
                    if (d==6){
                        d=7;
                    }
                    chess_mana[a][b].rect_.x=(b+2)*105+29;
                    chess_mana[a][b+2]=chess_mana[a][b];
                    chess_mana[a][b]=null_render_image;
                    chess_mana[a][d].rect_.x=(d-abs(d-b)+1)*105+29;
                    chess_mana[a][d-abs(d-b)+1]=chess_mana[a][d];
                    chess_mana[a][d]=null_render_image;
                    in_dat=covert_commend_in(a,b,a,b+2);
                    std::cout << in_dat;
                    Mix_PlayChannel(-1, move_sound, 0);


                }
                else if (test_check==-5){
                    phong_cap_x=a;
                    phong_cap_y=b;
                    phong_cap_x_b=c;
                    phong_cap_y_b=d;
                    phong_cap(chess_mana,renderer,board_text,phong_cap_x,phong_cap_y,phong_cap_x_b,phong_cap_y_b,in_dat[4]);
                    check_turn=!check_turn;
                    Mix_PlayChannel(-1, move_sound, 0);

                }
                else {
                chess_mana[a][b].rect_.x=d*105+29;
                chess_mana[a][b].rect_.y=c*105+29;
                chess_mana[c][d]=chess_mana[a][b];
                chess_mana[a][b]=null_render_image;
                Mix_PlayChannel(-1, move_sound, 0);
                }


            }

            //chess board reder
            SDL_RenderClear(renderer);
            chess_board.Load_image(renderer,900,900);


            reset_button.Load_image(renderer,30,30);
//            for (int i=0; i<8; i++){
//                for (int j=0; j<8; j++){
//
//                    chess_mana[i][j].Load_image(renderer,100,100);
//                }
//            }

            if (phong_cap_check){
                char phong_gi;
                if (window_event.type == SDL_MOUSEBUTTONDOWN && mouse_x>125 && mouse_y>400 && mouse_x<250 && mouse_y<500){
                    phong_gi='B';
                    phong_cap(chess_mana,renderer,board_text,phong_cap_x,phong_cap_y,phong_cap_x_b,phong_cap_y_b,phong_gi);
                    check_turn=!check_turn;
                    phong_gi=tolower(phong_gi);
                    board_data_now=board_data_now+covert_commend_in(phong_cap_x,phong_cap_y,phong_cap_x_b,phong_cap_y_b)+phong_gi+' ';
                    phong_cap_check=false;

                }

                else if (window_event.type == SDL_MOUSEBUTTONDOWN && mouse_x>350 && mouse_y>400 && mouse_x<425 && mouse_y<500){
                    phong_gi='N';
                    phong_cap(chess_mana,renderer,board_text,phong_cap_x,phong_cap_y,phong_cap_x_b,phong_cap_y_b,phong_gi);
                    check_turn=!check_turn;
                    phong_gi=tolower(phong_gi);
                    board_data_now=board_data_now+covert_commend_in(phong_cap_x,phong_cap_y,phong_cap_x_b,phong_cap_y_b)+phong_gi+' ';
                    phong_cap_check=false;

                }
                else if (window_event.type == SDL_MOUSEBUTTONDOWN && mouse_x>525 && mouse_y>400 && mouse_x<600 && mouse_y<500){
                    phong_gi='Q';
                    phong_cap(chess_mana,renderer,board_text,phong_cap_x,phong_cap_y,phong_cap_x_b,phong_cap_y_b,phong_gi);
                    check_turn=!check_turn;
                    phong_gi=tolower(phong_gi);
                    board_data_now=board_data_now+covert_commend_in(phong_cap_x,phong_cap_y,phong_cap_x_b,phong_cap_y_b)+phong_gi+' ';
                    phong_cap_check=false;

                }
                else if (window_event.type == SDL_MOUSEBUTTONDOWN && mouse_x>700 && mouse_y>400 && mouse_x<775 && mouse_y<500){
                    phong_gi='R';
                    phong_cap(chess_mana,renderer,board_text,phong_cap_x,phong_cap_y,phong_cap_x_b,phong_cap_y_b,phong_gi);
                    check_turn=!check_turn;
                    phong_gi=tolower(phong_gi);
                    board_data_now=board_data_now+covert_commend_in(phong_cap_x,phong_cap_y,phong_cap_x_b,phong_cap_y_b)+phong_gi+' ';
                    phong_cap_check=false;

                }

                phong_cap_img.Load_image(renderer,900,900);
            }
            for (int i=0; i<8; i++){
                for (int j=0; j<8; j++){

                    chess_mana[i][j].Load_image(renderer,100,100);
                }
            }


            if (game_status!=-1){
                if (game_status==1){
                    if(window_event.type == SDL_MOUSEBUTTONDOWN && mouse_x>350 && mouse_y>700 && mouse_x<410 && mouse_y<730){
                        new_game(chess_mana, renderer,board_text,null_render_image, board_data_now,check_turn,nhap_thanh_check);
                        game_status=-1;
                    }
                    else if(window_event.type == SDL_MOUSEBUTTONDOWN && mouse_x>500 && mouse_y>700 && mouse_x<550 && mouse_y<730){
                        return -1;
                    }


                    win_game.Load_image(renderer,900,900);

                }
                if (game_status==0){
                    if(window_event.type == SDL_MOUSEBUTTONDOWN && mouse_x>350 && mouse_y>700 && mouse_x<410 && mouse_y<730){
                        new_game(chess_mana, renderer,board_text,null_render_image, board_data_now,check_turn,nhap_thanh_check);
                        game_status=-1;
                    }
                    else if(window_event.type == SDL_MOUSEBUTTONDOWN && mouse_x>500 && mouse_y>700 && mouse_x<550 && mouse_y<730){
                        return -1;
                    }
                    lose_game.Load_image(renderer,900,900);
                }
            }


            SDL_RenderPresent(renderer);
            SDL_Delay(1);





        }








    }









    IMG_Quit();
    return 1;


}
