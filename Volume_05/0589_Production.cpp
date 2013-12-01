#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f

#include <iostream>
#include <cstdio>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <stack>
#include <limits>
#include <map>
#include <string>
#include <cstring>
#include <set>
#include <deque>
#include <bitset>
#include <list>
#include <cctype>
#include <utility>
  
using namespace std;
  
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P> PP;
  
static const double EPS = 1e-8;
  
static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};

class Dict{
public:
  string key;
  int num;
  Dict(string _k,int _n) : key(_k), num(_n) {}
  bool operator<(const Dict& d) const{
    if(key.size() != d.key.size()){
      return key.size() < d.key.size();
    }
    else{
      return key < d.key;
    }
  }
  bool operator>(const Dict& d) const{
    if(key.size() != d.key.size()){
      return key.size() > d.key.size();
    }
    else{
      return key > d.key;
    }
  }
};

int main(){
  int n;
  while(~scanf("%d",&n)){
    map<string,int> freq;
    for(int i=0;i<n;i++){
      string key;
      int num;
      cin >> key >> num;
      freq[key] += num;
    }
    vector<Dict> dict;
    for(map<string,int>::iterator it = freq.begin(); it != freq.end(); it++){
      dict.push_back(Dict(it->first,it->second));
    }
    sort(dict.begin(),dict.end());
    for(int i=0;i<dict.size();i++){
      printf("%s %d\n",dict[i].key.c_str(),dict[i].num);
    }
  }
}
