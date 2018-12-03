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
		string username;
		vector<Ebkin> ebk;
		int srcnum, srcmax, e_storage, max_storage;
		int delay[3];
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