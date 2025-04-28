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

// Phương thức nhập dữ liệu mẫu để kiểm thử
void loadSampleData()
{
    // Thêm một số sản phẩm mẫu vào kho
    inventory[product_count++] = Product("P001", "Gạo", 100, 15000, "30/12/2025");
    inventory[product_count++] = Product("P002", "Mì ăn liền", 200, 3500, "15/05/2025");
    inventory[product_count++] = Product("P003", "Nước mắm", 50, 25000, "10/10/2026");
    inventory[product_count++] = Product("P004", "Dầu ăn", 30, 40000, "25/05/2025");
    inventory[product_count++] = Product("P005", "Muối", 80, 7000, "31/12/2030");

    // Thêm một số đầu bếp mẫu
    chefs[chef_count++] = ChefStaff("C001", "Nguyễn Văn A", "0987654321");
    chefs[chef_count++] = ChefStaff("C002", "Trần Thị B", "0912345678");

    // Thêm một số nhà cung cấp mẫu
    suppliers[supplier_count++] = Supplier("S001", "Công ty TNHH Thực phẩm ABC", "123 Đường XYZ, Quận 1, TP.HCM", "0289123456");
    suppliers[supplier_count++] = Supplier("S002", "Công ty CP Thực phẩm DEF", "456 Đường UVW, Quận 2, TP.HCM", "0289654321");

    std::cout << "Đã tải dữ liệu mẫu thành công.\n";
}

// Lớp WarehouseManager (Thủ kho)
class WarehouseManager
{
private:
    std::string id;
    std::string name;
    std::string phone_number;

    // Danh sách các phiếu xuất kho
    InventoryOutRecord out_records[MAX_RECORDS];
    int out_record_count;

    // Danh sách các phiếu nhập kho
    InventoryInRecord in_records[MAX_RECORDS];
    int in_record_count;

    // Danh sách đơn đặt hàng
    PurchaseOrder purchase_orders[MAX_ORDERS];
    int order_count;

    // Kho sản phẩm
    Product inventory[MAX_PRODUCTS];
    int product_count;

    // Danh sách đầu bếp
    ChefStaff chefs[MAX_CHEFS];
    int chef_count;

    // Danh sách nhà cung cấp
    Supplier suppliers[MAX_SUPPLIERS];
    int supplier_count;

    // Phương thức hỗ trợ vẽ đường kẻ ngang cho bảng
    void drawTableLine(int width) const
    {
        std::cout << "+";
        for (int i = 0; i < width; i++)
        {
            std::cout << "-";
        }
        std::cout << "+" << std::endl;
    }

public:
    WarehouseManager() : out_record_count(0), in_record_count(0), order_count(0),
                         product_count(0), chef_count(0), supplier_count(0) {}

    WarehouseManager(std::string id, std::string name, std::string phone)
        : id(id), name(name), phone_number(phone),
          out_record_count(0), in_record_count(0), order_count(0),
          product_count(0), chef_count(0), supplier_count(0) {}

    // Phương thức nhập thông tin thủ kho
    void inputManagerInfo()
    {
        std::cout << "===== NHẬP THÔNG TIN THỦ KHO =====\n";
        std::cout << "Nhập mã thủ kho: ";
        std::cin >> id;
        std::cin.ignore();
        std::cout << "Nhập tên thủ kho: ";
        std::getline(std::cin, name);
        std::cout << "Nhập số điện thoại: ";
        std::getline(std::cin, phone_number);
        std::cout << "Đã nhập thông tin thủ kho thành công!\n";
    }

    // Phương thức hiển thị thông tin thủ kho
    void displayManagerInfo() const
    {
        std::cout << "\n===== THÔNG TIN THỦ KHO =====\n";
        std::cout << "Mã thủ kho: " << id << std::endl;
        std::cout << "Tên thủ kho: " << name << std::endl;
        std::cout << "Số điện thoại: " << phone_number << std::endl;
        std::cout << "============================\n";
    }

    // Phương thức xử lý yêu cầu xuất kho
    void processRequest(std::string chefId)
    {
        bool chefExists = false;
        for (int i = 0; i < chef_count; i++)
        {
            if (chefs[i].getId() == chefId)
            {
                chefExists = true;
                break;
            }
        }

        if (!chefExists)
        {
            std::cout << "Không tìm thấy đầu bếp với mã " << chefId << std::endl;
            return;
        }

        InventoryOutRecord record;
        record.input();

        // Kiểm tra hàng tồn kho
        bool sufficient = true;
        for (int i = 0; i < record.getProductCount(); i++)
        {
            ProductEntry *products = record.getProducts();
            std::string product_id = products[i].product_id;
            int quantity = products[i].quantity;

            int index = -1;
            for (int j = 0; j < product_count; j++)
            {
                if (inventory[j].getId() == product_id)
                {
                    index = j;
                    break;
                }
            }

            if (index == -1 || inventory[index].getQuantity() < quantity)
            {
                sufficient = false;
                std::cout << "Không đủ hàng trong kho cho sản phẩm " << product_id << std::endl;
            }
        }

        if (sufficient)
        {
            // Cập nhật số lượng trong kho
            for (int i = 0; i < record.getProductCount(); i++)
            {
                ProductEntry *products = record.getProducts();
                std::string product_id = products[i].product_id;
                int quantity = products[i].quantity;

                for (int j = 0; j < product_count; j++)
                {
                    if (inventory[j].getId() == product_id)
                    {
                        inventory[j].setQuantity(inventory[j].getQuantity() - quantity);
                        break;
                    }
                }
            }

            // Lưu phiếu xuất kho
            if (out_record_count < MAX_RECORDS)
            {
                out_records[out_record_count++] = record;
                std::cout << "Đã tạo phiếu xuất kho thành công.\n";
                dispatchToChef(chefId);
            }
            else
            {
                std::cout << "Không thể lưu thêm phiếu xuất kho, đã đạt giới hạn.\n";
            }
        }
    }

    // Giao hàng cho đầu bếp
    void dispatchToChef(std::string chefId)
    {
        for (int i = 0; i < chef_count; i++)
        {
            if (chefs[i].getId() == chefId)
            {
                std::cout << "Đã giao hàng cho đầu bếp " << chefs[i].getName() << std::endl;
                return;
            }
        }
        std::cout << "Không tìm thấy đầu bếp với mã " << chefId << std::endl;
    }

    // Kiểm tra hàng tồn kho
    void checkInventory()
    {
        std::cout << "\n===== KIỂM TRA HÀNG TỒN KHO =====\n";

        if (product_count == 0)
        {
            std::cout << "Kho hiện đang trống.\n";
            return;
        }

        // Tính toán độ rộng của các cột
        const int idWidth = 10;
        const int nameWidth = 25;
        const int qtyWidth = 10;
        const int priceWidth = 15;
        const int expiryWidth = 15;
        const int totalWidth = idWidth + nameWidth + qtyWidth + priceWidth + expiryWidth + 6; // +6 cho các dấu |

        // Vẽ header của bảng
        drawTableLine(totalWidth);
        std::cout << "| " << std::left << std::setw(idWidth) << "Mã SP"
                  << "| " << std::setw(nameWidth) << "Tên sản phẩm"
                  << "| " << std::setw(qtyWidth) << "Số lượng"
                  << "| " << std::setw(priceWidth) << "Giá"
                  << "| " << std::setw(expiryWidth) << "Hạn sử dụng" << "|" << std::endl;
        drawTableLine(totalWidth);

        // Hiển thị từng sản phẩm
        for (int i = 0; i < product_count; i++)
        {
            std::cout << "| " << std::left << std::setw(idWidth) << inventory[i].getId()
                      << "| " << std::setw(nameWidth) << inventory[i].getName()
                      << "| " << std::setw(qtyWidth) << inventory[i].getQuantity()
                      << "| " << std::setw(priceWidth) << std::fixed << std::setprecision(2) << inventory[i].getPrice()
                      << "| " << std::setw(expiryWidth) << inventory[i].getExpiryDate() << "|" << std::endl;
        }

        drawTableLine(totalWidth);
    }

    // Thêm sản phẩm mới vào kho
    void addNewProduct()
    {
        if (product_count >= MAX_PRODUCTS)
        {
            std::cout << "Không thể thêm sản phẩm, đã đạt giới hạn.\n";
            return;
        }

        Product newProduct;
        newProduct.input();

        // Kiểm tra sản phẩm đã tồn tại chưa
        for (int i = 0; i < product_count; i++)
        {
            if (inventory[i].getId() == newProduct.getId())
            {
                std::cout << "Sản phẩm có mã " << newProduct.getId() << " đã tồn tại!\n";
                return;
            }
        }

        inventory[product_count++] = newProduct;
        std::cout << "Đã thêm sản phẩm thành công.\n";
    }

    // Tạo đơn đặt hàng
    void createPurchaseOrder()
    {
        if (order_count >= MAX_ORDERS)
        {
            std::cout << "Không thể tạo thêm đơn đặt hàng, đã đạt giới hạn.\n";
            return;
        }

        // Kiểm tra xem có nhà cung cấp nào không
        if (supplier_count == 0)
        {
            std::cout << "Vui lòng thêm nhà cung cấp trước khi tạo đơn đặt hàng.\n";
            return;
        }

        // Hiển thị danh sách nhà cung cấp
        std::cout << "\n===== DANH SÁCH NHÀ CUNG CẤP =====\n";
        displaySuppliers();

        PurchaseOrder order;
        order.input();

        // Kiểm tra nhà cung cấp có tồn tại không
        bool found = false;
        for (int i = 0; i < supplier_count; i++)
        {
            if (suppliers[i].getId() == order.getSupplierId())
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            std::cout << "Không tìm thấy nhà cung cấp với mã " << order.getSupplierId() << std::endl;
            return;
        }

        purchase_orders[order_count++] = order;
        order.sendToSupplier();
    }

    // Nhập phiếu nhập kho
    void processDelivery()
    {
        if (in_record_count >= MAX_RECORDS)
        {
            std::cout << "Không thể lưu thêm phiếu nhập kho, đã đạt giới hạn.\n";
            return;
        }

        InventoryInRecord record;
        record.input();

        // Cập nhật số lượng trong kho
        for (int i = 0; i < record.getProductCount(); i++)
        {
            ProductEntry *products = record.getProducts();
            std::string product_id = products[i].product_id;
            int quantity = products[i].quantity;
            double price = products[i].price;

            bool found = false;
            for (int j = 0; j < product_count; j++)
            {
                if (inventory[j].getId() == product_id)
                {
                    inventory[j].setQuantity(inventory[j].getQuantity() + quantity);
                    inventory[j].setPrice(price); // Cập nhật giá mới
                    found = true;
                    break;
                }
            }

            if (!found && product_count < MAX_PRODUCTS)
            {
                // Thêm sản phẩm mới vào kho
                std::string name, expiry_date;
                std::cout << "Sản phẩm mới, vui lòng nhập thông tin:\n";
                std::cout << "Tên sản phẩm: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                std::cout << "Hạn sử dụng (DD/MM/YYYY): ";
                std::getline(std::cin, expiry_date);

                inventory[product_count++] = Product(product_id, name, quantity, price, expiry_date);
            }
        }

        in_records[in_record_count++] = record;
        std::cout << "Đã nhập kho thành công.\n";
    }

    // Hiển thị danh sách phiếu xuất kho
    void displayOutRecords() const
    {
        std::cout << "\n===== DANH SÁCH PHIẾU XUẤT KHO =====\n";

        if (out_record_count == 0)
        {
            std::cout << "Không có phiếu xuất kho nào.\n";
            return;
        }

        for (int i = 0; i < out_record_count; i++)
        {
            std::cout << "\nPhiếu xuất kho #" << (i + 1) << ":\n";
            out_records[i].display();
        }
    }

    // Hiển thị danh sách phiếu nhập kho
    void displayInRecords() const
    {
        std::cout << "\n===== DANH SÁCH PHIẾU NHẬP KHO =====\n";

        if (in_record_count == 0)
        {
            std::cout << "Không có phiếu nhập kho nào.\n";
            return;
        }

        for (int i = 0; i < in_record_count; i++)
        {
            std::cout << "\nPhiếu nhập kho #" << (i + 1) << ":\n";
            in_records[i].display();
        }
    }

    // Hiển thị danh sách đơn đặt hàng
    void displayPurchaseOrders() const
    {
        std::cout << "\n===== DANH SÁCH ĐƠN ĐẶT HÀNG =====\n";

        if (order_count == 0)
        {
            std::cout << "Không có đơn đặt hàng nào.\n";
            return;
        }

        for (int i = 0; i < order_count; i++)
        {
            std::cout << "\nĐơn đặt hàng #" << (i + 1) << ":\n";
            purchase_orders[i].display();
        }
    }

    // Thêm đầu bếp
    void addChef()
    {
        if (chef_count >= MAX_CHEFS)
        {
            std::cout << "Không thể thêm đầu bếp, đã đạt giới hạn.\n";
            return;
        }

        ChefStaff chef;
        chef.input();

        // Kiểm tra xem đầu bếp đã tồn tại chưa
        for (int i = 0; i < chef_count; i++)
        {
            if (chefs[i].getId() == chef.getId())
            {
                std::cout << "Đầu bếp có mã " << chef.getId() << " đã tồn tại!\n";
                return;
            }
        }

        chefs[chef_count++] = chef;
        std::cout << "Đã thêm đầu bếp thành công.\n";
    }

    // Hiển thị danh sách đầu bếp
    void displayChefs() const
    {
        std::cout << "\n===== DANH SÁCH ĐẦU BẾP =====\n";

        if (chef_count == 0)
        {
            std::cout << "Không có đầu bếp nào trong danh sách.\n";
            return;
        }

        // Tính toán độ rộng của các cột
        const int idWidth = 10;
        const int nameWidth = 25;
        const int phoneWidth = 15;
        const int totalWidth = idWidth + nameWidth + phoneWidth + 4; // +4 cho các dấu |

        // Vẽ header của bảng
        drawTableLine(totalWidth);
        std::cout << "| " << std::left << std::setw(idWidth) << "Mã"
                  << "| " << std::setw(nameWidth) << "Tên đầu bếp"
                  << "| " << std::setw(phoneWidth) << "Số điện thoại" << "|" << std::endl;
        drawTableLine(totalWidth);

        // Hiển thị từng đầu bếp
        for (int i = 0; i < chef_count; i++)
        {
            std::cout << "| " << std::left << std::setw(idWidth) << chefs[i].getId()
                      << "| " << std::setw(nameWidth) << chefs[i].getName()
                      << "| " << std::setw(phoneWidth) << chefs[i].getPhoneNumber() << "|" << std::endl;
        }

        drawTableLine(totalWidth);
    }

    // Thêm nhà cung cấp
    void addSupplier()
    {
        if (supplier_count >= MAX_SUPPLIERS)
        {
            std::cout << "Không thể thêm nhà cung cấp, đã đạt giới hạn.\n";
            return;
        }

        Supplier supplier;
        supplier.input();

        // Kiểm tra xem nhà cung cấp đã tồn tại chưa
        for (int i = 0; i < supplier_count; i++)
        {
            if (suppliers[i].getId() == supplier.getId())
            {
                std::cout << "Nhà cung cấp có mã " << supplier.getId() << " đã tồn tại!\n";
                return;
            }
        }

        suppliers[supplier_count++] = supplier;
        std::cout << "Đã thêm nhà cung cấp thành công.\n";
    }

    // Hiển thị danh sách nhà cung cấp
    void displaySuppliers() const
    {
        std::cout << "\n===== DANH SÁCH NHÀ CUNG CẤP =====\n";

        if (supplier_count == 0)
        {
            std::cout << "Không có nhà cung cấp nào trong danh sách.\n";
            return;
        }

        // Tính toán độ rộng của các cột
        const int idWidth = 10;
        const int nameWidth = 25;
        const int addressWidth = 30;
        const int phoneWidth = 15;
        const int totalWidth = idWidth + nameWidth + addressWidth + phoneWidth + 5; // +5 cho các dấu |

        // Vẽ header của bảng
        drawTableLine(totalWidth);
        std::cout << "| " << std::left << std::setw(idWidth) << "Mã"
                  << "| " << std::setw(nameWidth) << "Tên nhà cung cấp"
                  << "| " << std::setw(addressWidth) << "Địa chỉ"
                  << "| " << std::setw(phoneWidth) << "Số điện thoại" << "|" << std::endl;
        drawTableLine(totalWidth);

        // Hiển thị từng nhà cung cấp
        for (int i = 0; i < supplier_count; i++)
        {
            std::cout << "| " << std::left << std::setw(idWidth) << suppliers[i].getId()
                      << "| " << std::setw(nameWidth) << suppliers[i].getName()
                      << "| " << std::setw(addressWidth) << suppliers[i].getAddress()
                      << "| " << std::setw(phoneWidth) << suppliers[i].getPhoneNumber() << "|" << std::endl;
        }

        drawTableLine(totalWidth);
    }

    // Phương thức tìm kiếm sản phẩm theo mã
    void searchProductById() const
    {
        std::string search_id;
        std::cout << "Nhập mã sản phẩm cần tìm: ";
        std::cin >> search_id;

        bool found = false;
        for (int i = 0; i < product_count; i++)
        {
            if (inventory[i].getId() == search_id)
            {
                found = true;

                std::cout << "\n===== THÔNG TIN SẢN PHẨM =====\n";
                std::cout << "Mã sản phẩm: " << inventory[i].getId() << std::endl;
                std::cout << "Tên sản phẩm: " << inventory[i].getName() << std::endl;
                std::cout << "Số lượng: " << inventory[i].getQuantity() << std::endl;
                std::cout << "Giá: " << std::fixed << std::setprecision(2) << inventory[i].getPrice() << std::endl;
                std::cout << "Hạn sử dụng: " << inventory[i].getExpiryDate() << std::endl;
                break;
            }
        }

        if (!found)
        {
            std::cout << "Không tìm thấy sản phẩm có mã " << search_id << std::endl;
        }
    }

    // Phương thức tìm kiếm sản phẩm theo tên
    void searchProductByName() const
    {
        std::string search_name;
        std::cout << "Nhập tên sản phẩm cần tìm: ";
        std::cin.ignore();
        std::getline(std::cin, search_name);

        const int idWidth = 10;
        const int nameWidth = 25;
        const int qtyWidth = 10;
        const int priceWidth = 15;
        const int expiryWidth = 15;
        const int totalWidth = idWidth + nameWidth + qtyWidth + priceWidth + expiryWidth + 6;

        bool found = false;
        for (int i = 0; i < product_count; i++)
        {
            // Tìm kiếm không phân biệt hoa thường
            std::string product_name = inventory[i].getName();
            std::string name_lower = search_name;
            std::string product_lower = product_name;

            // Chuyển sang chữ thường
            for (size_t j = 0; j < name_lower.length(); j++)
            {
                name_lower[j] = std::tolower(name_lower[j]);
            }
            for (size_t j = 0; j < product_lower.length(); j++)
            {
                product_lower[j] = std::tolower(product_lower[j]);
            }

            if (product_lower.find(name_lower) != std::string::npos)
            {
                if (!found)
                {
                    // Vẽ header của bảng nếu là sản phẩm đầu tiên tìm thấy
                    std::cout << "\n===== KẾT QUẢ TÌM KIẾM =====\n";
                    drawTableLine(totalWidth);
                    std::cout << "| " << std::left << std::setw(idWidth) << "Mã SP"
                              << "| " << std::setw(nameWidth) << "Tên sản phẩm"
                              << "| " << std::setw(qtyWidth) << "Số lượng"
                              << "| " << std::setw(priceWidth) << "Giá"
                              << "| " << std::setw(expiryWidth) << "Hạn sử dụng" << "|" << std::endl;
                    drawTableLine(totalWidth);
                }

                found = true;
                std::cout << "| " << std::left << std::setw(idWidth) << inventory[i].getId()
                          << "| " << std::setw(nameWidth) << inventory[i].getName()
                          << "| " << std::setw(qtyWidth) << inventory[i].getQuantity()
                          << "| " << std::setw(priceWidth) << std::fixed << std::setprecision(2) << inventory[i].getPrice()
                          << "| " << std::setw(expiryWidth) << inventory[i].getExpiryDate() << "|" << std::endl;
            }
        }

        if (found)
        {
            drawTableLine(totalWidth);
        }
        else
        {
            std::cout << "Không tìm thấy sản phẩm có tên chứa \"" << search_name << "\"" << std::endl;
        }
    }

    // Kiểm tra và báo cáo sản phẩm sắp hết hạn
    void checkExpiryProducts()
    {
        std::cout << "\n===== SẢN PHẨM SẮP HẾT HẠN =====\n";

        // Lấy ngày hiện tại
        time_t now = time(0);
        struct tm *current_time = localtime(&now);
        int current_day = current_time->tm_mday;
        int current_month = current_time->tm_mon + 1;
        int current_year = current_time->tm_year + 1900;

        const int idWidth = 10;
        const int nameWidth = 25;
        const int qtyWidth = 10;
        const int expiryWidth = 15;
        const int totalWidth = idWidth + nameWidth + qtyWidth + expiryWidth + 5;

        bool found = false;

        for (int i = 0; i < product_count; i++)
        {
            std::string expiry = inventory[i].getExpiryDate();
            // Giả sử định dạng ngày là DD/MM/YYYY
            int day, month, year;
            if (sscanf(expiry.c_str(), "%d/%d/%d", &day, &month, &year) == 3)
            {
                // Kiểm tra xem sản phẩm có sắp hết hạn trong vòng 30 ngày không
                if (year == current_year)
                {
                    if (month == current_month)
                    {
                        if (day - current_day <= 30 && day - current_day >= 0)
                        {
                            if (!found)
                            {
                                // Vẽ header của bảng nếu là sản phẩm đầu tiên tìm thấy
                                drawTableLine(totalWidth);
                                std::cout << "| " << std::left << std::setw(idWidth) << "Mã SP"
                                          << "| " << std::setw(nameWidth) << "Tên sản phẩm"
                                          << "| " << std::setw(qtyWidth) << "Số lượng"
                                          << "| " << std::setw(expiryWidth) << "Hạn sử dụng" << "|" << std::endl;
                                drawTableLine(totalWidth);
                            }

                            found = true;
                            std::cout << "| " << std::left << std::setw(idWidth) << inventory[i].getId()
                                      << "| " << std::setw(nameWidth) << inventory[i].getName()
                                      << "| " << std::setw(qtyWidth) << inventory[i].getQuantity()
                                      << "| " << std::setw(expiryWidth) << inventory[i].getExpiryDate() << "|" << std::endl;
                        }
                    }
                    else if (month - current_month == 1)
                    {
                        // Nếu tháng tiếp theo, kiểm tra xem có phải trong vòng 30 ngày không
                        int days_in_month;
                        switch (current_month)
                        {
                        case 2:
                            days_in_month = (current_year % 4 == 0 &&
                                             (current_year % 100 != 0 || current_year % 400 == 0))
                                                ? 29
                                                : 28;
                            break;
                        case 4:
                        case 6:
                        case 9:
                        case 11:
                            days_in_month = 30;
                            break;
                        default:
                            days_in_month = 31;
                        }

                        if ((days_in_month - current_day) + day <= 30)
                        {
                            if (!found)
                            {
                                // Vẽ header của bảng nếu là sản phẩm đầu tiên tìm thấy
                                drawTableLine(totalWidth);
                                std::cout << "| " << std::left << std::setw(idWidth) << "Mã SP"
                                          << "| " << std::setw(nameWidth) << "Tên sản phẩm"
                                          << "| " << std::setw(qtyWidth) << "Số lượng"
                                          << "| " << std::setw(expiryWidth) << "Hạn sử dụng" << "|" << std::endl;
                                drawTableLine(totalWidth);
                            }

                            found = true;
                            std::cout << "| " << std::left << std::setw(idWidth) << inventory[i].getId()
                                      << "| " << std::setw(nameWidth) << inventory[i].getName()
                                      << "| " << std::setw(qtyWidth) << inventory[i].getQuantity()
                                      << "| " << std::setw(expiryWidth) << inventory[i].getExpiryDate() << "|" << std::endl;
                        }
                    }
                }
            }
            else if (year > current_year && month == 1 && current_month == 12)
            {
                // Kiểm tra các sản phẩm hết hạn vào tháng 1 năm sau
                if ((31 - current_day) + day <= 30)
                {
                    if (!found)
                    {
                        // Vẽ header của bảng nếu là sản phẩm đầu tiên tìm thấy
                        drawTableLine(totalWidth);
                        std::cout << "| " << std::left << std::setw(idWidth) << "Mã SP"
                                  << "| " << std::setw(nameWidth) << "Tên sản phẩm"
                                  << "| " << std::setw(qtyWidth) << "Số lượng"
                                  << "| " << std::setw(expiryWidth) << "Hạn sử dụng" << "|" << std::endl;
                        drawTableLine(totalWidth);
                    }

                    found = true;
                    std::cout << "| " << std::left << std::setw(idWidth) << inventory[i].getId()
                              << "| " << std::setw(nameWidth) << inventory[i].getName()
                              << "| " << std::setw(qtyWidth) << inventory[i].getQuantity()
                              << "| " << std::setw(expiryWidth) << inventory[i].getExpiryDate() << "|" << std::endl;
                }
            }
        }
    }

    if (found)
    {
        drawTableLine(totalWidth);
    }
    else
    {
        std::cout << "Không có sản phẩm nào sắp hết hạn trong vòng 30 ngày.\n";
    }
}

// Kiểm tra và báo cáo sản phẩm đã hết hạn
void
checkExpiredProducts()
{
    std::cout << "\n===== SẢN PHẨM ĐÃ HẾT HẠN =====\n";

    // Lấy ngày hiện tại
    time_t now = time(0);
    struct tm *current_time = localtime(&now);
    int current_day = current_time->tm_mday;
    int current_month = current_time->tm_mon + 1;
    int current_year = current_time->tm_year + 1900;

    const int idWidth = 10;
    const int nameWidth = 25;
    const int qtyWidth = 10;
    const int expiryWidth = 15;
    const int totalWidth = idWidth + nameWidth + qtyWidth + expiryWidth + 5;

    bool found = false;

    for (int i = 0; i < product_count; i++)
    {
        std::string expiry = inventory[i].getExpiryDate();
        // Giả sử định dạng ngày là DD/MM/YYYY
        int day, month, year;
        if (sscanf(expiry.c_str(), "%d/%d/%d", &day, &month, &year) == 3)
        {
            // Kiểm tra xem sản phẩm đã hết hạn chưa
            if (year < current_year ||
                (year == current_year && month < current_month) ||
                (year == current_year && month == current_month && day < current_day))
            {
                if (!found)
                {
                    // Vẽ header của bảng nếu là sản phẩm đầu tiên tìm thấy
                    drawTableLine(totalWidth);
                    std::cout << "| " << std::left << std::setw(idWidth) << "Mã SP"
                              << "| " << std::setw(nameWidth) << "Tên sản phẩm"
                              << "| " << std::setw(qtyWidth) << "Số lượng"
                              << "| " << std::setw(expiryWidth) << "Hạn sử dụng" << "|" << std::endl;
                    drawTableLine(totalWidth);
                }

                found = true;
                std::cout << "| " << std::left << std::setw(idWidth) << inventory[i].getId()
                          << "| " << std::setw(nameWidth) << inventory[i].getName()
                          << "| " << std::setw(qtyWidth) << inventory[i].getQuantity()
                          << "| " << std::setw(expiryWidth) << inventory[i].getExpiryDate() << "|" << std::endl;
            }
        }
    }

    if (found)
    {
        drawTableLine(totalWidth);
    }
    else
    {
        std::cout << "Không có sản phẩm nào đã hết hạn.\n";
    }
}

// Kiểm tra và báo cáo sản phẩm sắp hết hàng
void checkLowStockProducts()
{
    std::cout << "\n===== SẢN PHẨM SẮP HẾT HÀNG =====\n";

    const int idWidth = 10;
    const int nameWidth = 25;
    const int qtyWidth = 10;
    const int totalWidth = idWidth + nameWidth + qtyWidth + 4;

    bool found = false;

    // Định nghĩa ngưỡng tồn kho thấp (có thể điều chỉnh)
    const int LOW_STOCK_THRESHOLD = 10;

    for (int i = 0; i < product_count; i++)
    {
        if (inventory[i].getQuantity() <= LOW_STOCK_THRESHOLD)
        {
            if (!found)
            {
                // Vẽ header của bảng nếu là sản phẩm đầu tiên tìm thấy
                drawTableLine(totalWidth);
                std::cout << "| " << std::left << std::setw(idWidth) << "Mã SP"
                          << "| " << std::setw(nameWidth) << "Tên sản phẩm"
                          << "| " << std::setw(qtyWidth) << "Số lượng" << "|" << std::endl;
                drawTableLine(totalWidth);
            }

            found = true;
            std::cout << "| " << std::left << std::setw(idWidth) << inventory[i].getId()
                      << "| " << std::setw(nameWidth) << inventory[i].getName()
                      << "| " << std::setw(qtyWidth) << inventory[i].getQuantity() << "|" << std::endl;
        }
    }

    if (found)
    {
        drawTableLine(totalWidth);
    }
    else
    {
        std::cout << "Không có sản phẩm nào sắp hết hàng.\n";
    }
}

// Chỉnh sửa thông tin sản phẩm
void editProduct()
{
    std::string product_id;
    std::cout << "Nhập mã sản phẩm cần chỉnh sửa: ";
    std::cin >> product_id;

    bool found = false;
    for (int i = 0; i < product_count; i++)
    {
        if (inventory[i].getId() == product_id)
        {
            found = true;

            std::cout << "\n===== THÔNG TIN HIỆN TẠI =====\n";
            std::cout << "Mã sản phẩm: " << inventory[i].getId() << std::endl;
            std::cout << "Tên sản phẩm: " << inventory[i].getName() << std::endl;
            std::cout << "Số lượng: " << inventory[i].getQuantity() << std::endl;
            std::cout << "Giá: " << std::fixed << std::setprecision(2) << inventory[i].getPrice() << std::endl;
            std::cout << "Hạn sử dụng: " << inventory[i].getExpiryDate() << std::endl;

            std::cout << "\n===== NHẬP THÔNG TIN MỚI =====\n";
            std::cout << "Mã sản phẩm không thể thay đổi\n";

            std::string name;
            int quantity;
            double price;
            std::string expiry_date;

            std::cin.ignore();
            std::cout << "Nhập tên sản phẩm mới (để trống nếu không thay đổi): ";
            std::getline(std::cin, name);
            if (!name.empty())
            {
                inventory[i].setName(name);
            }

            std::cout << "Nhập số lượng mới (nhập -1 nếu không thay đổi): ";
            std::cin >> quantity;
            if (quantity != -1)
            {
                inventory[i].setQuantity(quantity);
            }

            std::cout << "Nhập giá mới (nhập -1 nếu không thay đổi): ";
            std::cin >> price;
            if (price != -1)
            {
                inventory[i].setPrice(price);
            }

            std::cin.ignore();
            std::cout << "Nhập hạn sử dụng mới (DD/MM/YYYY) (để trống nếu không thay đổi): ";
            std::getline(std::cin, expiry_date);
            if (!expiry_date.empty())
            {
                inventory[i].setExpiryDate(expiry_date);
            }

            std::cout << "Đã cập nhật thông tin sản phẩm thành công.\n";
            break;
        }
    }

    if (!found)
    {
        std::cout << "Không tìm thấy sản phẩm có mã " << product_id << std::endl;
    }
}

// Xoá sản phẩm
void deleteProduct()
{
    std::string product_id;
    std::cout << "Nhập mã sản phẩm cần xoá: ";
    std::cin >> product_id;

    bool found = false;
    for (int i = 0; i < product_count; i++)
    {
        if (inventory[i].getId() == product_id)
        {
            found = true;

            // Hiển thị thông tin sản phẩm trước khi xoá
            std::cout << "\n===== THÔNG TIN SẢN PHẨM SẼ BỊ XOÁ =====\n";
            std::cout << "Mã sản phẩm: " << inventory[i].getId() << std::endl;
            std::cout << "Tên sản phẩm: " << inventory[i].getName() << std::endl;
            std::cout << "Số lượng: " << inventory[i].getQuantity() << std::endl;
            std::cout << "Giá: " << std::fixed << std::setprecision(2) << inventory[i].getPrice() << std::endl;
            std::cout << "Hạn sử dụng: " << inventory[i].getExpiryDate() << std::endl;

            char confirm;
            std::cout << "\nBạn có chắc chắn muốn xoá sản phẩm này? (y/n): ";
            std::cin >> confirm;

            if (confirm == 'y' || confirm == 'Y')
            {
                // Di chuyển tất cả sản phẩm sau vị trí i lên một bước
                for (int j = i; j < product_count - 1; j++)
                {
                    inventory[j] = inventory[j + 1];
                }
                product_count--;
                std::cout << "Đã xoá sản phẩm thành công.\n";
            }
            else
            {
                std::cout << "Đã huỷ việc xoá sản phẩm.\n";
            }
            break;
        }
    }

    if (!found)
    {
        std::cout << "Không tìm thấy sản phẩm có mã " << product_id << std::endl;
    }
}

// Xuất kho theo yêu cầu của đầu bếp
void processChefRequest()
{
    // Kiểm tra xem có đầu bếp nào trong hệ thống không
    if (chef_count == 0)
    {
        std::cout << "Không có đầu bếp nào trong hệ thống. Vui lòng thêm đầu bếp trước.\n";
        return;
    }

    // Hiển thị danh sách đầu bếp
    displayChefs();

    std::string chef_id;
    std::cout << "Nhập mã đầu bếp yêu cầu xuất kho: ";
    std::cin >> chef_id;

    // Xử lý yêu cầu xuất kho
    processRequest(chef_id);
}

// Thống kê giá trị hàng tồn kho
void inventoryValueReport()
{
    std::cout << "\n===== BÁO CÁO GIÁ TRỊ HÀNG TỒN KHO =====\n";

    if (product_count == 0)
    {
        std::cout << "Kho không có sản phẩm nào.\n";
        return;
    }

    const int idWidth = 10;
    const int nameWidth = 25;
    const int qtyWidth = 10;
    const int priceWidth = 15;
    const int valueWidth = 15;
    const int totalWidth = idWidth + nameWidth + qtyWidth + priceWidth + valueWidth + 6;

    // Vẽ header của bảng
    drawTableLine(totalWidth);
    std::cout << "| " << std::left << std::setw(idWidth) << "Mã SP"
              << "| " << std::setw(nameWidth) << "Tên sản phẩm"
              << "| " << std::setw(qtyWidth) << "Số lượng"
              << "| " << std::setw(priceWidth) << "Đơn giá"
              << "| " << std::setw(valueWidth) << "Thành tiền" << "|" << std::endl;
    drawTableLine(totalWidth);

    double total_value = 0.0;

    for (int i = 0; i < product_count; i++)
    {
        double value = inventory[i].getQuantity() * inventory[i].getPrice();
        total_value += value;

        std::cout << "| " << std::left << std::setw(idWidth) << inventory[i].getId()
                  << "| " << std::setw(nameWidth) << inventory[i].getName()
                  << "| " << std::setw(qtyWidth) << inventory[i].getQuantity()
                  << "| " << std::setw(priceWidth) << std::fixed << std::setprecision(2) << inventory[i].getPrice()
                  << "| " << std::setw(valueWidth) << std::fixed << std::setprecision(2) << value << "|" << std::endl;
    }

    drawTableLine(totalWidth);
    std::cout << "| " << std::left << std::setw(totalWidth - 2) << "TỔNG GIÁ TRỊ HÀNG TỒN KHO" << "|" << std::endl;
    std::cout << "| " << std::left << std::setw(totalWidth - 2) << std::fixed << std::setprecision(2) << total_value << "|" << std::endl;
    drawTableLine(totalWidth);
}

// Thống kê hàng xuất kho theo thời gian
void inventoryOutReport()
{
    std::string start_date, end_date;

    std::cout << "\n===== BÁO CÁO HÀNG XUẤT KHO THEO THỜI GIAN =====\n";
    std::cout << "Nhập ngày bắt đầu (DD/MM/YYYY): ";
    std::cin.ignore();
    std::getline(std::cin, start_date);
    std::cout << "Nhập ngày kết thúc (DD/MM/YYYY): ";
    std::getline(std::cin, end_date);

    int start_day, start_month, start_year;
    int end_day, end_month, end_year;

    if (sscanf(start_date.c_str(), "%d/%d/%d", &start_day, &start_month, &start_year) != 3 ||
        sscanf(end_date.c_str(), "%d/%d/%d", &end_day, &end_month, &end_year) != 3)
    {
        std::cout << "Định dạng ngày không hợp lệ!\n";
        return;
    }

    // Tạo bảng thống kê
    std::cout << "\n===== BÁO CÁO HÀNG XUẤT KHO TỪ " << start_date << " ĐẾN " << end_date << " =====\n";

    if (out_record_count == 0)
    {
        std::cout << "Không có phiếu xuất kho nào trong hệ thống.\n";
        return;
    }

    bool found = false;

    for (int i = 0; i < out_record_count; i++)
    {
        std::string record_date = out_records[i].getDate();
        int record_day, record_month, record_year;

        if (sscanf(record_date.c_str(), "%d/%d/%d", &record_day, &record_month, &record_year) == 3)
        {
            // Kiểm tra xem phiếu có nằm trong khoảng thời gian không
            bool in_range = false;

            if (record_year > start_year && record_year < end_year)
            {
                in_range = true;
            }
            else if (record_year == start_year && record_year == end_year)
            {
                if (record_month > start_month && record_month < end_month)
                {
                    in_range = true;
                }
                else if (record_month == start_month && record_month == end_month)
                {
                    if (record_day >= start_day && record_day <= end_day)
                    {
                        in_range = true;
                    }
                }
                else if (record_month == start_month && record_month != end_month)
                {
                    if (record_day >= start_day)
                    {
                        in_range = true;
                    }
                }
                else if (record_month != start_month && record_month == end_month)
                {
                    if (record_day <= end_day)
                    {
                        in_range = true;
                    }
                }
            }
            else if (record_year == start_year && record_year != end_year)
            {
                if (record_month > start_month || (record_month == start_month && record_day >= start_day))
                {
                    in_range = true;
                }
            }
            else if (record_year != start_year && record_year == end_year)
            {
                if (record_month < end_month || (record_month == end_month && record_day <= end_day))
                {
                    in_range = true;
                }
            }

            if (in_range)
            {
                found = true;
                std::cout << "\nPhiếu xuất kho #" << (i + 1) << ":\n";
                out_records[i].display();
            }
        }
    }

    if (!found)
    {
        std::cout << "Không có phiếu xuất kho nào trong khoảng thời gian này.\n";
    }
}

// Thống kê hàng nhập kho theo thời gian
void inventoryInReport()
{
    std::string start_date, end_date;

    std::cout << "\n===== BÁO CÁO HÀNG NHẬP KHO THEO THỜI GIAN =====\n";
    std::cout << "Nhập ngày bắt đầu (DD/MM/YYYY): ";
    std::cin.ignore();
    std::getline(std::cin, start_date);
    std::cout << "Nhập ngày kết thúc (DD/MM/YYYY): ";
    std::getline(std::cin, end_date);

    int start_day, start_month, start_year;
    int end_day, end_month, end_year;

    if (sscanf(start_date.c_str(), "%d/%d/%d", &start_day, &start_month, &start_year) != 3 ||
        sscanf(end_date.c_str(), "%d/%d/%d", &end_day, &end_month, &end_year) != 3)
    {
        std::cout << "Định dạng ngày không hợp lệ!\n";
        return;
    }

    // Tạo bảng thống kê
    std::cout << "\n===== BÁO CÁO HÀNG NHẬP KHO TỪ " << start_date << " ĐẾN " << end_date << " =====\n";

    if (in_record_count == 0)
    {
        std::cout << "Không có phiếu nhập kho nào trong hệ thống.\n";
        return;
    }

    bool found = false;
    double total_value = 0.0;

    for (int i = 0; i < in_record_count; i++)
    {
        // Lưu ý: Trong lớp InventoryInRecord, chúng ta cần có một getter cho delivery_date
        // Tôi sẽ giả định rằng có phương thức getDeliveryDate()
        std::string record_date = in_records[i].getDeliveryDate();
        int record_day, record_month, record_year;

        if (sscanf(record_date.c_str(), "%d/%d/%d", &record_day, &record_month, &record_year) == 3)
        {
            // Kiểm tra xem phiếu có nằm trong khoảng thời gian không
            bool in_range = false;

            if (record_year > start_year && record_year < end_year)
            {
                in_range = true;
            }
            else if (record_year == start_year && record_year == end_year)
            {
                if (record_month > start_month && record_month < end_month)
                {
                    in_range = true;
                }
                else if (record_month == start_month && record_month == end_month)
                {
                    if (record_day >= start_day && record_day <= end_day)
                    {
                        in_range = true;
                    }
                }
                else if (record_month == start_month && record_month != end_month)
                {
                    if (record_day >= start_day)
                    {
                        in_range = true;
                    }
                }
                else if (record_month != start_month && record_month == end_month)
                {
                    if (record_day <= end_day)
                    {
                        in_range = true;
                    }
                }
            }
            else if (record_year == start_year && record_year != end_year)
            {
                if (record_month > start_month || (record_month == start_month && record_day >= start_day))
                {
                    in_range = true;
                }
            }
            else if (record_year != start_year && record_year == end_year)
            {
                if (record_month < end_month || (record_month == end_month && record_day <= end_day))
                {
                    in_range = true;
                }
            }

            if (in_range)
            {
                found = true;
                std::cout << "\nPhiếu nhập kho #" << (i + 1) << ":\n";
                in_records[i].display();
                total_value += in_records[i].calculateTotalPrice();
            }
        }
    }

    if (found)
    {
        std::cout << "\n====================================\n";
        std::cout << "TỔNG GIÁ TRỊ NHẬP KHO: " << std::fixed << std::setprecision(2) << total_value << std::endl;
        std::cout << "====================================\n";
    }
    else
    {
        std::cout << "Không có phiếu nhập kho nào trong khoảng thời gian này.\n";
    }
}

// Phương thức nhập dữ liệu mẫu để kiểm thử
// void loadSampleData()
// {
//     // Thêm một số sản phẩm mẫu vào kho
//     inventory[product_count++] = Product("P001", "Gạo", 100, 15000, "30/12/2025");
//     inventory[product_count++] = Product("P002", "Mì ăn liền", 200, 3500, "15/05/2025");
//     inventory[product_count++] = Product("P003", "Nước mắm", 50, 25000, "10/10/2026");
//     inventory[product_count++] = Product("P004", "Dầu ăn", 30, 40000, "25/05/2025");
//     inventory[product_count++] = Product("P005", "Muối", 80, 7000, "31/12/2030");

//     // Thêm một số đầu bếp mẫu
//     chefs[chef_count++] = ChefStaff("C001", "Nguyễn Văn A", "0987654321");
//     chefs[chef_count++] = ChefStaff("C002", "Trần Thị B", "0912345678");

//     // Thêm một số nhà cung cấp mẫu
//     suppliers[supplier_count++] = Supplier("S001", "Công ty TNHH Thực phẩm ABC", "123 Đường XYZ, Quận 1, TP.HCM", "0289123456");
//     suppliers[supplier_count++] = Supplier("S002", "Công ty CP Thực phẩm DEF", "456 Đường UVW, Quận 2, TP.HCM", "0289654321");

//     std::cout << "Đã tải dữ liệu mẫu thành công.\n";
// }

// Phương thức hiển thị menu chính
void displayMainMenu()
{
    std::cout << "\n============= QUẢN LÝ KHO NHÀ HÀNG =============\n";
    std::cout << "1. Quản lý sản phẩm\n";
    std::cout << "2. Quản lý đầu bếp\n";
    std::cout << "3. Quản lý nhà cung cấp\n";
    std::cout << "4. Quản lý xuất/nhập kho\n";
    std::cout << "5. Quản lý đơn đặt hàng\n";
    std::cout << "6. Thống kê báo cáo\n";
    std::cout << "7. Tải dữ liệu mẫu\n";
    std::cout << "8. Thông tin thủ kho\n";
    std::cout << "0. Thoát\n";
    std::cout << "================================================\n";
    std::cout << "Chọn chức năng: ";
}

// Phương thức hiển thị menu quản lý sản phẩm
void displayProductMenu()
{
    std::cout << "\n============= QUẢN LÝ SẢN PHẨM =============\n";
    std::cout << "1. Xem danh sách sản phẩm\n";
    std::cout << "2. Thêm sản phẩm mới\n";
    std::cout << "3. Chỉnh sửa thông tin sản phẩm\n";
    std::cout << "4. Xóa sản phẩm\n";
    std::cout << "5. Tìm kiếm sản phẩm theo mã\n";
    std::cout << "6. Tìm kiếm sản phẩm theo tên\n";
    std::cout << "7. Kiểm tra sản phẩm sắp hết hạn\n";
    std::cout << "8. Kiểm tra sản phẩm đã hết hạn\n";
    std::cout << "9. Kiểm tra sản phẩm sắp hết hàng\n";
    std::cout << "0. Quay lại\n";
    std::cout << "===========================================\n";
    std::cout << "Chọn chức năng: ";
}

// Phương thức hiển thị menu quản lý đầu bếp
void displayChefMenu()
{
    std::cout << "\n============= QUẢN LÝ ĐẦU BẾP =============\n";
    std::cout << "1. Xem danh sách đầu bếp\n";
    std::cout << "2. Thêm đầu bếp mới\n";
    std::cout << "0. Quay lại\n";
    std::cout << "==========================================\n";
    std::cout << "Chọn chức năng: ";
}

// Phương thức hiển thị menu quản lý nhà cung cấp
void displaySupplierMenu()
{
    std::cout << "\n============= QUẢN LÝ NHÀ CUNG CẤP =============\n";
    std::cout << "1. Xem danh sách nhà cung cấp\n";
    std::cout << "2. Thêm nhà cung cấp mới\n";
    std::cout << "0. Quay lại\n";
    std::cout << "==============================================\n";
}
int main()
{
    displayMainMenu();
    return 0;
}