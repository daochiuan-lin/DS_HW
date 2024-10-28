#include <iostream>
#include <cstdlib>
#include <ctime>

#define SIZE 100

using namespace std;

class Node
{
public:
	Node()
	{
		next = NULL;
		pre = NULL;
	}
	Node(int n)
	{
		data = n;
		next = NULL;
		pre = NULL;
	}
	int getData() { return data; }
	Node *getNext() { return next; }
	Node *getPre() { return pre; }
	void setData(int d) { data = d; }
	void setNext(Node *n) { next = n; }
	void setPre(Node *p) { pre = p; }
private:
	int data;
	Node *next, *pre; 
};

class List
{
public:
	List() { list = NULL; }
	List(int n) { generate(n); }
	
	void generate(int n)
	{
		int j;
		list = NULL;
		for(j = 0;j < n;j ++)
			generate();
	}
	
	void generate()
	{
		Node *buf = new Node(rand()%10);
		buf->setNext(list);
		if(list != NULL)
			list->setPre(buf);
		list = buf;
	}
	
    void bubbleSort()
    {
        while(true){
	        Node *cur = list;
	        bool flag = true;
	        while(cur->getNext() != NULL){
	            if(cur->getData() > cur->getNext()->getData()){
	                int temp = cur->getData();
	                cur->setData(cur->getNext()->getData());
	                cur->getNext()->setData(temp);
	                flag = false;
	            }
	            cur = cur->getNext();
	        }
	        if(flag) break;
	    }
	}
	
	void selectionSort()
	{
	    Node *cur = list;
	    while(cur->getNext() != NULL){
            Node *target = cur->getNext();
            while(target != NULL){
                if(cur->getData() > target->getData()){
                    int temp = cur->getData();
	                cur->setData(target->getData());
	                target->setData(temp);
                }
	            target = target->getNext();
	        }
	        cur = cur->getNext();
	    }
	}
	
	void insertionSort()
	{
	    Node *cur = list->getNext();
	    while(cur != NULL){
	        Node *target = cur->getPre();
	        while(target->getData() > target->getNext()->getData()){
	            int temp = target->getData();
	            target->setData(target->getNext()->getData());
	            target->getNext()->setData(temp);
	            if(target->getPre() == NULL) break;
	            target = target->getPre();
	        }
	        cur = cur->getNext();
	    }
	} 
	
	void print()
	{
		Node *cur = list;
		while(cur != NULL)
		{
			cout<<cur->getData()<<" ";
			cur = cur->getNext();
		}
		cout<<endl;
	}
private:
	Node *list;
};

int main()
{
	srand(time(NULL));
	List *l = new List(7);
	l->print();
	l->bubbleSort();
	l->print();
	cout << endl;
	
	l = new List(7);
	l->print();
	l->selectionSort();
	l->print();
	cout << endl;
		
	l = new List(7);
	l->print();
	l->insertionSort();
	l->print();
}
