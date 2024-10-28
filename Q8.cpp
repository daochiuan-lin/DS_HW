#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

#define SIZE 10
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

class Grid
{
public:
	Grid()
	{
		Grid(0);
	}
	Grid(int s)
	{
		state = s;
		dir[UP] = NULL;
		dir[DOWN] = NULL;
		dir[LEFT] = NULL;
		dir[RIGHT] = NULL;
	}
	Grid *getDir(int d) { return dir[d]; }
	int getState() { return state; }
	void setDir(int d, Grid *g) { dir[d] = g; }
	void setState(int s) { state = s;}
private:
	Grid *dir[4];
	int state;
};

struct List
{
public:
	List()
	{
		top = 0;
	}
	/*
	Insert an element from top
	*/
	void addElement(Grid *g)
	{
	    data[top] = g;
	    top++;
	}
	/*
	remove an element from top and return a pointer point to the element.
	If list is empty, return NULL.
	*/
	Grid *removeElement()
	{
	    if(top){
	        top--;
	        return data[top];
	    }
	    return NULL;
	}
	void printPath()
	{
		int j;
		for(j = 1;j < top;j ++)
		{
			if(data[j] == data[j - 1]->getDir(UP))
			{
				cout<<"UP\n";
			}
			else if(data[j] == data[j - 1]->getDir(DOWN))
			{
				cout<<"DOWN\n";
			}
			else if(data[j] == data[j - 1]->getDir(LEFT))
			{
				cout<<"LEFT\n";
			}
			else if(data[j] == data[j - 1]->getDir(RIGHT))
			{
				cout<<"RIGHT\n";
			}
		}
	}
private:
	Grid *data[SIZE * SIZE];
	int top;
};

class Maze
{
public:
	Maze()
	{
		initMaze(SIZE);
	}
	/*
	function initMaze
	Alocate a 2-D link list with s * s sizes as the map of maze.
	Inside the maze enery gird with state 0 represent empty space and 1 represent wall.
	The gird in left top is start point and right bottom is finish point.
	Randomly generate 20% wall in the maze.
	Make sure start point and finish point are 0

	動態配置一個二維的鏈結串列，大小是 s * s，用這個鏈結串列表示迷宮的地圖
	節點中 0 的值表示可以移動的空間， 1 表示牆壁 
	左上角的位置表示起點，右下角的位置表示終點
	請在迷宮中加入 20% 的牆壁 
	然後確定起點跟終點都是可以移動的位置 
	*/
    void initMaze(int s)
    {
        Grid *temp[s][s];
        for(int i = 0; i < s; i++){
            for(int j = 0; j < s; j++){
                temp[i][j] = new Grid();
                if(i) {
                    temp[i][j]->setDir(UP,temp[i-1][j]);
                    temp[i-1][j]->setDir(DOWN,temp[i][j]);
                }
	            if(j) {
	                temp[i][j]->setDir(LEFT,temp[i][j-1]);
                    temp[i][j-1]->setDir(RIGHT,temp[i][j]);
	            }
	            }
	    }
	    maze = temp[0][0];
	    int build = SIZE*SIZE/5;
	    while(build--){
            int x = rand()%(SIZE*SIZE-2)+1;
            if(temp[x/SIZE][x%SIZE]->getState()) continue;
            temp[x/SIZE][x%SIZE]->setState(1);
	    }
	    maze = temp[0][0];
	    
	}
	/*
	function getPath
	This function will find a path between start point and finish point.
	Return a list content the path information inside.
	If there is no path between two point then the list will be empty.

	這個函數會找到起點到終點間的一條路徑
	回傳一個 list 包含著路徑的資訊
	如果找不到路徑的話 list 就會是空的 
	*/
	bool trail(Grid *grid,List *list){
	    if(!grid){
	        return 0;
	    } // border
	    list->addElement(grid);
	    if(grid->getState()) {
	        list->removeElement();
	        return 0;
	    }// wall
	    grid->setState(1);
	    if(!grid->getDir(DOWN) && !grid->getDir(RIGHT)) {
	        return 1;
	    } // end
	    if(trail(grid->getDir(RIGHT),list)) return 1;//right
	    if(trail(grid->getDir(DOWN),list)) return 1;//down
	    if(trail(grid->getDir(LEFT),list)) return 1;//left
	    if(trail(grid->getDir(UP),list)) return 1;//up
	    list->removeElement();
	    return 0;
	}
	List *getPath()
	{
	    trail(maze,&path);
	    return &path;
	}
	void printMaze()
	{
		Grid *j = maze, *k;
		while(j != NULL)
		{
			k = j;
			while(k != NULL)
			{
				cout<<k->getState();
				k = k->getDir(RIGHT); 
			}
			cout<<endl;
			j = j->getDir(DOWN);
		}
	}
private:
	Grid *maze;
	List path;
};

int main()
{
    srand(time(NULL));
	Maze *maze = new Maze();
	maze->printMaze();
	maze->getPath()->printPath();
}
