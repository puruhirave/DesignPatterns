//Define different Momo types

#ifndef MOMOTYPES_H
#define MOMOTYPES_H

#include "stdafx.h"
#include "IMomos.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class VegMomo : public IMomo {
public:
    VegMomo(string items) :ingredients(items), total_cost(50) {}
    ~VegMomo() {}
    void operator()() {
        prepare();
    }
    void addCost(int c) { total_cost += c; }
    void addDescription(string des) { ingredients.append(des); };
    IMomo* get() { return this; }

private:

    VegMomo(const VegMomo&);
    string ingredients;
    int total_cost;
    void prepare() {
        std::stringstream sTotal;
        sTotal << total_cost;
        cout << " Veg Momo with " + ingredients + " (TotalCost: " + sTotal.str() + ")" << endl;
    }
};

class NonVegMomo : public IMomo {
public:
    NonVegMomo(string items) :ingredients(items), total_cost(60) {}
    ~NonVegMomo() {}
    void operator()() {
        prepare();
    }
    void addCost(int c) { total_cost += c; }
    void addDescription(string des) { ingredients.append(des); };
    IMomo* get() { return this; }

private:
    NonVegMomo(const NonVegMomo&);
    string ingredients;
    int total_cost;
    void prepare() {
        std::stringstream sTotal;
        sTotal << total_cost;
        cout << " Non-Veg Momo with " + ingredients + " (TotalCost: " + sTotal.str() + ")" << endl << endl;
    }
};

#endif