#pragma once
#include "User.h"
#include "Order.h"

class Customer : public User {
public:
    Customer(int uid, const std::string& uname, const std::string& uemail)
        : User(uid, uname, uemail, "customer") {}

    void createOrder(std::shared_ptr<Order> order) override {
        orders.push_back(order);
    }

    void viewOrderStatus(int orderId) override {
        auto it = std::find_if(orders.begin(), orders.end(),
            [orderId](const std::shared_ptr<Order>& o) { return o->getId() == orderId; });
        if (it != orders.end()) {
            std::cout << "Status: " << (*it)->getStatus() << std::endl;
        }
    }

    void cancelOrder(int orderId) override {
        auto it = std::find_if(orders.begin(), orders.end(),
            [orderId](const std::shared_ptr<Order>& o) { return o->getId() == orderId; });
        if (it != orders.end()) {
            (*it)->setStatus("canceled");
        }
    }

    void addToOrder(std::shared_ptr<Order> order, int productId, int quantity);
    void removeFromOrder(std::shared_ptr<Order> order, int productId);
    void makePayment(std::shared_ptr<Order> order);
};
