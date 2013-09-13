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
 
const static int tx[] = {0,1,1,1,0,-1,-1,-1};
const static int ty[] = {-1,-1,0,1,1,1,0,-1};

int main(){
  int target_num;
  string card;
  while(cin >> target_num >> card){
    if(target_num == 0 && card == "0") break;

    //1 ^(1) 2 ^(2) 2 ^(3) 4 ^(4)
    vector<int> dp[100];
    for(int i=0;i<card.size();i++){
      dp[i].push_back(atoi(card.substr(0,i+1).c_str()));
      for(int j=0;j<i;j++){
	//0->j j->i
	for(int k=0;k<dp[j].size();k++){
	  int rear = atoi(card.substr(j+1,i-j).c_str());
	  dp[i].push_back(dp[j][k] + rear);
	  // printf("%d %d\n",dp[j][k],rear);
	}
      }
    }

    int res = -1;
    bool reject = false;
    for(int i=0;i<dp[card.size()-1].size();i++){
      if(target_num >= dp[card.size()-1][i]){
	if(res < dp[card.size()-1][i]){
	  res = dp[card.size()-1][i];
	  reject = false;
	}
	else if(res == dp[card.size()-1][i]){
	  reject = true;
	}
      }
      // printf("%d\n",dp[card.size()-1][i]);
    }
    
    if(res == -1){
      printf("error\n");
    }
    else if(reject){
      printf("rejected\n");
    }
    else{
      printf("%d\n",res);
    }
  }
}
