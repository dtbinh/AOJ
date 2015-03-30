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
#include <iterator>
 
using namespace std;
 
typedef long long ll;
typedef pair <double,double> P;
typedef pair <int,P > PP;
 
int tx[] = {0,1,0,-1};//URDL
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

bool McCullochPitts(const vector<P>& white,const vector<P>& black){
  vector<double> weight(3);
  double alpha = 5.0;

  bool res = false;
  weight[0] = 0.0;
  weight[1] = 0.0;
  weight[2] = 0.0;

  for(int round = 0; round < 5000000; round++){
    bool isok = true;
    for(int i = 0; i < white.size(); i++){
      double o = (weight[0] + weight[1] * white[i].first + weight[2] * white[i].second);
      //white == 0
      //black == 1
      if(o > 0){
	weight[0] -= alpha;
	weight[1] -= alpha * white[i].first;
	weight[2] -= alpha * white[i].second;
	isok = false;
      }
    }
    for(int i = 0;i < black.size(); i++){
      double o = (weight[0] + weight[1] * black[i].first + weight[2] * black[i].second);
      //white == 0
      //black == 1
      if(o <= 0){
	weight[0] += alpha;
	weight[1] += alpha * black[i].first;
	weight[2] += alpha * black[i].second;
	isok = false;
      }
    }
    if(isok){
      res = true;
      break;
    }
  }
  return res;
}

int main(){
  int n,m;
  while(~scanf("%d %d",&n,&m)){
    if(n == 0 && m == 0) break;

    vector<P> white;
    for(int i = 0; i < n; i++){
      double x,y;
      scanf("%lf %lf",&x,&y);
      white.push_back(P(x,y));
    }
    vector<P> black;
    for(int i = 0; i < m; i++){
      double x,y;
      scanf("%lf %lf",&x,&y);
      black.push_back(P(x,y));
    }

    printf("%s\n",McCullochPitts(white,black) ? "YES" : "NO");
  }
}
