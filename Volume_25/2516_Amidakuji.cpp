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

bool check(const vector<int>& matrix,int freq[12],int W){
  for(int i=0;i<matrix.size();i++){
    if(matrix[i] != i) return false;
  }

  for(int i=0;i<W;i++){
    if(freq[i] != 0) return false;
  }
  return true;
}

int dfs(const vector<int>& matrix,
	const vector<int>& patterns,
	int freq[12],
	int W,int H,int height){
  if(height >= H){
    return H;
  }

  if(check(matrix,freq,W)){
    return height;
  }

  int res = H;
  for(int i=0;i<patterns.size();i++){
    vector<int> next = matrix;
    int S = patterns[i];
    int next_freq[12];
    memcpy(next_freq,freq,sizeof(int)*W);

    for(int j=0;j<=W-1;j++){
      if(S & (1<<j)){
	swap(next[j],next[j+1]);
	next_freq[j]--;
      }
    }
    res = min(res,dfs(next,patterns,next_freq,W,H,height+1));
  }
  return res;
}

int main(){
  int W,H;
  while(~scanf("%d %d",&W,&H)){
    vector<int> matrix;
    for(int i=0;i<W;i++){
      matrix.push_back(i);
    }

    int freq[12];
    memset(freq,0,sizeof(freq));

    for(int i=0;i<H;i++){
      int line;
      scanf("%d",&line);
      line--;
      swap(matrix[line],matrix[line+1]);
      freq[line]++;
    }
    
    vector<int> patterns;
    for(int S=0;S<=(1<<(W-1)) - 1;S++){
      bool isok = true;
      for(int prohibit=2;prohibit <= W;prohibit++){
	int base = (1<<prohibit) - 1;

	for(int pos = 0; pos + prohibit <= W; pos++){
	  if((base & S) == base) {
	    isok = false;
	    break;
	  }
	  base <<= 1;
	}
      }

      for(int pos=0;pos<W;pos++){
	if(freq[pos] <= 0 && (S & (1<<pos))){
	  isok = false;
	}
      }

      if(isok){
	patterns.push_back(S);
      }
    }

    printf("%d\n",dfs(matrix,patterns,freq,W,H,0));
  }
}
