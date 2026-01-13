#pragma once
#include "User.h"
#include "DatabaseConnection.h"

class Manager : public User {
public:
    Manager(int uid, const std::string& uname, const std::string& uemail)
        : User(uid, uname, uemail, "manager") {}

    void createOrder(std::shared_ptr<Order> order) override {}
    void viewOrderStatus(int orderId) override {}
    void cancelOrder(int orderId) override {}

    void approveOrder(int orderId, DatabaseConnection<std::string>& db);
    void updateStock(int productId, int quantity, DatabaseConnection<std::string>& db);
};
