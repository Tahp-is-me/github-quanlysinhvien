#ifndef DANHSACHLOP_H
#define DANHSACHLOP_H

#include "khaibao.h"

// Các hàm xử lý chuỗi và tìm kiếm
int SoSanhChuoi(char* s1, char* s2);
int TimKiemLop(DS_LOPSV &ds, char* maLop);

void ThemLop(DS_LOPSV &ds, char* ma = NULL, char* ten = NULL);

// Các hàm quản lý lớp
// void ThemLop(DS_LOPSV &ds);
// void ThemLopCoSan(DS_LOPSV &ds, char malop[], char tenlop[]);
void XoaLop(DS_LOPSV &ds);
void inDanhSachLopAZ(DS_LOPSV &ds); 
// File IO
void LuuFile(DS_LOPSV &ds);
void DocFile(DS_LOPSV &ds);

// Giải phóng bộ nhớ
void GiaiPhongBoNho(DS_LOPSV &ds);

#endif