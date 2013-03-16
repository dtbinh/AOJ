
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
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
 
static const double EPS = 1e-8;
 
int main(){
    string str;
    char conv;
    while(cin>>str){
        cin >> conv;
 
        if(conv == 'X') break;
        //under score
        if(count(str.begin(),str.end(),'_')){
            if(conv == 'L'){
                //str[0] = 'A' + (str[0]-'a');
                string res="";
                for(int i=0;i+1<str.size();i++){
                    if(str[i]=='_' && ('a' <= str[i+1] && str[i+1] <= 'z')){
                        str[i+1]='A'+(str[i+1]-'a');
                        i++;
                    }
                }
 
                string::iterator it = remove(str.begin(),str.end(),'_');
                str.erase(it,str.end());
            }
            else if(conv == 'U'){
                str[0] = 'A' + (str[0]-'a');
                for(int i=0;i+1<str.size();i++){
                    if(str[i]=='_' && ('a' <= str[i+1] && str[i+1] <= 'z')){
                        str[i+1]='A'+(str[i+1]-'a');
                        i++;
                    }
                }
 
                string::iterator it = remove(str.begin(),str.end(),'_');
                str.erase(it,str.end());
            }
        }
        //Upper CamelCase
        else if('A' <= str[0] && str[0] <= 'Z'){
            if(conv == 'L'){
                str[0] = 'a' + (str[0]-'A');
            }
            else if(conv == 'D'){
                string res="";
                str[0] = 'a' + (str[0]-'A');
 
                res.push_back(str[0]);
                for(int i=1;i<str.size();i++){
                    if('A' <= str[i] && str[i] <= 'Z'){
                        res.push_back('_');
                        res.push_back('a' + (str[i]-'A'));
                    }
                    else{
                        res.push_back(str[i]);
                    }
                }
 
                str = res;
            }
 
        }
        //Lower CamelCase
        else{
            if(conv == 'U'){
                str[0] = 'A' + (str[0]-'a');
            }
            else if(conv == 'D'){
                string res="";
                str[0] = 'a' + (str[0]-'a');
                res.push_back(str[0]);
                for(int i=1;i<str.size();i++){
                    if('A' <= str[i] && str[i] <= 'Z'){
                        res.push_back('_');
                        res.push_back('a' + str[i]-'A');
                    }
                    else{
                        res.push_back(str[i]);
                    }
                }
                str = res;
            }
        }
 
        cout << str << endl;
    }
}

