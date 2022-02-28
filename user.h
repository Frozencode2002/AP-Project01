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
	void eline(){
		cout << "==============================================================================================\n";
	}
	void main_menu(){
		eline();
		cout << "1.我是买家 2.我是卖家 3.个人信息管理 4.注销登录\n";
		eline();
	}
	void sell_menu(){
		eline();
		cout << "1.发布商品 2.查看发布商品 3.修改商品信息 4.下架商品 5.查看历史订单 6.返回用户主界面\n";
		eline();
	}
	void buy_menu(){
		eline();
		cout << "1.查看商品列表 2.购买商品 3.搜索商品 4.查看历史订单 5.查看商品详细信息 6.返回用户主界面\n";
		eline();
	}
	void modify_menu(){
		eline();
		cout << "1.查看信息 2.修改信息 3.充值 4.返回用户主界面\n";
		eline();
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
	string getTime(){
	    time_t timep;
	    time (&timep); //获取time_t类型的当前时间
	    char tmp[64];
	    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S",localtime(&timep) );//对日期和时间进行格式化
	    return tmp;
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
	void write_cmd(string name, int op, string sel_col = "", string sel_val = "", vector <string> col = {}, vector <string> val = {}){
		string ord = getTime();
		ord += ": ";
		if(op == 1){
			ord += G.SELECT_G(name, sel_col, sel_val);
		}
		else if(op == 2){
			ord += G.INSERT_G(name, val);
		}	
		else{
			ord += G.UPDATE_G(name, col, val, sel_col, sel_val);
		}
		ofstream cmd("commands.txt", ios::app);
		cmd << "\n";
		cmd << ord;
		cmd.close();
	}
	void run(string user_id){
		main_menu();
		string op;
		cout << "输入操作:";
		cin >> op;
		while(op != "4"){
			if(op == "1"){
				buy_run(user_id);
			}
			else if(op == "2"){
				sell_run(user_id);
			}
			else if(op == "3"){
				modify_run(user_id);
			}
			else{
				cout << "您输入的操作不合法！\n";
			}
			main_menu();
			cout << "输入操作:";
			cin >> op;
		}
		return;
	}
	void buy_run(string user_id){
		buy_menu();
		string op;
		cout << "请输入操作:";
		cin >> op;
		while(op != "6"){
			if(op == "1"){

			}
			else if(op == "2"){

			}
			else if(op == "3"){

			}
			else if(op == "4"){

			}
			else if(op == "5"){

			}
			else{
				cout << "您输入的操作不合法！\n";
			}
			buy_menu();
			cout << "请输入操作:";
			cin >> op;
		}
		return;
	}
	void sell_run(string user_id){
		sell_menu();
		string op;
		cout << "请输入操作:";
		cin >> op;
		while(op != "6"){
			if(op == "1"){
				sell_release(user_id);
			}
			else if(op == "2"){
				sell_view(user_id);
			}
			else if(op == "3"){
				sell_modify(user_id);
			}
			else if(op == "4"){
				sell_ban(user_id);
			}
			else if(op == "5"){
				sell_view_ord(user_id);
			}
			else{
				cout << "您输入的操作不合法！\n";
			}
			sell_menu();
			cout << "请输入操作:";
			cin >> op;
		}
		return;
	}
	void modify_run(string user_id){
		modify_menu();
		string op;
		cout << "输入操作:";
		cin >> op;
		while(op != "4"){
			if(op == "1"){

			}
			else if(op == "2"){

			}
			else if(op == "3"){

			}
			else{
				cout << "您输入的操作不合法！\n";
			}
			modify_menu();
			cout << "输入操作:";
			cin >> op;
		}
		return;
	}
	void sell_release(string user_id){
		bool flag = true;
		vector <string> good_info;
		string user_in;
		cout << "请输入商品名称:";
		cin >> user_in;
		good_info.push_back(user_in);
		cout << "请输入商品价格:";
		cin >> user_in;
		if(stod(user_in) < 0.0) flag = false;
		good_info.push_back(user_in);
		cout << "请输入商品数量:";
		cin >> user_in;
		if(stoi(user_in) <= 0) flag = false;
		good_info.push_back(user_in);
		cout << "请输入商品描述:";
		cin >> user_in;
		good_info.push_back(user_in);
		cout << "请确认发布的商品信息无误!\n";
		cut_line();
		cout << "商品名称:";
		cout << good_info[0] << endl;
		cout << "商品价格:";
		cout << good_info[1] << endl;
		cout << "商品数量:";
		cout << good_info[2] << endl;
		cout << "商品描述:";
		cout << good_info[3] << endl;  
		cut_line();
		cout << "您确认要发布商品吗?(y/n)";
		cin >> user_in;
		if(user_in == "y" && flag){
			write_cmd("commodity", 2, "", "", {}, good_info);
			cout << "发布成功!\n";
			string g_id = get_hash();
			string g_time = getTime();
			ofstream good_list("commodity.txt", ios::app);
			good_list << "\n";
			good_list << g_id <<",";
			for(auto s : good_info) good_list << s << ",";
			good_list << user_id << ",";
			good_list << g_time.substr(0, 10) << ",";
			good_list << "销售中";
			good_list.close();
		}
		else{
			cout << "发布失败!(人为取消或商品属性不合法)\n";
		}
	}
	void sell_view(string user_id){
		write_cmd("commodity", 1);
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
			if(one_line[5] == user_id || one_line[5] == "卖家ID") COMMODITY.push_back(one_line);
		}
		good_list.close();
		cut_line();
		ui_print(COMMODITY);
		cut_line();
	}
	void sell_modify(string user_id){
		bool flag = true, inc = false;
		string g_id, op, g_info, g_val;
		cout << "请输入被修改的商品ID:";
		cin >> g_id;
		cout << "请输入被修改的商品属性:(1.价格 2.描述)";
		cin >> op;
		if(op != "1" && op != "2"){
			cout << "此操作不合法!\n";
			return;
		}
		if(op == "1"){
			cout << "请输入被修改的商品价格:";
			cin >> g_val;
			if(stod(g_val) < 0.0){
				cout << "商品价格不合法!\n";
				return;
			}
		}
		else{
			cout << "请输入被修改的商品描述:";
			cin >> g_info;
		}

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
			if(one_line[0] == g_id){
				inc = true;
				if(one_line[5] != user_id) flag = false;
			}
		}
		good_list.close();
		if(!inc){
			cout << "该商品不存在!\n";
			return;
		}
		if(!flag){
			cout << "您不是该商品的卖家，无权限修改!\n";
			return;
		}
		for(int i = 0; i < COMMODITY.size(); i++){
			if(COMMODITY[i][0] == g_id){
				if(op == "1"){
					COMMODITY[i][2] = g_val;
				}
				else{
					COMMODITY[i][4] = g_info;
				}
			}
		}
		cout << "请确认修改的商品信息无误!\n";
		cut_line();
		for(auto s : COMMODITY){
			if(s[0] == g_id || s[0] == "商品ID"){
				for(int i = 0; i < s.size(); i++){
					cout << s[i];
					if(i + 1 != s.size()) cout << ",";
				}
				cout << "\n";
			}
		}
		cut_line();
		cout << "确认修改?(y/n)";
		string uop;
		cin >> uop;
		if(uop == "y"){
			cout << "修改成功!\n";
			file_print(COMMODITY, "commodity.txt");
			if(op == "1"){
				write_cmd("commodity", 3, "商品ID", g_id, {"价格"}, {g_val});
			}
			else{
				write_cmd("commodity", 3, "商品ID", g_id, {"描述"}, {g_info});
			}
		}
		else{
			cout << "修改失败!\n";
		}
	}
	void sell_ban(string user_id){
		bool flag = true, inc = false;
		string g_id;
		cout << "请输入要下架的商品ID:";
		cin >> g_id;

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
			if(one_line[0] == g_id){
				inc = true;
				if(one_line[5] != user_id) flag = false;
			}
		}
		good_list.close();
		if(!inc){
			cout << "该商品不存在!\n";
			return;
		}
		if(!flag){
			cout << "您不是该商品的卖家，无权限修改!\n";
			return;
		}
		cout << "请确认是否下架该商品!\n";
		cut_line();
		for(auto s : COMMODITY){
			if(s[0] == g_id || s[0] == "商品ID"){
				for(int i = 0; i < s.size(); i++){
					cout << s[i];
					if(i + 1 != s.size()) cout << ",";
				}
				cout << "\n";
			}
		}
		cut_line();
		for(int i = 0; i < COMMODITY.size(); i++){
			if(COMMODITY[i][0] == g_id){
				COMMODITY[i][7] = "已下架";
			}
		}
		cout << "确认下架?(y/n)";
		string op;
		cin >> op;
		if(op == "y"){
			cout << "下架成功!\n";
			write_cmd("commodity", 3, "商品ID", g_id, {"商品状态"}, {"已下架"});
			file_print(COMMODITY, "commodity.txt");
		}
		else{
			cout << "下架失败!\n";
		}
	}
	void sell_view_ord(string user_id){
		write_cmd("order", 1);
		ifstream ord_list("order.txt", ios::in);
		vector <vector<string>> ORDER;
		regex cat_line_info("([A-Z0-9a-z\\-\\.\u4e00-\u9fa5]+)(?=[,]*)"); //merge!
		while(!ord_list.eof()){
			string line_info, tokens;
			smatch tem_word;
			vector<string> one_line;
			getline(ord_list, line_info);	
			string::const_iterator iterstart = line_info.begin();
			string::const_iterator iterend = line_info.end();
			while(regex_search(iterstart, iterend, tem_word, cat_line_info)){
				tokens = tem_word[0];
				one_line.push_back(tokens);
				iterstart = tem_word[0].second;
			}
			if(one_line[5] == user_id || one_line[5] == "卖家ID") ORDER.push_back(one_line);
		}
		ord_list.close();
		cut_line();
		ui_print(ORDER);
		cut_line();
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
	string log_in(string name, string password){ // return user id
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
private:
	SQL G;
};