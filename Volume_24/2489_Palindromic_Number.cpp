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
  
using namespace std;
  
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P> PP;
  
static const double EPS = 1e-8;

static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};

int main(){
  vector<int> palindrome;
  for(int i=1;i<=10000;i++){
    stringstream ss;
    ss << i;
    string str;
    string r_str;
    ss >> str;

    r_str = str;
    reverse(r_str.begin(),r_str.end());


    if(str == r_str){
      palindrome.push_back(i);
    }
  }

  sort(palindrome.begin(),palindrome.end());
  int num;
  while(~scanf("%d",&num)){
    int idx = lower_bound(palindrome.begin(),palindrome.end(),num) - palindrome.begin();

    int cand[3] = {INF,INF,INF};

    if(idx - 1 >= 0) cand[0] = palindrome[idx-1]; 
    cand[1] = palindrome[idx]; 
    if(idx + 1 < palindrome.size()) cand[2] = palindrome[idx+1];

    int diff = INF;
    int res = INF;
    for(int i=0;i<3;i++){
      if(abs(cand[i] - num) < diff){
	res = cand[i];
	diff = abs(cand[i] - num);
      }
      else if(abs(cand[i] - num) == diff){
	res = min(res,cand[i]);
      }
    }
    printf("%d\n",res);
  }
}
