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
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

char NextChar(char from,int count){
  return (from-'a' + count) % 26 + 'a';
}

int main(){
  int N;

  while(~scanf("%d",&N)){
    if(N==0) break;
    char buf[128];    
    scanf("%s",buf);

    vector<P> ops;
    for(int i=0;i<N;i++){
      int a,b;
      scanf("%d %d",&a,&b);
      ops.push_back(P(a,b));
    }
    reverse(ops.begin(),ops.end());
    for(int i=0;i<N;i++){
      int a = ops[i].first;
      int b = ops[i].second;
      int diff = abs(a-b);
      buf[a-1] = NextChar(buf[a-1],diff);
      buf[b-1] = NextChar(buf[b-1],diff);
      swap(buf[a-1],buf[b-1]);
    }
    printf("%s\n",buf);
  }
}
