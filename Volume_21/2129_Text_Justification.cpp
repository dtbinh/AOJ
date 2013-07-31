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
  
static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};

void print_dp(int dp[1001],int paragraph_len,int p1,int p2){
  for(int i=0;i<=paragraph_len;i++){
    printf("i:=%d j:=%d dp[%d]:=%d\n",p1,p2,i,dp[i]);
  }
  printf("\n");
}

int main(){
  int paragraph_len,paper_width;
  
  int case_num = 1;
  while(~scanf("%d %d",&paragraph_len,&paper_width)){
    if(paragraph_len == 0 && paper_width == 0) break;

    int a[1001];
    int sum[1001][1001];
    memset(a,0,sizeof(a));
    
    for(int i=0;i<paragraph_len;i++){
      scanf("%d",a+i);
    }

    for(int i=0;i<paragraph_len;i++){
      int tmp = 0;
      for(int j=i;j<paragraph_len;j++){
	tmp += a[j];
	sum[i][j] = tmp;
      }
    }
    
    int dp[1001];
    for(int i=0;i<paragraph_len;i++){
      dp[i] = abs(sum[0][i] - paper_width);
      for(int j=0;j<i;j++){
	dp[i] = min(dp[i],dp[j]+abs(sum[j+1][i]-paper_width));
	// print_dp(dp,paragraph_len,i,j);
      }
    }
    
    dp[paragraph_len-1] = min(dp[paragraph_len-1],max(0,sum[0][paragraph_len-1]-paper_width));
    for(int i=0;i<paragraph_len;i++){
      dp[paragraph_len-1]
	= min(dp[paragraph_len-1],
	      dp[i] + max(0,sum[i+1][paragraph_len-1]-paper_width)
	);
    }
    
    printf("Case %d: %d\n",case_num++,dp[paragraph_len-1]);
  }
}
