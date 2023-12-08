#ifndef CANDYLAND_H
#define CANDYLAND_H

#include <iostream>
#include "Candy.h"
#include "Riddle.h"
#include "Character.h"
#include "CandyStore.h"
#include "Tile.h" 
#include "Board.h"
#include "Player.h"

using namespace std; 

class CandyLand
{
   public: 
   CandyLand();

   void setCharacterMenu(string); //character_file_name
   void displayCharacters();
   void setCandyMenu(string); //candy_file_name
   void displayCandies();

   void setRiddleMenu(string);

   Character findCharacter(string);
   void displayStats(Player);
   Candy findMenuCandy(string);
   bool removeMenuCandy(string);

   Board isShortcutTile(int, Board, int);
   Board isIceCreamShopTile(int, Board, Player[2]); 
   Board isGumdropForestTile(int, Board, Player[2], int);
   Board isGingerbreadHouseTile(int, Board, Player[2], int); 

   void isStaminaRefill(int, Player[2]);
   void isGoldWindfall(int, Player[2]);
   void isRobbersRepel(int, Player[2]);
   void isCandyAquistition(int, Player[2]);

   void isCandyBandits(int, Player[]);
   bool isLostLabyrinth(int, Player[]); //use this bool (stuck) to skip a turn in candyland playGame
   bool isCandyAvalanche(int, Player[]);
   bool isStickyTaffyTrap(int, Player[]); //use this bool to skip a turn in candyland playGame

   void solvePuzzle(int, Player[2]);

   void startGame(Player[2]);
   void playGame(Board, Player[2]); 

   private:
   int static const _MAX_CHARACTERS_MENU = 4;
   int static const _MAX_CANDY_MENU = 9;
   int static const _MAX_RIDDLE_MENU = 3;
   Character _character_menu[_MAX_CHARACTERS_MENU]; 
   int _cur_characters_menu = 0;
   Candy _candy_menu[_MAX_CANDY_MENU];
   int _cur_candy_menu = 0;
   Riddle _riddle_menu[_MAX_RIDDLE_MENU];
   int _cur_riddle_menu = 0;
};
#endif