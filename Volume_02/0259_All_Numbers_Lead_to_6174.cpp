#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
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

bool is_all_same(string num){
  sort(num.begin(),num.end());
  for(int i=0;i+1<num.size();i++){
    if(num[i] != num[i+1]){
      return false;
    }
  }
  return true;
}

bool is_6174(const string& num){
  if(num[0] == '6'
     && num[1] == '1'
     && num[2] == '7'
     && num[3] == '4'){
    return true;
  }

  return false;
}

bool is_0000(const string& num){
  if(num[0] == '0'
     && num[1] == '0'
     && num[2] == '0'
     && num[3] == '0'){
    return true;
  }

  return false;
}

int main(){
  string LminusS;
  
  while(cin >> LminusS){
    if(is_0000(LminusS)) break;

    int count = INF;
    for(int round=0;round <= 1000000;round++){
      if(is_all_same(LminusS)) break;
      if(is_6174(LminusS)){
	count = round;
	break;
      }
      string smaller = LminusS;
      sort(smaller.begin(),smaller.end());
      
      string larger = LminusS;
      sort(larger.begin(),larger.end(),greater<char>());

      int num = atoi(larger.c_str()) - atoi(smaller.c_str());
      stringstream ss;
      ss << num;
      string next = ss.str();
      while(next.size() < 4) next = "0" + next;
      LminusS = next;
    }

    if(count == INF){
      printf("NA\n");
    }
    else {
      printf("%d\n",count);
    }
  }
}
