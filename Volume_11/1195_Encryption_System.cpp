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
 
const static int tx[] = {0,1,0,-1};
const static int ty[] = {-1,0,1,0};

const static double EPS = 1e-8;

int dfs(int pos,int used,const string& encrypted){
  if(pos == encrypted.size()){
    return 1;
  }
  int res = 0;
  for(int offset = 0; offset <= 1; offset++){
    if(encrypted[pos] == 'z' && offset == 1) continue;
    if(offset == 0){
      if(encrypted[pos] != 'a' 
	 && !(used & (1 << ((encrypted[pos] + offset) - 'a')))) continue;
      res += dfs(pos + 1,used,encrypted);
    }
    else if(offset == 1){
      if(used & (1 << ((encrypted[pos] + offset) - 'a'))) continue;
      res += dfs(pos + 1,used | (1 << ((encrypted[pos] + offset) - 'a')),encrypted);
    }
  }
  return res;
}

int main(){
  string str;
  while(cin >> str){
    if(str == "#") break;
    printf("%d\n",dfs(0,0,str));
  }
}
