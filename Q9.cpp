#include <iostream>
#include <cmath>

using namespace std;

template<class T>
class BinaryTreeInArray {
private:
  T *array;
  int height;
  int numOfElement;
  void resize(int size) {
    T *temp = new T[numOfElement];
    int j;
    for(j = 0;j < numOfElement;j ++)
      temp[j] = array[j];
    delete array;
    array = new T[static_cast<int>(pow(2, height + 1)) - 1];
    for(j = 0;j < numOfElement;j ++)
      array[j] = temp[j];
    height ++;
    delete temp;
  }
public:
  BinaryTreeInArray() : array(nullptr), height(0), numOfElement(0) {}
  void addElementAsCompleteTree(T data) {
    int cap = pow(2, height) - 1;
    if(numOfElement + 1 > cap)
      resize((cap + 1) * 2 - 1);
    array[numOfElement] = data;
    numOfElement ++;
    }
    void displayInorder(int i) {
      if(i<numOfElement){
          displayInorder(2 * i + 1);
          cout<<array[i]<<" ";
          displayInorder(2 * i + 2);
      }
    }
    void displayPreorder(int i) {
      if(i<numOfElement){
          cout<<array[i]<<" ";
          displayPreorder(2 * i +1);
          displayPreorder(2 * i +2);
      }
    }
    void displayPostorder(int i) {
      if(i<numOfElement){
          displayPostorder(2 * i +1);
          displayPostorder(2 * i +2);
          cout<<array[i]<<" ";
      }
    }
};

template<class T>
class BinaryTreeInLinkedList {
private:
  class TreeNode {
  private:
  public:
    TreeNode(T d) : data(d), left(nullptr), right(nullptr) {}
    TreeNode *left, *right;
    T data;
  };
  TreeNode *root;
  int numOfElement;
public:
  BinaryTreeInLinkedList() : root(nullptr), numOfElement(0) {}
  
  void addElementAsCompleteTree(T data) {
    if (!numOfElement) {
        root = new TreeNode(data);
        numOfElement++;
        return;
    }
    numOfElement++;    
    int height = floor(log2(numOfElement))+1;
    TreeNode *cur = root,*pre = nullptr;
    int low_bound = pow(2,height-1),up_bound = pow(2,height)-1;
    while(1){
        if(!cur){
            cur = new TreeNode(data);
            if(up_bound%2 == 0) pre->left = cur;
            else pre->right = cur;
            break;
        }
        int mid = (up_bound+low_bound)/2;
        if(numOfElement > mid) { //go right
            pre = cur;
            cur = cur->right;
            low_bound = mid++;
        }
        else { //left
            pre = cur;
            cur = cur->left;
            up_bound = mid;
        }
    }
  }
  void in(TreeNode *n){
    if(n){
        in(n->left);
        cout << n->data << ' ';
        in(n->right);
    }
  }
  void pre(TreeNode *n){
    if(n){
        cout << n->data << ' ';
        pre(n->left);
        pre(n->right);
    }
  }
  void post(TreeNode *n){
    if(n){
        post(n->left);
        post(n->right);
        cout << n->data << ' ';
    }
  }
  void displayInorder() {
    in(root);
  }
  void displayPreorder() {
    pre(root);
  }
  void displayPostorder() {
    post(root);
  }
};

int main()
{
  BinaryTreeInArray<int> *b = new BinaryTreeInArray<int>;
  BinaryTreeInLinkedList<int> *tree = new BinaryTreeInLinkedList<int>;
  int j, n;
  cin >> n;
  for(j = 0;j < n;j ++) {
    b->addElementAsCompleteTree(j);
    tree->addElementAsCompleteTree(j);
  }
  b->displayInorder(0);
  cout << endl;
  tree->displayInorder();
  cout << endl;
  b->displayPreorder(0);
  cout << endl;
  tree->displayPreorder();
  cout << endl;
  b->displayPostorder(0);
  cout << endl;
  tree->displayPostorder();
  cout << endl;
  return 0;
}
