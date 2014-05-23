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
      sa_sort(0,n,len);
      
      tmp[sa[0]] = 0;
      for(int i=1;i<= n;i++){
	tmp[sa[i]] = tmp[sa[i-1]] + (compare_sa(sa[i-1],sa[i],len) ? 1 : 0);
      }
      for(int i=0;i<=n;i++){
	rank[i] = tmp[i];
      }
    }
  }

  void sa_sort(int lhs,int rhs,int len){
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
    
    sa_sort(lhs,j,len);
    sa_sort(i,rhs,len);
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
    rank = new int[n+12](); //not to be too small
    tmp = new int[n+12]();
    sa = new int[n+12]();
    construct_sa();
  }

  ~SuffixArray(){
    delete[] rank;
    delete[] tmp;
    delete[] sa;
  }

  int bsearch_first(const string& T){
    int lower = -1;
    int upper = S.length();
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
    int upper = S.length();
    while(lower + 1 < upper){
      int mid = lower + (upper - lower) / 2;
      if(S.compare(sa[mid],T.length(),T) <= 0){
	lower = mid;
      }
      else{
	upper = mid;
      }
    }

    if(lower > S.length() || S.compare(sa[lower],T.length(),T) != 0) return -1;
    return lower;
  }
  int hits(const string& T){
    int first = bsearch_first(T);
    int last = bsearch_last(T);

    if(first == -1 || last == -1) return 0;
    
    return last - first + 1;
  }
};


int a[] = {5,5,5,104,5,5,5,1};
bool comp(int i,int j){
  return a[i] < a[j];
}

void quiclens(int a[10],int lhs,int rhs){
  if(lhs >= rhs) return;

  int pivot = lhs + (rhs - lhs) / 2;
  for(int i=0;i<7;i++){
    cout << a[i] << " ";
  }
  cout << "\n";

  cout << "piv: " << pivot << endl;
  cout << "a[piv]: " << a[pivot] << endl;
  int i = lhs;
  int j = rhs;
  while(1){
    while(comp(i,pivot)) i++;
    while(comp(pivot,j)) j--;

    if(i >= j) break;
    cout << "a[i]: " << a[i] << endl;
    cout << "a[j]: " << a[j] << endl;
    swap(a[i],a[j]);
    i++;
    j--;
  }

  for(int i=0;i<7;i++){
    cout << a[i] << " ";
  }
  cout << "\n";

  quiclens(a,lhs,i-1);
  quiclens(a,j+1,rhs);
}
  
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

  // quiclens(a,0,6);
  // cout << endl;
}
