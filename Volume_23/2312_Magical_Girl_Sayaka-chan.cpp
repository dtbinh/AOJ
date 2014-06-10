#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
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
 
const static int tx[] = {0,1,1,1,0,-1,-1,-1};
const static int ty[] = {-1,-1,0,1,1,1,0,-1};
 
static const double EPS = 1e-8;


int num_of_notes;
int num_of_beauty;
ll force_of_repulsion;
ll sum[200001];
ll dp[2001][2001];
int notes[2001];
ll beauty[100001];

int compute(int i,int j){
  ll lhs = sum[notes[i]];
  ll rhs = (notes[j] - 1 < 0 ? 0 :sum[notes[j] - 1]);

  printf("lhs:%d rhs:%d\n",lhs,rhs);
  return (lhs - rhs) / force_of_repulsion;
}

int main(){
  while(~scanf("%d %d %lld",
	       &num_of_notes,
	       &num_of_beauty,
	       &force_of_repulsion)){

    for(int note_idx = 0; note_idx < num_of_notes; note_idx++){
      scanf("%d",notes + note_idx);
      notes[note_idx]--;
    }

    memset(sum,0,sizeof(sum));

    for(int beauty_idx = 0; beauty_idx < num_of_beauty; beauty_idx++){
      scanf("%d",beauty + beauty_idx);
      sum[beauty_idx] = (beauty_idx - 1 >= 0 ? sum[beauty_idx - 1] : 0) + beauty[beauty_idx];
    }

    printf("beauty:\n");
    for(int beauty_idx = 0; beauty_idx < num_of_beauty; beauty_idx++){
      printf("%d ",beauty[beauty_idx]);
    }
    printf("\n");

    sort(notes,notes + num_of_notes);
    reverse(notes,notes + num_of_notes);

    printf("revised notes:\n");
    for(int i=0;i<num_of_notes;i++){
      printf("%d ",notes[i]);
    }
    printf("\n");

    memset(dp,0x3f,sizeof(dp));

    dp[0][0] = 0;
    for(int i=0;i<num_of_notes;i++){
      for(int j=0;j<=i;j++){
	int larger_idx = max(i,j) + 1;

	printf("noteinfo: notes[%d] = %d, notes[%d] - 1 = %d\n",i,notes[i],larger_idx,notes[larger_idx] - 1);
	printf("before0: dp[%d][%d] = %lld\n",larger_idx,j,dp[larger_idx][j]);

	dp[larger_idx][j]
	  = min(dp[larger_idx][j],dp[i][j] + compute(i,larger_idx));

	printf("after0:  dp[%d][%d] = %lld\n",larger_idx,j,dp[larger_idx][j]);

	printf("noteinfo: notes[%d] = %d, notes[%d] - 1 = %d\n",j,notes[j],larger_idx,notes[larger_idx] - 1);
	printf("before1: dp[%d][%d] = %lld\n",larger_idx,i,dp[larger_idx][i]);
	dp[larger_idx][i]
	  = min(dp[larger_idx][i],dp[i][j] + compute(j,larger_idx));
	printf("after1:  dp[%d][%d] = %lld\n",larger_idx,i,dp[larger_idx][i]);
      }
    }

    ll res = LINF;
    for(int i=0;i<num_of_notes;i++){
      printf("dp[%d][%d] = %lld, add = %lld\n",num_of_notes - 1,i,dp[num_of_notes - 1][i],(sum[notes[i]] - sum[notes[num_of_notes - 1]]) / force_of_repulsion);
      res = min(dp[num_of_notes - 1][i] + compute(i,num_of_notes - 1),res);
    }
    
    printf("%lld\n",res);
  }
}
