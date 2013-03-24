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

int main(){
  int M,N;
  while(~scanf("%d %d",&M,&N)){

    int max_score = 0;
    for(int ppl_idx=0;ppl_idx<M;ppl_idx++){
      int sum = 0;
      for(int problem_idx =0;problem_idx<N;problem_idx++){
	int flag;
	scanf("%d",&flag);
	if(flag == 1) sum++;
      }
      max_score = max(sum,max_score);
    }

    printf("%d\n",max_score);
  }
}
