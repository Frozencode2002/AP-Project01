#include "cal.h"
#include <bits/stdc++.h>
using namespace std;
int main(){
	TOKENS A, B, C;
	A.modify(1);
	B.modify(2);
	C.f(A, B);
	cout << C.show();
}