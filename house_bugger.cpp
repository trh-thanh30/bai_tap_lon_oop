#include <iostream>
#include <string>
#include <regex>
#include <iomanip>
using namespace std;

// Hàm kiểm tra định dạng số điện thoại
bool isValidPhoneNumber(const string &phone_number)
{
    regex phone_regex("^0[0-9]{9}$"); // Bắt đầu bằng 0, theo sau là 9 chữ số
    return regex_match(phone_number, phone_regex);
}

// lớp yêu cầu của nhân viên
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
            cout << "Enter your product name: ";
            cin.ignore();
            getline(cin, this->productName);
            if (this->productName.empty())
            {
                cout << "Product name is req" << endl;
            }
        } while (this->productName.empty());
        do
        {
            cout << "Enter your product quantity: ";
            cin >> this->quantityRequested;
            if (this->quantityRequested < 0)
            {
                cout << "Invalid quantity" << endl;
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

// Lớp nhân viên đầu bếp
class Chef_Staff
{
private:
    string name, id, phone_number;
    int requestCount; // Số lượng yêu cầu
public:
    InventoryRequest requests[100]; // Mảng lưu trữ các yêu cầu
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
        // Giữ nguyên phần này
        cin.ignore();
        do
        {
            cout << "Enter your ID: ";
            getline(cin, id);
            if (id.empty())
                cout << "ID is required.\n";
        } while (id.empty());

        do
        {
            cout << "Enter your Name: ";
            getline(cin, name);
            if (name.empty())
                cout << "Name is required.\n";
        } while (name.empty());

        do
        {
            cout << "Enter your Phone Number (EX: 0901234567): ";
            getline(cin, phone_number);
            if (!isValidPhoneNumber(phone_number))
                cout << "Invalid phone number. Your number phone must be 10 number\n";
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

    int getRequestCount()
    {
        return requestCount;
    }

    void RequestToInventory(int numberProduct)
    {
        for (int i = 0; i < numberProduct; i++)
        {
            cout << "Created product #" << i + 1 << ": \n";
            requests[requestCount].Setter();
            requestCount++;
        }
    }

    void ShowRequests()
    {
        cout << left;
        cout << "\nRequests for Chef ID: " << id << " - " << name << endl;
        cout << setw(20) << "Product name" << setw(20) << "Quantity" << endl;
        cout << string(40, '-') << endl;

        for (int i = 0; i < requestCount; i++)
        {
            requests[i].Getter();
        }
        cout << string(40, '-') << endl;
    }
};

// lớp sản phẩm
class Product
{
protected:
    string productId, productName;
    int quantity;
    double price;
    // Thêm ngày hết hạn sử dụng
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
            cout << "Enter product Id: ";
            getline(cin, this->productId);
            if (this->productId.empty())
            {
                cout << "Product Id is required.\n";
            }
        } while (this->productId.empty());

        do
        {
            cout << "Enter product name: ";
            getline(cin, this->productName);
            if (this->productName.empty())
            {
                cout << "Product name is required.\n";
            }
        } while (this->productName.empty());

        do
        {
            cout << "Enter product price: ";
            cin >> this->price;
            if (this->price < 0 || cin.fail())
            {
                cout << "Invalid price. Please enter a real number \n";
                cin.clear();
                cin.ignore(10000, '\n'); // Clear the input buffer
            }
            else
            {
                break;
            }
        } while (true);

        cout << "Enter product quantity: ";
        cin >> this->quantity;

        // Thêm nhập thông tin hạn sử dụng
        cout << "Enter expiry date (dd mm yyyy): ";
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

// ----- LỚP ĐƠN ĐẶT HÀNG -----
class PurchaseOrder
{
private:
    string orderId;
    int orderDay, orderMonth, orderYear;
    int requiredDay, requiredMonth, requiredYear; // Thời điểm cần nhận hàng
    string supplierId;

    struct OrderItem
    {
        string productId;
        string productName;
        int quantity;
    };

    OrderItem orderItems[100];
    int totalItems;

public:
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
        this->supplierId;
    }

    void Setter()
    {
        cin.ignore();
        do
        {
            cout << "Enter Purchase Order ID: ";
            getline(cin, this->orderId);
            if (this->orderId.empty())
            {
                cout << "Order ID is required.\n";
            }
        } while (this->orderId.empty());

        cout << "Enter Order Date (dd mm yyyy): ";
        cin >> this->orderDay >> this->orderMonth >> this->orderYear;

        cout << "Enter Required Delivery Date (dd mm yyyy): ";
        cin >> this->requiredDay >> this->requiredMonth >> this->requiredYear;
        cin.ignore();

        do
        {
            cout << "Enter Supplier ID: ";
            getline(cin, this->supplierId);
            if (this->supplierId.empty())
            {
                cout << "Supplier ID is required.\n";
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
        cout << "\n======= PURCHASE ORDER DETAILS =======\n";
        cout << "Order ID: " << orderId << endl;
        cout << "Order Date: " << orderDay << "/" << orderMonth << "/" << orderYear << endl;
        cout << "Required Delivery Date: " << requiredDay << "/" << requiredMonth << "/" << requiredYear << endl;
        cout << "Supplier ID: " << supplierId << endl;
        cout << "\nOrdered Items:\n";
        cout << left;
        cout << setw(10) << "ID" << setw(20) << "Product Name" << setw(15) << "Quantity" << endl;
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
};

class Invoice
{
private:
    string idInvoice;
    int day, month, year; // ngày giao hàng
public:
    Invoice(string idInvoice = "", int day = 0, int month = 0, int year = 0)
    {
        this->idInvoice = idInvoice;
        this->day = day;
        this->month = month;
        this->year = year;
    }
    ~Invoice() {}
    void Setter()
    {
        cout << "Enter id invoice: ";
        cin.ignore();
        getline(cin, this->idInvoice);
        cout << "Enter date shipping(dd/mm/yy): ";
        cin >> this->day >> this->month >> this->year;
    }
};

// ----- LỚP PHIẾU XUẤT KHO -----
class ExportInvoice
{
private:
    string invoiceId;
    int day, month, year;
    string reason;
    string chefId; // Mã số nhân viên đầu bếp nhận hàng

    // Sử dụng cấu trúc để lưu chi tiết sản phẩm xuất kho
    struct ExportItem
    {
        string productId;
        string productName;
        int quantity;
    };

    ExportItem exportItems[100]; // Mảng lưu các mặt hàng xuất
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
            cout << "Enter Export Invoice ID: ";
            getline(cin, this->invoiceId);
            if (this->invoiceId.empty())
            {
                cout << "Invoice ID is required.\n";
            }
        } while (this->invoiceId.empty());

        cout << "Enter Date (dd mm yyyy): ";
        cin >> this->day >> this->month >> this->year;
        cin.ignore();

        cout << "Enter reason for export: ";
        getline(cin, this->reason);

        do
        {
            cout << "Enter Chef ID receiving items: ";
            getline(cin, this->chefId);
            if (this->chefId.empty())
            {
                cout << "Chef ID is required.\n";
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
        cout << "\n======= EXPORT INVOICE DETAILS =======\n";
        cout << "Invoice ID: " << invoiceId << endl;
        cout << "Date: " << day << "/" << month << "/" << year << endl;
        cout << "Reason: " << reason << endl;
        cout << "Chef ID: " << chefId << endl;
        cout << "\nExported Items:\n";
        cout << left;
        cout << setw(10) << "ID" << setw(20) << "Product Name" << setw(15) << "Quantity" << endl;
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
};

// ----- LỚP HỒ SƠ XUẤT KHO -----
class ExportRecord
{
private:
    ExportInvoice exportInvoices[1000]; // Lưu tối đa 1000 phiếu xuất
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
            cout << "No export invoices available.\n";
            return;
        }

        cout << "\n====== EXPORT RECORD SUMMARY ======\n";
        cout << left;
        cout << setw(15) << "Invoice ID" << setw(15) << "Date" << setw(15) << "Chef ID" << endl;
        cout << string(45, '-') << endl;

        for (int i = 0; i < totalInvoices; i++)
        {
            cout << setw(15) << exportInvoices[i].getInvoiceId()
                 << setw(15) << "DD/MM/YYYY" // Thay bằng ngày thực tế
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
        cout << "Invoice with ID " << invoiceId << " not found.\n";
    }

    int getTotalExports()
    {
        return totalInvoices;
    }
};

// ----- LỚP HỒ SƠ NHẬP KHO -----
class ImportRecord
{
private:
    Invoice importInvoices[1000]; // Sử dụng lớp Invoice hiện có như phiếu nhập kho
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
        // Cần bổ sung phương thức get cho Invoice để hiển thị
        cout << "\n====== IMPORT RECORD SUMMARY ======\n";
        // Hiển thị danh sách phiếu nhập kho
    }

    int getTotalImports()
    {
        return totalInvoices;
    }
};

// Lớp nhà cung cấp
class Supplier
{
protected:
    string nameSupplier, phoneSupplier, addressSupplier, idSupplier;
    Product products[100]; // Mảng chứa tối đa 100 sản phẩm

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
            cout << "Enter your ID: ";
            getline(cin, this->idSupplier);
            if (this->idSupplier.empty())
            {
                cout << "ID is required.\n";
            }
        } while (this->idSupplier.empty());
        do
        {
            cout << "Enter your name: ";
            getline(cin, this->nameSupplier);
            if (this->nameSupplier.empty())
            {
                cout << "Name is required.\n";
            }
        } while (this->nameSupplier.empty());
        do
        {
            cout << "Enter your phone number: ";
            getline(cin, this->phoneSupplier);
            if (!isValidPhoneNumber(this->phoneSupplier) || this->phoneSupplier.empty())
            {
                cout << "Invalid phone number\n";
            }
        } while (this->phoneSupplier.empty() || !isValidPhoneNumber(this->phoneSupplier));
        cout << "Enter your address: ";
        getline(cin, this->addressSupplier);
    }
    void Getter()
    {
        cout << left;
        cout << setw(10) << this->idSupplier << setw(20) << this->nameSupplier << setw(20) << this->phoneSupplier << setw(20) << this->addressSupplier << endl;
    }
    void createProduct(int length)
    {

        for (int i = 0; i < length; i++)
        {
            cout << "Creating product #" << i + 1 << ":\n";
            products[totalProducts].Setter();
            totalProducts++;
        }
    }
    void showProducts()
    {
        cout << left;
        cout << setw(10) << "ID" << setw(20) << "Name product" << setw(20) << "Quantity" << setw(20) << "Price" << endl;
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
        cout << "\n====== PURCHASE ORDERS FOR " << nameSupplier << " ======\n";

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
            cout << "No pending purchase orders for this supplier.\n";
        }
    }
    Invoice processOrder(string orderId, PurchaseOrder orders[], int totalOrders)
    {
        Invoice newInvoice;
        bool orderFound = false;

        // Find the order
        for (int i = 0; i < totalOrders; i++)
        {
            if (orders[i].getOrderId() == orderId && orders[i].getSupplierId() == idSupplier)
            {
                orderFound = true;

                // Create invoice
                string invoiceId;
                int day, month, year;

                cout << "Processing order: " << orderId << endl;
                cout << "Enter delivery invoice ID: ";
                cin >> invoiceId;
                cout << "Enter delivery date (dd mm yyyy): ";
                cin >> day >> month >> year;

                // Initialize the invoice
                newInvoice = Invoice(invoiceId, day, month, year);

                // Add products from order to invoice
                // This would require additional implementation

                cout << "Order " << orderId << " processed successfully.\n";
                break;
            }
        }

        if (!orderFound)
        {
            cout << "Order not found or doesn't belong to this supplier.\n";
        }

        return newInvoice;
    }
    string getIdSupplier()
    {
        return this->idSupplier;
    }
    string getNameSupplier()
    {
        return this->nameSupplier;
    }
};

// Lớp quản lý thủ kho
class Warehouse_Staff
{
private:
    string name;
    Chef_Staff *chefs; // Con trỏ tới mảng các chef
    int totalChefs;    // Số lượng chef

    // Thêm thuộc tính để quản lý kho
    Product *inventory; // Sản phẩm trong kho
    int totalProducts;  // Tổng số sản phẩm trong kho

    // Hồ sơ xuất nhập kho
    ExportRecord *exportRecord;
    ImportRecord *importRecord;

    // Danh sách đơn đặt hàng
    PurchaseOrder *purchaseOrders;
    int totalOrders;

public:
    Warehouse_Staff(string name = "Kho Truong Thanh")
    {
        this->name = name;
        this->chefs = nullptr;
        this->totalChefs = 0;
        this->totalProducts = 0;
        this->totalOrders = 0;
        this->purchaseOrders = new PurchaseOrder[100];
    }
    ~Warehouse_Staff() {}

    // Thêm phương thức để cập nhật danh sách chef
    void setChefs(Chef_Staff *chefArray, int totalChefs)
    {
        this->chefs = chefArray;
        this->totalChefs = totalChefs;
    }

    // Thêm sản phẩm vào kho từ nhà cung cấp
    void addProductToInventory(Product product)
    {
        bool found = false;

        // Kiểm tra xem sản phẩm đã có trong kho chưa
        for (int i = 0; i < totalProducts; i++)
        {
            if (inventory[i].getProductId() == product.getProductId())
            {
                // Nếu đã có thì cập nhật số lượng
                inventory[i].setQuantity(inventory[i].getQuantity() + product.getQuantity());
                found = true;
                break;
            }
        }

        // Nếu chưa có thì thêm mới
        if (!found)
        {
            inventory[totalProducts] = product;
            totalProducts++;
        }
    }

    // Hiển thị tất cả sản phẩm trong kho
    void showInventory()
    {
        if (totalProducts == 0)
        {
            cout << "Inventory is empty.\n";
            return;
        }

        cout << "\n====== INVENTORY PRODUCTS ======\n";
        cout << left;
        cout << setw(10) << "ID" << setw(20) << "Name" << setw(15) << "Quantity"
             << setw(15) << "Price" << setw(15) << "Expiry Date" << endl;
        cout << string(75, '-') << endl;

        for (int i = 0; i < totalProducts; i++)
        {
            inventory[i].Getter();
        }
        cout << string(75, '-') << endl;
    }
    // Lấy yêu cầu từ nhân viên đầu bếp
    void getRequestStaffChef()
    {
        if (chefs == nullptr || totalChefs == 0)
        {
            cout << "No chef data available!" << endl;
            return;
        }

        bool hasRequests = false;

        // Duyệt qua tất cả các chef
        for (int i = 0; i < totalChefs; i++)
        {
            // Kiểm tra xem chef này có yêu cầu nào không
            if (chefs[i].getRequestCount() > 0)
            {
                hasRequests = true;
                cout << "\nRequests from Chef ID: " << chefs[i].getId() << endl;
                cout << left;
                cout << setw(20) << "Product name" << setw(20) << "Quantity" << endl;
                cout << string(40, '-') << endl;

                // Hiển thị tất cả các yêu cầu của chef này
                for (int j = 0; j < chefs[i].getRequestCount(); j++)
                {
                    chefs[i].getRequest(j).Getter();
                }
                cout << string(40, '-') << endl;
            }
        }

        if (!hasRequests)
        {
            cout << "No requests found from any chef." << endl;
        }
    }

    // Xử lý yêu cầu từ chef và tạo phiếu xuất kho
    void processChefRequest(string chefId)
    {
        bool found = false;
        int chefIndex = -1;

        // Tìm chef theo ID
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
            cout << "No requests found for Chef ID: " << chefId << endl;
            return;
        }

        // Tạo phiếu xuất kho mới
        ExportInvoice newExport;
        newExport.Setter();

        cout << "\nProcessing requests for Chef ID: " << chefId << endl;

        // Thêm từng sản phẩm vào phiếu xuất
        for (int i = 0; i < chefs[chefIndex].getRequestCount(); i++)
        {
            InventoryRequest request = chefs[chefIndex].getRequest(i);
            string productName;
            int requestedQuantity;
            productName = request.getProductName();
            requestedQuantity = request.getQuantity();

            // Tìm sản phẩm trong kho
            bool productFound = false;
            for (int j = 0; j < totalProducts; j++)
            {
                if (inventory[j].getProductName() == productName)
                {
                    productFound = true;

                    // Kiểm tra số lượng trong kho
                    if (inventory[j].getQuantity() >= requestedQuantity)
                    {
                        // Đủ số lượng, thêm vào phiếu xuất
                        newExport.addExportItem(inventory[j].getProductId(), productName, requestedQuantity);

                        // Cập nhật số lượng trong kho
                        inventory[j].setQuantity(inventory[j].getQuantity() - requestedQuantity);

                        cout << "Added " << requestedQuantity << " of " << productName << " to export invoice.\n";
                    }
                    else
                    {
                        cout << "Insufficient quantity for " << productName << " in inventory.\n";
                        cout << "Available: " << inventory[j].getQuantity() << ", Requested: " << requestedQuantity << endl;
                    }
                    break;
                }
            }

            if (!productFound)
            {
                cout << "Product " << productName << " not found in inventory.\n";
                break;
            }
        }

        // Thêm phiếu xuất vào hồ sơ xuất kho
        exportRecord->addExportInvoice(newExport);
        cout << "\nExport invoice created successfully!\n";
        newExport.Getter();
    }

    // tạo đơn hàng mua hàng
    // void createdOrder(int lengthOrder, Supplier suppliers[], int totalSupliers)
    // {
    //     string supllierId;
    //     bool found = false;
    //     do
    //     {
    //         cout << "Enter supplier Id: ";
    //         cin.ignore();
    //         getline(cin, supllierId);
    //         if (supllierId.empty())
    //         {
    //             cout << "Please enter a supplierid" << endl;
    //         }
    //     } while (supllierId.empty());
    //     for (int i = 0; i < totalSupliers; i++) {
    //         if(supplierId == suppliers.getIdSupplier()) {
    //             found = true;
    //             purchaseOrders->Setter();
    //         }
    //     }
    //     if(!found) {
    //         cout << "Supplier id invalid" << endl;
    //     }
    // }
    string getName()
    {
        return this->name;
    }

    // Đối chiếu hàng xuất và nhập để lập đơn đặt hàng
    void createPurchaseOrder(Supplier suppliers[], int totalSuppliers)
    {
        if (totalSuppliers == 0)
        {
            cout << "Not have supplier in system. Please try agin!!.\n";
            return;
        }

        // Hiển thị danh sách các nhà cung cấp để người dùng chọn
        cout << "\n====== LIST OF SUPPLIER ======\n";
        cout << left;
        cout << setw(10) << "ID" << setw(20) << "Tên nhà cung cấp" << endl;
        cout << string(30, '-') << endl;

        for (int i = 0; i < totalSuppliers; i++)
        {
            cout << setw(10) << suppliers[i].getIdSupplier() << setw(20) << suppliers[i].getNameSupplier() << endl;
        }
        cout << string(30, '-') << endl;

        // Nhập thông tin đơn hàng
        string supplierId;
        bool supplierFound = false;

        do
        {
            cout << "Enter id supplier: ";
            cin.ignore();
            getline(cin, supplierId);

            if (supplierId.empty())
            {
                cout << "Id supplier is requried!\n";
                continue;
            }

            // Kiểm tra xem nhà cung cấp có tồn tại không
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
                cout << "Not found id supplier. Please try aign!!!\n";
            }

        } while (!supplierFound);

        // Tạo đơn đặt hàng mới
        PurchaseOrder newOrder;
        newOrder.Setter(); // Gọi phương thức nhập thông tin cơ bản của đơn hàng

        // Thêm sản phẩm vào đơn hàng
        int numItems;
        cout << "Enter number of order product: ";
        cin >> numItems;

        for (int i = 0; i < numItems; i++)
        {
            string productId, productName;
            int quantity;

            cin.ignore();
            cout << "\nOrder #" << (i + 1) << ":\n";
            cout << "Enter id order: ";
            getline(cin, productId);

            cout << "Nhập tên sản phẩm: ";
            getline(cin, productName);

            cout << "Nhập số lượng cần đặt: ";
            cin >> quantity;

            // Thêm sản phẩm vào đơn hàng
            newOrder.addOrderItem(productId, productName, quantity);
        }

        // Thêm đơn hàng vào danh sách
        purchaseOrders[totalOrders] = newOrder;
        totalOrders++;

        cout << "\nĐã tạo đơn đặt hàng thành công!\n";
        newOrder.Getter(); // Hiển thị thông tin đơn hàng vừa tạo
    }

    // Phương thức hiển thị tất cả đơn đặt hàng
    void showAllPurchaseOrders()
    {
        if (totalOrders == 0)
        {
            cout << "Not have purchase orders yet!!!\n";
            return;
        }

        cout << "\n====== LIST OF PURCHASE ORDERS ======\n";
        cout << left;
        cout << setw(15) << "Id order" << setw(15) << "Suppliers" << endl;
        cout << string(30, '-') << endl;

        for (int i = 0; i < totalOrders; i++)
        {
            cout << setw(15) << purchaseOrders[i].getOrderId()
                 << setw(15) << purchaseOrders[i].getSupplierId() << endl;
        }
        cout << string(30, '-') << endl;
    }
};

// MENU PHỤ CHO CHEF STAFF
void ChefStaffMenu(Chef_Staff chefs[], int &totalChefs, int &numberProductReq)
{
    int choice;
    // Cập nhật thông tin chef cho warehouse

    do
    {
        cout << "\n==================== MENU - CHEF STAFF ====================" << endl;
        cout << "1. Create new chefs" << endl;
        cout << "2. Show all chef info" << endl;
        cout << "3. Send request to warehouse " << endl;
        cout << "4. Show requests" << endl;
        cout << "5. Back to main menu" << endl;
        cout << "Choose option: ";
        cin >> choice;
        cout << "\n";

        switch (choice)
        {
        case 1:
        {
            int number;
            cout << "Number of Chefs you want to create: ";
            cin >> number;

            for (int i = 0; i < number; ++i)
            {
                cout << "\nCreating chef #" << totalChefs + 1 << ":\n";
                chefs[totalChefs].Setter();
                totalChefs++;
            }
            break;
        }

        case 2:
            if (totalChefs == 0)
            {

                cout << "No chefs created yet.\n";
                cout << "Please create chefs first.\n";
            }
            else
            {
                cout << left;
                cout << setw(10) << "ID" << setw(20) << "Name" << setw(20) << "Phone Number" << endl;
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
                cout << "Who i'm? (enter id staff): ";
                cin.ignore();
                getline(cin, idStaffChoice);
                if (idStaffChoice.empty())
                {
                    cout << "This fill is required";
                }
            } while (idStaffChoice.empty());
            cout << "Enter product number: ";
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
            cout << "Created req successfully!!!" << endl;
            if (!found)
            {
                cout << "No staff chef found. Please try again!! " << endl;
            }
            break;
        }

        case 4:
            if (totalChefs == 0)
            {
                cout << "No chefs created yet.\n";
                cout << "Please create chefs first.\n";
            }
            else
            {
                int showChoice;
                cout << "1. Show requests for all chefs\n";
                cout << "2. Show requests for a specific chef\n";
                cout << "Choose option: ";
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
                        cout << "No requests created yet for any chef.\n";
                    }
                }
                else if (showChoice == 2)
                {
                    string id;
                    bool found = false;
                    cout << "Enter chef ID: ";
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
                                cout << "No requests created yet for this chef.\n";
                            }
                            found = true;
                            break;
                        }
                    }
                    if (!found)
                    {
                        cout << "Chef ID not found.\n";
                    }
                }
                else
                {
                    cout << "Invalid choice.\n";
                }
            }
            break;
        case 5:
            cout << "Returning to main menu...\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 5);
}

// MENU PHỤ CHO NHÀ CUNG CẤP
void SupplierMenu(Supplier suppliers[], int &totalSupplier, int &totalProduct, PurchaseOrder *purchaseOrders, int &totalOrders)
{
    int choice;
    string supplierIdChoice;

    do
    {
        cout << "\n==================== MENU - SUPPLIER  ====================" << endl;
        cout << "1. Create new supplier" << endl;
        cout << "2. Show all suppliers info" << endl;
        cout << "3. Create product" << endl;
        cout << "4. Show all products info" << endl;
        cout << "5. Get Order form Warehouse" << endl;
        cout << "6. Create order" << endl;
        cout << "7. Back to main menu" << endl;
        cout << "Choose option: ";
        cin >> choice;
        cout << "\n";

        switch (choice)
        {
        case 1:
        {
            int number;
            cout << "Number of Supplier you want to create: ";
            cin >> number;

            for (int i = 0; i < number; ++i)
            {
                cout << "\nCreating supplier #" << totalSupplier + 1 << ":\n";
                suppliers[totalSupplier].Setter();
                totalSupplier++;
            }
            break;
        }

        case 2:
            if (totalSupplier == 0)
            {
                cout << "No suppliers created yet.\n";
                cout << "Please create suppliers first.\n";
            }
            else
            {
                cout << left;
                cout << setw(10) << "ID" << setw(20) << "Name" << setw(20) << "Phone Number" << setw(24) << "Address" << endl;
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
                cout << "No suppliers created yet.\n";
                cout << "Please create suppliers first.\n";
                break;
            }
            else
            {
                bool found = false;
                cout << "Created product.\n";
                cout << "Number product you want to create: ";
                cin >> totalProduct;
                cout << "Select supplier to create product: ";
                cin >> supplierIdChoice;
                cout << "Creating product for supplier ID: " << supplierIdChoice << endl;

                for (int i = 0; i < totalSupplier; ++i)
                {
                    if (suppliers[i].getIdSupplier() == supplierIdChoice)
                    {
                        suppliers[i].createProduct(totalProduct);
                        found = true;
                        cout << "Product created successfully for supplier ID: " << supplierIdChoice << endl;
                        break;
                    }
                }
                if (!found)
                {
                    cout << "Supplier ID not found. Please check and try again.\n";
                    break;
                }
            }
            break;

        case 4:
            if (totalSupplier == 0)
            {
                cout << "No suppliers created yet.\n";
            }
            else
            {
                int showChoice;
                cout << "1. Show products for all suppliers\n";
                cout << "2. Show products for a specific supplier\n";
                cout << "Choose option: ";
                cin >> showChoice;

                if (showChoice == 1)
                {
                    bool hasProducts = false;
                    for (int i = 0; i < totalSupplier; i++)
                    {
                        if (suppliers[i].totalProducts > 0)
                        {
                            cout << "\nProducts for supplier ID: " << suppliers[i].getIdSupplier() << endl;
                            suppliers[i].showProducts();
                            hasProducts = true;
                        }
                    }
                    if (!hasProducts)
                    {
                        cout << "No products created yet for any supplier.\n";
                    }
                }
                else if (showChoice == 2)
                {
                    string id;
                    bool found = false;
                    cout << "Enter supplier ID: ";
                    cin >> id;

                    for (int i = 0; i < totalSupplier; i++)
                    {
                        if (suppliers[i].getIdSupplier() == id)
                        {
                            if (suppliers[i].totalProducts > 0)
                            {
                                cout << "\nProducts for supplier ID: " << id << endl;
                                suppliers[i].showProducts();
                            }
                            else
                            {
                                cout << "No products created yet for this supplier.\n";
                            }
                            found = true;
                            break;
                        }
                    }
                    if (!found)
                    {
                        cout << "Supplier ID not found.\n";
                    }
                }
                else
                {
                    cout << "Invalid choice.\n";
                }
            }
            break;
        case 5:
        {
            // View purchase orders for this supplier
            if (totalSupplier == 0)
            {
                cout << "No suppliers created yet.\n";
                break;
            }

            string supplierId;
            cout << "Enter supplier ID: ";
            cin >> supplierId;

            bool found = false;
            for (int i = 0; i < totalSupplier; i++)
            {
                if (suppliers[i].getIdSupplier() == supplierId)
                {
                    // This requires access to purchase orders
                    suppliers[i].viewPurchaseOrders(purchaseOrders, totalOrders);
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                cout << "Supplier ID not found.\n";
            }
            break;
        }

        case 6:
        {
            // Process a purchase order
            if (totalSupplier == 0)
            {
                cout << "No suppliers created yet.\n";
                break;
            }

            string supplierId, orderId;
            cout << "Enter supplier ID: ";
            cin >> supplierId;
            cout << "Enter order ID to process: ";
            cin >> orderId;

            bool found = false;
            for (int i = 0; i < totalSupplier; i++)
            {
                if (suppliers[i].getIdSupplier() == supplierId)
                {
                    Invoice newInvoice = suppliers[i].processOrder(orderId, purchaseOrders, totalOrders);
                    // Add this invoice to warehouse's import records
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                cout << "Supplier ID not found.\n";
            }
            break;
        }

        case 7:
            cout << "Returning to main menu...\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 7);
}

// MENU PHỤ CHO THỦ KHO
void WarehouseStaffMenu(Warehouse_Staff warehouses[], Chef_Staff chefs[], int totalChefs, int &numberProductReq, Supplier suppliers[], int &totalSupplier, int &totalOrders)
{
    int choice;
    warehouses[0].setChefs(chefs, totalChefs);
    do
    {
        cout << "\n==================== MENU - WAREHOUSE ====================" << endl;
        cout << "Hi " << warehouses->getName() << endl;
        cout << "-----------------------" << endl;
        cout << "1. Show all requests from chefs" << endl;
        cout << "2. Process chef requests" << endl;
        cout << "3. Create purchase order to supplier" << endl;
        cout << "4. Show all purchase orders" << endl;
        cout << "5. Show inventory" << endl;
        cout << "6. Show export records" << endl;
        cout << "7. Back to main menu" << endl;
        cout << "Choose option: ";
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
            cout << "Enter Chef ID to process request: ";
            cin >> chefId;
            warehouses->processChefRequest(chefId);
            break;
        }
        case 3:
        {
            warehouses->createPurchaseOrder(suppliers, totalSupplier);
            totalOrders++;
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
            // Hiển thị hồ sơ xuất kho - cần thực hiện
            cout << "This feature is under development.\n";
            break;
        }
        case 7:
            cout << "Returning to main menu...\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 7);
}

// MENU CHÍNH
void MenuPickJob()
{

    int choice;
    Chef_Staff chefs[100];
    int totalChefs = 0;
    int numberProductReq = 0;

    Supplier suppliers[100]; // Mảng chứa tối đa 100 nhà cung cấp
    int totalSupplier = 0;   // Biến đếm số lượng supplier đã tạo
    int totalProduct = 0;

    Warehouse_Staff warehouses[1];

    PurchaseOrder purchaseOrders[100];
    int totalOrders = 0;
    do
    {
        cout << "\n========== MENU FOR JOB SELECTION ==========" << endl;
        cout << "1. Chef Staff" << endl;
        cout << "2. Warehouse Staff" << endl;
        cout << "3. Supplier" << endl;
        cout << "4. Exit" << endl;
        cout << "Please select your job: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            ChefStaffMenu(chefs, totalChefs, numberProductReq);
            break;
        case 2:
            WarehouseStaffMenu(warehouses, chefs, totalChefs, numberProductReq, suppliers, totalSupplier, totalOrders);
            break;
        case 3:
            SupplierMenu(suppliers, totalSupplier, totalProduct, purchaseOrders, totalOrders);
            break;
        case 4:
            cout << "Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 4);
}

int main()
{
    MenuPickJob();
    return 0;
}