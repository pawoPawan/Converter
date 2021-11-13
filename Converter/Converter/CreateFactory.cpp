//
//  CreateFactory.cpp
//  Converter
//
//  Created by Pawan Kumar on 05/11/21.
//

#include "CreateFactory.hpp"
#include "Document_OBJ.hpp"
#include "Document_STL.hpp"
#include <iostream>
#include <string>
using namespace std;

CreateFactory::CreateFactory()
{
    cout << "CreateFactory::Constructor" << endl;
}

CreateFactory::~CreateFactory()
{
    cout << "CreateFactory::Destructor" << endl;
}

IDocument * CreateFactory::GetInstanceFromFile(const string & iDocFile)
{
    cout << "CreateFactory::GetInstance" << endl;
    
    // Get file extension from file name
    string strExtension = "";
    _GetFileExtension(iDocFile,strExtension);
    // try to add some run time mechanism to instanciate object
    if(0 == strExtension.compare("obj"))
        return new Document_OBJ(iDocFile);
    else if (0 == strExtension.compare("stl"))
        return new Document_STL(iDocFile);
    else return nullptr;
}

IDocument * CreateFactory::GetInstanceFromExtension(const std::string & iExtensionType)
{
    if(0 == iExtensionType.compare("obj"))
        return new Document_OBJ();
    else if (0 == iExtensionType.compare("stl"))
        return new Document_STL();
    else return nullptr;
}

//------------------- _GetFileExtension ---------------
void CreateFactory::_GetFileExtension(const std::string & iDocFile, std::string & ostrExtension)
{
    // Find last dot in string
    int len = iDocFile.length();
    int i = 0;
    for(i = len-1; i >= 0; i--)
        if(iDocFile[i] == '.')break;
    
    for(int j = i+1; j < len; j++)
        ostrExtension += iDocFile[j];
}
