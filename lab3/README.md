## SSE3 lab2

*student ID* : 2014313299 <br/>
*student Name* : Park Sejin <br/>

functions
+ Main
+ Library
    + Member
    + Resource
    + Space

### How to build or clean Library?
+ Use `make` command to build the file.
+ Use `make clean` command to clean object file.
+ `./lib` command can make output in output.dat

> **Main function :**
>   + main.cpp 파일에서는 두 번에 걸쳐 파일 입력 `input.dat`과 `space.dat` 파일에서 입력을 받고 두 번의 `while` 문을 통해 *op_code* 순서에 따라 결과 값을 `output.dat`에 저장합니다.

> **Library function :**
>   + `Library.h`
```C++
class Library{
    private:
        int floor_m, room_m, room_state, seat_m;
        int* seat_status;
        Study_Room** str;
        Seat*** set;
        vector<Book> book;
        vector<Magazine> mgz;
        vector<E_book> ebook;
        vector<Undergraduate> und;
        vector<Graduate> grd;
        vector<Faculty> fac;
    public:
        Library(int fl, int room_n, int seat_n);
        ~Library();
        void BorrowResource(int opn, int* nowdate, string rsc_type, string rsc_name, string mem_type, string mem_name, char op);
        void BorrowSpace(int opn, int* nowdate, string sp_type, int sp_num, string mem_type, string mem_name, char op, int num_mem, int rsv_time);
};
```
+ main 함수에서 input.dat과 space.dat의 날짜 중 먼저 들어온 요청을 처리한다.
+ StudyRoom, Seat은 고정된 자리로 배정하고, 나머지 Resource들과 Member들은 resource.dat과 들어오는 요청들에 따라 동적으로 생성한다.

> **Space function :**
>   + `Space.h`
```C++
class Space{
    protected:
        string username;
        int emptytime[4];
        int returntime[4];
        char state;
        Space();
    public:
        string getusername();
        char getstate();
        void setuserborrow(string mem_name, int* nowdate, int rsvtime);
        void setuserreturn();
        void setempty(int* d);
        void setstate();
        int isavailable(int* d);
        int getremaintime(int* d);
};
class Study_Room: public Space{
    public:
        Study_Room();
};
class Seat: public Space{
    public:
        Seat();
};
```
+ studyroom 과 seat은 space를 상속받아 각각의 공간을 할당받고 반납해주는 처리를 한다.
+ studyroom은 총 10개의 공간이 있고 각 공간은 최대 6명의 사람이 사용할 수 있다.
+ seat은 3개의 층, 각 층에 50개의 좌석이 있고 한 명당 1개의 좌석을 사용할 수 있다.

> **Member function :**
>   + `Member.h`
```C++
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
```
+ 추가된 두 개의 멤버 Graduate와 Faculty는 단지 빌릴 수 있는 책의 권 수, 기간 등만 Undergraduate와 다를 뿐 역할은 똑같다.

> **Resource function :**
>   + `Resource.h`
```C++
class Resource{
	protected:
		string srcname;
		string usrname;
		char state;
		int brwdate[3];
		int retdate[3];
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
```
+ 추가된 두 개의 Resource는 Book과 완전히 다른 역할은 한다.
+ Magazine의 경우 같은 이름의 Resource를 빌리려 해도 다른 달의 잡지이면 다른 잡지로 인식해 빌릴 수 있도록 만들었다.
+ E-book은 어느 한 명이 사용한다 해도 다른 사람들이 이용할 수 있고 기간이 지나면 자동으로 본인의 저장 공간에서 없어지게 된다.

### Inheritance Structure ###
- Library에 각 Resource, Space, Member들을 가리키는 포인터가 저장되어 있다.
- Resource는 Book, Magazine, E-book에게 상속되어 사용되고, Member도 Undergraduate, Graduate, Faculty에게 상속되어 사용된다.
- Space는 StudyRoom과 Seat에게 상속되어 각 space type에 맞게 class를 사용된다.