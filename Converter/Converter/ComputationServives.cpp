//
//  ComputationServives.cpp
//  Converter
//
//  Created by Pawan Kumar on 13/11/21.
//

#include "ComputationServives.hpp"

#include "converterconstants.h"
#include <math.h>

double ComputationServives::AreaOfTraingle(triangle & itriangle)
{
    double area = 0.0;
    
    // Get Vectors from Traingle coordinates
    vertex a, b, c;
    GetVectorsFromTriangleCordinates(itriangle, a, b);
    GetNormalFormCrossProduct(a,b,c);
    
    area = 0.5 * sqrt(c.m_x * c.m_x + c.m_y * c.m_y + c.m_z * c.m_z);
    return area;
}

void ComputationServives::ComputeUnitNormal(triangle & itriangle)
{
    ComputeNormalFromTriangle(itriangle,itriangle.vn);
    ComputeUnitNormalFromNormal(itriangle.vn);
}

void ComputationServives::CheckIfpointInsideModel(std::vector<triangle> & iArrayOfTriangles, bool & obInsideModel, vertex iGivenPoint)
{
    obInsideModel = true;
    double dOriVoulme = 0.0, dVolWithGivenPoint = 0.0;
    ComputeVolume(iArrayOfTriangles, dOriVoulme);
    ComputeVolume(iArrayOfTriangles, dOriVoulme, true, iGivenPoint);
    if ((dVolWithGivenPoint - dOriVoulme) > float(1.0e-9)) obInsideModel = false;
}

void ComputationServives::ComputeVolume(std::vector<triangle> & iArrayOfTriangles, double & odVolume,bool bCheckWithExternalPoint /*= false*/, vertex ivertexToCheck)
{
    // select a point from model
    // create prism for each triangle
    // sum up area of each prism
    // volume = (1/3)area of base traingle * height
    // to calculate height -- find plane of triangle
    // find the distance of point selected from plane
    vertex fiexedPoint = iArrayOfTriangles[0].v1;
    if(bCheckWithExternalPoint)fiexedPoint = ivertexToCheck;
    unsigned long int nTri = iArrayOfTriangles.size();
    double dVol = 0.0;
    for(unsigned long int idx = 0; idx < nTri; idx++)
    {
        double area = 0.0, dPlaneConst = 0.0, dSqRoot = 0.0, dMag = 0.0, dPerpenDist = 0.0;
        vertex a, b, c;
        GetVectorsFromTriangleCordinates(iArrayOfTriangles[idx], a, b);
        GetNormalFormCrossProduct(a,b,c);// Cross product will give direction ratio
        
        dSqRoot = sqrt(c.m_x * c.m_x + c.m_y * c.m_y + c.m_z * c.m_z);
        
        area = 0.5 * dSqRoot;
        
        dPlaneConst = (- c.m_x * iArrayOfTriangles[idx].v1.m_x - c.m_y * iArrayOfTriangles[idx].v1.m_y - c.m_z * iArrayOfTriangles[idx].v1.m_z);
        
        // Equation of plane will be
        // A X + BY + CZ + D = 0; A = c.m_x, B = c.m_y, C = c.m_z, D = dPlaneConst;
        
        // Fit absolute value in equation
        dMag = fabs((c.m_x * fiexedPoint.m_x + c.m_y * fiexedPoint.m_y + c.m_z * fiexedPoint.m_z + dPlaneConst));
        
        dPerpenDist = dMag / dSqRoot;
        
        dVol = dVol + (area * dPerpenDist)/3;
    }
    odVolume = dVol;
}

double ComputationServives::HeightOfTriangualrPrism(triangle & iTriangle)
{
    double dHeight = 0.0;
    // Compute the plane of traingle.
    // find the distance of point from plance.
    return dHeight;
}

void ComputationServives::ComputeNormalFromTriangle(triangle & iTriangle, vertex & oNormal)
{
    vertex u, v;
    GetVectorsFromTriangleCordinates(iTriangle,u,v);
    // Cross product will give direction ratio
    // Normal Vector
    GetNormalFormCrossProduct(u,v,oNormal);
}

void ComputationServives::ComputeUnitNormalFromNormal(vertex & oUnitNormal)
{
    float vmod = pow(oUnitNormal.m_x,2) + pow(oUnitNormal.m_y,2) + pow(oUnitNormal.m_z,2);
    vmod = sqrt(vmod);
    if (vmod > (float)1.0e-9)
    {
        oUnitNormal.m_x /= vmod;
        oUnitNormal.m_y /= vmod;
        oUnitNormal.m_z /= vmod;
    }
}

void ComputationServives::GetVectorsFromTriangleCordinates(triangle & iTriangle, vertex & u, vertex & v)
{
    u.m_x = iTriangle.v2.m_x - iTriangle.v1.m_x;
    u.m_y = iTriangle.v2.m_y - iTriangle.v1.m_y;
    u.m_z = iTriangle.v2.m_z - iTriangle.v1.m_z;
    
    v.m_x = iTriangle.v3.m_x - iTriangle.v1.m_x;
    v.m_y = iTriangle.v3.m_y - iTriangle.v1.m_y;
    v.m_z = iTriangle.v3.m_z - iTriangle.v1.m_z;
}

void ComputationServives::GetNormalFormCrossProduct(vertex & u, vertex & v, vertex & oNormal)
{
    oNormal.m_x = u.m_y * v.m_z - u.m_z * v.m_y;
    oNormal.m_y = u.m_z * v.m_x - u.m_x * v.m_z;
    oNormal.m_z = u.m_x * v.m_y - u.m_y * v.m_x;
}
