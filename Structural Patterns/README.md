# Structural Patterns
Structural design patterns are focused on how classes and objects can be composed, to form larger structures.
These patterns simplifies the structure by identifying the relationships.

## Decorator
* Category: Structural
* Intent:
   Inject additional responsibilities	to	an existing	object dynamically. Decorators	
  provide	a	flexible	alternative	to	subclassing.
	Decorator	has	both	an	is‐a	and	a	has‐a	relationship	to	
its	base	class.

![decoratorpattern](https://user-images.githubusercontent.com/6056609/43302516-ab9cc3ea-9188-11e8-82e5-cc85c8e594fc.png)

## Decorator Example : Momos Store

Decorator pattern usecase explained with one real life example as Momos store with different types of Momo Decorators.
For examples, abstract 'Momos' class used to create concreate Momos like Veg Momo and Non-Veg Momos.

The abstract Decorator class 'MomoDecorator' created by inheriting from 'Momo' interface and different concrete Decorators created like 'Fried Momo', 'Shezvan Momo', 'Chocolate Momo' etc.

![momodecorator](https://user-images.githubusercontent.com/6056609/43451378-70210d60-94d2-11e8-8996-45d032983361.png)

* The Decorator pattern is implemented with C++11 features. This code explains how the Momo objects are decorated at runtime without changing there behaviour? 
* The IMomo abstract class provided with 'operator()' pure virtual method as operation to be executed by concrete Momo object. 
```C
class IMomo{
public:
    IMomo(){};
    virtual ~IMomo(){};
    virtual void operator()() = 0;
    ....
    ...
    }
```

The Decorator 'is-a' Momo object and also 'has-a' pointer to the concreate Momo object as 'mDecorator'. Also it decorates and adds additional decoration cost by its own and calls the concrete Momo objects operation from 'operator()'.

```C
class ShezvanMomo : public MomoDecorator {
public:
    ShezvanMomo(IMomo* m) : MomoDecorator(m) {}
    ~ShezvanMomo() {}
    void operator()() {
        cout << " Decorated with special Sezvan sause and soup ";
        addCost(10);
        (*get())();
    }
    void addCost(int cost) {
        get()->addCost(cost);
    };
};
```


* Following driver code creates VegMomo, NonVeg Momos and decorates these objects.
```C
//Decorator driver code
int main()
{
    cout << "*** Decorator Demo (Momos Store) ***" << endl << endl;
    MomoStore store;

    //Veg momo -> Decorated with Shalow Fry
    std::unique_ptr<IMomo> vegmomo = std::make_unique<VegMomo>("Green vegitables");
    std::unique_ptr<IMomo> friedmomo = std::make_unique<FriedMomo>(vegmomo.get());
    store.addOrder(friedmomo.get());

    //NonVeg momo -> Decorated with Shezvan saus
    std::unique_ptr<IMomo> nonVegMomo = std::make_unique<NonVegMomo>("Chicken");
    std::unique_ptr<IMomo> szmomo = std::make_unique<ShezvanMomo>(nonVegMomo.get());
    store.addOrder(szmomo.get());

    //Veg momo -> Decorate with Fry -> Decorated with chocolate
    std::unique_ptr<IMomo> vegmomo1 = std::make_unique<VegMomo>("Cryspy items");
    std::unique_ptr<IMomo> friedmomo1 = std::make_unique<FriedMomo>(vegmomo1.get());
    std::unique_ptr<IMomo> chocomomo = std::make_unique<ChocolateMomo>(friedmomo1.get());
    store.addOrder(chocomomo.get());

    store.executeOrders();
    
    return 0;
}
```
* Why Unique pointer used while creating Momo objects and decorators? Why not shared pointer?
```C
First thing is that raw pointer is not used because not just to handle automatic life time of Momo Objects,
but otherwise it would require to call delete operator on Momo object in both driver code and MomoStore code also. 

Lets take real life scenario, where Momo manufactures has sold the Momo's to Seller/Distributor.
Now the ownership is changed from Manufacturer to Seller. Manufacturer no more requires ownership of these objects. 
So shared pointer not required. 
And the Decorator is new owner and he can also pass its ownershipt to another Decorator.

See the last scenario of ChocolateMomo.
```

Link to source code:
https://github.com/puruhirave/DesignPatterns/tree/master/Structural%20Patterns/Decorator

 Following screenshot shows last scenario of Veg Momo object decorated dynamically with FriedMomo Decorator and ChocolateMomo Decorator.

![objects](https://user-images.githubusercontent.com/6056609/43304796-131678c2-9193-11e8-9546-22b2d7fb26c5.png)
