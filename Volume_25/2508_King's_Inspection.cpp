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

static const string stations = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

int main(){

  int n;
  while(~scanf("%d",&n)){
    if(n==0) break;

    int back_dist[101];
    for(int i=0;i<n;i++){
      scanf("%d",back_dist+i);
    }
    string str;
    cin >> str;

    int back_idx = 0;
    for(int i=0;i<str.size();i++){
      int pos = lower_bound(stations.begin(),stations.end(),str[i]) - stations.begin();
      str[i] = stations[(pos - back_dist[back_idx] + stations.size()) % stations.size()];
      back_idx++;
      back_idx %= n;
    }

    cout << str << endl;
  }
}
