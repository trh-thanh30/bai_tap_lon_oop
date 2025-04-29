#include <iostream>
#include <string>
#include <regex>
#include <iomanip>
using namespace std;

// Ham kiem tra dinh dang so dien thoai
bool isValidPhoneNumber(const string &phone_number)
{
    regex phone_regex("^0[0-9]{9}$"); // Bat dau bang 0, theo sau la 9 chu so
    return regex_match(phone_number, phone_regex);
}

// Lop yeu cau cua nhan vien
class InventoryRequest
{
private:
    string productName;
    int quantityRequested;

public:
    InventoryRequest(string productName = "", int quantityRequested = 0)
    {
        this->productName = productName;
        this->quantityRequested = quantityRequested;
    }
    ~InventoryRequest() {}
    void Setter()
    {
        do
        {
            cout << "Nhap ten san pham: ";
            cin.ignore();
            getline(cin, this->productName);
            if (this->productName.empty())
            {
                cout << "Ten san pham la bat buoc" << endl;
            }
        } while (this->productName.empty());
        do
        {
            cout << "Nhap so luong san pham: ";
            cin >> this->quantityRequested;
            if (this->quantityRequested < 0)
            {
                cout << "So luong khong hop le" << endl;
            }
        } while (this->quantityRequested < 0);
    }
    void Getter()
    {
        cout << left;
        cout << setw(20) << this->productName << setw(20) << this->quantityRequested << endl;
    }
    string getProductName()
    {
        return this->productName;
    }
    int getQuantity()
    {
        return this->quantityRequested;
    }
};

// Lop nhan vien dau bep
class Chef_Staff
{
private:
    string name, id, phone_number;
    int requestCount; // So luong yeu cau
public:
    InventoryRequest requests[10]; // Mang luu tru cac yeu cau
    Chef_Staff(string name = "", string id = "", string phone_number = "")
    {
        this->name = name;
        this->id = id;
        this->phone_number = phone_number;
        this->requestCount = 0;
    }
    ~Chef_Staff() {}
    InventoryRequest getRequest(int index)
    {
        return requests[index];
    }
    void Setter()
    {
        cin.ignore();
        do
        {
            cout << "Nhap ID cua ban: ";
            getline(cin, id);
            if (id.empty())
                cout << "ID la bat buoc.\n";
        } while (id.empty());

        do
        {
            cout << "Nhap ten cua ban: ";
            getline(cin, name);
            if (name.empty())
                cout << "Ten la bat buoc.\n";
        } while (name.empty());

        do
        {
            cout << "Nhap so dien thoai (Vi du: 0901234567): ";
            getline(cin, phone_number);
            if (!isValidPhoneNumber(phone_number))
                cout << "So dien thoai khong hop le. So dien thoai phai co 10 so\n";
        } while (!isValidPhoneNumber(phone_number));
    }

    void Getter()
    {
        cout << left;
        cout << setw(10) << id << setw(20) << name << setw(20) << phone_number << endl;
    }

    string getId()
    {
        return this->id;
    }

    string getName()
    {
        return this->name;
    }

    int getRequestCount()
    {
        return requestCount;
    }

    void RequestToInventory(int numberProduct)
    {
        for (int i = 0; i < numberProduct; i++)
        {
            cout << "Tao yeu cau san pham #" << i + 1 << ": \n";
            requests[requestCount].Setter();
            requestCount++;
        }
    }

    void ShowRequests()
    {
        cout << left;
        cout << "\nYeu cau cua Dau bep ID: " << id << " - " << name << endl;
        cout << setw(20) << "Ten san pham" << setw(20) << "So luong" << endl;
        cout << string(40, '-') << endl;

        for (int i = 0; i < requestCount; i++)
        {
            requests[i].Getter();
        }
        cout << string(40, '-') << endl;
    }
};

// Lop san pham
class Product
{
protected:
    string productId, productName;
    int quantity;
    double price;
    // Ngay het han su dung
    int expiryDay, expiryMonth, expiryYear;

public:
    Product(string productId = "", string productName = "", int quantity = 0, double price = 0.0,
            int expiryDay = 0, int expiryMonth = 0, int expiryYear = 0)
    {
        this->productId = productId;
        this->productName = productName;
        this->quantity = quantity;
        this->price = price;
        this->expiryDay = expiryDay;
        this->expiryMonth = expiryMonth;
        this->expiryYear = expiryYear;
    }
    ~Product() {}

    void Setter()
    {
        cin.ignore();
        do
        {
            cout << "Nhap ma san pham: ";
            getline(cin, this->productId);
            if (this->productId.empty())
            {
                cout << "Ma san pham la bat buoc.\n";
            }
        } while (this->productId.empty());

        do
        {
            cout << "Nhap ten san pham: ";
            getline(cin, this->productName);
            if (this->productName.empty())
            {
                cout << "Ten san pham la bat buoc.\n";
            }
        } while (this->productName.empty());

        do
        {
            cout << "Nhap gia san pham: ";
            cin >> this->price;
            if (this->price < 0 || cin.fail())
            {
                cout << "Gia khong hop le. Vui long nhap mot so thuc \n";
                cin.clear();
                cin.ignore(10000, '\n'); // Xoa bo dem dau vao
            }
            else
            {
                break;
            }
        } while (true);

        cout << "Nhap so luong san pham: ";
        cin >> this->quantity;

        // Nhap thong tin han su dung
        cout << "Nhap han su dung (dd mm yyyy): ";
        cin >> this->expiryDay >> this->expiryMonth >> this->expiryYear;
    }

    void Getter()
    {
        cout << left;
        cout << setw(10) << productId << setw(20) << productName << setw(15) << quantity
             << setw(15) << price << setw(15) << expiryDay << "/" << expiryMonth << "/" << expiryYear << endl;
    }

    string getProductId()
    {
        return this->productId;
    }

    string getProductName()
    {
        return this->productName;
    }

    int getQuantity()
    {
        return this->quantity;
    }

    double getPrice()
    {
        return this->price;
    }

    void setQuantity(int newQuantity)
    {
        this->quantity = newQuantity;
    }

    string getExpiryDate()
    {
        return to_string(expiryDay) + "/" + to_string(expiryMonth) + "/" + to_string(expiryYear);
    }
};

// Lop don dat hang
class PurchaseOrder
{
private:
    string orderId;
    int orderDay, orderMonth, orderYear;
    int requiredDay, requiredMonth, requiredYear; // Thoi diem can nhan hang
    string supplierId;
    int totalItems;

public:
    struct OrderItem
    {
        string productId;
        string productName;
        int quantity;
    };

    OrderItem orderItems[10];
    PurchaseOrder(string orderId = "", int orderDay = 0, int orderMonth = 0, int orderYear = 0,
                  int requiredDay = 0, int requiredMonth = 0, int requiredYear = 0,
                  string supplierId = "")
    {
        this->orderId = orderId;
        this->orderDay = orderDay;
        this->orderMonth = orderMonth;
        this->orderYear = orderYear;
        this->requiredDay = requiredDay;
        this->requiredMonth = requiredMonth;
        this->requiredYear = requiredYear;
        this->supplierId = supplierId;
        this->totalItems = 0;
    }

    ~PurchaseOrder() {}

    string getSupplierId()
    {
        return this->supplierId;
    }

    void Setter()
    {
        cin.ignore();
        do
        {
            cout << "Nhap ma don dat hang: ";
            getline(cin, this->orderId);
            if (this->orderId.empty())
            {
                cout << "Ma don dat hang la bat buoc.\n";
            }
        } while (this->orderId.empty());

        cout << "Nhap ngay dat hang (dd mm yyyy): ";
        cin >> this->orderDay >> this->orderMonth >> this->orderYear;

        cout << "Nhap ngay can giao hang (dd mm yyyy): ";
        cin >> this->requiredDay >> this->requiredMonth >> this->requiredYear;
        cin.ignore();

        do
        {
            cout << "Nhap ma nha cung cap: ";
            getline(cin, this->supplierId);
            if (this->supplierId.empty())
            {
                cout << "Ma nha cung cap la bat buoc.\n";
            }
        } while (this->supplierId.empty());
    }

    void addOrderItem(string productId, string productName, int quantity)
    {
        orderItems[totalItems].productId = productId;
        orderItems[totalItems].productName = productName;
        orderItems[totalItems].quantity = quantity;
        totalItems++;
    }

    void Getter()
    {
        cout << "\n======= CHI TIET DON DAT HANG =======\n";
        cout << "Ma don: " << orderId << endl;
        cout << "Ngay dat: " << orderDay << "/" << orderMonth << "/" << orderYear << endl;
        cout << "Ngay can giao hang: " << requiredDay << "/" << requiredMonth << "/" << requiredYear << endl;
        cout << "Ma nha cung cap: " << supplierId << endl;
        cout << "\nCac mat hang dat:\n";
        cout << left;
        cout << setw(10) << "Ma SP" << setw(20) << "Ten san pham" << setw(15) << "So luong" << endl;
        cout << string(45, '-') << endl;

        for (int i = 0; i < totalItems; i++)
        {
            cout << setw(10) << orderItems[i].productId
                 << setw(20) << orderItems[i].productName
                 << setw(15) << orderItems[i].quantity << endl;
        }
        cout << string(45, '-') << endl;
    }

    string getOrderId()
    {
        return this->orderId;
    }

    string getRequiredDate()
    {
        return to_string(requiredDay) + "/" + to_string(requiredMonth) + "/" + to_string(requiredYear);
    }

    int getTotalItems()
    {
        return totalItems;
    }

    OrderItem getOrderItem(int index)
    {
        if (index >= 0 && index < totalItems)
            return orderItems[index];

        // Return empty item if index is out of bounds
        OrderItem emptyItem = {"", "", 0};
        return emptyItem;
    }
};

// Lop hoa don
class Invoice
{
private:
    string idInvoice;
    int day, month, year; // ngay giao hang

    // Thông tin nhà cung cấp
    string supplierId;
    string supplierName;
    string supplierPhone;
    string supplierAddress;

    // Sử dụng cấu trúc để lưu chi tiết sản phẩm
    struct InvoiceItem
    {
        string productId;
        string productName;
        int quantity;
        double price;
    };

    InvoiceItem items[10]; // Mảng các mặt hàng trong hóa đơn
    int totalItems;

public:
    Invoice(string idInvoice = "", int day = 0, int month = 0, int year = 0,
            string supplierId = "", string supplierName = "",
            string supplierPhone = "", string supplierAddress = "")
    {
        this->idInvoice = idInvoice;
        this->day = day;
        this->month = month;
        this->year = year;
        this->supplierId = supplierId;
        this->supplierName = supplierName;
        this->supplierPhone = supplierPhone;
        this->supplierAddress = supplierAddress;
        this->totalItems = 0;
    }

    ~Invoice() {}

    void Setter()
    {
        cout << "Nhap thong tin hoa don:\n";
        cin.ignore();

        cout << "Nhap ma hoa don: ";
        getline(cin, this->idInvoice);

        cout << "Nhap ngay giao hang (dd mm yyyy): ";
        cin >> this->day >> this->month >> this->year;

        cin.ignore();
        cout << "Nhap ma nha cung cap: ";
        getline(cin, this->supplierId);

        cout << "Nhap ten nha cung cap: ";
        getline(cin, this->supplierName);

        cout << "Nhap so dien thoai nha cung cap: ";
        getline(cin, this->supplierPhone);

        cout << "Nhap dia chi nha cung cap: ";
        getline(cin, this->supplierAddress);

        // Nhập thông tin các mặt hàng
        int numItems;
        cout << "Nhap so luong mat hang: ";
        cin >> numItems;

        for (int i = 0; i < numItems; i++)
        {
            cin.ignore();
            cout << "\nMat hang #" << (i + 1) << ":\n";

            cout << "Nhap ma san pham: ";
            getline(cin, items[totalItems].productId);

            cout << "Nhap ten san pham: ";
            getline(cin, items[totalItems].productName);

            cout << "Nhap so luong: ";
            cin >> items[totalItems].quantity;

            cout << "Nhap gia: ";
            cin >> items[totalItems].price;

            totalItems++;
        }
    }

    void addItem(string productId, string productName, int quantity, double price)
    {
        items[totalItems].productId = productId;
        items[totalItems].productName = productName;
        items[totalItems].quantity = quantity;
        items[totalItems].price = price;
        totalItems++;
    }

    void Getter()
    {
        cout << "\n======= CHI TIET HOA DON =======\n";
        cout << "Ma hoa don: " << idInvoice << endl;
        cout << "Ngay: " << day << "/" << month << "/" << year << endl;
        cout << "Ma nha cung cap: " << supplierId << endl;
        cout << "Ten nha cung cap: " << supplierName << endl;
        cout << "So dien thoai: " << supplierPhone << endl;
        cout << "Dia chi: " << supplierAddress << endl;

        cout << "\nDanh sach san pham:\n";
        cout << left;
        cout << setw(10) << "Ma SP" << setw(20) << "Ten san pham"
             << setw(10) << "So luong" << setw(10) << "Gia" << setw(15) << "Thanh tien" << endl;
        cout << string(65, '-') << endl;

        double grandTotal = 0;

        for (int i = 0; i < totalItems; i++)
        {
            double total = items[i].quantity * items[i].price;
            grandTotal += total;

            cout << setw(10) << items[i].productId
                 << setw(20) << items[i].productName
                 << setw(10) << items[i].quantity
                 << setw(10) << items[i].price
                 << setw(15) << total << endl;
        }

        cout << string(65, '-') << endl;
        cout << "Tong cong: " << grandTotal << endl;
    }

    string getIdInvoice()
    {
        return this->idInvoice;
    }

    string getSupplierId()
    {
        return this->supplierId;
    }

    string getDate()
    {
        return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
    }

    // Chuyển đổi hóa đơn thành mảng sản phẩm
    int getProductsFromInvoice(Product products[])
    {
        for (int i = 0; i < totalItems; i++)
        {
            // Tạo sản phẩm từ thông tin trong hóa đơn
            // Giả sử hạn sử dụng là 1 năm kể từ ngày nhập
            products[i] = Product(
                items[i].productId,
                items[i].productName,
                items[i].quantity,
                items[i].price,
                day,
                month,
                year + 1 // Hạn sử dụng 1 năm sau ngày nhập
            );
        }

        return totalItems;
    }
};

// Lop phieu xuat kho
class ExportInvoice
{
private:
    string invoiceId;
    int day, month, year;
    string reason;
    string chefId; // Ma so nhan vien dau bep nhan hang

    // Su dung cau truc de luu chi tiet san pham xuat kho
    struct ExportItem
    {
        string productId;
        string productName;
        int quantity;
    };

    ExportItem exportItems[10]; // Mang luu cac mat hang xuat
    int totalItems;

public:
    ExportInvoice(string invoiceId = "", int day = 0, int month = 0, int year = 0, string reason = "", string chefId = "")
    {
        this->invoiceId = invoiceId;
        this->day = day;
        this->month = month;
        this->year = year;
        this->reason = reason;
        this->chefId = chefId;
        this->totalItems = 0;
    }

    ~ExportInvoice() {}

    void Setter()
    {
        cin.ignore();
        do
        {
            cout << "Nhap ma phieu xuat kho: ";
            getline(cin, this->invoiceId);
            if (this->invoiceId.empty())
            {
                cout << "Ma phieu xuat kho la bat buoc.\n";
            }
        } while (this->invoiceId.empty());

        cout << "Nhap ngay xuat (dd mm yyyy): ";
        cin >> this->day >> this->month >> this->year;
        cin.ignore();

        cout << "Nhap ly do xuat kho: ";
        getline(cin, this->reason);

        do
        {
            cout << "Nhap ma dau bep nhan hang: ";
            getline(cin, this->chefId);
            if (this->chefId.empty())
            {
                cout << "Ma dau bep la bat buoc.\n";
            }
        } while (this->chefId.empty());
    }

    void addExportItem(string productId, string productName, int quantity)
    {
        exportItems[totalItems].productId = productId;
        exportItems[totalItems].productName = productName;
        exportItems[totalItems].quantity = quantity;
        totalItems++;
    }

    void Getter()
    {
        cout << "\n======= CHI TIET PHIEU XUAT KHO =======\n";
        cout << "Ma phieu: " << invoiceId << endl;
        cout << "Ngay: " << day << "/" << month << "/" << year << endl;
        cout << "Ly do: " << reason << endl;
        cout << "Ma dau bep: " << chefId << endl;
        cout << "\nSan pham xuat kho:\n";
        cout << left;
        cout << setw(10) << "Ma SP" << setw(20) << "Ten san pham" << setw(15) << "So luong" << endl;
        cout << string(45, '-') << endl;

        for (int i = 0; i < totalItems; i++)
        {
            cout << setw(10) << exportItems[i].productId
                 << setw(20) << exportItems[i].productName
                 << setw(15) << exportItems[i].quantity << endl;
        }
        cout << string(45, '-') << endl;
    }

    string getInvoiceId()
    {
        return this->invoiceId;
    }

    string getChefId()
    {
        return this->chefId;
    }

    string getDate()
    {
        return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
    }

    int getTotalItems()
    {
        return totalItems;
    }

    ExportItem getExportItem(int index)
    {
        if (index >= 0 && index < totalItems)
            return exportItems[index];

        // Return empty item if index is out of bounds
        ExportItem emptyItem = {"", "", 0};
        return emptyItem;
    }
};

// Lop ho so xuat kho
class ExportRecord
{
private:
    ExportInvoice exportInvoices[10]; // Luu toi da 10 phieu xuat
    int totalInvoices;

public:
    ExportRecord()
    {
        totalInvoices = 0;
    }

    ~ExportRecord() {}

    void addExportInvoice(ExportInvoice invoice)
    {
        exportInvoices[totalInvoices] = invoice;
        totalInvoices++;
    }

    void showAllExportInvoices()
    {
        if (totalInvoices == 0)
        {
            cout << "Khong co phieu xuat kho nao.\n";
            return;
        }

        cout << "\n====== DANH SACH PHIEU XUAT KHO ======\n";
        cout << left;
        cout << setw(15) << "Ma phieu" << setw(15) << "Ngay xuat" << setw(15) << "Ma dau bep" << endl;
        cout << string(45, '-') << endl;

        for (int i = 0; i < totalInvoices; i++)
        {
            cout << setw(15) << exportInvoices[i].getInvoiceId()
                 << setw(15) << exportInvoices[i].getDate()
                 << setw(15) << exportInvoices[i].getChefId() << endl;
        }
        cout << string(45, '-') << endl;
    }

    void showExportInvoiceDetails(string invoiceId)
    {
        for (int i = 0; i < totalInvoices; i++)
        {
            if (exportInvoices[i].getInvoiceId() == invoiceId)
            {
                exportInvoices[i].Getter();
                return;
            }
        }
        cout << "Khong tim thay phieu xuat voi ma: " << invoiceId << ".\n";
    }

    int getTotalExports()
    {
        return totalInvoices;
    }

    ExportInvoice getExportInvoice(int index)
    {
        if (index >= 0 && index < totalInvoices)
            return exportInvoices[index];

        // Return empty invoice if index is out of bounds
        return ExportInvoice();
    }
};

// Lop ho so nhap kho
class ImportRecord
{
private:
    Invoice importInvoices[10]; // Luu toi da 10 phieu nhap kho
    int totalInvoices;

public:
    ImportRecord()
    {
        totalInvoices = 0;
    }

    ~ImportRecord() {}

    void addImportInvoice(Invoice invoice)
    {
        importInvoices[totalInvoices] = invoice;
        totalInvoices++;
    }

    void showAllImportInvoices()
    {
        if (totalInvoices == 0)
        {
            cout << "Khong co phieu nhap kho nao.\n";
            return;
        }

        cout << "\n====== DANH SACH PHIEU NHAP KHO ======\n";
        cout << left;
        cout << setw(15) << "Ma phieu" << setw(15) << "Ngay nhap" << setw(15) << "Ma nha cung cap" << endl;
        cout << string(45, '-') << endl;

        for (int i = 0; i < totalInvoices; i++)
        {
            cout << setw(15) << importInvoices[i].getIdInvoice()
                 << setw(15) << importInvoices[i].getDate()
                 << setw(15) << importInvoices[i].getSupplierId() << endl;
        }
        cout << string(45, '-') << endl;
    }

    void showImportInvoiceDetails(string invoiceId)
    {
        for (int i = 0; i < totalInvoices; i++)
        {
            if (importInvoices[i].getIdInvoice() == invoiceId)
            {
                importInvoices[i].Getter();
                return;
            }
        }
        cout << "Khong tim thay phieu nhap kho voi ma: " << invoiceId << ".\n";
    }

    int getTotalImports()
    {
        return totalInvoices;
    }

    Invoice getImportInvoice(int index)
    {
        if (index >= 0 && index < totalInvoices)
            return importInvoices[index];

        // Return empty invoice if index is out of bounds
        return Invoice();
    }
};

// Lop nha cung cap
class Supplier
{
protected:
    string nameSupplier, phoneSupplier, addressSupplier, idSupplier;
    Product products[10]; // Mang chua toi da 10 san pham

public:
    int totalProducts = 0;

    Supplier(string nameSupplier = "", string phoneSupplier = "", string addressSupplier = "", string idSupplier = "")
    {
        this->idSupplier = idSupplier;
        this->nameSupplier = nameSupplier;
        this->phoneSupplier = phoneSupplier;
        this->addressSupplier = addressSupplier;
    }

    ~Supplier() {}

    void Setter()
    {
        cin.ignore();
        do
        {
            cout << "Nhap ma nha cung cap: ";
            getline(cin, this->idSupplier);
            if (this->idSupplier.empty())
            {
                cout << "Ma nha cung cap la bat buoc.\n";
            }
        } while (this->idSupplier.empty());

        do
        {
            cout << "Nhap ten nha cung cap: ";
            getline(cin, this->nameSupplier);
            if (this->nameSupplier.empty())
            {
                cout << "Ten nha cung cap la bat buoc.\n";
            }
        } while (this->nameSupplier.empty());

        do
        {
            cout << "Nhap so dien thoai: ";
            getline(cin, this->phoneSupplier);
            if (!isValidPhoneNumber(this->phoneSupplier) || this->phoneSupplier.empty())
            {
                cout << "So dien thoai khong hop le\n";
            }
        } while (this->phoneSupplier.empty() || !isValidPhoneNumber(this->phoneSupplier));

        cout << "Nhap dia chi: ";
        getline(cin, this->addressSupplier);
    }

    void Getter()
    {
        cout << left;
        cout << setw(10) << this->idSupplier << setw(20) << this->nameSupplier
             << setw(20) << this->phoneSupplier << setw(20) << this->addressSupplier << endl;
    }

    void createProduct(int length)
    {
        for (int i = 0; i < length; i++)
        {
            cout << "Tao san pham #" << i + 1 << ":\n";
            products[totalProducts].Setter();
            totalProducts++;
        }
    }

    void showProducts()
    {
        cout << left;
        cout << setw(10) << "Ma SP" << setw(20) << "Ten san pham" << setw(20) << "So luong" << setw(20) << "Gia" << endl;
        cout << string(70, '-') << endl;

        for (int i = 0; i < totalProducts; i++)
        {
            products[i].Getter();
        }
        cout << string(70, '-') << endl;
    }

    void viewPurchaseOrders(PurchaseOrder orders[], int totalOrders)
    {
        bool foundOrders = false;
        cout << "\n====== DON DAT HANG CHO " << nameSupplier << " ======\n";

        for (int i = 0; i < totalOrders; i++)
        {
            if (orders[i].getSupplierId() == idSupplier)
            {
                orders[i].Getter();
                foundOrders = true;
            }
        }

        if (!foundOrders)
        {
            cout << "Khong co don dat hang nao cho nha cung cap nay.\n";
        }
    }

    // Xu ly don dat hang va tao hoa don
    Invoice processOrder(string orderId, PurchaseOrder orders[], int totalOrders)
    {
        Invoice newInvoice;
        bool orderFound = false;

        // Tim don hang
        for (int i = 0; i < totalOrders; i++)
        {
            if (orders[i].getOrderId() == orderId && orders[i].getSupplierId() == idSupplier)
            {
                orderFound = true;

                // Tao hoa don tu don hang
                string invoiceId;
                int day, month, year;

                cout << "\nDang xu ly don hang: " << orderId << endl;

                cin.ignore();
                cout << "Nhap ma hoa don giao hang: ";
                getline(cin, invoiceId);

                cout << "Nhap ngay giao hang (dd mm yyyy): ";
                cin >> day >> month >> year;

                // Khoi tao hoa don voi thong tin nha cung cap
                newInvoice = Invoice(
                    invoiceId, day, month, year,
                    idSupplier, nameSupplier, phoneSupplier, addressSupplier);

                // Them san pham tu danh sach vao hoa don
                for (int j = 0; j < orders[i].getTotalItems(); j++)
                {
                    PurchaseOrder::OrderItem orderItem = orders[i].getOrderItem(j);

                    // Tim san pham trong danh muc nha cung cap
                    for (int k = 0; k < totalProducts; k++)
                    {
                        if (products[k].getProductId() == orderItem.productId ||
                            products[k].getProductName() == orderItem.productName)
                        {
                            // Them san pham vao hoa don
                            newInvoice.addItem(
                                products[k].getProductId(),
                                products[k].getProductName(),
                                orderItem.quantity,
                                products[k].getPrice());
                            break;
                        }
                    }
                }

                cout << "\nDon hang " << orderId << " da duoc xu ly thanh cong.\n";
                newInvoice.Getter(); // Hien thi thong tin hoa don
                break;
            }
        }

        if (!orderFound)
        {
            cout << "Khong tim thay don hang hoac don hang khong thuoc nha cung cap nay.\n";
        }

        return newInvoice;
    }

    // Phuong thuc de chon san pham tu danh muc cua nha cung cap
    void selectProductsForOrder(string orderId, PurchaseOrder orders[], int totalOrders)
    {
        bool orderFound = false;

        // Tim don hang
        for (int i = 0; i < totalOrders; i++)
        {
            if (orders[i].getOrderId() == orderId && orders[i].getSupplierId() == idSupplier)
            {
                orderFound = true;
                cout << "\nDang chon san pham cho don hang " << orderId << endl;

                // Hien thi danh sach san pham cua nha cung cap
                showProducts();

                // Tao hoa don moi
                string invoiceId;
                int day, month, year;

                cin.ignore();
                cout << "Nhap ma hoa don giao hang: ";
                getline(cin, invoiceId);

                cout << "Nhap ngay giao hang (dd mm yyyy): ";
                cin >> day >> month >> year;

                Invoice newInvoice(
                    invoiceId, day, month, year,
                    idSupplier, nameSupplier, phoneSupplier, addressSupplier);

                // Cho phep nguoi dung chon san pham
                int numProducts;
                cout << "Nhap so luong san pham muon them: ";
                cin >> numProducts;

                for (int j = 0; j < numProducts; j++)
                {
                    string productId;
                    int quantity;
                    bool found = false;

                    cin.ignore();
                    cout << "\nSan pham #" << (j + 1) << ":\n";
                    cout << "Nhap ma san pham: ";
                    getline(cin, productId);

                    cout << "Nhap so luong: ";
                    cin >> quantity;

                    // Tim san pham trong danh muc
                    for (int k = 0; k < totalProducts; k++)
                    {
                        if (products[k].getProductId() == productId)
                        {
                            found = true;

                            // Them san pham vao hoa don
                            newInvoice.addItem(
                                products[k].getProductId(),
                                products[k].getProductName(),
                                quantity,
                                products[k].getPrice());

                            cout << "Da them " << quantity << " " << products[k].getProductName() << endl;
                            break;
                        }
                    }

                    if (!found)
                    {
                        cout << "Khong tim thay san pham voi ma " << productId << " trong danh muc.\n";
                        j--; // Giam bo dem de nguoi dung nhap lai
                    }
                }

                // Hien thi hoa don da tao
                cout << "\nHoa don da duoc tao thanh cong:\n";
                newInvoice.Getter();

                break;
            }
        }

        if (!orderFound)
        {
            cout << "Khong tim thay don hang hoac don hang khong thuoc nha cung cap nay.\n";
        }
    }

    // Phuong thuc tao bao gia
    void createQuotation()
    {
        cout << "\n====== TAO BAO GIA ======\n";
        cout << "Nha cung cap: " << nameSupplier << " (Ma: " << idSupplier << ")\n";

        if (totalProducts == 0)
        {
            cout << "Khong co san pham nao de tao bao gia.\n";
            return;
        }

        cout << "\nCac san pham co san:\n";
        showProducts();

        cout << "\nDang tao bao gia...\n";

        // Tao mot bao gia don gian
        cout << left;
        cout << "\n====== BAO GIA ======\n";
        cout << "Ngay: " << "Ngay hien tai" << endl;
        cout << "Nha cung cap: " << nameSupplier << endl;
        cout << "Lien he: " << phoneSupplier << endl;
        cout << "Dia chi: " << addressSupplier << endl;

        cout << "\nBang gia san pham:\n";
        cout << left;
        cout << setw(10) << "Ma SP" << setw(20) << "Ten san pham"
             << setw(15) << "Don gia" << setw(15) << "So luong co san" << endl;
        cout << string(60, '-') << endl;

        for (int i = 0; i < totalProducts; i++)
        {
            cout << setw(10) << products[i].getProductId()
                 << setw(20) << products[i].getProductName()
                 << setw(15) << products[i].getPrice()
                 << setw(15) << products[i].getQuantity() << endl;
        }

        cout << string(60, '-') << endl;
        cout << "Dieu khoan va dieu kien:\n";
        cout << "1. Gia co hieu luc trong 30 ngay\n";
        cout << "2. Thanh toan: 30 ngay ke tu ngay giao hang\n";
        cout << "3. Thoi gian giao hang: Trong vong 7 ngay ke tu khi xac nhan don hang\n";
    }

    string getIdSupplier()
    {
        return this->idSupplier;
    }

    string getNameSupplier()
    {
        return this->nameSupplier;
    }

    Product getProduct(int index)
    {
        if (index >= 0 && index < totalProducts)
            return products[index];

        // Return empty product if index is out of bounds
        return Product();
    }
};

// Lop quan ly thu kho
class Warehouse_Staff
{
private:
    string name;
    Chef_Staff *chefs; // Con tro toi mang cac chef
    int totalChefs;    // So luong chef

    // Quan ly kho
    Product *inventory; // San pham trong kho
    int totalProducts;  // Tong so san pham trong kho

    // Ho so xuat nhap kho
    ExportRecord *exportRecord;
    ImportRecord *importRecord;

    // Danh sach don dat hang
    PurchaseOrder *purchaseOrders;
    int totalOrders;

public:
    Warehouse_Staff(string name = "Kho Hoosie Burger")
    {
        this->name = name;
        this->chefs = nullptr;
        this->totalChefs = 0;
        this->inventory = new Product[10]; // Khoi tao mang inventory
        this->totalProducts = 0;
        this->totalOrders = 0;
        this->purchaseOrders = new PurchaseOrder[10];

        // Khoi tao exportRecord va importRecord
        this->exportRecord = new ExportRecord();
        this->importRecord = new ImportRecord();
    }

    ~Warehouse_Staff()
    {
        if (inventory != nullptr)
            delete[] inventory;
        if (purchaseOrders != nullptr)
            delete[] purchaseOrders;
        if (exportRecord != nullptr)
            delete exportRecord;
        if (importRecord != nullptr)
            delete importRecord;
    }

    // Cap nhat danh sach chef
    void setChefs(Chef_Staff *chefArray, int totalChefs)
    {
        this->chefs = chefArray;
        this->totalChefs = totalChefs;
    }

    // Them san pham vao kho tu nha cung cap
    void addProductToInventory(Product product)
    {
        bool found = false;

        // Kiem tra xem san pham da co trong kho chua
        for (int i = 0; i < totalProducts; i++)
        {
            if (inventory[i].getProductId() == product.getProductId())
            {
                // Neu da co thi cap nhat so luong
                inventory[i].setQuantity(inventory[i].getQuantity() + product.getQuantity());
                found = true;
                break;
            }
        }

        // Neu chua co thi them moi
        if (!found)
        {
            inventory[totalProducts] = product;
            totalProducts++;
        }
    }

    // Hien thi tat ca san pham trong kho
    void showInventory()
    {
        if (totalProducts == 0)
        {
            cout << "Kho trong.\n";
            return;
        }

        cout << "\n====== SAN PHAM TRONG KHO ======\n";
        cout << left;
        cout << setw(10) << "Ma SP" << setw(20) << "Ten" << setw(15) << "So luong"
             << setw(15) << "Gia" << setw(15) << "Han su dung" << endl;
        cout << string(75, '-') << endl;

        for (int i = 0; i < totalProducts; i++)
        {
            inventory[i].Getter();
        }
        cout << string(75, '-') << endl;
    }

    // Lay yeu cau tu nhan vien dau bep
    void getRequestStaffChef()
    {
        if (chefs == nullptr || totalChefs == 0)
        {
            cout << "Khong co du lieu dau bep nao!" << endl;
            return;
        }

        bool hasRequests = false;

        // Duyet qua tat ca cac chef
        for (int i = 0; i < totalChefs; i++)
        {
            // Kiem tra xem chef nay co yeu cau nao khong
            if (chefs[i].getRequestCount() > 0)
            {
                hasRequests = true;
                cout << "\nYeu cau tu Dau bep ma: " << chefs[i].getId() << endl;
                cout << left;
                cout << setw(20) << "Ten san pham" << setw(20) << "So luong" << endl;
                cout << string(40, '-') << endl;

                // Hien thi tat ca cac yeu cau cua chef nay
                for (int j = 0; j < chefs[i].getRequestCount(); j++)
                {
                    chefs[i].getRequest(j).Getter();
                }
                cout << string(40, '-') << endl;
            }
        }

        if (!hasRequests)
        {
            cout << "Khong co yeu cau nao tu dau bep." << endl;
        }
    }

    // Xu ly yeu cau tu chef va tao phieu xuat kho
    void processChefRequest(string chefId)
    {
        bool found = false;
        int chefIndex = -1;

        // Tim chef theo ID
        for (int i = 0; i < totalChefs; i++)
        {
            if (chefs[i].getId() == chefId)
            {
                found = true;
                chefIndex = i;
                break;
            }
        }

        if (!found || chefs[chefIndex].getRequestCount() == 0)
        {
            cout << "Khong tim thay yeu cau nao tu Dau bep co ma: " << chefId << endl;
            return;
        }

        // Tao phieu xuat kho moi
        ExportInvoice newExport;
        newExport.Setter();

        cout << "\nDang xu ly yeu cau tu Dau bep ma: " << chefId << endl;

        // Them tung san pham vao phieu xuat
        for (int i = 0; i < chefs[chefIndex].getRequestCount(); i++)
        {
            InventoryRequest request = chefs[chefIndex].getRequest(i);
            string productName;
            int requestedQuantity;
            productName = request.getProductName();
            requestedQuantity = request.getQuantity();

            // Tim san pham trong kho
            bool productFound = false;
            for (int j = 0; j < totalProducts; j++)
            {
                if (inventory[j].getProductName() == productName)
                {
                    productFound = true;

                    // Kiem tra so luong trong kho
                    if (inventory[j].getQuantity() >= requestedQuantity)
                    {
                        // Du so luong, them vao phieu xuat
                        newExport.addExportItem(inventory[j].getProductId(), productName, requestedQuantity);

                        // Cap nhat so luong trong kho
                        inventory[j].setQuantity(inventory[j].getQuantity() - requestedQuantity);

                        cout << "Da them " << requestedQuantity << " " << productName << " vao phieu xuat kho.\n";
                    }
                    else
                    {
                        cout << "Khong du so luong " << productName << " trong kho.\n";
                        cout << "Co san: " << inventory[j].getQuantity() << ", Yeu cau: " << requestedQuantity << endl;
                    }
                    break;
                }
            }

            if (!productFound)
            {
                cout << "Khong tim thay san pham " << productName << " trong kho.\n";
                break;
            }
        }

        // Them phieu xuat vao ho so xuat kho
        exportRecord->addExportInvoice(newExport);
        cout << "\nPhieu xuat kho da duoc tao thanh cong!\n";
        newExport.Getter();
    }

    string getName()
    {
        return this->name;
    }

    // Tao don dat hang
    void createPurchaseOrder(Supplier suppliers[], int totalSuppliers)
    {
        if (totalSuppliers == 0)
        {
            cout << "Khong co nha cung cap nao trong he thong. Vui long them nha cung cap truoc.\n";
            return;
        }

        // Hien thi danh sach cac nha cung cap
        cout << "\n====== DANH SACH NHA CUNG CAP ======\n";
        cout << left;
        cout << setw(10) << "Ma NCC" << setw(20) << "Ten nha cung cap" << endl;
        cout << string(30, '-') << endl;

        for (int i = 0; i < totalSuppliers; i++)
        {
            cout << setw(10) << suppliers[i].getIdSupplier() << setw(20) << suppliers[i].getNameSupplier() << endl;
        }
        cout << string(30, '-') << endl;

        // Nhap thong tin don hang
        string supplierId;
        bool supplierFound = false;

        do
        {
            cout << "Nhap ma nha cung cap: ";
            cin.ignore();
            getline(cin, supplierId);

            if (supplierId.empty())
            {
                cout << "Ma nha cung cap la bat buoc!\n";
                continue;
            }

            // Kiem tra xem nha cung cap co ton tai khong
            for (int i = 0; i < totalSuppliers; i++)
            {
                if (suppliers[i].getIdSupplier() == supplierId)
                {
                    supplierFound = true;
                    break;
                }
            }

            if (!supplierFound)
            {
                cout << "Khong tim thay nha cung cap. Vui long thu lai!\n";
            }

        } while (!supplierFound);

        // Tao don dat hang moi
        PurchaseOrder newOrder;
        newOrder.Setter(); // Goi phuong thuc nhap thong tin co ban cua don hang

        // Them san pham vao don hang
        int numItems;
        cout << "Nhap so luong mat hang can dat: ";
        cin >> numItems;

        for (int i = 0; i < numItems; i++)
        {
            string productId, productName;
            int quantity;

            cin.ignore();
            cout << "\nMat hang #" << (i + 1) << ":\n";
            cout << "Nhap ma san pham: ";
            getline(cin, productId);

            cout << "Nhap ten san pham: ";
            getline(cin, productName);

            cout << "Nhap so luong can dat: ";
            cin >> quantity;

            // Them san pham vao don hang
            newOrder.addOrderItem(productId, productName, quantity);
        }

        // Them don hang vao danh sach
        purchaseOrders[totalOrders] = newOrder;
        totalOrders++;

        cout << "\nDa tao don dat hang thanh cong!\n";
        newOrder.Getter(); // Hien thi thong tin don hang vua tao
    }

    // Hien thi tat ca don dat hang
    void showAllPurchaseOrders()
    {
        if (totalOrders == 0)
        {
            cout << "Chua co don dat hang nao.\n";
            return;
        }

        cout << "\n====== DANH SACH DON DAT HANG ======\n";
        cout << left;
        cout << setw(15) << "Ma don hang" << setw(15) << "Nha cung cap" << endl;
        cout << string(30, '-') << endl;

        for (int i = 0; i < totalOrders; i++)
        {
            cout << setw(15) << purchaseOrders[i].getOrderId()
                 << setw(15) << purchaseOrders[i].getSupplierId() << endl;
        }
        cout << string(30, '-') << endl;
    }

    // Doi chieu hang xuat va nhap de lap don dat hang
    void reconcileInventory()
    {
        if (totalProducts == 0)
        {
            cout << "Khong co san pham nao trong kho de doi chieu.\n";
            return;
        }

        cout << "\n====== DOI CHIEU HANG TRONG KHO ======\n";
        cout << "San pham duoi nguong ton kho hoac can dat them:\n";

        // Nguong ton kho toi thieu - co the dieu chinh theo nhu cau
        const int MIN_QUANTITY = 10;

        bool needToOrder = false;

        cout << left;
        cout << setw(10) << "Ma SP" << setw(20) << "Ten san pham" << setw(15) << "Ton kho" << endl;
        cout << string(45, '-') << endl;

        for (int i = 0; i < totalProducts; i++)
        {
            // Kiem tra neu so luong ton kho duoi nguong toi thieu
            if (inventory[i].getQuantity() < MIN_QUANTITY)
            {
                cout << setw(10) << inventory[i].getProductId()
                     << setw(20) << inventory[i].getProductName()
                     << setw(15) << inventory[i].getQuantity() << endl;
                needToOrder = true;
            }
        }

        if (!needToOrder)
        {
            cout << "Khong co san pham nao can dat them.\n";
            return;
        }

        cout << string(45, '-') << endl;

        // Hoi nguoi dung co muon tao don dat hang khong
        char choice;
        cout << "Ban co muon tao don dat hang cho cac san pham nay khong? (y/n): ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y')
        {
            cout << "Chon nha cung cap de dat hang:\n";
            // Su dung phuong thuc tao don dat hang da co
        }
    }

    // Nhan hang tu nha cung cap
    void receiveProductFromSupplier(Invoice invoice, Product products[], int count)
    {
        // Them hoa don vao importRecord
        importRecord->addImportInvoice(invoice);

        cout << "\n====== NHAP KHO TU NHA CUNG CAP ======\n";
        cout << "Hoa don so: " << invoice.getIdInvoice() << endl;

        // Them cac san pham vao kho
        for (int i = 0; i < count; i++)
        {
            addProductToInventory(products[i]);
            cout << "Da nhap: " << products[i].getQuantity() << " "
                 << products[i].getProductName() << " vao kho.\n";
        }

        cout << "Da hoan tat nhap kho!\n";
    }

    // Hien thi ho so xuat kho
    void showExportRecords()
    {
        if (exportRecord != nullptr)
        {
            exportRecord->showAllExportInvoices();

            // Hien thi chi tiet cua mot phieu xuat cu the
            char viewDetails;
            cout << "Ban co muon xem chi tiet cua mot phieu xuat khong? (y/n): ";
            cin >> viewDetails;

            if (viewDetails == 'y' || viewDetails == 'Y')
            {
                string invoiceId;
                cout << "Nhap ma phieu xuat can xem: ";
                cin >> invoiceId;
                exportRecord->showExportInvoiceDetails(invoiceId);
            }
        }
        else
        {
            cout << "Ho so xuat kho chua duoc khoi tao.\n";
        }
    }

    // Hien thi ho so nhap kho
    void showImportRecords()
    {
        if (importRecord != nullptr)
        {
            importRecord->showAllImportInvoices();

            // Hien thi chi tiet cua mot phieu nhap cu the
            char viewDetails;
            cout << "Ban co muon xem chi tiet cua mot phieu nhap khong? (y/n): ";
            cin >> viewDetails;

            if (viewDetails == 'y' || viewDetails == 'Y')
            {
                string invoiceId;
                cout << "Nhap ma phieu nhap can xem: ";
                cin >> invoiceId;
                importRecord->showImportInvoiceDetails(invoiceId);
            }
        }
        else
        {
            cout << "Ho so nhap kho chua duoc khoi tao.\n";
        }
    }

    PurchaseOrder *getPurchaseOrders()
    {
        return purchaseOrders;
    }

    int getTotalOrders()
    {
        return totalOrders;
    }

    void setTotalOrders(int newTotal)
    {
        totalOrders = newTotal;
    }
};

// MENU PHU CHO CHEF STAFF
void ChefStaffMenu(Chef_Staff chefs[], int &totalChefs, int &numberProductReq)
{
    int choice;
    // Cap nhat thong tin chef cho warehouse

    do
    {
        cout << "\n==================== MENU - NHAN VIEN DAU BEP ====================" << endl;
        cout << "1. Tao dau bep moi" << endl;
        cout << "2. Hien thi thong tin tat ca dau bep" << endl;
        cout << "3. Gui yeu cau den kho" << endl;
        cout << "4. Hien thi yeu cau" << endl;
        cout << "5. Quay lai menu chinh" << endl;
        cout << "Chon tuy chon: ";
        cin >> choice;
        cout << "\n";

        switch (choice)
        {
        case 1:
        {
            int number;
            cout << "So luong Dau bep ban muon tao: ";
            cin >> number;

            for (int i = 0; i < number; ++i)
            {
                cout << "\nDang tao dau bep #" << totalChefs + 1 << ":\n";
                chefs[totalChefs].Setter();
                totalChefs++;
            }
            break;
        }

        case 2:
            if (totalChefs == 0)
            {
                cout << "Chua co dau bep nao duoc tao.\n";
                cout << "Vui long tao dau bep truoc.\n";
            }
            else
            {
                cout << left;
                cout << setw(10) << "Ma" << setw(20) << "Ten" << setw(20) << "So dien thoai" << endl;
                cout << string(42, '-') << endl;
                for (int i = 0; i < totalChefs; ++i)
                {
                    chefs[i].Getter();
                }
                cout << string(42, '-') << endl;
            }
            break;

        case 3:
        {
            string idStaffChoice;
            bool found = false;
            do
            {
                cout << "Ai la ban? (nhap ma dau bep): ";
                cin.ignore();
                getline(cin, idStaffChoice);
                if (idStaffChoice.empty())
                {
                    cout << "Thong tin nay la bat buoc";
                }
            } while (idStaffChoice.empty());
            cout << "Nhap so luong san pham: ";
            cin >> numberProductReq;
            cout << "\n";
            for (int i = 0; i < totalChefs; ++i)
            {
                if (idStaffChoice == chefs[i].getId())
                {
                    chefs[i].RequestToInventory(numberProductReq);
                    found = true;
                }
                cout << "\n";
            }
            cout << "Da tao yeu cau thanh cong!!!" << endl;
            if (!found)
            {
                cout << "Khong tim thay dau bep. Vui long thu lai!! " << endl;
            }
            break;
        }

        case 4:
            if (totalChefs == 0)
            {
                cout << "Chua co dau bep nao duoc tao.\n";
                cout << "Vui long tao dau bep truoc.\n";
            }
            else
            {
                int showChoice;
                cout << "1. Hien thi yeu cau cua tat ca dau bep\n";
                cout << "2. Hien thi yeu cau cua mot dau bep cu the\n";
                cout << "Chon tuy chon: ";
                cin >> showChoice;

                if (showChoice == 1)
                {
                    bool hasRequests = false;
                    for (int i = 0; i < totalChefs; i++)
                    {
                        if (chefs[i].getRequestCount() > 0)
                        {
                            chefs[i].ShowRequests();
                            hasRequests = true;
                        }
                    }
                    if (!hasRequests)
                    {
                        cout << "Chua co yeu cau nao duoc tao cho bat ky dau bep nao.\n";
                    }
                }
                else if (showChoice == 2)
                {
                    string id;
                    bool found = false;
                    cout << "Nhap ma dau bep: ";
                    cin >> id;

                    for (int i = 0; i < totalChefs; i++)
                    {
                        if (chefs[i].getId() == id)
                        {
                            if (chefs[i].getRequestCount() > 0)
                            {
                                chefs[i].ShowRequests();
                            }
                            else
                            {
                                cout << "Chua co yeu cau nao duoc tao cho dau bep nay.\n";
                            }
                            found = true;
                            break;
                        }
                    }
                    if (!found)
                    {
                        cout << "Khong tim thay ma dau bep.\n";
                    }
                }
                else
                {
                    cout << "Lua chon khong hop le.\n";
                }
            }
            break;
        case 5:
            cout << "Dang quay lai menu chinh...\n";
            break;

        default:
            cout << "Lua chon khong hop le. Vui long thu lai.\n";
            break;
        }
    } while (choice != 5);
}

// MENU PHU CHO NHA CUNG CAP
void SupplierMenu(Supplier suppliers[], int &totalSupplier, int &totalProduct, PurchaseOrder *purchaseOrders, int &totalOrders)
{
    int choice;
    string supplierIdChoice;

    do
    {
        cout << "\n==================== MENU - NHA CUNG CAP  ====================" << endl;
        cout << "1. Tao nha cung cap moi" << endl;
        cout << "2. Hien thi thong tin tat ca nha cung cap" << endl;
        cout << "3. Tao san pham" << endl;
        cout << "4. Hien thi thong tin tat ca san pham" << endl;
        cout << "5. Xem don dat hang tu Kho" << endl;
        cout << "6. Xu ly don dat hang" << endl;
        cout << "7. Tao bao gia" << endl;
        cout << "8. Chon san pham cho don hang" << endl;
        cout << "9. Quay lai menu chinh" << endl;
        cout << "Chon tuy chon: ";
        cin >> choice;
        cout << "\n";

        switch (choice)
        {
        case 1:
        {
            int number;
            cout << "So luong Nha cung cap ban muon tao: ";
            cin >> number;

            for (int i = 0; i < number; ++i)
            {
                cout << "\nDang tao nha cung cap #" << totalSupplier + 1 << ":\n";
                suppliers[totalSupplier].Setter();
                totalSupplier++;
            }
            break;
        }

        case 2:
            if (totalSupplier == 0)
            {
                cout << "Chua co nha cung cap nao duoc tao.\n";
                cout << "Vui long tao nha cung cap truoc.\n";
            }
            else
            {
                cout << left;
                cout << setw(10) << "Ma NCC" << setw(20) << "Ten" << setw(20) << "So dien thoai" << setw(24) << "Dia chi" << endl;
                cout << string(65, '-') << endl;
                for (int i = 0; i < totalSupplier; ++i)
                {
                    suppliers[i].Getter();
                }
                cout << string(65, '-') << endl;
            }
            break;

        case 3:
            if (totalSupplier == 0)
            {
                cout << "Chua co nha cung cap nao duoc tao.\n";
                cout << "Vui long tao nha cung cap truoc.\n";
                break;
            }
            else
            {
                bool found = false;
                cout << "Tao san pham.\n";
                cout << "So luong san pham ban muon tao: ";
                cin >> totalProduct;
                cout << "Chon nha cung cap de tao san pham: ";
                cin >> supplierIdChoice;
                cout << "Dang tao san pham cho nha cung cap ma: " << supplierIdChoice << endl;

                for (int i = 0; i < totalSupplier; ++i)
                {
                    if (suppliers[i].getIdSupplier() == supplierIdChoice)
                    {
                        suppliers[i].createProduct(totalProduct);
                        found = true;
                        cout << "Da tao san pham thanh cong cho nha cung cap ma: " << supplierIdChoice << endl;
                        break;
                    }
                }
                if (!found)
                {
                    cout << "Khong tim thay ma nha cung cap. Vui long kiem tra va thu lai.\n";
                    break;
                }
            }
            break;

        case 4:
            if (totalSupplier == 0)
            {
                cout << "Chua co nha cung cap nao duoc tao.\n";
            }
            else
            {
                int showChoice;
                cout << "1. Hien thi san pham cua tat ca nha cung cap\n";
                cout << "2. Hien thi san pham cua mot nha cung cap cu the\n";
                cout << "Chon tuy chon: ";
                cin >> showChoice;

                if (showChoice == 1)
                {
                    bool hasProducts = false;
                    for (int i = 0; i < totalSupplier; i++)
                    {
                        if (suppliers[i].totalProducts > 0)
                        {
                            cout << "\nSan pham cua nha cung cap ma: " << suppliers[i].getIdSupplier() << endl;
                            suppliers[i].showProducts();
                            hasProducts = true;
                        }
                    }
                    if (!hasProducts)
                    {
                        cout << "Chua co san pham nao duoc tao cho bat ky nha cung cap nao.\n";
                    }
                }
                else if (showChoice == 2)
                {
                    string id;
                    bool found = false;
                    cout << "Nhap ma nha cung cap: ";
                    cin >> id;

                    for (int i = 0; i < totalSupplier; i++)
                    {
                        if (suppliers[i].getIdSupplier() == id)
                        {
                            if (suppliers[i].totalProducts > 0)
                            {
                                cout << "\nSan pham cua nha cung cap ma: " << id << endl;
                                suppliers[i].showProducts();
                            }
                            else
                            {
                                cout << "Chua co san pham nao duoc tao cho nha cung cap nay.\n";
                            }
                            found = true;
                            break;
                        }
                    }
                    if (!found)
                    {
                        cout << "Khong tim thay ma nha cung cap.\n";
                    }
                }
                else
                {
                    cout << "Lua chon khong hop le.\n";
                }
            }
            break;
        case 5:
        {
            // Xem don dat hang tu kho
            if (totalSupplier == 0)
            {
                cout << "Chua co nha cung cap nao duoc tao.\n";
                break;
            }

            string supplierId;
            cout << "Nhap ma nha cung cap: ";
            cin >> supplierId;

            bool found = false;
            for (int i = 0; i < totalSupplier; i++)
            {
                if (suppliers[i].getIdSupplier() == supplierId)
                {
                    suppliers[i].viewPurchaseOrders(purchaseOrders, totalOrders);
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                cout << "Khong tim thay ma nha cung cap.\n";
            }
            break;
        }

        case 6:
        {
            // Xu ly don dat hang
            if (totalSupplier == 0)
            {
                cout << "Chua co nha cung cap nao duoc tao.\n";
                break;
            }

            string supplierId, orderId;
            cout << "Nhap ma nha cung cap: ";
            cin >> supplierId;
            cout << "Nhap ma don hang can xu ly: ";
            cin >> orderId;

            bool found = false;
            for (int i = 0; i < totalSupplier; i++)
            {
                if (suppliers[i].getIdSupplier() == supplierId)
                {
                    Invoice newInvoice = suppliers[i].processOrder(orderId, purchaseOrders, totalOrders);
                    // Them hoa don nay vao ho so nhap kho cua warehouse - can them ham trong Warehouse_Staff
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                cout << "Khong tim thay ma nha cung cap.\n";
            }
            break;
        }

        case 7:
        {
            // Tao bao gia
            if (totalSupplier == 0)
            {
                cout << "Chua co nha cung cap nao duoc tao.\n";
                break;
            }

            string supplierId;
            cout << "Nhap ma nha cung cap: ";
            cin >> supplierId;

            bool found = false;
            for (int i = 0; i < totalSupplier; i++)
            {
                if (suppliers[i].getIdSupplier() == supplierId)
                {
                    suppliers[i].createQuotation();
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                cout << "Khong tim thay ma nha cung cap.\n";
            }
            break;
        }

        case 8:
        {
            // Chon san pham cho don hang
            if (totalSupplier == 0)
            {
                cout << "Chua co nha cung cap nao duoc tao.\n";
                break;
            }

            string supplierId, orderId;
            cout << "Nhap ma nha cung cap: ";
            cin >> supplierId;
            cout << "Nhap ma don hang can xu ly: ";
            cin >> orderId;

            bool found = false;
            for (int i = 0; i < totalSupplier; i++)
            {
                if (suppliers[i].getIdSupplier() == supplierId)
                {
                    suppliers[i].selectProductsForOrder(orderId, purchaseOrders, totalOrders);
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                cout << "Khong tim thay ma nha cung cap.\n";
            }
            break;
        }

        case 9:
            cout << "Dang quay lai menu chinh...\n";
            break;

        default:
            cout << "Lua chon khong hop le. Vui long thu lai.\n";
            break;
        }
    } while (choice != 9);
}

// MENU PHU CHO THU KHO
void WarehouseStaffMenu(Warehouse_Staff warehouses[], Chef_Staff chefs[], int totalChefs, int &numberProductReq, Supplier suppliers[], int &totalSupplier, int &totalOrders)
{
    int choice;
    warehouses[0].setChefs(chefs, totalChefs);
    do
    {
        cout << "\n==================== MENU - THU KHO ====================" << endl;
        cout << "Xin chao " << warehouses->getName() << endl;
        cout << "-----------------------" << endl;
        cout << "1. Xem tat ca yeu cau tu dau bep" << endl;
        cout << "2. Xu ly yeu cau tu dau bep" << endl;
        cout << "3. Tao don dat hang den nha cung cap" << endl;
        cout << "4. Xem tat ca don dat hang" << endl;
        cout << "5. Xem hang ton kho" << endl;
        cout << "6. Xem ho so xuat kho" << endl;
        cout << "7. Xem ho so nhap kho" << endl;
        cout << "8. Doi chieu hang ton kho va chuan bi don hang" << endl;
        cout << "9. Nhan hang tu nha cung cap" << endl;
        cout << "10. Quay lai menu chinh" << endl;
        cout << "Chon tuy chon: ";
        cin >> choice;
        cout << "\n";

        switch (choice)
        {
        case 1:
        {
            warehouses->getRequestStaffChef();
            break;
        }
        case 2:
        {
            string chefId;
            cout << "Nhap ma dau bep de xu ly yeu cau: ";
            cin >> chefId;
            warehouses->processChefRequest(chefId);
            break;
        }
        case 3:
        {
            warehouses->createPurchaseOrder(suppliers, totalSupplier);
            totalOrders++; // Cập nhật biến totalOrders
            warehouses->setTotalOrders(totalOrders); // Cập nhật lại trong warehouses
            break;
        }
        case 4:
        {
            warehouses->showAllPurchaseOrders();
            break;
        }
        case 5:
        {
            warehouses->showInventory();
            break;
        }
        case 6:
        {
            warehouses->showExportRecords();
            break;
        }
        case 7:
        {
            warehouses->showImportRecords();
            break;
        }
        case 8:
        {
            warehouses->reconcileInventory();
            break;
        }
        case 9:
        {
            // Nhan hang tu nha cung cap
            if (totalSupplier == 0)
            {
                cout << "Chua co nha cung cap nao trong he thong. Vui long them nha cung cap truoc.\n";
                break;
            }

            // Hien thi danh sach nha cung cap
            cout << "\n====== NHA CUNG CAP ======\n";
            cout << left;
            cout << setw(10) << "Ma NCC" << setw(20) << "Ten" << endl;
            cout << string(30, '-') << endl;

            for (int i = 0; i < totalSupplier; i++)
            {
                cout << setw(10) << suppliers[i].getIdSupplier()
                     << setw(20) << suppliers[i].getNameSupplier() << endl;
            }
            cout << string(30, '-') << endl;

            // Chon nha cung cap
            string supplierId;
            bool found = false;
            int supplierIndex = -1;

            cout << "Nhap ma nha cung cap: ";
            cin >> supplierId;

            for (int i = 0; i < totalSupplier; i++)
            {
                if (suppliers[i].getIdSupplier() == supplierId)
                {
                    found = true;
                    supplierIndex = i;
                    break;
                }
            }

            if (!found)
            {
                cout << "Khong tim thay nha cung cap.\n";
                break;
            }

            // Tao hoa don nhap hang
            Invoice newInvoice;
            newInvoice.Setter();

            // Chuyen doi hoa don thanh mang san pham
            Product receivedProducts[10];
            int productCount = newInvoice.getProductsFromInvoice(receivedProducts);

            // Nhap hang vao kho
            warehouses->receiveProductFromSupplier(newInvoice, receivedProducts, productCount);
            break;
        }
        case 10:
            cout << "Dang quay lai menu chinh...\n";
            break;

        default:
            cout << "Lua chon khong hop le. Vui long thu lai.\n";
            break;
        }
    } while (choice != 10);
}

// MENU CHINH
void MenuPickJob()
{
    int choice;
    Chef_Staff chefs[10];
    int totalChefs = 0;
    int numberProductReq = 0;

    Supplier suppliers[10];
    int totalSupplier = 0;
    int totalProduct = 0;

    Warehouse_Staff warehouses[1];
    int totalOrders = 0; // Biến theo dõi tổng số đơn hàng
    
    do
    {
        cout << "\n========== MENU LUA CHON VI TRI ==========" << endl;
        cout << "1. Nhan vien Dau bep" << endl;
        cout << "2. Thu kho" << endl;
        cout << "3. Nha cung cap" << endl;
        cout << "4. Thoat" << endl;
        cout << "Vui long chon vi tri cua ban: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            ChefStaffMenu(chefs, totalChefs, numberProductReq);
            break;
        case 2:
            // Truyền biến totalOrders để WarehouseStaffMenu có thể cập nhật nó
            WarehouseStaffMenu(warehouses, chefs, totalChefs, numberProductReq, suppliers, totalSupplier, totalOrders);
            break;
        case 3:
            // Truyền biến totalOrders vào thay vì gọi phương thức getTotalOrders()
            SupplierMenu(suppliers, totalSupplier, totalProduct, warehouses[0].getPurchaseOrders(), totalOrders);
            break;
        case 4:
            cout << "Tam biet!\n";
            break;
        default:
            cout << "Lua chon khong hop le. Vui long thu lai.\n";
            break;
        }
    } while (choice != 4);
}

int main()
{
    MenuPickJob();
    return 0;
}