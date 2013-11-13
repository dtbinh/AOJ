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

class Nodes {
public:
  class Nodes* children[256];
  bool has_word;
  Nodes() : has_word(false){
    for(int i=0;i<256;i++){
      children[i] = NULL;
    }
  }
};

class Trie {
private:
  Nodes* root;
public:
  Trie(){
    root = new Nodes();
  }

  void insert(const string& str){
    Nodes* current = root;
    for(int i=0;i<str.size();i++){
      char c = str[i];
      if(current->children[c] == NULL){
	current->children[c] = new Nodes();
      }
      current = current->children[c];
    }
    current->has_word = true;
  }

  bool common_prefix_search(const string& str){
    Nodes* current = root;

    for(int i=0;i<str.size();i++){
      char c = str[i];
      if(current->children[c] != NULL){
	current = current->children[c];
      }
      else{
	return false;
      }

      if(current->has_word) return true;
    }

    return false;
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

    Trie trie;
    for(int sequence_idx=0;sequence_idx < total_prohibited_sequences;sequence_idx++){
      string str;
      cin >> str;
      trie.insert(str);
    }

    
  }
}
