#ifndef __MINESWEEPER_HPP__
#define __MINESWEEPER_HPP__

enum DIFFICULT
{
    EASY,
    MID,
    HARD,
    USER
};

enum GameState
{
    WIN,
    LOST,
    OK // Go on not lost
};


struct Position
{
    int y;
    int x;
    bool mine;      // true -> yes 
    bool discover;  //true -> yes false -> no
    int num;        // indicate the numbers of bombs around when it is not bomb
    bool flag;

    Position():mine(false),discover(false),num(0),flag(false), y(0), x(0){}
    Position(bool min, bool dis, int n):mine(min),discover(dis),num(n),flag(false),y(0), x(0){}
};


class MineSweeper
{
public:
    MineSweeper();
    MineSweeper(DIFFICULT level, int h = 9, int w = 9, int num = 10);
    ~MineSweeper();

    GameState Move(int y, int x, bool flag);
    void DisplayMapInside();
    void DisplayCover();

private:
    void BFS(int y, int x);
    void CreateMap();
    
private:
    Position **game_map;
    int num_mines;
    int width;
    int height;
    int num_discover;
};

#endif