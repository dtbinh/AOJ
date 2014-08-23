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

class Compare{
private:
  const int len;
  const int n;
  const int* rank;
public:
  Compare(int _l,int _n,int* _r) :
    len(_l),n(_n),rank(_r) {}
  bool operator() (int i,int j) const{
    return compare_sa(i,j,len);
  }

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
};

class SuffixArray {
protected:
  string S;
  int* rank;
  int* sa;
  int* lcp;
  int n;
private:
  void construct_sa(){
    for(int i= 0; i <= n;i++){
      sa[i] = i;
      rank[i] = (i < n ? S[i] : -1);
    }

    int* tmp = new int[2 * n + 1]();
    Compare init(1,n,rank);
    sort(sa,sa+n+1,init);

    for(int len = 1; len <= n; len *= 2){
      Compare comp(len,n,rank);
      sort(sa,sa+n+1,comp);
      
      tmp[sa[0]] = 0;
      for(int i=1;i<= n;i++){
	tmp[sa[i]] = tmp[sa[i-1]] + (comp.compare_sa(sa[i-1],sa[i],len) ? 1 : 0);
      }
      for(int i=0;i<=n;i++){
	rank[i] = tmp[i];
      }
    }
    delete[] tmp;
  }

  void construct_lcp(){
    int h = 0;
    lcp[0] = 0;

    for(int i=0;i < n;i++){
      int j= sa[rank[i] - 1];
      if(h > 0) h--;
      for(; j + h < n && i + h < n; h++){
	if(S[j + h] == '$' || S[i + h] == '$') break;
	if(S[j + h] != S[i + h]) break;
      }
      lcp[rank[i] - 1] = h;
    }
  }
  
public:
  SuffixArray(const string& _S){
    S = _S;
    n = S.length();
    rank = new int[n + 12](); //not to be too small
    sa = new int[n + 12]();
    lcp = new int[n + 12]();
    construct_sa();
    construct_lcp();
  }

  ~SuffixArray(){
    delete[] rank;
    delete[] sa;
    delete[] lcp;
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

    disp();
    return last - first + 1;
  }

  int get_lcp(int i) const{
    assert(i < n);
    return lcp[i];
  }

  int get_sa(int i) const{
    assert(i < n);
    return sa[i];
  }

  int get_rank(int i) const{
    assert(i < n);
    return rank[i];
  }

  int size() const{
    return n;
  }

  //for debug
  void disp() const{
    for(int i=0;i<=S.length();i++){
      printf("rank[%02d] := %02d",sa[i], rank[sa[i]]);
      printf(" lcp[%02d] := %02d ",i, lcp[i]);
      cout << S.substr(sa[i],S.length()) << endl;
    }
  }

};

class SegmentTree {
private:
  int* dat;
  int n;
public:
  SegmentTree(int _size){
    n = 1;
    while(n < _size) n *= 2;
    dat = new int[n * 2 - 1];
    fill(dat,dat + n * 2 - 1,INF);
  }

  ~SegmentTree(){
    delete[] dat;
  }

  void update(int idx,int val){
    idx += n - 1; //offset: n - 1 
    dat[idx] = val;
    while(idx > 0){
      idx = (idx - 1) / 2;
      dat[idx] = min(dat[idx * 2 + 1],dat[idx * 2 + 2]);
    }
  }

  int query(int a,int b,int idx = 0,
	    int l = 0,int r = INF){
    if(r == INF) r = n;

    if(r <= a || b <= l) return INF;
    
    if(a <= l && r <= b) return dat[idx];
    
    else{
      int vl = query(a, b, idx * 2 + 1, l, (l + r) / 2);
      int vr = query(a, b, idx * 2 + 2, (l + r) / 2, r);
      return min(vl,vr);
    }
  }
};

int main(){
  string input;
  while(getline(cin,input)){
    
    string str;
    for(int i=0;i<input.size();i++){
      if(isalpha(input[i])){
	str.push_back(toupper(input[i]));
      }
    }

    string r_str = str;
    reverse(r_str.begin(),r_str.end());
    SuffixArray sa(str + "$" + r_str);
    SegmentTree segtree(sa.size());

    for(int i=0; i+1 < sa.size(); i++){
      segtree.update(i,sa.get_lcp(i));
    }

    //odd
    for(int center=0;center<str.size();center++){
      int r_center = sa.size() - center - 1;
      int lcp = segtree.query(
	min(
	  sa.get_rank(center),
	  sa.get_rank(r_center)
	),
	max(
	  sa.get_rank(center),
	  sa.get_rank(r_center)
	)
      );

      if(lcp == INF) continue;
      if(lcp <= 1) continue;

      int len = (lcp % 2 == 0 ? 2 * lcp - 1 : lcp);
      cout << str.substr(center-lcp + 1,len) << endl;
    }

    //even
    for(int center_rhs=1;center_rhs<str.size();center_rhs++){
      int center_lhs = center_rhs - 1;
      int r_center_lhs = sa.size() - center_lhs - 1;
      int lcp = segtree.query(
	min(
	  sa.get_rank(center_rhs),
	  sa.get_rank(r_center_lhs)
	),
	max(
	  sa.get_rank(center_rhs),
	  sa.get_rank(r_center_lhs)
	)
      );

      if(lcp == INF) continue;
      if(lcp <= 1) continue;

      cout << str.substr(center_lhs - lcp + 1,lcp * 2) << endl;
    }
  }
}
