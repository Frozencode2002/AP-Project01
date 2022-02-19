#include "cal.h"
#include <bits/stdc++.h>
using namespace std;
int main(){
	TOKENS a;
	string n;
	cin >> n;
	a.read(n);
	cout << a.io_check() << endl;
}