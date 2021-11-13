//
//  ComputationServives.hpp
//  Converter
//
//  Created by Pawan Kumar on 13/11/21.
//

#ifndef ComputationServives_hpp
#define ComputationServives_hpp

#include <stdio.h>
#include "converterconstants.h"

class ComputationServives
{
public:
    // Area of Triangle
    static double AreaOfTraingle(triangle & triangle);
    
    // Compute Unit Normal
    static void ComputeUnitNormal(triangle & itriangle);
    
    // Check if a point is inside  model or not
    static void CheckIfpointInsideModel(std::vector<triangle> & iArrayOfTriangles, bool & obInsideModel, vertex iGivenPoint);
    
    // compute volume
    static void ComputeVolume(std::vector<triangle> & iArrayOfTriangles, double & odVolume, bool bCheckWithExternalPoint = false, vertex ivertexToCheck = {});
    
    // Height of Prism
    static double HeightOfTriangualrPrism(triangle & iTriangle);
    
    // Compute Normal
    static void ComputeNormalFromTriangle(triangle & iTriangle,vertex & oNormal);
    
    // compute unit normal
    static void ComputeUnitNormalFromNormal(vertex & oUnitNormal);
    
    // Get Two vertex from triangle corrdinated
    static void GetVectorsFromTriangleCordinates(triangle & iTriangle, vertex & u, vertex & v);
    
    // Get Normal from cross product of two vectors
    static void GetNormalFormCrossProduct(vertex & u, vertex & v, vertex & oNormal);
};
#endif /* ComputationServives_hpp */
