#include <iostream>
#include <cstdio>
 
using namespace std;
 
int sum(int n){
  int res = 1;
  while(n / 10 != 0){
    res++;
    n/=10;
  }
 
  return res;
}
 
int main()
{
  int a,b;
  while(~scanf("%d %d",&a,&b)){
    printf("%d\n",sum(a+b));
  }
 
  return 0;
}
