//
//  IDocumentAbstract.cpp
//  Converter
//
//  Created by Pawan Kumar on 05/11/21.
//

#include "IDocumentAbstract.hpp"
#include <iostream>
#include <cstring>
#include <string>
using namespace std;


IDocumentAbstract::IDocumentAbstract()
{
    cout << "IDocumentAbstract::Constructor" << endl;
    _strNewFileName = "";
    _strDoCFileLocation = "";
    _strFileExtension = "";
}
IDocumentAbstract::IDocumentAbstract(const std::string & iDocFile)
{
    cout << "IDocumentAbstract::Constructor" << endl;
    _strNewFileName = "";
    _strDoCFileLocation = "";
    _strFileExtension = "";
    _SetFileLocation(iDocFile);
    _SetFileExtension(_GetFileExtension());
}
IDocumentAbstract::~IDocumentAbstract()
{
    cout << "IDocumentAbstract::Destructor" << endl;
}

void IDocumentAbstract::_SetFileLocation(string iFileLocation)
{
    _strDoCFileLocation = iFileLocation;
}

void IDocumentAbstract::_SetFileExtension(string iFileExtension)
{
    _strFileExtension = iFileExtension;
}
void IDocumentAbstract::_GetFileLocation(string & oFileLocation)
{
    oFileLocation = _strDoCFileLocation;
}

void IDocumentAbstract::GetFileExtension(std::string & ostrFileExt)
{
    ostrFileExt = _strFileExtension;
}

void IDocumentAbstract::_GetOutPutFileName(std::string istrFileExtension, std::string & oFileLocation)
{
    oFileLocation = _strNewFileName + "_Output" + "." + istrFileExtension;
}

//------------------- _GetFileExtension ---------------
string IDocumentAbstract::_GetFileExtension()
{
    // Find last dot in string
    string ostrExtension;
    int len = _strDoCFileLocation.length();
    int i = 0;
    for(i = len-1; i >= 0; i--)
        if(_strDoCFileLocation[i] == '.')break;
    
    for(int j = i+1; j < len; j++)
        ostrExtension += _strDoCFileLocation[j];
    
    for(int k =0;k < i; k++)
        _strNewFileName += _strDoCFileLocation[k];
    
    return ostrExtension;
}


