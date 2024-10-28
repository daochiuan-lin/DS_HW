#include<iostream>
#include<cstdlib>
#include<ctime>

#define SIZE 10

using namespace std;

class Node
{
public:
	Node()
	{
		Node(0, 0);
	}
	Node(int r, int c)
	{
		row = r;
		col = c;
	}
	int getRow() { return row; }
	int getCol() { return col; }
	void setRow(int r)
	{
		if(r >= 0 && r < SIZE)
			row = r;
	}
	void setCol(int c)
	{
		if(c >= 0 && c < SIZE)
			col = c;
	}
private:
	int col, row;
};

class List
{
public:
	List()
	{
		top = 0;
	}
	/*
	function addElement
	Insert an element from list
	*/
	void addElement(int r, int c)
	{
	    data[top] = Node(r,c);
	    top++;
	}
	/*
	function removeElement
	remove an element from list and return a pointer point to the element.
	If list is empty, return NULL.
	*/
	Node *removeElement()
	{
	    if(top){
	        top--;
	        return &data[top];
	    }
	    return NULL;
	}
	void printList()
	{
		int j;
		for(j = 0;j < top;j ++)
		{
			cout<<"("<<data[j].getRow()<<", "<<data[j].getCol()<<")"<<endl;
		}
	}
private:
	Node data[SIZE * SIZE];
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
	Alocate a 2-D array with s * s sizes as the map of maze.
	Inside the maze where 0 represent empty space and 1 represent wall.
	[0][0] is start point and [s - 1][s - 1] is finish point.
	Randomly generate 20% wall in the maze.
	Make sure [0][0] and [s - 1][s - 1] are 0

	動態配置一個二維的陣列，大小是 s * s ，用這個陣列表示迷宮的地圖
	陣列中 0 的值表示可以移動的空間， 1 表示牆壁 
	[0][0] 的位置表示起點 [s - 1][s - 1] 的位置表示終點
	請在迷宮中加入 20% 的牆壁 
	然後確定起點跟終點都是可以移動的位置 
	*/
  	void allocArray(int ***p, int m, int n) {
  		*p = (int **)malloc(m * sizeof(int *));
  		int *arr = (int *)malloc(m * n * sizeof(int));
		for (int i = 0; i < m; i++) (*p)[i] = &arr[i*n];
	}
	void initMaze(int s)
	{
      allocArray(&maze,SIZE,SIZE);
      int build = SIZE*SIZE/5;
      while(build){
        int x = rand()%(SIZE*SIZE-2)+1;
        if(maze[x/SIZE][x%SIZE] == 1) continue;
        maze[x/SIZE][x%SIZE] = 1;
        build--;
      }
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
	bool trail(int r,int c,List *list){
	    if(r < 0 || c < 0 || r == SIZE || c == SIZE){
	        return 0;
	    } // border
	    list->addElement(r,c);
	    if(maze[r][c]) {
	        list->removeElement();
	        return 0;
	    }// wall
	    maze[r][c] = 1;
	    if(r == SIZE-1 && c == SIZE-1) {
	        return 1;
	    } // end
	    if(trail(r,c+1,list)) return 1;//right
	    if(trail(r+1,c,list)) return 1;//down
	    if(trail(r,c-1,list)) return 1;//left
	    if(trail(r-1,c,list)) return 1;//up
        list->removeElement();
	    return 0;
	}
	List *getPath()
	{
	    trail(0,0,&path);
	    return &path;
	}
	void printMaze()
	{
		int j, k;
		for(j = 0;j < SIZE;j ++)
		{
			for(k = 0;k < SIZE;k ++)
			{
				if(maze[j][k] == 0)
					cout<<"0"<<" ";
				else if(maze[j][k] == 1)
					cout<<"1"<<" ";
			}
			cout<<"\n";
		}
	}
private:
	int **maze;
	List path;
};

int main()
{
    srand(time(NULL));
	Maze *maze = new Maze();
	maze->printMaze();
	maze->getPath()->printList();
}
