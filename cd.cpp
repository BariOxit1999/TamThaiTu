// ============================================================
// cd.cpp - FILE CAI DAT (implementation)
// Cai dat toan bo cac ham da khai bao trong kb.h
// ============================================================

#include "kb.h"
#include <limits>
#include <iomanip>
using namespace std;

// ============================================================
// ---------------- LINKED LIST: DANH SACH SACH --------------
// ============================================================

// Khoi tao danh sach rong
void khoiTaoDanhSach(NodeSach*& head) {
    head = nullptr;
}

// Tim sach theo ma bang cach duyet tuan tu tung node
// (dung de doi chieu ket qua voi ham tim bang BST ben duoi)
NodeSach* timTheoMa_LinearSearch(NodeSach* head, int ma) {
    NodeSach* p = head;
    while (p != nullptr) {
        if (p->data.maSach == ma) return p;
        p = p->next;
    }
    return nullptr;
}

// Kiem tra ma sach da ton tai chua (dung khi them sach moi)
bool dungChungMaSach(NodeSach* head, int ma) {
    return timTheoMa_LinearSearch(head, ma) != nullptr;
}

// Tu dong sinh ma sach moi = ma lon nhat hien co + 1
// (neu danh sach rong thi bat dau tu 1)
int taoMaMoi(NodeSach* head) {
    int maxMa = 0;
    NodeSach* p = head;
    while (p != nullptr) {
        if (p->data.maSach > maxMa) maxMa = p->data.maSach;
        p = p->next;
    }
    return maxMa + 1;
}

// Them 1 cuon sach moi vao CUOI danh sach lien ket
// Tra ve con tro toi node vua them (de con lien ket sang BST)
NodeSach* themSachVaoDanhSach(NodeSach*& head, int ma, string ten, string tacGia, int soLuong) {
    NodeSach* newNode = new NodeSach;
    newNode->data.maSach = ma;
    newNode->data.tenSach = ten;
    newNode->data.tacGia = tacGia;
    newNode->data.tongSoLuong = soLuong;
    newNode->data.soLuongCon = soLuong;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
    } else {
        NodeSach* p = head;
        while (p->next != nullptr) p = p->next;
        p->next = newNode;
    }
    return newNode;
}

// Xoa 1 cuon sach khoi danh sach lien ket theo ma sach
bool xoaSachKhoiDanhSach(NodeSach*& head, int ma) {
    if (head == nullptr) return false;

    // Truong hop can xoa la node dau tien
    if (head->data.maSach == ma) {
        NodeSach* temp = head;
        head = head->next;
        delete temp;
        return true;
    }

    NodeSach* truoc = head;
    NodeSach* hienTai = head->next;
    while (hienTai != nullptr) {
        if (hienTai->data.maSach == ma) {
            truoc->next = hienTai->next;
            delete hienTai;
            return true;
        }
        truoc = hienTai;
        hienTai = hienTai->next;
    }
    return false; // khong tim thay
}

// In toan bo danh sach sach ra man hinh dang bang
// Bang se TU GIAN RONG cot theo du lieu thuc te (khong dung do rong co dinh
// nua), vi vay ten sach/tac gia du dai bao nhieu cung khong bi vo bang.
void hienThiDanhSach(NodeSach* head) {
    if (head == nullptr) {
        cout << "Danh sach sach dang trong.\n";
        return;
    }

    // Buoc 1: duyet 1 luot qua danh sach de tim do dai LON NHAT cua tung cot
    // (bat dau tu do dai cua chinh tieu de cot, de tieu de khong bi cat)
    const string TIEU_DE_MA = "MA";
    const string TIEU_DE_TEN = "TEN SACH";
    const string TIEU_DE_TACGIA = "TAC GIA";
    const string TIEU_DE_SOLUONG = "CON LAI/TONG";

    size_t rongMa = TIEU_DE_MA.size();
    size_t rongTen = TIEU_DE_TEN.size();
    size_t rongTacGia = TIEU_DE_TACGIA.size();
    size_t rongSoLuong = TIEU_DE_SOLUONG.size();

    NodeSach* p = head;
    while (p != nullptr) {
        size_t doDaiMa = to_string(p->data.maSach).size();
        if (doDaiMa > rongMa) rongMa = doDaiMa;

        if (p->data.tenSach.size() > rongTen) rongTen = p->data.tenSach.size();
        if (p->data.tacGia.size() > rongTacGia) rongTacGia = p->data.tacGia.size();

        string chuoiSoLuong = to_string(p->data.soLuongCon) + "/" + to_string(p->data.tongSoLuong);
        if (chuoiSoLuong.size() > rongSoLuong) rongSoLuong = chuoiSoLuong.size();

        p = p->next;
    }

    // Buoc 2: tinh tong do rong duong ke ngang " | " noi giua 4 cot (3 dau noi)
    size_t tongDoRong = rongMa + rongTen + rongTacGia + rongSoLuong + 3 * 3;

    // Buoc 3: in tieu de va bang theo do rong vua tinh duoc
    cout << "\n";
    cout << left << setw((int)rongMa) << TIEU_DE_MA << " | "
         << left << setw((int)rongTen) << TIEU_DE_TEN << " | "
         << left << setw((int)rongTacGia) << TIEU_DE_TACGIA << " | "
         << TIEU_DE_SOLUONG << "\n";
    cout << string(tongDoRong, '-') << "\n";

    p = head;
    while (p != nullptr) {
        string chuoiSoLuong = to_string(p->data.soLuongCon) + "/" + to_string(p->data.tongSoLuong);
        cout << left << setw((int)rongMa) << p->data.maSach << " | "
             << left << setw((int)rongTen) << p->data.tenSach << " | "
             << left << setw((int)rongTacGia) << p->data.tacGia << " | "
             << chuoiSoLuong << "\n";
        p = p->next;
    }
    cout << string(tongDoRong, '-') << "\n";
}

// Giai phong toan bo bo nho cua danh sach lien ket (dung khi ket thuc chuong trinh)
void giaiPhongDanhSach(NodeSach*& head) {
    NodeSach* p = head;
    while (p != nullptr) {
        NodeSach* temp = p;
        p = p->next;
        delete temp;
    }
    head = nullptr;
}

// ============================================================
// ------------------ BST: TIM KIEM THEO MA -------------------
// ============================================================

// Chen 1 ma sach moi vao cay BST (theo quy tac: trai < goc < phai)
NodeBST* chenBST(NodeBST* root, int ma, NodeSach* lienKet) {
    if (root == nullptr) {
        NodeBST* newNode = new NodeBST;
        newNode->maSach = ma;
        newNode->lienKetToiSach = lienKet;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }
    if (ma < root->maSach) {
        root->left = chenBST(root->left, ma, lienKet);
    } else if (ma > root->maSach) {
        root->right = chenBST(root->right, ma, lienKet);
    }
    // neu ma trung nhau thi bo qua (khong chen trung)
    return root;
}

// Tim mot node trong BST theo ma sach
NodeBST* timBST(NodeBST* root, int ma) {
    if (root == nullptr) return nullptr;
    if (root->maSach == ma) return root;
    if (ma < root->maSach) return timBST(root->left, ma);
    return timBST(root->right, ma);
}

// Tim node nho nhat trong 1 cay con (dung khi xoa node co 2 con)
static NodeBST* timNodeNhoNhat(NodeBST* root) {
    while (root->left != nullptr) root = root->left;
    return root;
}

// Xoa 1 node trong BST theo ma sach (co du 3 truong hop: 0, 1, 2 con)
NodeBST* xoaKhoiBST(NodeBST* root, int ma) {
    if (root == nullptr) return nullptr;

    if (ma < root->maSach) {
        root->left = xoaKhoiBST(root->left, ma);
    } else if (ma > root->maSach) {
        root->right = xoaKhoiBST(root->right, ma);
    } else {
        // tim thay node can xoa
        if (root->left == nullptr && root->right == nullptr) {
            // Truong hop 1: khong co con nao
            delete root;
            return nullptr;
        } else if (root->left == nullptr) {
            // Truong hop 2: chi co con phai
            NodeBST* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            // Truong hop 2: chi co con trai
            NodeBST* temp = root->left;
            delete root;
            return temp;
        } else {
            // Truong hop 3: co ca 2 con
            // -> lay node nho nhat ben cay con phai thay the
            NodeBST* thayThe = timNodeNhoNhat(root->right);
            root->maSach = thayThe->maSach;
            root->lienKetToiSach = thayThe->lienKetToiSach;
            root->right = xoaKhoiBST(root->right, thayThe->maSach);
        }
    }
    return root;
}

// Giai phong toan bo bo nho cua cay BST
void giaiPhongBST(NodeBST*& root) {
    if (root == nullptr) return;
    giaiPhongBST(root->left);
    giaiPhongBST(root->right);
    delete root;
    root = nullptr;
}

// ============================================================
// --------------- STACK: LICH SU MUON SACH -------------------
// ============================================================

void khoiTaoStack(StackLichSu& s) {
    s.top = -1;
}

bool stackRong(StackLichSu& s) {
    return s.top == -1;
}

bool stackDay(StackLichSu& s) {
    return s.top == MAX_STACK - 1;
}

// Them 1 phieu muon len dinh stack
bool push(StackLichSu& s, PhieuMuon pm) {
    if (stackDay(s)) return false; // stack day, khong push duoc nua
    s.top++;
    s.data[s.top] = pm;
    return true;
}

// Lay phieu muon tren dinh stack ra (dung khi hoan tac)
bool pop(StackLichSu& s, PhieuMuon& pm) {
    if (stackRong(s)) return false;
    pm = s.data[s.top];
    s.top--;
    return true;
}

// In lich su muon sach, tu lan muon GAN NHAT den xa nhat (dung tinh chat LIFO cua stack)
void hienThiStack(StackLichSu& s) {
    if (stackRong(s)) {
        cout << "Chua co lich su muon sach nao.\n";
        return;
    }
    cout << "\n(Hien thi tu lan muon GAN NHAT den XA NHAT)\n";
    cout << "----------------------------------------------------------\n";
    for (int i = s.top; i >= 0; i--) {
        cout << "Ma sach: " << s.data[i].maSach
             << " | Ten sach: " << s.data[i].tenSach
             << " | Nguoi muon: " << s.data[i].tenNguoiMuon << "\n";
    }
    cout << "----------------------------------------------------------\n";
}

// ============================================================
// --------------- QUEUE: HANG DOI DAT TRUOC -------------------
// ============================================================

void khoiTaoQueue(HangDoi& q) {
    q.front = nullptr;
    q.rear = nullptr;
}

bool queueRong(HangDoi& q) {
    return q.front == nullptr;
}

// Them 1 yeu cau dat truoc vao CUOI hang doi
void enqueue(HangDoi& q, DatTruoc dt) {
    NodeQueue* newNode = new NodeQueue;
    newNode->data = dt;
    newNode->next = nullptr;

    if (q.rear == nullptr) {
        // hang doi dang rong
        q.front = newNode;
        q.rear = newNode;
    } else {
        q.rear->next = newNode;
        q.rear = newNode;
    }
}

// Lay 1 yeu cau dat truoc ra khoi DAU hang doi (nguoi dat truoc lau nhat se ra truoc - FIFO)
bool dequeue(HangDoi& q, DatTruoc& dt) {
    if (queueRong(q)) return false;
    NodeQueue* temp = q.front;
    dt = temp->data;
    q.front = q.front->next;
    if (q.front == nullptr) q.rear = nullptr; // hang doi vua het phan tu
    delete temp;
    return true;
}

// In toan bo hang doi dat truoc (tu nguoi dau tien den nguoi cuoi cung)
void hienThiQueue(HangDoi& q) {
    if (queueRong(q)) {
        cout << "Hang doi dat truoc dang trong.\n";
        return;
    }
    cout << "\n(Thu tu tu NGUOI DAT TRUOC LAU NHAT den GAN NHAT)\n";
    cout << "----------------------------------------------------------\n";
    NodeQueue* p = q.front;
    int stt = 1;
    while (p != nullptr) {
        cout << stt << ". Ma sach: " << p->data.maSach
             << " | Nguoi dat: " << p->data.tenNguoiDat << "\n";
        p = p->next;
        stt++;
    }
    cout << "----------------------------------------------------------\n";
}

void giaiPhongQueue(HangDoi& q) {
    NodeQueue* p = q.front;
    while (p != nullptr) {
        NodeQueue* temp = p;
        p = p->next;
        delete temp;
    }
    q.front = nullptr;
    q.rear = nullptr;
}

// ============================================================
// ------------------------ HAM PHU TRO ------------------------
// ============================================================

// Nhap 1 so nguyen an toan: neu nguoi dung go chu se bao loi va
// bat nhap lai, tranh vong lap vo tan do loi cin (bug hay gap).
int nhapSoNguyen(string thongBao) {
    int x;
    while (true) {
        cout << thongBao;
        cin >> x;
        if (cin.fail()) {
            cin.clear(); // xoa co loi cua cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // bo qua du lieu sai
            cout << "Ban vui long nhap so! Thu lai.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // don dep buffer truoc khi getline
            return x;
        }
    }
}

void inMenu() {
    cout << "\n";
    cout << "=================== QUAN LY THU VIEN ===================\n";
    cout << " 1. Them sach moi\n";
    cout << " 2. Hien thi danh sach sach\n";
    cout << " 3. Tim sach theo ma (dung BST)\n";
    cout << " 4. Muon sach\n";
    cout << " 5. Tra sach\n";
    cout << " 6. Hoan tac lan muon gan nhat (dung Stack)\n";
    cout << " 7. Xem lich su muon sach\n";
    cout << " 8. Xem hang doi dat truoc sach (dung Queue)\n";
    cout << " 9. Xoa sach\n";
    cout << " 0. Thoat chuong trinh\n";
    cout << "==========================================================\n";
}

// ============================================================
// ------------------- CAC CHUC NANG NGHIEP VU ------------------
// (Cac ham nay ket hop nhieu cau truc du lieu voi nhau va duoc
//  goi truc tiep tu vong lap Menu trong ctc.cpp)
// ============================================================

// 1. THEM SACH: them vao Linked List, sau do chen ma vao BST de tim nhanh
void chucNang_ThemSach(NodeSach*& head, NodeBST*& root) {
    cout << "\n--- THEM SACH MOI ---\n";
    string ten, tacGia;
    int soLuong;

    cout << "Nhap ten sach: ";
    getline(cin, ten);
    cout << "Nhap tac gia: ";
    getline(cin, tacGia);
    soLuong = nhapSoNguyen("Nhap so luong: ");

    if (soLuong <= 0) {
        cout << "So luong phai lon hon 0. Huy them sach.\n";
        return;
    }

    int maMoi = taoMaMoi(head); // he thong tu sinh ma, tranh trung ma
    NodeSach* nodeVuaThem = themSachVaoDanhSach(head, maMoi, ten, tacGia, soLuong);
    root = chenBST(root, maMoi, nodeVuaThem);

    cout << "Them sach thanh cong! Ma sach duoc cap la: " << maMoi << "\n";
}

// 2. HIEN THI: duyet toan bo Linked List
void chucNang_HienThiDanhSach(NodeSach* head) {
    cout << "\n--- DANH SACH SACH TRONG THU VIEN ---\n";
    hienThiDanhSach(head);
}

// 3. TIM SACH: dung BST de tim theo ma (nhanh hon duyet tuan tu)
void chucNang_TimSachTheoMa(NodeBST* root) {
    cout << "\n--- TIM SACH THEO MA ---\n";
    int ma = nhapSoNguyen("Nhap ma sach can tim: ");
    NodeBST* ketQua = timBST(root, ma);
    if (ketQua == nullptr) {
        cout << "Khong tim thay sach co ma " << ma << ".\n";
        return;
    }
    Sach& s = ketQua->lienKetToiSach->data;
    cout << "Tim thay!\n";
    cout << "Ma sach : " << s.maSach << "\n";
    cout << "Ten sach: " << s.tenSach << "\n";
    cout << "Tac gia : " << s.tacGia << "\n";
    cout << "Con lai : " << s.soLuongCon << "/" << s.tongSoLuong << "\n";
}

// 4. MUON SACH:
//    - Neu con sach: giam so luong, day 1 phieu muon vao Stack (lich su)
//    - Neu het sach: cho nguoi dung vao Queue (hang doi dat truoc)
void chucNang_MuonSach(NodeSach* head, StackLichSu& lichSu, HangDoi& hangDoi) {
    cout << "\n--- MUON SACH ---\n";
    int ma = nhapSoNguyen("Nhap ma sach muon muon: ");
    NodeSach* node = timTheoMa_LinearSearch(head, ma);

    if (node == nullptr) {
        cout << "Khong tim thay sach co ma " << ma << ".\n";
        return;
    }

    cout << "Nhap ten nguoi muon: ";
    string ten;
    getline(cin, ten);

    if (node->data.soLuongCon > 0) {
        node->data.soLuongCon--;
        PhieuMuon pm;
        pm.maSach = ma;
        pm.tenSach = node->data.tenSach;
        pm.tenNguoiMuon = ten;
        push(lichSu, pm);
        cout << "Muon sach thanh cong! Sach con lai: " << node->data.soLuongCon << "\n";
    } else {
        // Het sach -> dua vao hang doi dat truoc
        DatTruoc dt;
        dt.maSach = ma;
        dt.tenNguoiDat = ten;
        enqueue(hangDoi, dt);
        cout << "Sach da het! Ban da duoc them vao hang doi dat truoc.\n";
    }
}

// 5. TRA SACH:
//    - Tang so luong con lai
//    - Neu co nguoi trong hang doi dat truoc sach nay -> tu dong giao cho ho (dequeue)
void chucNang_TraSach(NodeSach* head, HangDoi& hangDoi) {
    cout << "\n--- TRA SACH ---\n";
    int ma = nhapSoNguyen("Nhap ma sach can tra: ");
    NodeSach* node = timTheoMa_LinearSearch(head, ma);

    if (node == nullptr) {
        cout << "Khong tim thay sach co ma " << ma << ".\n";
        return;
    }

    node->data.soLuongCon++;
    cout << "Da nhan tra sach: " << node->data.tenSach << "\n";

    // Kiem tra xem co ai dang dat truoc dung cuon sach nay khong
    // (duyet queue tu dau, ai xep hang lau nhat va dung ma sach thi uu tien truoc - FIFO)
    if (!queueRong(hangDoi)) {
        // Vi Queue chi ho tro dequeue tu dau, ta se dung 1 hang doi tam
        // de tim dung nguoi dang doi cuon sach vua tra, giu nguyen thu tu FIFO
        // cho nhung nguoi con lai.
        HangDoi tamThoi;
        khoiTaoQueue(tamThoi);
        bool daGiao = false;
        DatTruoc dt;

        while (dequeue(hangDoi, dt)) {
            if (!daGiao && dt.maSach == ma) {
                node->data.soLuongCon--; // giao ngay cho nguoi dat truoc
                cout << "Tu dong giao sach cho nguoi dat truoc: " << dt.tenNguoiDat << "\n";
                daGiao = true;
            } else {
                enqueue(tamThoi, dt); // giu lai, cho vao hang doi tam theo dung thu tu
            }
        }
        // tra hang doi da loc lai ve hang doi chinh
        hangDoi = tamThoi;
    }
}

// 6. HOAN TAC: pop phieu muon gan nhat ra khoi Stack, tra lai sach cho ke
void chucNang_HoanTacMuonSach(NodeSach* head, StackLichSu& lichSu) {
    cout << "\n--- HOAN TAC LAN MUON GAN NHAT ---\n";
    PhieuMuon pm;
    if (!pop(lichSu, pm)) {
        cout << "Khong co lan muon nao de hoan tac.\n";
        return;
    }
    NodeSach* node = timTheoMa_LinearSearch(head, pm.maSach);
    if (node != nullptr) {
        node->data.soLuongCon++;
    }
    cout << "Da hoan tac: " << pm.tenNguoiMuon << " tra lai sach \"" << pm.tenSach << "\".\n";
}

// 9. XOA SACH: xoa dong thoi khoi Linked List va khoi BST
void chucNang_XoaSach(NodeSach*& head, NodeBST*& root, HangDoi& hangDoi) {
    cout << "\n--- XOA SACH ---\n";
    int ma = nhapSoNguyen("Nhap ma sach can xoa: ");

    if (timTheoMa_LinearSearch(head, ma) == nullptr) {
        cout << "Khong tim thay sach co ma " << ma << " de xoa.\n";
        return;
    }

    root = xoaKhoiBST(root, ma);
    xoaSachKhoiDanhSach(head, ma);
    cout << "Da xoa sach co ma " << ma << " khoi thu vien.\n";
    (void)hangDoi; // tham so du phong, chua can dung toi khi xoa
}

// 7. XEM LICH SU MUON: in toan bo Stack
void chucNang_XemLichSuMuon(StackLichSu& lichSu) {
    cout << "\n--- LICH SU MUON SACH ---\n";
    hienThiStack(lichSu);
}

// 8. XEM HANG DOI DAT TRUOC: in toan bo Queue
void chucNang_XemHangDoiDatTruoc(HangDoi& hangDoi) {
    cout << "\n--- HANG DOI DAT TRUOC SACH ---\n";
    hienThiQueue(hangDoi);
}