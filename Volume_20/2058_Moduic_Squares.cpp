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
#include <complex>
#include <assert.h>
 
using namespace std;
 
typedef long long ll;
typedef pair <double,double> P;
 
static const int tx[] = {+0,+1,+0,-1};
static const int ty[] = {-1,+0,+1,+0};
 
static const double EPS = 1e-8;

int table[3][3];

bool check(int mod){
  set<int> result;
  for(int y = 0; y < 3; y++){
    int sum = 0;
    for(int x = 0; x < 3; x++){
      sum += table[y][x];
    }
    result.insert(sum % mod);
  }
  if(result.size() > 1) return false;

  for(int x = 0; x < 3; x++){
    int sum = 0;
    for(int y = 0; y < 3; y++){
      sum += table[y][x];
    }
    result.insert(sum % mod);
  }
  if(result.size() > 1) return false;

  result.insert((table[0][0] + table[1][1] + table[2][2]) % mod);
  result.insert((table[0][2] + table[1][1] + table[2][0]) % mod);
  return (result.size() == 1);
}

int dfs(int pos,int used,int mod){
  if(pos >= 9 && check(mod)){
    return 1;
  }
  else if(pos >= 9){
    return 0;
  }
  int res = 0;
  int x = pos % 3;
  int y = pos / 3;

  if(table[y][x] == 0){
    for(int i = 1; i <= 10; i++){
      if(used & (1<<i)) continue;
      table[y][x] = i;
      res += dfs(pos + 1, used | (1<<i),mod);
      table[y][x] = 0;
    }
  }
  else{
    res += dfs(pos + 1, used,mod);
  }
  return res;
}

int main(){
  while(~scanf("%d",&table[0][0])){
    int used = 0;
    if(table[0][0] != 0){
      used |= (1<<table[0][0]);
    }

    for(int y = 0; y < 3; y++){
      for(int x = 0; x < 3; x++){
	if(y == 0 && x == 0) continue;
	scanf("%d",&table[y][x]);
	if(table[y][x] != 0){
	  used |= (1<<table[y][x]);
	}
      }
    }
    int mod;
    scanf("%d",&mod);
    if(mod == -1) break;

    used |= (1<<mod);
    int res = 0;
    if(mod == 0){
      int prev = used;
      for(int i = 1; i <= 10; i++){
	if(used & (1<<i)) continue;
	used |= (1<<i);
	mod = i;
	res += dfs(0,used,mod);
	used = prev;
      }
    }
    else{
      res += dfs(0,used,mod);
    }
    printf("%d\n",res);
  }
}
