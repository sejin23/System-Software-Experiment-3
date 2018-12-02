#include <string>
using namespace std;

class Space{
    protected:
        string username;    //빌린 사람 정보
        int emptytime[4];   //자리비운 시간
        int returntime[4];  //반납 시간 년,월,일,시
        char state; //현재 상태
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