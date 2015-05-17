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

map<string,int> note2idx;
const static int idx2dist[] = {-1,1,2};
const static int offset[] = {11,0,1};

int dfs(int note_pos,int stair_pos,
	const vector<int>& stair,const vector<int>& song){

  if(stair_pos + 2 * (song.size() - note_pos) < stair.size() - 2){
    return false;
  }

  if(note_pos == song.size() - 1
     && stair_pos >= stair.size() - 2){
    return true;
  }
  else if(note_pos == song.size() - 1){
    return false;
  }

  bool res = false;
  for(int i = 0; i < 3; i++){
    int next = stair_pos + idx2dist[i];
    if(next < 0 || next >= stair.size()) continue;
    if(song[note_pos + 1] != (stair[next] + offset[i]) % 12) continue;
    res |= dfs(note_pos + 1,next,stair,song);
  }
  return res;
}

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
    for(int test_i = 0; test_i < total_test_cases; test_i++){
      int num_of_steps;
      int song_length;
      scanf("%d %d",&num_of_steps,&song_length);
      vector<int> stair;
      vector<int> song;
      for(int i = 0; i < num_of_steps; i++){
	string note;
	cin >> note;
	stair.push_back(note2idx[note]);
      }
      for(int i = 0; i < song_length; i++){
	string note;
	cin >> note;
	song.push_back(note2idx[note]);
      }

      printf("%s\n",dfs(-1,-1,stair,song) ? "Yes" : "No");
    }
  }
}
