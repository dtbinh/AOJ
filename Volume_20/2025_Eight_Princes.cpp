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
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

ll nCr(int n,int r){
 return (r==0 || n==r) ? 1 : nCr(n-1,r) + nCr(n-1,r-1);
}

ll fact(ll n)
{
  return (n <= 1 ? 1 : n * fact(n-1));
}

int main(){
  int seats;
  while(~scanf("%d",&seats)){
    if(seats == 0) break;
  }
}
