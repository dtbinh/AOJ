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

  //              0
  //            1   2
  //           3  4  5 
  //          6  7  8  9 
  //        10 11 12 13 14
  //       15 16 17 18 19 20
  //      21 22 23 24 25 26 27
  //    28 29 30 31 32 33 34 35
  //   36 37 38 39 40 41 42 43 44
  //  45 46 47 48 49 50 51 52 53 54
const string edges_str[] = {"1 2", // 0
			    "0 2 4 3","0 1 4 5", //1 2
			    "1 4 6 7","1 2 3 5 7 8","2 4 8 9", //3 4 5
			    "3 7 10 11","3 4 6 8 11 12","4 5 7 9 12 13","5 8 13 14", //6 7 8 9
			    "6 11 15 16","6 7 10 12 16 17","7 8 11 13 17 18"," 8 9 12 14 18 19","9 13 19 20",//10 11 12 13 14
			    "10 16 21 22","10 11 15 17 22 23","11 12 16 18 23 24","12 13 17 19 24 25","13 14 18 20 25 26","14 19 26 27",//15 16 17 18 19 20
			    "15 22 28 29","15 16 21 23 29 30","16 17 22 24 30 31","17 18 23 25 31 32","18 19 24 26 32 33","19 29 25 27 33 34","20 26 34 35",//21 22 23 24 25 26 27
			    "21 29 36 37","21 22 28 30 37 38","22 23 29 31 38 39","23 24 30 32 39 40","24 25 31 33 40 41","25 26 32 34 41 42","26 27 33 35 42 43","27 34 43 44",//28 29 30 31 32 33 34 35
			    "28 37 45 46","28 29 36 38 46 47","29 30 37 39 47 48","30 31 38 40 48 49","31 32 39 41 49 50","32 33 40 42 50 51","33 34 41 43 51 52","34 35 42 44 52 53","35 43 53 54",//36 37 38 39 40 41 42 43 44
			    "36 46","36 37 45 47","37 38 46 49","38 39 47 49","39 40 48 50","40 41 49 51","41 42 50 52","42 43 51 53","43 44 52 54","44 53",//45 46 47 48 49 50 51 52 53 54
};
  

class Stage{
 
public:
  int size;
  vector< vector<int> > edges;
  int nodes[55];
  int prev_nodes[55];
  int latest_stone;
  Stage(int _s) : size(_s){
    for(int i=0;i<(1+size)*size/2;i++){
      vector<int> tmp = split(" ",edges_str[i]);
      edges.push_back(tmp);
    }
    memset(nodes,0,sizeof(nodes));
    memset(prev_nodes,0,sizeof(prev_nodes));

    latest_stone = -1;
  }

  bool set_stone(int node_idx,int num){
    if(nodes[node_idx] != 0) return false;

    latest_stone = num;
    nodes[node_idx] = num;
    return true;
  }

  bool update(){
    bool has_space[55];
    bool visited[55];
    bool hold[55];

    //init
    memcpy(prev_nodes,nodes,sizeof(int)*55);
    memset(has_space,false,sizeof(has_space));
    memset(visited,false,sizeof(visited));
    memset(hold,false,sizeof(hold));

    //marking
    for(int i=0;i<(1+size)*size/2;i++){
      check_dfs(i,nodes[i],visited,has_space);
    }

    bool isok = false;

    //overwrite
    for(int node_idx=0;node_idx<(1+size)*size/2;node_idx++){
      if(has_space[node_idx]){
	hold_dfs(node_idx,nodes[node_idx],hold);
      }
    }

    for(int node_idx=0;node_idx<(1+size)*size/2;node_idx++){
      if(!hold[node_idx]){
	nodes[node_idx] = 0;
	isok = true;
      }
    }

    return isok;
  }
  
  int compute_score(){
        //count score
    int score = 0;
    for(int i=0;i<(1+size)*size/2;i++){
      if(nodes[i] == 0 && prev_nodes[i] != 0){
	if(prev_nodes[i] != latest_stone){
	  score++;
	}
	else if(prev_nodes[i] == latest_stone){
	  score--;
	}
      }
    }
    return score;
  }

  void check_dfs(int node_idx,int num,bool visited[55],bool has_space[55]){
    if(visited[node_idx]) return;
    
    visited[node_idx] = true;

    for(int i=0;i<edges[node_idx].size();i++){
      int next_node = edges[node_idx][i];
      if(next_node >= (1+size)*size/2) continue;
      if(nodes[next_node] == 0){
	has_space[node_idx] = true;
	return;
      }
      if(nodes[next_node] != num) continue;
      if(visited[next_node]) continue;
      check_dfs(next_node,num,visited,has_space);
    }
  }

  void hold_dfs(int node_idx,int num,bool hold[55]){
    hold[node_idx] = true;
    for(int i=0;i<edges[node_idx].size();i++){
      int next_node = edges[node_idx][i];
      if(next_node >= (1+size)*size/2) continue;
      if(nodes[next_node] == 0) continue;
      if(nodes[next_node] != num) continue;
      if(hold[next_node]) continue;
      hold_dfs(next_node,num,hold);
    }
  }
    
  vector<int> split(string delim,string str){
    vector<int> res;
    str += delim;
    for(int i=0;i<str.size();i++){
      for(int j=1;i+j<=str.size();j++){
	if(str.substr(i,j).find(delim) != string::npos){
	  int num = atoi(str.substr(i,j-1).c_str());
	  if(str.substr(i,j-1).size() >0 ) res.push_back(num);
	  i+=j-1;
	  break;
	}
      }
    }
    
    return res;
  }

  void dump(){
    int idx = 0;
    for(int i=1;i<=size;i++){
      for(int j=0;j<i;j++){
	printf("%d",nodes[idx]);
	idx++;
      }
      printf("\n");
    }
  }

  bool operator==(const Stage& s) const{
    for(int i=0;i<(1+size)*size/2;i++){
      if(s.nodes[i] != nodes[i]) return false;
    }
    return true;
  }
};

int main(){
  int stage_size,current_turn;
  while(~scanf("%d %d",&stage_size,&current_turn)){
    if(stage_size == 0) break;
    Stage current(stage_size);
    int idx = 0;
    for(int i=1;i<=stage_size;i++){
      for(int j=0;j<i;j++){
	int num;
	scanf("%d",&num);
	current.set_stone(idx,num);
	idx++;
      }
    }

    Stage next(stage_size);
    next = current;
    int res = -INF;
    for(int idx=0;idx<(1+current.size)*current.size/2;idx++){
      if(!next.set_stone(idx,current_turn)) continue;

      // printf("prev\n");
      // next.dump();

      next.update();

      // printf("after update\n");
      // next.dump();

      int score = next.compute_score();
      res = max(res,score);
      next = current;
    }
    printf("%d\n",res);
  }
}
