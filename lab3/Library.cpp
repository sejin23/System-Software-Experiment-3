#include <fstream>
#include <iostream>
#include <sstream>
#include "Library.h"
using namespace std;
int namewithnumbers(string name){
    int i;
    for(i=0;i<name.length();i++){
        if(name.at(i) >= '0' && name.at(i) <= '9') return 1;
    }
    return 0;
}

int cmpdate(int* in, int* sp){
    if(in[0] != sp[0]%100){
        if(in[0] > sp[0]%100) return 2;
        else return 1;
    }
    if(in[1] != sp[1]){
        if(in[1] > sp[1]) return 2;
        else return 1;
    }
    if(in[2] != sp[2]){
        if(in[2] > sp[2]) return 2;
        else return 1;
    }
    return 1;
}

int mgzcmp(string src, int* date){
    string year = src.substr(1, 2), month = src.substr(4, 5);
    int yy, mm;
    stringstream sy(year);
    stringstream sm(month);
    sy >> yy;
    sm >> mm;
    if(yy > date[0] || yy < date[0] - 1) return 0;
    if(yy == date[0] - 1){
        if(mm < date[1]) return 0;
        else return 1;
    }
    if(yy == date[0]){
        if(mm > date[1]) return 0;
        else return 1;
    }
    return 1;
}

Library::Library(int fl, int room_n, int seat_n){
    int i, j, k;
    string rsrcType, rsrcName, Name, cap;
    string sp_type, mem_type, mem_name;
    string rsc_type, rsc_name, inmem_type, inmem_name;
    char op, inop, sl;
    int sp_num, num_of_mem, rsv_time, inbreak, spbreak;
    int* date = new int[4];
    int* indate = new int[3];
    floor_m = fl;
    room_m = room_n;
    seat_m = seat_n;
    ifstream fre("resource.dat");
    ofstream fout("output.dat");
    fout << "Op_#\tReturn_code\tDescription";
    fre >> rsrcType >> rsrcName;
    while(1){
        fre >> rsrcType >> rsrcName;
        if(fre.eof()) break;
        if(!rsrcType.compare("Book")){
            Book temp(rsrcName);
            book.push_back(temp);
        }else if(!rsrcType.compare("Magazine")){
            Magazine temp(rsrcName);
            mgz.push_back(temp);
        }else if(!rsrcType.compare("E-book")){
            Name = rsrcName.substr(0, rsrcName.find('['));
            cap = rsrcName.substr(rsrcName.find('[')+1, rsrcName.find(']'));
            stringstream ss(cap);
            ss >> i;
            E_book temp(Name, i);
            ebook.push_back(temp);
        }
    }
    fre.close();
    fout.close();
    str = new Study_Room*[room_n];
    for(i=0;i<room_n;i++) str[i] = new Study_Room();
    set = new Seat**[fl];
    for(i=0;i<fl;i++){
        set[i] = new Seat*[seat_n];
        for(j=0;j<seat_n;j++) set[i][j] = new Seat();
    }
    seat_status = new int[fl];
    for(i=0;i<fl;i++) seat_status[i] = 0;
    room_state = 0;
    i = 1;
    k = 0;
    inbreak = 0;
    spbreak = 0;
    ifstream fin("input.dat");
    ifstream fsp("space.dat");
    getline(fin, sp_type);
    getline(fsp, sp_type);
    while(1){
        if(k == 0){
            fin >> indate[0] >> sl >> indate[1] >> sl >> indate[2];
            fin >> rsc_type >> rsc_name >> inop >> inmem_type >> inmem_name;
            fsp >> date[0] >> sl >> date[1] >> sl >> date[2] >> sl >> date[3];
            fsp >> sp_type >> sp_num >> op >> mem_type >> mem_name;
            if(op == 'B') fsp >> num_of_mem >> rsv_time;
        }else if(k == 1){
            fin >> indate[0] >> sl >> indate[1] >> sl >> indate[2];
            if(fin.eof()) inbreak = 1;
            fin >> rsc_type >> rsc_name >> inop >> inmem_type >> inmem_name;
        }else{
            fsp >> date[0] >> sl >> date[1] >> sl >> date[2] >> sl >> date[3];
            if(fsp.eof()) spbreak = 1;
            fsp >> sp_type >> sp_num >> op >> mem_type >> mem_name;
            if(op == 'B') fsp >> num_of_mem >> rsv_time;
        }
        if(!inbreak && !spbreak)
            k = cmpdate(indate, date);
        else if(inbreak && spbreak)
            break;
        else{
            if(inbreak) k = 2;
            else if(spbreak) k = 1;
        }
        try{
            if(k == 1) BorrowResource(i, indate, rsc_type, rsc_name, inmem_type, inmem_name, inop);
            else if(k == 2) BorrowSpace(i, date, sp_type, sp_num, mem_type, mem_name, op, num_of_mem, rsv_time);
        }catch(int err){
            ofstream fout;
            fout.open("output.dat", ios_base::out | ios_base::app);
            fout << endl << i << "\t-1\t";
            if(err == 1) fout << "Date out of range.";
            else if(err == 2) fout << "Non-exist space type.";
            else if(err == 3) fout << "Non-exist operation.";
            else if(err == 4) fout << "Non-exist member type.";
            else if(err == 5) fout << "Member name with numbers.";
            else if(err == 6) fout << "Nagative.";
            fout.close();
        }
        i++;
    }
    fin.close();
    fsp.close();
    delete[] indate;
    delete[] date;
}

Library::~Library(){
    int i, j;
    delete seat_status;
    for(i=0;i<room_m;i++) delete str[i];
    delete[] str;
    for(i=0;i<floor_m;i++){
        for(j=0;j<seat_m;j++) delete set[i][j];
    }
    for(i=0;i<floor_m;i++) delete[] set[i];
    delete[] set;
}

void Library::BorrowResource(int opn, int* nowdate, string rsc_type, string rsc_name, string mem_type, string mem_name, char op){
    int i, temp, isdelay = 0;
    int* date;
    int* delaydate;
    string name, month;
    ofstream fout;
    fout.open("output.dat", ios_base::out | ios_base::app);
    if(nowdate[0] < 10) throw 1;
    if(mem_type.compare("Undergraduate") && mem_type.compare("Graduate") && mem_type.compare("Faculty")) throw 4;
    if(namewithnumbers(mem_name)) throw 5;
    if(op == 'B'){
        if(!rsc_type.compare("Book")){
            vector<Book>::iterator iter;
            for(iter=book.begin();iter!=book.end();++iter){
                if(!rsc_name.compare(iter->getsrcname())){
                    if(!mem_type.compare("Undergraduate")){
                        vector<Undergraduate>::iterator mter;
                        for(mter=und.begin();mter!=und.end();++mter){
                            if(!mem_name.compare(mter->getusername())){
                                if((temp = mter->notborrowmore()) > 0){    //return code 2
                                    fout << endl << opn << "\t2\tExceeds your possible number of borrow. Possible # of borrows: " << temp;
                                    return;
                                }
                                if(mter->isdelayedMem(nowdate)){
                                    isdelay = 1;
                                    delaydate = mter->getdelayeddate();
                                }
                                break;
                            }
                        }
                        if(mter == und.end()){
                            Undergraduate mem(mem_name);
                            und.push_back(mem);
                        }
                    }else if(!mem_type.compare("Graduate")){
                        vector<Graduate>::iterator mter;
                        for(mter=grd.begin();mter!=grd.end();++mter){
                            if(!mem_name.compare(mter->getusername())){
                                if((temp = mter->notborrowmore()) > 0){    //return code 2
                                    fout << endl << opn << "\t2\tExceeds your possible number of borrow. Possible # of borrows: " << temp;
                                    return;
                                }
                                if(mter->isdelayedMem(nowdate)){
                                    isdelay = 1;
                                    delaydate = mter->getdelayeddate();
                                }
                                break;
                            }
                        }
                        if(mter == grd.end()){
                            Graduate mem(mem_name);
                            grd.push_back(mem);
                        }
                    }else if(!mem_type.compare("Faculty")){
                        vector<Faculty>::iterator mter;
                        for(mter=fac.begin();mter!=fac.end();++mter){
                            if(!mem_name.compare(mter->getusername())){
                                if((temp = mter->notborrowmore()) > 0){    //return code 2
                                    fout << endl << opn << "\t2\tExceeds your possible number of borrow. Possible # of borrows: " << temp;
                                    return;
                                }
                                if(mter->isdelayedMem(nowdate)){
                                    isdelay = 1;
                                    delaydate = mter->getdelayeddate();
                                }
                                break;
                            }
                        }
                        if(mter == fac.end()){
                            Faculty mem(mem_name);
                            fac.push_back(mem);
                        }
                    }
                    if(iter->isborrowed()){ //이미 빌려간 자료
                        if(!mem_name.compare(iter->getusrname())){  //return code 4
                            fout << endl << opn << "\t4\tYou already borrowed this book at ";
                            date = iter->getborroweddate();
                            if(date[0] < 10) fout << 0;
                            fout << date[0] << "/";
                            if(date[1] < 10) fout << 0;
                            fout << date[1] << "/";
                            if(date[2] < 10) fout << 0;
                            fout << date[2];
                            delete[] date;
                            return;
                        }else{
                            fout << endl << opn << "\t5\tOther member already borrowed this book. This book will be returned at ";
                            date = iter->getreturndate();
                            if(date[0] < 10) fout << 0;
                            fout << date[0] << "/";
                            if(date[1] < 10) fout << 0;
                            fout << date[1] << "/";
                            if(date[2] < 10) fout << 0;
                            fout << date[2];
                            delete[] date;
                            return;
                        }
                    }
                    if(isdelay == 1){    //return code 6
                        if(!mem_type.compare("Undergraduate")){
                            fout << endl << opn << "\t6\tRestricted Member until ";
                            if(delaydate[0] < 10) fout << 0;
                            fout << delaydate[0] << "/";
                            if(delaydate[1] < 10) fout << 0;
                            fout << delaydate[1] << "/";
                            if(delaydate[2] < 10) fout << 0;
                            fout << delaydate[2];
                        }else
                            fout << endl << opn << "\t16\tPreviously borrowed books are overdue, so borrow is limited.";
                        delete[] delaydate;
                        return;
                    }
                    iter->setBorrow(mem_name, mem_type, nowdate);
                    if(!mem_type.compare("Undergraduate")){
                        vector<Undergraduate>::iterator mter;
                        for(mter=und.begin();mter!=und.end();++mter){
                            if(!mem_name.compare(mter->getusername())) mter->setborrow();
                        }
                    }else if(!mem_type.compare("Graduate")){
                        vector<Graduate>::iterator mter;
                        for(mter=grd.begin();mter!=grd.end();++mter){
                            if(!mem_name.compare(mter->getusername())) mter->setborrow();
                        }
                    }else if(!mem_type.compare("Faculty")){
                        vector<Faculty>::iterator mter;
                        for(mter=fac.begin();mter!=fac.end();++mter){
                            if(!mem_name.compare(mter->getusername())) mter->setborrow();
                        }
                    }
                    fout << endl << opn << "\t0\tSuccess.";
                    return;
                }
            }
            if(iter == book.end()){     //return code 1
                fout << endl << opn << "\t1\tNon exist resource.";
                return;
            }
        }else if(!rsc_type.compare("Magazine")){
            name = rsc_name.substr(0, rsc_name.find('['));
            month = rsc_name.substr(rsc_name.find('['));
            vector<Magazine>::iterator iter;
            for(iter=mgz.begin();iter!=mgz.end();++iter){
                if(!name.compare(iter->getsrcname())){
                    if(!mgzcmp(month, nowdate)){
                        fout << endl << opn << "\t1\tNon exist resource.";
                        return;
                    }
                    if(!mem_type.compare("Undergraduate")){
                        vector<Undergraduate>::iterator mter;
                        for(mter=und.begin();mter!=und.end();++mter){
                            if(!mem_name.compare(mter->getusername())){
                                if((temp = mter->notborrowmore()) > 0){    //return code 2
                                    fout << endl << opn << "\t2\tExceeds your possible number of borrow. Possible # of borrows: " << temp;
                                    return;
                                }
                                if(mter->isdelayedMem(nowdate)){
                                    isdelay = 1;
                                    delaydate = mter->getdelayeddate();
                                }
                                break;
                            }
                        }
                        if(mter == und.end()){
                            Undergraduate mem(mem_name);
                            und.push_back(mem);
                        }
                    }else if(!mem_type.compare("Graduate")){
                        vector<Graduate>::iterator mter;
                        for(mter=grd.begin();mter!=grd.end();++mter){
                            if(!mem_name.compare(mter->getusername())){
                                if((temp = mter->notborrowmore()) > 0){    //return code 2
                                    fout << endl << opn << "\t2\tExceeds your possible number of borrow. Possible # of borrows: " << temp;
                                    return;
                                }
                                if(mter->isdelayedMem(nowdate)){
                                    isdelay = 1;
                                    delaydate = mter->getdelayeddate();
                                }
                                break;
                            }
                        }
                        if(mter == grd.end()){
                            Graduate mem(mem_name);
                            grd.push_back(mem);
                        }
                    }else if(!mem_type.compare("Faculty")){
                        vector<Faculty>::iterator mter;
                        for(mter=fac.begin();mter!=fac.end();++mter){
                            if(!mem_name.compare(mter->getusername())){
                                if((temp = mter->notborrowmore()) > 0){    //return code 2
                                    fout << endl << opn << "\t2\tExceeds your possible number of borrow. Possible # of borrows: " << temp;
                                    return;
                                }
                                if(mter->isdelayedMem(nowdate)){
                                    isdelay = 1;
                                    delaydate = mter->getdelayeddate();
                                }
                                break;
                            }
                        }
                        if(mter == fac.end()){
                            Faculty mem(mem_name);
                            fac.push_back(mem);
                        }
                    }
                    if(iter->isborrowedmgz(month)){ //이미 빌려간 자료
                        if(!mem_name.compare(iter->getmgzusrname(month))){  //return code 4
                            fout << endl << opn << "\t4\tYou already borrowed this book at ";
                            date = iter->getmgzborroweddate(month);
                            if(date[0] < 10) fout << 0;
                            fout << date[0] << "/";
                            if(date[1] < 10) fout << 0;
                            fout << date[1] << "/";
                            if(date[2] < 10) fout << 0;
                            fout << date[2];
                            delete[] date;
                            return;
                        }else{
                            fout << endl << opn << "\t5\tOther member already borrowed this book. This book will be returned at ";
                            date = iter->getmgzreturndate(month);
                            if(date[0] < 10) fout << 0;
                            fout << date[0] << "/";
                            if(date[1] < 10) fout << 0;
                            fout << date[1] << "/";
                            if(date[2] < 10) fout << 0;
                            fout << date[2];
                            delete[] date;
                            return;
                        }
                    }
                    if(isdelay == 1){    //return code 6
                        if(!mem_type.compare("Undergraduate")){
                            fout << endl << opn << "\t6\tRestricted Member until ";
                            if(delaydate[0] < 10) fout << 0;
                            fout << delaydate[0] << "/";
                            if(delaydate[1] < 10) fout << 0;
                            fout << delaydate[1] << "/";
                            if(delaydate[2] < 10) fout << 0;
                            fout << delaydate[2];
                        }else
                            fout << endl << opn << "\t16\tPreviously borrowed books are overdue, so borrow is limited.";
                        delete[] delaydate;
                        return;
                    }
                    iter->setMgzBorrow(mem_name, mem_type, month, nowdate);
                    if(!mem_type.compare("Undergraduate")){
                        vector<Undergraduate>::iterator mter;
                        for(mter=und.begin();mter!=und.end();++mter){
                            if(!mem_name.compare(mter->getusername())) mter->setborrow();
                        }
                    }else if(!mem_type.compare("Graduate")){
                        vector<Graduate>::iterator mter;
                        for(mter=grd.begin();mter!=grd.end();++mter){
                            if(!mem_name.compare(mter->getusername())) mter->setborrow();
                        }
                    }else if(!mem_type.compare("Faculty")){
                        vector<Faculty>::iterator mter;
                        for(mter=fac.begin();mter!=fac.end();++mter){
                            if(!mem_name.compare(mter->getusername())) mter->setborrow();
                        }
                    }
                    fout << endl << opn << "\t0\tSuccess.";
                    return;
                }
            }
            if(iter == mgz.end()){      //return code 1
                fout << endl << opn << "\t1\tNon exist resource.";
                return;
            }
        }else if(!rsc_type.compare("E-book")){
            vector<E_book>::iterator iter;
            for(iter=ebook.begin();iter!=ebook.end();++iter){
                if(!rsc_name.compare(iter->getsrcname())){
                    temp = iter->getcapacity();
                    if(!mem_type.compare("Undergraduate")){
                        vector<Undergraduate>::iterator mter;
                        for(mter=und.begin();mter!=und.end();++mter){
                            if(!mem_name.compare(mter->getusername())){
                                if(mter->checkEbook(rsc_name, nowdate)){
                                    fout << endl << opn << "\t4\tYou already borrowed this book at ";
                                    date = iter->getborroweddate();
                                    if(date[0] < 10) fout << 0;
                                    fout << date[0] << "/";
                                    if(date[1] < 10) fout << 0;
                                    fout << date[1] << "/";
                                    if(date[2] < 10) fout << 0;
                                    fout << date[2];
                                    delete[] date;
                                    return;
                                }
                                if(mter->isdelayedMem(nowdate)){
                                    isdelay = 1;
                                    delaydate = mter->getdelayeddate();
                                    fout << endl << opn << "\t6\tRestricted Member until ";
                                    if(delaydate[0] < 10) fout << 0;
                                    fout << delaydate[0] << "/";
                                    if(delaydate[1] < 10) fout << 0;
                                    fout << delaydate[1] << "/";
                                    if(delaydate[2] < 10) fout << 0;
                                    fout << delaydate[2];
                                    delete[] delaydate;
                                    return;
                                }
                                if(!mter->canmoreEbook(temp, rsc_name, mem_type, nowdate)){
                                    fout << endl << opn << "\t15\tExceeds your storage capacity.";
                                    return;
                                }else{
                                    fout << endl << opn << "\t0\tSuccess.";
                                    return;
                                }
                            }
                        }
                        if(mter == und.end()){
                            Undergraduate mem(mem_name);
                            if(!mem.canmoreEbook(temp, rsc_name, mem_type, nowdate))
                                fout << endl << opn << "\t15\tExceeds your storage capacity.";
                            else fout << endl << opn << "\t0\tSuccess.";
                            und.push_back(mem);
                            return;
                        }
                    }else if(!mem_type.compare("Graduate")){
                        vector<Graduate>::iterator mter;
                        for(mter=grd.begin();mter!=grd.end();++mter){
                            if(!mem_name.compare(mter->getusername())){
                                if(mter->checkEbook(rsc_name, nowdate)){
                                    fout << endl << opn << "\t4\tYou already borrowed this book at ";
                                    date = iter->getborroweddate();
                                    if(date[0] < 10) fout << 0;
                                    fout << date[0] << "/";
                                    if(date[1] < 10) fout << 0;
                                    fout << date[1] << "/";
                                    if(date[2] < 10) fout << 0;
                                    fout << date[2];
                                    delete[] date;
                                    return;
                                }
                                if(mter->isdelayedMem(nowdate)){
                                    isdelay = 1;
                                    delaydate = mter->getdelayeddate();
                                    fout << endl << opn << "\t6\tRestricted Member until ";
                                    if(delaydate[0] < 10) fout << 0;
                                    fout << delaydate[0] << "/";
                                    if(delaydate[1] < 10) fout << 0;
                                    fout << delaydate[1] << "/";
                                    if(delaydate[2] < 10) fout << 0;
                                    fout << delaydate[2];
                                    delete[] delaydate;
                                    return;
                                }
                                if(!mter->canmoreEbook(temp, rsc_name, mem_type, nowdate)){
                                    fout << endl << opn << "\t15\tExceeds your storage capacity.";
                                    return;
                                }else{
                                    fout << endl << opn << "\t0\tSuccess.";
                                    return;
                                }
                            }
                        }
                        if(mter == grd.end()){
                            Graduate mem(mem_name);
                            if(!mem.canmoreEbook(temp, rsc_name, mem_type, nowdate))
                                fout << endl << opn << "\t15\tExceeds your storage capacity.";
                            else fout << endl << opn << "\t0\tSuccess.";
                            grd.push_back(mem);
                            return;
                        }
                    }else if(!mem_type.compare("Faculty")){
                        vector<Faculty>::iterator mter;
                        for(mter=fac.begin();mter!=fac.end();++mter){
                            if(!mem_name.compare(mter->getusername())){
                                if(mter->checkEbook(rsc_name, nowdate)){
                                    fout << endl << opn << "\t4\tYou already borrowed this book at ";
                                    date = iter->getborroweddate();
                                    if(date[0] < 10) fout << 0;
                                    fout << date[0] << "/";
                                    if(date[1] < 10) fout << 0;
                                    fout << date[1] << "/";
                                    if(date[2] < 10) fout << 0;
                                    fout << date[2];
                                    delete[] date;
                                    return;
                                }
                                if(mter->isdelayedMem(nowdate)){
                                    isdelay = 1;
                                    delaydate = mter->getdelayeddate();
                                    fout << endl << opn << "\t6\tRestricted Member until ";
                                    if(delaydate[0] < 10) fout << 0;
                                    fout << delaydate[0] << "/";
                                    if(delaydate[1] < 10) fout << 0;
                                    fout << delaydate[1] << "/";
                                    if(delaydate[2] < 10) fout << 0;
                                    fout << delaydate[2];
                                    delete[] delaydate;
                                    return;
                                }
                                if(!mter->canmoreEbook(temp, rsc_name, mem_type, nowdate)){
                                    fout << endl << opn << "\t15\tExceeds your storage capacity.";
                                    return;
                                }else{
                                    fout << endl << opn << "\t0\tSuccess.";
                                    return;
                                }
                            }
                        }
                        if(mter == fac.end()){
                            Faculty mem(mem_name);
                            if(!mem.canmoreEbook(temp, rsc_name, mem_type, nowdate))
                                fout << endl << opn << "\t15\tExceeds your storage capacity.";
                            else fout << endl << opn << "\t0\tSuccess.";
                            fac.push_back(mem);
                            return;
                        }
                    }
                }
            }
            if(iter == ebook.end()){    //return code 1
                fout << endl << opn << "\t1\tNon exist resource.";
                return;
            }
        }
    }else if(op == 'R'){
        if(!rsc_type.compare("Book")){
            vector<Book>::iterator iter;
            for(iter=book.begin();iter!=book.end();++iter){
                if(!rsc_name.compare(iter->getsrcname())){
                    if(!iter->isborrowed()){
                        fout << endl << opn << "\t3\tYou did not borrow this book.";
                        return;
                    }else{
                        if(mem_name.compare(iter->getusrname())){
                            fout << endl << opn << "\t3\tYou did not borrow this book.";
                            return;
                        }else{
                            temp = iter->returnresrc(nowdate);
                            if(!mem_type.compare("Undergraduate")){
                                vector<Undergraduate>::iterator mter;
                                for(mter=und.begin();mter!=und.end();++mter){
                                    if(!mem_name.compare(mter->getusername())){
                                        if(temp == 1){
                                            mter->setreturn();
                                            fout << endl << opn << "\t0\tSuccess.";
                                            return;
                                        }else{
                                            delaydate = iter->getreturndate();
                                            date = mter->setdelayreturn(delaydate, nowdate);
                                            fout << endl << opn << "\t7\tDelayed return. You'll be restricted until ";
                                            if(date[0] < 10) fout << 0;
                                            fout << date[0] << "/";
                                            if(date[1] < 10) fout << 0;
                                            fout << date[1] << "/";
                                            if(date[2] < 10) fout << 0;
                                            fout << date[2];
                                            delete[] date;
                                            return;
                                        }
                                    }
                                }
                            }else if(!mem_type.compare("Graduate")){
                                vector<Graduate>::iterator mter;
                                for(mter=grd.begin();mter!=grd.end();++mter){
                                    if(!mem_name.compare(mter->getusername())){
                                        if(temp == 1){
                                            mter->setreturn();
                                            fout << endl << opn << "\t0\tSuccess.";
                                            return;
                                        }else{
                                            delaydate = iter->getreturndate();
                                            date = mter->setdelayreturn(delaydate, nowdate);
                                            fout << endl << opn << "\t7\tDelayed return. You'll be restricted until ";
                                            if(date[0] < 10) fout << 0;
                                            fout << date[0] << "/";
                                            if(date[1] < 10) fout << 0;
                                            fout << date[1] << "/";
                                            if(date[2] < 10) fout << 0;
                                            fout << date[2];
                                            delete[] date;
                                            return;
                                        }
                                    }
                                }
                            }else if(!mem_type.compare("Faculty")){
                                vector<Faculty>::iterator mter;
                                for(mter=fac.begin();mter!=fac.end();++mter){
                                    if(!mem_name.compare(mter->getusername())){
                                        if(temp == 1){
                                            mter->setreturn();
                                            fout << endl << opn << "\t0\tSuccess.";
                                            return;
                                        }else{
                                            delaydate = iter->getreturndate();
                                            date = mter->setdelayreturn(delaydate, nowdate);
                                            fout << endl << opn << "\t7\tDelayed return. You'll be restricted until ";
                                            if(date[0] < 10) fout << 0;
                                            fout << date[0] << "/";
                                            if(date[1] < 10) fout << 0;
                                            fout << date[1] << "/";
                                            if(date[2] < 10) fout << 0;
                                            fout << date[2];
                                            delete[] date;
                                            return;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if(iter == book.end()){
                fout << endl << opn << "\t1\tNon exist resource.";
                return;
            }
        }else if(!rsc_type.compare("Magazine")){
            name = rsc_name.substr(0, rsc_name.find('['));
            month = rsc_name.substr(rsc_name.find('['));
            vector<Magazine>::iterator iter;
            for(iter=mgz.begin();iter!=mgz.end();++iter){
                if(!name.compare(iter->getsrcname())){
                    if(!iter->isborrowedmgz(month)){
                        fout << endl << opn << "\t3\tYou did not borrow this book.";
                        return;
                    }else{
                        if(mem_name.compare(iter->getmgzusrname(month))){
                            fout << endl << opn << "\t3\tYou did not borrow this book.";
                            return;
                        }else{
                            temp = iter->returnMgzsrc(nowdate, month);
                            if(!mem_type.compare("Undergraduate")){
                                vector<Undergraduate>::iterator mter;
                                for(mter=und.begin();mter!=und.end();++mter){
                                    if(!mem_name.compare(mter->getusername())){
                                        if(temp == 1){
                                            mter->setreturn();
                                            fout << endl << opn << "\t0\tSuccess.";
                                            return;
                                        }else{
                                            delaydate = iter->getmgzreturndate(month);
                                            date = mter->setdelayreturn(delaydate, nowdate);
                                            fout << endl << opn << "\t7\tDelayed return. You'll be restricted until ";
                                            if(date[0] < 10) fout << 0;
                                            fout << date[0] << "/";
                                            if(date[1] < 10) fout << 0;
                                            fout << date[1] << "/";
                                            if(date[2] < 10) fout << 0;
                                            fout << date[2];
                                            delete[] date;
                                            return;
                                        }
                                    }
                                }
                                if(mter==und.end()){
                                    fout << endl << opn << "\t3\tYou did not borrow this book.";
                                    return;
                                }
                            }else if(!mem_type.compare("Graduate")){
                                vector<Graduate>::iterator mter;
                                for(mter=grd.begin();mter!=grd.end();++mter){
                                    if(!mem_name.compare(mter->getusername())){
                                        if(temp == 1){
                                            mter->setreturn();
                                            fout << endl << opn << "\t0\tSuccess.";
                                            return;
                                        }else{
                                            delaydate = iter->getmgzreturndate(month);
                                            date = mter->setdelayreturn(delaydate, nowdate);
                                            fout << endl << opn << "\t7\tDelayed return. You'll be restricted until ";
                                            if(date[0] < 10) fout << 0;
                                            fout << date[0] << "/";
                                            if(date[1] < 10) fout << 0;
                                            fout << date[1] << "/";
                                            if(date[2] < 10) fout << 0;
                                            fout << date[2];
                                            delete[] date;
                                            return;
                                        }
                                    }
                                }
                                if(mter==grd.end()){
                                    fout << endl << opn << "\t3\tYou did not borrow this book.";
                                    return;
                                }
                            }else if(!mem_type.compare("Faculty")){
                                vector<Faculty>::iterator mter;
                                for(mter=fac.begin();mter!=fac.end();++mter){
                                    if(!mem_name.compare(mter->getusername())){
                                        if(temp == 1){
                                            mter->setreturn();
                                            fout << endl << opn << "\t0\tSuccess.";
                                            return;
                                        }else{
                                            delaydate = iter->getmgzreturndate(month);
                                            date = mter->setdelayreturn(delaydate, nowdate);
                                            fout << endl << opn << "\t7\tDelayed return. You'll be restricted until ";
                                            if(date[0] < 10) fout << 0;
                                            fout << date[0] << "/";
                                            if(date[1] < 10) fout << 0;
                                            fout << date[1] << "/";
                                            if(date[2] < 10) fout << 0;
                                            fout << date[2];
                                            delete[] date;
                                            return;
                                        }
                                    }
                                }
                                if(mter==fac.end()){
                                    fout << endl << opn << "\t3\tYou did not borrow this book.";
                                    return;
                                }
                            }
                        }
                    }
                }
            }
            if(iter==mgz.end()){
                fout << endl << opn << "\t1\tNon exist resource.";
                return;
            }
        }else if(!rsc_type.compare("E-book")){
            vector<E_book>::iterator iter;
            for(iter=ebook.begin();iter!=ebook.end();++iter){
                if(!rsc_name.compare(iter->getsrcname())){
                    temp = iter->getcapacity();
                    if(!mem_type.compare("Undergraduate")){
                        vector<Undergraduate>::iterator mter;
                        for(mter=und.begin();mter!=und.end();++mter){
                            if(!mem_name.compare(mter->getusername())){
                                if(!mter->checkEbook(rsc_name, nowdate)){
                                    fout << endl << opn << "\t3\tYou did not borrow this book.";
                                    return;
                                }else{
                                    mter->deleteEbook(temp, rsc_name);
                                    fout << endl << opn << "\t0\tSuccess.";
                                    return;
                                }
                            }
                        }
                        if(mter==und.end()){
                            fout << endl << opn << "\t3\tYou did not borrow this book.";
                            return;
                        }
                    }else if(!mem_type.compare("Graduate")){
                        vector<Graduate>::iterator mter;
                        for(mter=grd.begin();mter!=grd.end();++mter){
                            if(!mem_name.compare(mter->getusername())){
                                if(!mter->checkEbook(rsc_name, nowdate)){
                                    fout << endl << opn << "\t3\tYou did not borrow this book.";
                                    return;
                                }else{
                                    mter->deleteEbook(temp, rsc_name);
                                    fout << endl << opn << "\t0\tSuccess.";
                                    return;
                                }
                            }
                        }
                        if(mter==grd.end()){
                            fout << endl << opn << "\t3\tYou did not borrow this book.";
                            return;
                        }
                    }else if(!mem_type.compare("Faculty")){
                        vector<Faculty>::iterator mter;
                        for(mter=fac.begin();mter!=fac.end();++mter){
                            if(!mem_name.compare(mter->getusername())){
                                if(!mter->checkEbook(rsc_name, nowdate)){
                                    fout << endl << opn << "\t3\tYou did not borrow this book.";
                                    return;
                                }else{
                                    mter->deleteEbook(temp, rsc_name);
                                    fout << endl << opn << "\t0\tSuccess.";
                                    return;
                                }
                            }
                        }
                        if(mter==fac.end()){
                            fout << endl << opn << "\t3\tYou did not borrow this book.";
                            return;
                        }
                    }
                    return;
                }
            }
        }
    }else throw 3;
    fout.close();
}

void Library::BorrowSpace(int opn, int* nowdate, string sp_type, int sp_num, string mem_type, string mem_name, char op, int num_mem, int rsv_time){
    int i, j, temp, min = 24;
    ofstream fout;
    fout.open("output.dat", ios_base::out | ios_base::app);
    if(nowdate[0] < 2010) throw 1;
    if(mem_type.compare("Undergraduate") && mem_type.compare("Graduate") && mem_type.compare("Faculty")) throw 4;
    if(namewithnumbers(mem_name)) throw 5;
    if(rsv_time < 0) throw 6;
    if(!sp_type.compare("StudyRoom")){
        if(sp_num < 1 || sp_num > room_m){
            fout << endl << opn << "\t8\tInvalid space id.";
            return;
        }
        if(nowdate[3] < 9 || nowdate[3] > 18){
            fout << endl << opn << "\t9\tThis space is not available now. Available from 09 from 18.";
            return;
        }
    }else if(!sp_type.compare("Seat")){
        if(sp_num < 1 || sp_num > floor_m){
            fout << endl << opn << "\t8\tInvalid space id.";
            return;
        }
        if(sp_num == 2){
            if(nowdate[3] < 9 || nowdate[3] > 21){
                fout << endl << opn << "\t9\tThis space is not available now. Available from 09 from 21.";
                return;
            }
        }else if(sp_num == 3){
            if(nowdate[3] < 9 || nowdate[3] > 18){
                fout << endl << opn << "\t9\tThis space is not available now. Available from 09 from 18.";
                return;
            }
        }
    }else throw 2;
    if(op == 'B'){
        if(!sp_type.compare("StudyRoom")){
            for(i=0;i<room_m;i++){
                if(str[i] != NULL){
                    if(!str[i]->isavailable(nowdate) && !mem_name.compare(str[i]->getusername())){
                        fout << endl << opn << "\t11\tYou already borrowed this kind of space.";
                        return;
                    }
                }
            }
            if(num_mem > 6){
                fout << endl << opn << "\t12\tExceed available number.";
                return;
            }
            if(rsv_time > 3){
                fout << endl << opn << "\t13\tExceed available time.";
                return;
            }
            if(!str[sp_num-1]->isavailable(nowdate)){
                fout << endl << opn << "\t14\tThere is no remain space. This space is available after ";
                temp = str[sp_num-1]->getremaintime(nowdate);
                fout << temp << ".";
                return;
            }else{
                str[sp_num-1]->setuserborrow(mem_name, nowdate, rsv_time);
                fout << endl << opn << "\t0\tSuccess.";
                return;
            }
        }else if(!sp_type.compare("Seat")){
            for(i=0;i<floor_m;i++){
                for(j=0;j<seat_m;j++){
                    if(!set[i][j]->isavailable(nowdate) && !mem_name.compare(set[i][j]->getusername())){
                        fout << endl << opn << "\t11\tYou already borrowed this kind of space.";
                        return;
                    }
                }
            }
            if(num_mem > 1){
                fout << endl << opn << "\t12\tExceed available number.";
                return;
            }
            if(rsv_time > 3){
                fout << endl << opn << "\t13\tExceed available time.";
                return;
            }
            for(i=0;i<seat_m;i++){
                if(set[sp_num-1][i]->isavailable(nowdate)){
                    set[sp_num-1][i]->setuserborrow(mem_name, nowdate, rsv_time);
                    fout << endl << opn << "\t0\tSuccess.";
                    return;
                }else{
                    temp = set[sp_num-1][i]->getremaintime(nowdate);
                    if(min > temp) min = temp;
                }
            }
            if(i == seat_m){
                fout << endl << opn << "\t14\tThere is no remain space. This space is available after " << min;
                return;
            }
        }
    }else if(op == 'R'){
        if(!sp_type.compare("StudyRoom")){
            if(str[sp_num-1]->isavailable(nowdate)){
                fout << endl << opn << "\t10\tYou did not borrow this place.";
                return;
            }else{
                if(mem_name.compare(str[sp_num-1]->getusername())){
                    fout << endl << opn << "\t10\tYou did not borrow this place.";
                    return;
                }else{
                    str[sp_num-1]->setuserreturn();
                    fout << endl << opn << "\t0\tSuccess.";
                    return;
                }
            }
        }else if(!sp_type.compare("Seat")){
            for(i=0;i<seat_m;i++){
                if(!set[sp_num-1][i]->isavailable(nowdate)){
                    if(!mem_name.compare(set[sp_num-1][i]->getusername())){
                        set[sp_num-1][i]->setuserreturn();
                        fout << endl << opn << "\t0\tSuccess.";
                        return;
                    }
                }
            }
            fout << endl << opn << "\t10\tYou did not borrow this place.";
            return;
        }
    }else if(op == 'E'){
        if(!sp_type.compare("StudyRoom")){
            if(!str[sp_num-1]->isavailable(nowdate)){
                if(!mem_name.compare(str[sp_num-1]->getusername())){
                    str[sp_num-1]->setempty(nowdate);
                    fout << endl << opn << "\t0\tSuccess.";
                    return;
                }
            }
            fout << endl << opn << "\t10\tYou did not borrow this place.";
            return;
        }else if(!sp_type.compare("Seat")){
            for(i=0;i<seat_m;i++){
                if(!set[sp_num-1][i]->isavailable(nowdate)){
                    if(!mem_name.compare(set[sp_num-1][i]->getusername())){
                        str[sp_num-1]->setempty(nowdate);
                        fout << endl << opn << "\t0\tSuccess.";
                        return;
                    }
                }
            }
            fout << endl << opn << "\t10\tYou did not borrow this place.";
            return;
        }
    }else if(op == 'C'){
        if(!sp_type.compare("StudyRoom")){
            if(!str[sp_num-1]->isavailable(nowdate)){
                if(!mem_name.compare(str[sp_num-1]->getusername())){
                    if(str[sp_num-1]->getstate() == 'E'){
                        str[sp_num-1]->setstate();
                        fout << endl << opn << "\t0\tSuccess.";
                        return;
                    }
                }
            }
            fout << endl << opn << "\t10\tYou did not borrow this place.";
            return;
        }else if(!sp_type.compare("Seat")){
            for(i=0;i<seat_m;i++){
                if(!set[sp_num-1][i]->isavailable(nowdate)){
                    if(!mem_name.compare(set[sp_num-1][i]->getusername())){
                        str[sp_num-1]->setstate();
                        fout << endl << opn << "\t0\tSuccess.";
                        return;
                    }
                }
            }
            fout << endl << opn << "\t10\tYou did not borrow this place.";
            return;
        }
    }else throw 3;
    fout.close();
}