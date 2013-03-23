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
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

string GenerateNextHand(char head,char tail,map<string,bool>& used){
  for(char i='a';i<='z';i++){
    for(char j='a';j<='z';j++){
      string str = "";
      str.push_back(head);
      str.push_back(i);
      str.push_back(j);
      str.push_back(tail);
      // printf("%s\n",str.c_str());
      if(used.find(str) == used.end()){
	return str;
      }
    }
  }
}

int main(){
  printf("?aj\n"); fflush(stdout);
  char buf[128];
  map<string,bool> used;
  used["aj"] = true;
  string prev_my_hand = "aj";
  char next_my_tail = 'j';

  while(~scanf("%s",buf)){
    if(buf[0] != prev_my_hand[prev_my_hand.size()-1]
       || used.find(buf) != used.end()){
      printf("!OUT\n");
      fflush(stdout);
    }

    used[buf] = true;
    char next_my_head = buf[strlen(buf)-1];
    prev_my_hand = GenerateNextHand(next_my_head,next_my_tail,used);
    used[prev_my_hand] = true;
    printf("?%s\n",prev_my_hand.c_str());
    fflush(stdout);
  }
}
