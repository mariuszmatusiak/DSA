#ifndef DSA_ADAPTER_H
#define DSA_ADAPTER_H

class StoreDatabase {
public:
    void updateDatabase() {}
};

class StorePaymentService {
public:
    void handlePayment() {}
};

class StoreMessagingService {
public:
    void displayStatus() {}
};

/**
 * A complex subsystem wrapper and API gateway - facade
 */
class StoreSystemFacade {
private:
    StoreDatabase db;
    StorePaymentService ps;
    StoreMessagingService ms;
public:
    StoreSystemFacade() : db(), ps(), ms() {}
    void make_purchase() {
        ps.handlePayment();
        db.updateDatabase();
        ms.displayStatus();
    }
};

/*
int main (void) {
    StoreSystemFacade systemFacade{};
    systemFacade.make_purchase();
}
*/

#endif /* DSA_ADAPTER_H */
