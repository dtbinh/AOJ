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

class Editor{
private:
  string text;
  int cursor;
public:
  Editor(const string& _text) : text(_text),cursor(0) {}
  void forward_char(){
    if(text.size() > cursor) cursor++;
  }
  void forward_word(){
    int tmp = text.size();
    for(int pos=cursor;pos+1<text.size();pos++){
      if(text[pos] != ' '
	 && text[pos + 1] == ' '){
	tmp = pos + 1;
	break;
      }
    }
    cursor = tmp;
  }
  void backward_char(){
    if(0 < cursor) cursor--;    
  }
  void backward_word(){
    int tmp = 0;

    for(int pos=cursor-1;pos-1>=0;pos--){
      if(text[pos] != ' '
	 && text[pos - 1] == ' '){
	tmp = pos;
	break;
      }
    }
    cursor = tmp;
  }
  void insert(const string& str){
    string middle = str;
    string front = "";
    string rear = "";
    if(cursor > 0) front = text.substr(0,cursor);
    if(cursor < text.size()) rear = text.substr(cursor,text.size()-cursor);

    cursor = front.size() + middle.size();
    text = front + middle + rear;
  }
  void delete_char(){
    string front = "";
    string rear = "";
    if(cursor > 0) front = text.substr(0,cursor);
    if(cursor+1 < text.size()) rear = text.substr(cursor+1,text.size()-(cursor+1));
    text = front + rear;
  }
  void delete_word(){
    int delete_first = cursor;
    int delete_last = text.size();

    if(text[cursor] == ' '){
      bool update = false;
      for(int pos=cursor;pos<text.size();pos++){
	if(text[pos] != ' '){
	  update = true;
	  break;
	}
      }
      if(!update) return;

      for(int pos=cursor;pos<text.size();pos++){
	if(text[pos] != ' '
	   && text[pos+1] == ' '){
	  delete_last = pos;
	  break;
	}
      }
    }
    else{
      for(int pos=cursor;pos<text.size();pos++){
	if(text[pos] == ' '){
	  delete_last = pos - 1;
	  break;
	}
      }
    }

    string front = "";
    string rear = "";
    if(delete_first > 0){
      front = text.substr(0,delete_first);
    }
    if(delete_last < text.size()){
      rear = text.substr(delete_last+1,text.size()-delete_last);
    }
    text = front + rear;
  }
  void print_text(){
    string front = "";
    string rear = "";
    if(cursor > 0) front = text.substr(0,cursor);
    if(cursor < text.size()) rear = text.substr(cursor,text.size()-cursor);
    cout << front << "^" << rear << endl;
  }
};

int main(){
  string total_test_cases_str;

  while(getline(cin,total_test_cases_str)){
    stringstream ttc_ss;
    ttc_ss << total_test_cases_str;
    int total_test_cases;
    ttc_ss >> total_test_cases;

    for(int test_idx=0;test_idx<total_test_cases;test_idx++){
      string text;
      getline(cin,text);
      
      Editor editor(text);

      string total_commands_str;

      getline(cin,total_commands_str);
      stringstream total_commands_ss;
      total_commands_ss << total_commands_str;
      
      int total_commands;
      total_commands_ss >> total_commands;

      for(int command_idx=0;command_idx < total_commands; command_idx++){
	string fr_str;

	getline(cin,fr_str);

	string front="";
	string rear="";
	int str_pos = 0;
	for(int i=0;i<fr_str.size();i++){
	  if(fr_str[i] == ' '){
	    str_pos = i+1;
	    break;
	  }
	  front += fr_str[i];
	}
	for(int i=str_pos;i<fr_str.size();i++){
	  rear += fr_str[i];

	  if(i==str_pos && fr_str[i] == '"') {
	    //nothing todo
	  }
	  else if(fr_str[i] == '"'){
	    break;
	  }
	}

	if(front == "forward"){
	  if(rear == "char"){
	    editor.forward_char();
	  }
	  else if(rear == "word"){
	    editor.forward_word();
	  }
	}
	else if(front == "backward"){
	  if(rear == "char"){
	    editor.backward_char();
	  }
	  else if(rear == "word"){
	    editor.backward_word();
	  }
	}
	else if(front == "insert"){
	  editor.insert(rear.substr(1,rear.size()-2));
	}
	else if(front == "delete"){
	  if(rear == "char"){
	    editor.delete_char();
	  }
	  else if(rear == "word"){
	    editor.delete_word();
	  }
	}
      }
      editor.print_text();
    }
  }
}
