#ifndef START_BOT_H_INCLUDED
#define START_BOT_H_INCLUDED

void start_bot(){
    std::string stockfishPath = "stockfish.exe";
    Stock_fish_engine engine(stockfishPath);
    engine.sendCommand("uci");
    engine.sendCommand("ucinewgame");
    engine.sendCommand("setoption name UCI_LimitStrength value true");
    engine.sendCommand("setoption name UCI_Elo value 2000");
}



#endif // START_BOT_H_INCLUDED
