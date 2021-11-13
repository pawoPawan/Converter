//
//  main.cpp
//  Converter
//
//  Created by Pawan Kumar on 05/11/21.
//

#include <iostream>

#include <string>

#include "converterservices.hpp"
#include "converterconstants.h"

// Factory
#include "ICreateFactory.hpp"

// Document
#include "IDocument.hpp"
using namespace std;

void Converter(string & istrFileLocation, string & iToFileExtension);

int main(int argc, const char * argv[]) {
    string istrFileLocation = "";
    //istrFileLocation = "/Users/pawankumar/Desktop/Shapr3D/OBJ/Skull_v3_L2.123c1407fc1e-ea5c-4cb9-9072-d28b8aba4c36/12140_Skull_v3_L2.obj";
    string strToExtension = " ";
    cout << "Enter file to Convert(Full Path of File): ";
    cin >> istrFileLocation;
    
    cout << "Enter Out File Type: ";
    cin >> strToExtension;
    
    Converter(istrFileLocation,strToExtension);

    return 0;
}

void Converter(string & istrFileLocation, string & iToFileExtension)
{
    ICreateFactory * pIFactory = nullptr;
    IDocument * pDoc = nullptr;
    string strOutPutFile="";
    // Create Document Factory
    pIFactory = ICreateFactory::GetFactory();
    
    if(pIFactory == nullptr)
    {
        cout << "Factory creation failed" << endl;
        goto Escapeway;
    }
    
    // Get Document Instance from input file
    pDoc = pIFactory->GetInstanceFromFile(istrFileLocation);
    if(pDoc == nullptr)
    {
        cout << "Document creation failed" << endl;
        goto Escapeway;
    }
    
    // Convert document from one format to another
    pDoc->ConvertDocument(iToFileExtension,strOutPutFile);
    
    Escapeway:
    delete pIFactory;
    pIFactory = nullptr;
    delete pDoc;
    pDoc = nullptr;
}
