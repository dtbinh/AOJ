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

bool check(int hands[3]){
  for(int h=0;h<12;h++){
    for(int m=0;m<60;m++){
      for(int s=0;s<60;s++){
	int h_angle = h*30 + (m/12)*6;
	int m_angle = m*6;
	int s_angle = s*6;

	int idx[] = {0,1,2};
	do{
	  int a = hands[idx[0]];
	  int b = hands[idx[1]];
	  int c = hands[idx[2]];

	  for(int offset=0;offset<360;offset+=6){
	    int next_a = ((a*6 + offset) % 360);
	    int next_b = ((b*6 + offset) % 360);
	    int next_c = ((c*6 + offset) % 360);

	    if(next_a == h_angle 
	       && next_b == m_angle 
	       && next_c == s_angle){
	      printf("h:%d m:%d s:%d\n",h,m,s);
	    }
	  }
	}while(next_permutation(idx,idx+3));
      }
    }
  }
}
int main(){
  int total_watches;
  while(~scanf("%d",&total_watches)){
    if(total_watches == 0) break;
    for(int watch_idx = 0; watch_idx < total_watches; watch_idx++){
      int hands[3];
      for(int hand_idx = 0; hand_idx < 3; hand_idx++){
	scanf("%d",hands + hand_idx);
      }
      check(hands);
    }
  }
}
