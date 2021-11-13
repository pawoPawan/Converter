//
//  Document_STL.hpp
//  Converter
//
//  Created by Pawan Kumar on 10/11/21.
//

#ifndef Document_STL_hpp
#define Document_STL_hpp

#include <stdio.h>
#include <vector>
#include "IDocumentAbstract.hpp"
#include "converterconstants.h"


class Document_STL : public IDocumentAbstract
{
public:
    Document_STL();
    Document_STL(const std::string & iDocFile);
    ~Document_STL();
    void ConvertDocument(std::string & istrToExtension, std::string & ostrOutPutFile);
    void AppendTriangles(std::vector<triangle> & iArrayOfTriangles);
    void SetFileLocation(std::string istrFileLocation);
    void WriteSTLFile();
private:
    std::vector<triangle> _tri_faces;
protected:
    
};
#endif /* Document_STL_hpp */
