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
 
static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

int main(){
  int money_limit;
  int total_secret_artists;
  int total_standard_artists;
  int to_pick_standard_artists;
  while(~scanf("%d %d %d %d",
	       &money_limit,
	       &total_secret_artists,
	       &total_standard_artists,
	       &to_pick_standard_artists)){
    for(int i=0;i<total_secret_artists;i++){
      string name;
      int cost;
      int satisfaction;
    }
    for(int i=0;i<total_standard_artists;i++){
      string name;
      int cost;
      int satisfaction;
    }
  }
}
