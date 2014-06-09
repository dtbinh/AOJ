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


ll sum[200001];
ll dp[2001][2001];
int notes[2001];
ll beauty[100001];

int main(){
  int num_of_notes;
  int num_of_beauty;
  ll force_of_repulsion;
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

    sort(notes,notes + num_of_notes);
    reverse(notes,notes + num_of_notes);

    memset(dp,0x3f,sizeof(dp));

    dp[0][0] = 0;
    for(int i=0;i<num_of_notes;i++){
      for(int j=0;j<=i;j++){
	int larger_idx = max(i,j) + 1;
	dp[larger_idx][j]
	  = min(dp[larger_idx][j],
		dp[i][j] + (sum[notes[i]] - sum[notes[larger_idx] - 1]) / force_of_repulsion);

	dp[larger_idx][i]
	  = min(dp[larger_idx][i],
		dp[i][j] + (sum[notes[j]] - sum[notes[larger_idx] - 1]) / force_of_repulsion);
      }
    }

    ll res = LINF;
    for(int i=0;i<num_of_notes;i++){
      res = min(dp[num_of_notes - 1][i]
		+ (sum[notes[i]] - sum[notes[num_of_notes - 1] - 1]) / force_of_repulsion,
		res);
    }

    printf("%lld\n",res);
  }
}
