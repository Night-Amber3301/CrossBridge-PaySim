// main.cpp
#include "payment.hpp"
#include <iostream>

int main() {
    PaymentProcessor processor;

    std::string txnId = processor.authorizeCard("1234-5678-9012-3456", 99.99);
    if (txnId.empty()) {
        std::cout << "Authorization failed.\n";
        return 1;
    }

    std::cout << "Transaction Authorized: " << txnId << std::endl;

    if (processor.completePayment(txnId)) {
        std::cout << "Payment completed.\n";
    } else {
        std::cout << "Payment failed to complete.\n";
    }

    if (processor.refundPayment(txnId)) {
        std::cout << "Refund successful.\n";
    } else {
        std::cout << "Refund failed.\n";
    }

    return 0;
}
