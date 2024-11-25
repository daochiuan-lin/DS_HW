#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

//design your won Node using in Trie
class Node {
public:
    string str;
    vector<Node*> children;
    bool valid;
    Node(string text): str(text), valid(1){
        children.clear();
    }
    Node(): str(""), valid(0){
        children.clear();
    }
    int compare(string text){
        if(!str.size()) return 0;
        int i = 0;
        while(text[i] == str[i]){ 
            i++;
            if(i == text.size()){
                return -1; // parameter is shorter or same
            }
            if(i == str.size()){
                return -2; // str in node is shorter 
            }
        }
        return i; //different in str[i]
    }
    Node *scan(char ch){
        for(auto child : children){
            if(child->str.front() == ch) return child;
        }
        return nullptr;
    }
    void split(int i){
        if(i == str.size()) return;
        Node *node = new Node(str.substr(i));
        valid = 0;
        str = str.substr(0,i);
        children.swap(node->children);
        children.push_back(node);
    }
};

class Trie {
private:
    Node *root;
public:
    Trie() {
        root = new Node;
    }

    void insert(string str){
        Node *cur = root;
        while(true){
            Node *child = cur->scan(str.front());
            if(!child){
                cur->children.push_back(new Node(str));
                break;
            } 
            int i = child->compare(str);
            if(i == -1){// str is shorter than (or the same as) child
                child->split(str.size());
                child->valid = 1;
                break;
            }
            else if(i == -2){//child is shorter than str
                str = str.substr(child->str.size());
                cur = child;
            }
            else{ // i is the location of difference 
                child->split(i);
                child->children.push_back(new Node(str.substr(i)));
                break;
            }
        }
    }

    bool search(string substring) {
        Node *cur = root;
        while(true){
            cur = cur->scan(substring.front());
            if(!cur) return false;
            int i = cur->compare(substring);
            if(i == -2) substring = substring.substr(cur->str.size());
            else if(cur->str == substring && cur->valid) return true;
            else return false;
        }
    }

    void preorder(){
        cout << "[]" << endl;
        for(auto child : root->children){
            print(child,1);
        }
    }

    void print(Node *cur,int spaces){
        for(int i = 0; i < spaces; i++){
            cout << ' ';
        }
        cout << cur->str << endl;
        for(auto child : cur->children){
            print(child,spaces+1);
        }
    }

    ~Trie() {
        destruct(root);
    }
    void destruct(Node *node){
        for(auto child : node->children){
            destruct(child);
        }
        delete node;
    }
};

int main()
{
	Trie *trie = new Trie();
	string command, key, value;
	while(1)
	{
		cin>>command;
		if(command == "insert")
		{
			cin>>value;
			trie->insert(value);
		}
		else if(command == "search")
		{
			cin>>key;
			if(trie->search(key))
				cout << "exist" << endl;
			else
				cout << "not exist" << endl;
		}
		else if(command == "print")
		{
			trie->preorder();
		}
		else if(command == "exit")
		{
			break;
		}
	}
}
