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

static const char iwi[] = {'i','w','(',')'};

int FastPow(int x,int power){
  int res = 1;
  while(power){
    if(power & 1) res *= x;
    x *= x;
    power >>= 1;
  }
  return res;
}

bool isClear(char buf[12]){
  if(strlen(buf) % 2 != 0
     && (buf[strlen(buf) / 2] == '('
	 || buf[strlen(buf) / 2] == ')')) return false;
  for(int i=0,j=strlen(buf)-1;i<strlen(buf)/2;i++,j--){
    if(buf[i] == '(' && buf[j] != ')') return false;
    else if(buf[i] == ')' && buf[j] != '(') return false;
    else if(buf[i] == 'i' && buf[j] != 'i') return false;
    else if(buf[i] == 'w' && buf[j] != 'w') return false;
  }
  return true;
}

int CountFlag(int S){
  int res = 0;
  while(S){
    if(S & 1) res++;
    S >>= 1;
  }
  return res;
}

int main(){
  char buf[12];
  while(~scanf("%s",buf)){
    int upper = FastPow(4,strlen(buf));

    int min_modify_count = INF;
    for(int S=0;S<=upper;S++){
      int tmp_S = S;
      char tmp_buf[12];
      
      int modify_count = 0;
      memset(tmp_buf,'\0',sizeof(tmp_buf));
      strcpy(tmp_buf,buf);

      for(int i=0;i<strlen(tmp_buf);i++){
	if(buf[i] != iwi[tmp_S % 4]) modify_count++;
	tmp_buf[i] = iwi[tmp_S % 4];
	tmp_S /= 4;
      }

      if(!isClear(tmp_buf)) continue;

      min_modify_count = min(modify_count,min_modify_count);
    }
    printf("%d\n",min_modify_count);
  }
}
