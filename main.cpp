#include <iostream>
#include <vector>
#include <string>
#include <ctype.h>
/// board creation 
int BoardSize = 5;
std::vector<std::vector<char>> board(BoardSize, std::vector<char>(BoardSize, ' '));
void print_board(){
    std::cout << " ";
    for(int j = 0; j < BoardSize; j++)
    {
        char colHeader = 'A' + j;
        std::cout << colHeader;
    }
    for(int i = 0; i < BoardSize; i++)
    {
        int rowHeader = 0 + i;
        std::cout << rowHeader;
        for(int j = 0; j < BoardSize; j++)
        {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
bool is_digit(const std::string& s){
    if(s.empty()) return false;
    for(char c : s)
    {
        if(!std::isdigit(c)) return false;
    }
    return true;
}
char parse_input()
{

}
void play_pvp()
{

}
void open_settings(){

}
int main(){
    while(true)
    {
        std::string game_mode_str;
        std::cout << "Wybierz tryb: \n 1. Gracz kontra Gracz \n 2. Ustawienia \n";
        std::cin >> game_mode_str;
        if(!is_digit(game_mode_str)) continue;
        int game_mode = std::stoi(game_mode_str);
        if(game_mode < 1 || game_mode > 2) continue;
        switch (game_mode){
            case 1:
                play_pvp();
            case 2:
                open_settings();
        }
    }
    print_board();
    std::cin.get();
    return 0;
}