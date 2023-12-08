#include <iostream>
#include <cmath>
#include <string>

#include "Candy.h"
#include "Card.h"
#include "Player.h"

using namespace std;
string toLOWER(string word)
{
   string temp_word = "";
   for(int i = 0; i < word.length(); i++)
   {
      word[i] = tolower(word[i]);
   }
   return word;
}
int random(int min, int max)
{
   return (rand() % (max - min + 1) + min);
}
Player::Player()
{
   Candy empty_candy = {"", "", "", 0, "", 0};
   
   _stamina = 0;
   _gold = 0;
   _candy_amount = 0; //amount of initiliazed candy structs in the inventory array
   for(int i = 0; i < _MAX_CANDY_AMOUNT; i++)
   {
      _inventory[i] = empty_candy;
   }

}
//parameterized constructor 
Player::Player(string name, int stamina, double gold, Candy candy_array[], const int CANDY_ARRAY_SIZE)
{
   Candy empty_candy = {"", "", "", 0, "", 0};

   _stamina = stamina; 
   _gold = gold;
   _candy_amount = 0;

   for(int i = 0; i < _MAX_CANDY_AMOUNT; i++)
   {
      _inventory[i] = empty_candy;
   }

   if(CANDY_ARRAY_SIZE > _MAX_CANDY_AMOUNT)
   {
      for(int i = 0; i < _MAX_CANDY_AMOUNT; i++)
      {
         _inventory[i] = candy_array[i];
         if(candy_array[i].name != empty_candy.name) //only increment if it is not empty
         {
            _candy_amount++;
         }
      }
   }  
   else 
   {
      for(int i = 0; i < CANDY_ARRAY_SIZE; i++) 
      {
         _inventory[i] = candy_array[i];
         if(candy_array[i].name != empty_candy.name)
         {
            _candy_amount++;
         }
      }
   }
}
int Player::getCandyAmount() const
{
   return _candy_amount;
}
void Player::setName(string name)
{
   _name = name;
}
string Player::getName()
{
   return _name;
}
void Player::setCharName(string char_name)
{
   _char_name = char_name;
}
string Player::getCharName()
{
   return _char_name;
} 
void Player::setStamina(int stamina)
{
   _stamina = stamina;
}
int Player::getStamina()
{
   return _stamina;
}
void Player::setGold(double gold)
{
   _gold = gold;
}
double Player::getGold()
{
   return _gold;
}   
//used in the result.txt
string Player::getInventory()
{
   string temp;
   for(int i = 0; i < _candy_amount; i++)
   {
      if(i == _candy_amount - 1)
      {
         temp += _inventory[i].name;
      }
      else
      {
         temp += _inventory[i].name + " ";
      }
   }
   return temp;
}

void Player::printInventory()
{
   Candy empty_candy = {"", "", "", 0, "", 0};
   int index = 0;
   for(int i = 0; i < 3; i++)
   { 
      for(int j = 0; j < 3; j++)
      {
         cout << "|[";
         if(_inventory[index].name == empty_candy.name) 
         {
            cout << "Empty"; 
         }
         else
         {
            cout << _inventory[index].name; 
         }
         cout << "]";
         index++;
      }
         cout << "]|" << endl;
   }

}

Candy Player::findCandy(string candy_name)
{
   bool found = false; 
   string temp_candy_name;
   Candy found_candy;
   Candy empty_candy = {"", "", "", 0, "", 0};
   for(int i = 0; i < _candy_amount; i++)
   {
      if(toLOWER(_inventory[i].name) == toLOWER(candy_name)) 
      {
         found = true;
         found_candy = _inventory[i];
         break; 
      }
   }
   if(found == false)
   {
      found_candy = empty_candy; 
   }
   return found_candy;
}

bool Player::addCandy(Candy candy)
{
   bool added = false;
   if(_candy_amount <= _MAX_CANDY_AMOUNT)
   {
      for(int i = 0; i < _MAX_CANDY_AMOUNT; i++)
      {
         if(_inventory[i].name == "")
         {
            _inventory[i] = candy;
            added = true;
            _candy_amount++;
            break;
         }
      }
   }
   else //inventory is full 
   {
      return added;
   }
   return added;
}

bool Player::removeCandy(string candy_name)
{
   bool removed = false; 
   string temp_candy_name;
   Candy empty_candy = {"", "", "", 0, "", 0};

   if(_candy_amount >= 0) // there is something to remove 
   {
   
      for(int i = 0; i < _candy_amount; i++)
      {
         if(toLOWER(_inventory[i].name) == toLOWER(candy_name)) 
         {
            for(int j = i; j < _candy_amount - 1; j++) //max candy 
            {
               _inventory[j] = _inventory[j+1];
            }
            _inventory[_candy_amount - 1].name = "";
            _candy_amount--;
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
//draws card fro player and returns the appropriate change they will use in move player 
int Player::drawCard(int cur_position)
{
   int rand_card = random(1, 9);
   Card cur_card; 
   Card new_card;
   int change = 0;
  

   if (rand_card == 1 || rand_card == 2) //magenta 
   {
      cur_card.color = "Mulberry Magenta";
      new_card.color = "Mulberry Magenta";
      cur_card.color_num = 0;
      cur_card.is_double = false;
   }
   else if (rand_card == 3 || rand_card == 4) //green
   {
      cur_card.color = "Minty Green";
      new_card.color = "Minty Green";
      cur_card.color_num = 1;
      cur_card.is_double = false;
   }
   else if (rand_card == 5 || rand_card == 6) //blue
   {
      cur_card.color = "Bubblegum Blue";
      new_card.color = "Bubblegum Blue";
      cur_card.color_num = 2;
      cur_card.is_double = false;
   }
   else if(rand_card == 7) //double magenta
   {
      cur_card.color = "Double Mulberry Magenta";
      new_card.color = "Mulberry Magenta";
      cur_card.color_num = 0;
      cur_card.is_double = true;
   }
   else if(rand_card == 8) //double green
   {
      cur_card.color = "Double Minty Green";
      new_card.color = "Minty Green";
      cur_card.color_num = 1;
      cur_card.is_double = true;
   }
   else if(rand_card == 9) //double blue
   {
      cur_card.color = "Double Bubblegum Blue";
      new_card.color = "Bubblegum Blue";
      cur_card.color_num = 2;
      cur_card.is_double = true;
   }
   
   if(cur_position % 3 == 0) //magenta 
   {
      if(cur_card.color_num == 0)
      {
         change = 3; 
      }
      else if(cur_card.color_num == 1)
      {
         change = 1;
      }
      else if(cur_card.color_num == 2)
      {
         change = 2;
      }
      if(cur_card.is_double == true)
      {
         change += 3;
         
      }
   }
   if(cur_position % 3 == 1) //green 
   {
      if(cur_card.color_num == 1)
      {
         change = 3; 
      }
      else if(cur_card.color_num == 2)
      {
         change = 1;
      }
      else if(cur_card.color_num == 0)
      {
         change = 2;
      }
      if(cur_card.is_double == true)
      {
         change += 3;
      }
   }
   if(cur_position % 3 == 2) //blue 
   {
      if(cur_card.color_num == 2)
      {
         change = 3; 
      }
      else if(cur_card.color_num == 0)
      {
         change = 1;
      }
      else if(cur_card.color_num == 1)
      {
         change = 2;
      }
      if(cur_card.is_double == true)
      {
         change += 3;
      }
   }

   if(cur_position + change >= 82)
   { 

      change = 82 - cur_position;
      new_card.color = "Castle";
   }
   cout << "You drew a " << cur_card.color << " card. Your card advances to " << new_card.color << " tile." << endl;
   return change;
}

string Player::playRockPaperScissors()
{
   string result = "lose";
   string choice1;
   string computer_choice;
   bool tie = false;
   
   do
   {
      int rand_choice = random(1,3);
      if(rand_choice == 1)
      {
         computer_choice = "r";
      }
      else if(rand_choice == 2)
      {
         computer_choice = "p";
      }
      if(rand_choice == 3)
      {
         computer_choice = "s";
      }
      
      cout << "Player 1: Enter r, p, or s" << endl; 
      getline(cin, choice1);
      while(choice1 != "r" && choice1 != "p" && choice1 != "s")
      {
         cout << "Invalid input!" << endl; 
         getline(cin, choice1);
      }

      cout << "The computer selected: " << computer_choice << endl; 
      if(choice1 == computer_choice)
      {
         tie = true;
         cout << "Tie! Play again" << endl;
      }
      else if((choice1 == "r" && computer_choice == "s") || (choice1 == "s" && computer_choice == "p") || (choice1 == "p" && computer_choice == "r"))
      {
         cout << "You have won "<< endl;
         tie = false;
         result = "won";
      }
      else if((choice1 == "r" && computer_choice == "p") || (choice1 == "s" && computer_choice == "r") || (choice1 == "p" && computer_choice == "s"))
      {
         cout << "You have lost " << endl;
         tie = false;
         result = "lost";
      }
   } while (tie == true);
   return result; 
}

