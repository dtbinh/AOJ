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
#include <complex>
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P > PP;
 

static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-10;

double dp[1<<12][12];

double compute_distance(int prev,int next,
			const vector<int>& boxes){
  double h = abs(boxes[prev] - boxes[next]);
  double r = abs(boxes[prev] + boxes[next]);
  double w = sqrt(r * r - h * h);
  return w - (double)boxes[prev] + (double)boxes[next];
}

int main(){
  string str;
  while(getline(cin,str)){
    stringstream ss;
    ss << str;
    int box_width;
    ss >> box_width;

    int box;
    vector<int> boxes;
    while(ss >> box){
      boxes.push_back(box);
    }

    for(int S=0;S<=(1<<12)-1;S++){
      for(int i=0;i<12;i++){
	dp[S][i] = (double)box_width + 10.0;
      }
    }

    for(int i=0;i<boxes.size();i++){
      dp[(1<<i)][i] = 2 * boxes[i];
    }

    for(int S = 0; S <= (1<<boxes.size()) - 1;S++){
      for(int prev = 0; prev < boxes.size(); prev++){
	if(!(S & (1<<prev))) continue;
	for(int next = 0; next<boxes.size();next++){
	  if(S & (1<<next)) continue;
	  dp[S | (1<<next)][next] = min(dp[S | (1<<next)][next],
					dp[S][prev] + compute_distance(prev,next,boxes));
	}
      }
    }

    //OK,NA

    bool isok = false;
    for(int i = 0; i < boxes.size(); i++){
      if(dp[(1<<boxes.size())-1][i] <= (double)box_width + EPS){
	isok = true;
      }
    }
    printf("%s\n",isok ? "OK" : "NA");
  }
}
