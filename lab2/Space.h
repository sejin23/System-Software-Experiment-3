#include <string>
using namespace std;
class Space{
    protected:
        string user_name;
        char state;
        int rsv_time;
        int date[4];
        virtual int validate(int* d, char op);
};

class Study_Room: public Space{
    private:
        int personnel;
    public:
        Study_Room();
        ~Study_Room();
        string getusrname();
        int validate(int* d, char op);
        void setResrv(string name, int time, int resv_n, int* d);

};

class Seat: public Space{
    private:
        int floor;
    public:
        Seat();
        ~Seat();
        string getusrname();
        int validate(int* d, char op);
};