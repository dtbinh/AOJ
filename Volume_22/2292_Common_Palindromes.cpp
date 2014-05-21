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
  int* rank;
  int* tmp;
  int* sa;
  int n;
  bool compare_sa(int i,int j,int k) const{
    if(rank[i] != rank[j]) return rank[i] < rank[j];
    else {
      int ri = i + k <= n ? rank[i + k] : -1;
      int rj = j + k <= n ? rank[j + k] : -1;
      return ri < rj;
    }
  }
  void construct_sa(){
    for(int i= 0; i <= n;i++){
      sa[i] = i;
      rank[i] = (i < n ? S[i] : -1);
    }
    
    for(int k = 1; k <= n; k *= 2){
      qsort(0,n + 1,k);
      
      tmp[sa[0]] = 0;
      for(int i=1;i<= n;i++){
	tmp[sa[i]] = tmp[sa[i-1]] + (compare_sa(sa[i-1],sa[i],k) ? 1 : 0);
      }
      for(int i=0;i<=n;i++){
	rank[i] = tmp[i];
      }
    }
  }

  void qsort(int lhs,int rhs,int k){
    if(lhs >= rhs) return;
    int pivot = (lhs + rhs) / 2;
    
    int i = lhs;
    int j = rhs;
    while(i < j){
      while(i < pivot && compare_sa(i,pivot,k)){
	i++;
      }
      while(pivot < j && compare_sa(pivot,j,k)){
	j--;
      }
      swap(sa[i],sa[j]);
      i++; j--;
    }

    qsort(lhs,pivot-1,k);
    qsort(pivot+1,rhs,k);
  }
public:
  SuffixArray(const string& _S){
    S = _S;
    n = S.length();
    rank = new int[n+10]; //not to be too small
    tmp = new int[n+10];
    sa = new int[n+10];
    construct_sa();
  }

  ~SuffixArray(){
    delete[] rank;
    delete[] tmp;
    delete[] sa;
  }

  int bsearch_first(const string& T){
    int a = 0;
    int b = S.length();
    while(b - a > 1){
      int c = (a + b) / 2;
      if(S.compare(sa[c],T.length(),T) > 0){
	a = c;
      }
      else{
	b = c;
      }
    }
    if(b >= S.length() || S.compare(sa[b],T.length(),T) != 0){
      return -1;
    }
    return b;
  }

  bool bsearch_last(const string& T){
    int a = 0;
    int b = S.length();
    while(b - a > 1){
      int c = (a + b) / 2;
      if(S.compare(sa[c],T.length(),T) < 0){
	a = c;
      }
      else{
	b = c;
      }
    }

    if( b < 0 || S.compare(sa[b],T.length(),T) != 0){
      return -1;
    }
    return b;
  }

  int hits(const string& T){
    int first = bsearch_first(T);
    int last = bsearch_last(T);

    if(first == -1 || last == -1) return 0;
    
    return last - first + 1;
  }
};
  
int main(){
  string from;
  while(cin >> from){
    string to;
    cin >> to;
    SuffixArray sa(to);
    int res = 0;
    for(int i=0;i<from.size();i++){
      string query = "";
      for(int length=1;i + length<=from.size();length++){
	query += from[i + length - 1];
	if(query.size() > to.size()) continue;
	res += sa.hits(query);
      }
    }

    printf("%d\n",res);
  }
}
