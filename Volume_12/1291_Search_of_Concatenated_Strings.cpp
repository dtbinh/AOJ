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
#include <iterator>
#include <complex>
#include <assert.h>
 
using namespace std;
 
typedef long long ll;
typedef pair <double,double> P;
typedef pair <int,P > PP;
 
int tx[] = {+0,+1,+0,-1};//URDL
int ty[] = {-1,+0,+1,+0};
 
static const double EPS = 1e-8;

bool dp[5500][1<<12];

int main(){
  int num_of_element_strings;
  int num_of_lines;
  while(~scanf("%d %d",&num_of_element_strings,&num_of_lines)){
    if(num_of_element_strings == 0 && num_of_lines == 0) break;

    vector<string> elements;
    for(int i = 0; i < num_of_element_strings; i++){
      string tmp;
      cin >> tmp;
      elements.push_back(tmp);
    }

    string text= "";
    for(int i = 0; i < num_of_lines; i++){
      string tmp;
      cin >> tmp;
      text += tmp;
    }

    memset(dp,false,sizeof(dp));
    for(int i = 0; i < elements.size(); i++){
      int next = 0;
      while(true){
	int current = text.find(elements[i],next);
	if(current == string::npos) break;
	dp[current + elements[i].size()][1<<i] = true;
	next = current + 1;
      }
    }

    for(int text_i = 0; text_i < text.size(); text_i++){
      for(int S = 0; S < (1<<elements.size()); S++){
	if(!dp[text_i][S]) continue;
	for(int to = 0; to < elements.size(); to++){
	  if((S & (1<<to))) continue;
	  dp[text_i + elements[to].size()][S | (1<<to)] 
	    |= dp[text_i + elements[to].size()][(1<<to)];
    	}
      }
    }
    int res = 0;
    for(int text_i = 0; text_i <= text.size(); text_i++){
      if(dp[text_i][(1<<elements.size()) - 1]) res++;
    }
    printf("%d\n",res);
  }
}
