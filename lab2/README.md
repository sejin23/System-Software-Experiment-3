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
typedef struct _restrict{
    Undergraduate* und;
    struct _restrict* next;
}rsted;
class Library{
    private:
        int floor_m, room_m, room_status, seat_m, rsc_m;
        int* seat_status;
        Study_Room** str;
        Seat*** set;
        rsted* rstd_mem;
        Book** book;
    public:
        Library(int fl, int room_n, int seat_n);
        ~Library();
        void exeReserve(int* d, string sp_type, int sp_n, char op, string mem_name, string mem_type, int mem_n, int rsv_time);
        int validID(string sp_type, int sp_n);
        int executable(int* d, int rsv_time, string sp_type, int fl);
        int borrowed(string mem_name, string sp_type, char op, int* d);
        int execmem(string sp_type, int mem_n);
        int exectime(string sp_type, string mem_name, int* d, char op, int rsv_time);
        int fullspace(string sp_type, char op, int sp_n, int* d);
        int searchRsc(string src_name);
        int execresrc(string mem_name, string mem_type, char op, int* d);
        int isBorrowed(string mem_name, string mem_type, string rsc_type, string rsc_name, char op);
        int* borroweddate(string mem_name, string mem_type, string rsc_name, string rsc_type);
        int isDelayedMem(string mem_name, string mem_type, char op, int* d);
        int* delayeddate(string mem_name, string mem_type);
        int setBorrow(string mem_name, string mem_type, string rsc_name, string rsc_type, char op, int* d);
};
```
+ main 함수에서 각 *op_code*에 맞춰 각 조건을 확인할 수 있도록 Library의 함수를 불러온다.
+ StudyRoom, Seat은 고정된 자리로 배정하고, book도 고정된 개수만큼 입력을 받아 그 안에서 처리한다. 그리고 restrict member는 Linked List로 추가하여 member를 확인할 수 있다.

> **Space function :**
>   + `Space.h`
```C++
class Space{
    protected:
        string user_name;
        char state;
        int rsv_time;
        int date[4];
};
class Study_Room: public Space{
    private:
        int personnel;
    public:
        Study_Room();
        string getusrname();
        int validate(int* d, char op);
        void setResrv(string name, int time, int resv_n, int* d);
        void setstate(char op);
        int getrsvtime();
        int* getstartdate();
};
class Seat: public Space{
    private:
        int floor;
    public:
        Seat();
        string getusrname();
        int validate(int* d, char op);
        void borrResrv(string mem_name, int* d, int t, int fl);
        void emtResrv();
        void cmbResrv();
        int getrsvtime();
        int* getstartdate();
};
```
+ studyroom 과 seat은 space를 상속받아 각각의 공간을 할당받고 반납해주는 처리를 한다.
+ studyroom은 총 10개의 공간이 있고 각 공간은 최대 6명의 사람이 사용할 수 있다.
+ seat은 3개의 층, 각 층에 50개의 좌석이 있고 한 명당 1개의 좌석을 사용할 수 있다.

*Resource와 Member에 대한 내용은 lab1에 존재한다.*

### Inheritance Structure ###
- Library에 각 Resource, Space, Member들을 가리키는 포인터가 저장되어 있다.
- Resource는 Book에게 상속되어 book class를 이용되고, Member도 Undergraduate에게 상속되어 undergraduate class를 이용된다.
- Space는 StudyRoom과 Seat에게 상속되어 각 space type에 맞게 class를 사용된다.