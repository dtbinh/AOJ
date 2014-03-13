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

struct Bar{
  int x;
  int y;
};

int main(){
  int total_vertical_bars;
  int total_horizontal_bars;
  int max_height;
  int total_selected_bars;
  while(~scanf("%d %d %d %d",
	       &total_vertical_bars,
	       &total_horizontal_bars,
	       &max_height,
	       &total_selected_bars)){
    ll sum = 0;
    int points[1001];
    memset(points,0,sizeof(points));
    for(int i=0;i<total_vertical_bars;i++){
      scanf("%d",points + i);
    }
    vector<int> bars[1001];
    memset(bars,0,sizeof(bars));
    for(int i=0;i<total_horizontal_bars;i++){
      int x,y;
      scanf("%d %d",&x,&y);
      bars[y-1].push_back(x-1);
    }

    int matrix[1001];
    for(int i=0;i<total_vertical_bars;i++) matrix[i] = i;

    int mod[1001][1001];
    for(int height=0;height < max_height;height++){
      for(int i=0;i<bars[height].size();i++){
	int x = bars[height][i];
	swap(matrix[x],matrix[x+1]);
      }

      memcpy(mod[height],matrix,sizeof(int)*1001);
    }

    //re-init
    for(int i=0;i<total_vertical_bars;i++) matrix[i] = i;
    for(int height=0;height < max_height;height++){
      for(int i=0;i<bars[height].size();i++){
	mod[height-1];

	mod[height+1];
	mod[max_height];
      }
    }

  }
}
