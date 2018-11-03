#include <string>
#include "Resource.h"
using namespace std;

typedef struct _mem{
	int numOfBorrow;
	Member* user;
	Date restricted;
	struct _mem* next;
}Mem;

class Library{
	private:
		Mem* header;
		Resource* Resrc;
		int op;
	public:
		Library();
		~Library();
		int setLib(string username, string usertype, string Src, string Srctype, char state, Date* condate);
		int getMemTypeMaxNOB(string memname, string memtype);
		Date* getBorrowedDate(string src, string srctype);
		Date* getRestrictedDate(string memname);
};
