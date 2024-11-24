#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>



//design your won SuffixTreeNode using in SuffixTree
class SuffixTreeNode {
public:
    std::string str;
    std::vector<SuffixTreeNode*> children;
    int used;
    SuffixTreeNode(std::string text): str(text), used(1){
        children.clear();
    }
    SuffixTreeNode(): str(""), used(0){
        children.clear();
    }
    int compare(std::string text){
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
    SuffixTreeNode *scan(char ch){
        for(auto child : children){
            if(child->str.front() == ch) return child;
        }
        return nullptr;
    }
    void split(int i){
        if(i == str.size()) return;
        SuffixTreeNode *node = new SuffixTreeNode(str.substr(i));
        node->used = used;
        str = str.substr(0,i);
        children.swap(node->children);
        children.push_back(node);
    }
};

class SuffixTree {
private:
    SuffixTreeNode *root;
    std::string text;
public:
    SuffixTree(const std::string &text) : text(text) {
        root = new SuffixTreeNode;
        for(int i = 0; i < text.length() ; i++){
            std::string str = text.substr(i);
            SuffixTreeNode *cur = root;
            while(true){
                SuffixTreeNode *child = cur->scan(str.front());
                if(!child){
                    cur->children.push_back(new SuffixTreeNode(str));
                    break;
                } 
                int i = child->compare(str);
                if(i == -1){// str is shorter than (or the same as) child
                    child->split(str.size());
                    child->used++;
                    break;
                }
                else if(i == -2){//child is shorter than str
                    str = str.substr(child->str.size());
                    child->used++;
                    cur = child;
                }
                else{ // i is the location of difference 
                    child->split(i);
                    child->children.push_back(new SuffixTreeNode(str.substr(i)));
                    child->used++;
                    break;
                }
            }
        }
    }

    bool exist(std::string substring) {
        SuffixTreeNode *cur = root;
        while(true){
            cur = cur->scan(substring.front());
            if(!cur) return false;
            int i = cur->compare(substring);
            if(i > 0) return false;
            if(i == -1) return true;
            if(i == -2) substring = substring.substr(cur->str.size());
        }
    }

    int count(std::string substring) {
                SuffixTreeNode *cur = root;
        while(true){
            cur = cur->scan(substring.front());
            if(!cur) return 0;
            int i = cur->compare(substring);
            if(i > 0) return 0;
            if(i == -1) return cur->used;
            if(i == -2) substring = substring.substr(cur->str.size());
        }
    }

    ~SuffixTree() {
        destruct(root);
    }
    void destruct(SuffixTreeNode *node){
        for(auto child : node->children){
            destruct(child);
        }
        delete node;
    }
};

int main() {
    std::string text = "";
    while(true) {
      std::string temp;
      getline(std::cin, temp);
      if(temp == "")
        break;
      text += temp;
    }
    SuffixTree tree(text);

    std::string query;
    while(true) {
      getline(std::cin, query);
      if(query == "")
        break;
      std::cout << "Existence of '" << query << "': " << (tree.exist(query) ? "Yes" : "No") << std::endl;
      std::cout << "Count of '" << query << "': " << tree.count(query) << std::endl;
    }
    return 0;
}
