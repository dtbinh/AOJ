#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
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

int main(){
  int total_pipes;
  while(~scanf("%d",&total_pipes)){
    if(total_pipes == 0) break;

    unsigned int sum = 0;
    for(int i=0;i<total_pipes;i++){
      int pipe;
      scanf("%d",&pipe);
      sum += pipe;
    }

    int total_joins = total_pipes - 1;

    vector<int> joins;
    for(int i=0;i<total_joins;i++){
      int join;
      scanf("%d",&join);
      sum += join;
      joins.push_back(join);
    }

    sort(joins.begin(),joins.end());
    unsigned int res = sum;
    for(int pipe_num=2,join_idx=0;pipe_num <= total_pipes; pipe_num++,join_idx++){
      sum -= joins[join_idx];
      res = max(sum * pipe_num,res);
    }
    printf("%u\n",res);
  }
}
