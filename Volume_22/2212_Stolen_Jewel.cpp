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
 
//int tx[] = {0,1,0,-1};
//int ty[] = {-1,a0,1,0};
 
const int tx[] = {0,1,1,0};
const int ty[] = {0,0,1,1};
 
static const double EPS = 1e-8;

struct Response {
  bool is_valid;
  int last_pos;
};

class Trie {
private:
  int base[1024];
  int check[1024];
  bool dic[1024];

public:
  Trie(){
    memset(base,0,sizeof(base));
    memset(check,0,sizeof(check));
    memset(dic,false,sizeof(dic));
  }

  Response traverse(int n,int k){
    int m = base[n] + k;
    if (check[m] == n){
      Response r = {true,m};
      return r;
    }
    else{
      //can't find
      Response r = {false,m};
      return r;
    }
  }

  vector<int> common_prefix_search(const string& str) {
    vector<int> result;
    Response r = {true,0};
    for(int i=0;i<str.size();i++){
      r = traverse(r.last_pos,str[i]);
      if(!r.is_valid){
	break;
      }

      if(dic[r.last_pos]){
	result.push_back(r.last_pos);
      }
    }

    return result;
  }

  void init(vector<string> str_v,int pos = 0){
    sort(str_v.begin(),str_v.end());

    bool isok = true;
    for(int v_idx = 0; v_idx < str_v.size(); v_idx++){
      string str = str_v[v_idx];
      common_prefix_search(str);
    }
  }
};

int main(){
  char stage[50][50];
  int H,W;
  while(~scanf("%d %d",&H,&W)){
    for(int y=0;y<H;y++){
      char line[51];
      scanf("%s",line);
      for(int x=0;x<W;x++){
	stage[y][x] = line[x];
      }
    }
    int total_prohibited_sequences;
    scanf("%d",&total_prohibited_sequences);


    for(int sequence_idx=0;sequence_idx < total_prohibited_sequences;sequence_idx++){
      char sequence[12];
      scanf("%s",sequence);
    }
    
  }
}
