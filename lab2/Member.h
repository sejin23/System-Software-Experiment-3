#include <string>
#include <vector>
using namespace std;
typedef struct ebkin{
	string rscname;
	int cap;
	int retd[3];
}Ebkin;
class Member {
	protected:
		string username;	//유저 정보
		vector<Ebkin> ebk;	//빌린 전자 책의 정보
		int srcnum, srcmax, e_storage, max_storage;	//빌린 책의 권 수, 전자책 용량
		int delay[3];	//연체 시간 년월일
		Member(string mem_name, int usablersc);
		~Member();
	public:
		string getusername();
		int* getdelayeddate();
		int notborrowmore();
		int isdelayedMem(int* d);
		int setborrow();
		void setreturn();
		int* setdelayreturn(int* retdate, int* nowdate);
		int canmoreEbook(int cap, string src, string mem_type, int* d);
		int checkEbook(string src, int* d);
		void deleteEbook(int cap, string src_name);
};

class Undergraduate: public Member{
	public:
		Undergraduate(string name);
};

class Graduate: public Member{
	public:
		Graduate(string name);
};

class Faculty: public Member{
	public:
		Faculty(string name);
};