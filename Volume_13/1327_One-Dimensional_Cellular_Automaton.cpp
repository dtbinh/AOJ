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

template <class T> class Matrix1D;
template <class T> class Matrix2D;

template <class T> class Matrix1D{
public:
  vector<T> matrix1d;
  int modulo;

  Matrix1D(int size,int _m) : modulo(_m){
    for(int i=0;i<size;i++){
      matrix1d.push_back(i);
    }
  }
  
  Matrix1D(int _m) : modulo(_m){
  }

  Matrix1D(){}
  
  Matrix1D(const vector<T>& mat,T _m) : modulo(_m){
    matrix1d = mat;
  }
  
  T& operator[](int idx){
    return matrix1d[idx];
  }

  const T& operator[](int idx) const{
    return matrix1d[idx];
  }
  
  const int size() const{
    return matrix1d.size();
  }

  void print_mat(){
    for(int x=0;x<matrix1d.size();x++){
      printf("%s%d",x==0 ? "" : " ",matrix1d[x]);
    }
    printf("\n");
  }
};

template <class T> class Matrix2D{
public:
  vector< vector<T> > matrix2d;
  int modulo;
  Matrix2D(int size_row,int size_col,int _m) : modulo(_m){
    for(int y=0;y<size_row;y++){
      vector<T> tmp;
      for(int x=0;x<size_col;x++){
	tmp.push_back(0);
      }
      matrix2d.push_back(tmp);
    }
  }

  Matrix2D(int _m) : modulo(_m){
  }

  Matrix2D(){}

  vector<T>& operator[](int idx){
    return matrix2d[idx];
  }
  
  const vector<T>& operator[](int idx) const{
    return matrix2d[idx];
  }
  
  Matrix1D<T> operator *(const Matrix1D<T>& matrix1d){
    Matrix1D<int> res(matrix1d.size(),modulo);
    for(int y=0;y<matrix2d.size();y++){

      int sum = 0;
      for(int x=0;x<matrix2d[0].size();x++){
	int mat1d_y = x;
	sum += matrix2d[y][x] * matrix1d[mat1d_y] % modulo;
      }
      res[y] = sum % modulo;
    }
    return res;
  }
  
  Matrix2D<T> operator *(const Matrix2D<T>& _matrix2d){
    Matrix2D<int> res(_matrix2d.size(),_matrix2d[0].size(),modulo);
    for(int src_row_idx=0;src_row_idx<matrix2d.size();src_row_idx++){
      for(int dst_col_idx=0;dst_col_idx<_matrix2d[0].size();dst_col_idx++){
	for(int dst_row_idx=0;dst_row_idx<_matrix2d.size();dst_row_idx++){
	  int src_col_idx = dst_row_idx;
	  res[src_row_idx][dst_col_idx] 
	    += matrix2d[src_row_idx][src_col_idx] * _matrix2d[dst_row_idx][dst_col_idx] % modulo;
	  res[src_row_idx][dst_col_idx] %= modulo;
	}
      }
    }
    return res;
  }

  const int size() const{
    return matrix2d.size();
  }

  void print_mat(){
    for(int y=0;y<matrix2d.size();y++){
      for(int x=0;x<matrix2d[0].size();x++){
	int mat1d_y = x;
	printf("%d ",matrix2d[y][x]);
      }
      printf("\n");
    }
  }
};

int main(){
  int N,M,A,B,C,T;
  while(~scanf("%d %d %d %d %d %d",
	       &N,&M,&A,&B,&C,&T)){
    if(N==0) break;

    vector<int> S0;
    for(int i=0;i<N;i++){
      int num;
      scanf("%d",&num);
      S0.push_back(num);
    }
    
    Matrix1D<int> mat1d(S0,M);
    Matrix2D<int> mat2d(N,N,M);

    int abc[3] = {A,B,C};
    int x = -1;
    for(int y=0;y<N;y++){
      for(int abc_idx=0;abc_idx<3;abc_idx++){
    	if(x+abc_idx < 0) continue;
    	if(x+abc_idx >= N) continue;
    	mat2d[y][x+abc_idx] = abc[abc_idx];
      }
      x++;
    }

    Matrix2D<int> base = mat2d;
    for(int i=0;i<T-1;i++){
      mat2d = mat2d * base;
    }

    Matrix1D<int> res;
    if(T <= 0){
      res = mat1d;
    }
    else{
      res = mat2d*mat1d;
    }

    res.print_mat();
  }
}
