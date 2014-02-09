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
 
const static int tx[] = {0,1,1,1,0,-1,-1,-1};
const static int ty[] = {-1,-1,0,1,1,1,0,-1};

const static double EPS = 1e-12;

template <class T> class Matrix{
private:
  T** A;
  T* B;
  int N;
public:
  Matrix(int _N){
    N = _N;
    A = new T*[N];
    B = new T[N];
    for(int y=0;y<N;y++){
      A[y] = new T[N];
      for(int x=0;x<N;x++){
	A[y][x] = 0;
      }
    }
    for(int y=0;y<N;y++){
      B[y] = 0;
    }
  }

  Matrix(T** _A,T* _B,int _N){
    N = _N;
    A = new T*[N];
    B = new T[N];
    for(int dy=N-1,sy=0;dy>=0;dy--,sy++){
      A[dy] = new T[N];
      for(int x=0;x<N;x++){
	A[dy][x] = _A[sy][x];
      }
    }
    for(int dy=N-1,sy=0;dy>=0;dy--,sy++){
      B[dy] = _B[sy];
    }
  }

  void gauss_jordan(){
    for(int pivot_y=0;pivot_y<N;pivot_y++){
      int pivot_x=pivot_y;
      double pivot = A[pivot_y][pivot_x];
      if(abs(pivot) < EPS) continue;

      for(int x=0;x<N;x++){
	A[pivot_y][x] /= pivot;
      }
      B[pivot_y] /= pivot;
      for(int y=0;y<N;y++){
	if(y == pivot_y) continue;
	if(abs(A[y][pivot_x]) < EPS) continue;

	double scalar = (A[y][pivot_x] / A[pivot_y][pivot_x]);
	B[y] -= B[pivot_y] * scalar;

	for(int x=0;x<N;x++){
	  A[y][x] -=  A[pivot_y][x] * scalar;
	}
      }
    }    
  }

  const T atB(int idx) const{
    return B[idx];
  }

  void dispB(const string str){
    
    printf("B(%s)=[",str.c_str());
    for(int i=0;i<N;i++){
      printf("%lf ",B[i]);
    }
    printf("]\n");
  }
  void dispA(const string str){
    printf("A(%s)=[",str.c_str());
    for(int y=0;y<N;y++){
      printf("\n");
      for(int x=0;x<N;x++){
	printf("%lf ",A[y][x]);
      }
    }
    printf("]\n");
  }
};

int fast_pow(int x,int power){
  int res = 1;

  while(power){
    if(power & 1) res *= x;
    x *= x;
    power >>= 1;
  }
  return res;
}

void disp_mat2d(double** A,int N){
    printf("A=[");
    for(int y=0;y<N;y++){
      printf("\n");
      for(int x=0;x<N;x++){
	printf("%lf ",A[y][x]);
      }
    }
    printf("\n]\n");
}

void disp_mat1d(double* B,int N){
    printf("B=[\n");
    for(int y=0;y<N;y++){
      printf("%lf\n",B[y]);
    }
    printf("]\n");
}

int main(){
  int dimension;
  while(~scanf("%d",&dimension)){
    if(dimension == 0) break;
    double* B = new double[dimension+3];

    for(int x=0;x<=dimension+2;x++){
      scanf("%lf",B + x);
    }

    double** A = new double*[dimension+1];
    double* B_dash = new double[dimension+1];

    map<string,vector<unsigned int> > history;
    for(unsigned int S=0;S<(1<<(dimension+3));S++){
      if(__builtin_popcount(S) != (dimension+1)) continue;
      
      int y=0;
      for(int use_y=0;use_y<=dimension+2;use_y++){
	if(!(S & (1UL<<use_y))) continue;
	B_dash[y] = B[use_y];
	A[y] = new double[dimension+1];

	for(int x=0,power=dimension;x<=dimension;x++,power--){
	  A[y][x] = (double)fast_pow(use_y,power);
	}
	y++;
      }

      Matrix<double> mat(A,B_dash,dimension+1);
      mat.gauss_jordan();

      string key = "";
      for(int idx=dimension;idx>=0;idx--){
	stringstream ss;
	char buf[128];
	sprintf(buf,"%.4lf",mat.atB(idx));
	ss << buf;
	key += "|" + ss.str();
      }
      key += "|";

      history[key].push_back(S);
    }

    int res = 0;
    for(map<string,vector<unsigned int> >::iterator it = history.begin();
	it != history.end();
	it++){
      unsigned int S = 0;
      for(int i=0;i< it->second.size();i++){
	S |= it->second[i];
      }

      if(__builtin_popcount(S) == (dimension+2)){
	for(int i=0;i<=dimension+2;i++){
	  if(!(S & (1<<i))){
	    res = i;
	    break;
	  }
	}
      }
    }
    printf("%d\n",res);
  }
}
