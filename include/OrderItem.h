#pragma once

class OrderItem {
private:
    int productId;
    int quantity;
    double price;
public:
    OrderItem(int pid, int qty, double p) : productId(pid), quantity(qty), price(p) {}
    int getProductId() const { return productId; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }
};
