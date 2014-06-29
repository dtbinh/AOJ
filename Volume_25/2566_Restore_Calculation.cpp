#define _USE_MATH_DEFINES
#define INF 1000000100

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
static const int MOD = 1000000007;
int dp[51][2];

int main(){
  char numbers[3][55];
  while(~scanf("%s",numbers[0])){
    if(numbers[0][0] == '0') break;
    
    memset(dp,0,sizeof(dp));
    for(int i=1;i<3;i++){
      scanf("%s",numbers[i]);
    }

    int N=strlen(numbers[0]);
    reverse(numbers[0],numbers[0]+N);
    reverse(numbers[1],numbers[1]+N);
    reverse(numbers[2],numbers[2]+N);

    dp[0][0] = 1;
    for(int x=0;x<N;x++){
      int left = 0;
      int right = -1;
      int q_count = 0;

      for(int y=0;y<2;y++){
	if(numbers[y][x] != '?'){
	  left += numbers[y][x] - '0';
	}
	else{
	  q_count++;
	}
      }

      if(numbers[2][x] != '?'){
	right = numbers[2][x] - '0';
      }

      for(int carry = 0; carry < 2; carry++){
	//num of ? eq 2
	if(q_count == 2){
	  for(int i=0; i<10;i++){
	    for(int j=0; j<10;j++){
	      if(x == N - 1 && (i==0 || j==0)) continue;
	      //C is not known
	      if(right == -1){
		dp[x+1][(i+j+carry) / 10] += dp[x][carry] % MOD;
		dp[x+1][(i+j+carry) / 10] %= MOD;
	      }
	      //C is known
	      else if((i+j+carry) % 10 == right){
		dp[x+1][(i+j+carry) / 10] += dp[x][carry] % MOD;
		dp[x+1][(i+j+carry) / 10] %= MOD;
	      }
	    }
	  }
	}
	
	//num of ? eq 1
	if(q_count == 1){
	  for(int i=0; i<10;i++){
	    if(x == N - 1 && i==0) continue;
	    //C is not known
	    if(right == -1){
	      dp[x+1][(i+left+carry) / 10] += dp[x][carry] % MOD;
	      dp[x+1][(i+left+carry) / 10] %= MOD;
	    }
	    //C is known
	    else if((i+left+carry) % 10 == right){
	      dp[x+1][(i+left+carry) / 10] += dp[x][carry] % MOD;
	      dp[x+1][(i+left+carry) / 10] %= MOD;
	    }
	  }
	}
	
	//num of ? eq 0
	if(q_count == 0){
	  if(right != -1 && (left + carry) % 10 == right){
	    dp[x+1][(left+carry) / 10] += dp[x][carry] % MOD;
	    dp[x+1][(left+carry) / 10] %= MOD;
	  }
	  if(right == -1){
	    if(x == N - 1 && (left+carry) % 10 == 0) continue;
	    dp[x+1][(left+carry) / 10] += dp[x][carry] % MOD;
	    dp[x+1][(left+carry) / 10] %= MOD;
	  }
	}
      }
      
    }

    printf("%d\n",(dp[strlen(numbers[0])][0] % MOD));
  }
}
