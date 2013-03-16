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
 
typedef long long ll;
using namespace std;
 
int gcd(int a, int b)
{
  if(b == 0)
    {
      return a;
    }
  else
    {
      return gcd(b, a % b);
    }
}
 
int main()
{
  int a,b;
  while(~scanf("%d %d",&a,&b)){
    printf("%d %d\n",gcd(a,b),a/gcd(a,b)*b);
  }
}
