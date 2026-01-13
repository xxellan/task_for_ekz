#pragma once
#include <vector>
#include <memory>
#include <string>
#include <numeric>
#include "OrderItem.h"
#include "Payment.h"

class Order {
private:
    int id;
    std::string status;
    double totalPrice;
    std::vector<std::unique_ptr<OrderItem>> items;
    std::unique_ptr<Payment> payment;

public:
    Order(int oid) : id(oid), status("pending"), totalPrice(0.0) {}

    int getId() const { return id; }
    std::string getStatus() const { return status; }
    void setStatus(const std::string& s) { status = s; }

    void addItem(std::unique_ptr<OrderItem> item) {
        totalPrice += item->getPrice() * item->getQuantity();
        items.push_back(std::move(item));
    }

    void removeItem(int productId) {
        auto it = std::remove_if(items.begin(), items.end(),
            [productId](const std::unique_ptr<OrderItem>& i) { return i->getProductId() == productId; });
        items.erase(it, items.end());
    }

    double getTotalPrice() {
        return std::accumulate(items.begin(), items.end(), 0.0,
            [](double sum, const std::unique_ptr<OrderItem>& i) { return sum + i->getPrice() * i->getQuantity(); });
    }

    void setPayment(std::unique_ptr<Payment> p) { payment = std::move(p); }
    void pay() { if (payment) payment->pay(); }
};
