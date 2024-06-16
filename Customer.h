#include"Thuvien.h"
struct Customer {
    string phone;
    string name;
    long point;
};
// Tạo danh sách liên kết đơn cho tập khách hàng
struct NodeCustomer {
    Customer customer;
    NodeCustomer* next;
};
// Tạo đối tượng Quản lý khách hàng, khai báo các thuộc tính và phương thức hàm(thêm, tìm kiếm, cập nhật, xóa, lọc) và khởi tạo danh sách liên kết rỗng
typedef NodeCustomer* CustomerList;
class CustomerManager {
private:
    CustomerList C;
    int sizeList;
public:
    CustomerManager() : C(NULL), sizeList(0) {}
    NodeCustomer* addCustomer();
    int getSizeList() const { return sizeList; }
    void updateCustomer(const string& phone);
    void deleteCustomer(const string& phone);
    NodeCustomer* findCustomerByPhone(const string& phone);
    void displayCustomers() const;
    void filterCustomer(string phone);
    void UpdatePoint(const string& phone, int point, int status);
};
// Thêm khách hàng
NodeCustomer* CustomerManager::addCustomer() {
    NodeCustomer* P = new NodeCustomer;
    cout << "Moi ban nhap thong tin khach hang: \n\n";
    cout << "So dien thoai: ";
    cin >> P->customer.phone;
    cin.ignore();
    cout << "Ten khach hang: ";
    getline(cin, P->customer.name);
    P->customer.point = 0;
    P->next = NULL;
    if (C == NULL) {
        C = P;
    }
    else {
        NodeCustomer* R = C;
        while (R->next != NULL) R = R->next;
        R->next = P;
    }
    sizeList++;
    return P;

}
// Tìm khách hàng bằng số điện thoại và trả về địa chỉ node đó
NodeCustomer* CustomerManager::findCustomerByPhone(const string& phone) {
    NodeCustomer* P = C;
    while (P != NULL) {
        if (P->customer.phone == phone) return P;
        else P = P->next;
    }
    return NULL;
}

// Hàm lọc khách hàng theo số điện thoại
void CustomerManager::filterCustomer(string phone) {
    NodeCustomer* P = findCustomerByPhone(phone);
    if (P == NULL) {
        cout << "Khong tim thay khach hang!" << endl;
    }
    else {
        cout << left << setw(15) << "So dien thoai" << setw(30) << "Ten khach hang" << setw(10) << "Diem tich luy" << endl;
        cout << left << setw(15) << "--------------" << setw(30) << "----------------------------" << setw(10) << "--------" << endl;
        cout << left << setw(15) << P->customer.phone << setw(30) << P->customer.name << setw(10) << P->customer.point << endl;
    }
}

// Hàm cập nhật thông tin khách hàng
void CustomerManager::updateCustomer(const string& phone) {
    cin.ignore();
    NodeCustomer* Q = findCustomerByPhone(phone);
    if (Q == NULL) {
        cout << "Khong tim thay khach hang!" << endl;
    }
    else {
        cout << "So dien thoai: ";
        getline(cin, Q->customer.phone);
        cout << "Ten khach hang: ";
        getline(cin, Q->customer.name);
        // cout << "Enter Customer Points: ";
        // cin >> Q->customer.point;
    }
}

// Hàm xóa khách hàng khỏi danh sách
void CustomerManager::deleteCustomer(const string& phone) {
    if (C == NULL) return;

    NodeCustomer* P = C;
    NodeCustomer* prev = NULL;

    // Tìm kiếm khách hàng bằng sđt
    while (P != NULL && P->customer.phone != phone) {
        prev = P;
        P = P->next;
    }
    if (P == NULL) {
        cout << "Khong tim thay khach hang!" << endl;
        return;
    }

    // Nếu khách hàng là đầu danh sách
    if (prev == NULL) {
        C = P->next;
    }
    else {
        prev->next = P->next;
    }

    delete P;
    sizeList--;
    cout << "Da xoa khach hang!  " << P->customer.name << endl;
}
// Hàm hiển thị thông tin khách hàng
void CustomerManager::displayCustomers() const {
    cout << "               ==== KHACH HANG ====\n" << endl;
    NodeCustomer* P = C;
    cout << left << setw(15) << "So dien thoai" << setw(30) << "Ten khach hang" << setw(10) << "Diem tich luy" << endl;
    cout << left << setw(15) << "--------------" << setw(30) << "----------------------------" << setw(10) << "--------" << endl;
    while (P != NULL) {
        cout << left << setw(15) << P->customer.phone << setw(30) << P->customer.name << setw(10) << P->customer.point << endl;
        P = P->next;
    }
    cout << "\nSo luong:  " << getSizeList() << endl;
}
// Hàm cập nhật số điểm tích lũy hiện tại của khách
void CustomerManager::UpdatePoint(const string& phone, int point, int status) {
    NodeCustomer* Q = findCustomerByPhone(phone);
    if (Q == NULL) {
        cout << "Khong tim thay khach hang!" << endl;
        return;
    }
    Q->customer.point += status * point;
}
