//
//  CreateFactory.hpp
//  Converter
//
//  Created by Pawan Kumar on 05/11/21.
//

#ifndef CreateFactory_hpp
#define CreateFactory_hpp

#include <stdio.h>
#include "ICreateFactory.hpp"
#include <string>

class IDocument;
class CreateFactory: public ICreateFactory
{
public:
    CreateFactory();
    ~CreateFactory();
    IDocument * GetInstanceFromFile(const std::string & iDocFile);
    IDocument * GetInstanceFromExtension(const std::string & iExtensionType);
private:
    void _GetFileExtension(const std::string & iDocFile, std::string & ostrExtension);
protected:
};
#endif /* CreateFactory_hpp */
