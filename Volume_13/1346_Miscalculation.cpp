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
#include <complex>
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P > PP;

typedef complex<double> Point;
const static double EPS = 1e-12;

int main(){
  string expr;
  int bob_ans;
  while(cin >> expr >> bob_ans){
    vector<char> ope;
    vector<int> ope_pos;
    vector<int> nums;
    for(int i = 0; i< expr.size();i++){
      if(isdigit(expr[i])){
	int sum = 0;
	while(i < expr.size() && isdigit(expr[i])){
	  sum *= 10;
	  sum += expr[i] - '0';
	  i++;
	}
	nums.push_back(sum);
	i--;
      }
      else if(expr[i] == '+'){
	ope.push_back(expr[i]);
	ope_pos.push_back(i);
      }
      else if(expr[i] == '*'){
	ope.push_back(expr[i]);
	ope_pos.push_back(i);
      }
    }

    vector<int> multi_first_num(nums);
    vector<char> order;
    order.push_back('*');
    order.push_back('+');

    bool used[1001];
    memset(used,false,sizeof(used));

    for(int order_i = 0; order_i < order.size(); order_i++){
      for(int i = 0; i < ope.size();i++){
	if(order[order_i] == ope[i]){
	  int res = 0;
	  if(ope[i] == '*') res = multi_first_num[i] * multi_first_num[i+1];
	  if(ope[i] == '+') res = multi_first_num[i] + multi_first_num[i+1];

	  for(int j = i+1; j < multi_first_num.size(); j++){
	    multi_first_num[j] = res;
	    if(j == multi_first_num.size() || !used[j]) break;
	  }
	  for(int j = i; j >= 0; j--){
	    multi_first_num[j] = res;
	    if(j == 0 || !used[j - 1]) break;
	  }

	  used[i] = true;
	}
      }
    }


    vector<int> left2right_num(nums);
    memset(used,false,sizeof(used));

    for(int i = 0; i < ope.size();i++){
      int res = 0;
      if(ope[i] == '*') res = left2right_num[i] * left2right_num[i+1];
      if(ope[i] == '+') res = left2right_num[i] + left2right_num[i+1];
      
      for(int j = i+1; j < left2right_num.size(); j++){
	left2right_num[j] = res;
	if(j == left2right_num.size() || !used[j]) break;
      }
      for(int j = i; j >= 0; j--){
	left2right_num[j] = res;
	if(j == 0 || !used[j - 1]) break;
      }
      used[i] = true;
    }

    if(bob_ans == multi_first_num[0]
       && bob_ans != left2right_num[0]){
      printf("M\n");
    }
    else if(bob_ans != multi_first_num[0]
	    && bob_ans == left2right_num[0]){
      printf("L\n");
    }
    else if(bob_ans == multi_first_num[0]
	    && bob_ans == left2right_num[0]){
      printf("U\n");
    }
    else{
      printf("I\n");
    }
  }    
}
