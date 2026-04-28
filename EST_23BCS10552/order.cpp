#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

struct Item {
    int id;
    string name;
    double price;
    int quantity;
};

class Inventory {
public:
    void addItem(const Item& item) {
        items_[item.id] = item;
    }

    bool checkStock(int itemId, int needed) const {
        auto it = items_.find(itemId);
        if (it == items_.end()) return false;
        return it->second.quantity >= needed;
    }

    bool reserveStock(int itemId, int qty) {
        auto it = items_.find(itemId);
        if (it == items_.end()) return false;
        if (it->second.quantity < qty) return false;
        it->second.quantity -= qty;
        return true;
    }

    const Item* getItem(int itemId) const {
        auto it = items_.find(itemId);
        if (it == items_.end()) return nullptr;
        return &it->second;
    }

private:
    unordered_map<int, Item> items_;
};

class PaymentGateway {
public:
    bool processPayment(const std::string& userEmail, double amount) {
        cout<< "[Payment] Processing payment for " << userEmail << ": Rs" << amount << "\n";
        if (amount > 1000.0) {
            cout << "[Payment] Payment declined (amount too large in mock).\n";
            return false;
        }
        cout << "[Payment] Payment successful.\n";
        return true;
    }
};

class EmailService {
public:
    void sendEmail(const std::string& to, const std::string& subject, const std::string& body) {
        cout << "[Email] Sending email to: " << to << "\n";
        cout << "[Email] Subject: " << subject << "\n";
        cout << "[Email] Body: " << body << "\n";
    }
};

class OrderService {
public:
    OrderService(Inventory& inv, PaymentGateway& pg, EmailService& es)
        : inv_(inv), pg_(pg), es_(es) {}

    bool placeOrder(const std::string& userEmail, int itemId, int qty) {
        cout << "\n[Order] Placing order for " << userEmail << " - Item " << itemId << " x" << qty << "\n";

        if (!inv_.checkStock(itemId, qty)) {
            cout << "[Order] Failed: insufficient stock for item " << itemId << "\n";
            return false;
        }

        const Item* item = inv_.getItem(itemId);
        if (!item) {
            cout << "[Order] Failed: item not found\n";
            return false;
        }
k
        double total = item->price * qty;
            cout << "[Order] Total amount: Rs" << total << "\n";

        if (!pg_.processPayment(userEmail, total)) {
            cout << "[Order] Failed: payment declined\n";
            return false;
        }

        if (!inv_.reserveStock(itemId, qty)) {
            cout << "[Order] Failed: could not reserve stock (race)\n";
            return false;
        }

        string subject = "Order confirmation";
        string body = "Thank you for your order of " + std::to_string(qty) + " x " + item->name + ". Total: Rs" + std::to_string(total);
        es_.sendEmail(userEmail, subject, body);

        std::cout << "[Order] Order placed successfully for " << userEmail << "\n";
        return true;
    }

private:
    Inventory& inv_;
    PaymentGateway& pg_;
    EmailService& es_;
};

int main() {
    Inventory inv;
    inv.addItem({1, "Widget", 199.99, 10});
    inv.addItem({2, "Gadget", 1200.00, 2});

    PaymentGateway pg;
    EmailService es;
    OrderService svc(inv, pg, es);

    svc.placeOrder("alice@example.com", 1, 2);

    svc.placeOrder("bob@example.com", 2, 1);

    svc.placeOrder("carol@example.com", 1, 20);

    return 0;
}
#include <iostream>
using namespace std;
class stock {
public:
  int stockId;
  string name;
  int quantity;

public:
  stock(int id, string n, int q) {
    stockId = id;
    name = n;
    quantity = q;
  }
}; class Order {
private:
  int orderId;
  string orderDate;
  double orderAmount;
  int quantity;

public:
  Order(int id, string date, double amount, int quantity) {
    orderId = id;
    orderDate = date;
    orderAmount = amount;
    quantity = quantity;
  }
  void stockcheck() {
    stock s1(1, "Product1", 10);
    if (quantity > s1.quantity) {
      cout << "Stock not available" << endl;
    } else if (s1.quantity == 0) {
      cout << "Stock not available" << endl;
    } else {
      cout << "Stock available" << endl;
    }
  }
};
