#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#include <cstdio>
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
#include <cctype>
#include <utility>
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P > PP;

const static double EPS = 1e-12;

int main(){
  int num_of_shops;
  int num_of_restrictions;

  while(~scanf("%d %d",&num_of_shops,&num_of_restrictions)){
    int go[1002];
    int ref[1002];
    bool trap[1002];
    memset(go,-1,sizeof(go));
    memset(ref,-1,sizeof(ref));
    memset(trap,false,sizeof(trap));

    for(int restriction_i = 0; restriction_i < num_of_restrictions; restriction_i++){
      int to,from;
      scanf("%d %d",&to,&from);
      go[from] = to;
      ref[to] = from;
      trap[to] = true;
    }

    int pos = 0;
    int cost = 0;
    bool used[1002] = {};
    while(pos <= num_of_shops){
      if(go[pos] != -1){
	cost += abs(pos - go[pos]);
	pos = go[pos];
	continue;
      }
      for(int next = 0; next <= num_of_shops + 1; next++){
	if(used[next]) continue;
	if(trap[next] && !used[ref[next]]) continue;

	cost += next - pos;
	pos = next;
	break;
      }
      used[pos] = true;
    }
    printf("%d\n",cost);
  }
}
