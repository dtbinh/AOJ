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

class Requirement{
public:
  int upper;
  int lower;
  Requirement() : upper(INF),lower(0) {}
  Requirement(int _u,int _l) : upper(_u),lower(_l) {}
};

int total_commands;
int total_skills;

bool check_path(int from_command,int to_command,
		Requirement requirement[101][101]){
  for(int skill_id = 1; skill_id <= total_skills;skill_id++){
    if(requirement[from_command][skill_id].lower
       > requirement[to_command][skill_id].upper){
      return false;
    }
    if(requirement[from_command][skill_id].upper
       < requirement[to_command][skill_id].lower){
      return false;
    }
  }
  return true;
}

int main(){
  while(~scanf("%d %d",&total_commands,&total_skills)){
    Requirement requirement[101][101];    
    for(int command_idx = 0; command_idx < total_commands; command_idx++){
      int total_conditions;
      scanf("%d",&total_conditions);
      for(int condition_idx = 0; condition_idx < total_conditions; condition_idx++){
	int skill_id;
	string symbol;
	int required_point;
	cin >> skill_id >> symbol >> required_point;
	if(symbol == ">=") {
	  requirement[command_idx][skill_id].lower
	    = max(required_point,requirement[command_idx][skill_id].lower);
	}
	else if(symbol == "<="){
	  requirement[command_idx][skill_id].upper
	    = min(required_point,requirement[command_idx][skill_id].lower);
	}
      }
    }

    
    bool edge[total_commands][total_commands];
    //init
    for(int from = 0; from < total_commands; from++){
      for(int to = 0; to < total_commands; to++){
	edge[from][to] = check_path(from,to,requirement);
      }
    }

    bool isok = false;
    bool used[total_commands];
    fill(used,used+total_commands,false);

    int count = 0;
    for(int round = 0;round < total_commands;round++){
      for(int from = 0;from < total_commands;from++){
	for(int to = 0; to < total_commands; to++){
	  if(edge[from][to] && !used[from] && !used[to]){
	    used[from] = true;
	    count++;
	    goto next;
	  }
	}
      }
    next:;
    }
    
    if(count == total_commands){
      isok = true;
    }

    printf("%s\n",isok ? "Yes" : "No");
  }
}
