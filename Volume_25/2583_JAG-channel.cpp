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
  
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};


int main(){
  int total_lines;
  while(~scanf("%d",&total_lines)){
    if(total_lines == 0) break;

    char responses[1024][64];
    int parent[1024];
    int depth_log[1024];
    memset(parent,-1,sizeof(parent));

    for(int line_idx = 0; line_idx < total_lines; line_idx++){
      char buf[64];
      scanf("%s",buf);
      strcpy(responses[line_idx],buf);
      int depth = count(buf,buf + strlen(buf),'.');
      depth_log[line_idx] = depth;
      for(int prev_idx = line_idx - 1; prev_idx >= 0; prev_idx--){
	if(depth_log[prev_idx] < depth){
	  parent[line_idx] = prev_idx;
	  break;
	}
      }
    }

    int connect[1024];
    memset(connect,-1,sizeof(connect));
    for(int first_idx = 0; first_idx < total_lines; first_idx++){
      for(int last_idx = first_idx + 1; last_idx < total_lines; last_idx++){
	if(parent[first_idx] == parent[last_idx]){
	  connect[first_idx] = last_idx;
	  break;
	}
      }
    }
    for(int line_idx = 0; line_idx < total_lines; line_idx++){
      if(depth_log[line_idx] != 0){
	responses[line_idx][depth_log[line_idx] - 1] = '+';
      }

      if(connect[line_idx] != -1){
	int last_idx = connect[line_idx];
	for(int i = line_idx + 1; i < last_idx; i++){
	  if(responses[i][depth_log[line_idx] - 1] != '+'){
	    responses[i][depth_log[line_idx] - 1] = '|';
	  }
	}
      }
    }

    for(int line_idx = 0; line_idx < total_lines; line_idx++){
      for(int i = 0; i < (int)strlen(responses[line_idx]); i++){
	if(responses[line_idx][i] == '.'){
	  responses[line_idx][i] = ' ';
	}
      }
      printf("%s",responses[line_idx]);
    }
  }
}
