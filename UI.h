#include "user.h"
#include "admin.h"
class UI{
public:
	void eline(){
		cout << "==============================================================\n";
	}
	void menu(){
		eline();
		cout << "1.管理员登录 2.用户注册 3.用户登录 4.退出程序\n";
		eline();
	}
	void run(){
		menu();
		admin ad;
		user u;	
		string op;
		cout << "输入操作:";
		cin >> op;
		while(op != "4"){
			if(op == "1"){
				ad.run();
			}
			else if(op == "2"){
				u.user_reg();
			}
			else if(op == "3"){
				string name, pwd;
				cout << "请输入用户名:";
				cin >> name;
				cout << "请输入密码:";
				cin >> pwd;
				string ans = u.log_in(name, pwd);
				if(ans == ""){
					cout << "登录失败!\n";
				}
				else{
					// u.run with id
				}
			}
			else{
				cout << "请输入合法的操作!\n";
			}
			menu();
			cout << "输入操作:";
			cin >> op;
		}
		return;
	}
};