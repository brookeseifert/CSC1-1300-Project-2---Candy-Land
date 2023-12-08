#ifndef CANDYSTORE_H
#define CANDYSTORE_H

#include <iostream>

#include "Candy.h"
#include "Player.h"
//#include "CandyLand.h"

using namespace std; 

class CandyStore
{
   public: 

   CandyStore();
   CandyStore(string);

   void setStoreName(string);
   string getStoreName();

   void setStorePosition(int);
   int getStorePosition();

   int getStoreCandyCount();

   bool addCandy(Candy); 
   bool removeCandy(string);
   Candy findCandy(string);
   Candy findCandyType(string);
   void displayCandies();
   void setCandyMenu(Candy[]);
   string visitCandyStore(int, Player[], Candy[]);


   private:
   string _store_name;
   const static int _MAX_CANDIES = 3; 
   const static int _MAX_ALL_CANDIES = 9;
   Candy _store_menu[_MAX_CANDIES]; 
   int _store_candy_count = 0;
   int _store_position;
   
};
#endif

/*

*/