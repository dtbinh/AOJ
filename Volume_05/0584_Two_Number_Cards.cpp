#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#include <iostream>
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
#include <cstdio>

using namespace std;

typedef long long ll;
typedef pair <int,int> P;

static const double eps = 1e-8;

const int tx[4] = {+0,+1,+0,-1};
const int ty[4] = {-1,+0,+1,+0};

int main(){
  int n;
  while(~scanf("%d",&n)){
    priority_queue<int> que;
    for(int i = 0; i < n; i++){
      int num;
      scanf("%d",&num);
      que.push(num);
      while(que.size() > 4){
	que.pop();
      }
    }
    
    vector<int> cards;
    while(!que.empty()){
      cards.push_back(que.top());
      que.pop();
    }

    vector<int> res;
    for(int i = 0; i < cards.size(); i++){
      for(int j = 0; j < cards.size(); j++){
	if(i == j) continue;
	stringstream ss;
	ss << cards[i] << cards[j];
	res.push_back(atoi(ss.str().c_str()));
      }
    }
    sort(res.begin(),res.end());
    printf("%d\n",res[2]);
  }
}
