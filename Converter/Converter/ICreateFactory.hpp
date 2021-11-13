//
//  ICreateFactory.hpp
//  Converter
//
//  Created by Pawan Kumar on 05/11/21.
//

#ifndef ICreateFactory_hpp
#define ICreateFactory_hpp

#include <stdio.h>

#include <string>

class IDocument;
class ICreateFactory
{
public:
    virtual ~ICreateFactory(){};
    virtual IDocument * GetInstanceFromFile(const std::string & iDocFileType) = 0;
    virtual IDocument * GetInstanceFromExtension(const std::string & iExtensionType) = 0;
    static ICreateFactory * GetFactory();

private:

protected:

};
#endif /* ICreateFactory_hpp */
