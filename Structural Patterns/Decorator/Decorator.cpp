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
    void addOrder(shared_ptr<IMomo> m)
    {
        orders.push_back(m);
    }
    void executeOrders()
    {
        cout << "...Execute orders..." << endl;
	while (!orders.empty()) {
		auto m = orders.front();
		orders.pop_front();
		(*m)();
	}
    }
private:
    std::list<shared_ptr<IMomo>> orders;
    MomoStore(const MomoStore &);
    MomoStore &operator =(const MomoStore &);
};

//Decorator driver code
int main()
{
    cout << "*** Decorator Demo (Momos Store) ***" << endl << endl;
    MomoStore store;

    	//Veg momo -> Decorated with Shalow Fry
	std::unique_ptr<IMomo> vegmomo = std::make_unique<VegMomo>("Green vegitables");
	std::unique_ptr<IMomo> friedmomo = std::make_unique<FriedMomo>(std::move(vegmomo));
	store.addOrder(std::move(friedmomo));

	//NonVeg momo -> Decorated with Shezvan saus
	std::unique_ptr<IMomo> nonVegMomo = std::make_unique<NonVegMomo>("Chicken");
	std::unique_ptr<IMomo> szmomo = std::make_unique<ShezvanMomo>(std::move(nonVegMomo));
	store.addOrder(std::move(szmomo));

	//Veg momo -> Decorate with Fry -> Decorated with chocolate
	std::unique_ptr<IMomo> vegmomo1 = std::make_unique<VegMomo>("Chocolate Caramel");
	std::unique_ptr<IMomo> friedmomo1 = std::make_unique<FriedMomo>(std::move(vegmomo1));
	std::unique_ptr<IMomo> chocomomo = std::make_unique<ChocolateMomo>(std::move(friedmomo1));
	store.addOrder(std::move(chocomomo));

    store.executeOrders();

    cin.get();
    return 0;
}


