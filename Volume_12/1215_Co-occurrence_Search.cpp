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
typedef pair <int,P> PP;
  
static const double EPS = 1e-8;

void print_text(const string& text){
  int offset = 0;
  int text_i = 0;
  while(offset < text.size()){
    for(text_i = offset; text_i < text.size(); text_i++){
      if(text_i - offset >= 72) break;
      printf("%c",text[text_i]);
    }
    printf("\n");
    offset += 72;
  }
}

void print_co_occurrence(const string& text,const string& query){

  int head = 0;
  int tail = 0;

  int include_keys = 0;
  int freq[256] = {};

  bool is_key[256];
  memset(is_key,false,sizeof(is_key));

  for(int query_i = 0; query_i < query.size(); query_i++){
    is_key[query[query_i]] = true;
  }

  int min_tail = INF;
  int min_len = INF;
  int ans_freq = 0;
  string ans = "";

  while(tail < text.size()){
    for(;head < text.size();head++){
      if(is_key[text[head]] && !freq[text[head]]++){
	include_keys++;
	if(include_keys == query.size()){
	  head++;
	  break;
	}
      }
    }

    for(;tail <= head;tail++){
      if(is_key[text[tail]] && !--freq[text[tail]]){

	if(include_keys == query.size()) {
	  if((head -1) - tail + 1 < min_len){
	    min_len = (head -1) - tail + 1;
	    ans = text.substr(tail,(head -1) - tail + 1);
	    ans_freq = 1;
	  }
	  else if((head -1) - tail + 1 == min_len){
	    ans_freq++;
	  }
	}
	include_keys--;
	tail++;
	break;
      }
    }
  }

  if(ans_freq == 0){
    printf("%d\n",ans_freq);
    printf("\n");
  }
  else{
    printf("%d\n",ans_freq);
    printf("\n");
    print_text(ans);
    printf("\n");
  }
}

int main(){
  string str;
  int phase = 0;
  string text = "";
  string query = "";
  while(getline(cin,str)){
    if(str.size() == 0){
      phase++;
      continue;
    }
    if(phase % 2 == 0){
      text += str;
    }
    else{
      query = str;

      print_co_occurrence(text,query);
      
      query = "";
      text = "";
    }
  }
}
