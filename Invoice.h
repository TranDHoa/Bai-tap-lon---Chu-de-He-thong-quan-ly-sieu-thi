#include"Product.h"
#include "Customer.h"

int TyLeDoiRaDiem = 10000;
int TyLeDoiRaTien = 1000;

int random(int minN, int maxN) {
	return minN + rand() % (maxN + 1 - minN);
}
struct Date {
	int day;
	int month;
	int year;
	friend istream& operator >> (istream& is, Date& d) {
		string s;
		while (true) {
			cin >> s;
			if (s.size() == 10 && s[2] == '/' && s[5] == '/') break;
			cout << "Nhap sai dinh dang, vui long nhap lai (dd/mm/yyyy): ";
		}
		d.day = (s[0] - 48) * 10 + (s[1] - 48);
		d.month = (s[3] - 48) * 10 + (s[4] - 48);
		d.year = (s[6] - 48) * 1000 + (s[7] - 48) * 100 + (s[8] - 48) * 10 + (s[9] - 48);
		return is;
	}

	friend ostream& operator << (ostream& os, Date d) {
		cout << d.day << " / " << d.month << " / " << d.year;
		return os;
	}
};
//  HOA DON
struct Invoice {
	Date date;
	int ID;
	string Name;
	ProductManager List;
	int totalRev;
	int totalCap;
};
// Tạo danh sách liên kết đơn cho hóa đơn
struct NodeInvoice {
	Invoice info;
	NodeInvoice* next;
};
// Tạo đối tượng Quản lý hóa đơn bao gồm các thuộc tính và phương thức
class InvoiceManager {
private:
	NodeInvoice* listInvoice;
public:
	InvoiceManager() : listInvoice(NULL) {}
	void DisPlayInvoice();
	void XuatManHinh(NodeInvoice* P) {
		cout << "Ngay:\t" << P->info.date << "\n";
		P->info.List.displayProductsInvoice();
	}
	NodeInvoice* addInvoice(Date date, int id, string name, ProductManager list);
	NodeInvoice* findInvoice(int id);
	void filterInvoice();
	void Sale(CustomerManager& khach, ProductManager& kho);
	void exportInvoice(int id, ProductManager list, Date date, long long Money, long long Discount);
	void Revenue_Profit();
	void CP_History(CustomerManager list);
	int SoBatKy() {
		while (1) {
			int r = random(100000, 999999);
			if (findInvoice(r) == NULL) {
				return r;
			}
		}
	}
};
// Hiển thị danh sách tất cả các hóa đơn
void InvoiceManager::DisPlayInvoice() {
	cout << "                  ==== HOA DON ====\n" << endl;
	NodeInvoice* P = listInvoice;
	while (P != NULL) {
		cout << "ID hoa don: " << P->info.ID << "   \t\tDate: " << P->info.date << endl;
		ProductManager Q = P->info.List;
		Q.displayProductsInvoice();
		P = P->next;
	}
	getch();
}
// Thêm hóa đơn mới vào danh sách hóa đơn
NodeInvoice* InvoiceManager::addInvoice(Date date, int id, string name, ProductManager list) {
	NodeInvoice* P = new NodeInvoice;
	P->next = NULL;
	P->info.date = date;
	P->info.ID = id;
	P->info.List = list;
	P->info.Name = name;
	P->info.totalRev = list.totalAmount();
	P->info.totalCap = list.totalAmountGoc();
	if (listInvoice == NULL) {
		listInvoice = P;
		return P;
	}
	NodeInvoice* R = listInvoice;
	while (R->next != NULL) R = R->next;
	R->next = P;
	return P;
}
NodeInvoice* InvoiceManager::findInvoice(int id) {
	NodeInvoice* P = listInvoice;
	while (P != NULL) {
		if (P->info.ID == id) {
			return P;
		}
		P = P->next;
	}
	return NULL;
}
// Tìm kiếm hóa đơn theo id - id là cố định mỗi hóa đơn và được tạo ngẫu nhiên
void InvoiceManager::filterInvoice() {
	int id;
	cout << "Nhap ID hoa don can tim kiem: ";
	cin >> id;
	NodeInvoice* P = findInvoice(id);
	if (P == NULL) {
		cout << "Khong ton tai hoa don!" << endl;
		return;
	}
	cout << "ID: " << P->info.ID << "\t\t\tDate: " << P->info.date;
	ProductManager Q = P->info.List;
	cout << "\n";
	Q.displayProductsInvoice();
	getch();
	system("cls");
}

// Xuất hóa đơn cho khách hàng
void InvoiceManager::exportInvoice(int id, ProductManager list, Date date, long long money, long long discount) {
	system("cls");
	cout << "Ma hoa don :" << id << "                 " << date << endl;
	list.displayProductsInvoice();
	cout << "Giam gia : - " << discount << endl;
	cout << "Thanh tien : " << money;
	getch();
	system("cls");
}
// Thủ tục bán hàng
void InvoiceManager::Sale(CustomerManager& khach, ProductManager& kho) {
	Date date;
	int point = 0;
	cout << "Nhap ngay mua: ";
	cin >> date;
	ProductManager listBuy;
	char check;
	string sdt = "";
	NodeCustomer* P = NULL;
	char cc;
	long long discount;
	do {
		NodeProduct* Z = new NodeProduct;
		cout << "ID san pham: ";
		cin >> Z->product.id;
		NodeProduct* Q = kho.findProductById(Z->product.id);
		if (Q == NULL) {
			cout << "Khong tim thay san pham!" << endl;
			goto a;
		}
	b:
		cout << "So luong can mua: ";
		cin >> Z->product.quantity;
		if (Z->product.quantity > Q->product.quantity) {
			cout << "Vuot qua so san pham hien co!" << endl;
			cout << "Tiep tuc mua san pham? (y/n):";
			cin >> check;
			if (check == 'y') {
				goto b;
			}
			delete Z;
			goto a;
		}
		Z->product.salePrice = Q->product.salePrice;
		Z->product.name = Q->product.name;
		Z->product.purchasePrice = Q->product.purchasePrice;
		listBuy.addProduct(Z->product.id, Z->product.name, Z->product.purchasePrice, Z->product.salePrice, Z->product.quantity);
		kho.Buy(Z->product.id, Z->product.quantity);
	a:
		cout << "Tiep tuc mua san pham? (y/n): ";
		cin >> cc;
		if (cc == 'y') check = true;
		else check = false;
		cin.ignore();
	} while (check);
	cout << "Su dung tich diem? (y/n): ";
	cin >> check;
	if (check == 'y') {
		cout << "So dien thoai khach hang: ";
		cin >> sdt;
		P = khach.findCustomerByPhone(sdt);
		if (P == NULL) {
			cout << "Khach hang chua co mat tren he thong, tien hanh them moi.\n";
			P = khach.addCustomer();
		}
		khach.UpdatePoint(P->customer.phone, listBuy.totalAmount() / TyLeDoiRaDiem, 1);
		khach.filterCustomer(sdt);
	c:
		cout << "Ban co muon su dung diem (y/n): "; cin >> check;
		if (check == 'y') {
			cout << "So diem muon doi (x1000vnd): ";
			cin >> point;
			if (point > P->customer.point) {
				cout << "Vuot qua so diem hien co!" << endl;
				goto c;
			}
			khach.UpdatePoint(P->customer.phone, point, -1);
			cout << "So diem con lai : " << P->customer.point << endl;

		}
	}
	int s = SoBatKy();

	NodeInvoice* A = addInvoice(date, s, sdt, listBuy);
	A->info.totalRev = A->info.totalRev - TyLeDoiRaTien * point;
	discount = TyLeDoiRaTien * point;
	cout << "So tien phai thanh toan: " << A->info.totalRev << endl;
	exportInvoice(s, listBuy, date, A->info.totalRev, discount);
	return;
}
// Hàm xuất doanh thu, lợi nhuận theo ngày, tháng, năm
void InvoiceManager::Revenue_Profit() {
	Date d;
	int DoanhThu = 0;
	int Goc = 0;
	cout << "Nhap thoi gian can tim: "; cin >> d;
	NodeInvoice* P = listInvoice;
	while (P != NULL) {
		if ((P->info.date.day == d.day || d.day == 0) && (P->info.date.month == d.month || d.month == 0) && P->info.date.year == d.year) {
			XuatManHinh(P);
			DoanhThu += P->info.totalRev;
			Goc += P->info.totalCap;
		}
		P = P->next;
	}
	cout << "Doanh thu ";
	if (d.day != 0) cout << "ngay " << d.day << " ";
	if (d.month != 0) cout << "thang " << d.month << " ";
	cout << "nam " << d.year << " : " << DoanhThu << "\nLoi nhuan: " << DoanhThu - Goc << endl;
	getch();
	system("cls");
}
// Tìm kiếm các mặt hàng mà khách đã mua
void InvoiceManager::CP_History(CustomerManager list) {
	string id;
	char c;
a:
	cout << "Nhap ten id khach hang: "; cin >> id;
	if (list.findCustomerByPhone(id) == NULL) {
		cout << "Khong co trong danh sach khach hang!" << endl;
		cout << "Ban muon tiep tuc tim: (y/n) "; cin >> c;
		if (c == 'y') goto a; else return;

	}
	NodeInvoice* P = listInvoice;
	while (P != NULL) {
		if (!id.compare(P->info.Name)) {
			XuatManHinh(P);
		}
		P = P->next;
	}
	getch();
	system("cls");
}

