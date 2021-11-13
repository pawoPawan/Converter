//
//  TransfornationServices.cpp
//  Converter
//
//  Created by Pawan Kumar on 13/11/21.
//

#include "TransfornationServices.hpp"
#include "converterconstants.h"
#include <iostream>
#include <math.h>

using namespace std;

void TransfornationServices::TransformData(triangle & itriangle,vector<bool> bTransform, std::vector<std::vector<double>> & idTransformationdetails)
{
    if(bTransform.size() <= 3)return;
    // Get Transformation Details
    bool bRoationTransformation = bTransform[0];
    bool bTranslationTransformation = bTransform[1];
    bool bScalingTransformation = bTransform[2];
    
    if(bRoationTransformation)ApplyRoationalTranformationOnTraingle(itriangle, idTransformationdetails[0]);
    if(bTranslationTransformation)ApplyTranslationalTranformationOnTraingle(itriangle, idTransformationdetails[1]);
    if(bScalingTransformation)ApplyScalingTranformationOnTraingle(itriangle, idTransformationdetails[2]);
}

void TransfornationServices::ApplyRoationalTranformationOnTraingle(triangle & itriangle, vector<double> & iRotationAngle)
{
    // Rotate along X - Axis
    RotateTriangleAlongXAxis(itriangle, iRotationAngle[0]);
    
    // Rotate along Y - Axis
    RotateTriangleAlongYAxis(itriangle, iRotationAngle[1]);

    // Rotate along Z - Axis
    RotateTriangleAlongZAxis(itriangle, iRotationAngle[2]);
}

void TransfornationServices::RotateTriangleAlongXAxis(triangle & itriangle, double dXRotationAngle)
{
    // For X axis Rotation..
    // Xnew = Xold;
    // Ynew = Yold * Cos(theta) - Zold * Sin(theta)
    // Znew = Yold * Sin(theta) + Zold * Cos(theta)
    dXRotationAngle = dXRotationAngle * 3.14159 /180; // convert to radian
    itriangle.v1.m_y = itriangle.v1.m_y * cos(dXRotationAngle) - itriangle.v1.m_z * sin(dXRotationAngle);
    itriangle.v1.m_z = itriangle.v1.m_y * sin(dXRotationAngle) + itriangle.v1.m_z * cos(dXRotationAngle);
}

void TransfornationServices::RotateTriangleAlongYAxis(triangle & itriangle, double dYRotationAngle)
{
    // For Y axis Rotation..
    // Xnew = Zold * Sin(theta) + Xold * Cos(theta);
    // Ynew = Yold
    // Znew = Yold * Cos(theta) - Xold * Sin(theta)
    dYRotationAngle = dYRotationAngle * 3.14159 /180; // convert to radian
    itriangle.v1.m_x = itriangle.v1.m_z * sin(dYRotationAngle) + itriangle.v1.m_x * cos(dYRotationAngle);
    itriangle.v1.m_z = itriangle.v1.m_y * cos(dYRotationAngle) - itriangle.v1.m_x * sin(dYRotationAngle);
}

void TransfornationServices::RotateTriangleAlongZAxis(triangle & itriangle, double dZRotationAngle)
{
    // For Z axis Rotation..
    // Xnew = Xold * Cos(theta) - Yold * Sin(theta);
    // Ynew = Xold * Sin(theta) + Yold * Cos(theta)
    // Znew = Zold
    dZRotationAngle = dZRotationAngle * 3.14159 /180; // convert to radian
    itriangle.v1.m_x = itriangle.v1.m_x * cos(dZRotationAngle) - itriangle.v1.m_y * sin(dZRotationAngle);
    itriangle.v1.m_y = itriangle.v1.m_x * sin(dZRotationAngle) + itriangle.v1.m_y * cos(dZRotationAngle);
}


void TransfornationServices::ApplyTranslationalTranformationOnTraingle(triangle & itriangle, vector<double> & iTranslationalInfos)
{
    // Apply Transformation on vertex V1, v2 ad v3 of triangle
    // Translate each vertex
    itriangle.v1.m_x = itriangle.v1.m_x + iTranslationalInfos[0];
    itriangle.v1.m_y = itriangle.v1.m_y + iTranslationalInfos[1];
    itriangle.v1.m_z = itriangle.v1.m_z + iTranslationalInfos[2];
    
    itriangle.v2.m_x = itriangle.v2.m_x + iTranslationalInfos[0];
    itriangle.v2.m_y = itriangle.v2.m_y + iTranslationalInfos[1];
    itriangle.v2.m_z = itriangle.v2.m_z + iTranslationalInfos[2];
    
    itriangle.v3.m_x = itriangle.v3.m_x + iTranslationalInfos[0];
    itriangle.v3.m_y = itriangle.v3.m_y + iTranslationalInfos[1];
    itriangle.v3.m_z = itriangle.v3.m_z + iTranslationalInfos[2];
}

void TransfornationServices::ApplyScalingTranformationOnTraingle(triangle & itriangle, vector<double> & iScalingfactor)
{
    // Apply Transformation on vertex V1, v2 ad v3 of triangle
    // Scale each vertex
    itriangle.v1.m_x = itriangle.v1.m_x * iScalingfactor[0];
    itriangle.v1.m_y = itriangle.v1.m_y * iScalingfactor[1];
    itriangle.v1.m_z = itriangle.v1.m_z * iScalingfactor[2];
    
    itriangle.v2.m_x = itriangle.v2.m_x * iScalingfactor[0];
    itriangle.v2.m_y = itriangle.v2.m_y * iScalingfactor[1];
    itriangle.v2.m_z = itriangle.v2.m_z * iScalingfactor[2];
    
    itriangle.v3.m_x = itriangle.v3.m_x * iScalingfactor[0];
    itriangle.v3.m_y = itriangle.v3.m_y * iScalingfactor[1];
    itriangle.v3.m_z = itriangle.v3.m_z * iScalingfactor[2];
}


void TransfornationServices::GetTransformationDetails(vector<bool> & bTransformation, std::vector<std::vector<double>> & idTransformationdetails)
{
    vector<double> dRotationalTransfromation{};
    vector<double> dTranslationalTransformation{};
    vector<double> dScalingTransformation{};
    vector<bool> bTransform{};
    
    // Get the factors which needs to be required for transformation
    int nTrans = 0;
    cout << "Enter 1 for Rotational Transformation, 0 to continue: ";
    cin >> nTrans;
    if(nTrans)GetRotationalTransformationDetails(dRotationalTransfromation);
    bTransformation.push_back(nTrans);
    idTransformationdetails.push_back(dRotationalTransfromation);
    
    nTrans = 0;
    cout << "Enter 1 for Translational Transformation, 0 to continue: ";
    cin >> nTrans;
    if(nTrans)GetTranslationalTransformationDetails(dTranslationalTransformation);
    bTransformation.push_back(nTrans);
    idTransformationdetails.push_back(dTranslationalTransformation);
    
    nTrans = 0;
    cout << "Enter 1 for Scalable Transformation, 0 to continue: ";
    cin >> nTrans;
    if(nTrans)GetScalingTransformationDetails(dScalingTransformation);
    bTransformation.push_back(nTrans);
    idTransformationdetails.push_back(dScalingTransformation);
}

void TransfornationServices::GetRotationalTransformationDetails(vector<double> & dRotationalTransformation)
{
    // For X axis Rotation..
    // Xnew = Xold;
    // Ynew = Yold * Cos(theta) - Zold * Sin(theta)
    // Znew = Yold * Sin(theta) + Zold * Cos(theta)
    double dRotAngle = 0.0;
    cout << "Enter Rotation angle along X Axis in degree: ";
    cin >> dRotAngle;
    dRotationalTransformation.push_back(dRotAngle);
    
    // For Y axis Rotation..
    // Xnew = Zold * Sin(theta) + Xold * Cos(theta);
    // Ynew = Yold
    // Znew = Yold * Cos(theta) - Xold * Sin(theta)
    dRotAngle = 0.0;
    cout << "Enter Rotation angle along Y Axis in degree: ";
    cin >> dRotAngle;
    dRotationalTransformation.push_back(dRotAngle);
    
    // For Z axis Rotation..
    // Xnew = Xold * Cos(theta) - Yold * Sin(theta);
    // Ynew = Xold * Sin(theta) + Yold * Cos(theta)
    // Znew = Zold
    dRotAngle = 0.0;
    cout << "Enter Rotation angle along Z Axis in degree: ";
    cin >> dRotAngle;
    dRotationalTransformation.push_back(dRotAngle);

}

void TransfornationServices::GetTranslationalTransformationDetails(vector<double> & dTranslationalTransformation)
{
    // Xnew = Xold + Tx
    double dTranslMag = 0.0;
    cout << "Enter Translation in X direction: ";
    cin >> dTranslMag;
    dTranslationalTransformation.push_back(dTranslMag);
    
    // Ynew = Yold + Ty
    dTranslMag = 0.0;
    cout << "Enter Translation in Y direction: ";
    cin >> dTranslMag;
    dTranslationalTransformation.push_back(dTranslMag);
    
    // Znew = Zold + Tz
    dTranslMag = 0.0;
    cout << "Enter Translation in Z direction: ";
    cin >> dTranslMag;
    dTranslationalTransformation.push_back(dTranslMag);
}

void TransfornationServices::GetScalingTransformationDetails(vector<double> & dScalingTransformation)
{
    // Xnew = Xold * Sx;
    double dTranslMag = 0.0;
    cout << "Enter Scaling in X direction: ";
    cin >> dTranslMag;
    dScalingTransformation.push_back(dTranslMag);
    
    // Ynew = Yold * Sy;
    dTranslMag = 0.0;
    cout << "Enter Scaling in Y direction: ";
    cin >> dTranslMag;
    dScalingTransformation.push_back(dTranslMag);
    
    // Znew = Zold * Sz;
    dTranslMag = 0.0;
    cout << "Enter Scaling in Z direction: ";
    cin >> dTranslMag;
    dScalingTransformation.push_back(dTranslMag);
}
