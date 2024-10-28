#include <iostream>
#include <cstring>

#define SIZE 100

using namespace std;

class Queue
{
private:
    bool isFull() const {
      if(length == SIZE) return true;
      return false;
    }
    bool isEmpty() const {
      if (length == 0) return true;
      return false;
    }
    int nextTop() const {
      if(top == SIZE) return 1;
      return top + 1;
    }
    int nextBot() const {
      if(bot+2 == SIZE) return -1;
    return bot + 1;
    }
public:
    Queue()
    {
        top = 0;
        bot = -1;
        length = 0;
    }
    int enqueue(int val)
    {
       if (isFull())
           return -1;
       top = nextTop();
       data[top-1] = val;
       length++;
       return 1;
    }
    int *dequeue()
    {
       if (isEmpty())
           return nullptr;
       int *data_loc = &data[bot+1];
       bot = nextBot();
       length--;
       return data_loc;
    }
    void print(){
        cout << '[';
        for(int i = 0 ; i < SIZE ; i++){
            cout << data[i] << ',';
        }
        cout << ']' << " top:" << top << " bot:" << bot << " length:" <<length<<endl;
    }
private:
    int length;
    int data[SIZE];
    int top, bot;
};

int main()
{
    int data, *temp;
    char command[50];
    Queue *queue = new Queue();
    while(1)
    {
        cin>>command;
        if(strcmp(command, "exit") == 0)
        {
            break;
        }
        else if(strcmp(command, "enqueue") == 0)
        {
            cout<<"Please input a integer data:";
            cin>>data;
            if(queue->enqueue(data) == 1)
            {
                cout<<"Successfully enqueue data "<<data<<" into queue."<<endl;
            }
            else
            {
                cout<<"Failed to enqueue data into queue."<<endl;
            }
        }
        else if(strcmp(command, "dequeue") == 0) 
        {
            temp = queue->dequeue();
            if(temp == NULL)
            {
                cout<<"Failed to dequeue a data from queue.\n";
            }
            else
            {
                cout<<"Dequeue data "<<*temp<<" from queue."<<endl;
            }
        }
        queue->print();
        cout << endl;
    }
}
