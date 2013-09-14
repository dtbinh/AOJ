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

int main(){
  int N;
  while(~scanf("%d",&N)){
    ll c_left = 0;
    ll c_right = 0;
    for(int i=0;i<N;i++){
      
      int pos,insert_num;
      char insert_char[2];
      scanf("%d %s %d",&pos,insert_char,&insert_num);
      if(insert_char[0] == '(') c_left += insert_num;
      else if(insert_char[0] == ')') c_right += insert_num;
      
      printf("%s\n",(c_left == c_right ? "Yes" : "No"));
    }
  }
}
