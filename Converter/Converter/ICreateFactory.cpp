//
//  ICreateFactory.cpp
//  Converter
//
//  Created by Pawan Kumar on 05/11/21.
//

#include "ICreateFactory.hpp"
#include "CreateFactory.hpp"

#include <iostream>
using namespace std;

ICreateFactory * ICreateFactory::GetFactory()
{
    cout << "ICreateFactory::GetFactory" << endl;
    return new CreateFactory();
}

