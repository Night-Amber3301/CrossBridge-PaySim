#include <jni.h>
#include <string>
#include "payment.hpp"

static PaymentProcessor processor;

extern "C" JNIEXPORT jstring JNICALL
Java_NativePayment_authorizeCard(JNIEnv* env, jobject, jstring cardNum, jdouble amount) {
    const char* nativeCard = env->GetStringUTFChars(cardNum, 0);
    std::string txnId = processor.authorizeCard(nativeCard, amount);
    env->ReleaseStringUTFChars(cardNum, nativeCard);
    return env->NewStringUTF(txnId.c_str());
}

extern "C" JNIEXPORT jboolean JNICALL
Java_NativePayment_completePayment(JNIEnv* env, jobject, jstring txnId) {
    const char* nativeTxn = env->GetStringUTFChars(txnId, 0);
    bool result = processor.completePayment(nativeTxn);
    env->ReleaseStringUTFChars(txnId, nativeTxn);
    return result ? JNI_TRUE : JNI_FALSE;
}

extern "C" JNIEXPORT jboolean JNICALL
Java_NativePayment_refundPayment(JNIEnv* env, jobject, jstring txnId) {
    const char* nativeTxn = env->GetStringUTFChars(txnId, 0);
    bool result = processor.refundPayment(nativeTxn);
    env->ReleaseStringUTFChars(txnId, nativeTxn);
    return result ? JNI_TRUE : JNI_FALSE;
}
