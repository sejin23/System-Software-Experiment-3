#include <string>
using namespace std;

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