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
 
int main()
{
  int a,b,c,d,e,f;
  double A[2][2];
  double B[2];
  double inv_A[2][2];
  while(~scanf("%d %d %d %d %d %d",&a,&b,&c,&d,&e,&f)){
    int det = a*e-b*d;
    A[0][0]=a; A[0][1] = b;
    A[1][0]=d; A[1][1] = e;
    B[0] = c;
    B[1] = f; 
 
    inv_A[0][0]=A[1][1]; inv_A[0][1]=-A[0][1];
    inv_A[1][0]=-A[1][0]; inv_A[1][1]=A[0][0];
 
    double res[2];
    res[0]=0;
    res[1]=0;
 
    for(int j=0;j<2;j++){
      for(int k=0;k<2;k++){
	res[j]+=1.0/(double)det *inv_A[j][k]*B[k];
      }
    }
 
    printf("%.3f %.3f\n",res[0],res[1]);
  }
}
