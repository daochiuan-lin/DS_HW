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
	                flag = false;//cp = 1(cur pre),cur = 2,target = 3,tn = 4(target next);
	                Node *target = cur->getNext(),*tn = cur->getNext()->getNext(),*cp = cur->getPre();
	                if(cp) cp->setNext(target);
	                cur->setNext(tn);
	                target->setNext(cur);
	                if(tn) tn->setPre(cur);
	                target->setPre(cp);
	                cur->setPre(target);
	                if(cur == list) list = target;
	                cur = target;
	            }
	            cur = cur->getNext();
	        }
	        if(flag) break;
	    }
	}
	
	void selectionSort()
	{
	    Node *cur = list;
	    bool flag = true;
	    while(cur->getNext() != NULL){
	        
            Node *target = cur->getNext(),*min = cur;
            while(target){
                if(min->getData() > target->getData()) min = target;
	            target = target->getNext();
	        }
	        if(min < cur){
                if(min->getPre()) min->getPre()->setNext(min    ->getNext());
                if(min->getNext()) min->getNext()->setPre(min    ->getPre());//slice down min
                if(cur->getPre()){//put it infront of cur
                    cur->getPre()->setNext(min);
                    min->setPre(cur->getPre());
                }
                min->setNext(cur);
                cur->setPre(min);
	        }
            if(flag){
                list = min;
                flag = false;
            }
	        cur = min->getNext();
	    }
	    
	    
	}
	
	void insertionSort()
	{
	    Node *cur = list->getNext();
	    while(cur != NULL){
	        Node *target = cur;
	        while(target->getPre()->getData() > cur->getData()){
	            target = target->getPre();
	            if(target->getPre() == NULL) break;
	        }
	        Node *hold = cur->getNext();
	        if(target != cur){
	            cur->getPre()->setNext(cur->getNext());
	            if(cur->getNext())cur->getNext()->setPre(cur->getPre());
	            cur->setPre(target->getPre());
	            if(cur->getPre()) cur->getPre()->setNext(cur);
	            else list = cur;
	            cur->setNext(target);
	            cur->getNext()->setPre(cur);
	        }
	        cur = hold;
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
	cout << "end" << endl;
}
