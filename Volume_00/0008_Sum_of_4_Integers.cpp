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
 
int main(){
  int n;
  while(~scanf("%d",&n)){
    int res = 0;
    for(int a=0;a<=9;a++)
      for(int b=0;b<=9;b++)
	for(int c=0;c<=9;c++)
	  for(int d=0;d<=9;d++)
	    if(a+b+c+d == n) res++;
    printf("%d\n",res);
  }
}
