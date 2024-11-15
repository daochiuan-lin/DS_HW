#include <bits/stdc++.h>
using namespace std;

template<class T>
class MinMaxHeap {
public:
    MinMaxHeap() {}
    //The insert function in a Min-Max Heap adds a new element to the heap while maintaining its unique properties.
    void insert(T value) {
        mmh.push_back(value);
        int i = mmh.size()-1;
        if(inMin(i) && mmh[i] > mmh[(i-1)/2]){
            swap(mmh[i],mmh[(i-1)/2]);
            i = (i-1)/2;
        }
        else if(!inMin(i) && mmh[i] < mmh[(i-1)/2]){
            swap(mmh[i],mmh[(i-1)/2]);
            i = (i-1)/2;
        }
        if(inMin(i)){
            while(1){
                if(mmh[i] >= mmh[((i-1)/2-1)/2]) break;
                swap(mmh[i],mmh[((i-1)/2-1)/2]);
                i = ((i-1)/2-1)/2;
            }
        }
        else{
            while(1){
                if(mmh[i] <= mmh[((i-1)/2-1)/2] || floor(log2(i+1)) == 1) break;
                swap(mmh[i],mmh[((i-1)/2-1)/2]);
                i = ((i-1)/2-1)/2;
            }
        }
    }
    // Retrieve the minimum element in the heap, throw an exception when heap is empty
    T getMin() const {
        if(mmh.empty()) throw runtime_error("it's empty");
        return mmh[0];
    }
    // Retrieve the maximum element in the heap, throw an exception when heap is empty
    T getMax() const {
        if(mmh.empty()) throw runtime_error("it's empty");
        if(mmh.size() < 3) return mmh[mmh.size()-1];
        return (mmh[1] > mmh[2])?mmh[1]:mmh[2];
    }
    // Delete the minimum element in the heap, throw an exception when heap is empty
    void deleteMin() {
        if(mmh.empty()) throw runtime_error("it's empty");
        swap(mmh[0],mmh[mmh.size()-1]);
        mmh.pop_back();
        int i = 0,m = 0;
        T curmin = mmh[i];
        while(1){
            for(int j = 1;j < 5;j++){
                if((i*2+1)*2+j >= mmh.size()) break;
                if(mmh[(i*2+1)*2+j] < curmin) {
                    m = j;
                    curmin = mmh[(i*2+1)*2+j];
                }
            }
            if(m == 0) break;
            swap(mmh[i],mmh[(i*2+1)*2+m]);
            i = (i*2+1)*2+m;
            m = 0;
        }
    }
    // Delete the maximum element in the heap, throw an exception when heap is empty
    void deleteMax() {
        if(mmh.empty()) throw runtime_error("it's empty");
        if(mmh.size() > 2){
            swap((mmh[1] > mmh[2])?mmh[1]:mmh[2],mmh[mmh.size()-1]);
        }
        mmh.pop_back();
        if(mmh.size() < 2) return;
        int i = (mmh[1] < mmh[2])?1:2 ,m = 0;
        T curmax = mmh[i];
        if(mmh.size() < 8){
            if(mmh[i] < mmh[i*2+1] && i*2+1 < mmh.size()) swap(mmh[i],mmh[i*2+1]);
            if(mmh[i] < mmh[i*2+2] && i*2+2 < mmh.size()) swap(mmh[i],mmh[i*2+2]);
            return;
        }
        while(1){
            m = 0;
            for(int j = 1;j < 5;j++){
                if((i*2+1)*2+j >= mmh.size()) break;
                if(mmh[(i*2+1)*2+j] > curmax) {
                    m = j;
                    curmax = mmh[(i*2+1)*2+j];
                }
            }
            if(m == 0) break;
            swap(mmh[i],mmh[(i*2+1)*2+m]);
            i = (i*2+1)*2+m;
        }
    }

    bool inMin(T i){
        if(static_cast<int>(floor(log2(i+1)))%2 == 0){
            return true;
        }
        return false;
    }
    
    void check(){
        for(int i = 0; i < mmh.size();i++) 
            cout << mmh[i] << ' ';
        cout << endl;
    }

private:
    //create any member you need to complete MinMaxHap
    std::vector<T> mmh;
};
int main() {
    MinMaxHeap<int> mmHeap;
    int j;
    srand(time(NULL));
    for(j = 0;j < 10;j ++)
      mmHeap.insert(rand() % 100);

    while(true) {
      try {
        std::cout << mmHeap.getMin() << " ";
        mmHeap.deleteMin();
      }
      catch(std::exception) {
        break;
      }
    }
    std::cout << std::endl;
    
    for(j = 0;j < 10;j ++)
      mmHeap.insert(rand() % 100);

    while(true) {
      try {
        std::cout << mmHeap.getMax() << " ";
        mmHeap.deleteMax();
      }
      catch(std::exception) {
        break;
      }
    }

    return 0;
}
