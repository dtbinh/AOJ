#include <iostream>
#include <cstdio>
#include <algorithm>
 
using namespace std;
 
int tall[5000];
int idx=0;
 
int main(){
  while(~scanf("%d",tall+idx)){
    idx++;
  }
 
  sort(tall,tall+idx,greater<int>());
 
  for(int i=0;i<3;i++){
    printf("%d\n",tall[i]);
  }
}
