#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cctype>

#include "Tile.h"
#include "Riddle.h"
#include "Candy.h"
#include "Character.h"
#include "Board.h"
#include "CandyStore.h"
#include "Player.h"
#include "CandyLand.h"

using namespace std;
string toLow(string word)
{
   string temp_word = "";
   for(int i = 0; i < word.length(); i++)
   {
      word[i] = tolower(word[i]);
   }
   return word;
}
int randGenerator(int min, int max)
{
   return (rand() % (max - min + 1) + min);
}

CandyLand::CandyLand()
{
   Character empty_character = {"", 0, 0};
   Candy empty_candy = {"", "", "", 0, "", 0};
   for(int i = 0; i < 9; i++)
   {
      empty_character.inventory[i] = empty_candy; 
   }
   for(int i = 0; i < _MAX_CHARACTERS_MENU - 1; i++) //- 1?
   {
      _character_menu[i] = empty_character;
      _cur_characters_menu++;
   }
}
void CandyLand::setCharacterMenu(string character_file)
{
   string line, name, stamina, gold, candies;
   Candy temp_candy;
   Candy temp_candy_menu[9];
   Character temp_character;
   ifstream file_in;
   _cur_characters_menu = 0;
   file_in.open(character_file);

   int i = 0; 
   string temp; //processing header
   getline(file_in, temp); 
   while(!file_in.eof())
   {
      getline(file_in, line);
      stringstream ss(line);
      if(line == "")
      {
         continue;
      }
      getline(ss, name, '|');
      getline(ss, stamina, '|');
      getline(ss, gold, '|');
      temp_character.name = name;
      temp_character.stamina = stoi(stamina); 
      temp_character.gold = stod(gold);
      int j = 0;
      while(getline(ss, candies, ','))
      {
         temp_candy = findMenuCandy(candies);
         temp_character.inventory[j] = temp_candy;
         j++;
      }
      _character_menu[i] = temp_character;
      _cur_characters_menu++;
      i++;
      //return flag;
   }
   file_in.close();
}

void CandyLand::displayCharacters()
{
   for(int x = 0; x < _cur_characters_menu; x++)
   {
      cout << "Name: " << _character_menu[x].name << endl; 
      cout << "Stamina: " << _character_menu[x].stamina << endl; 
      cout << "Gold: " << _character_menu[x].gold << endl; 
      cout << "Candies: " << endl; 
      int index = 0;
      for(int i = 0; i < 3; i++)
      { 
         for(int j = 0; j < 3; j++)
         {
            cout << "|[";
            if(_character_menu[x].inventory[index].name == "") 
            {
               cout << "Empty"; 
            }
            else
            {
               cout << _character_menu[x].inventory[index].name; 
            }
            cout << "]";
            index++;
         }
         cout << "]|" << endl;
      }
      cout << "---------------------------------------------------------" << endl;
   }
}

void CandyLand::setCandyMenu(string candy_file)
{
   string line, name, description, effect_type, effect_value, candy_type, price;
   Candy temp_candy;

   ifstream file_in;
   file_in.open(candy_file);
   string temp; 
   getline(file_in, temp);
   int i = 0;
   while(!file_in.eof())
   {
      getline(file_in, line);
      stringstream ss(line);
      if(line == "")
      {
         continue;
      }
      getline(ss, name, '|');
      getline(ss, description, '|');
      getline(ss, effect_type, '|');
      getline(ss, effect_value, '|');
      getline(ss, candy_type, '|');
      getline(ss, price, '|');
            
      temp_candy.name = name;
      temp_candy.description = description;
      temp_candy.effect_type = effect_type;
      //cout << effect_value << endl;
      temp_candy.effect_value = stoi(effect_value);
      temp_candy.candy_type = candy_type;
      temp_candy.price = stod(price);

      _candy_menu[i] = temp_candy;
      _cur_candy_menu++;
      i++;
   }
   file_in.close();
}
void CandyLand::displayCandies()
{
   cout << "Candies: " << endl; 
      int index = 0;
      for(int i = 0; i < 3; i++)
      { 
         for(int j = 0; j < 3; j++)
         {
            cout << "|[";
            if(_candy_menu[index].name == "") 
            {
               cout << "Empty"; 
            }
            else
            {
               cout << _candy_menu[index].name; 
            }
            cout << "]";
            index++;
         }
         cout << "]|" << endl;
      }
}
void CandyLand::setRiddleMenu(string riddle_file)
{
   string line, question, answer;
   Riddle temp_riddle;
   
   ifstream file_in;

   file_in.open(riddle_file);
   int i = 0; 
   while(!file_in.eof())
   {
      getline(file_in, line);
      stringstream ss(line);
      if(line == "")
      {
         continue;
      }
      getline(ss, question, '|');
      getline(ss, answer, '|');
      temp_riddle.question = question;
      temp_riddle.answer = answer; 
      
      _riddle_menu[i] = temp_riddle;
      _cur_riddle_menu++;
      i++;
      //return flag;
   }
   file_in.close();
}

void CandyLand::displayStats(Player player)
{
   cout << "Player name: " << player.getName() << endl;
   cout << "Character name: " << player.getCharName() << endl; 
   cout << "Stamina: " << player.getStamina() << endl; 
   cout << "Gold: " << player.getGold() << endl; 
   player.printInventory();
}
Character CandyLand::findCharacter(string character_name)
{
   bool found = false; 
   string temp_character_name;
   Character found_character;
   Character empty_character;
   for(int i = 0; i < _cur_characters_menu; i++)
   {
      if(toLow(_character_menu[i].name) == toLow(character_name)) 
      {
         found = true;
         found_character = _character_menu[i];
         break; 
      }
   }
   if(found == false)
   {
      found_character = empty_character; 
   }
   return found_character;
}
Candy CandyLand::findMenuCandy(string candy_name)
{
   bool found = false; 
   string temp_candy_name;
   Candy found_candy;
   Candy empty_candy = {"", "", "", 0, "", 0};
   for(int i = 0; i < _cur_candy_menu; i++)
   {
      if(toLow(_candy_menu[i].name) == toLow(candy_name)) 
      {
         found = true;
         found_candy = _candy_menu[i];
         break; 
      }
   }
   if(found == false)
   {
      found_candy = empty_candy; 
   }
   return found_candy;
}
bool CandyLand::removeMenuCandy(string candy_name)
{
   bool removed = false; 
   string temp_candy_name;
   Candy empty_candy = {"", "", "", 0, "", 0};

   if(_cur_candy_menu >= 0) // there is something to remove 
   {
      for(int i = 0; i < _cur_candy_menu; i++)
      {
         if(toLow(_candy_menu[i].name) == toLow(candy_name)) //need to be using my toLower funciton 
         {
            for(int j = i; j < _cur_candy_menu - 1; j++) //max candy 
            {
               _candy_menu[j] = _candy_menu[j+1];
            }
            _candy_menu[_cur_candy_menu - 1].name = "";
            _cur_candy_menu--;
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
//moves character ahead 4 spots
Board CandyLand::isShortcutTile(int player_num, Board board, int change)
{
   cout << "Shortcut Tile: Your spirits soar as you're propelled four tiles ahead, closing in on the Candy Castle." << endl;
   if(player_num == 1)
   {
      if((83 - board.getPlayer1Position()) < 4) //not past the end of the board 
      {
         board.setPlayer1Position(83);
      }
      else 
      {
         board.movePlayer(1, 4); //change + 4
      }
   }
   else if(player_num == 2)
   {
      if((83 - board.getPlayer2Position()) < 4)
      {
         board.setPlayer2Position(83);
      }
      else 
      {
         board.movePlayer(2, 4); //change + 4
      }
   }
   return board;
}
//allows the player another draw card, will check special tiles again within function
Board CandyLand::isIceCreamShopTile(int player_num, Board board, Player players[])
{
   cout << "Ice Cream Stop Tile: Congrats! You get a chance to draw a card again." << endl;
   int change1;
   int change2;
   int break1_count = 0;
   int break2_count = 0;
      //player 1 
      if(player_num == 1)
      {
         if(players[0].getStamina() <= 0)
         {
            cout << "Your stamina is too low to move... be patient while it reloads." << endl;
            if(break1_count <= 0)
            {
               break1_count++;
            }
            else 
            {
               players[0].setStamina(20);
            }
         }
         else
         {
            change1 = players[0].drawCard(board.getPlayer1Position());
            board.movePlayer(1, change1);

            if(board.getTile(board.getPlayer1Position()).tile_type == "shortcut tile")
            {
               board = isShortcutTile(1, board, change1);
            }
            else if(board.getTile(board.getPlayer1Position()).tile_type == "ice cream shop tile")
            {
               cout << "You landed on another Ice cream shop tile... Candy Land is stingy with it's cards though. You can't draw again until your next turn." << endl; 
            }
            else if(board.getTile(board.getPlayer1Position()).tile_type == "gumdrop forest tile")
            {
               board = isGumdropForestTile(1, board, players, change1);
               displayStats(players[0]);
            }
            else if(board.getTile(board.getPlayer1Position()).tile_type == "gingerbread house")
            {
               board = isGingerbreadHouseTile(1, board, players, change1);
            }
            // will check treasure candy store and gummy candy after since theyre in seperate else blocks 
         
            players[0].setStamina(players[0].getStamina() -1); //decrease stamina by one unit here as as well since its two moves total
         }
         return board;
      }
      //player 2
      else if(player_num == 2)
      {
         if(players[1].getStamina() <= 0)
         {
            cout << "Your stamina is too low to move... be patient while it reloads." << endl;
            if(break2_count <= 0)
            {
               break2_count++;
            }
            else 
            {
               players[1].setStamina(20);
            }
         }
         else 
         {
            change2 = players[1].drawCard(board.getPlayer2Position());
            board.movePlayer(2, change2);
            if(board.getTile(board.getPlayer2Position()).tile_type == "shortcut tile")
            {
               board = isShortcutTile(2, board, change2);
            }
            else if(board.getTile(board.getPlayer2Position()).tile_type == "ice cream shop tile")
            {
               cout << "You landed on another Ice cream shop tile... Candy Land is stingy with it's card's though. You can't draw again until your next turn." << endl; 
            }
            else if(board.getTile(board.getPlayer2Position()).tile_type == "gumdrop forest tile")
            {
               board = isGumdropForestTile(2, board, players, change2);
               displayStats(players[1]);
            }
            else if(board.getTile(board.getPlayer2Position()).tile_type == "gingerbread house")
            {
               board = isGingerbreadHouseTile(2, board, players, change2);
            }
            players[1].setStamina(players[1].getStamina() -1); //decrease stamina by one unit here as as well since its two move
         }
         return board;
      }
   
   return board;
}
//moves player back by 4 spaces and removes random amount of candy 
Board CandyLand::isGumdropForestTile(int player_num, Board board, Player players[2], int change)
{
   int rand_gold = randGenerator(5,10);
   cout << "Gumdrop Forest Tile: Oops, You head back 4 tiles and lose " << rand_gold << " gold." << endl;
   if(player_num == 1)
   {
      if(players[0].getGold() - rand_gold < 0) //checks if gold will be less than 0 and adjusts 
      {
         rand_gold = players[0].getGold();
      }
      players[0].setGold(players[0].getGold() - rand_gold);
      if(board.getPlayer1Position() < 4) //maybe =
      {
         board.setPlayer1Position(0);
      }
      else 
      {
         board.movePlayer(1, -4); // change - 4
      }
   }
   else if(player_num == 2)
   {
      if(players[1].getGold() - rand_gold < 0)
      {
         rand_gold = players[1].getGold();
      }
      players[1].setGold(players[1].getGold() - rand_gold);
      if(board.getPlayer2Position() < 4)
      {
         board.setPlayer2Position(0); 
      }
      else 
      {
         board.movePlayer(2, -4); //change - 4
      }
   }
   return board;
}
//moves character back to previous change value and removes a immunity candy 
Board CandyLand::isGingerbreadHouseTile(int player_num, Board board, Player players[2], int change)
{
   cout << "Gingerbread House Tile: It's a bittersweet return to your previous location, accompanied by the forfeiture of one immunity candy." << endl;
   if(player_num == 1)
   {
      board.setPlayer1Position(board.getPlayer1Position() - change);
      
      if(players[0].findCandy("Caramel Comet").name == "Caramel Comet") //checks for immunity
      {
         players[0].removeCandy("Caramel Comet");
         cout << "Your updated candy stats are: " << endl;
         players[0].printInventory();
      }
      else if(players[0].findCandy("Bubblegum Blast").name == "Bubblegum Blast") //checks for immunity
      {

         players[0].removeCandy("Bubblegum Blast");
         cout << "Your updated candy stats are: " << endl;
         players[0].printInventory();
      }
      else if(players[0].findCandy("Sparkling Sapphire|").name == "Sparkling Sapphire") //checks for immunity 
      {

         players[0].removeCandy("Sparkling Sapphire|");
         cout << "Your updated candy stats are: " << endl;
         players[0].printInventory();
      }
      else 
      {
         cout << "You have no immunity candy to lose!" << endl;
      }
   }
   else if(player_num == 2)
   {
      board.setPlayer2Position(board.getPlayer2Position() - change);
   
      if(players[1].findCandy("Caramel Comet").name == "Caramel Comet")
      {
         players[1].removeCandy("Caramel Comet");
         cout << "Your updated candy stats are: " << endl;
         players[1].printInventory(); 
      }
      else if(players[1].findCandy("Bubblegum Blast").name == "Bubblegum Blast")
      {
         players[1].removeCandy("Bubblegum Blast");
         cout << "Your updated candy stats are: " << endl;
         players[1].printInventory();
      }
      else if(players[1].findCandy("Sparkling Sapphire|").name == "Sparkling Sapphire")
      {

         players[1].removeCandy("Sparkling Sapphire|");
         cout << "Your updated candy stats are: " << endl;
         players[1].printInventory();
      }
      else 
      {
         cout << "You have no immunity candy to lose!" << endl;
      }
   }
   return board;
}
//increases players stamina by a random value
void CandyLand::isStaminaRefill(int player_num, Player players[2])
{
   cout << "You landed on a Stamina Refill. Enjoy your reward!" << endl;
   int rand_stamina = randGenerator(10, 30);
   int new_stamina = 0;
   if((players[player_num].getStamina() + rand_stamina) > 100) //make sure stamina doesn't pass 100
   {
      new_stamina = 100 - players[player_num].getStamina();
   }
   else 
   {
      new_stamina = rand_stamina + players[player_num].getStamina();
   }
   players[player_num].setStamina(new_stamina);
}
//increases players gold by a random amount 
void CandyLand::isGoldWindfall(int player_num, Player players[2])
{
   cout << "You landed on Gold Windfall. Enjoy your reward!" << endl;
   int rand_gold = randGenerator(20, 40);
   int new_gold = 0;
   if((players[player_num].getGold() + rand_gold) > 100) //make sure gold doesn't pass 100
   {
      new_gold = 100 - players[player_num].getGold();
   }
   else 
   {
      new_gold = rand_gold + players[player_num].getGold();
   }
  players[player_num].setGold(new_gold);
}
//adds robber repel to players inventory if space allows
void CandyLand::isRobbersRepel(int player_num, Player players[2])
{
   cout << "You landed on Robber's Repel." << endl;
   Candy robbers_repel;
   robbers_repel.name = "Robber's Repel"; 
   robbers_repel.description = "This candy acts as an anti-robbery shield, safeguarding the player's gold from potential theft by others during their journey.";
   robbers_repel.effect_type = "other";
   robbers_repel.effect_value = 50;
   robbers_repel.candy_type = "immunity";
   robbers_repel.price = 40;
   if(players[player_num].getCandyAmount() < 9)
   {
      players[player_num].addCandy(robbers_repel);
   }
   else 
   {
      string remove_candy;
      string yorn;
      cout << "Would you like to give up a candy to accept the Robber's Repel? y/n" << endl; 
      getline(cin, yorn);
      while(toLow(yorn) != "y" && toLow(yorn) != "n")
      {
         cout << "Invalid input!" << endl;
         getline(cin, yorn);
      }
      if(toLow(yorn) == "y")
      {
         if(players[player_num].getCandyAmount() == 9) //inventory is full
         {
            cout << "What candy do you relinquish?" << endl;
            players[player_num].printInventory();
            getline(cin, remove_candy);
            while(toLow(players[player_num].findCandy(remove_candy).name) != toLow(remove_candy))
            {
               cout << "Invalid input!" << endl;
               getline(cin, remove_candy);
            }
            players[player_num].removeCandy(remove_candy);
            players[player_num].addCandy(robbers_repel);
            cout << "Your new inventory is: " << endl;
            players[player_num].printInventory();
         }
         else 
         {
            players[player_num].addCandy(robbers_repel);
            cout << "Your new inventory is: " << endl;
            players[player_num].printInventory();
         }

      }
      else 
      {
         cout << "Alright then, carry on." << endl; 
      }
   }
}
//gives player one of two candys if space allows
void CandyLand::isCandyAquistition(int player_num, Player players[2])
{
   cout << "You landed on a Candy Aquisition." << endl;
   Candy aquired_candy; 
   Candy treasure_truffle; 
   treasure_truffle.name = "Treasure Hunter's Truffle";
   treasure_truffle.description = "Allows player to unlock a random hidden treasure";
   treasure_truffle.effect_type = "other";
   treasure_truffle.effect_value = 0;
   treasure_truffle.candy_type = "magical";
   treasure_truffle.price = 20;

   Candy jellybean_vigor; 
   jellybean_vigor.name = "Jellybean of Vigor";
   jellybean_vigor.description = "Increases the stamina by a 50 units";
   jellybean_vigor.effect_type = "stamina";
   jellybean_vigor.effect_value = 50;
   jellybean_vigor.candy_type = "stamina";
   jellybean_vigor.price = 20;

   int rand_candy = randGenerator(1,100);
   if(rand_candy <= 30)// 30 % chance
   {
      cout << "You got Treasure Hunter's Truffle!" << endl;
      aquired_candy = treasure_truffle;
   }
   else if(rand_candy > 30) //70 % chance
   {
      cout << "You got Jelly Bean of Vigor!" << endl; 
      aquired_candy = jellybean_vigor;
   }
   string remove_candy;
   string yorn;
   cout << "Would you like to accept this candy? y/n" << endl; 
   getline(cin, yorn);
   while(toLow(yorn) != "y" && toLow(yorn) != "n")
   {
      cout << "Invalid input!" << endl;
      getline(cin, yorn);
   }
   if(toLow(yorn) == "y")
   {
      if(players[player_num].getCandyAmount() == 9)
      {
         cout << "What candy do you relinquish?" << endl;
         players[player_num].printInventory();
         getline(cin, remove_candy);
         while(toLow(players[player_num].findCandy(remove_candy).name) != toLow(remove_candy))
         {
            cout << "Invalid input!" << endl;
            getline(cin, remove_candy);
         }
         players[player_num].removeCandy(remove_candy);
         players[player_num].addCandy(aquired_candy);
         cout << "Your new inventory is: " << endl;
         players[player_num].printInventory();
      }
      else 
      {
         players[player_num].addCandy(aquired_candy);
         cout << "Your new inventory is: " << endl;
         players[player_num].printInventory();
      }
   }
   else 
   {
      cout << "Alright then, carry on." << endl; 
   }
}
//CALAMITIES
//removes random amount of gold from layer 
void CandyLand::isCandyBandits(int player_num, Player players[])
{
   cout << "Oh no! Candy Bandits gave swiped your gold coins" << endl; 
   int rand_gold = randGenerator(1, 10);
   if(players[player_num].getGold() - rand_gold < 0) //make sure gold doesn't go bellow 0
   {
      rand_gold = players[player_num].getGold();
   }
   players[player_num].setGold(players[player_num].getGold() - rand_gold);
}
//plays rock paper scissors to avoid a skiped turn
bool CandyLand::isLostLabyrinth(int player_num, Player players[])
{
   bool lost = false; 
   string results;
   cout << "Oh dear you got lost in the Lollipop Labyrinth! Play Rock, Paper, Sciccors to find your way back." << endl; 
   results = players[player_num].playRockPaperScissors();
   if(results == "lost")
   {
      lost = true; 
   }
   else 
   {
      lost = false;
   }
   return lost; //checked in main and if lost is true add to skip counter
}
//removes random amount of stamina if the player lost and skips turn 
bool CandyLand::isCandyAvalanche(int player_num, Player players[])
{
   bool lost = false; 
   string results;
   cout << "Watch out! A candy avalanche has struck! You can recover the damage by playing Rock, Paper, Scissors." << endl;
   int rand_stamina = randGenerator(5, 10);
   results = players[player_num].playRockPaperScissors();
   if(results == "lost")
   {
      lost = true; 
      if(players[player_num].getStamina() - rand_stamina < 0) //checks if stamina will go bellow 0
      {
         rand_stamina = players[player_num].getStamina();
      }
      players[player_num].setStamina(players[player_num].getStamina() - rand_stamina);
   }
   else 
   {
      lost = false;
   }
   return lost;
}
//will skip a turn unless the player has special candies
bool CandyLand::isStickyTaffyTrap(int player_num, Player players[])
{
   bool stuck = true;
   cout << "Opps! You are stuck in a sticky taffy trap!" << endl;
   if(players[player_num].findCandy("Breezy Butterscotch").name == "Breezy Butterscotch")
   {
      cout << "You have Breezy Butterscotch it will save you from losing a turn!" << endl;
      players[player_num].removeCandy("Breezy Butterscotch");
      stuck = false;
   }
   else if(players[player_num].findCandy("Frosty Fizz").name == "Frosty Fizz")
   {
      cout << "You have Frosty Fizz it will save you from losing a turn!" << endl;
      players[player_num].removeCandy("Frosty Fizz");
      stuck = false;
   }
   return stuck;
}

void CandyLand::startGame(Player players[2])
{
   string bought_candy1;
   string bought_candy2;
   CandyStore initial_store;
   string num_players;
   string player1_name; 
   string player2_name;
   string character1_choice;
   string character2_choice;
   string character_file = "characters.txt";
   string candy_file = "candy.txt";
   string riddle_file = "riddles.txt";

   setCandyMenu(candy_file);
   setCharacterMenu(character_file);
   setRiddleMenu(riddle_file);

   initial_store.setCandyMenu(_candy_menu);


   cout << "Welcome to the game of Candy Land! Please enter the number of participants: " << endl; 
   getline(cin, num_players);
   while(num_players != "2")
   {
      cout << "Invalid input!(Hint: A pair of friends is more fun!)" << endl;
      getline(cin, num_players);
   }
   cout << "Enter player 1 name: " << endl; 
   cin >> player1_name; 
   cin.clear();
   cin.ignore(1000, '\n');
   players[0].setName(player1_name);

   cout << "Here is a list of characters you can choose from:" << endl; 
   displayCharacters();
   getline(cin, character1_choice);
   while(toLow(findCharacter(character1_choice).name) != toLow(character1_choice))
   {
      cout << "Invalid input!" << endl;
      getline(cin, character1_choice);
   }
   //remove character
   players[0].setCharName(findCharacter(character1_choice).name);
   players[0].setStamina(findCharacter(character1_choice).stamina);
   players[0].setGold(findCharacter(character1_choice).gold);
      for(int i = 0; i < 9; i++)
      {
         players[0].addCandy(findCharacter(character1_choice).inventory[i]);
      }

   cout << "The charater you choose is: " << players[0].getCharName() << endl;
   for(int i = 0; i < _cur_characters_menu; i++)
      {
         if(toLow(_character_menu[i].name) == toLow(character1_choice))
         {
            for(int j = i; j < _MAX_CHARACTERS_MENU - 1; j++)
            {
               _character_menu[j] = _character_menu[j+1];
            }
            _cur_characters_menu--;
            break;
         }
      }
   //player 1 visit candy
   cout << "Let's visit a candy store to get started." << endl;
   bought_candy1 = initial_store.visitCandyStore(0, players, _candy_menu);
 
   cout << "Enter player 2 name: " << endl; 
   cin >> player2_name; 
   cin.clear();
   cin.ignore(1000, '\n');
   players[1].setName(player2_name);

   cout << "Here is a list of characters you can choose from:" << endl; 
   displayCharacters();
   getline(cin, character2_choice);
   while(toLow(findCharacter(character2_choice).name) != toLow(character2_choice))
   {
      cout << "Invalid input!" << endl;
      getline(cin, character2_choice);
   }
   players[1].setCharName(findCharacter(character2_choice).name);
   players[1].setStamina(findCharacter(character2_choice).stamina);
   players[1].setGold(findCharacter(character2_choice).gold);

      for(int i = 0; i < 9; i++)
      {
         players[1].addCandy(findCharacter(character2_choice).inventory[i]);
         
      }
   cout << "The character you choose is: " << players[1].getCharName() << endl;
   cout << "Let's visit a candy store to get started." << endl;
   bought_candy2 = initial_store.visitCandyStore(1, players, _candy_menu);

}

void CandyLand::playGame(Board board, Player players[2])
{
   //used to write to at the end of the game
   ofstream file_out; 
   file_out.open("results.txt");
   
   bool game_over = false; //ends the game 
   bool turn_over1 = true; //used for do while loop with candy stats
   bool turn_over2 = true;
   string menu_choice1; 
   string menu_choice2;
   int change1 = 0;
   int change2 = 0;
   int break1_count = 0; //used for stamina break
   int break2_count = 0;
   int calamity_break1 = 0; //used for calamity break
   int calamity_break2 = 0;
   int gummy_break1 = 0; //used for gummy wall break
   int gummy_break2 = 0;
   CandyStore candy_store1;
   CandyStore candy_store2;
   CandyStore candy_store3;

   string bought_candy1;
   string bought_candy2;

   candy_store1.setCandyMenu(_candy_menu);
   candy_store2.setCandyMenu(_candy_menu);
   candy_store3.setCandyMenu(_candy_menu);

   do{
      // PLAYER ONE'S TURN
      do{
         turn_over1 = true;
         cout << "It's " << players[0].getName() << "'s turn." << endl << "Please select a menu option:" << endl; 
         cout << "1. Draw card" << endl;
         cout << "2. Use candy" << endl;
         cout << "3. Show player stats" << endl;
         getline(cin, menu_choice1); 
         while(menu_choice1 != "1" && menu_choice1 != "2" && menu_choice1 != "3")
         {
            cout << "Invalid input!" << endl;
            getline(cin, menu_choice1); 
         }
         if(menu_choice1 == "1") //DRAW A CARD
         {
            if(players[0].getStamina() <= 0) //checking if stamina is 0 or lower, will result in 2 turns lost
            {
               cout << "Your stamina is too low to move... be patient while it reloads." << endl;
               if(break1_count <= 0)
               {
                  break1_count++;
               }
               else 
               {
                  players[0].setStamina(20);
               }
            }
            else if(calamity_break1 > 0) //checking if a calamity caused a missed turn
            {
               cout << "The calamity got you. Sit this turn out." << endl;
               calamity_break1 = 0; //reset once you've sat once
            }
            else if(gummy_break1 > 0) //checking if a gummy wall caused a missed turn 
            {
               cout << "You ran into a gummy baricade. Sit this turn out" << endl;
               gummy_break1 = 0; //reset to zero once you've served your turn
            }
            else
            {
               
               change1 = players[0].drawCard(board.getPlayer1Position());
               board.movePlayer(1, change1);

               //CHECK FOR ALL CALAMITIES
                  if(board.getTile(board.getPlayer1Position()).tile_type == "regular tile") //only allowed on regular tiles 
                  {
                     int rand_calamity = randGenerator(1, 100);
                     if(rand_calamity <= 40) //40 percent chance it is calamity
                     {
                        int which_calamity = randGenerator(1, 100);
                        if(which_calamity >= 1 && which_calamity < 30) //30 % chance
                        {
                           isCandyBandits(0, players);
                           displayStats(players[0]);
                        }
                        else if(which_calamity >= 30 && which_calamity < 65) //35 % chance
                        {
                           bool stuck = false;
                           stuck = isLostLabyrinth(0, players); 
                           if(stuck == true)
                           {
                              calamity_break1++;
                           }
                        }
                        else if(which_calamity >= 65 && which_calamity < 80) //15 % chance
                        {
                           bool stuck = false;
                           stuck = isCandyAvalanche(0, players);
                           if(stuck == true)
                           {
                              calamity_break1++;
                           }
                           displayStats(players[0]);
                        }
                        else if(which_calamity >= 80 && which_calamity < 100) //20 % chance
                        {
                           bool stuck = false;
                           stuck = isStickyTaffyTrap(0, players);
                           if(stuck == true)
                           {
                              calamity_break1++;
                           }
                        }
                     }
                  }

                  //CHECK FOR SPECIAL TILES
                  else if(board.getTile(board.getPlayer1Position()).tile_type == "shortcut tile")
                  {
                     board = isShortcutTile(1, board, change1);
                  }
                  else if(board.getTile(board.getPlayer1Position()).tile_type == "ice cream shop tile")
                  {
                     if(board.sameTile(1) == true) //CHECK FOR SAME TILE function swaps positions
                     {
                        int stolen_gold = randGenerator(5,30);
                        string candy_name = "robbers_reppel";
                        cout << "You landed on the same tile as " << players[1].getName() << " they might get your gold!" << endl;
                        if(players[0].findCandy(candy_name).name != candy_name) //if opponent doesnt have robbers repel
                        {
                           if(stolen_gold > players[0].getGold())
                           {
                              stolen_gold = players[0].getGold();
                           }
                           players[0].setGold(players[0].getGold() - stolen_gold);
                           players[1].setGold(players[1].getGold() + stolen_gold);
                        }
                     }
                     board.displayBoard(); 
                     board = isIceCreamShopTile(1, board, players);
                  }
                  else if(board.getTile(board.getPlayer1Position()).tile_type == "gumdrop forest tile")
                  {
                     board = isGumdropForestTile(1, board, players, change1);
                     displayStats(players[0]);
                  }
                  else if(board.getTile(board.getPlayer1Position()).tile_type == "gingerbread house tile")
                  {
                     board = isGingerbreadHouseTile(1, board, players, change1);
                  }

                  //CHECK FOR TREASURES 
                  if(board.getTile(board.getPlayer1Position()).treasure == "gold windfall")
                  {
                     isGoldWindfall(0, players);
                     displayStats(players[0]);
                  }
                  else if(board.getTile(board.getPlayer1Position()).treasure == "stamina refill")
                  {
                     isStaminaRefill(0, players);
                     displayStats(players[0]);
                  }
                  else if(board.getTile(board.getPlayer1Position()).treasure == "robber's repel")
                  {
                     isRobbersRepel(0, players);
                     displayStats(players[0]);
                  }
                  else if(board.getTile(board.getPlayer1Position()).treasure == "candy aquisition")
                  {
                     isCandyAquistition(0, players);
                  }

                  //CHECK FOR EACH CANDYSTORE
                  if(board.getTile(board.getPlayer1Position()).tile_type == "candy store 1")
                  {
                     string yorn;
                     cout << "You landed on a candy store! Would you like to buy a candy? y/n" << endl; 
                     getline(cin, yorn);
                     while(toLow(yorn) != "y" && toLow(yorn) != "n")
                     {
                        cout << "Invalid input!" << endl;
                        getline(cin, yorn);
                     }
                     if(toLow(yorn) == "y")
                     {
                        bought_candy1 = candy_store1.visitCandyStore(0, players, _candy_menu);
                        //removeMenuCandy(bought_candy1);
                     }
                     else 
                     {
                        cout << "No candy for you then!" << endl; 
                     }
                  }
                  else if(board.getTile(board.getPlayer1Position()).tile_type == "candy store 2")
                  {
                     string yorn;
                     cout << "You landed on a candy store! Would you like to buy a candy? y/n" << endl; 
                     getline(cin, yorn);
                     while(toLow(yorn) != "y" && toLow(yorn) != "n")
                     {
                        cout << "Invalid input!" << endl;
                        getline(cin, yorn);
                     }
                     if(toLow(yorn) == "y")
                     {
                        bought_candy1 = candy_store2.visitCandyStore(0, players, _candy_menu);
                        //removeMenuCandy(bought_candy1);
                     }
                     else 
                     {
                        cout << "No candy for you then!" << endl; 
                     }
                  }
                  else if(board.getTile(board.getPlayer1Position()).tile_type == "candy store 3")
                  {
                     string yorn;
                     cout << "You landed on a candy store! Would you like to buy a candy? y/n" << endl; 
                     getline(cin, yorn);
                     while(toLow(yorn) != "y" && toLow(yorn) != "n")
                     {
                        cout << "Invalid input!" << endl;
                        getline(cin, yorn);
                     }
                     if(toLow(yorn) == "y")
                     {
                        bought_candy1 = candy_store3.visitCandyStore(0, players, _candy_menu);
                        //removeMenuCandy(bought_candy1);
                     }
                     else 
                     {
                        cout << "No candy for you then!" << endl; 
                     }
                  }
               //CHECK IF LANDED IN GUMMY CANDY
               if(board.getTile(board.getPlayer1Position()).tile_type == "gummy candy")
               {
                  gummy_break1 = 1;
               }
               //CHECK FOR SAME TILE
               if(board.sameTile(1) == true)
               {
                  int stolen_gold = randGenerator(5,30);
                  string candy_name = "robbers_reppel";
                  cout << "You landed on the same tile as " << players[1].getName() << " they might get your gold!" << endl;
                  if(players[0].findCandy(candy_name).name != candy_name)
                  {
                     if(stolen_gold > players[0].getGold())
                     {
                        stolen_gold = players[0].getGold();
                     }
                  players[0].setGold(players[0].getGold() - stolen_gold);
                  players[1].setGold(players[1].getGold() + stolen_gold);
                  }
                  displayStats(players[0]);
               }
               board.displayBoard();
               players[0].setStamina(players[0].getStamina() -1); 
            }
         }
         else if(menu_choice1 == "2") //USE CANDY
         {
            if(players[0].getCandyAmount() == 0) //if there is no candy left
            {
               cout << "You're out of candy! There's nothing to use." << endl;
            }
            else
            {
               string use_candy;
               cout << "Please select a candy from your inventory to use: " << endl;
               players[0].printInventory();
               getline(cin, use_candy);
               while(toLow(players[0].findCandy(use_candy).name) != toLow(use_candy))
               {
                  cout << "Invalid input!" << endl;
                  getline(cin, use_candy);
               }

               if(use_candy == "Frosty Fizz")
               {
                  int new_stamina = 10;
                  if((players[0].getStamina() + new_stamina) > 100)
                  {
                     new_stamina = 100 - players[0].getStamina();
                  }
                  else 
                  {
                     new_stamina = 10 + players[0].getStamina();
                  }
                  players[0].setStamina(new_stamina);
                  cout << "Your stamina increases by 10!" << endl;
                  players[0].removeCandy("Frosty Fizz");
                  displayStats(players[0]);
               }
               else if(use_candy == "Breezy Butterscotch") 
               {
                  int new_stamina = 15;
                  if((players[0].getStamina() + new_stamina) > 100)
                  {
                     new_stamina = 100 - players[0].getStamina();
                  }
                  else 
                  {
                     new_stamina = 15 + players[0].getStamina();
                  }
                  players[0].setStamina(new_stamina);
                  cout << "Your stamina increases by 15!" << endl;
                  players[0].removeCandy("Lucky Licorice");
                  displayStats(players[0]);
               }
               else if(use_candy == "Fearsome Fudge") 
               {
                  int tile_num = randGenerator((board.getPlayer1Position() + 1),81); 
                  cout << "You placed a gummy candy somewhere...who knows when it'll pop up. It could get you too! Risk...reward." << endl;
                  board.setTileType(tile_num, "gummy candy");
                  players[0].removeCandy("Fearsome Fudge");
               }
               else if(use_candy == "Lucky Licorice") //harms other player
               {
                  //unless opponent has protective candy 
                  if(players[1].findCandy("Bubblegum Blast").name == "Bubblegum Blast")
                  {
                     cout << "Your opponent has Bubblegum Blast... your candy can't hurt them!" << endl;
                     players[1].removeCandy("Bubblegum Blast");
                  }
                  else if(players[1].findCandy("Sparkling Saphire").name == "Sparkling Saphire")
                  {
                     cout << "Your opponent has Sparkling Saphire... your candy can't hurt them!" << endl;
                     players[1].removeCandy("Sparkling Saphire");
                  }
                  else if(players[1].findCandy("Caramel Comet").name == "Caramel Comet")
                  {
                     cout << "Your opponent has Caramel Comet... your candy can't hurt them!" << endl;
                     players[1].removeCandy("Caramel Comet");
                  }
                  else 
                  {
                     int new_stamina;
                     if((players[1].getStamina() - 10) < 0)
                     {
                        new_stamina = players[1].getStamina();
                     }
                     else 
                     {
                        new_stamina = players[1].getStamina() - 10;
                     }
                     players[1].setStamina(new_stamina);
                     cout << "Your opponent will lose 10 units of stamina!" << endl;
                  }
                  players[0].removeCandy("Lucky Licorice");
               }
               else if(use_candy == "Venomous Vortex") //harms other player
               {
                  //unless opponent has protective candy 
                  if(players[1].findCandy("Sparkling Saphire").name == "Sparkling Saphire")
                  {
                     cout << "Your opponent has Sparkling Saphire... your candy can't hurt them!" << endl;
                     players[1].removeCandy("Sparkling Saphire");
                  }
                  else if(players[1].findCandy("Caramel Comet").name == "Caramel Comet")
                  {
                     cout << "Your opponent has Caramel Comet... your candy can't hurt them!" << endl;
                     players[1].removeCandy("Caramel Comet");
                  }
                  else 
                  {
                     int new_stamina;
                     if((players[1].getStamina() - 15) < 0)
                     {
                        new_stamina = players[1].getStamina();
                     }
                     else 
                     {
                        new_stamina = players[1].getStamina() - 15;
                     }
                     players[1].setStamina(new_stamina);
                     cout << "Your opponent will lose 15 units of stamina!" << endl;
                  }
                  players[0].removeCandy("Venomous Vortex");
               }
               else if(use_candy == "Toxic Taffy") //harms other player
               {
                  //unless opponent has protective candy 
                  if(players[1].findCandy("Caramel Comet").name == "Caramel Comet")
                  {
                     cout << "Your opponent has Caramel Comet... your candy can't hurt them!" << endl;
                     players[1].removeCandy("Caramel Comet");
                  }
                  else 
                  {
                     int new_stamina;
                     if((players[1].getStamina() - 20) < 0)
                     {
                        new_stamina = players[1].getStamina();
                     }
                     else 
                     {
                        new_stamina = players[1].getStamina() - 20;
                     }
                     players[1].setStamina(new_stamina);
                     cout << "Your opponent will lose 20 units of stamina!" << endl;
                  }
                  players[0].removeCandy("Toxic Taffy");
               }
               else if(use_candy == "Bubblegum Blast") //protective candy 
               {
                  cout << "You can't use this candy... it will protect you when you need it!" << endl; 
               }
               else if(use_candy == "Sparkling Sapphire") //protective candy
               {
                  cout << "You can't use this candy... it will protect you when you need it!" << endl; 
               }
               else if(use_candy == "Caramel Comet") //protective candy
               {
                  cout << "You can't use this candy... it will protect you when you need it!" << endl; 
               }
               else if(use_candy == "Jellybean of Vigor") //protective candy
               {
                  int new_stamina = 50;
                  if((players[0].getStamina() + new_stamina) > 100)
                  {
                     new_stamina = 100 - players[0].getStamina();
                  }
                  else 
                  {
                     new_stamina = 50 + players[0].getStamina();
                  }
                  players[0].setStamina(new_stamina);
                  cout << "Your stamina increases by 50!" << endl;
                  players[0].removeCandy("Jellybean of Vigor");
                  displayStats(players[0]);
               }
               else if(use_candy == "Treasure Hunter's Truffle")
               {
                  players[0].removeCandy("Treasure Hunter's Truffle");
                  solvePuzzle(0, players);
                  players[0].printInventory();
               }
            }
         }
         else if(menu_choice1 == "3") //SHOW STATS
         {
            displayStats(players[0]);
            turn_over1 = false;
         }
      } while (turn_over1 == false); //makes sure it wasn't show stats before moving on 
      
      //PLAYER 2 TURN
      do
      {
         turn_over2 = true;
         cout << "It's " << players[1].getName() << "'s turn." << endl << "Please select a menu option:" << endl; 
         cout << "1. Draw card" << endl;
         cout << "2. Use candy" << endl;
         cout << "3. Show player stats" << endl;
         getline(cin, menu_choice2); 
         while(menu_choice2 != "1" && menu_choice2 != "2" && menu_choice2 != "3")
         {
            cout << "Invalid input!" << endl;
            getline(cin, menu_choice2); 
         }
         if(menu_choice2 == "1") //DRAW CARD
         {
            if(players[1].getStamina() <= 0)
            {
               cout << "Your stamina is too low to move... be patient while it reloads." << endl;
               if(break2_count <= 0)
               {
                  break2_count++;
               }
               else 
               {
                  players[1].setStamina(20);
               }
            }
            else if(calamity_break2 > 0)
            {
               cout << "The calamity got you. Sit this turn out." << endl;
               calamity_break2 = 0; //reset to zero once you've served your turn
            }
            else if(gummy_break2 > 0)
            {
               cout << "You ran into a gummy baricade. Sit this turn out" << endl;
               gummy_break2 = 0; //reset to zero once you've served your turn
            }
            else 
            {
               //player 2
               change2 = players[1].drawCard(board.getPlayer2Position());
               board.movePlayer(2, change2);
               if(board.getTile(board.getPlayer2Position()).tile_type == "regular tile")
               {
                  int rand_calamity = randGenerator(1, 100);
                  if(rand_calamity <= 40)
                  {
                     int which_calamity = randGenerator(1, 100);
                     if(which_calamity >= 1 && which_calamity < 30)
                     {                        
                        isCandyBandits(1, players);
                        displayStats(players[1]); //not displaying stats
                     }
                     else if(which_calamity >= 30 && which_calamity < 65)
                     {
                        bool stuck = false;
                        stuck = isLostLabyrinth(1, players); //even if you are false its false 
                        if(stuck == true)
                        {
                           calamity_break2++;
                        }
                     }
                     else if(which_calamity >= 65 && which_calamity < 80)
                     {                        
                        bool stuck = false;
                        stuck = isCandyAvalanche(1, players);
                        if(stuck == true)
                        {
                           calamity_break2++;
                        }
                        displayStats(players[1]);
                     }
                     else if(which_calamity >= 80 && which_calamity < 100)
                     {
                        bool stuck = false;
                        stuck = isStickyTaffyTrap(1, players);
                        if(stuck == true)
                        {
                           calamity_break2++;
                        }
                     }
                     
                  }
               }

                  //check for special tiles
                  if(board.getTile(board.getPlayer2Position()).tile_type == "shortcut tile")
                  {
                     board = isShortcutTile(2, board, change2);
                  }
                  else if(board.getTile(board.getPlayer2Position()).tile_type == "ice cream shop tile")
                  {
                     if(board.sameTile(2) == true)
                     {
                        int stolen_gold = randGenerator(5,30);
                        string candy_name = "robbers_reppel";
                        cout << "You landed on the same tile as " << players[0].getName() << ", they might get your gold!" << endl;
                        if(players[1].findCandy(candy_name).name != candy_name)
                        {
                           if(stolen_gold > players[1].getGold())
                           {
                              stolen_gold = players[1].getGold();
                           }
                           players[1].setGold(players[1].getGold() - stolen_gold);
                           players[0].setGold(players[0].getGold() + stolen_gold);
                        }
                     }
                     board.displayBoard(); ////
                     board = isIceCreamShopTile(2, board, players);
                  }
                  else if(board.getTile(board.getPlayer2Position()).tile_type == "gumdrop forest tile")
                  {
                     board = isGumdropForestTile(2, board, players, change2);
                     displayStats(players[1]);
                  }
                  else if(board.getTile(board.getPlayer2Position()).tile_type == "gingerbread house")
                  {
                     board = isGingerbreadHouseTile(2, board, players, change2);
                  }
                  //check treasure
                  if(board.getTile(board.getPlayer2Position()).treasure == "gold windfall")
                  {
                     isGoldWindfall(1, players);
                     displayStats(players[1]);
                  }
                  else if(board.getTile(board.getPlayer2Position()).treasure == "stamina refill")
                  {
                     isStaminaRefill(1, players);
                     displayStats(players[1]);
                  }
                  else if(board.getTile(board.getPlayer2Position()).treasure == "robber's repel")
                  {
                     isRobbersRepel(1, players);
                     displayStats(players[1]);
                  }
                  else if(board.getTile(board.getPlayer2Position()).treasure == "candy aquisition")
                  {
                     isCandyAquistition(1, players);
                  }
                  //check for candy store
                  if(board.getTile(board.getPlayer2Position()).tile_type == "candy store 1")
                  {
                     string yorn;
                     cout << "You landed on a candy store! Would you like to buy a candy? y/n" << endl; 
                     getline(cin, yorn);
                     while(toLow(yorn) != "y" && toLow(yorn) != "n")
                     {
                        cout << "Invalid input!" << endl;
                        getline(cin, yorn);
                     }
                     if(toLow(yorn) == "y")
                     {
                        bought_candy2 = candy_store1.visitCandyStore(1, players, _candy_menu);
                        //removeMenuCandy(bought_candy2);
                     }
                     else 
                     {
                        cout << "No candy for you then!" << endl; 
                     }
                  }
                  else if(board.getTile(board.getPlayer2Position()).tile_type == "candy store 2")
                  {
                     string yorn;
                     cout << "You landed on a candy store! Would you like to buy a candy? y/n" << endl; 
                     getline(cin, yorn);
                     while(toLow(yorn) != "y" && toLow(yorn) != "n")
                     {
                        cout << "Invalid input!" << endl;
                        getline(cin, yorn);
                     }
                     if(toLow(yorn) == "y")
                     {
                        bought_candy2 = candy_store2.visitCandyStore(1, players, _candy_menu);
                        //removeMenuCandy(bought_candy2);
                     }
                     else 
                     {
                        cout << "No candy for you then!" << endl; 
                     }
                  }
                  else if(board.getTile(board.getPlayer2Position()).tile_type == "candy store 3")
                  {
                     string yorn;
                     cout << "You landed on a candy store! Would you like to buy a candy? y/n" << endl; 
                     getline(cin, yorn);
                     while(toLow(yorn) != "y" && toLow(yorn) != "n")
                     {
                        cout << "Invalid input!" << endl;
                        getline(cin, yorn);
                     }
                     if(toLow(yorn) == "y")
                     {
                        bought_candy2 = candy_store3.visitCandyStore(1, players, _candy_menu);
                        //removeMenuCandy(bought_candy2);
                     }
                     else 
                     {
                        cout << "No candy for you then!" << endl; 
                     }
                  }
                  //CHECK IF LANDED IN GUMMY CANDY
               if(board.getTile(board.getPlayer2Position()).tile_type == "gummy candy")
               {
                  cout << "Candy baricade encountered!" << endl;
                  gummy_break2 = 1;
               }
               
               if(board.sameTile(2) == true)
               {
                  int stolen_gold = randGenerator(5,30);
                  string candy_name = "robbers_reppel";
                  cout << "You landed on the same tile as " << players[0].getName() << ", they might get your gold!" << endl;
                  if(players[1].findCandy(candy_name).name != candy_name)
                  {
                     if(stolen_gold > players[1].getGold())
                     {
                        stolen_gold = players[1].getGold();
                     }
                     players[1].setGold(players[1].getGold() - stolen_gold);
                     players[0].setGold(players[0].getGold() + stolen_gold);
                  }
                  displayStats(players[1]);
               }

               board.displayBoard();
               players[1].setStamina(players[1].getStamina() -1); //decrease stamina by one unit
            }
         }
         else if(menu_choice2 == "2") //USE CANDY
         {
            if(players[1].getCandyAmount() == 0) //if there is nothing to use 
            {
               cout << "You're out of candy! There's nothing to use." << endl;
            }
            else 
            {
               string use_candy;
               cout << "Please select a candy from your inventory to use: " << endl;
               players[1].printInventory();
               getline(cin, use_candy);
               while(toLow(players[1].findCandy(use_candy).name) != toLow(use_candy))
               {
                  cout << "Invalid input!" << endl;
                  getline(cin, use_candy);
               }

               if(use_candy == "Frosty Fizz")
               {
                  int new_stamina = 10;
                  if((players[1].getStamina() + new_stamina) > 100)
                  {
                     new_stamina = 100 - players[1].getStamina();
                  }
                  else 
                  {
                     new_stamina = 10 + players[1].getStamina();
                  }
                  players[1].setStamina(new_stamina);
                  cout << "Your stamina increases by 10!" << endl;
                  players[1].removeCandy("Frosty Fizz");
                  displayStats(players[1]);
               }
               else if(use_candy == "Breezy Butterscotch")
               {
                  int new_stamina = 15;
                  if((players[1].getStamina() + new_stamina) > 100)
                  {
                     new_stamina = 100 - players[1].getStamina();
                  }
                  else 
                  {
                     new_stamina = 15 + players[1].getStamina();
                  }
                  players[1].setStamina(new_stamina);
                  cout << "Your stamina increases by 15!" << endl;
                  players[1].removeCandy("Breezy Butterscotch");
                  displayStats(players[1]);
               }
               else if(use_candy == "Fearsome Fudge") 
               {
                  int tile_num = randGenerator((board.getPlayer2Position() + 1),81); 
                  cout << "You placed a gummy candy somewhere...who knows when it'll pop up. It could get you too! Risk...reward." << endl;
                  board.setTileType(tile_num, "gummy candy");
                  players[1].removeCandy("Fearsome Fudge");
               }
               else if(use_candy == "Lucky Licorice") //harms other player
               {
                  //unless has bubblegum blast, sparkinf saphire or Caramel comet
                  if(players[0].findCandy("Bubblegum Blast").name == "Bubblegum Blast")
                  {
                     cout << "Your opponent has Bubblegum Blast... your candy can't hurt them!" << endl;
                     players[0].removeCandy("Bubblegum Blast");
                  }
                  else if(players[0].findCandy("Sparkling Saphire").name == "Sparkling Saphire")
                  {
                     cout << "Your opponent has Sparkling Saphire... your candy can't hurt them!" << endl;
                     players[0].removeCandy("Sparkling Saphire");
                  }
                  else if(players[0].findCandy("Caramel Comet").name == "Caramel Comet")
                  {
                     cout << "Your opponent has Caramel Comet... your candy can't hurt them!" << endl;
                     players[0].removeCandy("Caramel Comet");
                  }
                  else 
                  {
                     int new_stamina;
                     if((players[0].getStamina() - 10) < 0)
                     {
                        new_stamina = players[0].getStamina();
                     }
                     else 
                     {
                        new_stamina = players[0].getStamina() - 10;
                     }
                     players[0].setStamina(new_stamina);
                     cout << "Your opponent will lose 10 units of stamina!" << endl;
                  }
                  players[1].removeCandy("Lucky Licorice");
               }
               else if(use_candy == "Venomous Vortex")
               {
                  //unless has sparkinf saphire or Caramel comet
                  if(players[0].findCandy("Sparkling Saphire").name == "Sparkling Saphire")
                  {
                     cout << "Your opponent has Sparkling Saphire... your candy can't hurt them!" << endl;
                     players[0].removeCandy("Sparkling Saphire");
                  }
                  else if(players[0].findCandy("Caramel Comet").name == "Caramel Comet")
                  {
                     cout << "Your opponent has Caramel Comet... your candy can't hurt them!" << endl;
                     players[0].removeCandy("Caramel Comet");
                  }
                  else 
                  {
                     int new_stamina;
                     if((players[0].getStamina() - 15) < 0)
                     {
                        new_stamina = players[0].getStamina();
                     }
                     else 
                     {
                        new_stamina = players[0].getStamina() - 15;
                     }
                     players[0].setStamina(new_stamina);
                     cout << "Your opponent will lose 15 units of stamina!" << endl;
                  }
                  players[1].removeCandy("Venomous Vortex");
               }
               else if(use_candy == "Toxic Taffy")
               {
                  //unless has Caramel comet
                  if(players[0].findCandy("Caramel Comet").name == "Caramel Comet")
                  {
                     cout << "Your opponent has Caramel Comet... your candy can't hurt them!" << endl;
                     players[0].removeCandy("Caramel Comet");
                  }
                  else 
                  {
                     int new_stamina;
                     if((players[0].getStamina() - 20) < 0)
                     {
                        new_stamina = players[0].getStamina();
                     }
                     else 
                     {
                        new_stamina = players[0].getStamina() - 20;
                     }
                     players[0].setStamina(new_stamina);
                     cout << "Your opponent will lose 20 units of stamina!" << endl;
                  }
                  players[1].removeCandy("Toxic Taffy");
               }
               else if(use_candy == "Bubblegum Blast")
               {
                  cout << "You can't use this candy... it will protect you when you need it!" << endl; 
               }
               else if(use_candy == "Sparkling Sapphire")
               {
                  cout << "You can't use this candy... it will protect you when you need it!" << endl; 
               }
               else if(use_candy == "Caramel Comet")
               {
                  cout << "You can't use this candy... it will protect you when you need it!" << endl; 
               }
               else if(use_candy == "Jellybean of Vigor")
               {
                  int new_stamina = 50;
                  if((players[1].getStamina() + new_stamina) > 100)
                  {
                     new_stamina = 100 - players[1].getStamina();
                  }
                  else 
                  {
                     new_stamina = 50 + players[1].getStamina();
                  }
                  players[1].setStamina(new_stamina);
                  cout << "Your stamina increases by 50!" << endl;
                  players[1].removeCandy("Jellybean of Vigor");
                  displayStats(players[1]);
               }
               else if(use_candy == "Treasure Hunter's Truffle")
               {
                  players[1].removeCandy("Treasure Hunter's Truffle");
                  solvePuzzle(1, players);
                  players[1].printInventory();
               }
            }
            
         }
         else if(menu_choice2 == "3") //SHOW STATS
         {
            displayStats(players[1]);
            turn_over2 = false;
         }
      } while(turn_over2 == false);

      //PLAYER 2 TURN IS OVER

      if(board.getPlayer1Position() == 82) //player1 wins
      {
         game_over = true;
         cout << "Congratulations, " << players[0].getName() << " has won Candy Land!" << endl; 
         displayStats(players[0]);

         //add to the file
         file_out << "Winner: " << players[0].getName() << endl;
         file_out << "Stamina: " << players[0].getStamina() << endl;
         file_out << "Gold: " << players[0].getGold() << endl;
         file_out << "Candies: " << players[0].getInventory() << endl;
         
      }
      else if(board.getPlayer2Position() == 82) //player2 wins
      {
         game_over = true; 
         cout << "Congratulations, " << players[1].getName() << " has won Candy Land!" << endl; 
         displayStats(players[1]);

         //add to the file
         file_out << "Winner: " << players[1].getName() << endl;
         file_out << "Stamina: " << players[1].getStamina() << endl;
         file_out << "Gold: " << players[1].getGold() << endl;
         file_out << "Candies: " << players[1].getInventory() << endl;
      }
      
   }while(game_over == false);

}
//decides between riddle or rock paper scissors
void CandyLand::solvePuzzle(int player_num, Player players[])
{
   int rand_candy = randGenerator(1,9);
   int rand_puzzle = randGenerator(1,2); 
   Candy new_candy = _candy_menu[rand_candy];
   string yorn;

   if(rand_puzzle == 1)//solve riddle 
   {
      string answer;
      cout << "Unlock a candy by solving a riddle!" << endl;
      int rand_riddle = randGenerator(0,2); //indexed because its looking in an array

      cout << _riddle_menu[rand_riddle].question << endl; 
      getline(cin, answer);

      string correct_answer = _riddle_menu[rand_riddle].answer;
      if(answer == correct_answer) // they answered correctly they get the option of gaining candy 
      {
         cout << "Correct! You get a " << new_candy.name << " as a prize." << endl;
         string remove_candy;
         string yorn;
         cout << "Would you like to give up a candy to accept this? y/n" << endl; 
         getline(cin, yorn);
         while(toLow(yorn) != "y" && toLow(yorn) != "n")
         {
            cout << "Invalid input!" << endl;
            getline(cin, yorn);
         }
         if(toLow(yorn) == "y")
         {
            if(players[player_num].getCandyAmount() == 9)
            {
               cout << "What candy do you relinquish?" << endl;
               players[player_num].printInventory();
               getline(cin, remove_candy);
               while(toLow(players[player_num].findCandy(remove_candy).name) != toLow(remove_candy))
               {
                  cout << "Invalid input!" << endl;
                  getline(cin, remove_candy);
               }
               players[player_num].removeCandy(remove_candy);
               players[player_num].addCandy(new_candy);
               cout << "Your new inventory is: " << endl;
               players[player_num].printInventory();
            }
            else 
            {
               players[player_num].addCandy(new_candy);
               cout << "Your new inventory is: " << endl;
               players[player_num].printInventory();
            }
         }
         else 
         {
            cout << "Alright then, carry on." << endl; 
         }

      }
      else 
      {
         cout << "Not quite, maybe next time!" << endl;
      }
   }
   else if(rand_puzzle == 2)//play rock paper scissors
   {
      string results = players[player_num].playRockPaperScissors();
      if(results == "won") //if they win they get the option of gaining a candy 
      {
         cout << "You get a " << new_candy.name << " as a prize." << endl;
         string remove_candy;
         string yorn;
         cout << "Would you like to give up a candy to accept this? y/n" << endl; 
         getline(cin, yorn);
         while(toLow(yorn) != "y" && toLow(yorn) != "n")
         {
            cout << "Invalid input!" << endl;
            getline(cin, yorn);
         }
         if(toLow(yorn) == "y")
         {
            if(players[player_num].getCandyAmount() == 9)
            {
               cout << "What candy do you relinquish?" << endl;
               players[player_num].printInventory();
               getline(cin, remove_candy);
               while(toLow(players[player_num].findCandy(remove_candy).name) != toLow(remove_candy))
               {
                  cout << "Invalid input!" << endl;
                  getline(cin, remove_candy);
               }
               players[player_num].removeCandy(remove_candy);
               players[player_num].addCandy(new_candy);
               cout << "Your new inventory is: " << endl;
               //players[player_num].printInventory();
            }
            else 
            {
               players[player_num].addCandy(new_candy);
               cout << "Your new inventory is: " << endl;
               //players[player_num].printInventory();
            }
         }
         else 
         {
            cout << "Alright then, carry on." << endl; 
         }
      }
      else
      {
         cout << "Not quite, maybe next time!" << endl;
      }
   }
}

