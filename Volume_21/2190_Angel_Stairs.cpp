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

class State {
public:
  int stair_pos;
  int note_pos;
  int cost;
  State(int stair_pos,int note_pos,int cost) :
    stair_pos(stair_pos),note_pos(note_pos), cost(cost) {}
  bool operator<(const State& s) const {
    return cost < s.cost;
  }
  bool operator>(const State& s) const {
    return cost > s.cost;
  }
};

map<string,int> note2idx;
string idx2note[] = {
  "C",
  "C#",
  "D",
  "D#",
  "E",
  "F",
  "F#",
  "G",
  "G#",
  "A",
  "A#",
  "B"
};

map<int,bool> dp[50001];

int main(){
  int total_test_cases;
  note2idx["C"] = 0;
  note2idx["C#"] = 1;
  note2idx["D"] = 2;
  note2idx["D#"] = 3;
  note2idx["E"] = 4;
  note2idx["F"] = 5;
  note2idx["F#"] = 6;
  note2idx["G"] = 7;
  note2idx["G#"] = 8;
  note2idx["A"] = 9;
  note2idx["A#"] = 10;
  note2idx["B"] = 11;

  while(~scanf("%d",&total_test_cases)){
    for(int i = 0; i <= 50000; i++){
      dp[i].clear();
    }
    for(int test_i = 0; test_i < total_test_cases; test_i++){
      int num_of_steps;
      int song_length;
      scanf("%d %d",&num_of_steps,&song_length);
      vector<string> stair;
      vector<string> song;
      for(int i = 0; i < num_of_steps; i++){
	string note;
	cin >> note;
	stair.push_back(note);
      }
      for(int i = 0; i < song_length; i++){
	string note;
	cin >> note;
	song.push_back(note);
      }

      priority_queue<State> que;
      que.push(State(-1,-1,0));

      bool isok = false;
      while(!que.empty()){
	State s = que.top();
	que.pop();

	if(s.note_pos == song_length - 1
	   && s.stair_pos >= num_of_steps - 2){
	  isok = true;
	  break;
	}
	for(int dist = -1; dist <= 2; dist++){
	  if(dist == 0) continue;

	  int next = s.stair_pos + dist;
	  if(next < 0) continue;
	  if(next >= num_of_steps) continue;

	  int offset = 0;
	  if(dist == -1) offset = 12 - 1;
	  if(dist == 2) offset = 1;
	  if(song[s.note_pos + 1] != idx2note[(note2idx[stair[next]] + offset) % 12]) continue;
	  if(dp[s.note_pos + 1].find(next) != dp[s.note_pos + 1].end()) continue;
	  dp[s.note_pos + 1][next] = true;
	  que.push(State(next,s.note_pos + 1,s.cost + 1));
	}
      }
      printf("%s\n",isok ? "Yes" : "No");
    }
  }
}
