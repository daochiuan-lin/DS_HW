#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>
#include <queue>
using namespace std;


class ExpressionTree {
private:
    struct Node {
        std::string value;
        Node* left;
        Node* right;
        Node* parent;
        Node(const std::string& val) : value(val), left(nullptr), right(nullptr), parent(nullptr){}
    };

    Node* root;

public:
    //Constructor of class ExpressionTree take a string as an infix expression and build the expression tree base on that.
    //there are five different operation you have to consider, +(addition), -(subtraction), *(multiplication), /(division) and %(modulus).
    //you also need to consider -(negative) sign.
    //all operands are integer
    ExpressionTree(const std::string &expression) {
        std::stringstream ss(expression);
        root = insert(ss,NULL);
    }
    Node* insert(std::stringstream &ss,Node* subTreeRoot){
        std::string str;
        ss >> str;
        Node *n;
        try{
            std::stoi(str); //string to int
            n = new Node(str);
        }
        catch(std::invalid_argument){ // "("
            n = insert(ss,NULL);
        }
        if(ss >> str){
            if(str == ")") return n;
            Node *op = new Node(str);
            if(str == "+" || str == "-"){
                if(subTreeRoot){ // after */%
                    op->left = subTreeRoot;
                    op->left->parent = op;
                    op->right = insert(ss,NULL);
                    op->right->parent = op;
                    return n;
                }
                op->left = n; // solo +-
                op->left->parent = op;
                op->right = insert(ss,NULL);
                op->right->parent = op;
                return op;
            }
            if(str == "*" || str == "/"){
                op->left = n;
                op->left->parent = op;
                if(subTreeRoot){
                    op->right = insert(ss,subTreeRoot);
                    op->right->parent = op;
                }
                else{
                    op->right = insert(ss,op);
                    op->right->parent = op;
                }
                if(op->parent) return op->parent;
                return op;
            }
            if(str == "%"){
                    op->left = subTreeRoot;
                    op->left->parent = op;
                    op->right = insert(ss,op);
                    op->right->parent = op;
                    return n;
            }
        }
        return n;
    }
    ~ExpressionTree() { deleteTree(root); }

    void deleteTree(Node* node) {
        if (node == nullptr) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
    //print all element in infix order.
    void printInFixOrder() {
        printInFixOrder(root);
        cout << endl;
    }
    void printInFixOrder(Node *n) {
        if(!n) return;
        try{
            std::stoi(n->value); //string to int
            std::cout << n->value << ' ';
        }
        catch(std::invalid_argument){ // "("
            std::cout << '(';
            printInFixOrder(n->left);
            std::cout << n->value << ' ';
            printInFixOrder(n->right);  
            std::cout << ')';
        }
    }
    //print all element in prefix order.
    void printPreFixOrder() {
        printPreFixOrder(root);
        cout << endl;
    }
    
    void printPreFixOrder(Node *n) {
        if(!n) return;
        try{
            std::stoi(n->value); //string to int
            std::cout << n->value << ' ';
        }
        catch(std::invalid_argument){ // "("
            std::cout << n->value << ' ';
            printPreFixOrder(n->left);
            printPreFixOrder(n->right);
        }
    }
    //print all element in postfix order.
    void printPostFixOrder() {
        printPostFixOrder(root);
        cout << endl;
    }
    void printPostFixOrder(Node *n) {
        if(!n) return;
        try{
            std::stoi(n->value); //string to int
            std::cout << n->value << ' ';
        }
        catch(std::invalid_argument){ // "("
            printPostFixOrder(n->left);
            printPostFixOrder(n->right);
            std::cout << n->value << ' ';
        }
    }
    //evaluate the expression, this function return an int sience % can only work with integer in C
    int eval() {
        return evaluate(root);
        cout << endl;
    }
    int evaluate(Node *node){
        try{
            int i = std::stoi(node->value);
            return i;
        }
        catch(std::invalid_argument){
            int A = evaluate(node->left);
            int B = evaluate(node->right);
            switch(node->value[0]){
                case '+':
                    return A+B;
                case '-':
                    return A-B;
                case '*':
                    return A*B;
                case '/':
                    return A/B;
                case '%':
                    return A%B;
            }
        }
        return 0;
    }
};

int main() {
    std::string infix = "( -12 + 3 ) * 4 % 5";
    ExpressionTree exprTree(infix);

    std::cout << "Inorder: ";
    exprTree.printInFixOrder();
    std::cout << "Preorder: ";
    exprTree.printPreFixOrder();
    std::cout << "Postorder: ";
    exprTree.printPostFixOrder();
    std::cout << "Evaluated result: " << exprTree.eval() << std::endl;

    return 0;
}
