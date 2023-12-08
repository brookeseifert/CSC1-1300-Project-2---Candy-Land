-----------------------
HOW TO COMPILE AND RUN 
-----------------------
Compile: g++ -Wall -Werror -Wpedantic -std=c++17 0candyLandDriver.cpp CandyLand.cpp Board.cpp Player.cpp CandyStore.cpp
Run: ./project2
-----------------------
DEPENDENCIES
-----------------------
Board.h, Candy.h, CandyLand.h, CandyStore.h, Card.h, Character.h, Player.h, Riddle.h, and Tile.h must be in the same directory as the .cpp files in order to compile. 
Additionally, the following text files must be in that same folder:
candy.txt, characters.txt, results.txt, and riddles.txt.
-----------------------
SUBMISSION INFROMATION
-----------------------
CSCI1300 Fall 2023 Project 2
Author: Brooke Seifert
Recitation: 304 - Aditya Chandra
Date: Dec 7, 2023
-----------------------
ABOUT THIS PROJECT 
-----------------------
This project is losely based on the board game "Candy Land" with additions such as calamities, treasures, and special tiles. 
It is a 2 person interactive game that allows the user to choose a character to traverse the Candy Land board as. 
As the user progresses through the game, they may encounter obstacles, solve riddles, use candys, and buy more powerful candies. The goal is to reach the castle before the other player does and be crowned the Victor of Candy Land.  
