// ============================================================
// ctc.cpp - CHUONG TRINH CHINH (main)
// De tai: QUAN LY THU VIEN
//
// File nay chi lam nhiem vu: khoi tao du lieu, hien thi Menu,
// nhan lua chon cua nguoi dung va goi ham chuc nang tuong ung
// (cac ham chuc nang duoc cai dat ben file cd.cpp).
                                //Thầy gợi ý tạo audio cho sách, hình ảnh sách và theo cảm hứng tương tự tiktok////
// ============================================================

#include "kb.h"
using namespace std;

int main() {
    // ---- Khoi tao 4 cau truc du lieu chinh ----
    NodeSach* danhSachSach = nullptr;   // Linked List: danh sach sach
    NodeBST* cayTimKiem = nullptr;      // BST: tim sach theo ma
    StackLichSu lichSuMuon;             // Stack: lich su muon sach
    HangDoi hangDoiDatTruoc;            // Queue: hang doi dat truoc sach

    khoiTaoDanhSach(danhSachSach);
    khoiTaoStack(lichSuMuon);
    khoiTaoQueue(hangDoiDatTruoc);

    // ---- Tao san mot vai sach mau de tien kiem thu ----
    NodeSach* n1 = themSachVaoDanhSach(danhSachSach, taoMaMoi(danhSachSach), "Lap Trinh C++ Can Ban", "Nguyen Van A", 3);
    cayTimKiem = chenBST(cayTimKiem, n1->data.maSach, n1);

    NodeSach* n2 = themSachVaoDanhSach(danhSachSach, taoMaMoi(danhSachSach), "Cau Truc Du Lieu Va Giai Thuat", "Tran Thi B", 2);
    cayTimKiem = chenBST(cayTimKiem, n2->data.maSach, n2);

    NodeSach* n3 = themSachVaoDanhSach(danhSachSach, taoMaMoi(danhSachSach), "Toan Roi Rac", "Le Van C", 1);
    cayTimKiem = chenBST(cayTimKiem, n3->data.maSach, n3);

    cout << "Chao mung ban den voi chuong trinh QUAN LY THU VIEN!\n";
    cout << "(Da tao san 3 sach mau de ban tien kiem thu chuong trinh)\n";

    int luaChon;
    do {
        inMenu();
        luaChon = nhapSoNguyen("Nhap lua chon cua ban: ");

        switch (luaChon) {
            case 1:
                chucNang_ThemSach(danhSachSach, cayTimKiem);
                break;
            case 2:
                chucNang_HienThiDanhSach(danhSachSach);
                break;
            case 3:
                chucNang_TimSachTheoMa(cayTimKiem);
                break;
            case 4:
                chucNang_MuonSach(danhSachSach, lichSuMuon, hangDoiDatTruoc);
                break;
            case 5:
                chucNang_TraSach(danhSachSach, hangDoiDatTruoc);
                break;
            case 6:
                chucNang_HoanTacMuonSach(danhSachSach, lichSuMuon);
                break;
            case 7:
                chucNang_XemLichSuMuon(lichSuMuon);
                break;
            case 8:
                chucNang_XemHangDoiDatTruoc(hangDoiDatTruoc);
                break;
            case 9:
                chucNang_XoaSach(danhSachSach, cayTimKiem, hangDoiDatTruoc);
                break;
            case 0:
                cout << "Cam on ban da su dung chuong trinh. Tam biet!\n";
                break;
            default:
                cout << "Lua chon khong hop le, vui long chon lai.\n";
        }
    } while (luaChon != 0);

    // ---- Giai phong toan bo bo nho da cap phat truoc khi ket thuc ----
    giaiPhongBST(cayTimKiem);
    giaiPhongDanhSach(danhSachSach);
    giaiPhongQueue(hangDoiDatTruoc);

    return 0;
}