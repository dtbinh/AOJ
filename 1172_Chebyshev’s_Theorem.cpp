
#include <iostream>
#include <deque>
#include <cstdio>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <sstream>
 
using namespace std;
 
int dp[1000001];
int main(){
  fill((int*)dp,(int*)dp + 1000000,1);
  dp[0] = 0;
  dp[1] = 0;
  for(int i=2;i*i<=1000000;i++){
    if(!dp[i]) continue;
    for(int j=i+i;j<=1000000;j+=i){
      dp[j] = 0;
    }
  }
 
  int n;
  while(~scanf("%d",&n)){
    if(n==0) break;
    int sum = 0;
    for(int i=n+1;i<=n*2;i++){
      sum += dp[i];
    }
    printf("%dn",sum);
  }
}

