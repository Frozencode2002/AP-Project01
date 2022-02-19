#define TOKENS_SIZE = 100
class TOKENS{
public:
	TOKENS(){
		data = 0;
		return;
	}
	void modify(int x){
		data = x;
	}
	int show(){
		return data;
	}
 	void f(TOKENS x, TOKENS y){
		data = x.show() + y.show();
	}
private:
	int data;
};