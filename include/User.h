#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Order.h"

class User {
protected:
    int id;
    std::string name;
    std::string email;
    std::string role;

public:
    std::vector<std::shared_ptr<Order>> orders;

    User(int uid, const std::string& uname, const std::string& uemail, const std::string& urole)
        : id(uid), name(uname), email(uemail), role(urole) {}

    virtual ~User() = default;

    virtual void createOrder(std::shared_ptr<Order> order) = 0;
    virtual void viewOrderStatus(int orderId) = 0;
    virtual void cancelOrder(int orderId) = 0;
};
