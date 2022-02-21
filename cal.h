#include <bits/stdc++.h>
using namespace std;
#define TOKENS_SIZE 100
#define eps 1e-9
class TOKENS{
public:
	TOKENS(){
		read_data = "";
		ans = 0;
	}
	void read(string io_in){
		int len = io_in.length();
		for(int i = 0; i < len; i++){
			if(io_in[i] != ' ') read_data += io_in.substr(i, 1);
		}
	}
	bool deal(string read_data, double &res){
	    int op[TOKENS_SIZE];
	    char tmp[TOKENS_SIZE];
	    int cnt = 0;
	    double tem = 0, num[TOKENS_SIZE];
	    int last_0_flag = 0, len = read_data.size();
	    int dot_flag = 0, cnt_dot = 0;
	    for(int i = 0; i < len; i++) tmp[i] = read_data[i];
	    for(int i = 0; i < TOKENS_SIZE; i++) op[i] = 0;
	    for (int i = 0; i < len; i++)
	    {
            if (!('0' <= tmp[i] && tmp[i] <= '9'))
            {
            	if(tmp[i] == '.'){
            		if(dot_flag) return false;
            		dot_flag = 1;
            	}
                else if (tem != 0 || last_0_flag == 1)
                {
                	for(int i = 1; i <= cnt_dot; i++) tem /= 10.0;
                    num[cnt++] = tem;
                    tem = 0;
                    last_0_flag = 0;
                    dot_flag = 0;
                    cnt_dot = 0;
                }
                else if(i == 0 || (tmp[i - 1] != ')' && !('0' <= tmp[i - 1] && tmp[i - 1] <= '9'))){
                    len += 2;
                    for(int j = len - 1; j >= i + 2; j--){
                            tmp[j] = tmp[j - 2];
                    }
                    tmp[i + 1] = '1';
                    tmp[i + 2] = '*';
                    op[i] = 1;
                }
            }
            else
            {
                tem = tem * 10.0 + (tmp[i] - '0') * 1.0;
                if(tem == 0) last_0_flag = 1;
                else last_0_flag = 0;
                if(dot_flag) cnt_dot++;
            }
	    }
	    if (tem != 0 || last_0_flag){
	    	for(int i = 1; i <= cnt_dot; i++) tem /= 10.0;
	    	num[cnt++] = tem;
	     	// 需要处理最后一个操作数是0 的情况！！
	    }
	    // for(int i = 0; i < cnt; i++) printf("%.3f\n", num[i]);
	    int cnt_stack = 0, cnt_token = 0, tem_num = 0, stack[TOKENS_SIZE];
	    double token[TOKENS_SIZE]; // stack为操作符栈  token为后缀表达式
	    stack[0] = '#';                                                        // '#'
	    int priority_map[TOKENS_SIZE];
	    // cnt_stack 指向当前最后一个有效操作符
	    // init the map
	    priority_map[35] = 0; // #
	    priority_map[40] = 1; // (
	    priority_map[43] = 2; // +
	    priority_map[45] = 2; // -
	    priority_map[42] = 3; // *
	    priority_map[47] = 3; // /
	    priority_map[41] = 4; // )

	    int flag = 0;
	    double minus_flag = 1.0;
	    int suf_op_pos[TOKENS_SIZE];
	    for(int i = 0; i < TOKENS_SIZE; i++) suf_op_pos[i] = 0;
	    for (int i = 0; i < len; i++)
	    {
	            if (('0' <= tmp[i] && tmp[i] <= '9') || tmp[i] == '.')
	            { // num
	                if (!flag)
	                {
	                    flag = 1;
	                    token[cnt_token] = num[tem_num++] * minus_flag;
	                    suf_op_pos[cnt_token] = 1;
	                    minus_flag = 1.0;
	                    cnt_token++;
	                }
	            }
	            else
	            { // op
	                flag = 0;
	                if (tmp[i] == '(')
	                {                             // st[i] = 1
	                    stack[++cnt_stack] = '('; // (
	                }
	                else if (tmp[i] == '+' || (tmp[i] == '-' && !op[i]))
	                {
	                    while (cnt_stack && priority_map[stack[cnt_stack]] >= priority_map[(int)tmp[i]])
	                    {
	                        token[cnt_token++] = -stack[cnt_stack];
	                        cnt_stack--;
	                    }
	                    stack[++cnt_stack] = tmp[i];
	                }
	                else if (tmp[i] == '*' || tmp[i] == '/')
	                {
	                    while (cnt_stack && priority_map[stack[cnt_stack]] >= priority_map[(int)tmp[i]])
	                    {
	                        token[cnt_token++] = -stack[cnt_stack];
	                        cnt_stack--;
	                    }
	                    stack[++cnt_stack] = tmp[i];
	                }
	                else if (tmp[i] == ')')
	                {
	                    while (cnt_stack && stack[cnt_stack] != '(')
	                    {
	                        token[cnt_token++] = -stack[cnt_stack];
	                        cnt_stack--;
	                    }
	                    cnt_stack--;
	                }
	                else if(tmp[i] == '-'){
	                    minus_flag = -1.0;
	                }
	                else
	                {
	                    // ignore the space
	                }
	            }
	    }
	    while (cnt_stack)
	    {
	            token[cnt_token++] = -stack[cnt_stack];
	            cnt_stack--;
	    }
	    // for(int i = 0; i < cnt_token; i++) cout << token[i] << endl;
	    int cal_num = 0;
	    double cal_stack[TOKENS_SIZE];
	    for (int i = 0; i < cnt_token; i++)//
	    {
	            if (suf_op_pos[i])
	            {
	                cal_stack[cal_num++] = token[i];
	            }
	            else if (token[i] == -43)
	            {
	                cal_stack[cal_num - 2] = cal_stack[cal_num - 2] + cal_stack[cal_num - 1];
	                cal_num--;
	            }
	            else if (token[i] == -45)
	            {
	                cal_stack[cal_num - 2] = cal_stack[cal_num - 2] - cal_stack[cal_num - 1];
	                cal_num--;
	            }
	            else if (token[i] == -42)
	            {
	                cal_stack[cal_num - 2] = cal_stack[cal_num - 2] * cal_stack[cal_num - 1];
	                cal_num--;
	            }
	            else if (token[i] == -47)
	            {
	            	if(abs(cal_stack[cal_num - 1]) < eps) return false;
	                cal_stack[cal_num - 2] = cal_stack[cal_num - 2] / cal_stack[cal_num - 1];
	                cal_num--;
	            }
	    }
	    if(cal_num > 1) return false;
	    res = cal_stack[0];
	    return true;
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
			if(i > 0 && find(read_data[i], op) && find(read_data[i - 1], op)) return false; // +*
			if(i > 0 && read_data[i] == ')' && find(read_data[i - 1], op)) return false; // -)
			if(i == len - 1 && find(read_data[i], op)) return false; // last_op
			if(i > 0 && read_data[i - 1] == '(' && find(read_data[i], op) && read_data[i] != '-') return false; // (+		
			if(cnt < 0) return false;
		}
		if(cnt != 0) return false;
		return deal(read_data, ans);
	}
	double out(){
		return ans;
	}
private:
	string read_data;
	double ans;
};