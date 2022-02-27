#include <bits/stdc++.h>
#include <regex>
#include <unistd.h>
using namespace std;
class SQL{
public:
	string SELECT_G(string name, string colomn = "", string value = ""){
		string res = "";
		res += "SELECT * FROM " + name;
		if(colomn != ""){
			res += " WHERE " + colomn + " CONTAINS " + value;
		}
		return res;
	}
	string INSERT_G(string name, vector <string> data){
		string res = "";
		res += "INSERT INTO " + name + " VALUES " + "(";
		for(int i = 0; i < data.size(); i++){
			res += data[i];
			if(i + 1 != data.size()) res += ",";
		}
		res += ")";
		return res;
	}
	string UPDATE_G(string name, vector<string> col, vector<string> val, string sel_col, string sel_val){
		string res = "";
		res += "UPDATE " + name + " SET ";
		for(int i = 0; i < val.size(); i++){
			res += col[i] + " = " + val[i];
			if(i + 1 != val.size()) res += ","; 
		}
		res += " WHERE ";
		res += sel_col + " = " + sel_val;
		return res;
	}
	int regex_m(string T){
		regex instr_pattern[] = {
			regex("(\\s*INSERT\\s+INTO\\s+)([A-Z_0-9a-z\u4e00-\u9fa5]+)(\\s+VALUES\\s+)([(].*[)]\\s*)"),
			regex("(\\s*UPDATE\\s+)([A-Z_0-9a-z\u4e00-\u9fa5]+)\\s+(SET)\\s+(.*(?=WHERE))(WHERE)\\s+([A-Z_0-9a-z\u4e00-\u9fa5]+)\\s+(=)\\s+([A-Z_0-9a-z\u4e00-\u9fa5]+)\\s*"),//=
			regex("(\\s*SELECT\\s+)(.*)(?=\\s)\\s+(FROM\\s+)(.*(?=\\s))\\s+(WHERE\\s+)([A-Z_0-9a-z\u4e00-\u9fa5]+)\\s+(CONATINS)\\s+([A-Z_0-9a-z\u4e00-\u9fa5]+)\\s*"),
			regex("(\\s*SELECT\\s+)(.*)(?=\\s)\\s+(FROM\\s+)([A-Z_0-9a-z\u4e00-\u9fa5]+\\s*)"), //检查是否是*
		};
		int cnt = sizeof(instr_pattern) / sizeof(regex);
		smatch res;
		for(int i = 0; i < cnt; i++){
			if(regex_match(T, res, instr_pattern[i])){
				return i;
			}
		}
		return -1;
	}
};