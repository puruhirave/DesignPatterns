//Define interface for Momo dish

#ifndef MOMOS_H
#define MOMOS_H

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

class IMomo{
public:
    IMomo(){};
    virtual ~IMomo(){};
    virtual void operator()() = 0;
    virtual IMomo* get() = 0;
    virtual void addCost(int addCost) = 0;
private:
    IMomo(const IMomo &);
    IMomo &operator =(const IMomo &);
};

#endif