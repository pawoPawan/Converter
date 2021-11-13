//
//  Document_OBJ.hpp
//  Converter
//
//  Created by Pawan Kumar on 05/11/21.
//

#ifndef Document_OBJ_hpp
#define Document_OBJ_hpp

#include <stdio.h>
#include <vector>

#include "IDocumentAbstract.hpp"
#include "converterconstants.h"

class Document_OBJ : public IDocumentAbstract
{
public:
    Document_OBJ();
    Document_OBJ(const std::string & iDocFile);
    ~Document_OBJ();
    void ConvertDocument(std::string & istrToExtension, std::string & ostrOutPutFile);
    void GetArrayOfFace(std::vector<face> & oArrayOfFace);
    void GetArrayOfGeometryVertex(std::vector<vertex> & oArrayOfGeoVertex);
    void GetArrayOfTextureVertex(std::vector<vertex> & oArrayOfTextureVertex);
    void GetArrayOfNormalVertex(std::vector<vertex> & oArrayOfNormalVertex);
    //friend class Document_STL;
private:
    
    void _InitialiseVariables();
    
    // Parse OBJ File
    void _ParseOBJFile();
    
    // Read File
    void _Read_File();
    
    // Append Vertex
    void _AppendVertex(const std::string & strLineToAppend);
    
    // Append Face
    void _AppendFace(const std::string & strLineToAppend);
    
    // Append Geometric, Texture and Normal veertex
    void _AppendGeometricVertex(const std::string & istrLineToAppend);
    void _AppendTextureVertex(const std::string & istrLineToAppend);
    void _AppendNormalVertex(const std::string & istrLineToAppend);
    
    // Break line in vertex corrdinates
    std::vector<float> _AppendVertexInVector(const std::string & istrLineToBreak);
    
    std::vector<std::string> _GetAllVerticesOfFace(const std::string & istrLineToAppend);
    
    // Data Memebers
    std::vector<vertex> _Vertex_Geometry;
    std::vector<vertex> _Vertex_Texture;
    std::vector<vertex> _Vertex_Normal;
    std::vector<face> _Face;
protected:

};
#endif /* Document_OBJ_hpp */
