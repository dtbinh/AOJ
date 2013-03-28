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

bool isSymmetry(string str){
  // x := i w ""
  // "i" x "i"
  // "w" x "w"
  // "(" x ")"
  // ")" x "("
  // "{" x "}"
  // "}" x "{"
  // "[" x "]"
  // "]" x "["
  for(int i=0,j=str.size()-1;i<str.size() && i <= j;i++,j--){
    if(str[i] == 'i' && str[j] != 'i') return false;
    else if(str[i] == 'w' && str[j] != 'w') return false;
    else if(str[i] == '(' && str[j] != ')') return false;
    else if(str[i] == ')' && str[j] != '(') return false;
    else if(str[i] == '{' && str[j] != '}') return false;
    else if(str[i] == '}' && str[j] != '{') return false;
    else if(str[i] == '[' && str[j] != ']') return false;
    else if(str[i] == ']' && str[j] != '[') return false;
  }
  return true;
}

bool has_iwi(string str){

  int iwi_num = 0;
  for(int i=0;i+2<str.size();i++){
    if(str[i] == 'i'
       && str[i+1] == 'w'
       && str[i+2] == 'i'){
      iwi_num++;
    }
  }
  if(iwi_num != 1) return false;

  int i_num=0;
  int w_num=0;
  for(int i=0;i<str.size();i++){
    if(str[i] == 'i') i_num++;
    if(str[i] == 'w') w_num++;
  }

  if(i_num != iwi_num*2) return false;
  if(w_num != iwi_num) return false;

  return true;
}

int main(){
  char buf[16];

  while(~scanf("%s",buf)){
    int res = 0;
    for(int S=0;S<=(1<<strlen(buf)) -1; S++){
      string str = "";
      for(int i=0;i<strlen(buf);i++){
	if(S & (1<<i)) str.push_back(buf[i]);
      }
      if(!has_iwi(str)) continue;
      if(isSymmetry(str)) res = max(res,(int)str.size());
    }
    printf("%d\n",res);
  }
}
