
#define _USE_MATH_DEFINES
#define INF 100000000
 
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
typedef pair <int,P> PP;
 
static const double EPS = 1e-8;
 
const int tx[] = {0,1,0,-1};
const int ty[] = {1,0,-1,0};
 
string num2str(int num){
    string res="";
        int multi = num / 1000;
         
        if(multi > 1) res.push_back(multi+'0');
        if(multi >= 1) res.push_back('m');
        num %= 1000;
 
        multi = num / 100;
        if(multi > 1) res.push_back(multi+'0');
        if(multi >= 1) res.push_back('c');
        num %= 100;
 
        multi = num / 10;
        if(multi > 1) res.push_back(multi+'0');
        if(multi >= 1) res.push_back('x');
        num %= 10;
 
        multi = num / 1;
        if(multi > 1) res.push_back(multi+'0');
        if(multi >= 1) res.push_back('i');
        num %= 1;
 
    return res;
}
 
int main(){
    string str1,str2;
    int n;
    cin >> n;
    for(int t=0;t<n;t++){
        cin >> str1;
        cin >> str2;
        //mcxi,1000,100,10,1
        int sum = 0;
        int multi = 1;
        for(int i=0;i<str1.size();i++){
            if(isdigit(str1[i])){
                multi = str1[i] - '0';
            }
            else{
                if(str1[i] == 'm') sum += multi * 1000;
                if(str1[i] == 'c') sum += multi * 100;
                if(str1[i] == 'x') sum += multi * 10;
                if(str1[i] == 'i') sum += multi * 1;
                multi = 1;
            }
        }
 
        multi = 1;
        for(int i=0;i<str2.size();i++){
            if(isdigit(str2[i])){
                multi = str2[i] - '0';
            }
            else{
                if(str2[i] == 'm') sum += multi * 1000;
                if(str2[i] == 'c') sum += multi * 100;
                if(str2[i] == 'x') sum += multi * 10;
                if(str2[i] == 'i') sum += multi * 1;
                multi = 1;
            }
        }
 
        printf("%s\n",num2str(sum).c_str());
    }
}

