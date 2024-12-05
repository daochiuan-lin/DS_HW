#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

template<class T>
class BinaryThreadedTreeNode {
public:
    T *data;
    BinaryThreadedTreeNode *left, *right;
    bool isThread;
    BinaryThreadedTreeNode(T d) : right(nullptr), left(nullptr) {
        data = new T {d};
    }
    BinaryThreadedTreeNode() : data(nullptr), right(nullptr), left(nullptr) {}
};

template<class T>
class BinarySearchThreadedTree : BinaryThreadedTreeNode<T> {
private:
    void CreateThread() {
        CreateThread(nullptr);
    }
    void CreateThread(BinaryThreadedTreeNode<T> *last){
        if(!this->data) {
            this->right = last;
            return;
        }
        static_cast<BinarySearchThreadedTree<T> *>(this->left)->CreateThread(this);
        static_cast<BinarySearchThreadedTree<T> *>(this->right)->CreateThread(last);
    }
public:
    BinarySearchThreadedTree() : BinaryThreadedTreeNode<T>() {}
    BinarySearchThreadedTree *insert(T d) {
        if(!this->data) {
            this->data = new T {d};
            this->left = new BinarySearchThreadedTree();
            this->right = new BinarySearchThreadedTree();
            return this;
        }
        else {
            if(*this->data > d)
                return (static_cast<BinarySearchThreadedTree<T> *>(this->left))->insert(d);
            else
                return (static_cast<BinarySearchThreadedTree<T> *>(this->right))->insert(d);
        }
    }
    void print() {
        this->CreateThread();
        BinaryThreadedTreeNode<T> *cur = this;
        while(cur){
            while(cur->data){
                cur = cur->left;
            }
            while(cur){
                if(!cur->data) {
                    cur = cur->right;
                    if(cur){
                        cout << *cur->data << ' ';
                        cur = cur->right;
                        break;
                    }
                }
                else{
                    cout << *cur->data << ' ';
                    cur = cur->right;
                }
            }
        }
    }
};

int main() {
    int j;
    BinarySearchThreadedTree<int> bstt;
    srand(time(nullptr));
    for(j = 0;j < 10;j ++){
        bstt.insert(rand() % 100);
    }
    bstt.print();
}
