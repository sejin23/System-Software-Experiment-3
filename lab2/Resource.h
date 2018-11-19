#include <string>
#include "Member.h"
using namespace std;

class Resource{
	protected:
		string srcname;
		char state;
		int duedate[3];
		Undergraduate* und;
		Resource(string src_name);
		~Resource();
};

class Book: public Resource{
	public:
		Book(string src_name);
		char getrscstate();
		string getsrcname();
		string getusername();
		void borrowresrc(string mem_name, string mem_type, int* d);
		int returnresrc(string mem_name, string mem_type, int* d);
		int* getdelay();
};

int CompareDate(int* srcDate, int* dueDate);