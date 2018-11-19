#include <string>
using namespace std;

class Member{
	protected:
		string memname;
		Member();
};

class Undergraduate: public Member{
	private:
		int numOfBorrow;
		int delayed[3];
	public:
		Undergraduate();
		string getUserName();
		int comparedate(int* d);
		int* getdelayed();
		void setmember(string mem_name);
		void setdelayed(int* d, int* delay);
};
