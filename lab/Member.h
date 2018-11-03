#include <string>
using namespace std;

class Undergraduate{
	private:
		int numOfBorrow;
	protected:
		Undergraduate();
		int getNumOfBorr();
};

class Member: public Undergraduate{
	private:
		string Rsrcname;
	public:
		Member(string name, string type);
		string getMemName();
		int getNOBbyMem(string type);		
};
