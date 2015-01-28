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
 
const static int tx[] = {0,1,0,-1};
const static int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

int main(){
  int total_test_cases;
  while(~scanf("%d",&total_test_cases)){
    int cell[30];
    for(int test_i = 0; test_i < total_test_cases; test_i++){
      for(int cell_i = 0; cell_i < 30; cell_i++){
	int num;
	scanf("%d",&num);
	cell[cell_i] = num;
      }
    }
  }
}
