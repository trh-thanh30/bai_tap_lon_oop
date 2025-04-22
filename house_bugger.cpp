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
// Lớp nhân viên đầu bếp
class Chef_Staff

{
private:
    string name, id, phone_number;

public:
    Chef_Staff(string name = "", string id = "", string phone_number = "")
    {
        this->name = name;
        this->id = id;
        this->phone_number = phone_number;
    }
    ~Chef_Staff() {}
    void Setter()
    {
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

    void ShowRequests()
    {
        cout << "Show chef's requests here\n";
    }

    void RequestToInventory()
    {
        cout << "Sending request to inventory...\n";
    }
};

// Lớp quản lý thủ kho
class Warehouse_Staff
{
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
private:
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

// MENU PHỤ CHO CHEF STAFF
void ChefStaffMenu(Chef_Staff chefs[], int &totalChefs)
{
    int choice;
    do
    {
        cout << "\n==================== MENU - CHEF STAFF ====================" << endl;
        cout << "1. Create new chefs" << endl;
        cout << "2. Show all chef info" << endl;
        cout << "3. Show requests (demo)" << endl;
        cout << "4. Send request to inventory (demo)" << endl;
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
            cout << "Showing requests (demo only).\n";
            break;

        case 4:
            cout << "Sending request to inventory (demo only).\n";
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
            else if (suppliers->totalProducts == 0)
            {
                cout << "No products created yet.\n";
            }
            else
            {
                for (int i = 0; i < totalSupplier; i++)
                {
                    suppliers[i].showProducts();
                    break;
                }
            }
            break;

        case 5:
            cout << "Returning to main menu...\n";
            break;

        default:
            cout
                << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 5);
}

// MENU CHÍNH
void MenuPickJob()
{
    int choice;
    Chef_Staff chefs[100];
    int totalChefs = 0;

    Supplier suppliers[100]; // Mảng chứa tối đa 100 nhà cung cấp
    int totalSupplier = 0;   // Biến đếm số lượng supplier đã tạo
    int totalProduct = 0;
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
            ChefStaffMenu(chefs, totalChefs);
            break;
        case 2:
            cout << "Warehouse Staff selected (chưa có chức năng).\n";
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
