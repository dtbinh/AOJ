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
  
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};

int main(){
  int N;
  while(~scanf("%d",&N)){
    set<int> has_carpet;
    int count = 0;
    for(int i=0;i<N;i++){
      int height;
      scanf("%d",&height);
      count++;

      if(has_carpet.count(height)) count--;
      set<int>::iterator it = upper_bound(has_carpet.begin(),has_carpet.end(),height);
      has_carpet.erase(it,has_carpet.end());
      has_carpet.insert(height);
    }
    printf("%d\n",count);
  }
}
