#include <iostream>  
#include <fstream>   
#include <cstring>   
#include <iomanip>   
#include <stdlib.h> 
#include <conio.h>

using namespace std;

const int MAX_LOPTINCHI = 10000;
const int MAX_LOPSINHVIEN = 10000;
struct MonHoc{
    char MAMH[15];      
    char TENMH[50];     
    int sotinchilythuyet;          
    int sotinchithuchanh;
};

struct MH{
    MonHoc mh;
    MH *left, *right;
};
typedef MH* caymonhoc;

struct LopTinChi{
    int MALOPTC;        
    char MAMH[10];      
    char nienkhoa[10];   
    int hocky;         
    int nhom;           
    int sosvmin;        
    int sosvmax;        
    bool huylop;       
    PTRDK dssvdk = nullptr;
};

struct DS_LOPTINCHI{
    int n = 0;
    LopTinChi* danhsach[MAX_LOPTINCHI];
};

struct SinhVien{
    char MASV[15];       
    char HO[50];        
    char TEN[50];       
    char PHAI[5];       
    char SODT[15];      
    char MALOP[15];
};

struct SV{
    SinhVien sv;
    SV *next;
};
typedef SV* PTRSV;

struct DangKy{
    char MASV[15];      
    float DIEM;         
    bool huydangky;
};

struct DK{
    DangKy dk;
    DK *next;
};
typedef DK* PTRDK;

struct LopSV{
    char MALOP[15];     
    char TENLOP[50];
    PTRSV dssv = nullptr;
};

struct DS_LOPSV{
    int n = 0;
    LopSV* danhsachlopsv[MAX_LOPSINHVIEN];
};

int main(){
    caymonhoc dsmonhoc = nullptr;

    DS_LOPTINCHI dsloptc;
    dsloptc.n = 0;

    DS_LOPSV dslopsv;
    dslopsv.n = 0;
}