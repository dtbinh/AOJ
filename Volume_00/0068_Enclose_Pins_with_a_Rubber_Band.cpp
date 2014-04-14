#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f

#include <complex>
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
  
using namespace std;
  
typedef long long ll;
typedef complex<double> P;
  
static const double EPS = 1e-8;
  
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};

double dot(const P& a,const P& b) {
  return (a.real() * b.real() + a.imag() * b.imag());
}

double cross(P a, P b) {
  return (a.real() * b.imag() - a.imag() * b.real());
}
bool cmp_x(const P& p, const P& q){
  if(p.real() != q.real()) return p.real() < q.real();
  return p.imag() < q.imag();
}

vector<P> convex_hull(P* ps, int n){
  sort(ps, ps+n, cmp_x);
  int k = 0;
  vector<P> qs(n * 2);
  for(int i=0; i < n; i++){
    while(k > 1 && cross(qs[k - 1] - qs[k - 2],ps[i] - qs[k - 1]) <= 0) k--;
    qs[k++] = ps[i];
  }
  for(int i=n - 2,t = k; i >= 0; i--){
    while(k > t && cross(qs[k - 1] - qs[k - 2],ps[i] - qs[k - 1]) <= 0) k--;
    qs[k++] = ps[i];
  }
  qs.resize(k-1);
  return qs;
}

double dist(const P& p,const P& q){
  return dot(p-q,p-q);
}

int main(){
  int N;
  while(~scanf("%d",&N)){
    if(N == 0) break;

    P ps[10001];
    for(int i=0;i<N;i++){
      double x,y;
      scanf("%lf,%lf",&x,&y);
      ps[i] = P(x,y);
    }
    vector<P> qs = convex_hull(ps,N);
    cout << N - qs.size() << endl;
  }
}
