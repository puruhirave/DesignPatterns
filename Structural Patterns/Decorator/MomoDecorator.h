//Define various Momos Decorators

#ifndef MOMO_DECORATOR_H
#define MOMO_DECORATOR_H

#include "stdafx.h"
#include "IMomos.h"
#include <memory>
#include <iostream>
#include <string>
using namespace std;

class MomoDecorator : public IMomo {
public:
	MomoDecorator(std::unique_ptr<IMomo> m) : mDecorator(std::move(m)) {}
	virtual void operator()() = 0;
	virtual void addCost(int addCost) = 0;
	IMomo* get() { return mDecorator->get(); }
protected:
	MomoDecorator(const MomoDecorator& dec) : mDecorator(dec.mDecorator->get()) {}
	std::unique_ptr<IMomo> mDecorator;
};

class FriedMomo : public MomoDecorator {
public:
	FriedMomo(std::unique_ptr<IMomo> m) : MomoDecorator(std::move(m)) {}
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
	ShezvanMomo(std::unique_ptr<IMomo> m) : MomoDecorator(std::move(m)) {}
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
	ChocolateMomo(std::unique_ptr<IMomo> m) : MomoDecorator(std::move(m)) {}
	~ChocolateMomo() {}
	void operator()() {
		cout << " Decorated with Chocolate sause ";
		addCost(30);
		(*get())();
	}
	void addCost(int cost) { 
		get()->addCost(cost); 
	};
};

#endif
