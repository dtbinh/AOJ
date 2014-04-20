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
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

int main(){
  char stage[4][4] = {{'A','B','C'},{'D','E','F'},{'G','H','I'}};
  string pass;
  while(cin >> pass){
    bool isok = true;
    for(int i=0;i+1<pass.size();i++){
      int sx=0,sy=0,gx=0,gy=0;
      for(int y=0;y<3;y++){
	for(int x=0;x<3;x++){
	  if(pass[i] == stage[y][x]){
	    sx = x;
	    sy = y;
	  }
	}
      }
      for(int y=0;y<3;y++){
	for(int x=0;x<3;x++){
	  if(pass[i+1] == stage[y][x]){
	    gx = x;
	    gy = y;
	  }
	}
      }
      if(!(abs(gx - sx) > 1
	   || abs(gy - sy) > 1)
	 && !(abs(gx - sx) == 1 && abs(gy - sy) == 1)
	 && !(gx == sx && gy == sy)){
	// nothing to do
      }
      else{
	isok = false;
      }
    }

    if(isok){
      cout << pass << endl;
    }
  }
}
