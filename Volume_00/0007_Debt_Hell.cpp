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
  scanf("%d",&n);
  double base = 100000;
  for(int i=0;i<n;i++){
    base*=1.05;
    if((int)base %1000 !=0) {
      int tmp = (int)base / 1000;
      base = tmp*1000 + 1000;
    }
 
  }
  printf("%d\n",(int)base);
}
