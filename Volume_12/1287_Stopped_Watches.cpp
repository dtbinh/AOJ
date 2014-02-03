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

void check(int hands[3],vector<int>& candidates){
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
	      candidates.push_back(h*60*60+m*60+s);
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
    vector<int> watches[total_watches];
    vector<int> all_times;
    for(int watch_idx = 0; watch_idx < total_watches; watch_idx++){
      int hands[3];
      for(int hand_idx = 0; hand_idx < 3; hand_idx++){
	scanf("%d",hands + hand_idx);
      }
      vector<int> candidates;
      check(hands,candidates);
      watches[watch_idx] = candidates;

      for(int candidate_idx=0;candidate_idx < candidates.size(); candidate_idx++){
	all_times.push_back(candidates[candidate_idx]);
      }
    }
    sort(all_times.begin(),all_times.end());
    all_times.erase( unique(all_times.begin(), all_times.end()), all_times.end() );

    int min_diff = INF;
    string res = "";
    for(int first_idx = 0; first_idx < all_times.size(); first_idx++){
      for(int last_idx = first_idx; last_idx < all_times.size(); last_idx++){
	int first_time = all_times[first_idx];
	int last_time = all_times[last_idx];

	bool isok = true;

	int diff = all_times[last_idx] - all_times[first_idx];
	for(int watch_idx=0;watch_idx < total_watches;watch_idx++){
	  const vector<int>& candidates = watches[watch_idx]; 

	  int first_time_idx = lower_bound(candidates.begin(),candidates.end(),first_time) - candidates.begin();

	  if(first_time_idx >= candidates.size()
	     || candidates[first_time_idx] > last_time){
	    isok = false;
	    break;
	  }
	}

	if(isok
	   && min_diff > diff){
	  min_diff = diff;
	  char buf[64];
	  sprintf(buf,"%02d:%02d:%02d %02d:%02d:%02d",
		  first_time/3600,(first_time%3600)/60,first_time%60,
		  last_time/3600,(last_time%3600)/60,last_time%60);
	  res = buf;
	}
      }
    }

    printf("%s\n",res.c_str());
  }
}
