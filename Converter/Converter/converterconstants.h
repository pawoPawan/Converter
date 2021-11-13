//
//  converterconstants.h
//  Converter
//
//  Created by Pawan Kumar on 05/11/21.
//

#ifndef converterconstants_h
#define converterconstants_h


#include <vector>

struct vertex
{
    float m_x;
    float m_y;
    float m_z;
};

struct triangle
{
    vertex vn;
    vertex v1;
    vertex v2;
    vertex v3;
};

struct face
{
    std::vector<int> face_v;
    std::vector<int> face_vt;
    std::vector<int> face_vn;
};

#endif /* converterconstants_h */
