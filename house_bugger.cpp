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

// Lớp quản lý thủ kho
class Warehouse_Staff
{
private:
    string name;
    // Thay đổi chefs từ một chef duy nhất thành một mảng các chef
    Chef_Staff *chefs; // Con trỏ tới mảng các chef
    int totalChefs;    // Số lượng chef

public:
    Warehouse_Staff(string name = "Kho Truong Thanh")
    {
        this->name = name;
        this->chefs = nullptr;
        this->totalChefs = 0;
    }

    // Thêm phương thức để cập nhật danh sách chef
    void setChefs(Chef_Staff *chefArray, int totalChefs)
    {
        this->chefs = chefArray;
        this->totalChefs = totalChefs;
    }

    void getProductInStock() // hàm này sẽ lấy số lượng sản phẩm có trong kho
    {
        // Chức năng trong tương lai
    }

    void getRequestStaffChef() // hàm này sẽ lấy yêu cầu lấy hàng của nhân viên đầu bếp
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

    void requestGetProductInInvoice() // hàm này sẽ yêu cầu lấy thêm hàng đến với nhà cung cấp
    {
        // Chức năng trong tương lai
    }

    string getName()
    {
        return this->name;
    }
};

// lớp sản phẩm
class Product
{
protected:
    string productId, productName;
    int quantity;
    double price;

public:
    Product(string productId = "", string productName = "", int quantity = 0, double price = 0.0)
    {
        this->productId = productId;
        this->productName = productName;
        this->quantity = quantity;
        this->price = price;
    }
    ~Product()
    {
    }
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
    }
    void Getter()
    {
        cout << left;
        cout << setw(10) << productId << setw(20) << productName << setw(20) << quantity << setw(20) << price << endl;
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
    string getIdSupplier()
    {
        return this->idSupplier;
    }
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
};

// lớp hóa đơn
class Invoice : public Supplier
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
    void Getter()
    {
    }
};

// lớp 

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
void SupplierMenu(Supplier suppliers[], int &totalSupplier, int &totalProduct)
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
        cout << "5. Back to main menu" << endl;
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
            cout << "Returning to main menu...\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 5);
}

// MENU PHỤ CHO THỦ KHO
void WarehouseStaffMenu(Warehouse_Staff warehouses[], Chef_Staff chefs[], int totalChefs, int &numberProductReq)
{
    int choice;
    warehouses[0].setChefs(chefs, totalChefs);
    do
    {
        cout << "\n==================== MENU - WAREHOUSE ====================" << endl;
        cout << "Hi " << warehouses->getName() << endl;
        cout << "-----------------------" << endl;
        cout << "1. Show all requests form chefs" << endl;
        cout << "2. Send product to chef staff " << endl;
        cout << "3. Show products in stock" << endl;
        cout << ""
        cout << "4. Back to main menu" << endl;
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
        }
        break;

        case 3:
        {
            break;
        }

        case 4:
            cout << "Returning to main menu...\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 4);
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
    do
    {
        cout << "\n========== MENU FOR JOB SELECTION ==========" << endl;
        cout << "1. Chef Staff" << endl;
        cout << "2. Warehouse Staff (not yet implemented)" << endl;
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
            WarehouseStaffMenu(warehouses, chefs, totalChefs, numberProductReq);
            break;
        case 3:
            SupplierMenu(suppliers, totalSupplier, totalProduct);
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