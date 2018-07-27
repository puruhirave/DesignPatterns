// Decorator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <memory>
#include "IMomos.h"
#include "MomoTypes.h"
#include "MomoDecorator.h"
#include <list>
#include <vector>
using namespace std;

class MomoStore {
public:
    MomoStore() {}
    ~MomoStore() {}
    void addOrder(IMomo* m)
    {
        orders.push_back(m);
    }
    void executeOrders()
    {
        cout << "...Execute orders..." << endl;
        while (!orders.empty()) {
            IMomo *m = orders.front();
            orders.pop_front();
            (*m)();
        }
    }
private:
    std::list<IMomo *> orders;
    MomoStore(const MomoStore &);
    MomoStore &operator =(const MomoStore &);
};

//Decorator driver code
int main()
{
    cout << "*** Decorator Demo (Momos Store) ***" << endl << endl;
    MomoStore store;

    //Veg momo -> Decorated with Shalow Fry
    std::shared_ptr<VegMomo> vegmomo = std::make_shared<VegMomo>("Green vegitables");
    std::shared_ptr<FriedMomo> friedmomo = std::make_shared<FriedMomo>(vegmomo.get());
    store.addOrder(friedmomo.get());

    //NonVeg momo -> Decorated with Shezvan saus
    std::shared_ptr<NonVegMomo> nonVegMomo = std::make_shared<NonVegMomo>("Chicken");
    std::shared_ptr<ShezvanMomo> szmomo = std::make_shared<ShezvanMomo>(nonVegMomo.get());
    store.addOrder(szmomo.get());

    //Veg momo -> Decorate with Fry -> Decorated with chocolate
    std::shared_ptr<VegMomo> vegmomo1 = std::make_shared<VegMomo>("Cryspy items");
    std::shared_ptr<FriedMomo> friedmomo1 = std::make_shared<FriedMomo>(vegmomo1.get());
    std::shared_ptr<ChocolateMomo> chocomomo = std::make_shared<ChocolateMomo>(friedmomo1.get());
    store.addOrder(chocomomo.get());

    store.executeOrders();

    cin.get();
    return 0;
}


