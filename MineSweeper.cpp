#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <time.h>
#include <algorithm>
#include "MineSweeper.hpp"

MineSweeper::MineSweeper():height(9),width(9), num_mines(9), num_discover(0)
{
    CreateMap();
    DisplayMapInside();
}

MineSweeper::MineSweeper(DIFFICULT level, int h, int w, int num)
{
    num_discover = 0;
    switch (level)
    {
    case EASY:
        height = 9;
        width = 9;
        num_mines = 10;
        break;
    case MID:
        height = 16;
        width = 16;
        num_mines = 40;
        break;
    case HARD:
        height = 16;
        width = 30;
        num_mines = 99;
        break;
    case USER:
        height = h;
        width = w;
        num_mines = num;
        break;
    default:
        height = 9;
        width = 9;
        num_mines = 10;
        break;
    }
    CreateMap();
    DisplayMapInside();
}

void MineSweeper::CreateMap()
{
    // New the array
    game_map = new Position*[height];
    for (int h=0; h < height; h++)
    {
        game_map[h] = new Position[width];
    }
    
    // initialize the (y, x) for position in map for BFS
    for (int h = 0; h<height;h++)
    {
        for(int w = 0;w<width; w++)
        {
            game_map[h][w].y = h;
            game_map[h][w].x = w;
        }
    }

    // make a list of range(0, width*heigh) without overlapping
    srand(time(NULL));
    std::vector<int> num_list;
    while(num_list.size() < num_mines){
        int num = random()%(height*width);
        if(std::find(num_list.begin(), num_list.end(), num) == num_list.end())
        {
            num_list.push_back(num);
            std::cout << num << " ";
        }       
    }
    std::cout << std::endl;

    // Put mine on the map
    for(auto it:num_list)
    {
        int y = it / height;
        int x = it % width;
        game_map[y][x].mine = true;
        game_map[y][x].discover = false;
        game_map[y][x].num = 9;
        std::cout << y << "," << x << ":" << game_map[y][x].mine << " ";
    }

    std::cout << std::endl;
    
    // Caculate the number of non-mine position
    for(int h = 0; h < height; h++)
    {
        for(int w = 0; w < width; w++)
        {
            if(!game_map[h][w].mine)
            {
                for (int i = 0; i < 9; i++)
                {
                    int ty = h-1+i/3;
                    int tx = w-1+i%3;
                    if(ty >= 0 && ty < height &&
                    tx >= 0 && tx < width &&
                    (ty != h || tx != w) && game_map[ty][tx].mine) 
                    {
                        game_map[h][w].num++;
                    }
                }
                
            }
        }
    }    
}


MineSweeper::~MineSweeper()
{
    for(int i = 0; i < height; ++i) {
        delete [] game_map[i];
    }
    delete [] game_map;
}

void MineSweeper::DisplayMapInside()
{
    for(int h = 0; h < height; h++)
    {
        for (int w=0; w < width; w++)
        {
            std::cout<< game_map[h][w].num << " ";
        }
        std::cout << std::endl;
    }
}

void MineSweeper::DisplayCover()
{
    std::cout << "New Board:" << std::endl;
    for(int h = 0; h < height; h++)
    {
        for (int w=0; w < width; w++)
        {
            if(!game_map[h][w].discover)
            {
                if(game_map[h][w].flag)
                {
                    std::cout << "F ";
                }
                else 
                {
                    std::cout << "* ";
                }
            } else
            {
                if (game_map[h][w].num == 0)
                {
                    std::cout <<"  ";
                }else
                {
                    std::cout << game_map[h][w].num << " ";
                }
            }   
        }
        std::cout << std::endl;
    }
}

// true -> OK
// false -> NOK
GameState MineSweeper::Move(int y, int x, bool flag = false)
{
    // if not discovered, then 
    if(!game_map[y][x].discover)
    {
        if(flag)
        {
            // if flag is on the position, remove flag
            // if flag is not on the position, add flag
            game_map[y][x].flag = !game_map[y][x].flag;
        } else
        {
            // not discovered, then click it
            game_map[y][x].discover = true;
            if(game_map[y][x].mine)
            {
                DisplayCover();
                return LOST;
            } else 
            {
                // not mine
                num_discover++;
                if(game_map[y][x].num == 0)
                {
                    BFS(y, x);
                }             
            }
        }
    }

    DisplayCover();
    if(width*height - num_mines > num_discover)
    {
        return OK;
    }else
    {
        return WIN;
    }      
}

/* 
def bfs(g,start):
  start.setDistance(0)
  start.setPred(None)
  vertQueue = Queue()
  vertQueue.enqueue(start)
  while (vertQueue.size() > 0):
    currentVert = vertQueue.dequeue()
    for nbr in currentVert.getConnections():
      if (nbr.getColor() == 'white'):
        nbr.setColor('gray')
        nbr.setDistance(currentVert.getDistance() + 1)
        nbr.setPred(currentVert)
        vertQueue.enqueue(nbr)
    currentVert.setColor('black')
*/
void MineSweeper::BFS(int y, int x)
{
    std::queue<Position *> pos_queue;
    pos_queue.push(&game_map[y][x]);
    while (!pos_queue.empty())
    {
        Position *cur_pos = pos_queue.front();
        pos_queue.pop();
        for (int i = 0; i < 9; i++)
        {
            int ty = cur_pos->y-1+i/3;
            int tx = cur_pos->x-1+i%3;
            if(ty >= 0 && ty < height &&
            tx >= 0 && tx < width &&
            (ty != cur_pos->y || tx != cur_pos->x)&& !game_map[ty][tx].discover) 
            {
                game_map[ty][tx].discover = true;
                if(game_map[ty][tx].num == 0)
                {                    
                    pos_queue.push(&game_map[ty][tx]);
                }
            }
        }
    }
}