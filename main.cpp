#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <iomanip>
struct GameSettings {
    char player1symbol = 'X', player2symbol = 'O';
    int BoardSize = 5;
    int SymbolsToWin = 3;
};
void print_board(const GameSettings& settings, const std::vector<std::vector<char>>& board) {
    std::cout << std::setw(3) << " "; 
    for(int j = 0; j < settings.BoardSize; j++) {
        char colHeader = 'A' + j;
        std::cout << std::setw(3) << colHeader;
    }
    std::cout << "\n";

    for(int i = 0; i < settings.BoardSize; i++) {
        std::cout << std::setw(3) << i; 
        for(int j = 0; j < settings.BoardSize; j++) {
            std::cout << std::setw(3) << board[i][j]; 
        }
        std::cout << "\n";
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
bool parse_input(const std::string& input, int& row, int& col, const GameSettings& settings)
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
        if(col < 0 || col >= settings.BoardSize) return false;
        if(row < 0 || row >= settings.BoardSize) return false;

    return true;
 
}
void open_settings(GameSettings& settings) {
    std::string choice;
    while (true) {
        std::cout << "Ustawienia gry \n";
        std::cout << " 1. Wybierz rozmiar planszy, obecnie " << settings.BoardSize << "\n";
        std::cout << " 2. Zmien symbol gracza 1, obecnie " << settings.player1symbol << "\n";
        std::cout << " 3. Zmien symbol gracza 2, obecnie " << settings.player2symbol << "\n";
        std::cout << " 4. Zmien warunek wygranej (ile symboli pod rzad), obecnie " << settings.SymbolsToWin << "\n";
        std::cout << " 5. Wroc do menu glownego\n";
        std::cout << "Twoj wybor: ";
        std::cin >> choice;

        if (!is_digit(choice)) {
            std::cout << "Niepoprawny wybor (wpisz numer opcji).\n";
            continue;
        }

        int choice_i = std::stoi(choice);
        switch (choice_i) {
        case 1: {
            std::string newSize_s;
            std::cout << "Podaj nowy rozmiar planszy (od 3 do 10): ";
            std::cin >> newSize_s;

            if (!is_digit(newSize_s)) {
                std::cout << "To nie liczba!\n";
                break;
            }

            int newSize = std::stoi(newSize_s);

            if (newSize >= 3 && newSize <= 10) {
                settings.BoardSize = newSize;
                if (settings.SymbolsToWin > settings.BoardSize) {
                    settings.SymbolsToWin = settings.BoardSize;
                    std::cout << "Uwaga: SymbolsToWin byl wiekszy niz rozmiar planszy. Dostosowano do " << settings.SymbolsToWin << ".\n";
                }

                std::cout << "Rozmiar planszy ustawiony na: " << settings.BoardSize << "\n";
            }
            else {
                std::cout << "Niepoprawny rozmiar!\n";
            }

            break;
        }
        case 2: {
            char newSymbol;
            std::cout << "Podaj symbol gracza 1: ";
            std::cin >> newSymbol;

            if (newSymbol == ' ' || std::isdigit((newSymbol))) {
                std::cout << "Niepoprawny symbol (nie moze byc spacja ani cyfra).\n";
                break;
            }

            if (newSymbol == settings.player2symbol) {
                std::cout << "Ten symbol jest używany przez gracza 2!\n";
                break;
            }

            settings.player1symbol = newSymbol;
            break;
        }
        case 3: {
            char newSymbolCase3;
            std::cout << "Podaj symbol gracza 2: ";
            std::cin >> newSymbolCase3;

            if (newSymbolCase3 == ' ' || std::isdigit((newSymbolCase3))) {
                std::cout << "Niepoprawny symbol (nie moze byc spacja ani cyfra).\n";
                break;
            }

            if (newSymbolCase3 == settings.player1symbol) {
                std::cout << "Ten symbol jest już używany przez gracza 1!\n";
                break;
            }
            settings.player2symbol = newSymbolCase3;
            break;
        }
        case 4: {
            std::cout << "Podaj ile symboli pod rzad jest wymagane by wygrać: ";
            std::string change_win_condition_s;
            std::cin >> change_win_condition_s;

            if (!is_digit(change_win_condition_s)) {
                std::cout << "To nie jest liczba!\n";
                break;
            }

            int new_win_condition = std::stoi(change_win_condition_s);

            if (new_win_condition == settings.SymbolsToWin) {
                std::cout << "To ta sama liczba!\n";
            }
            else if (new_win_condition < 3 || new_win_condition > settings.BoardSize) {
                std::cout << "Niepoprawna liczba, musi być >=3 i <= rozmiar planszy\n";
            }
            else {
                settings.SymbolsToWin = new_win_condition;
                std::cout << "Liczba symboli do wygranej ustawiona na: " << settings.SymbolsToWin << "\n";
            }

            break;
        }
        case 5:
            return;
        default:
            std::cout << "Nieznana opcja.\n";
            break;
        }
    }
}
bool make_move(char current_player,  std::vector<std::vector<char>>& board, const GameSettings& settings, int& row, int&col){
    std::string input;
    std::cin >> input;
    if(!parse_input(input, row, col, settings))
    {
     std::cout << "Zle dane\n";   
     return false;
    }
    if(board[row][col] != ' ')
    {
        std::cout << "To pole jest juz zajete";
        return false;
    }
    board[row][col] = current_player;
    return true;
}

bool check_draw(const std::vector<std::vector<char>>& board)
{
    for(const auto& row : board){
        for(const auto& cell : row){
            if(cell == ' ') return false;
        }
    }
    return true; 
}
bool check_win_row(const GameSettings& settings, const std::vector<std::vector<char>>& board, int row, int col, char CurrentPlayer){
    int count = 1;
    int i = col - 1; /// w lewo 
    while(i >= 0 && board[row][i] == CurrentPlayer)
    {
        count++;
        i--;
    }
    i = col + 1; /// w prawo 
    while(i < settings.BoardSize && board[row][i] == CurrentPlayer)
    {
        count++;
        i++;
    }
    if(!(count >= settings.SymbolsToWin)) return false;

    return true;
}
bool check_win_col(const GameSettings& settings, const std::vector<std::vector<char>>& board, int row, int col, char CurrentPlayer)
{
    int count = 1;
    int i = row - 1; /// w góre 
    while(i >= 0 && board[i][col] == CurrentPlayer){
        count++;
        i--;
    }
    i = row + 1;
    while(i < settings.BoardSize && board[i][col] == CurrentPlayer){
        count++;
        i++;
    }
    if(!(count >= settings.SymbolsToWin)) return false;

    return true;
}
bool check_win_diagonal(const GameSettings& settings, const std::vector<std::vector<char>>& board, int row, int col, char CurrentPlayer)
{
    int r = row - 1;
    int c = col - 1;
    int count = 1;
    while(r >= 0 && c >= 0 && board[r][c] == CurrentPlayer){ /// w lewo w dół 
        r--;
        c--;
        count++;
    }
    r = row + 1;
    c = col + 1;
    while(r < settings.BoardSize && c < settings.BoardSize && board[r][c] == CurrentPlayer)
    {
        r++;
        c++;
        count++;
    }
    if(count >= settings.SymbolsToWin) return true;

    r = row - 1;
    c = col + 1;
    count = 1;
    while(r >= 0 && c < settings.BoardSize && board[r][c] == CurrentPlayer)
    {
        r--;
        c++;
        count++;
    }
    r = row + 1;
    c = col - 1;
    while(r < settings.BoardSize && c >= 0 && board[r][c] == CurrentPlayer)
    {
        r++;
        c--;
        count++;
    }
    if(count >= settings.SymbolsToWin) return true;

    return false;
}
bool check_win(const GameSettings& settings, const std::vector<std::vector<char>>& board, int row, int col, char CurrentPlayer)
{
    return check_win_col(settings, board, row, col, CurrentPlayer) || 
           check_win_row(settings, board, row, col, CurrentPlayer) ||
           check_win_diagonal(settings, board, row, col, CurrentPlayer);
}
void play_pvp(const GameSettings& settings)
{
    std::vector<std::vector<char>> board(settings.BoardSize, std::vector<char>(settings.BoardSize, ' '));
    char Current_Player = settings.player1symbol;
    int row, col;
    while(true)
    {
        print_board(settings, board);
        if(make_move(Current_Player, board, settings, row, col)){
            if(check_win(settings, board, row, col, Current_Player)){
                print_board(settings, board);
                std::cout << "Wygrywa gracz: " << Current_Player << "!\n";
                break;
            }
            if(check_draw(board)){
                print_board(settings, board);
                std::cout << "Remis! \n";
                break;
            }
            Current_Player = (Current_Player == settings.player1symbol) ? settings.player2symbol : settings.player1symbol;
        }
    }
}
int main(){
    GameSettings settings;
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
                play_pvp(settings);
                break;
            case 2:
                open_settings(settings);
                break;
        }
    }
    return 0;
}