#include "danhsachsinhvien.h"
#include "danhsachlop.h"
#include <iostream>

void ThemSinhVien(PTRSV &First, SinhVien sv){
    PTRSV svmoi = new SV();
    svmoi->sv = sv;
    svmoi->next = nullptr;

    if(First == nullptr || SoSanhChuoi(sv.MASV, First->sv.MASV) < 0){
        svmoi->next = First;
        First = svmoi;
    }else{
        PTRSV p = First;
        while(p->next != nullptr && SoSanhChuoi(p->next->sv.MASV, sv.MASV) < 0){
            p = p->next;
        }
        
        if(SoSanhChuoi(p->sv.MASV, sv.MASV) == 0){
            cout << "Loi: Ma sinh vien " << sv.MASV << " da ton tai!" << endl;
            delete svmoi;
            return;
        }

        svmoi->next = p->next;
        p->next = svmoi;
    }
}

void XoaSinhVien(DS_LOPSV &dsLopSV){
    char malop[15];
    cout << "Nhap ma lop cua sinh vien can xoa: ";
    cin >> malop;
    cin.ignore();

    int index = TimKiemLop(dsLopSV, malop);
    if (index == -1) {
        cout << "Ma lop khong ton tai!" << endl;
        return;
    }

    PTRSV &First = dsLopSV.danhsachlopsv[index]->dssv;
    if (First == nullptr) {
        cout << "Lop nay hien tai chua co sinh vien." << endl;
        return;
    }

    char masv[15];
    cout << "Nhap ma sinh vien can xoa: ";
    cin.getline(masv, 15);

    PTRSV truoc = nullptr;
    PTRSV sau = First;

    while (sau != nullptr && SoSanhChuoi(sau->sv.MASV, masv) != 0) {
        truoc = sau;
        sau = sau->next;
    }

    if (sau == nullptr) {
        cout << "Khong tim thay ma sinh vien " << masv << " trong lop " << malop << endl;
        return;
    }

    char xacnhan;
    cout << "Ban co chac muon xoa SV: " << sau->sv.HO << " " << sau->sv.TEN << "? (y/n): ";
    cin >> xacnhan;
    cin.ignore();

    if (xacnhan == 'y' || xacnhan == 'Y') {
        if (truoc == nullptr) {
            First = First->next; // Xóa đầu
        } else {
            truoc->next = sau->next; // Xóa giữa hoặc cuối
        }
        delete sau;
        
        // Lưu lại toàn bộ danh sách sinh viên vào file sau khi thay đổi
        LuuFileSinhVien(dsLopSV); 
        cout << "Da xoa thanh cong!" << endl;
    } else {
        cout << "Da huy lenh xoa." << endl;
    }
}

void HieuChinhSinhVien(DS_LOPSV &dsLopSV) {
    char malop[15];
    cout << "Nhap ma lop cua sinh vien can hieu chinh: ";
    cin >> malop;
    cin.ignore();

    int index = TimKiemLop(dsLopSV, malop);
    if (index == -1) {
        cout << "Ma lop khong ton tai!" << endl;
        return;
    }

    PTRSV p = dsLopSV.danhsachlopsv[index]->dssv;
    char masv[15];
    cout << "Nhap ma sinh vien can chinh: ";
    cin.getline(masv, 15);

    // Tìm kiếm sinh viên bằng SoSanhChuoi
    while (p != nullptr && SoSanhChuoi(p->sv.MASV, masv) != 0) {
        p = p->next;
    }

    if (p == nullptr) {
        cout << "Khong tim thay ma sinh vien " << masv << " trong lop " << malop << endl;
    } else {
        cout << "--- Nhap thong tin moi ---" << endl;
        cout << "Ho moi: "; cin.getline(p->sv.HO, 50);
        cout << "Ten moi: "; cin.getline(p->sv.TEN, 50);
        cout << "Phai: "; cin.getline(p->sv.PHAI, 5);
        cout << "So DT: "; cin.getline(p->sv.SODT, 15);

        LuuFileSinhVien(dsLopSV); // Lưu lại thay đổi vào file
        cout << "Hieu chinh thanh cong!" << endl;
    }
}

void NhapSinhVien(DS_LOPSV &dsLopSV){
    char malop[15];
    cout << "Nhap ma lop: "; 
    cin >> malop;

    int index = TimKiemLop(dsLopSV, malop);

    if(index == -1){
        cout << "Ma lop khong ton tai!" << endl;
        return;
    }
    cin.ignore();

    while(true){
        SinhVien sv;
        cout << "Nhap Ma SV (Bam Enter de dung): ";
        cin.getline(sv.MASV, 15);
       
        if(sv.MASV[0] == '\0'){
            break; 
        }

        cout << "Ho: "; cin.getline(sv.HO, 50);
        cout << "Ten: "; cin.getline(sv.TEN, 50);
        cout << "Phai: "; cin.getline(sv.PHAI, 5);
        cout << "So DT: "; cin.getline(sv.SODT, 15);
        
        for(int i = 0; i < 15; i++){
            sv.MALOP[i] = malop[i];
            if(malop[i] == '\0') break;
        }
        ThemSinhVien(dsLopSV.danhsachlopsv[index]->dssv, sv);
    }
    
    LuuFileSinhVien(dsLopSV);
}

bool SoSanh(SinhVien a, SinhVien b) {
    int soSanhTen = SoSanhChuoi(a.TEN, b.TEN);
    if (soSanhTen < 0) return true;
    if (soSanhTen > 0) return false;

    int soSanhHo = SoSanhChuoi(a.HO, b.HO);
    if (soSanhHo < 0) return true;
    if (soSanhHo > 0) return false;

    return SoSanhChuoi(a.MASV, b.MASV) < 0;
}

void ChiaDanhSach(PTRSV First, PTRSV &truoc, PTRSV &sau) {
    PTRSV nhanh = First->next;
    PTRSV cham = First;

    //tìm điểm giữa
    while (nhanh != nullptr){
        nhanh = nhanh->next;
        if (nhanh != nullptr) {
            cham = cham->next;
            nhanh = nhanh->next;
        }
    }
    truoc = First;
    sau = cham->next;
    cham->next = nullptr;
}

// Ham tron hai danh sach da sap xep
PTRSV TronDanhSach(PTRSV a, PTRSV b) {
    PTRSV ket_qua = nullptr;

    if (a == nullptr) return b;
    else if (b == nullptr) return a;

    // So sanh va de quy de tron
    if (SoSanh(a->sv, b->sv)) {
        ket_qua = a;
        ket_qua->next = TronDanhSach(a->next, b);
    } else {
        ket_qua = b;
        ket_qua->next = TronDanhSach(a, b->next);
    }
    return ket_qua;
}

// Ham chinh thuc hien Merge Sort
void SapXepMergeSort(PTRSV &First){
    PTRSV dau = First;
    PTRSV trai;
    PTRSV phai;

    if ((dau == nullptr) || (dau->next == nullptr)) return;

    ChiaDanhSach(dau, trai, phai);

    SapXepMergeSort(trai);
    SapXepMergeSort(phai);

    // Tron lai sau khi da sap xep xong
    First = TronDanhSach(trai, phai);
}

void InDSSV(DS_LOPSV ds){
    char malop[15];
    cout << "Nhap ma lop: "; 
    cin >> malop;

    int index = TimKiemLop(ds, malop);

    if(index == -1){
        cout << "Ma lop khong ton tai!" << endl;
        return;
    }
    cin.ignore();

    PTRSV goc = ds.danhsachlopsv[index]->dssv;
    if(goc == nullptr){
        cout << "Lop nay hien tai chua co sinh vien." << endl;
        return;
    }

    //Tao ban sao danh sach de sap xep (tranh lam thay doi DSLK goc cua lop)
    PTRSV dau_tam = nullptr, duoi_tam = nullptr;
    for (PTRSV p = goc; p != nullptr; p = p->next) {
        PTRSV nut_moi = new SV;
        nut_moi->sv = p->sv;
        nut_moi->next = nullptr;
        if (dau_tam == nullptr) {
            dau_tam = nut_moi;
        } else {
            duoi_tam->next = nut_moi;
        }
        duoi_tam = nut_moi;
    }

    SapXepMergeSort(dau_tam);

    cout << "\nDANH SACH SINH VIEN LOP: " << malop << endl;
    cout << left << setw(5) << "STT" << setw(15) << "MA SV" << setw(25) << "HO" << setw(15) << "TEN" << endl;
    
    int stt = 1;
    PTRSV hien_tai = dau_tam;
    while(hien_tai != nullptr){
        cout << left << setw(5) << stt++ 
             << setw(15) << hien_tai->sv.MASV 
             << setw(25) << hien_tai->sv.HO 
             << setw(15) << hien_tai->sv.TEN << endl;
        
        PTRSV nut_xoa = hien_tai;
        hien_tai = hien_tai->next;
        delete nut_xoa;
    }
}

void TimSinhVien(DS_LOPSV dsLopSV){
    char masv[15];
    cout << "Nhap ma sinh vien can tim: ";
    cin.ignore();
    cin.getline(masv, 15);

    bool timthay = false;

    for (int i = 0; i < dsLopSV.n; i++) {
        PTRSV p = dsLopSV.danhsachlopsv[i]->dssv;

        while (p != nullptr){
            if(SoSanhChuoi(p->sv.MASV, masv) == 0){ 
                cout << "\n--- THONG TIN SINH VIEN TIM THAY ---" << endl;
                cout << "Ma SV: " << p->sv.MASV << endl;
                cout << "Ho ten: " << p->sv.HO << " " << p->sv.TEN << endl;
                cout << "Phai: " << p->sv.PHAI << endl;
                cout << "So DT: " << p->sv.SODT << endl;
                cout << "Ma lop: " << p->sv.MALOP << endl;
                
                timthay = true;
                break;
            }
            p = p->next;
        }
        if(timthay) break;
    }

    if(!timthay){
        cout << "Khong tim thay sinh vien co ma: " << masv << endl;
    }
}

void LuuFileSinhVien(DS_LOPSV ds){
    ofstream fout("danhsachsinhvien.txt");
    if (!fout) return;

    for (int i = 0; i < ds.n; i++) {
        PTRSV p = ds.danhsachlopsv[i]->dssv;
        while (p != nullptr) {
            fout << p->sv.MASV << "|" << p->sv.HO << "|"
                 << p->sv.TEN << "|" << p->sv.PHAI << "|"
                 << p->sv.SODT << "|" << p->sv.MALOP << endl;
            p = p->next;
        }
    }
    fout.close();
}

void DocFileSinhVien(DS_LOPSV &dsLopSV) {
    ifstream fin("danhsachsinhvien.txt");
    if (!fin) return;

    SinhVien sv;
    while (fin.getline(sv.MASV, 15, '|') &&
           fin.getline(sv.HO, 50, '|') &&
           fin.getline(sv.TEN, 50, '|') &&
           fin.getline(sv.PHAI, 5, '|') &&
           fin.getline(sv.SODT, 15, '|') &&
           fin.getline(sv.MALOP, 15)) { 
        
        int index = TimKiemLop(dsLopSV, sv.MALOP);
        if (index != -1) {
            ThemSinhVien(dsLopSV.danhsachlopsv[index]->dssv, sv);
        }
    }
    fin.close();
}