//
//  converterservices.hpp
//  Converter
//
//  Created by Pawan Kumar on 05/11/21.
//

#ifndef converterservices_hpp
#define converterservices_hpp

#include <stdio.h>
#include <string>
#include "converterconstants.h"
class IDocument;
class converterservices
{
public:

    static void GetAction(int iAction/*, Action & oAction*/);
    static void ConvertDocument(IDocument * ipFromDoc, const std::string istrToFileExtension,const std::string  istrOutPutFileName);

private:
    
    static void _ConvertFromOBJFile(IDocument * ipFromObjDoc, IDocument * ipToDoc, const std::string istrToFileExtension,std::string  istrOutPutFileName, std::vector<bool>  bTransform, std::vector<std::vector<double>> & idTransformationdetails);
    static void _ConvertFromOBJToSTL(IDocument * ipFromObjDoc, IDocument * ipToSTLDoc,std::string istrOutPutFileName, std::vector<bool> bTransform, std::vector<std::vector<double>> & idTransformationdetails);
};
#endif /* converterservices_hpp */
