#include <iostream>
#include <sstream>
#include <fstream>
#include "Candy.h" 
//#include "Player.h"
#include "CandyStore.h"

using namespace std;

int randomNum(int min, int max)
{
   return (rand() % (max - min + 1) + min);
}
string lowerCase(string word)
{
   string temp_word = "";
   for(int i = 0; i < word.length(); i++)
   {
      word[i] = tolower(word[i]);
   }
   return word;
}
CandyStore::CandyStore()
{
   _store_name = "";
   
}
CandyStore::CandyStore(string store_name)
{
   _store_name = store_name; 
}

void CandyStore::setStoreName(string store_name)
{
   _store_name = store_name; 
}
string CandyStore::getStoreName()
{
   return _store_name;
}

void CandyStore::setStorePosition(int store_position)
{
   _store_position = store_position;
}
int CandyStore::getStorePosition()
{
   return _store_position; 
}

int CandyStore::getStoreCandyCount()
{
   return _store_candy_count;
}

bool CandyStore::addCandy(Candy candy)
{
   if(_store_candy_count == _MAX_CANDIES)
   {
      cout << "Store has max candies. Unable to add more" << endl; 
      return false;
   }
   _store_menu[_store_candy_count] = candy;
   _store_candy_count++;
   return true;
}
bool CandyStore::removeCandy(string candy_name)
{
   bool removed = false; 
   string temp_candy_name;
   Candy empty_candy = {"", "", "", 0, "", 0};

   if(_store_candy_count >= 0) // there is something to remove 
   {
   
      for(int i = 0; i < _store_candy_count; i++)
      {
         if(lowerCase(_store_menu[i].name) == lowerCase(candy_name)) //need to be using my toLower funciton 
         {
            for(int j = i; j < _store_candy_count - 1; j++) //max candy 
            {
               _store_menu[j] = _store_menu[j+1];
            }
            _store_menu[_store_candy_count - 1].name = "";
            _store_candy_count--;
            removed = true; 
            break;
         }
      }
      return removed;
   }
   else
   {
      return removed;
   }
   return removed;
}

Candy CandyStore::findCandy(string candy_name)
{
   bool found = false; 
   string temp_candy_name;
   Candy found_candy;
   Candy empty_candy = {"", "", "", 0, "", 0};
   for(int i = 0; i < _store_candy_count; i++)
   {
      if(lowerCase(_store_menu[i].name) == lowerCase(candy_name)) 
      {
         found = true;
         found_candy = _store_menu[i];
         break; 
      }
   }
   if(found == false)
   {
      found_candy = empty_candy; 
   }
   return found_candy;
}
Candy CandyStore::findCandyType(string candy_type)
{
   bool found = false; 
   string temp_candy_name;
   Candy found_candy;
   Candy empty_candy = {"", "", "", 0, "", 0};
   for(int i = 0; i < _store_candy_count; i++)
   {
      if(lowerCase(_store_menu[i].candy_type) == lowerCase(candy_type)) 
      {
         found = true;
         found_candy = _store_menu[i];
         break; 
      }
   }
   if(found == false)
   {
      found_candy = empty_candy; 
   }
   return found_candy;
}
//assigns 3 candys to a candy store object that are differing names and types 
void CandyStore::setCandyMenu(Candy candy_menu[9]) //takes in _candy_menu from CandyLand class
{
   int i = 0;
   while(i < 3)
   {
      int rand_candy1 = randomNum(0,8); //indexed 
      Candy rand_candy = candy_menu[rand_candy1];
      if(rand_candy.name != findCandy(rand_candy.name).name && rand_candy.candy_type != findCandyType(rand_candy.candy_type).candy_type)
      {
         addCandy(candy_menu[rand_candy1]);
         i++;
      }
   }
}

void CandyStore::displayCandies()
{
   int index = 0;
   if(_store_candy_count == 0)
   {
      cout << "No candies are present in candy store." << endl;
      return;
   }
   for(int j = 0; j < 3; j++)
   {
      cout << "|[";
      if(_store_menu[index].name == "") 
      {
         cout << "Empty"; 
      }
      else
      {
         cout << _store_menu[index].name; 
      }
         cout << "]|"; //////
         index++;
   }
   cout << endl;
}
string CandyStore::visitCandyStore(int player_num, Player players[2], Candy candy_menu[9]) //take in the menu of candys from candyland 
{
   string yorn;
   string purchase;
   string remove_candy;
   string candy_choice;
   
   cout << "Here are your options: " << endl;
   displayCandies();
   cout << "Would you like to purchase a candy? y/n" << endl; 
   getline(cin, purchase);
   while(lowerCase(purchase) != "y" && lowerCase(purchase) != "n")
   {
      cout << "Invalid input!" << endl;
      getline(cin, purchase);
   }
   if(lowerCase(purchase) == "y")
   {
      cout << "What candy would you like to purchase: " << endl; 
      getline(cin, candy_choice);
      while(lowerCase(findCandy(candy_choice).name) != lowerCase(candy_choice))
      {
         cout << "Invalid input!" << endl;
         getline(cin, candy_choice);
      }
      
      if(players[player_num].getCandyAmount() == 9)
      {
         cout << "A you willing to give up a candy to purchase this one? y/n" << endl;
         getline(cin, yorn);
         while(lowerCase(yorn) != "y" && lowerCase(yorn) != "n")
         {
            cout << "Invalid input!" << endl;
            getline(cin, yorn);
         }
         if(lowerCase(yorn) == "y")
         {
            cout << "What candy do you relinquish?" << endl;
            players[player_num].printInventory();
            getline(cin, remove_candy);
            while(lowerCase(players[player_num].findCandy(remove_candy).name) != lowerCase(remove_candy))
            {
               cout << "Invalid input!" << endl;
               getline(cin, remove_candy);
            }
            players[player_num].removeCandy(remove_candy); //take away players candy

            int price = findCandy(candy_choice).price;
            if(players[player_num].getGold() - price < 0)
            {
               price = players[player_num].getGold();
            }
            players[player_num].setGold(players[player_num].getGold() - price); //adjust players gold

            players[player_num].addCandy(findCandy(candy_choice)); //add the choice to the palyers inventory 
            cout << "Your new inventory is: " << endl;
            players[player_num].printInventory();
         }
         else 
         {
            cout << "No candy for you then." << endl; 
         }
      }
      else 
      {
         players[player_num].setGold(players[player_num].getGold() - findCandy(candy_choice).price);
         players[player_num].addCandy(findCandy(candy_choice));
         cout << "Your new inventory is: " << endl;         
         players[player_num].printInventory();
      }
   }
   else 
   {
      cout << "Alright then, carry on." << endl;
      remove_candy = "";
   }
   return remove_candy;
}
