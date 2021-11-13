//
//  Document_OBJ.cpp
//  Converter
//
//  Created by Pawan Kumar on 05/11/21.
//

#include "Document_OBJ.hpp"
#include "converterservices.hpp"
#include "converterconstants.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


Document_OBJ::Document_OBJ():IDocumentAbstract()
{
    cout << "Document_OBJ::Constructor" << endl;
    _InitialiseVariables();
}
// Document_OBJ::Constructor
Document_OBJ::Document_OBJ(const std::string & iDocFile):IDocumentAbstract(iDocFile)
{
    cout << "Document_OBJ::Constructor" << endl;
    _InitialiseVariables();
    _ParseOBJFile();
}

// Document_OBJ::Destructor
Document_OBJ::~Document_OBJ()
{
    cout << "Document_OBJ::Destructor" << endl;
}

// Document_OBJ::_InitialiseVariables
void Document_OBJ::_InitialiseVariables()
{
    cout << "Initialise Document_OBJ Variables" << endl;
    
    // Initaialised all variables
    _Vertex_Geometry = {};
    _Vertex_Texture = {};
    _Vertex_Normal = {};
    _Face = {};
}

void Document_OBJ::GetArrayOfFace(std::vector<face> & oArrayOfFace)
{
    oArrayOfFace = _Face;
}

void Document_OBJ::GetArrayOfGeometryVertex(std::vector<vertex> & oArrayOfGeoVertex)
{
    oArrayOfGeoVertex = _Vertex_Geometry;
}

void Document_OBJ::GetArrayOfTextureVertex(std::vector<vertex> & oArrayOfTextureVertex)
{
    oArrayOfTextureVertex = _Vertex_Texture;
}

void Document_OBJ::GetArrayOfNormalVertex(std::vector<vertex> & oArrayOfNormalVertex)
{
    oArrayOfNormalVertex = _Vertex_Normal;
}

//Document_OBJ::ConvertDocument
void Document_OBJ::ConvertDocument(std::string & istrToExtension, std::string & ostrOutPutFile)
{
    cout << "Document_OBJ::ConvertDocument" << endl;
    _GetOutPutFileName(istrToExtension,ostrOutPutFile);
    converterservices::ConvertDocument(this, istrToExtension,ostrOutPutFile);
}


// Document_OBJ::_ParseOBJFile
void Document_OBJ::_ParseOBJFile()
{
    string strFileLocation = "";
    _GetFileLocation(strFileLocation);
    if(strFileLocation.length() <= 0)
    {
        cout << "File not avaialable" << endl;
        return;
    }
    _Read_File();
}

// Document_OBJ::_Read_File
void Document_OBJ::_Read_File()
{
    // Open current file
    fstream read_file;
    read_file.open(_strDoCFileLocation,ios::in);
    string sCurr_Line;
    while(getline(read_file,sCurr_Line))
    {
        if(sCurr_Line.empty())continue;
        if (sCurr_Line[0] == 'v')
            _AppendVertex(sCurr_Line);
        else if (sCurr_Line[0] == 'f')
            _AppendFace(sCurr_Line);
    }
}

// Document_OBJ::_AppendVertex
void Document_OBJ::_AppendVertex(const string & istrLineToAppend)
{
    if(istrLineToAppend[1] == ' ')
        _AppendGeometricVertex(istrLineToAppend);
    else if (istrLineToAppend[1] == 't')
        _AppendTextureVertex(istrLineToAppend);
    else if (istrLineToAppend[1] == 'n')
        _AppendNormalVertex(istrLineToAppend);
}

// Document_OBJ::_AppendGeometricVertex
void Document_OBJ::_AppendGeometricVertex(const string & istrLineToAppend)
{
    // extract vertices from line and fill vertex_Geometry x,y,z value
    vector<float> ver_coord = _AppendVertexInVector(istrLineToAppend);
    
    vertex curr_Geo_Ver;
    curr_Geo_Ver.m_x = ver_coord[0];
    curr_Geo_Ver.m_y = ver_coord[1];
    curr_Geo_Ver.m_z = ver_coord[2];
    
    _Vertex_Geometry.push_back(curr_Geo_Ver);
}

// Document_OBJ::_AppendTextureVertex
void Document_OBJ::_AppendTextureVertex(const string & istrLineToAppend)
{
    // extract vertices from line and fill vector_Texture U, V, W value
    vector<float> ver_coord = _AppendVertexInVector(istrLineToAppend);
    
    vertex curr_Tex_Ver;
    curr_Tex_Ver.m_x = ver_coord[0];
    curr_Tex_Ver.m_y = ver_coord[1];
    curr_Tex_Ver.m_z = ver_coord[2];
    
    _Vertex_Texture.push_back(curr_Tex_Ver);
}

// Document_OBJ::_AppendNormalVertex
void Document_OBJ::_AppendNormalVertex(const string & istrLineToAppend)
{
    // extract vertices from line and fill vector_Normal i, j, k value
    vector<float> ver_coord = _AppendVertexInVector(istrLineToAppend);
    
    vertex curr_Nor_Ver;
    curr_Nor_Ver.m_x = ver_coord[0];
    curr_Nor_Ver.m_y = ver_coord[1];
    curr_Nor_Ver.m_z = ver_coord[2];
    
    _Vertex_Normal.push_back(curr_Nor_Ver);
}

// Document_OBJ::_AppendVertexInVector
vector<float> Document_OBJ::_AppendVertexInVector(const string & istrLineToBreak)
{
    vector<float> ver_coord;
    string curr_word;
    
    int slen = istrLineToBreak.length();
    for(int idx = 3; idx < slen; idx++)
    {
        if (istrLineToBreak[idx] == ' ' && curr_word.length() > 0)
        {
            ver_coord.push_back(stof(curr_word));
            curr_word = "";
        }
        else if (istrLineToBreak[idx] == '\r' && curr_word.length() > 0)
        {
            ver_coord.push_back(stof(curr_word));
            curr_word = "";
        }
        else if (istrLineToBreak[idx] != ' ' || istrLineToBreak[idx] != '\r') curr_word += istrLineToBreak[idx];
    }
    return ver_coord;
}

// Document_OBJ::_AppendFace
void Document_OBJ::_AppendFace(const string & istrLineToAppend)
{
    // extract face and append  vertices numbers
    vector<string> face_vertex = _GetAllVerticesOfFace(istrLineToAppend);
    
    int nSzVer = face_vertex.size();
    face faceToAppend;
    for(int idx = 0; idx < nSzVer; idx++)
    {
        vector<int> face_ver;
        string str_tmp_ver = face_vertex[idx];
        string str_tmp = "";
        int nlen = str_tmp_ver.length();
        for(int i = 0; i < nlen; i++)
        {
            if(str_tmp_ver[i] == '/' || str_tmp_ver[i] == '\0')
            {
                face_ver.push_back(stoi(str_tmp));
                str_tmp = "";
            }
            else str_tmp += str_tmp_ver[i];
        }
        face_ver.push_back(stoi(str_tmp));
        faceToAppend.face_v.push_back(face_ver[0]);
        faceToAppend.face_vt.push_back(face_ver[1]);
        faceToAppend.face_vn.push_back(face_ver[2]);
    }
    _Face.push_back(faceToAppend);
}

std::vector<string> Document_OBJ::_GetAllVerticesOfFace(const std::string & istrLineToAppend)
{
    int slen = istrLineToAppend.length();
    string str_curr = "";
    vector<string> faces_ver;
    for(int idx = 2; idx < slen; idx++)
    {
        if(istrLineToAppend[idx] == ' ' && str_curr.length() > 0)
        {
            faces_ver.push_back(str_curr);
            str_curr = "";
        }
        else if (istrLineToAppend[idx] == '\r' && str_curr.length() > 0)
        {
            faces_ver.push_back(str_curr);
            str_curr = "";
            break;
        }
        else if (istrLineToAppend[idx] != '\r' || istrLineToAppend[idx] != ' ')str_curr += istrLineToAppend[idx];
    }
    return faces_ver;
}

