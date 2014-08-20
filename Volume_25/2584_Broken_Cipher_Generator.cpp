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
typedef pair <int,char> PC;
typedef pair <int,string> PS;
  
static const double EPS = 1e-8;
  
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};

PS Cipher(int pos,const string& str);
PS String(int pos,const string& str);
PC Letter(int pos,const string& str);

PS Cipher(int pos,const string& str){
  string res="";
  while(pos < str.size() && str[pos] != ']'){
    PS p = String(pos,str);
    pos = p.first;
    res += p.second;
  }
  return PS(pos,res);
}

PC Letter(int pos,const string& str){
  if(str[pos] == '+'){
    PC p1 = Letter(pos+1,str);
    p1.second = ((p1.second - 'A') + 1) % ('Z' - 'A' + 1) + 'A';
    return p1;
  }
  else if(str[pos] == '-'){
    PC p2 = Letter(pos+1,str);
    p2.second = ((p2.second - 'A') + ('Z' - 'A')) % ('Z' - 'A' + 1) + 'A';
    return p2;
  }
  else if(isalpha(str[pos])){
    return PC(pos+1,str[pos]);
  }
}

PS String(int pos,const string& str){
  if(str[pos] == '['){
    PS p1 = Cipher(pos+1,str);
    reverse(p1.second.begin(),p1.second.end());
    p1.first++;
    return p1;
  }
  else{
    string tmp = "";
    PC p2 = Letter(pos,str);
    tmp += p2.second;
    return PS(p2.first,tmp);
  }
}

string dfs(string str,
	   const vector<int>& question_pos,int idx){
  if(idx == question_pos.size()){
    return Cipher(0,str).second;
  }
  string res = string(500,'Z');

  for(char i = 'A'; i <= 'Z'; i++){
    str[question_pos[idx]] = i;
    res = min(res,dfs(str,question_pos,idx+1));
  }
  return res;
}

int main(){
  string str;
  while(cin >> str){
    if(str == ".") break;

    vector<int> question_pos;
    for(int i=0;i<str.size();i++){
      if(str[i] == '?'){
	question_pos.push_back(i);
      }
    }
    cout << dfs(str,question_pos,0) << endl;
  }
}
