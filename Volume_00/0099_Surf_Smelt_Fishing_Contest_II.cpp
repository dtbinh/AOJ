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
#include <assert.h>
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P > PP;
 
static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};

static const double EPS = 1e-10;

struct Participant{
public:
  int id;
  int fish;
  Participant(int _id,int _f) : id(_id),fish(_f){}
  Participant() : id(0),fish(0){}

  bool operator<(const Participant& t) const{
    if(id == t.id){
      return fish < t.fish;
    }
    else {
      return (id < t.id);
    }
  }
  bool operator>(const Participant& t) const{
    if(id == t.id){
      return fish > t.fish;
    }
    else {
      return (id > t.id);
    }
  }
  bool operator==(const Participant& t) const{
    return (id == t.id && fish == t.fish);
  }
};

class SegmentTree{
private:
  struct Participant* participants;
  int n;
public:
  SegmentTree(int _n){
    n = 1;
    while(n < _n) n *= 2;

    participants = new Participant[2*n+1];
    for(int i=0;i<2*n+1;i++){
      participants[i] = Participant(i,0);
    }

  }

  void insert(int idx,int f){
    idx += n - 1;

    participants[idx].id = idx - (n - 1);
    participants[idx].fish += f;

    while(idx > 0){
      idx = (idx - 1) / 2;
      int lhs =idx * 2 + 1;
      int rhs =idx * 2 + 2;

      if(participants[lhs].fish < participants[rhs].fish){
	participants[idx].fish = participants[rhs].fish;
	participants[idx].id = participants[rhs].id;
      }
      else if(participants[lhs].fish > participants[rhs].fish){
	participants[idx].fish = participants[lhs].fish;
	participants[idx].id = participants[lhs].id;
      }
      else if(participants[lhs].fish == participants[rhs].fish){
	int next_id = min(participants[lhs].id,participants[rhs].id);
	participants[idx].fish = participants[rhs].fish;
	participants[idx].id = next_id;
      }
    }
  }

  Participant query(int a,int b,int idx,int l,int r){
    if(r <= a || b <= l) return Participant(0,-100000);
    if(a <= l && r <= b) return participants[idx];
    else{
      Participant left = query(a,b,idx * 2 + 1,1,(l+r) / 2);
      Participant right = query(a,b,idx * 2 + 2,(l+r) / 2,r);
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
  int total_participants;
  int total_events;

  while(~scanf("%d %d",&total_participants,&total_events)){
    SegmentTree seg_tree(total_participants);

    for(int event_idx = 0; event_idx < total_events; event_idx++){
      int id;
      int fish;
      scanf("%d %d",&id,&fish);
      seg_tree.insert(id,fish);

      Participant p = seg_tree.query(0,total_participants,0,0,total_participants);
      printf("%d %d\n",p.id, p.fish);
    }
  }
}
