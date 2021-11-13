//
//  Document_STL.cpp
//  Converter
//
//  Created by Pawan Kumar on 10/11/21.
//

#include "Document_STL.hpp"
#include "converterconstants.h"
#include <string>
#include <fstream>

using namespace std;

Document_STL::Document_STL():IDocumentAbstract()
{
    
}
Document_STL::Document_STL(const std::string & iDocFile):IDocumentAbstract(iDocFile)
{
    
}

Document_STL::~Document_STL()
{
    
}

void Document_STL::ConvertDocument(std::string & istrToExtension, std::string & ostrOutPutFile)
{
    
}

void Document_STL::AppendTriangles(std::vector<triangle> & iArrayOfTriangles)
{
    _tri_faces = iArrayOfTriangles;
}

void Document_STL::SetFileLocation(std::string istrFileLocation)
{
    _strDoCFileLocation = istrFileLocation;
}
void Document_STL::WriteSTLFile()
{
    // Create a new file and append in order for each triangle
    
    // header infos
    std::string strHeader = "solid STLFile-output";
    char cheader[80] = "solid STLFile-output";
    char attribute[2] = "0";
    unsigned long int nTriangles = _tri_faces.size();
    
    // Open file
    std::ofstream output_STLFile;
    output_STLFile.open(_strDoCFileLocation,  std::ios::out | std::ios::binary);
    // ofstream::write function writes in binary format
    output_STLFile.write(cheader,sizeof(cheader));
    output_STLFile.write(reinterpret_cast<const char *>(&nTriangles),4);
    
    // Run a loop for each traingular face and append the info
    for(unsigned long int idx = 0; idx < nTriangles; idx++)
    {
        // Normal vector
        output_STLFile.write(reinterpret_cast<const char *>(&_tri_faces[idx].vn.m_x), sizeof(_tri_faces[idx].vn.m_x));
        output_STLFile.write(reinterpret_cast<const char *>(&_tri_faces[idx].vn.m_y), sizeof(_tri_faces[idx].vn.m_x));
        output_STLFile.write(reinterpret_cast<const char *>(&_tri_faces[idx].vn.m_z), sizeof(_tri_faces[idx].vn.m_x));

        // Vertex 1
        output_STLFile.write(reinterpret_cast<const char *>(&_tri_faces[idx].v1.m_x), sizeof(_tri_faces[idx].v1.m_x));
        output_STLFile.write(reinterpret_cast<const char *>(&_tri_faces[idx].v1.m_y), sizeof(_tri_faces[idx].v1.m_x));
        output_STLFile.write(reinterpret_cast<const char *>(&_tri_faces[idx].v1.m_z), sizeof(_tri_faces[idx].v1.m_x));
        
        // vertex 2
        output_STLFile.write(reinterpret_cast<const char *>(&_tri_faces[idx].v2.m_x), sizeof(_tri_faces[idx].v2.m_x));
        output_STLFile.write(reinterpret_cast<const char *>(&_tri_faces[idx].v2.m_y), sizeof(_tri_faces[idx].v2.m_x));
        output_STLFile.write(reinterpret_cast<const char *>(&_tri_faces[idx].v2.m_z), sizeof(_tri_faces[idx].v2.m_x));
        
        // vertex 3
        output_STLFile.write(reinterpret_cast<const char *>(&_tri_faces[idx].v3.m_x), sizeof(_tri_faces[idx].v3.m_x));
        output_STLFile.write(reinterpret_cast<const char *>(&_tri_faces[idx].v3.m_y), sizeof(_tri_faces[idx].v3.m_x));
        output_STLFile.write(reinterpret_cast<const char *>(&_tri_faces[idx].v3.m_z), sizeof(_tri_faces[idx].v3.m_x));
        
        
        // Unsigned integer of 2 bytes
        output_STLFile.write(attribute,2);
    }
    output_STLFile.close();
}
