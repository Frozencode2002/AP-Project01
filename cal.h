#include <bits/stdc++.h>
using namespace std;
#define TOKENS_SIZE 100
class TOKENS{
public:
	TOKENS(){}
	void read(string io_in){
		read_data = io_in;
	}
	bool io_check(){
		int cnt = 0;
		int len = read_data.length();
		char op[4] = {'+', '-', '*', '/'};
		auto find = [=](char s, char *op){
			for(int i = 0; i < 4; i++) if(op[i] == s) return true;
			return false;
		};
		for(int i = 0; i < len; i++){
			if(read_data[i] == '(') cnt++;
			if(read_data[i] == ')') cnt--;
			if(i > 0 && find(read_data[i], op) && find(read_data[i - 1], op)) return false;
			if(cnt < 0) return false;
		}
		if(cnt != 0) return false;
		return true;
	}
private:
	string read_data;
	int op_stack_len, op_stack[TOKENS_SIZE];
	int num_stack_len, num_stack[TOKENS_SIZE];
};