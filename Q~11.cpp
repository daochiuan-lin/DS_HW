#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

template<class T>
class BinarySearchTree {
private:
  struct Node {
    T data;
    Node *left, *right;
  };
  void inorder(Node *cur) {
    if(!cur)
      return;
    inorder(cur->left);
    cout << cur->data << " ";
    inorder(cur->right);
  }
  Node *root;
public:
  BinarySearchTree() : root(nullptr) {}
  void insertElement(T d) {
    if(root == nullptr){
    	Node *node = new Node;
        root = node;
        node->data = d;
        return;
    }
    Node *cur = root; 
    while(true){
        if(d > cur->data && cur->right){
            cur = cur->right;
        }
        else if(d > cur->data){
            Node *node = new Node;
            cur->right = node;
            node->data = d;
            break; 
        }
        else if(d <= cur->data && cur->left){
            cur = cur->left;
        }
        else{
            Node *node = new Node;
            cur->left = node;
            node->data = d;
            break;
        }
    }
  }
  void print() {
    inorder(root);
    cout << endl;
  }
  bool search(T d) {
    Node *cur = root;
    while(1){
        if(d == cur->data) return true;
        if(d <= cur->data && !cur->left) return false;
        if(d > cur->data && !cur->right) return false;
        if(d <= cur->data){
            cur = cur->left;
            continue;
        }
        if(d > cur->data) cur = cur->right;
    }
  }
  int height() {
    return height(root,0);
  }
  int height(Node *n,int h) {
    if(!n) return h;
    return max(height(n->left,h+1),height(n->right,h+1));
  }
};

int main() {
  int data;
  string command;
  BinarySearchTree<int> *bst = new BinarySearchTree<int>();
  while(true) {
    cin >> command;
    if(command == "insert") {
      cin >> data;
      bst->insertElement(data);
    }
    else if(command == "search") {
      cin >> data;
      if(bst->search(data))
        cout << "true" << endl;
      else
        cout << "false" << endl;
    }
    else if(command == "height") {
      cout << bst->height() << endl;
    }
    else if(command == "print") {
      bst->print();
    }
    else if(command == "exit") {
      break;
    }
  }
}
