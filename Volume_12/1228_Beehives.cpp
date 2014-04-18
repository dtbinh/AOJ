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

pair<int,int> maja(int x) {
  if (x == 0) return pair<int,int>(0,0);
  int n = static_cast<int>(ceil((-1.0+sqrt(1.0+4.0/3.0*x))/2.0));
  int a = 3*n*(n-1), d = static_cast<int>(ceil((1.0*x-a)/n-1.0));
  int k = x - a - n * d;
  switch (d) {
  case 0: return pair<int,int>(n-k,k);
  case 1: return pair<int,int>(-k,n);
  case 2: return pair<int,int>(-n,n-k);
  case 3: return pair<int,int>(-n+k,-k);
  case 4: return pair<int,int>(k,-n);
  case 5: return pair<int,int>(n,-n+k);
  }
}

int majadist(const pair<int,int> &a, const pair<int,int> &b) {
  int dx = abs(a.first - b.first);
  int dy = abs(a.second - b.second);
  int dz = abs(a.first+a.second-b.first-b.second);
  return min(dx+dy, min(dx+dz, dy+dz));
}

int main(){
  int N;
  
  int char2num[256];
  char2num['e'] = 1;
  char2num['d'] = 2;
  char2num['c'] = 3;
  char2num['b'] = 4;
  char2num['a'] = 5;
  char2num['f'] = 6;

  while(~scanf("%d",&N)){
    for(int i=0;i<N;i++){
      string routes[2];
      map<pair<int,int>,bool> visited[2];
      for(int person=0;person<2;person++){
	cin >> routes[person];

	pair<int,int> current(0,0);
	visited[person][current] = true;
	for(int k=0;k<routes[person].size();k++){
	  current.first 
	    += maja(char2num[routes[person][k]]).first;
	  current.second 
	    += maja(char2num[routes[person][k]]).second;
	  cout << "x: " << current.first;
	  cout << " y: " << current.second << endl;
	  visited[person][current] = true;
	}
      }

      string garbage;
      cin >> garbage;

      int offset_x = visited[1].begin()->first.first - visited[0].begin()->first.first;
      int offset_y = visited[1].begin()->first.second - visited[0].begin()->first.second;

      bool isok = true;
      for(map<pair<int,int>,bool>::iterator it = visited[1].begin();
	  it != visited[1].end();
	  it++){
	pair<int,int> moved(it->first.first+offset_x,
			    it->first.second+offset_y);
	if(visited[1].find(moved) == visited[1].end()){
	  isok = false;
	}
      }
      printf("%s\n",isok ? "true" : "false");
    }
  }
}
