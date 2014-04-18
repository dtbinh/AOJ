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
  string strN;
  
  int char2num[256];
  char2num['f'] = 1;
  char2num['e'] = 2;
  char2num['d'] = 3;
  char2num['c'] = 4;
  char2num['b'] = 5;
  char2num['a'] = 6;
  int chars[] = {'f','e','d','c','b','a'};

  while(getline(cin,strN)){
    int N = atoi(strN.c_str());
    
    for(int i=0;i<N;i++){
      string routes[2];
      map<pair<int,int>,bool> visited[2][6];

      for(int person=0;person<2;person++){
	getline(cin,routes[person]);

	for(int offset=0;offset< 6;offset++){
	  for(int char_idx=0;char_idx<6;char_idx++){
	    char2num[chars[char_idx]]
	      = (char_idx + offset) % 6 + 1;	  
	  }  
	  pair<int,int> current(0,0);
	  visited[person][offset][current] = true;

	  for(int k=0;k<routes[person].size();k++){
	    current.first 
	      += maja(char2num[routes[person][k]]).first;
	    current.second 
	      += maja(char2num[routes[person][k]]).second;
	    // cout << "x: " << current.first;
	    // cout << " y: " << current.second << endl;
	    visited[person][offset][current] = true;
	  }
	}
      }
	
      string garbage;
      getline(cin,garbage);

      bool res = false;
      for(int src_offset=0;src_offset< 6;src_offset++){
	for(int dst_offset=0;dst_offset< 6;dst_offset++){
	  int offset_x
	    = visited[1][dst_offset].begin()->first.first
	    - visited[0][src_offset].begin()->first.first;
	  int offset_y
	    = visited[1][dst_offset].begin()->first.second
	    - visited[0][src_offset].begin()->first.second;

	  bool isok = true;
	  for(map<pair<int,int>,bool>::iterator it = visited[0][src_offset].begin();
	      it != visited[0][src_offset].end();
	      it++){
	    pair<int,int> moved(it->first.first+offset_x,
				it->first.second+offset_y);
	    if(visited[1][dst_offset].find(moved) == visited[1][dst_offset].end()){
	      isok = false;
	      break;
	    }
	  }
	  res |= isok;
	}
      }
      printf("%s\n",res ? "true" : "false");
    }
  }
}
