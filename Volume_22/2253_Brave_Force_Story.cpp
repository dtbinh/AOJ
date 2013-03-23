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
 
int tx[] = {0,1,1,0,-1,-1};
int ty[] = {1,1,0,-1,-1,0};
 
static const double EPS = 1e-8;

class State{
public:
  int mStep;
  int mX;
  int mY;
  State(int step,int x,int y) : mStep(step), mX(x), mY(y) {}
  bool operator <(const State& s) const{
    return mStep < s.mStep;
  }

  bool operator >(const State& s) const{
    return mStep > s.mStep;
  }
};

// int CoundVisitedCell(map<P,int>& stage){
//   int count = 0;
//   for(int y=-30;y<=30;y++){
//     for(int x=-30;x<=30;x++){
//       if(stage.find(P(x,y)) == stage.end()) continue;
//       if(stage[P(x,y)] >= 0) count++;
//     }
//   }
//   return count;
// }


int main(){
  int t,n;
  while(~scanf("%d %d",&t,&n)){

    if(t==0 && n==0) break;

    map<P,int> stage;
    for(int i=0;i<n;i++){
      int x,y;
      scanf("%d %d",&x,&y);
      stage[P(x,y)] = -1;
    }

    int sx,sy;
    scanf("%d %d",&sx,&sy);

    priority_queue<State,vector<State>,greater<State> > que;
    que.push(State(0,sx,sy));
    stage[P(sx,sy)] = 0;

    int res = 0;
    while(!que.empty()){
      State s = que.top();
      que.pop();

      res++;
      if(s.mStep >= t) continue;

      for(int i=0;i<6;i++){
	int dx = s.mX + tx[i];
	int dy = s.mY + ty[i];

	//obstacle
	if(stage.find(P(dx,dy)) != stage.end()
	   && stage[P(dx,dy)] == -1) continue;

	//small step count is better
	if(stage.find(P(dx,dy)) != stage.end() 
	   && s.mStep+1 >= stage[P(dx,dy)] ) continue;

	stage[P(dx,dy)] = s.mStep+1;
	que.push(State(s.mStep+1,dx,dy));
      }
    }

    printf("%d\n",res);
  }
}
