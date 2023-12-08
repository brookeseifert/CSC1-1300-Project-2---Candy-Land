#ifndef CHARACTER_H
#define  CHARACTER_H

#include <iostream>
using namespace std;
#include "Candy.h"

struct Character
{
   string name; 
   int stamina;
   double gold; 
   int static const MAX_CANDY = 9;
   Candy inventory[MAX_CANDY];
};

#endif 