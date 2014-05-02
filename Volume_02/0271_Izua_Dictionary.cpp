#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#include <iostream>
#include <sstream>
#include <cstdio>
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

using namespace std;

typedef long long ll;
typedef pair<int,string> P;

const static ll MOD = 1000000007;

class BinaryIndexedTree {
private:
  int* bit;
  int n;
public:
  BinaryIndexedTree(int _size){
    bit = new int[_size];
    n = _size;
    fill(bit,bit+_size,0);
  }
  int sum(int i){
    int s = 0;
    while(i > 0){
      s += bit[i];
      i -= i & -i;
    }
    return s;
  }
  
  void add(int i, int x){
    while(i <= n){
      bit[i] += x;
      i += i & -i;
    }
  }
};

int main(){
  int N,R;
  ll dp[100001];
  ll target[100001];

  while(~scanf("%d %d",&N,&R)){
    if(N == 0) break;

    memset(dp,0,sizeof(dp));
    dp[0] = 1;

    for(int i=1;i<=N;i++){
      target[i] = i;
      // 4
      // v v v v
      //  1 2 3
      dp[i] = dp[i-1] * i % MOD;
    }
    for(int r = 0; r< R;r++){
      int from_idx;
      int to_idx;
      scanf("%d %d",&from_idx,&to_idx);
      swap(target[from_idx],target[to_idx]);
    }

    ll res = 0;
    BinaryIndexedTree BIT(100001);
    for(int i=N,j=0;i>=1;i--,j++){
      res += ((dp[j] % MOD) * (BIT.sum(target[i] - 1) % MOD) % MOD);
      res %= MOD;
      BIT.add(target[i],1);
    }
    printf("%lld\n",res);
  }
}
