#include "Payment.h"

CardPayment::CardPayment(const std::string& num) : cardNumber(num) {}
void CardPayment::pay(double amount) {
    std::cout << "Оплата картой " << cardNumber << ": " << amount << " руб.\n";
}

EWalletPayment::EWalletPayment(const std::string& id) : walletId(id) {}
void EWalletPayment::pay(double amount) {
    std::cout << "Оплата электронным кошельком " << walletId << ": " << amount << " руб.\n";
}
