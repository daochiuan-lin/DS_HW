#include <iostream> //1111111
#include <cmath>
#include <vector>

using namespace std;

template<class T>
class TreeInLinkedList {
private:
  class TreeNode {
  private:
  public:
    TreeNode(T d, TreeNode *p) : data(d), parent(p) {}
    TreeNode *parent;
    T data;
  };
  vector<TreeNode *> *nodeList;
public:
  TreeInLinkedList() {
    nodeList = new vector<TreeNode *>();
  }
  void addElement(T data) {
    int j, k = nodeList->size();
    if(data == 1) {
      nodeList->clear();
      nodeList = new vector<TreeNode *>();
      TreeNode *newNode = new TreeNode(data, nullptr);
      nodeList->push_back(newNode);
    }
    else {
      for(j = 0;j < k;j ++) {
        if(data % (*nodeList)[j]->data == 0) {
          TreeNode *newNode = new TreeNode(data, (*nodeList)[j]);
          nodeList->push_back(newNode);
        }
      }
    }
  }
  void displayPreorder() {
    displayPreorder(0);
  }
  void displayPreorder(int i){
    cout << (*nodeList)[i]->data << ' ';
    for(int j = i+1;j < nodeList->size();j++){
        if((*nodeList)[j]->parent == (*nodeList)[i]){
            displayPreorder(j);
        }
    }
  }
  void displayPostorder() {
    displayPostorder(0);
  }
  void displayPostorder(int i){
    for(int j = i+1;j < nodeList->size();j++){
        if((*nodeList)[j]->parent == (*nodeList)[i]){
            displayPostorder(j);
        }
    }
    cout << (*nodeList)[i]->data << ' ';
  }
};

int main()
{
  TreeInLinkedList<int> *tree = new TreeInLinkedList<int>();
  int j;
  int n;
  cin >> n;
  for(j = 1;j <= n;j ++)
    tree->addElement(j);
  tree->displayPreorder();
  cout << endl;
  tree->displayPostorder();
  cout << endl;
}
