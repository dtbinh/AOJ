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
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

char gID[100001];
int gSum_except_asterisk;
bool gAsterisk_line[10];
int gCandidates[10];
int gCandidate_num;

int dfs(const string& x,int depth);
int ComputeNum(int num,int idx);
int ComputeExceptAsterTotal();
void JudgeAsteriskLine();
int fast_pow(int x,int power);
int fact(int x);
bool isValid(const string& line);

int dfs(const string& x,int depth){
  if(depth == 0){
    if(isValid(x)){
      return 1;
    }
    return 0;
  }

  int res = 0;
  for(int i=0;i<gCandidate_num;i++){
    string tmp = x;
    tmp.push_back(gCandidates[i]+'0');
    res += dfs(tmp,depth-1);
  }

  return res;
}

int ComputeNum(int num,int idx){
  if(idx % 2) return num;
  return num*2 >= 10 ? 1 + num*2%10 : num*2;
}

int ComputeExceptAsterTotal(){
  int res = 0;
  for(int i=0;i<strlen(gID);i++){
    if(gID[i] == '*') continue;
    int idx = strlen(gID) - i;
    res += ComputeNum(gID[i]-'0',idx);
  }
  return res;
}

void JudgeAsteriskLine(){
  int res = 0;
  int asterisk_idx = 0;
  for(int i=0;i<strlen(gID);i++){
    int idx = strlen(gID) - i;
    if(gID[i] == '*') gAsterisk_line[asterisk_idx++] = (idx % 2 == 0) ? true : false;
  }
}

int fast_pow(int x,int power){
  int res = 1;

  //2 ^ 4(0100)
  //2 ^ 2 * 2 ^ 2
  while(power){
    if(power & 1) res *= x;
    x *= x;
    power >>= 1;
  }
  return res;
}

int fact(int x){
  return x-1 <= 0 ? x*1 : x*fact(x-1);
}

bool isValid(const string& line){
  int sum = 0;
  for(int i=0;i<line.size();i++){
    //true:even false:odd
    if(gAsterisk_line[i]) sum += ComputeNum(line[i]-'0',2);
    else sum += ComputeNum(line[i]-'0',3);
  }
  if((gSum_except_asterisk + sum) % 10 == 0){
    return true;
  }

  return false;
}

int main(){
  int n;

  while(~scanf("%d",&n)){
    scanf("%s",gID);
    scanf("%d",&gCandidate_num);
    for(int i=0;i<gCandidate_num;i++){
      scanf("%d",gCandidates+i);
    }
    gSum_except_asterisk = ComputeExceptAsterTotal();
    int asterisk_num = count(gID,gID+n,'*');
    JudgeAsteriskLine();
    int res = 0;
    res = dfs("",asterisk_num);
    printf("%d\n",res);
  }
}
