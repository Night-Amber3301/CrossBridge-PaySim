public class NativePayment {
    static {
        System.loadLibrary("paysim_jni"); // Your C++ DLL name (without .dll)
    }

    public native String authorizeCard(String cardNum, double amount);
    public native boolean completePayment(String txnId);
    public native boolean refundPayment(String txnId);

    public static void main(String[] args) {
        NativePayment np = new NativePayment();

        String txnId = np.authorizeCard("4111111111111111", 100.50);
        System.out.println("Txn ID: " + txnId);

        boolean paid = np.completePayment(txnId);
        System.out.println("Payment complete: " + paid);

        boolean refunded = np.refundPayment(txnId);
        System.out.println("Payment refunded: " + refunded);
    }
}
