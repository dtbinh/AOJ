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
 
const static int tx[] = {0,1,1,1,0,-1,-1,-1};
const static int ty[] = {-1,-1,0,1,1,1,0,-1};
 
static const double EPS = 1e-12;

void dfs(vector<int>& log){
}

int main(){
  string str;
  while(cin >> str){
    string shrinked = "";
    for(int i=0;i<str.size();){
      if(i+3 <= str.size()
	 && str.substr(i,3) == "egg"){
	shrinked += "0";
	i+=3;
	continue;
      }
      else if(i+7 <= str.size() 
	      && str.substr(i,7) == "chicken"){
	shrinked += "1";
	i+=7;
	continue;
      }
      i++;
    }

    vector<string> log;
    int prev = 0;
    for(int i=0;i+1<shrinked.length();i++){
      if(shrinked[i] == shrinked[i+1]){
	log.push_back(shrinked.substr(prev,i-prev + 1));
	prev = i+1;
      }
    }
    if(prev < shrinked.length()){
      log.push_back(shrinked.substr(prev,shrinked.size()-prev));
    }

    int max_length = 0;
    string res = "egg";
    for(int i=0;i<log.size();i++){
      if(max_length < log[i].length()){
	max_length = log[i].length();
	if(log[i][log[i].length()-1] == '1'){
	  res = "chicken";
	}
	if(log[i][log[i].length()-1] == '0'){
	  res = "egg";
	}
      }
    }

    cout << res << endl;
  }
}
