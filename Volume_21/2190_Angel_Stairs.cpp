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

int main(){
  int total_test_cases;
  while(~scanf("%d",&total_test_cases)){
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
    }
  }
}
