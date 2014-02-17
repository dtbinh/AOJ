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
  
using namespace std;
  
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P> PP;
  
static const double EPS = 1e-8;
  
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
int ComputeSum(int cage[10],int l,int r){
  int res = 0;
  for(int i=l;i<=r;i++){
    res += cage[i];
  }
  return res;
}
int main(){
  int max_lion_num,cage_num,man_num;
  while(~scanf("%d %d %d",&cage_num,&max_lion_num,&man_num)){
    int res = -1;
    int res_cage[10];
    int limit[10][10];
    memset(limit,-1,sizeof(limit));
 
    bool count_mistake = 0;
    for(int i=0;i<man_num;i++){
      int left_idx,right_idx,num;
      scanf("%d %d %d",&left_idx,&right_idx,&num);
      if(limit[left_idx-1][right_idx-1] != -1
	 && limit[left_idx-1][right_idx-1] != num){
	count_mistake = true;
      }
      limit[left_idx-1][right_idx-1] = num;
    }
 
    int total_max = pow((max_lion_num+1),cage_num)+EPS;
    for(int i=total_max;i>=0;i--){
      int bits = i;
      int cage[10];
      int total = 0;
      for(int j=0;j<cage_num;j++){
	int lion_num = bits % (max_lion_num+1);
	bits /= (max_lion_num+1);
	cage[j] = lion_num;
	total += lion_num;
	// printf("%d",lion_num);
	// printf("cage_idx:%d lion_num:%d\n",j,lion_num);
      }
      // printf("\n");
 
      bool isok = true;
      for(int l=0;l<cage_num;l++){
	for(int r=l;r<cage_num;r++){
	  if(limit[l][r] == -1) continue;
	  int sum = ComputeSum(cage,l,r);
	  if(sum != limit[l][r]){
	    isok = false;
	  }
	}
      }
      if(isok){
	// printf("total:%d\n",total);
	if(res <= total){
	  res = total;
	  for(int j=0;j<cage_num;j++){
	    res_cage[j] = cage[j];
	  }
	}
      }
    }
 
    if(res != -1 && !count_mistake){
      printf("%d",res_cage[0]);
      for(int i = 1;i <cage_num;i++){
	printf(" %d",res_cage[i]);
      }
      printf("\n");
    }
    else{
      printf("%d\n",-1);
    }
  }
}
