
#include <iostream>
#include "Tile.h"
#include "Board.h"
#include "CandyStore.h"

int randGen(int min, int max)
{
   return (rand() % (max - min + 1) + min);
}

Board::Board()
{
    resetBoard();
}

void Board::resetBoard()
{
    const int COLOR_COUNT = 3;
    const string COLORS[COLOR_COUNT] = {MAGENTA, GREEN, BLUE};
    Tile new_tile;
    string current_color;
    int placed_treasure = 0;
    int placed_candy_store1 = 0;
    int placed_candy_store2 = 0;
    int placed_candy_store3 = 0;
    CandyStore candy_store;

    for(int i = 0; i < _BOARD_SIZE - 1; i++)
    {
        current_color = COLORS[i % COLOR_COUNT];
        new_tile.color = current_color;
        int rand_type = randGen(1,100);
        //SET SPECIAL TILES
        if(rand_type < 7 && rand_type >= 1)
        {
            new_tile.tile_type = "shortcut tile";
        }
        else if(rand_type < 14 && rand_type >= 7)
        {
            new_tile.tile_type = "ice cream shop tile";
        }
        else if(rand_type < 21 && rand_type >= 14)
        {
            new_tile.tile_type = "gumdrop forest tile";
        }
        else if(rand_type < 28 && rand_type >= 21)
        {
            new_tile.tile_type = "gingerbread house tile";
        }
        else 
        {
            new_tile.tile_type = "regular tile";
        }
        
        _tiles[i] = new_tile;
    }
  
    new_tile.color = ORANGE; 
    new_tile.tile_type = "regular tile";
    _tiles[_BOARD_SIZE - 1] = new_tile;

    while(placed_treasure < 3)
    {
        //PLACE TREASURES
        int rand_treasure = randGen(1, 100);
        if(rand_treasure <= 10 )
        {
            _tiles[rand_treasure].treasure = "gold windfall";
            placed_treasure++;
        }
        else if(rand_treasure <= 40 && rand_treasure > 10)
        {
            _tiles[rand_treasure].treasure = "candy aquisition";
            placed_treasure++;
            //decision between jellybean and treasure hunter in implementation 
        }
        else if(rand_treasure <= 70 && rand_treasure > 40)
        {
            _tiles[rand_treasure].treasure = "robber's repel";
            placed_treasure++;
        }
        else if(rand_treasure <= 100 && rand_treasure > 70) 
        {
            _tiles[rand_treasure].treasure = "stamina refill";
            placed_treasure++;
        }
    }
    while(placed_candy_store1 < 1 || placed_candy_store2 < 1 || placed_candy_store3 < 1)
    {
        int rand_candy_store = randGen(1, 100);
        //PLACE CANDY STORES
        if(rand_candy_store > 0 && rand_candy_store <= 26 && placed_candy_store1 < 1 && _tiles[rand_candy_store].color == MAGENTA) //magenta tile
        {
            _tiles[rand_candy_store].tile_type = "candy store 1";
            placed_candy_store1++;
        }
        else if(rand_candy_store > 26 && rand_candy_store <= 53 && placed_candy_store2 < 1 && _tiles[rand_candy_store].color == GREEN) // green tile
        {
            _tiles[rand_candy_store].tile_type = "candy store 2";
            placed_candy_store2++;
        }
        else if(rand_candy_store > 53 && rand_candy_store <= 81 && placed_candy_store3 < 1 && _tiles[rand_candy_store].color == BLUE) // blue tile
        {
            _tiles[rand_candy_store].tile_type = "candy store 3";
            placed_candy_store3++;
        }
    }
    _player1_position = 0;
    _player2_position = 0;
}

void Board::displayTile(int position) 
{
    if (position < 0 || position >= _BOARD_SIZE)
    {
        return;
    }
    Tile target = _tiles[position];
    cout << target.color << " ";
    if (position == _player1_position)
    {
        cout << "1";
    }
    else if(position == _player2_position)
    {
        cout << "2";
    }
    else
    {
        cout << " ";
    }
    cout << " " << RESET;
}

void Board::setTileType(int position, string type) //used for setting fearsome fudge 
{
    if(type != "gummy candy" && type != "candy store 1" && type != "candy store 2" && type != "candy store 3" && type != "shortcut tile" && type != "ice cream shop tile" && type != "gumdrop forest tile" && type != "gingerbread house tile")
    {
        type = "regular tile";
    }
    _tiles[position].tile_type = type;
}

Tile Board::getTile(int position)
{
    Tile empty_tile = {"", "", "", 0};
    if (position < 0 || position >= _BOARD_SIZE)
    {
        return empty_tile;
    }
    Tile target = _tiles[position];
    return target;
}

void Board::displayBoard()
{
    cout << "Here's the updated trail." << endl;
    // First horizontal segment
    for (int i = 0; i <= 23; i++)
    {
        displayTile(i);
    }
    cout << endl;
    // First vertical segment
    for (int i = 24; i <= 28; i++)
    {
        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        displayTile(i);
        cout << endl;
    }
    // Second horizontal segment
    for (int i = 52; i > 28; i--)
    {
        displayTile(i);
    }
    cout << endl;
    // Second vertical segment
    for (int i = 53; i <= 57; i++)
    {
        displayTile(i);
        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        cout << endl;
    }
    // Third horizontal segment
    for (int i = 58; i < _BOARD_SIZE; i++)
    {
        displayTile(i);
    }
    cout << ORANGE << "Castle" << RESET << endl;
}
bool Board::setPlayer1Position(int new_position)
{
    if (new_position >= 0 && new_position < _BOARD_SIZE)
    {

        _player1_position = new_position;
    }
    return true;
}
int Board::getPlayer1Position() const
{
    int position = 0;
    position = _player1_position;
    return position; 
}
bool Board::setPlayer2Position(int new_position)
{
    if (new_position >= 0 && new_position < _BOARD_SIZE)
    {

        _player2_position = new_position;
    }
    return true;
}
int Board::getPlayer2Position() const
{
    int position = 0; 
    position = _player2_position;
    return position; 
}

int Board::getBoardSize() const
{
    return _BOARD_SIZE;
}

int Board::getCandyStoreCount() const
{
    return _candy_store_count;
}

bool Board::addCandyStore(int position)
{
    if (_candy_store_count >= _MAX_CANDY_STORE)
    {
        return false;
    }
    _candy_store_position[_candy_store_count] = position;
    _candy_store_count++;
    return true;
}

bool Board::isPositionCandyStore(int board_position)
{
    for (int i = 0; i < _candy_store_count; i++)
    {
        if(_candy_store_position[i] == board_position)
        {
            return true;
        }
    }
    return false;
}

bool Board::movePlayer(int player_num, int tile_to_move_forward)
{
    bool flag = true;
    if(player_num == 1)
    {
        int new_player_position = tile_to_move_forward + _player1_position;
        if(new_player_position < 0 || new_player_position >= _BOARD_SIZE)
        {
            flag = false;
        }
        _player1_position = new_player_position;
    }
    else if(player_num == 2)
    {
        int new_player_position = tile_to_move_forward + _player2_position;
        if(new_player_position < 0 || new_player_position >= _BOARD_SIZE)
        {
            flag = false;
        }
        _player2_position = new_player_position;
    }
  return flag;
}
//checks if the players have the same position 
bool Board::sameTile(int player_num) //put in the curent player as player_num
{
    bool flag = false;

    if(_player1_position == _player2_position)
    {
        if(player_num == 1) //cur_player is player1
        {
            setPlayer2Position(getPlayer2Position() - 1);
        }
        else if(player_num == 2)
        {
            setPlayer1Position(getPlayer1Position() - 1);
        }
        flag = true; 
    }
  return flag;
}