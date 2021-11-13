//
//  converterservices.cpp
//  Converter
//
//  Created by Pawan Kumar on 05/11/21.
//
#include <iostream>
#include <math.h>
#include "converterservices.hpp"
#include "IDocumentAbstract.hpp"
#include "ICreateFactory.hpp"
#include "converterconstants.h"
#include "Document_STL.hpp"
#include "Document_OBJ.hpp"
#include "TransfornationServices.hpp"
#include "ComputationServives.hpp"


using namespace std;

void converterservices::GetAction(int iAction/*,Action &oAction*/)
{
    cout << "converterservices::GetAction" << endl;
    // if (1 == iAction) oAction = Read_Action;
    // else if (2 == iAction) oAction = Write_Action;
    // else if (3 == iAction) oAction = Convert_Action;
    // else oAction = Undefined_Action;
}

void converterservices::ConvertDocument(IDocument * ipFromDoc, const std::string  istrToFileExtension, const std::string istrOutPutFileName)
{
    if (nullptr == ipFromDoc)return;
    
    // Creaete a file for new doc to write
    ICreateFactory * pIFactory = nullptr;
    IDocument * pToDoc = nullptr;
    pIFactory = ICreateFactory::GetFactory();
    if(pIFactory == nullptr)
    {
        cout << "Factory creation failed" << endl;
        return;
        delete pIFactory;
        pIFactory = nullptr;
        delete pToDoc;
        pToDoc = nullptr;
    }
    
    // Get Document Instance from input file
    pToDoc = pIFactory->GetInstanceFromExtension(istrToFileExtension);
    if(pToDoc == nullptr)
    {
        cout << "Document creation failed" << endl;
        delete pIFactory;
        pIFactory = nullptr;
        delete pToDoc;
        pToDoc = nullptr;
        return;
    }

    // Ask user for transformation
    int nTrans = 0;
    cout << "Want to transform Data(Enter 1 to Transform, 0 if do not want to transform): ";
    cin >> nTrans;
    
    vector<bool> bTransform{};// Order Rotation, Translation, scaling
    vector<vector<double>> dTransformationdetails{};
    if (nTrans) TransfornationServices::GetTransformationDetails(bTransform,dTransformationdetails);
    
    string strCurrFileExt = "";
    ipFromDoc->GetFileExtension(strCurrFileExt);
    if (0 == strCurrFileExt.compare("obj"))
        _ConvertFromOBJFile(ipFromDoc, pToDoc, istrToFileExtension, istrOutPutFileName, bTransform, dTransformationdetails);
    else if (0 == strCurrFileExt.compare("obj"))
    {
        // _ConvertFromSTLFile()
    }
    //IDocumentAbstract * pDocAbs = dynamic_cast<IDocumentAbstract * >(ipDoc);
    //if(nullptr == pDocAbs) return;
    
    // delete all from memory
    delete pIFactory;
    pIFactory = nullptr;
    delete pToDoc;
    pToDoc = nullptr;
}

void converterservices::_ConvertFromOBJFile(IDocument * ipFromObjDoc, IDocument * ipToDoc, const std::string  istrToFileExtension, std::string istrOutPutFileName, vector<bool> bTransform, std::vector<std::vector<double>> & idTransformationdetails)
{
    // Create a new instance of object type istrOutPutFileName
    if (0 == istrToFileExtension.compare("stl"))
    {
        _ConvertFromOBJToSTL(ipFromObjDoc,ipToDoc,istrOutPutFileName,bTransform,idTransformationdetails);
    }
    else if (0 == istrToFileExtension.compare("3ds"))
    {
        
    }
}

void converterservices::_ConvertFromOBJToSTL(IDocument * ipFromObjDoc, IDocument * ipToSTLDoc, std::string istrOutPutFileName, vector<bool> bTransform, std::vector<std::vector<double>> & idTransformationdetails)
{
    if ((nullptr == ipFromObjDoc) || (nullptr == ipToSTLDoc))return;
    
    // variables for OBJ File
    std::vector<face> arrayOfFace;
    std::vector<vertex> arrayOfGeometric_Vertex;
    std::vector<vertex> arrayOfTexture_Vertex;
    std::vector<vertex> arrayOfNormal_Vertex;
    
    // Variables for STL File
    std::vector<triangle> triangle_Faces;
    
    Document_OBJ * pOBJFile = dynamic_cast<Document_OBJ *>(ipFromObjDoc);
    Document_STL * pSTLFile = dynamic_cast<Document_STL *>(ipToSTLDoc);
    if ((nullptr == pOBJFile) || (nullptr == pSTLFile))
    {
        delete pOBJFile;
        delete pSTLFile;
        return;
    }
    
    //---------------------
    pSTLFile->SetFileLocation(istrOutPutFileName);
    
    pOBJFile->GetArrayOfFace(arrayOfFace);
    pOBJFile->GetArrayOfGeometryVertex(arrayOfGeometric_Vertex);
    pOBJFile->GetArrayOfTextureVertex(arrayOfTexture_Vertex);
    pOBJFile->GetArrayOfNormalVertex(arrayOfNormal_Vertex);
    
    // From face get trainagles and append in STL DOC
    
    // read each face and apppend triangles
    std::vector<triangle> arrayOfTriangle{};
    unsigned long int nFaces =  arrayOfFace.size();
    const float eps = (float) 1.0e-9;
    
    float fModelSArea = 0.0;
    int nComputeArea = 0;
    cout << "Enter 1 to compute Surface Area of Model other wise 0: ";
    cin >> nComputeArea;
    bool bComputeSA = false;
    if(nComputeArea)bComputeSA = true;
    for(int nFno = 0; nFno < nFaces; nFno++)
    {
        face curr_face = arrayOfFace[nFno];
        unsigned long int nVer_Curr_face = curr_face.face_v.size();
        int nNo_Tri = nVer_Curr_face - 2;
        int fs = 0;
        for(int nTri = 0; nTri < nNo_Tri; nTri++)
        {
            // 1,2,3,4
            // 0,1,2,3
            triangle curr_tri = {};
            curr_tri.v1 = arrayOfGeometric_Vertex[curr_face.face_v[0]-1];
            curr_tri.v2 = arrayOfGeometric_Vertex[curr_face.face_v[fs+1]-1];
            curr_tri.v3 = arrayOfGeometric_Vertex[curr_face.face_v[fs+2]-1];
            // TRANSFORM
            TransfornationServices::TransformData(curr_tri, bTransform, idTransformationdetails);
       
            // calculate unit normal
            ComputationServives::ComputeUnitNormal(curr_tri);
            
            if(bComputeSA)fModelSArea += ComputationServives::AreaOfTraingle(curr_tri);
            // Append each trainagle in array of Trainagle
            arrayOfTriangle.push_back(curr_tri);
            
            fs += 1;
        }
    }
    // Append array of trainagle to STL Doc file
    pSTLFile->AppendTriangles(arrayOfTriangle);
    
    //------------ Write to STL File --------------
    pSTLFile->WriteSTLFile();
    
    if(nComputeArea)cout << "Model Surface Area is: " << fModelSArea << " Units."<< endl;
    
    int nCheckPoint = 0;
    cout << "Enter 1 to check if a point is inside model otherwise 0: ";
    cin >> nCheckPoint;
    
    if(nCheckPoint)
    {
        bool bInsideModel = false;
        vertex dPointToCheck {};
        
        double dPoint = 0.0;
        cout << "Enter X Coordiinate: ";
        cin >> dPoint;
        dPointToCheck.m_x = dPoint;
        
        dPoint = 0.0;
        cout << "Enter Y Coordiinate: ";
        cin >> dPoint;
        dPointToCheck.m_y = dPoint;
        
        dPoint = 0.0;
        cout << "Enter Z Coordiinate: ";
        cin >> dPoint;
        dPointToCheck.m_z = dPoint;
        
        ComputationServives::CheckIfpointInsideModel(arrayOfTriangle, bInsideModel, dPointToCheck);
        if(bInsideModel)cout << "Inside Mode." << endl;
        else cout << "OutSide Model" << endl;
    }
    
    
    nCheckPoint = 0;
    cout << "Enter 1 to compute volume of model otherwise 0: ";
    cin >> nCheckPoint;
    if(nCheckPoint)
    {
        double dvolume = 0.0;
        ComputationServives::ComputeVolume(arrayOfTriangle, dvolume);
        cout << "Volume of model is: " << dvolume << " Units." << endl;
    }
    
    pOBJFile = nullptr;
    pSTLFile = nullptr;
}

