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

int main(){
  int total_questions;
  int total_ppl;
  while(~scanf("%d %d",&total_questions,&total_ppl)){
    if(total_questions == 0 && total_ppl == 0) break;

    vector<string> answers;
    for(int ppl_i = 0; ppl_i < total_ppl; ppl_i++){
      string ans;
      cin >> ans;
      answers.push_back(ans);
    }

    int res = INF;
    for(int S = 0; S <= (1<<total_questions) - 1; S++){
      map<string,int> freq;

      for(int ppl_i = 0; ppl_i < total_ppl; ppl_i++){
	string tmp = "";
	for(int question_i = 0; question_i < total_questions; question_i++){
	  if(!(S & (1 << question_i))) continue;
	  tmp.push_back(answers[ppl_i][question_i]);
	}
	freq[tmp]++;
      }

      bool isok = true;
      for(map<string,int>::iterator it = freq.begin();
	  it != freq.end();
	  it++){
	if(it->second > 1){
	  isok = false;
	  break;
	}
      }

      if(isok){
	res = min(res,__builtin_popcount(S));
      }
    }

    printf("%d\n",res);
  }
}
