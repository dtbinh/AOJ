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
 
static const double EPS = 1e-8;

int main(){
  int N;
  while(~scanf("%d",&N)){
    for(int m=0;m<N;m++){
      ll bits[9];
      for(int i=0;i<9;i++){
	scanf("%x",bits+i);
      }

      ll key = 0;
      for(int i=0;i<32;i++){
	ll mask = (1LL<<i);
	ll sum = 0;
	for(int j=0;j<8;j++) sum += bits[j] ^ key;
	if((sum & mask) != (bits[8] & mask)){
	    key |= mask;
	}
      }

      printf("%x\n",key);
    }
  }
}
