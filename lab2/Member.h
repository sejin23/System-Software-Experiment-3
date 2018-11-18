#include <string>
using namespace std;
typedef struct _rsv{
	int date[3];
	int stt, rsv;
	struct _rsv* next;
}rsvt;

class Member{
	protected:
		string memname;
		rsvt* rsvhead;
		Member();
};

class Undergraduate: public Member{
	private:
		int maxRST;
		int numOfBorrow;
	public:
		Undergraduate();
		string getUserName();
		void setRsv(int* d, int time);
		int RSTdiff(int* d, int time);
};
