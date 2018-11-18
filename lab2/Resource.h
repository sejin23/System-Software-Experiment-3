#include <string>
#include "Member.h"
using namespace std;

typedef struct _date{
	int year, month, day;
}Date;

typedef struct _rsrcs{
	Member* Mem;
	string Rsrcname;
	struct _rsrcs* next;
	Date* dueDate;
	char state;
}Rsrcs;

class Book{
	private:
		Rsrcs* header;
	protected:
		Book();
		~Book();
		void setBook(string src);
		Date* getBookdueDate(string src);
		int IsExisted(string src);
		int IsOverlap(string name, string src);
		int setBorrowBook(string src, string memname, string memtype, Date* borrowdate);
		int getBorrowBook(string src, string memname, string memtype, Date* borrowdate);
		int setReturnBook(string src, string memname, string memtype, Date* returndate);
		int getReturnBook(string src, string memname, string memtype, Date* returndate);
};

class Resource: public Book{
	public:
		Resource();
		~Resource();
		void setResrc();
		int findResrc(string src, string type);
		int findOverlap(string memname, string srcname, string srctype, char state);
		int searchResrc(string src, string type, string memname, string memtype, Date* strdate, char stat);
		int confirmResrc(string src, string type, string memname, string memtype, Date* strdate, char stat);
		Date* getdueDate(string src, string type);
};

int CompareDate(Date* srcDate, Date* dueDate);
