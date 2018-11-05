# System Software Experiment 3 Report

*student Id* : 2014313299 <br />
*student Name* : Park Sejin

### functions
- Main function
- Library function
    - Member function
    - Resource function

### How to build or clean Library App?
- Use `make` command to build the file.
- Use `make clean` command to clean your object file.

- `./lib` command can make output in `output.dat`

> **Main function :**
>    + main.cpp 파일의 입력은 `input.dat` 파일로 생성되고, 이에 대한 출력은 `output.dat` 파일에 저장됩니다.
>    + 이 함수는 Library 객체를 생성해서 member들과 resource들의 정보를 생성 및 불러오게 됩니다.

> **Library function :**
>    + Library.h code
```C++
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
```
    + Library.cpp에서는 Member class를 Linked List 형태로 생성하고 Resource class는 constructor에서만 새로 생성한다.
    + setLib 함수가 현재 도서관에 대출 또는 반납 시 결과에 대한 op code를 반환해주는 함수이다.

> **Member function :**
>    + Member.h code
```C++
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
```
>    + Member.cpp에서는 Linked List에서 사용할 각각의 사람들에 대한 책을 빌린 정보, 빌릴 수 있는 책의 제한 개수 등을 실행한다.

> **Resource function :**
>    + Resource.h code
```C++
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
```
>    + Resource.cpp에서는 각 Resource의 정보와 이 Resource를 대출한 사람의 정보를 나타내는 함수들에 대한 구현이 되어 있다.

#### Inheritance Structure
    - Library는 전체 resource를 가지고 있는 Resource를 생성하고, Resource를 빌리거나 반납할 때에만 생성되고 삭제되는 Member 변수를 사용한다.
    - Member class는  Undergraduate class를 상속한 후 빌릴 수 있는 권수를 저장한다.
    - Resource class는 Book class를 상속한 후 내부 Linked List에서 이 Resource를 빌리게 되면 Member class를 생성해 저장하고 있는 구조이다.