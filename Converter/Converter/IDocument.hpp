//
//  IDocument.hpp
//  Converter
//
//  Created by Pawan Kumar on 05/11/21.
//

#ifndef IDocument_hpp
#define IDocument_hpp

#include <stdio.h>
#include <string>
class IDocument
{
public:
    virtual ~IDocument(){};

    // Convert Doument to desifred format
    virtual void ConvertDocument(std::string & istrToExtension, std::string & ostrOutPutFile) = 0;
    
    virtual void GetFileExtension(std::string & ostrFileExt) = 0;
    
    //virtual void ParseValuesFromOtherFormat(IDocument * iDocToParsing) = 0;
private:

protected:

};
#endif /* IDocument_hpp */
