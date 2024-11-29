//PREPEND BEGIN
/*some text*/
//PREPEND END

//TEMPLATE BEGIN
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <ctime>
using namespace std;

template<class T>
class Node
{
public:
	Node()
	{
		data = new T;
	}
	Node(T d)
	{
		data = new T;
		(*data) = d;
	}
	Node &operator=(T d)
	{
		(*data) = d;
		return *this;
	}
	friend std::ostream &operator<<(std::ostream &out, Node n)
	{
		out<<*(n.data);
		return out;
	}
	friend std::ostream &operator<<(std::ostream &out, Node *n)
	{
		out<<*(n->data);
		return out;
	}
	void setData(T d)
	{
		*data = d;
	}
	T &getData() const
	{
		return *data;
	}
protected:
	T *data;
};

template<class T>
class BinaryTreeNode : public Node<T>
{
public:
	BinaryTreeNode() : Node<T>()
	{
		left = NULL;
		right = NULL;
	}
	BinaryTreeNode(T d) : Node<T>(d)
	{
		left = NULL;
		right = NULL;
	}
	BinaryTreeNode(BinaryTreeNode<T> *l, BinaryTreeNode<T> *r) : Node<T>()
	{
		left = l;
		right = r;
	}
	BinaryTreeNode(T d, BinaryTreeNode<T> *l, BinaryTreeNode<T> *r) : Node<T>(d)
	{
		left = l;
		right = r;
	}
	void setLeft(BinaryTreeNode<T> *l)
	{
		left = l;
	}
	void setRight(BinaryTreeNode<T> *r)
	{
		right = r;
	}
	BinaryTreeNode<T> *&getLeft()
	{
		return left;
	}
	BinaryTreeNode<T> *&getRight()
	{
		return right;
	}
	bool operator>(BinaryTreeNode<T> n)
	{
		if(*(this->data) > *(n.data))
			return true;
		return false;
	}
	bool operator==(BinaryTreeNode<T> n)
	{
		if(*(this->data) == *(n.data))
			return true;
		return false;
	}
private:
	BinaryTreeNode<T> *left, *right;
};

template<class T>
class AVLTree
{
private:
  BinaryTreeNode<T> *root;
  void inorder(BinaryTreeNode<T> *cur, int n)
  {
    if(cur == NULL)
      return;
    inorder(cur->getRight(), n + 1);
    int j;
    for(j = 0;j < n;j ++)
      cout << "  ";
    cout << cur << endl;
    inorder(cur->getLeft(), n + 1);
  }
public:
  AVLTree() : root(nullptr) {}
  void insert(T d) {
    BinaryTreeNode<T> *node = new BinaryTreeNode<T>(d);
    if(root == nullptr){
        root = node;
        return;
    }
    BinaryTreeNode<T> *cur = root; 
    while(true){
      if(d > cur->getData() && cur->getRight()){
        cur = cur->getRight();
      }
      else if(d > cur->getData()){
        cur->getRight() = node;
        node->getData() = d;
        break; 
      }
      else if(d < cur->getData() && cur->getLeft()){
        cur = cur->getLeft();
      }
      else if (d < cur->getData()){
        cur->getLeft() = node;
        node->getData() = d;
        break;
      }
      else{
        delete node;
        return;
      }
    }
    int i = balance(root,d);
    if(i < 0 && i%2) root = rotateR(root,d);
    else if(i < 0 && !(i%2)) root = rotateL(root,d);
  }

  int balance(BinaryTreeNode<T> *n,T d){
    if(!n) return 0;
    int lh = balance(n->getLeft(),d),rh = balance(n->getRight(),d);
    if(lh < 0){
		if(lh%2) n->setLeft(rotateR(n->getLeft(),d));
		else n->setLeft(rotateL(n->getLeft(),d));
		lh = lh/(-2);
	}
	else if (rh < 0){
		if(rh%2) n->setRight(rotateR(n->getRight(),d));
		else n->setRight(rotateL(n->getRight(),d));
		rh = rh/(-2);
	}
	if(lh > rh+1) return -(lh + rh) - 1; //rotateR
	if(rh > lh+1) return -(lh + rh);
    return (lh>rh)?lh+1:rh+1;
  }

  BinaryTreeNode<T> *rotateR(BinaryTreeNode<T> *n,T d){
    BinaryTreeNode<T> *top;
    if (d < n->getLeft()->getData()){ // LL(left is higher, new node placed at left's left)
      top = n->getLeft();
      n->setLeft(top->getRight());
      top->setRight(n);
      return top;
    }
    top = n->getLeft()->getRight();// LR
    n->getLeft()->setRight(top->getLeft());
    top->setLeft(n->getLeft());
    n->setLeft(top->getRight());
    top->setRight(n);
    return top;
  }

  BinaryTreeNode<T> *rotateL(BinaryTreeNode<T> *n,T d){
    BinaryTreeNode<T> *top;
    if (d > n->getRight()->getData()){ // RR
      top = n->getRight();
      n->setRight(top->getLeft());
      top->setLeft(n);
      return top;
    }
    top = n->getRight()->getLeft();// LR
    n->getRight()->setLeft(top->getRight());
    top->setRight(n->getRight());
    n->setRight(top->getLeft());
    top->setLeft(n);
    return top;
  }

  void inorder(){
    inorder(root, 0);
  }
};

int main()
{
	AVLTree<int> *tree = new AVLTree<int>;
	srand(0);
	int j, k, i;
	for(j = 0;j < 20;j ++)
	{
		tree->insert(rand() % 100);
	}
	tree->inorder();
}
