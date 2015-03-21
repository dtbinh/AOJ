#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f

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
#include <assert.h>
  
using namespace std;
  
typedef long long ll;
typedef pair <int,int> P;
typedef pair <double,P> PP;
  
static const double EPS = 1e-8;

class SternBrocotTree {
public:
  SternBrocotTree(int B,int p)
    : max_depth(0),
      ans_left_numerator(0),
      ans_right_numerator(0),
      ans_left_denominator(0),
      ans_right_denominator(0){
    this->B = B;
    this->p = p;
  }

  void dfs(int left_numerator,int left_denominator,
	   int right_numerator,int right_denominator,int depth){
    int next_numerator = left_numerator + right_numerator;
    int next_denominator = left_denominator + right_denominator;

    if(contains(left_numerator,left_denominator,next_numerator,next_denominator)){
      dfs(left_numerator,left_denominator,next_numerator,next_denominator,depth+1);
    }

    if(max_depth < depth){
      max_depth = depth;
      ans_right_numerator = right_numerator;
      ans_right_denominator = right_denominator;
      ans_left_numerator = left_numerator;
      ans_left_denominator = left_denominator;
    }

    if(contains(next_numerator,next_denominator,right_numerator,right_denominator)){
      dfs(next_numerator,next_denominator,right_numerator,right_denominator,depth+1);
    }
  }
  void disp(){
    printf("%d/%d %d/%d\n",
	   ans_right_numerator,ans_right_denominator,
	   ans_left_numerator,ans_left_denominator);
  }
private:
  int B;
  int p;
  int max_depth;
  int ans_left_numerator;
  int ans_left_denominator;
  int ans_right_numerator;
  int ans_right_denominator;
  
  bool contains(int left_numerator,int left_denominator,
		int right_numerator,int right_denominator){
    if(left_numerator > B || left_denominator > B
       || right_numerator > B || right_denominator > B) return false;
    if(left_numerator * left_numerator < left_denominator * left_denominator * p
       && p * right_denominator * right_denominator < right_numerator * right_numerator){
      return true;
    }
    return false;
  }
};

int main(){
  int p;
  int n;

  while(~scanf("%d %d",&p,&n)){
    if(p == 0 && n == 0) break;
    SternBrocotTree sbt(n,p);
    sbt.dfs(0,1,1,0,0);
    sbt.disp();
  }
}
