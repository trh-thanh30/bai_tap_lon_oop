#include <iostream>
#include <iomanip> // để xuất bảng đẹp
using namespace std;

const int MAX = 100; // số lượng tối đa sản phẩm/phiếu/nhân viên

class ChefStaff
{
public:
    string staffId, name, phone;
    void input()
    {
        cout << "Nhap ma nhan vien: ";
        getline(cin, staffId);
        cout << "Nhap ten nhan vien: ";
        getline(cin, name);
        cout << "Nhap so dien thoai: ";
        getline(cin, phone);
    }
    void display()
    {
        cout << left << setw(15) << staffId
             << setw(20) << name
             << setw(15) << phone << endl;
    }
};

class Product
{
public:
    string productId, productName, expiryDate;
    void input()
    {
        cout << "Nhap ma san pham: ";
        getline(cin, productId);
        cout << "Nhap ten san pham: ";
        getline(cin, productName);
        cout << "Nhap han su dung (dd/mm/yyyy): ";
        getline(cin, expiryDate);
    }
    void display()
    {
        cout << left << setw(15) << productId
             << setw(20) << productName
             << setw(15) << expiryDate;
    }
};

class ProductItem
{
public:
    Product product;
    int quantity;
    double unitPrice;

    void input(bool isImport = true)
    {
        product.input();
        cout << "Nhap so luong: ";
        cin >> quantity;
        cin.ignore();
        if (isImport)
        {
            cout << "Nhap don gia: ";
            cin >> unitPrice;
            cin.ignore();
        }
        else
        {
            unitPrice = 0; // khi xuat kho khong can don gia
        }
    }

    void display(bool isImport = true)
    {
        product.display();
        cout << setw(10) << quantity;
        if (isImport)
            cout << setw(15) << fixed << setprecision(2) << unitPrice;
        cout << endl;
    }
};

class Supplier
{
public:
    string supplierName, supplierId, address, phone;

    void input()
    {
        cout << "Nhap ma NCC: ";
        getline(cin, supplierId);
        cout << "Nhap ten NCC: ";
        getline(cin, supplierName);
        cout << "Nhap dia chi: ";
        getline(cin, address);
        cout << "Nhap so dien thoai: ";
        getline(cin, phone);
    }

    void display()
    {
        cout << left << setw(15) << supplierId
             << setw(20) << supplierName
             << setw(30) << address
             << setw(15) << phone << endl;
    }
};

class ImportReceipt
{
public:
    string invoiceNumber, deliveryDate;
    Supplier supplier;
    ProductItem items[MAX];
    int itemCount;

    void input()
    {
        cout << "Nhap so hoa don: ";
        getline(cin, invoiceNumber);
        cout << "Nhap ngay giao hang (dd/mm/yyyy): ";
        getline(cin, deliveryDate);
        cout << "Nhap thong tin nha cung cap:\n";
        supplier.input();
        cout << "Nhap so luong mat hang: ";
        cin >> itemCount;
        cin.ignore();
        for (int i = 0; i < itemCount; i++)
        {
            cout << "\nNhap mat hang thu " << i + 1 << ":\n";
            items[i].input(true);
        }
    }

    void display()
    {
        cout << "\n===== HOA DON NHAP KHO =====\n";
        cout << "So hoa don: " << invoiceNumber << "\nNgay giao: " << deliveryDate << endl;
        cout << "Nha cung cap:\n";
        supplier.display();
        cout << "\nDanh sach hang nhap:\n";
        cout << left << setw(15) << "Ma SP"
             << setw(20) << "Ten SP"
             << setw(15) << "HSD"
             << setw(10) << "So luong"
             << setw(15) << "Don gia" << endl;
        for (int i = 0; i < itemCount; i++)
        {
            items[i].display(true);
        }
    }
};

class ExportReceipt
{
public:
    string receiptNumber, exportDate, reason;
    ChefStaff staff;
    ProductItem items[MAX];
    int itemCount;

    void input()
    {
        cout << "Nhap so phieu xuat: ";
        getline(cin, receiptNumber);
        cout << "Nhap ngay xuat (dd/mm/yyyy): ";
        getline(cin, exportDate);
        cout << "Nhap ly do xuat kho: ";
        getline(cin, reason);
        cout << "Nhap thong tin nhan vien nhan hang:\n";
        staff.input();
        cout << "Nhap so luong mat hang xuat: ";
        cin >> itemCount;
        cin.ignore();
        for (int i = 0; i < itemCount; i++)
        {
            cout << "\nNhap mat hang thu " << i + 1 << ":\n";
            items[i].input(false);
        }
    }

    void display()
    {
        cout << "\n===== PHIEU XUAT KHO =====\n";
        cout << "So phieu: " << receiptNumber << "\nNgay xuat: " << exportDate << "\nLy do: " << reason << endl;
        cout << "Nhan vien nhan:\n";
        staff.display();
        cout << "\nDanh sach hang xuat:\n";
        cout << left << setw(15) << "Ma SP"
             << setw(20) << "Ten SP"
             << setw(15) << "HSD"
             << setw(10) << "So luong" << endl;
        for (int i = 0; i < itemCount; i++)
        {
            items[i].display(false);
        }
    }
};

void showMenu()
{
    cout << "\n=========== MENU ==========\n";
    cout << "1. Nhap hoa don nhap kho\n";
    cout << "2. Xuat hoa don nhap kho\n";
    cout << "3. Nhap phieu xuat kho\n";
    cout << "4. Xuat phieu xuat kho\n";
    cout << "0. Thoat\n";
    cout << "============================\n";
    cout << "Chon chuc nang: ";
}

int main()
{
    ImportReceipt importReceipts[MAX];
    ExportReceipt exportReceipts[MAX];
    int importCount = 0, exportCount = 0;
    int choice;

    do
    {
        showMenu();
        cin >> choice;
        cin.ignore(); // bỏ ký tự '\n' còn lại

        switch (choice)
        {
        case 1:
            importReceipts[importCount++].input();
            break;
        case 2:
            for (int i = 0; i < importCount; i++)
            {
                importReceipts[i].display();
            }
            break;
        case 3:
            exportReceipts[exportCount++].input();
            break;
        case 4:
            for (int i = 0; i < exportCount; i++)
            {
                exportReceipts[i].display();
            }
            break;
        case 0:
            cout << "Thoat chuong trinh.\n";
            break;
        default:
            cout << "Lua chon khong hop le. Thu lai.\n";
            break;
        }
    } while (choice != 0);

    return 0;
}
