#include "cal.h"
#include <bits/stdc++.h>
using namespace std;
int main(){
	TOKENS a;
	string n;
	getline(cin, n);
	a.read(n);
	cout << a.io_check() << endl;
	printf("%.1f", a.out());
}