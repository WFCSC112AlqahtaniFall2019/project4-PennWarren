/* Class: TicTacToe
 * Author: Benjamin Raiford
 * Date: October 4, 2019
 * Description: A program that implements the game Tic-Tac-Toe
 */
#include <iostream>
#include <ctime>
#include <vector>
#include "TicTacToe.h"
using namespace std;

//For 1 person games, figure out whether the computer or player goes first
bool randomPlayer();

//Find number of players
int findGameType();

//Place mark for player
void placePlayerMark(TicTacToe& g);

//Place mark for computer
void placeComputerMark(TicTacToe& g);

int main() {
    TicTacToe game;
    srand(time(nullptr));

    //Play until this is false
    bool continueGame = true;

    //Find number of players
    int numPlayers = findGameType();

    //Print the initial board
    game.printBoard();

    //One Player Game
    if (numPlayers == 1){
        if(randomPlayer()){
            game.changePlayer();
        }
        while(continueGame){
            //Player's Turn
            if(game.getCurrentPlayerNumber() == 1){
                placePlayerMark(game);
            }
            //Computer's Turn
            else {
                placeComputerMark(game);
            }
            //Check for win
            if(game.checkForWin()){
                cout << "Player " << game.getCurrentPlayerNumber() << " wins!" << endl;
                continueGame = false;
            }
            //Check for draw
            if(game.isBoardFull()){
                cout << "The board is full... players draw." << endl;
                continueGame = false;
            }
            //Change player
            game.changePlayer();
        }
    }

    //Two Player Game
    else if(numPlayers == 2){
        while(continueGame){
            //Place mark
            placePlayerMark(game);

            //Check for win
            if(game.checkForWin()){
                cout << "Player " << game.getCurrentPlayerNumber() << " wins!" << endl;
                continueGame = false;
            }
            //Check for draw
            if(game.isBoardFull()){
                cout << "The board is full... players draw." << endl;
                continueGame = false;
            }
            //Change player
            game.changePlayer();
        }
    }

    return 0;
}

bool randomPlayer(){
    //50/50 chance
    return rand() % 2 == 0;
}
int findGameType(){
    int numP = 0;
    while (numP < 1 || numP > 2) {
        cout << "Would you like to play with one player or two players? Enter either 1 or 2: " << endl;
        cin >> numP;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');//clear input to prevent runtime errors
        //only accept 1 or 2 as input
        if(numP < 1 || numP > 2) {
            cout << "Please enter a valid number of players" << endl;
        }
    }
    return numP;
}
void placePlayerMark(TicTacToe& g){
    int r,c;
    bool loopAgain;//set to true while placeMark returns false
    do{
        loopAgain = false;
        cout << "Enter row and column using 1-3" << endl;
        cin >> r >> c;//input coordinates in a user-friendly way
        cin.ignore(numeric_limits<streamsize>::max(),'\n');//clear input to prevent runtime errors
        r--, c--;//make user input work with the bounds 0-2
        //only accept valid input
        if(!g.placeMark(r,c)) {
            cout << "Please enter a valid position\n" << endl;
            loopAgain = true;
        }
    }while(loopAgain);
    g.printBoard();
}
void placeComputerMark(TicTacToe& g){
    int r,c;
    bool loopAgain;
    do{
        loopAgain = false;
        r = rand() % 3;//computer row
        c = rand() % 3;//computer column
        //only accept valid input
        if(!g.placeMark(r,c)){
            loopAgain = true;
        }
    }while(loopAgain);
    cout << "Computer chooses Row: " << r+1 << " Column: " << c+1 << endl;
    g.printBoard();
}
