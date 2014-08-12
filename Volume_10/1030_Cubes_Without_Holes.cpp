#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdio>
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
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
 
static const double EPS = 1e-8;

class Input{
public:
  string axis;
  int a,b;
  Input(string _ax,int _a,int _b)
    : axis(_ax), a(_a), b(_b) {}
};

int main(){
  int n,total_queries;
  while(~scanf("%d %d",&n,&total_queries)){
    if(n == 0 && total_queries == 0) break;

    int res = n * n * n;

    vector<int> points[256];
    vector<Input> inputs;
    for(int i=0; i < total_queries; i++){
      string axis;
      int a,b;
      cin >> axis >> a >> b;
      points[axis[0]].push_back(a);
      points[axis[1]].push_back(b);
      inputs.push_back(Input(axis,a,b));
    }
    sort(points['x'].begin(),points['x'].end());
    points['x'].erase(unique(points['x'].begin(),points['x'].end()),points['x'].end());

    sort(points['y'].begin(),points['y'].end());
    points['y'].erase(unique(points['y'].begin(),points['y'].end()),points['y'].end());

    sort(points['z'].begin(),points['z'].end());
    points['z'].erase(unique(points['z'].begin(),points['z'].end()),points['z'].end());

    bool dp[points['x'].size()][points['y'].size()][points['z'].size()];
    for(int x = 0; x < points['x'].size(); x++){
      for(int y = 0; y < points['y'].size(); y++){
	for(int z = 0; z < points['z'].size(); z++){
	  dp[x][y][z] = false;
	}
      }
    }

    for(int i=0; i < inputs.size(); i++){
      string axis = inputs[i].axis;
      
      char other = (axis[0] != 'x' && axis[1] != 'x') ? 'x'
	: (axis[0] != 'y' && axis[1] != 'y') ? 'y' : 'z';

      int proj_a = lower_bound(points[axis[0]].begin(),points[axis[0]].end(),inputs[i].a) - points[axis[0]].begin();
      int proj_b = lower_bound(points[axis[1]].begin(),points[axis[1]].end(),inputs[i].b) - points[axis[1]].begin();

      for(int i=0;i<points[other].size();i++){
	if(other == 'x'){
	  if(!dp[i][proj_a][proj_b]) res--;
	  dp[i][proj_a][proj_b] = true;
	}
	else if(other == 'y'){
	  if(!dp[proj_a][i][proj_b]) res--;
	  dp[proj_a][i][proj_b] = true;
	}
	else if(other == 'z'){
	  if(!dp[proj_a][proj_b][i]) res--;
	  dp[proj_a][proj_b][i] = true;
	}
      }
      res -= (n - points[other].size());
    }
    
    printf("%d\n",res);
  }
}
