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
      string tmp_stage;
      cin >> tmp_stage;
      vector<int> stage;
      for(int i = 0; i < tmp_stage.size(); i++){
	stage.push_back(tmp_stage[i] - '0');
      }

      int count = 0;
      while(stage.size() >= 2){
	stringstream ss;
	ss << (stage[stage.size()-2] + stage[stage.size()-1]);
	stage.pop_back();
	stage.pop_back();
	for(int i = 0; i < ss.str().size(); i++){
	  stage.push_back(ss.str()[i] - '0');
	}
	count++;
      }
      printf("%s\n",count % 2 == 0 ? "Audrey wins." : "Fabre wins.");
    }
  }
}
