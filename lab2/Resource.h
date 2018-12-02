#include <string>
#include <vector>
using namespace std;

class Resource{
	protected:
		string srcname;	//자원 이름
		string usrname;	//대여 유저정보
		char state;		//현재 대여 상태
		int brwdate[3];	//빌린 날짜 년,월,일
		int retdate[3];	//반납일 년,월,일
		Resource(string src);
	public:
		string getsrcname();
		string getusrname();
		int isborrowed();
		int* getborroweddate();
		int* getreturndate();
		void setBorrow(string mem_name, string mem_type, int* nowdate);
		int returnresrc(int* d);
};

class Book: public Resource{
	public:
		Book(string src_name);
};
typedef struct _monthly{
	string month; 
	string user;
	int brwdate[3];
	int retdate[3];
}M_User;
class Magazine: public Resource{
	private:
		vector<M_User> muser;
	public:
		Magazine(string src_name);
		int isborrowedmgz(string month);
		string getmgzusrname(string month);
		int* getmgzborroweddate(string month);
		int* getmgzreturndate(string month);
		void setMgzBorrow(string mem_name, string mem_type, string month, int* nowdate);
		int returnMgzsrc(int* d, string month);
};

class E_book: public Resource{
	private:
		int capacity;
	public:
		E_book(string src_name, int cap);
		int getcapacity();
};