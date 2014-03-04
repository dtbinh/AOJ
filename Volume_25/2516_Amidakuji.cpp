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
  int W,H;
  while(~scanf("%d %d",&W,&H)){
    vector<int> matrix;
    for(int i=0;i<W;i++){
      matrix.push_back(i);
    }
    vector<pair<int,int> > permutation;
    for(int i=0;i<H;i++){
      int line;
      scanf("%d",&line);
      line--;
      int lhs = matrix[line];
      int rhs = matrix[line+1];
      swap(matrix[line],matrix[line+1]);
      permutation.push_back(make_pair(min(lhs,rhs),max(lhs,rhs)));
    }

    bool used[16];
    memset(used,false,sizeof(used));
    
    int res = 0;

    for(int i=0;i<H;i++){
      if(used[i]) continue;
      int lhs = permutation[i].first;
      int rhs = permutation[i].second;
      for(int j=i+1;j<H;j++){
	if(lhs == permutation[j].first
	   && rhs == permutation[j].second){
	  used[i] = true;
	  used[j] = true;
	  break;
	}
      }
    }

    for(int i=0;i<H;i++){
      if(used[i]) continue;
      res++;
      used[i] = true;
      int bits = 0; 
      bits |= (1<<permutation[i].first);
      bits |= (1<<permutation[i].second);
      for(int j=i+1;j<H;j++){
	if(used[j]) continue;
	if(!(bits & (1<<permutation[j].first))
	   && !(bits & (1<<permutation[j].second))){
	  bits |= (1<<permutation[j].first);
	  bits |= (1<<permutation[j].second);
	  used[j] = true;
	}
      }
    }
    printf("%d\n",res);
  }
}
