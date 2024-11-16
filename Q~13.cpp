#include <bits/stdc++.h>
using namespace std;

template<class T>
class MaxHeap {
public:
  //Constructing a empty heap.
  MaxHeap(){}
  //To add an element to the heap.
  void insert(T n){
    mh.push_back(n);
    int i = mh.size()-1;
    while(true){
      if(mh[i] <= mh[(i+1)/2]) break;
      swap(mh[i],mh[(i+1)/2]);
      i = (i+1)/2;
    }
  }
  //To remove the root element in the heap and return it.
  T extract(){
    swap(mh[0],mh[mh.size()-1]);
    T r = mh.back();
    mh.pop_back();
    int i = 0;
    while(i*2+1 > mh.size()-1){
      int t;
      if(i*2+2 > mh.size()-1) t = i*2+1;
      else t = (mh[i*2+1] > mh[i*2+2])?i*2+1:i*2+2;
      if(mh[t] < mh[i]) break;
      swap(mh[i],mh[t]);
      i = t;
    }
    return r;
  }
  //Return the number of element int the heap.
  int count(){
    return mh.size();
  }
private:
  std::vector<T> mh;
};
