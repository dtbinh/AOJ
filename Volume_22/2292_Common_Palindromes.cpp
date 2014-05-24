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

  bool compare_sa(int i,int j,int len) const{
    if(rank[i] != rank[j]) return rank[i] < rank[j];
    else{
      int ri = (i + len <= n ? rank[i + len] : -1);
      int rj = (j + len <= n ? rank[j + len] : -1);
      return ri < rj;
    }
  }

  bool equal_sa(int i,int j,int len) const{
    int ri = (i + len <= n ? rank[i + len] : -1);
    int rj = (j + len <= n ? rank[j + len] : -1);
    
    return (rank[i] == rank[j] && ri == rj);
  }
  void construct_sa(){
    for(int i= 0; i <= n;i++){
      sa[i] = i;
      rank[i] = (i < n ? S[i] : -1);
    }

    for(int len = 1; len <= n; len *= 2){
      sort_sa(0,n,len);
      
      tmp[sa[0]] = 0;
      for(int i=1;i<= n;i++){
	tmp[sa[i]] = tmp[sa[i-1]] + (compare_sa(sa[i-1],sa[i],len) ? 1 : 0);
      }
      for(int i=0;i<=n;i++){
	rank[i] = tmp[i];
      }
    }
  }

  void sort_sa(int lhs,int rhs,int len){
    if(lhs >= rhs) return;
    int i = lhs - 1;
    int j = rhs;
    int pivot = rhs;
    int p = lhs - 1;
    int q = rhs;
    // cout << pivot << endl;

    while(1){
      while(compare_sa(sa[++i],sa[pivot],len));
      while(compare_sa(sa[pivot],sa[--j],len)){
	if(j == lhs)  break;
      }
      if(j <= i) break;
      swap(sa[i],sa[j]);

      if(equal_sa(sa[i],sa[pivot],len)) { p++; swap(sa[p],sa[i]); }
      if(equal_sa(sa[j],sa[pivot],len)) { q--; swap(sa[j],sa[q]); }

    }
    swap(sa[i],sa[rhs]);
    j = i - 1;
    i = i + 1;

    for(int k=lhs; k < p; k++, j--) swap(sa[k],sa[j]);
    for(int k=rhs-1; k > q; k--, i++) swap(sa[i],sa[k]);
    
    sort_sa(lhs,j,len);
    sort_sa(i,rhs,len);
  }
  
  //for debug
  void disp(){
    for(int i=0;i<=S.length();i++){
      printf("rank[%d] := %d",sa[i], rank[sa[i]]);
      printf(" rank[%d + %d] := %d ",sa[i],S.length(),rank[sa[i] + S.length()]);
      cout << S.substr(sa[i],S.length()) << endl;
    }
  }
public:
  SuffixArray(const string& _S){
    S = _S;
    n = S.length();
    rank = new int[2 * n + 1](); //not to be too small
    tmp = new int[2 * n + 1]();
    sa = new int[2 * n + 1]();
    construct_sa();
  }

  ~SuffixArray(){
    delete[] rank;
    delete[] tmp;
    delete[] sa;
  }

  int bsearch_first(const string& T){
    int lower = -1;
    int upper = S.length() + 1;
    while(lower + 1 < upper){
      int mid = lower + (upper - lower) / 2;
      if(S.compare(sa[mid],T.length(),T) < 0){
	lower = mid;
      }
      else{
	upper = mid;
      }
    }
    if(upper < 0 || S.compare(sa[upper],T.length(),T) != 0) return -1;
    return upper;
  }

  int bsearch_last(const string& T){
    int lower = -1;
    int upper = S.length() + 1;
    while(lower + 1 < upper){
      int mid = lower + (upper - lower) / 2;
      if(S.compare(sa[mid],T.length(),T) <= 0){
	lower = mid;
      }
      else{
	upper = mid;
      }
    }

    if(lower < 0 || S.compare(sa[lower],T.length(),T) != 0) return -1;
    return lower;
  }
  int hits(const string& T){
    int first = bsearch_first(T);
    int last = bsearch_last(T);

    if(first == -1 || last == -1) return 0;

    // cout << "query: " << T << endl;
    // disp();
    // cout << "lst: " << last << " fst: " << first << endl;
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

    map<string,int> freq;
    for(double center_pos=0;center_pos < (double)from.size();center_pos += 0.5){
      string query = "";
      for(int radius=0;radius<=from.size();radius++){
	int lhs = (int)(ceil(center_pos - (double)radius) + EPS);
	int rhs = (int)(center_pos + (double)radius);
	if(lhs < 0 || rhs >= from.size()) break;
	if(from[lhs] != from[rhs]) break;

	if(radius == 0){
	  if((double)lhs < center_pos - EPS
	     && center_pos + EPS < (double)rhs){
	    // nothing to do
	  }
	  else{
	    query = from.substr((int)(center_pos + EPS),1);
	  }
	}
	else{
	  query
	    = from.substr(lhs,1) + query + from.substr(rhs,1);
	}

	freq[query]++;
      }
    }

    for(map<string,int>::iterator it = freq.begin();
	it != freq.end();
	it++){
      int hit = sa.hits(it->first);
      res += it->second * hit;
    }
    
    printf("%d\n",res);
  }
}
