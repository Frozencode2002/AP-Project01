#include "gettime.h"
#include "SQL.h"
#include <regex>
#include <unistd.h>
using namespace std;
class admin{
public:
	string getTime(){
	    time_t timep;
	    time (&timep); //获取time_t类型的当前时间
	    char tmp[64];
	    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S",localtime(&timep) );//对日期和时间进行格式化
	    return tmp;
	}
	admin(){
		username = "admin";
		password = "123456";
	}
	bool verify(string user_in, string password_in){
		return (user_in == username) && (password == password_in);
	}
	void cut_line(){
		cout << "****************************************************************\n";
	}
	void menu(){
		cout << "=============================================================================================\n";
		cout << "1.查看所有商品 2.搜索所有商品 3.下架所有商品 4.查看所有订单 5.查看所有用户 6.封禁用户 7.注销\n";
		cout << "=============================================================================================\n";
	}
	void run(){
		menu();
		cout << "请输入操作:";
		string op;
		cin >> op;
		while(op != "7"){
			if(op == "1"){
				view_good();
			}
			else if(op == "2"){
				cout << "请输入商品名称:";
				string g_name;
				cin >> g_name;
				search_good(g_name);	
			}
			else if(op == "3"){
				cout << "请输入要下架的商品ID:";
				string id;
				cin >> id;
				disable_good(id);
			}
			else if(op == "4"){
				view_order();
			}
			else if(op == "5"){
				view_user();
			}
			else if(op == "6"){
				cout << "请输入要封禁的用户ID:";
				string id;
				cin >> id;
				disable_user(id);
			}
			else{
				cout << "选项不合法\n";
			}
			menu();
			cout << "请输入操作:";
			cin >> op;
		}
		cout << "注销成功\n";
		return;
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
	void view_good(){
		string ord = getTime();
		ord += ": " + G.SELECT_G("commodity");
		ofstream cmd("command.txt", ios::app);
		cmd << "\n";
		cmd << ord;
		cmd.close();

		ifstream good_list("commodity.txt", ios::in);
		vector <vector<string>> COMMODITY;
		regex cat_line_info("([A-Z0-9a-z\\-\\.\u4e00-\u9fa5]+)(?=[,]*)"); //merge!
		while(!good_list.eof()){
			string line_info, tokens;
			smatch tem_word;
			vector<string> one_line;
			getline(good_list, line_info);	
			string::const_iterator iterstart = line_info.begin();
			string::const_iterator iterend = line_info.end();
			while(regex_search(iterstart, iterend, tem_word, cat_line_info)){
				tokens = tem_word[0];
				one_line.push_back(tokens);
				iterstart = tem_word[0].second;
			}
			COMMODITY.push_back(one_line);
		}
		good_list.close();
		cut_line();
		ui_print(COMMODITY);
		cut_line();
	}
	void search_good(string good_name){
		ifstream good_list("commodity.txt", ios::in);
		vector <vector<string>> COMMODITY;
		regex cat_line_info("([A-Z0-9a-z\\-\\.\u4e00-\u9fa5]+)(?=[,]*)"); //merge!
		while(!good_list.eof()){
			string line_info, tokens;
			smatch tem_word;
			vector<string> one_line;
			getline(good_list, line_info);	
			string::const_iterator iterstart = line_info.begin();
			string::const_iterator iterend = line_info.end();
			while(regex_search(iterstart, iterend, tem_word, cat_line_info)){
				tokens = tem_word[0];
				one_line.push_back(tokens);
				iterstart = tem_word[0].second;
			}
			if(one_line[0] == "商品ID" || one_line[1] == good_name) COMMODITY.push_back(one_line);
		}
		good_list.close();
		cut_line();
		ui_print(COMMODITY);
		cut_line();
	}
	void disable_good(string good_id){
		ifstream good_list("commodity.txt", ios::in);
		vector <vector<string>> COMMODITY;
		regex cat_line_info("([A-Z0-9a-z\\-\\.\u4e00-\u9fa5]+)(?=[,]*)"); //merge!
		cout << "确认要下架该商品吗?" << endl;
		cut_line();
		while(!good_list.eof()){
			string line_info, tokens;
			smatch tem_word;
			vector<string> one_line;
			getline(good_list, line_info);	
			string::const_iterator iterstart = line_info.begin();
			string::const_iterator iterend = line_info.end();
			while(regex_search(iterstart, iterend, tem_word, cat_line_info)){
				tokens = tem_word[0];
				one_line.push_back(tokens);
				iterstart = tem_word[0].second;
			}
			if(one_line[0] == "商品ID" || one_line[0] == good_id){
				for(int i = 0; i < one_line.size(); i++){
					cout << one_line[i];
					if(i + 1 != one_line.size()) cout << ",";
				}
				cout << "\n";
			}
			if(one_line[0] == good_id) one_line[7] = "已下架";
			COMMODITY.push_back(one_line);
		}
		good_list.close();
		cut_line();
		cout << "请选择(y/n):";
		string option;
		cin >> option;
		if(option == "y"){
			cout << "下架成功\n";
			file_print(COMMODITY, "commodity.txt");
		}
		else{
			cout << "取消下架\n";
		}
	}
	void view_order(){
		ifstream order_list("order.txt", ios::in);
		vector <vector<string>> order;
		regex cat_line_info("([A-Z0-9a-z\\-\\.\u4e00-\u9fa5]+)(?=[,]*)"); //merge!
		while(!order_list.eof()){
			string line_info, tokens;
			smatch tem_word;
			vector<string> one_line;
			getline(order_list, line_info);	
			string::const_iterator iterstart = line_info.begin();
			string::const_iterator iterend = line_info.end();
			while(regex_search(iterstart, iterend, tem_word, cat_line_info)){
				tokens = tem_word[0];
				one_line.push_back(tokens);
				iterstart = tem_word[0].second;
			}
			order.push_back(one_line);
		}
		order_list.close();
		cut_line();
		ui_print(order);
		cut_line();
	}
	void view_user(){
		ifstream user_list("user.txt", ios::in);
		vector <vector<string>> user;
		regex cat_line_info("([A-Z0-9a-z\\-\\.\u4e00-\u9fa5]+)(?=[,]*)"); //merge!
		while(!user_list.eof()){
			string line_info, tokens;
			smatch tem_word;
			vector<string> one_line;
			getline(user_list, line_info);	
			string::const_iterator iterstart = line_info.begin();
			string::const_iterator iterend = line_info.end();
			while(regex_search(iterstart, iterend, tem_word, cat_line_info)){
				tokens = tem_word[0];
				one_line.push_back(tokens);
				iterstart = tem_word[0].second;
			}
			user.push_back(one_line);
		}
		user_list.close();
		cut_line();
		ui_print(user);
		cut_line();
	}
	void ban_good_by_user(string name){
		ifstream good_list("commodity.txt", ios::in);
		vector <vector<string>> COMMODITY;
		regex cat_line_info("([A-Z0-9a-z\\-\\.\u4e00-\u9fa5]+)(?=[,]*)"); //merge!
		while(!good_list.eof()){
			string line_info, tokens;
			smatch tem_word;
			vector<string> one_line;
			getline(good_list, line_info);	
			string::const_iterator iterstart = line_info.begin();
			string::const_iterator iterend = line_info.end();
			while(regex_search(iterstart, iterend, tem_word, cat_line_info)){
				tokens = tem_word[0];
				one_line.push_back(tokens);
				iterstart = tem_word[0].second;
			}
			if(one_line[5] == name) one_line[7] = "已下架";
			COMMODITY.push_back(one_line);
		}
		good_list.close();
		file_print(COMMODITY, "commodity.txt");
	}
	void disable_user(string name){
		ifstream user_list("user.txt", ios::in);
		vector <vector<string>> user;
		regex cat_line_info("([A-Z0-9a-z\\-\\.\u4e00-\u9fa5]+)(?=[,]*)"); //merge!
		cout << "确认要封禁该用户吗?" << endl;
		cut_line();
		while(!user_list.eof()){
			string line_info, tokens;
			smatch tem_word;
			vector<string> one_line;
			getline(user_list, line_info);	
			string::const_iterator iterstart = line_info.begin();
			string::const_iterator iterend = line_info.end();
			while(regex_search(iterstart, iterend, tem_word, cat_line_info)){
				tokens = tem_word[0];
				one_line.push_back(tokens);
				iterstart = tem_word[0].second;
			}
			if(one_line[0] == "用户ID" || one_line[0] == name){
				for(int i = 0; i < one_line.size(); i++){
					cout << one_line[i];
					if(i + 1 != one_line.size()) cout << ",";
				}
				cout << "\n";
			}
			if(one_line[0] == name) one_line[6] = "封禁";
			user.push_back(one_line);
		}
		user_list.close();
		cut_line();
		cout << "请选择(y/n):";
		string option;
		cin >> option;
		if(option == "y"){
			cout << "封禁成功\n";
			file_print(user, "user.txt");
		}
		else{
			cout << "封禁失败\n";
		}
	}
private:
	string username, password;
	SQL G;
};