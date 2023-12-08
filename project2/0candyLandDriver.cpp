// CSCI 1300 Fall 2023
// Author: Brooke Seifert
// TA: AC
// Project 2
#include "Board.h"
#include "Tile.h"
#include "Player.h"
#include "CandyStore.h"
#include "CandyLand.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cassert>

using namespace std;

int main()
{
    srand(time(0));
    
    CandyLand game; 
    Board board;
    Player p1;
    Player p2;
    Player players[2] = {p1, p2};
    game.startGame(players); //loads all candies, characters, and sets players - first candy store visit 
    game.playGame(board, players); //game play with turns and ending 
    
    return 0;
}




