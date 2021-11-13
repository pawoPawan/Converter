//
//  IDocumentAbstract.hpp
//  Converter
//
//  Created by Pawan Kumar on 05/11/21.
//

#ifndef IDocumentAbstract_hpp
#define IDocumentAbstract_hpp

#include <stdio.h>
#include <string>
#include "IDocument.hpp"

class IDocumentAbstract : public IDocument
{
public:
    IDocumentAbstract();
    IDocumentAbstract(const std::string & iDocFile);
    virtual ~IDocumentAbstract();

    virtual void ConvertDocument(std::string & istrToExtension, std::string & ostrOutPutFile) = 0;
    virtual void GetFileExtension(std::string & ostrFileExt);
    //virtual void ParseValuesFromOtherFormat(IDocument * iDocToParsing);

private:
    std::string _GetFileExtension();
protected:
    void _SetFileExtension(std::string iFileExtension);
    void _SetFileLocation(std::string iFileExtension);
    
    void _GetFileLocation(std::string & oFileLocation);
    void _GetOutPutFileName(std::string istrFileExtension, std::string & oFileLocation);
    
    std::string _strDoCFileLocation;
    std::string _strFileExtension;
    std::string _strNewFileName;

};
#endif /* IDocumentAbstract_hpp */
