#define _USE_MATH_DEFINES
#define INF 10000000
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>
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

using namespace std;

typedef long long ll;
typedef pair<int,string> P;

static const double EPS = 1e-8;

struct Team{
public:
  int id;
  int point;
  Team(int _id,int _p) : id(_id),point(_p){}
  Team() : id(0),point(0){}

  bool operator<(const Team& t) const{
    if(id == t.id){
      return point < t.point;
    }
    else {
      return (id < t.id);
    }
  }
  bool operator>(const Team& t) const{
    if(id == t.id){
      return point > t.point;
    }
    else {
      return (id > t.id);
    }
  }
  bool operator==(const Team& t) const{
    return (id == t.id && point == t.point);
  }
};

class SegmentTree{
private:
  struct Team* points;
  int n;
public:
  SegmentTree(int _n){
    n = 1;
    while(n < _n) n *= 2;

    points = new Team[n];
  }

  void insert(int idx,int p){
    idx += n - 1;

    points[idx].id = idx - (n - 1);
    points[idx].point = p;

    while(idx > 0){
      idx = (idx - 1) / 2;
      int lhs =idx * 2 + 1;
      int rhs =idx * 2 + 2;

      if(points[lhs].point < points[rhs].point){
	points[idx].point = points[rhs].point;
	points[idx].id = points[rhs].id;
      }
      else if(points[lhs].point > points[rhs].point){
	points[idx].point = points[lhs].point;
	points[idx].id = points[lhs].id;
      }
      else if(points[lhs].point == points[rhs].point){
	int next_id = min(points[lhs].id,points[rhs].id);
	points[idx].point = points[rhs].point;
	points[idx].id = next_id;
      }
    }
  }

  Team query(int a,int b,int idx,int l,int r){
    if(r <= a || b <= l) return Team(0,0);
    if(a <= l && r <= b) return points[idx];
    else{
      Team left = query(a,b,idx * 2 + 1,1,(l+r) / 2);
      Team right = query(a,b,idx * 2 + 2,(l+r) / 2,r);
      if(left < right){
	return right;
      }
      else if(left == right){
	return left;
      }
      else if(left > right){
	return left;
      }
    }
  }
};

int main(){
  int total_teams,total_records,contest_duration;
  while(~scanf("%d %d %d",
	       &total_teams,
	       &total_records,
	       &contest_duration)){
    
    priority_queue<Team> que;
    
    int disp_time[100001];
    
    memset(disp_time,0,sizeof(disp_time));
    int prev_champ = 1;
    int prev_time = 0;
    SegmentTree seg_tree(total_teams+1);

    for(int record_idx=0;record_idx<total_records;record_idx++){
      int id,time,point;
      scanf("%d %d %d",&id,&time,&point);
      
      seg_tree.insert(id,point);
      Team team = seg_tree.query(0,total_teams,0,0,total_teams);
      if(prev_champ != team.id){
	disp_time[prev_champ] += time - prev_time;
	prev_time = time;
	prev_champ = team.id;
      }
    }
    disp_time[prev_champ] += contest_duration - prev_time;
    
    int res = 0;
    int max_disp = 0;
    for(int team_idx=1;team_idx <= total_teams; team_idx++){
      if(max_disp < disp_time[team_idx]){
	max_disp = disp_time[team_idx];
	res = team_idx;
      }
    }
    printf("%d\n",res);
  }
}
