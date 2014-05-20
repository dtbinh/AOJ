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
 
const int tx[] = {0,1,1,0};
const int ty[] = {0,0,1,1};
 
static const double EPS = 1e-8;


class SuffixArray {
private:
  string S;
  int k; //word length
  int n;
  int* rank;
  int* tmp;
  int* sa;
  
  void construct_sa(){
    for(int i= 0; i <= n;i++){
      sa[i] = i;
      rank[i] = i < n ? S[i] : -1;
    }
    
    for(k = 1; k <= n; k *= 2){
      sort(sa,sa + (n + 1),compare_sa);
      
      tmp[sa[0]] = 0;
      for(int i=1;i<= n;i++){
	tmp[sa[i]] = tmp[sa[i-1]] + (compare_sa(sa[i-1],sa[i]) ? 1 : 0);
      }
      for(int i=0;i<=n;i++){
	rank[i] = tmp[i];
      }
    }
  }

  bool compare_sa(int i,int j) const{
    if(rank[i] != rank[j]) return rank[i] < rank[j];
    else {
      int ri = i + k <= n ? rank[i + k] : -1;
      int rj = j + k <= n ? rank[j + k] : -1;
      return ri < rj;
    }
  }
public:
  SuffixArray(const string& S){
    n = S.length();
    rank = new int[n+1];
    tmp = new int[n+1];
    sa = new int[n+1];
    construct_sa();
  }

  ~SuffixArray(){
    delete[] rank;
    delete[] tmp;
    delete[] sa;
  }

  bool contain(const string& T){
    int a = 0;
    int b = S.length();
    while(b - a > 1){
      int c = (a + b) / 2;
      if(S.compare(sa[c],T.length(),T) < 0) a = c;
      else b = c;
    }
    return S.compare(sa[b],T.length(),T) == 0;
  }
};

bool compare_sa(int i,int j){
  if(rank[i] != rank[j]) return rank[i] < rank[j];
  else {
    int ri = i + k <= n ? rank[i + k] : -1;
    int rj = j + k <= n ? rank[j + k] : -1;
    return ri < rj;
  }
}
  
int main(){
  
}
