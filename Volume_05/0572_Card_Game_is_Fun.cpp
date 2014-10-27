#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#include <iostream>
#include <sstream>
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
#include <cstdio>

using namespace std;

typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P> PP;
typedef pair <int,PP> PPP;

static const double eps = 1e-8;

int dp[5001][5001];

int main(){
  int num_of_A,num_of_B;
  while(~scanf("%d %d",&num_of_A,&num_of_B)){
    int A[5001];
    int B[5001];
    for(int i = 0; i < num_of_A; i++){
      scanf("%d",A + i);
    }
    for(int i = 0; i < num_of_B; i++){
      scanf("%d",B + i);
    }


    int res = 0;
    for(int start = 0; start < num_of_B; start++){
      int j = 0;
      for(int i = start; i < num_of_B;){
	for(; j < num_of_A; j++){
	  if(B[i] == A[j]){
	    i++;
	    res = max(res,i - start);
	  }
	}
	break;
      }
    }

    printf("%d\n",res);
  }
}
