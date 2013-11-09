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
typedef pair <ll,ll> P;
typedef pair <int,P > PP;
 
const static int tx[] = {1,0,-1,0};
const static int ty[] = {0,1,0,-1};

static const double EPS = 1e-8;

ll segments[2][100000];

void make_segment(const vector<ll>& bomb_points,ll segments[2][100000]){
  memset(segments,0,sizeof(segments));

  for(int i=0;i<bomb_points.size();i++){
    if(i % 2 == 0){
      ///center is used
      //c --- seg0 ---| --- seg1(erased) -- | --- seg2 -- |
      ll next = bomb_points[i];
      ll prev = i-1 >= 0 ? bomb_points[i-1] : 0;
      ll sum = i-2 >= 0 ? segments[1][i-2] : 0;
      segments[1][i] = next - prev + sum;

      segments[0][i] = (i-1 >= 0 ? segments[0][i-1] : 0);
    }
    else if(i % 2 == 1){
      ///center is not used
      //c --- seg0(erased) ---| --- seg1 -- | --- seg2(erased) -- |
      ll next = bomb_points[i];
      ll prev = i-1 >= 0 ? bomb_points[i-1] : 0;
      ll sum = i-2 >= 0 ? segments[0][i-2] : 0;
      segments[0][i] = next - prev + sum;

      segments[1][i] = (i-1 >=0 ? segments[1][i-1] : 0);
    }
  }
}

bool judge_center_used(int end_point,const vector<ll>& bomb_points){
  //c --- seg0 ---| --- seg1 -- | --- seg2 -- |
  //                                   e      |<-lower_bound
  int outer_bomb_point_idx
    = lower_bound(bomb_points.begin(),bomb_points.end(),end_point) - bomb_points.begin();
  return outer_bomb_point_idx % 2 == 0;
}

bool judge_here_used(int end_point,bool is_center_used,const vector<ll>& bomb_points){
  //c --- seg0 ---| --- seg1 -- | --- seg2 -- |
  //                                   e      |<-lower_bound
  int outer_bomb_point_idx
    = lower_bound(bomb_points.begin(),bomb_points.end(),end_point) - bomb_points.begin();
  return (is_center_used ? outer_bomb_point_idx % 2 == 0 : outer_bomb_point_idx % 2 != 0);
}

ll compute_segment_distance(const vector<ll>& bomb_points,ll segments[2][100000],int start, int end){
  int yard_lhs_point = min(start,end);
  int yard_rhs_point = max(start,end);

  // c --- y_lhs --- BOMB --- BOMB --- y_rhs
  int bomb_lhs_idx = lower_bound(bomb_points.begin(),bomb_points.end(),yard_lhs_point) - bomb_points.begin();
  int bomb_rhs_idx = lower_bound(bomb_points.begin(),bomb_points.end(),yard_rhs_point) - bomb_points.begin() - 1;
  
  if(bomb_lhs_idx > bomb_rhs_idx){
    // printf("s:%d e:%d yard:%d\n",start,end,abs(yard_rhs_point-yard_lhs_point));
    return abs(yard_rhs_point-yard_lhs_point);
  }
  else if(bomb_lhs_idx < bomb_rhs_idx){
    bool is_center_used = judge_center_used(start,bomb_points);

    bool is_lhs_yard_used = judge_here_used(yard_lhs_point,is_center_used,bomb_points);
    bool is_rhs_yard_used = judge_here_used(yard_rhs_point,is_center_used,bomb_points);

    ll segment_distance =  segments[(int)is_center_used][bomb_rhs_idx] - segments[(int)is_center_used][bomb_lhs_idx];
    
    ll yard_lhs_to_bomb_distance = (is_lhs_yard_used ? bomb_points[bomb_lhs_idx] - yard_lhs_point : 0);
    ll yard_rhs_to_bomb_distance = (is_rhs_yard_used ? yard_rhs_point - bomb_points[bomb_rhs_idx] : 0);
    // printf("%s\n",is_center_used ? "center used" : "no");
    // printf("s:%d e:%d seg:%d ",start,end,segment_distance);    
    // printf("y1:%d y2:%d\n",yard_lhs_to_bomb_distance ,yard_rhs_to_bomb_distance);

    return  segment_distance + yard_lhs_to_bomb_distance + yard_rhs_to_bomb_distance;
  }
  else if(bomb_lhs_idx == bomb_rhs_idx){
    // printf("s:%d e:%d yard:%d\n",start,end,abs(bomb_points[bomb_lhs_idx] - start));
    return  abs(bomb_points[bomb_lhs_idx] - start);

  }
}

int main(){
  int N,M;
  while(~scanf("%d %d",&N,&M)){

    vector<ll> bomb_points;
    vector<P> yarns;
    for(int i=0;i<N;i++){
      ll s,t;
      scanf("%lld %lld",&s,&t);
      yarns.push_back(P(s,t));
    }
    for(int i=0;i<M;i++){
      ll p;
      scanf("%lld",&p);
      bomb_points.push_back(p);
    }

    sort(bomb_points.begin(),bomb_points.end());

    make_segment(bomb_points,segments);

    ll sum = 0;
    for(int yarn_idx=0;yarn_idx<yarns.size();yarn_idx++){
      ll start = yarns[yarn_idx].first;
      ll end = yarns[yarn_idx].second;
      sum += compute_segment_distance(bomb_points,segments,start,end);
    }

    printf("%lld\n",sum);
  }
}
