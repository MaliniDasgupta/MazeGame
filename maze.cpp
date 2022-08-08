#include <string>
#include <iostream>
#include <fstream>
#include <vector>

void UserInputMode(std::vector<std::string> &Board); //function called when game is in user input mode
void FileInputMode(std::vector<std::string> &Board, std::string InputFile); //function called when game is in file input mode
void PrintBoard(std::vector<std::string> Board); //function called to print board
int ValidMove(std::vector<std::string> &Board, char move, int& won); //function called to check for valid move, returns 1 if valid. If the move results in the user winning the game, the value of 'won' becomes 1

int main(int argc, char* argv[]){
    
    if(argc<2 || argc>3){
        std::cerr << "Wrong number of arguments." << std::endl;
        return 1;
    }

    std::ifstream InputBoard {argv[1]};
    std::vector<std::string> Board;
    std::string line; 
    while(InputBoard>>line){   // Used https://stackoverflow.com/questions/7868936/read-file-line-by-line-using-ifstream-in-c to learn how to read through a file
        Board.push_back(line);
    }    
    if(argc==2){
        UserInputMode(Board);
    }
    else{
        FileInputMode(Board, argv[2]);
    }

}

void UserInputMode(std::vector<std::string> &Board){
    //function called when game is in user input mode
    PrintBoard(Board);
    char move;
    do{
        std::cout << "> ";
        std::cin >> move;
        if(move == 'a' || move == 'd' || move == 'w' || move == 's'){
            int won = 0;
            int check = ValidMove(Board,move,won);
            if(check){
                PrintBoard(Board);
                if(won){
                    std::cout << "You won the game." <<std::endl;
                    break;
                }
            }
            else{
                std::cout << "You can't move there." << std::endl;
                PrintBoard(Board);
            }
        }
        else if(move == 'q'){
            std::cout << "You quit the game." << std::endl;
        }
        else{
            std::cout << "Invalid input." << std::endl;
            PrintBoard(Board);
        }
    }
    while(move!='q');

}

void FileInputMode(std::vector<std::string> &Board, std::string InputFile){
    //function called when game is in file input mode
    std::ifstream input {InputFile};
    char a;
    int won = 0;
    int checker = 0;
    while(input>>a){
        if(a == 'w' || a == 'a' || a == 's' || a == 'd'){
            if(ValidMove(Board,a,won) == 1){
                if(won){
                    std::cout<<"That input results in a victory." << std::endl;
                    checker++;
                    break;
                }
                continue;
            }
            else{
                std::cout<<"Hit wall." << std::endl;
                checker++;
                break;
            }
        }
        else{
            std::cout << "Invalid input encountered in input sequence." << std::endl;
            checker++;
            break;
        }
    }
    if(checker == 0){
        std::cout << "That  input  does  not  reach  the  end." << std::endl;
    }
} 


void PrintBoard(std::vector<std::string> Board){
    //function called to print board
    std::cout << "-------" << std::endl;
    for(unsigned int i=0;i<Board.size();i++){
        std::cout << "|" << Board[i] << "|" << std::endl;
    }
    std::cout << "-------" << std::endl;
} 

int ValidMove(std::vector<std::string> &Board, char move, int& won){
    //function called to check for valid move, returns 1 if valid. If the move results in the user winning the game, the value of 'won' becaomes 1

    for(unsigned int i=0;i<Board.size();i++){
        for(unsigned int j=0;j<Board[i].length();j++){
            if(Board[i][j]=='@'){
                if(move == 'a'){
                    if(j!=0 && (Board[i][j-1] == '.' || Board[i][j-1] == '$')){
                       if(Board[i][j-1] == '$'){
                           won = 1;
                       }
                       Board[i][j] = '.';
                       Board[i][j-1] = '@';    
                       return 1;
                    }
                    return 0;
                }
                if(move == 'd'){
                    if(j!=Board[i].length()-1 && (Board[i][j+1] == '.' || Board[i][j+1] == '$')){
                        if(Board[i][j+1] == '$'){
                            won = 1;
                        }
                        Board[i][j] = '.';
                        Board[i][j+1] = '@';
                        return 1;
                    }
                    return 0;
                }
                if(move == 'w'){
                    if(i!=0 && (Board[i-1][j] == '.' || Board[i-1][j] == '$')){
                        if(Board[i-1][j] == '$'){
                            won = 1;
                        }
                        Board[i][j] = '.';
                        Board[i-1][j] = '@'; 
                        return 1;
                    }
                    return 0;
                }
                if(move == 's'){
                    if(i!=Board.size()-1 && (Board[i+1][j] == '.' || Board[i+1][j] == '$')){
                        if(Board[i+1][j] == '$'){
                            won = 1;
                        }
                        Board[i][j] = '.';
                        Board[i+1][j] = '@'; 
                        return 1;
                    }
                    return 0;
                }
            }
        }
    }
    return 0;
} 
