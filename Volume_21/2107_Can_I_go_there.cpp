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

struct State {
  int from;
  int to;
  State(int f,int t)
    : from(f),to(t) {}
};

void matrix_pow(const bool lhs[101][101],const bool rhs[101][101],
		bool result_matrix[101][101],int length){
  bool tmp[101][101] = {};
  for(int i = 0; i < length; i++){
    for(int j = 0; j < length; j++){
      bool sum = false;
      for(int k = 0; k < length; k++){
	sum |= (lhs[i][k] && rhs[k][j]);
      }
      tmp[i][j] = sum;
    }
  }
  memcpy(result_matrix,tmp,sizeof(bool)*101*101);
}

void fast_pow(int n,int length,bool A[101][101],bool B[101][101]) {
  for(int i = 0; i < length; i++){
    B[i][i] = 1;
  }
  while(n > 0) {
    if (n & 1){
      matrix_pow(B,A,B,length);
    }
    matrix_pow(A,A,A,length);
    n >>= 1;
  }
}

int main(){
  int total_stations;
  int total_sections;
  int total_steps;
  while(~scanf("%d %d %d",
	       &total_stations,
	       &total_sections,
	       &total_steps)){
    if(total_stations == 0 && total_sections == 0 && total_steps == 0) break;
    vector<int> edge[101];
    for(int section_i = 0; section_i < total_sections; section_i++){
      int src,dst;
      scanf("%d %d",&src,&dst);
      src--; dst--;
      edge[src].push_back(dst);
      edge[dst].push_back(src);
    }

    vector<State> states;
    states.push_back(State(-1,0));
    for(int from = 0; from < total_stations; from++){
      for(int i = 0; i < edge[from].size(); i++){
	int to = edge[from][i];
	states.push_back(State(from,to));
      }
    }

    bool init_matrix[101][101] = {};
    for(int y = 0; y < states.size(); y++){
      for(int x = 0; x < states.size(); x++){
	if(states[y].to == states[x].from
	   && states[y].from != states[x].to){
	  init_matrix[y][x] = true;
	}
      }
    }

    bool result_matrix[101][101] = {};
    fast_pow(total_steps,states.size(),init_matrix,result_matrix);

    bool isok = false;
    for(int i = 0; i < states.size(); i++){
      if(states[i].to == total_stations - 1 && result_matrix[0][i]){
	isok = true;
	break;
      }
    }
    printf("%s\n",isok ? "yes" : "no");
  }
}
