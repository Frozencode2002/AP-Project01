#include  "SQL.h"
using namespace std;
int main(){
	vector <string> col = {"qwq", "233"};
	vector <string> val = {"555", "666"};
	string name = "hhh";
	string sel_col = "hhhh", sel_val = "wwwww";
	SQL A;
	cout << A.SELECT_G(name, sel_col, sel_val) << endl;
	cout << A.INSERT_G(name, col) << endl;
	cout << A.UPDATE_G(name, col, val, sel_col, sel_val) << endl;
}