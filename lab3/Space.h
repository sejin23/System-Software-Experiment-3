#include <string>
using namespace std;

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