#include "Product.h"

Product::Product(int pid, const std::string& pname, double pprice, int pstock)
    : id(pid), name(pname), price(pprice), stock(pstock) {}

int Product::getId() const { return id; }
std::string Product::getName() const { return name; }
double Product::getPrice() const { return price; }
int Product::getStock() const { return stock; }

void Product::setPrice(double p) { price = p; }
void Product::setStock(int s) { stock = s; }

void Product::displayInfo() const {
    std::cout << "ID: " << id << ", " << name << ", Цена: " << price
              << ", На складе: " << stock << "\n";
}
