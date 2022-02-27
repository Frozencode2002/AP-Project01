#ifndef _SQL_H_
	#define _SQL_H_
	#include "SQL.h"
#endif
using namespace std;
class user{
public:
	void cut_line(){
		cout << "****************************************************************\n";
	}
	void ui_print(vector<vector<string>> &out){
		for(int i = 0; i < out.size(); i++){
			vector <string> line = out[i];
			for(int j = 0; j < line.size(); j++){
				cout << line[j];
				if(j + 1 != line.size()) cout << ",";
			}
			cout << "\n";
		}	
	}
	void file_print(vector<vector<string>> &out, string filename){
		ofstream file(filename, ios::out);
		for(int i = 0; i < out.size(); i++){
			vector <string> line = out[i];
			for(int j = 0; j < line.size(); j++){
				file << line[j];
				if(j + 1 != line.size()) file << ",";
			}
			if(i + 1 != out.size()) file << "\n";
		}
		file.close();
	}
	string get_hash(){
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		mt19937 rand_num(seed);  // 大随机数
		uniform_int_distribution<long long> dist(0, 14776336);  // 给定范围
		int num = dist(rand_num);
		string res = "";
		for(int i = 0; i < 4; i++){
			int tem = num % 62;
			num /= 62;
			if(tem < 10){
				res += to_string(tem);
			}
			else if(tem < 36){
				tem -= 10;
				res.push_back((char)('A' + tem));
			}
			else{
				tem -= 36;
				res.push_back((char)('a' + tem));
			}
		}
		return res;
	}
	void user_reg(){
		vector <string> info;
		string user_in;
		cout << "请输入用户名:";
		cin >> user_in;
		info.push_back(user_in);
		cout << "请输入密码:";
		cin >> user_in;
		info.push_back(user_in);
		cout << "请输入联系方式:";
		cin >> user_in;
		info.push_back(user_in);
		cout << "请输入地址:";
		cin >> user_in;
		info.push_back(user_in);

		bool flag = true;
		ifstream user_file("user.txt", ios::in);
		vector <vector<string>> all_info;
		vector <string> user_name;
		regex cat_line_info("([A-Z0-9a-z\\-\\.\u4e00-\u9fa5]+)(?=[,]*)"); //merge!
		while(!user_file.eof()){
			string line_info, tokens;
			smatch tem_word;
			vector<string> one_line;
			getline(user_file, line_info);	
			string::const_iterator iterstart = line_info.begin();
			string::const_iterator iterend = line_info.end();
			while(regex_search(iterstart, iterend, tem_word, cat_line_info)){
				tokens = tem_word[0];
				one_line.push_back(tokens);
				iterstart = tem_word[0].second;
			}
			user_name.push_back(one_line[1]);
			all_info.push_back(one_line);
		}
		user_file.close();
		for(auto s : user_name) if(s == info[0]) flag = false;
		if(!flag){
			while(!flag){
				cout << "您输入的用户名与现有用户名重复，请输入新的用户名:";
				cin >> info[0];
				flag = true;
				for(auto s : user_name) if(s == info[0]) flag = false;
			}
		}
		string ID = get_hash();
		bool uni_flag = true;
		for(auto s : all_info) if(s[0] == ID) uni_flag = false;
		while(!uni_flag){
			ID = get_hash();
			uni_flag = true;
			for(auto s : all_info) if(s[0] == ID) uni_flag = false;
		}
		vector <string> new_user;
		new_user.push_back(ID);
		for(auto s : info) new_user.push_back(s);
		new_user.push_back("0.0");
		new_user.push_back("正常");
		all_info.push_back(new_user);
		file_print(all_info, "user.txt");
		cout << "注册成功！" << "\n";
	}
	string log_in(string name, string password){
		string res = "";
		ifstream user_file("user.txt", ios::in);
		vector <vector<string>> all_info;
		regex cat_line_info("([A-Z0-9a-z\\-\\.\u4e00-\u9fa5]+)(?=[,]*)"); //merge!
		while(!user_file.eof()){
			string line_info, tokens;
			smatch tem_word;
			vector<string> one_line;
			getline(user_file, line_info);	
			string::const_iterator iterstart = line_info.begin();
			string::const_iterator iterend = line_info.end();
			while(regex_search(iterstart, iterend, tem_word, cat_line_info)){
				tokens = tem_word[0];
				one_line.push_back(tokens);
				iterstart = tem_word[0].second;
			}
			all_info.push_back(one_line);
			if(one_line[1] == name && one_line[2] == password){
				res = one_line[0];
			}
		}
		user_file.close();
		return res;
	}
};