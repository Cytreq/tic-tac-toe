#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <ctype.h>
/// board creation 
void create_board(int n){
    std::vector<std::vector<char>> board(n, std::vector<char>(n, ' '));
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
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

int main(){
    return 0;
}