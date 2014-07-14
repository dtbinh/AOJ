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
  
static const double EPS = 1e-8;
  
static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};

int main(){
  int N;
  while(~scanf("%d",&N)){
    vector<int> baumkuchen;

    int sum[100001];
    memset(sum,0,sizeof(sum));
    for(int i=0;i<N;i++){
      int width;
      scanf("%d",width);
      baumkuchen.push_back(width);
      sum[i] = (i - 1 >=0 ? sum[i - 1] : 0) + width;
    }
    
  }
}
