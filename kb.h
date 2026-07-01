// ============================================================
// kb.h - FILE KHAI BAO
// De tai: QUAN LY THU VIEN
// Noi dung: khai bao cac struct (cau truc du lieu) va prototype
//           cua tat ca cac ham se duoc cai dat trong cd.cpp
//
// 4 cau truc du lieu duoc su dung trong bai:
//   1. Linked List (danh sach lien ket) -> luu danh sach sach
//   2. BST (cay nhi phan tim kiem)      -> tim sach nhanh theo ma
//   3. Stack (ngan xep, dung mang)      -> luu lich su muon sach
//   4. Queue (hang doi, dung con tro)   -> hang doi dat truoc sach
// ============================================================

#ifndef KB_H
#define KB_H

#include <iostream>
#include <string>
using namespace std;

// ------------------------------------------------------------
// 1. CAU TRUC SACH
// Moi cuon sach co: ma sach (dung de tim kiem), ten, tac gia,
// tong so luong nhap ve va so luong con lai co the muon.
// ------------------------------------------------------------
struct Sach {
    int maSach;
    string tenSach;
    string tacGia;
    int tongSoLuong;
    int soLuongCon;
};

// Node cua danh sach lien ket (Linked List) chua sach
struct NodeSach {
    Sach data;
    NodeSach* next;
};

// ------------------------------------------------------------
// 2. CAY NHI PHAN TIM KIEM (BST)
// Cay nay chi luu "ma sach" de tim kiem cho nhanh (O(log n)),
// con du lieu chi tiet cua sach van nam ben Linked List.
// lienKetToiSach la con tro tro thang toi node ben Linked List,
// giup khong phai luu du lieu 2 lan.
// ------------------------------------------------------------
struct NodeBST {
    int maSach;
    NodeSach* lienKetToiSach;
    NodeBST* left;
    NodeBST* right;
};

// ------------------------------------------------------------
// 3. STACK (NGAN XEP) - luu lich su muon sach
// Dung mang tinh (mang co san) cho de hinh dung voi sinh vien
// nam nhat. Moi lan muon sach se PUSH 1 phieu muon vao stack.
// Khi can "hoan tac" (undo) lan muon gan nhat thi POP ra.
// ------------------------------------------------------------
struct PhieuMuon {
    int maSach;
    string tenSach;
    string tenNguoiMuon;
};

const int MAX_STACK = 200;

struct StackLichSu {
    PhieuMuon data[MAX_STACK];
    int top; // vi tri phan tu tren cung, -1 la rong
};

// ------------------------------------------------------------
// 4. QUEUE (HANG DOI) - hang doi dat truoc sach
// Dung danh sach lien ket (khong gioi han so luong) vi so
// nguoi dat truoc khong biet truoc duoc bao nhieu.
// Ai dat truoc thi duoc uu tien nhan sach truoc (FIFO).
// ------------------------------------------------------------
struct DatTruoc {
    int maSach;
    string tenNguoiDat;
};

struct NodeQueue {
    DatTruoc data;
    NodeQueue* next;
};

struct HangDoi {
    NodeQueue* front;
    NodeQueue* rear;
};

// ============================================================
// KHAI BAO HAM (PROTOTYPE)
// ============================================================

// ---------- Linked List: quan ly danh sach sach ----------
void khoiTaoDanhSach(NodeSach*& head);
NodeSach* timTheoMa_LinearSearch(NodeSach* head, int ma); // tim tuan tu (doi chieu voi BST)
NodeSach* themSachVaoDanhSach(NodeSach*& head, int ma, string ten, string tacGia, int soLuong);
bool xoaSachKhoiDanhSach(NodeSach*& head, int ma);
void hienThiDanhSach(NodeSach* head);
void giaiPhongDanhSach(NodeSach*& head);
int taoMaMoi(NodeSach* head);
bool dungChungMaSach(NodeSach* head, int ma);

// ---------- BST: tim kiem sach theo ma ----------
NodeBST* chenBST(NodeBST* root, int ma, NodeSach* lienKet);
NodeBST* timBST(NodeBST* root, int ma);
NodeBST* xoaKhoiBST(NodeBST* root, int ma);
void giaiPhongBST(NodeBST*& root);

// ---------- Stack: lich su muon sach ----------
void khoiTaoStack(StackLichSu& s);
bool stackRong(StackLichSu& s);
bool stackDay(StackLichSu& s);
bool push(StackLichSu& s, PhieuMuon pm);
bool pop(StackLichSu& s, PhieuMuon& pm);
void hienThiStack(StackLichSu& s);

// ---------- Queue: hang doi dat truoc ----------
void khoiTaoQueue(HangDoi& q);
bool queueRong(HangDoi& q);
void enqueue(HangDoi& q, DatTruoc dt);
bool dequeue(HangDoi& q, DatTruoc& dt);
void hienThiQueue(HangDoi& q);
void giaiPhongQueue(HangDoi& q);

// ---------- Cac chuc nang nghiep vu (goi tu Menu trong ctc.cpp) ----------
void chucNang_ThemSach(NodeSach*& head, NodeBST*& root);
void chucNang_HienThiDanhSach(NodeSach* head);
void chucNang_TimSachTheoMa(NodeBST* root);
void chucNang_MuonSach(NodeSach* head, StackLichSu& lichSu, HangDoi& hangDoi);
void chucNang_TraSach(NodeSach* head, HangDoi& hangDoi);
void chucNang_HoanTacMuonSach(NodeSach* head, StackLichSu& lichSu);
void chucNang_XoaSach(NodeSach*& head, NodeBST*& root, HangDoi& hangDoi);
void chucNang_XemLichSuMuon(StackLichSu& lichSu);
void chucNang_XemHangDoiDatTruoc(HangDoi& hangDoi);

// ---------- Ham phu tro ----------
void inMenu();
int nhapSoNguyen(string thongBao); // nhap so nguyen an toan, khong loi neu go chu

#endif