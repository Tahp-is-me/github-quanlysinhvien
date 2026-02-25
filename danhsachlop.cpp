#include "danhsachlop.h"
#include <algorithm>
#include <iostream>
#include <fstream>

void GiaiPhongBoNho(DS_LOPSV &ds){
    for(int i = 0; i < ds.n; i++){
        delete ds.danhsachlopsv[i];
    }
    ds.n = 0;
}

int SoSanhChuoi(char* s1, char* s2){
    while(*s1 && (*s1 == *s2)){
        s1++;  //Tăng con trỏ s1 để sang ký tự tiếp theo
        s2++;  //Tăng con trỏ s2 để sang ký tự tiếp theo
    }
    return *(unsigned char*)s1 - *(unsigned char*)s2;
}

int TimKiemLop(DS_LOPSV &ds, char* maLop){
    for(int i = 0; i < ds.n; i++){
        if(SoSanhChuoi(ds.danhsachlopsv[i]->MALOP, maLop) == 0){
            return i;
        }
    }
    return -1;
}

void ThemLop(DS_LOPSV &ds, char* ma, char* ten){
    if(ds.n >= MAX_LOPSINHVIEN){
        cout << "Danh sach day" << endl;
        return;
    }

    LopSV* lopmoi = new LopSV();
    
    if(ma != NULL && ten != NULL){
        int i = 0;
        while(ma[i] != '\0') { lopmoi->MALOP[i] = ma[i]; i++; }
        lopmoi->MALOP[i] = '\0';

        int j = 0;
        while(ten[j] != '\0') { lopmoi->TENLOP[j] = ten[j]; j++; }
        lopmoi->TENLOP[j] = '\0';
    }else{
        char malop_tam[15];
        cout << "Nhap ma lop: "; cin >> malop_tam;
        
        if(TimKiemLop(ds, malop_tam) != -1){
            cout << "Ma lop da ton tai!" << endl;
            delete lopmoi;
            return;
        }

        int i = 0;
        while(malop_tam[i] != '\0') { lopmoi->MALOP[i] = malop_tam[i]; i++; }
        lopmoi->MALOP[i] = '\0';

        cout << "Nhap ten lop: ";
        cin.ignore();
        cin.getline(lopmoi->TENLOP, 50);
    }

    lopmoi->dssv = nullptr;
    ds.danhsachlopsv[ds.n] = lopmoi;
    ds.n++;

    LuuFile(ds);
}

void XoaLop(DS_LOPSV &ds) {
    inDanhSachLopAZ(ds);
    
    char malop[15];
    cout << "Nhap ma lop ban muon xoa (hoac nhap '0' de thoat): ";
    cin >> malop;

    if(malop[0] == '0' && malop[1] == '\0') return;

    int vitri = TimKiemLop(ds, malop);
    if(vitri == -1){
        cout << "Loi: Khong tim thay ma lop '" << malop << "' trong he thong!" << endl;
        return;
    }

    char xacnhan;
    cout << "Ban chac chan muon xoa lop " << ds.danhsachlopsv[vitri]->TENLOP << "? (y/n): ";
    cin >> xacnhan;
    
    if(xacnhan == 'y' || xacnhan == 'Y'){
        delete ds.danhsachlopsv[vitri];

        for(int i = vitri; i < ds.n - 1; i++){
            ds.danhsachlopsv[i] = ds.danhsachlopsv[i + 1];
        }
        ds.n--;

        LuuFile(ds);
        cout << "Xoa lop thanh cong!" << endl;
    }else{
        cout << "Da huy thao tac xoa." << endl;
    }
}

void hoanvi(LopSV* &a, LopSV* &b){
    LopSV* temp = a;
    a = b;
    b = temp;
}

// Hàm phân đoạn của QuickSort
int PhanDoan(LopSV* ds[], int thap, int cao){
    char* chot = ds[cao]->TENLOP;
    int i = (thap - 1); 

    for (int j = thap; j <= cao - 1; j++) {
        // Nếu tên lớp hiện tại "nhỏ hơn hoặc bằng" tên lớp chốt
        if (SoSanhChuoi(ds[j]->TENLOP, chot) <= 0) {
            i++;
            hoanvi(ds[i], ds[j]);
        }
    }
    hoanvi(ds[i + 1], ds[cao]);
    return (i + 1);
}

// Hàm QuickSort đệ quy
void quickSort(LopSV* ds[], int thap, int cao) {
    if (thap < cao) {
        int pi = PhanDoan(ds, thap, cao);
        quickSort(ds, thap, pi - 1);
        quickSort(ds, pi + 1, cao);
    }
}

void inDanhSachLopAZ(DS_LOPSV &ds) {
    if (ds.n == 0) {
        cout << "Danh sach trong!" << endl;
        return;
    }

    quickSort(ds.danhsachlopsv, 0, ds.n - 1);

    cout << left << setw(15) << "MA LOP" << "|" << setw(35) << "TEN LOP" << endl;
    cout << "---------------------------------------------------" << endl;
    for (int i = 0; i < ds.n; i++) {
        cout << left << setw(15) << ds.danhsachlopsv[i]->MALOP 
             << "|" << setw(35) << ds.danhsachlopsv[i]->TENLOP << endl;
    }
    cout << "---------------------------------------------------" << endl;
}

void LuuFile(DS_LOPSV &ds){
    ofstream fout("danhsachlop.txt");
    if(!fout) return;

    for(int i = 0; i < ds.n; i++){
        fout << ds.danhsachlopsv[i]->MALOP << "|"
             << ds.danhsachlopsv[i]->TENLOP << endl;

    }
    fout.close();
}

void DocFile(DS_LOPSV &ds){
    ifstream fin("danhsachlop.txt");
    if(!fin) return;

    char malop[15], tenlop[50];
    while(fin.getline(malop, 15, '|') && fin.getline(tenlop, 50)){
        ThemLop(ds, malop, tenlop);
    }
    fin.close();
}