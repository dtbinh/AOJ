
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
 
//J,C,E,A,P,M
 
string Mr(string op,string str){
    if(op=="A"){
        reverse(str.begin(),str.end());
        return str;
    }
 
    else if(op=="C"){
        rotate(str.begin(),str.begin()+1,str.end());
        return str;
    }
 
    else if(op=="E"){
        if(str.size() % 2 == 0){
            string front = str.substr(0,str.size()/2);
            string rear = str.substr(str.size()/2,str.size()/2);
            return rear+front;
        }
        else{
            string front = str.substr(0,str.size()/2);
            string mid = str.substr(str.size()/2,1);
            string rear = str.substr(str.size()/2+1,str.size()/2);
            return rear + mid + front;
        }
    }
 
    else if(op=="J"){
        rotate(str.begin(),str.end()-1,str.end());
        return str;
    }
 
    //increament
    else if(op=="M"){
        for(int i=0;i<str.size();i++){
            if(isdigit(str[i])){
                str[i] = (str[i] < '9' ? str[i] + 1 : '0');
            }
        }
        return str;
    }
 
    //decrement
    else if(op=="P"){
        for(int i=0;i<str.size();i++){
            if(isdigit(str[i])){
                str[i] = (str[i] > '0' ? str[i] - 1 : '9');
            }
        }
        return str;
    }
 
}
 
int main(){
    int n;
    while(~scanf("%d",&n)){
        if(n==0) break;
        for(int i=0;i<n;i++){
            string msger;
            string msg;
            cin >> msger;
            cin >> msg;
 
            for(int j=msger.size()-1;j>=0;j--){
                msg = Mr(msger.substr(j,1),msg);
            }
            cout << msg << "\n";
        }
    }
}

