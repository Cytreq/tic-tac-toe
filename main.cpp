#include <iostream>
#include <vector>
#include <string>
#include <ctype.h>
/// board creation 
int BoardSize = 5;
char player1symbol = 'X', player2symbol = 'O';
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
        std::cout << rowHeader << " ";
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
bool parse_input(std::string input, int& row, int& col)
{

        if(!std::isalpha(input[0]) || input.size() < 2)
        {
            return false;
        }
        for(int i = 1; i < input.size(); i++)
        {
            if(!std::isdigit(input[i]))
            {
                return false;
            }
        }
        col = std::toupper(input[0]) - 'A';
        row = std::stoi(input.substr(1));
        if(col < 0 || col >= BoardSize) return false;
        if(row < 0 || row >= BoardSize) return false;

    return true;
 
}
void play_pvp()
{

}
void open_settings(){
    std::string choice;
    while(true)
    {
        std::cout << "Ustawienia gry \n";
        std::cout << " 1. Wybierz rozmiar planszy, obecnie " << BoardSize << "\n";
        std::cout << "2. Zmień symbol gracza 1, obecnie" << player1symbol << "\n";
        std::cout << "3. Zmień symbol gracza 2, obecnie" << player2symbol << "\n";
        std::cout << "4. Wróc do menu głównego\n";
        std::cout << "Twój wybór: ";
        std::cin >> choice;
        int choice_i = std::stoi(choice);
        switch (choice_i)
        {
        case 1: {
            std::string newSize_s;
            std::cout << "Podaj nowy rozmiar planszy (od 3 do 10): ";
            std::cin >> newSize_s;

            if(!is_digit(newSize_s)) {
                std::cout << "To nie liczba!\n";
                break;
            }

            int newSize = std::stoi(newSize_s);

            if(newSize >= 3 && newSize <= 10) {
                BoardSize = newSize;
                board = std::vector<std::vector<char>>(BoardSize, std::vector<char>(BoardSize, ' ')); 
                std::cout << "Rozmiar planszy ustawiony na: " << BoardSize << "\n";
            } else {
                std::cout << "Niepoprawny rozmiar!\n";
            }

            break;
} 

        case 2:
            std::cout << "Podaj symbol gracza 1: ";
            std::cin >> player1symbol;
            break;
        case 3: 
            std::cout << "Podaj symbol gracza 2: ";
            std::cin >> player2symbol;
            break;
        case 4:
            return;
        default:
            break;
        }
    }
    
}
void make_move(char current_player, std::string input){
    
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
                break;
            case 2:
                open_settings();
                break;
        }
    }
    print_board();
    std::cin.get();
    return 0;
}