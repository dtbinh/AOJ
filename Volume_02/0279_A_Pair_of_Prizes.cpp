#define _USE_MATH_DEFINES
#define INF 10000000
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>
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

using namespace std;

typedef long long ll;
typedef pair<int,string> P;

static const double EPS = 1e-8;

int main(){
  int N;
  while(~scanf("%d",&N)){
    if(N == 0) break;
    bool feed_flag = false;

    vector<int> prize;
    for(int i=0;i<N;i++){
      int capacity;
      scanf("%d",&capacity);
      prize.push_back(capacity);
      if(capacity >= 2) feed_flag = true;
    }

    int got[10001];
    memset(got,0,sizeof(got));
    
    int count = 0;
    for(int round = 0; round <= 100;round++){
      for(int i=0;i<N;i++){
	if(got[i] == 0 && prize[i] > 0){
	  got[i]++;
	  prize[i]--;
	  count++;
	}
      }
    }

    
    if(!feed_flag){
      printf("NA\n");
    }
    else{
      printf("%d\n",count + 1);
    }
  }
}
