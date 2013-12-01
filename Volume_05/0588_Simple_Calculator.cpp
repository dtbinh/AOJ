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

int main(){
  string element;
  queue<string> que;
  while(cin >> element){
    que.push(element);
  }

  int total = atoi(que.front().c_str());
  que.pop();
  while(!que.empty()){
    if(que.front() == "+"){
      que.pop();
      total += atoi(que.front().c_str());
      que.pop();
    }
    else if(que.front() == "-"){
      que.pop();
      total -= atoi(que.front().c_str());
      que.pop();
    }
    else if(que.front() == "*"){
      que.pop();
      total *= atoi(que.front().c_str());
      que.pop();
    }
    else if(que.front() == "/"){
      que.pop();
      total /= atoi(que.front().c_str());
      que.pop();
    }
    else{
      que.pop();
    }
  }
  printf("%d\n",total);
}
