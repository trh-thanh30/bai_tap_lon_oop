#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>

const int MAX_PRODUCTS = 100;
const int MAX_CHEFS = 20;
const int MAX_SUPPLIERS = 20;
const int MAX_RECORDS = 100;
const int MAX_ORDERS = 50;

// Lớp Product (Sản phẩm)
class Product
{
private:
    std::string id;
    std::string name;
    int quantity;
    double price;
    std::string expiry_date;

public:
    Product() {}

    Product(std::string id, std::string name, int quantity, double price, std::string expiry_date)
        : id(id), name(name), quantity(quantity), price(price), expiry_date(expiry_date) {}

    // Getters
    std::string getId() const { return id; }
    std::string getName() const { return name; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }
    std::string getExpiryDate() const { return expiry_date; }

    // Setters
    void setId(std::string newId) { id = newId; }
    void setName(std::string newName) { name = newName; }
    void setQuantity(int qty) { quantity = qty; }
    void setPrice(double newPrice) { price = newPrice; }
    void setExpiryDate(std::string date) { expiry_date = date; }

    void display() const
    {
        std::cout << std::setw(10) << id
                  << std::setw(20) << name
                  << std::setw(10) << quantity
                  << std::setw(10) << price
                  << std::setw(12) << expiry_date << std::endl;
    }

    void input()
    {
        std::cout << "Nhập mã sản phẩm: ";
        std::cin >> id;
        std::cin.ignore();
        std::cout << "Nhập tên sản phẩm: ";
        std::getline(std::cin, name);
        std::cout << "Nhập số lượng: ";
        std::cin >> quantity;
        std::cout << "Nhập giá: ";
        std::cin >> price;
        std::cin.ignore();
        std::cout << "Nhập hạn sử dụng (DD/MM/YYYY): ";
        std::getline(std::cin, expiry_date);
    }
};

// Lớp ChefStaff (Nhân viên đầu bếp)
class ChefStaff
{
private:
    std::string id;
    std::string name;
    std::string phone_number;

public:
    ChefStaff() {}

    ChefStaff(std::string id, std::string name, std::string phone_number)
        : id(id), name(name), phone_number(phone_number) {}

    // Getters
    std::string getId() const { return id; }
    std::string getName() const { return name; }
    std::string getPhoneNumber() const { return phone_number; }

    // Setters
    void setId(std::string newId) { id = newId; }
    void setName(std::string newName) { name = newName; }
    void setPhoneNumber(std::string newPhone) { phone_number = newPhone; }

    void requestInventory() const
    {
        std::cout << "Đầu bếp " << name << " (ID: " << id << ") đã gửi yêu cầu xuất kho.\n";
    }

    void display() const
    {
        std::cout << std::setw(10) << id
                  << std::setw(20) << name
                  << std::setw(15) << phone_number << std::endl;
    }

    void input()
    {
        std::cout << "Nhập mã đầu bếp: ";
        std::cin >> id;
        std::cin.ignore();
        std::cout << "Nhập tên đầu bếp: ";
        std::getline(std::cin, name);
        std::cout << "Nhập số điện thoại: ";
        std::getline(std::cin, phone_number);
    }
};

// Cấu trúc cho mỗi sản phẩm trong phiếu
struct ProductEntry
{
    std::string product_id;
    int quantity;
    double price; // Sử dụng cho phiếu nhập

    ProductEntry() : quantity(0), price(0.0) {}
    ProductEntry(std::string id, int qty, double p = 0.0) : product_id(id), quantity(qty), price(p) {}
};

// Lớp InventoryOutRecord (Phiếu xuất kho)
class InventoryOutRecord
{
private:
    std::string record_id;
    std::string date;
    std::string reason;
    std::string chef_id;
    ProductEntry products[MAX_PRODUCTS];
    int product_count;

public:
    InventoryOutRecord() : product_count(0) {}

    InventoryOutRecord(std::string id, std::string date, std::string reason, std::string chef)
        : record_id(id), date(date), reason(reason), chef_id(chef), product_count(0) {}

    // Getters
    std::string getRecordId() const { return record_id; }
    std::string getDate() const { return date; }
    std::string getReason() const { return reason; }
    std::string getChefId() const { return chef_id; }

    // Setters
    void setRecordId(std::string id) { record_id = id; }
    void setDate(std::string newDate) { date = newDate; }
    void setReason(std::string newReason) { reason = newReason; }
    void setChefId(std::string id) { chef_id = id; }

    void addProduct(std::string product_id, int quantity)
    {
        if (product_count < MAX_PRODUCTS)
        {
            products[product_count] = ProductEntry(product_id, quantity);
            product_count++;
        }
        else
        {
            std::cout << "Không thể thêm sản phẩm, đã đạt giới hạn.\n";
        }
    }

    void display() const
    {
        std::cout << "\n===== PHIẾU XUẤT KHO =====\n";
        std::cout << "Số phiếu: " << record_id << "\n";
        std::cout << "Ngày: " << date << "\n";
        std::cout << "Lý do: " << reason << "\n";
        std::cout << "Mã đầu bếp: " << chef_id << "\n";
        std::cout << "\nDanh sách sản phẩm xuất kho:\n";
        std::cout << std::setw(10) << "Mã SP" << std::setw(10) << "Số lượng" << std::endl;
        std::cout << "-----------------------------\n";

        for (int i = 0; i < product_count; i++)
        {
            std::cout << std::setw(10) << products[i].product_id
                      << std::setw(10) << products[i].quantity << std::endl;
        }
        std::cout << "=============================\n";
    }

    void input()
    {
        std::cout << "Nhập số phiếu xuất kho: ";
        std::cin >> record_id;
        std::cin.ignore();
        std::cout << "Nhập ngày (DD/MM/YYYY): ";
        std::getline(std::cin, date);
        std::cout << "Nhập lý do xuất kho: ";
        std::getline(std::cin, reason);
        std::cout << "Nhập mã đầu bếp: ";
        std::cin >> chef_id;

        std::cout << "Nhập số lượng loại sản phẩm cần xuất: ";
        std::cin >> product_count;

        if (product_count > MAX_PRODUCTS)
        {
            product_count = MAX_PRODUCTS;
            std::cout << "Chỉ cho phép tối đa " << MAX_PRODUCTS << " loại sản phẩm.\n";
        }

        for (int i = 0; i < product_count; i++)
        {
            std::cout << "Sản phẩm " << (i + 1) << ":\n";
            std::cout << "Mã sản phẩm: ";
            std::cin >> products[i].product_id;
            std::cout << "Số lượng: ";
            std::cin >> products[i].quantity;
        }
    }

    ProductEntry *getProducts() { return products; }
    int getProductCount() const { return product_count; }
};

// Lớp InventoryInRecord (Phiếu nhập kho)
class InventoryInRecord
{
private:
    std::string invoice_id;
    std::string supplier_name;
    std::string supplier_id;
    std::string address;
    std::string phone_number;
    std::string delivery_date;
    ProductEntry products[MAX_PRODUCTS];
    int product_count;

public:
    InventoryInRecord() : product_count(0) {}

    // Getters
    std::string getInvoiceId() const { return invoice_id; }
    std::string getSupplierId() const { return supplier_id; }

    void addProduct(std::string product_id, int quantity, double price)
    {
        if (product_count < MAX_PRODUCTS)
        {
            products[product_count] = ProductEntry(product_id, quantity, price);
            product_count++;
        }
        else
        {
            std::cout << "Không thể thêm sản phẩm, đã đạt giới hạn.\n";
        }
    }

    double calculateTotalPrice() const
    {
        double total = 0.0;
        for (int i = 0; i < product_count; i++)
        {
            total += products[i].quantity * products[i].price;
        }
        return total;
    }

    void display() const
    {
        std::cout << "\n===== PHIẾU NHẬP KHO =====\n";
        std::cout << "Số hóa đơn: " << invoice_id << "\n";
        std::cout << "Nhà cung cấp: " << supplier_name << " (ID: " << supplier_id << ")\n";
        std::cout << "Địa chỉ: " << address << "\n";
        std::cout << "Số điện thoại: " << phone_number << "\n";
        std::cout << "Ngày giao hàng: " << delivery_date << "\n";

        std::cout << "\nDanh sách sản phẩm nhập kho:\n";
        std::cout << std::setw(10) << "Mã SP" << std::setw(10) << "Số lượng"
                  << std::setw(12) << "Đơn giá" << std::setw(15) << "Thành tiền" << std::endl;
        std::cout << "-----------------------------------------------\n";

        for (int i = 0; i < product_count; i++)
        {
            double subtotal = products[i].quantity * products[i].price;
            std::cout << std::setw(10) << products[i].product_id
                      << std::setw(10) << products[i].quantity
                      << std::setw(12) << products[i].price
                      << std::setw(15) << subtotal << std::endl;
        }

        std::cout << "-----------------------------------------------\n";
        std::cout << "Tổng giá trị: " << calculateTotalPrice() << std::endl;
        std::cout << "=============================\n";
    }

    void input()
    {
        std::cout << "Nhập số hóa đơn: ";
        std::cin >> invoice_id;
        std::cin.ignore();
        std::cout << "Nhập tên nhà cung cấp: ";
        std::getline(std::cin, supplier_name);
        std::cout << "Nhập mã nhà cung cấp: ";
        std::cin >> supplier_id;
        std::cin.ignore();
        std::cout << "Nhập địa chỉ: ";
        std::getline(std::cin, address);
        std::cout << "Nhập số điện thoại: ";
        std::getline(std::cin, phone_number);
        std::cout << "Nhập ngày giao hàng (DD/MM/YYYY): ";
        std::getline(std::cin, delivery_date);

        std::cout << "Nhập số lượng loại sản phẩm nhập: ";
        std::cin >> product_count;

        if (product_count > MAX_PRODUCTS)
        {
            product_count = MAX_PRODUCTS;
            std::cout << "Chỉ cho phép tối đa " << MAX_PRODUCTS << " loại sản phẩm.\n";
        }

        for (int i = 0; i < product_count; i++)
        {
            std::cout << "Sản phẩm " << (i + 1) << ":\n";
            std::cout << "Mã sản phẩm: ";
            std::cin >> products[i].product_id;
            std::cout << "Số lượng: ";
            std::cin >> products[i].quantity;
            std::cout << "Đơn giá: ";
            std::cin >> products[i].price;
        }
    }

    ProductEntry *getProducts() { return products; }
    int getProductCount() const { return product_count; }
};

// Lớp PurchaseOrder (Đơn đặt hàng)
class PurchaseOrder
{
private:
    std::string order_id;
    ProductEntry products[MAX_PRODUCTS];
    int product_count;
    std::string order_date;
    std::string required_delivery_date;
    std::string supplier_id;

public:
    PurchaseOrder() : product_count(0) {}

    void addProduct(std::string product_id, int quantity)
    {
        if (product_count < MAX_PRODUCTS)
        {
            products[product_count] = ProductEntry(product_id, quantity);
            product_count++;
        }
        else
        {
            std::cout << "Không thể thêm sản phẩm, đã đạt giới hạn.\n";
        }
    }

    void sendToSupplier() const
    {
        std::cout << "Đơn hàng " << order_id << " đã được gửi đến nhà cung cấp " << supplier_id << ".\n";
    }

    void display() const
    {
        std::cout << "\n===== ĐƠN ĐẶT HÀNG =====\n";
        std::cout << "Mã đơn: " << order_id << "\n";
        std::cout << "Ngày đặt hàng: " << order_date << "\n";
        std::cout << "Ngày cần nhận hàng: " << required_delivery_date << "\n";
        std::cout << "Mã nhà cung cấp: " << supplier_id << "\n";

        std::cout << "\nDanh sách sản phẩm đặt mua:\n";
        std::cout << std::setw(10) << "Mã SP" << std::setw(10) << "Số lượng" << std::endl;
        std::cout << "-----------------------------\n";

        for (int i = 0; i < product_count; i++)
        {
            std::cout << std::setw(10) << products[i].product_id
                      << std::setw(10) << products[i].quantity << std::endl;
        }
        std::cout << "=============================\n";
    }

    void input()
    {
        std::cout << "Nhập mã đơn đặt hàng: ";
        std::cin >> order_id;
        std::cin.ignore();
        std::cout << "Nhập ngày đặt hàng (DD/MM/YYYY): ";
        std::getline(std::cin, order_date);
        std::cout << "Nhập ngày cần nhận hàng (DD/MM/YYYY): ";
        std::getline(std::cin, required_delivery_date);
        std::cout << "Nhập mã nhà cung cấp: ";
        std::cin >> supplier_id;

        std::cout << "Nhập số lượng loại sản phẩm cần đặt: ";
        std::cin >> product_count;

        if (product_count > MAX_PRODUCTS)
        {
            product_count = MAX_PRODUCTS;
            std::cout << "Chỉ cho phép tối đa " << MAX_PRODUCTS << " loại sản phẩm.\n";
        }

        for (int i = 0; i < product_count; i++)
        {
            std::cout << "Sản phẩm " << (i + 1) << ":\n";
            std::cout << "Mã sản phẩm: ";
            std::cin >> products[i].product_id;
            std::cout << "Số lượng: ";
            std::cin >> products[i].quantity;
        }
    }

    // Getters và Setters
    std::string getOrderId() const { return order_id; }
    std::string getOrderDate() const { return order_date; }
    std::string getRequiredDeliveryDate() const { return required_delivery_date; }
    std::string getSupplierId() const { return supplier_id; }

    void setOrderId(std::string id) { order_id = id; }
    void setOrderDate(std::string date) { order_date = date; }
    void setRequiredDeliveryDate(std::string date) { required_delivery_date = date; }
    void setSupplierId(std::string id) { supplier_id = id; }
};

// Lớp Supplier (Nhà cung cấp)
class Supplier
{
private:
    std::string id;
    std::string name;
    std::string address;
    std::string phone_number;

public:
    Supplier() {}

    Supplier(std::string id, std::string name, std::string address, std::string phone)
        : id(id), name(name), address(address), phone_number(phone) {}

    // Getters
    std::string getId() const { return id; }
    std::string getName() const { return name; }
    std::string getAddress() const { return address; }
    std::string getPhoneNumber() const { return phone_number; }

    // Setters
    void setId(std::string newId) { id = newId; }
    void setName(std::string newName) { name = newName; }
    void setAddress(std::string newAddress) { address = newAddress; }
    void setPhoneNumber(std::string newPhone) { phone_number = newPhone; }

    void display() const
    {
        std::cout << std::setw(10) << id
                  << std::setw(20) << name
                  << std::setw(25) << address
                  << std::setw(15) << phone_number << std::endl;
    }

    void input()
    {
        std::cout << "Nhập mã nhà cung cấp: ";
        std::cin >> id;
        std::cin.ignore();
        std::cout << "Nhập tên nhà cung cấp: ";
        std::getline(std::cin, name);
        std::cout << "Nhập địa chỉ: ";
        std::getline(std::cin, address);
        std::cout << "Nhập số điện thoại: ";
        std::getline(std::cin, phone_number);
    }
};
