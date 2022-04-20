#include<bits/stdc++.h>
#include <iostream>
#include<list>
#include <cstdlib>
#include<string>
#include <ctime>
using namespace std;
 
typedef struct{
    int *row;
}WinList;
 
 
class Player {
private:
    string name;
    int score;
public:
    Player() :Player {""}{}
    Player(string n) :score{0}, name{n}{}
 
    void won(){
        //increment the score
        score++;
    }
    int getScore(){ return this->score;}
 
    string getName(){ return this->name;}
};
 
struct Move
{
    int row, col;
};
 
char player = 'x', opponent = 'o';
 
 
// This function returns true if there are moves remaining on the board and false if there are no moves left to play.
bool isMovesLeft(char board[3][3])
{
    for (int i = 0; i<3; i++)
        for (int j = 0; j<3; j++)
            if (board[i][j]=='_')
                return true;
    return false;
}

string checkWinner(char b[3][3]) {
 
  // horizontal
  for (int row = 0; row<3; row++)
    {
        if (b[row][0]==b[row][1] &&
            b[row][1]==b[row][2])
        {
            if (b[row][0]==player)
                return "x";
            else if (b[row][0]==opponent)
                return "o";
        }
    }
 
  // Vertical
   for (int col = 0; col<3; col++)
    {
        if (b[0][col]==b[1][col] &&
            b[1][col]==b[2][col])
        {
            if (b[0][col]==player)
                return "x";
 
            else if (b[0][col]==opponent)
                return "o";
        }
    }
 
  // Diagonal
  // Checking for Diagonals for X or O victory.
    if (b[0][0]==b[1][1] && b[1][1]==b[2][2])
    {
        if (b[0][0]==player)
            return "x";
        else if (b[0][0]==opponent)
            return "o";
    }
 
    if (b[0][2]==b[1][1] && b[1][1]==b[2][0])
    {
        if (b[0][2]==player)
            return "x";
        else if (b[0][2]==opponent)
            return "o";
    }
 
  int openSpots = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (b[i][j] == '_') {
        openSpots++;
      }
    }
  }
 
  if(openSpots){
      return "null";
  }
  return "tie";
}
 
// This is the minimax function that considers all the possible ways the game can go and returns the value of the board

int minimax(char board[3][3], int depth, bool isMaximizing) {
  string result = checkWinner(board);
  if(result!="null"){
      if(result=="o") return 10;
      else if(result=="x") return -10;
      else return 0;
  }
 
 
  if (isMaximizing) {
    int bestScore = -1000;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        // Is the spot available?
        if (board[i][j] == '_') {
          board[i][j] = opponent;
          int score = minimax(board, depth + 1, false);
          board[i][j] = '_';
          bestScore = max(score, bestScore);
        }
      }
    }
    return bestScore;
  } else {
    int bestScore = 1000;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (board[i][j] == '_') {
          board[i][j] = player;
          int score = minimax(board, depth + 1, true);
          board[i][j] = '_';
          bestScore = min(score, bestScore);
        }
      }
    }
    return bestScore;
  }
}
 
 
// This will return the best possible move for the player

Move findBestMove(char board[3][3])
{
    int bestVal = -1000;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;
 
    // Traverse all cells, evaluate minimax function for
    // all empty cells. And return the cell with optimal
    // value.
    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            // Check if cell is empty
            if (board[i][j]=='_')
            {
                // Make the move
                board[i][j] = opponent;

                int moveVal = minimax(board, 0, false);
 
                // Undo the move
                board[i][j] = '_';
 
                // If the value of the current move is more than the best value, then update best
                if (moveVal > bestVal)
                {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
 
    return bestMove;
}
 
 
class Game {
private:
    char board[9];
    int emptyIndex[9];
    int gameOn, againstComputer;
    int emptyCount;
    WinList winlist[8];
 
    void displayBoard(){
        cout <<endl;
        cout << "   |   |   "<<endl;
        cout << " "<< board[0] <<" | "<<board[1]<<" | "<<board[2]<<endl;
        cout << "   |   |   "<<endl;
        cout << "-----------"<<endl;
        cout << "   |   |   "<<endl;
        cout << " "<< board[3] <<" | "<<board[4]<<" | "<<board[5]<<endl;
        cout << "   |   |   "<<endl;
        cout << "-----------"<<endl;
        cout << "   |   |   "<<endl;
        cout << " "<< board[6] <<" | "<<board[7]<<" | "<<board[8]<<endl;
        cout << "   |   |   "<<endl;
        cout <<endl;
    }
 
    void computerInput(){
 
 
        if(emptyCount < 0)
            return;
        emptyCount-=1;
 
 
        char board2[3][3] =
        {
            { '_', '_', '_' },
            { '_', '_', '_' },
            { '_', '_', '_' }
        };
 
        for(int i=0;i<9;++i){
 
            int c = i%3, r = i/3;
 
            if(board[i]=='X'){
                board2[r][c]='x';
            }else if(board[i]=='O'){
                board2[r][c]='o';
            }
        }
 
 
        Move bestMove = findBestMove(board2);
        int idx = bestMove.row * 3 + bestMove.col;
        cout<< "Computer choose: " << idx+1 << endl;
        board[idx]='O'; 
    }
 
    void playerInput(Player &player){
        int pos;
        cout << endl;
        cout << "\t" << player.getName() <<" Turn: ";
        cout <<"\t Enter the position " << endl;
        cin >> pos;
        pos -=1;
        if(emptyIndex[pos] == 1){
            cout << "-----Position not empty-------"<< endl;
            playerInput(player);
        } else {
            emptyIndex[pos] =1;
            emptyCount-=1;
            player.getName().compare("Player I") == 0 ? board[pos] ='X': board[pos] ='O';
        }
 
    }
 
    void checkWin(Player &p1,Player &p2){
        int i,j,k;
        bool flag = false;
        char first_symbol;
        for(i=0; i<8; i++){
            first_symbol = board[winlist[i].row[0]];
 
            if((first_symbol != 'X') && (first_symbol != 'O')){
                flag = false;
                continue;
            }
            flag = true;
            for(j=0;j<3;j++){
                if(first_symbol != board[winlist[i].row[j]]){
                    flag = false;
                    break;
                }
            }
            if(flag){
                gameOn = 0;
                if(first_symbol == 'X'){
                    cout << "-----------------------"<< endl;
                    cout << "\t Player I WON"<< endl;
                    cout << "-----------------------"<< endl;
                    p1.won();
                } else {
                    p2.won();
                    if(againstComputer){
                        cout << "-----------------------"<< endl;
                        cout << "\t Computer WON"<< endl;
                        cout << "-----------------------"<< endl;
                    } else {
                        cout << "-----------------------"<< endl;
                        cout << "\t Player II WON"<< endl;
                        cout << "-----------------------"<< endl;
 
                    }
                }
                displayScore(p1,p2);
                break;
            }
        }
    }
 
        void play(Player &p1,Player &p2){
            char rematch ='\0';
            int hand = 0;
            gameOn =1;
            displayBoard();
            while((emptyCount > 0) && (gameOn != 0)){
 
                if(againstComputer)
                    hand == 1 ? computerInput(): playerInput(p2);
                else
                    hand == 1 ? playerInput(p1): playerInput(p2);
                hand= !hand;
                displayBoard();
                checkWin(p1,p2);
            }
            if (emptyCount <=0){
                cout << "      -----------------------"<< endl;
                cout << "\t No WINNER"<< endl;
                cout << "      -----------------------"<< endl;
            }
            cout<< endl;
            cout << "Rematch Y/N: ";
            cin >> rematch;
            if((rematch == 'Y')||(rematch == 'y')){
                init();
                play(p1,p2);
            }
 
        }
    void displayScore(Player &p1, Player &p2){
        cout << endl;
        cout << "\t SCORE: \t";
        if(againstComputer)
            cout<<" Player I: " <<p1.getScore()<<" \t Computer: "<<p2.getScore()<< endl;
        else
            cout<<" Player I: " <<p1.getScore()<<" \t Player II: "<<p2.getScore()<< endl;
    }
 
public:
    Game(): emptyCount{0}, gameOn{1}, againstComputer{0}{
        init();
        winlist[0].row = new int[3]{0,1,2};
        winlist[1].row = new int[3]{3,4,5};
        winlist[2].row = new int[3]{6,7,8};
        winlist[3].row = new int[3]{0,3,6};
        winlist[4].row = new int[3]{1,4,7};
        winlist[5].row = new int[3]{2,5,8};
        winlist[6].row = new int[3]{0,4,8};
        winlist[7].row = new int[3]{2,4,6};
    }
 
    void init(){
        gameOn = 1;
 
        emptyCount =0;
        srand(time(0));
        for(size_t i=0; i<10; i++){
            emptyIndex[i] = 0;
            board[i] = (i+1) +'0';
            emptyCount++;
        }
        emptyCount--;
    }
 
    void onePlayerGame(){
        //Creating Player
        Player p("Player I");
        Player c("Computer");
        cout << "       -----------------------"<< endl;
        cout << "\t Player I: X \t Computer: O"<< endl;
        cout << "       -----------------------"<< endl;
        cout << endl;
        againstComputer = 1;
        play(c,p);
 
    }
 
    void twoPlayerGame(){
        //Creating Player
        Player p("Player I");
        Player c("Player II");
        cout << "       -----------------------"<< endl;
        cout << "\t Player I: X \t Player II: O"<< endl;
        cout << "       -----------------------"<< endl;
        cout << endl;
        againstComputer = 0;
        play(c,p);
    }
};
 
int main()
{
 
 
 
    int ch;
 
    while(1){
        cout<< "      ----------MENU----------" << endl;
        cout << "\t 1. 1 Player game" <<endl;
        cout << "\t 2. 2 Player game" <<endl;
        cout << "\t 3. To exit " <<endl;
        cout <<"      ------------------------" << endl;
        cout << endl;
        cout <<"\t Select an option" << endl;
        cin >> ch;
        switch(ch){
        case 1:{
            Game *game = new Game;
            game->init();
            game->onePlayerGame();
            }
            break;
        case 2:{
            Game *game = new Game;
            game->init();
            game->twoPlayerGame();
            }
            break;
        case 3:
            return 0;
        default:
            cout << "Invalid Choice! TRY AGAIN";
        }
 
    }
    return 0;
}
