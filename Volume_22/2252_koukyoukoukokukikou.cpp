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
 
int tx[] = {1,-1};
 
static const double EPS = 1e-8;
 
int main(){
  string buf;
  string lhs = "qwertasdfgzxcvb";
  string rhs = "yuiophjklnm";
  sort(lhs.begin(),lhs.end());
  sort(rhs.begin(),rhs.end());
 
  while(cin >> buf){
    if(buf == "#") break;
    int res = 0;
    bool flag = (lhs.find(buf[0]) != string::npos ? true : false);
    for(int i=1;i<buf.size();i++){
      bool old_flag = flag;
      flag = (lhs.find(buf[i]) != string::npos ? true : false);
      if(old_flag != flag) res++;
    }
 
    printf("%d\n",res);
  }
}
