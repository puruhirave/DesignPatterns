//Define various Momos Decorators

#ifndef MOMO_DECORATOR_H
#define MOMO_DECORATOR_H

#include "stdafx.h"
#include "IMomos.h"
#include <iostream>
#include <string>
using namespace std;

class MomoDecorator : public IMomo {
public:
    MomoDecorator(IMomo* m) : mDecorator(m) {}
    virtual void operator()() = 0;
    virtual void addCost(int addCost) = 0;
    IMomo* get() { return mDecorator; }
protected:
    MomoDecorator(const MomoDecorator& dec) : mDecorator(dec.mDecorator) {}
    IMomo* mDecorator;
};

class FriedMomo : public MomoDecorator {
public:
    FriedMomo(IMomo* m) : MomoDecorator(m) {}
    ~FriedMomo() {}
    void operator()() {
        cout << " Shalow Fried ";
        addCost(10);
        (*get())();
    }
    void addCost(int cost) {
        get()->addCost(cost);
    };

};

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

class ChocolateMomo : public MomoDecorator {
public:
    ChocolateMomo(IMomo* m) : MomoDecorator(m) {}
    ~ChocolateMomo() {}
    void operator()() {
        cout << " Decorated with Chocolate ";
        addCost(20);
        (*get())();
    }
    void addCost(int cost) {
        get()->addCost(cost);
    };
};

#endif