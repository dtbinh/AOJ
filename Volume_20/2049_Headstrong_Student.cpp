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

int visited[1000001];

int main(){
  int dividend;
  int divisor;
  while(~scanf("%d %d",&dividend,&divisor)){
    if(divisor == 0) break;
    
    memset(visited,-1,sizeof(visited));

    int pos = 0;
    int len = 0;
    for(int i = 0; i < 10; i++){
      // cout << "i" << i << " ";
      if(dividend % divisor == 0){
	// cout << dividend / divisor << endl;
	pos = i;
	len = 0;
	break;
      }
      // cout << dividend / divisor << endl;
      // cout << dividend % divisor << endl;
      if(visited[dividend % divisor] != -1){
	pos = visited[dividend % divisor];
	len = i - visited[dividend % divisor];
	break;
      }
      visited[dividend % divisor] = i;
      dividend %= divisor;
      dividend *= 10;
    }

    printf("%d %d\n",pos,len);
  }
}
