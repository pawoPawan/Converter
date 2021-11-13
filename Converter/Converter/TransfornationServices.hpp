//
//  TransfornationServices.hpp
//  Converter
//
//  Created by Pawan Kumar on 13/11/21.
//

#ifndef TransfornationServices_hpp
#define TransfornationServices_hpp

#include <stdio.h>
#include <stdio.h>
#include <string>
#include "converterconstants.h"

class TransfornationServices
{
public:
    static void TransformData(triangle & itriangle, std::vector<bool> bTransform, std::vector<std::vector<double>> & idTransformationdetails);
    
    
    // Fetch Transformational details
    static void GetTransformationDetails(std::vector<bool> & bTransformation, std::vector<std::vector<double>> & idTransformationdetails);
    static void GetRotationalTransformationDetails(std::vector<double> & dRotationalTransformation);
    static void GetTranslationalTransformationDetails(std::vector<double> & dTranslationalTransformation);
    static void GetScalingTransformationDetails(std::vector<double> & dScalingTransformation);
    
    
    // Transformation
    static void ApplyRoationalTranformationOnTraingle(triangle & itriangle, std::vector<double> & iRotationAngle);
    static void ApplyTranslationalTranformationOnTraingle(triangle & itriangle, std::vector<double> & iTranslationalInfos);
    static void ApplyScalingTranformationOnTraingle(triangle & itriangle, std::vector<double> & iScalingfactor);
    
    // Rotation along X, Y and Z
    static void RotateTriangleAlongXAxis(triangle & itriangle, double dXRotationAngle);
    static void RotateTriangleAlongYAxis(triangle & itriangle, double dYRotationAngle);
    static void RotateTriangleAlongZAxis(triangle & itriangle, double dZRotationAngle);
};
#endif /* TransfornationServices_hpp */
