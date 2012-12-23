
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
 
struct Data{
    bool val;
    int pos;
};
 
bool expression(const string&,int);
Data clause(const string&,int);
Data lite(const string&,int);
Data variable(const string&,int);
 
bool expression(const string& str,int pos){
    Data d;
    bool res = false;
 
    if(str[pos] == '('){
        d = clause(str,pos+1);
        pos = d.pos + 1;
        res |= d.val;
    }
 
    if(pos == str.size()) return res;
 
    if(str.substr(pos,2) == "|("){
        res |= expression(str,pos+1);
    }
 
    return res;
}
 
Data clause(const string& str,int pos){
    Data res;
    Data d1 = lite(str,pos);
    res.val = d1.val;
 
    pos = d1.pos;
    while(str[pos] == '&'){
        Data d2 = lite(str,pos+1);
        pos = d2.pos;
        res.val &= d2.val;
        res.pos = d2.pos;
    }
 
    return res;
}
 
Data lite(const string& str,int pos){
 
    if(str[pos]=='~'){
        Data d = variable(str,pos+1);
        d.val = !d.val;
        return d;
    }
    else{
        Data d = variable(str,pos);
        return d;
    }
}
 
Data variable(const string& str,int pos){
    Data d;
    d.pos = pos;
    d.val = 0;
    if(isdigit(str[pos])){
        Data d;
        d.pos = pos+1;
        d.val = (str[pos]-'0' == 1) ? true : false;
        return d;
    }
}
 
vector<string> split(string delim,string str){
    vector<string> res;
    str += delim;
    for(int i=0;i<str.size();i++){
        for(int j=1;i+j<=str.size();j++){
            if(str.substr(i,j).find(delim) != string::npos){
                string tmp = str.substr(i,j-1);
                if(str.substr(i,j-1).size() >0 ) res.push_back(tmp);
                i+=j-1;
                break;
            }
        }
    }
 
    return res;
}
 
int main(){
    string str;
    while(cin >> str){
        if(str == "#") break;
 
        vector<string> clause = split("|",str);
 
        bool isok = false;
        for(int i=0;i<clause.size();i++){
            string tmp = clause[i];
 
            map<char,int> alpha;
            int idx = 0;
            for(int j=0;j<tmp.size();j++){
                if(isalpha(tmp[j]) && alpha.find(tmp[j]) == alpha.end()){
                    alpha[tmp[j]]=idx++;
                }
            }
 
            int size = alpha.size();
 
            for(int S=0;S<=(1<<size)-1;S++){
                int val[3];
                for(int j=0;j<size;j++){
                    val[j] = (S >> j) & 1;
                }
 
                for(int j=0;j<clause[i].size();j++){             
                    if(isalpha(clause[i][j])){
                        tmp[j] = val[alpha[clause[i][j]]] + '0';
                    }
                }
 
                if(expression(tmp,0)){
                    isok = true;
                    break;
                }
            }
        }
 
        printf("%s\n",isok ? "yes" : "no");
 
    }
}

