#define _USE_MATH_DEFINES
#define INF 100000000
 
#include <iostream>
#include <cstdio>
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
typedef pair <int,P> PP;
 
static const double EPS = 1e-8;
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};

struct Purse{
  int possess10;
  int possess100;
  Purse(int _p10,int _p100){
    possess10 = _p10;
    possess100 = _p100;
  }
};
 
int main(){
  int total_2DRespecters;
  int init_storage10;
  int init_storage100;
  int upper_storage10;
  while(~scanf("%d %d %d %d",
	       &total_2DRespecters,
	       &init_storage10,
	       &init_storage100,
	       &upper_storage10)){

    vector<Purse> respecters;
    for(int respect_idx = 0; respect_idx < total_2DRespecters; respect_idx++){
      int possess10,possess100;
      scanf("%d %d",&possess10,&possess100);
      respecters.push_back(Purse(possess10,possess100));
    }
  }
}
