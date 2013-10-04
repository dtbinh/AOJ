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
 
static const double EPS = 1e-8;

int gPos = 0;

void parse_CAT(const string& str){
  if(gPos >= str.size()) return;

  if(gPos < str.size() && str[gPos++] != 'm'){
    gPos--;
    return;
  }
  parse_CAT(str);
  if(gPos < str.size() && str[gPos++] != 'e'){
    gPos--;
    return;
  }

  parse_CAT(str);
  if(gPos < str.size() && str[gPos++] != 'w'){
    gPos--;
    return;
  }

  return;
}

int main(){
  string str;
  while(cin >> str){
    gPos = 0;
    parse_CAT(str);
    printf("%s\n",(gPos != str.size()) ? "Rabbit" : "Cat");
  }
}
