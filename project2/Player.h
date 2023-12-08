#ifndef PLAYER_H
#define PLAYER_H

#include <iostream> 
#include "Candy.h"
//#include "CandyLand.h"

using namespace std;

class Player
{
   public:

   Player(); //deafault constructor 
   Player(string, int, double, Candy[], const int); //parametetized constructor

   int getCandyAmount() const; 
   
   void setName(string);
   string getName();

   void setCharName(string);
   string getCharName();
   
   void setStamina(int);
   int getStamina();
   
   void setGold(double);
   double getGold();

   string getInventory();

   void printInventory();
   Candy findCandy(string);
   bool addCandy(Candy);
   bool removeCandy(string);
   int drawCard(int);

   string playRockPaperScissors();

   private:
   const static int _MAX_CANDY_AMOUNT = 9;
   string _name;
   string _char_name;
   int _stamina;
   double _gold;
   Candy _inventory[_MAX_CANDY_AMOUNT];
   int _candy_amount; 

};

#endif