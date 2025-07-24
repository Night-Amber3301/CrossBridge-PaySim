#include <jsi/jsi.h>
#include "payment.hpp"
#include <memory>
using namespace facebook;

static std::unique_ptr<PaymentProcessor> processorPtr;

void install(jsi::Runtime& rt) {
    processorPtr = std::make_unique<PaymentProcessor>();

    auto authorize = jsi::Function::createFromHostFunction(
        rt,
        jsi::PropNameID::forAscii(rt, "authorizeCard"),
        2,
        [](jsi::Runtime& rt, const jsi::Value&, const jsi::Value* args, size_t) -> jsi::Value {
            std::string card = args[0].asString(rt).utf8(rt);
            double amount = args[1].asNumber();
            std::string txnId = processorPtr->authorizeCard(card, amount);
            return jsi::String::createFromUtf8(rt, txnId);
        });

    auto complete = jsi::Function::createFromHostFunction(
        rt,
        jsi::PropNameID::forAscii(rt, "completePayment"),
        1,
        [](jsi::Runtime& rt, const jsi::Value&, const jsi::Value* args, size_t) -> jsi::Value {
            std::string txn = args[0].asString(rt).utf8(rt);
            bool result = processorPtr->completePayment(txn);
            return jsi::Value(result);
        });

    auto refund = jsi::Function::createFromHostFunction(
        rt,
        jsi::PropNameID::forAscii(rt, "refundPayment"),
        1,
        [](jsi::Runtime& rt, const jsi::Value&, const jsi::Value* args, size_t) -> jsi::Value {
            std::string txn = args[0].asString(rt).utf8(rt);
            bool result = processorPtr->refundPayment(txn);
            return jsi::Value(result);
        });

    rt.global().setProperty(rt, "authorizeCard", std::move(authorize));
    rt.global().setProperty(rt, "completePayment", std::move(complete));
    rt.global().setProperty(rt, "refundPayment", std::move(refund));
}
