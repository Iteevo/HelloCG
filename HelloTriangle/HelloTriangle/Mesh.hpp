//
//  Mesh.hpp
//  HelloTriangle
//
//  Created by dn on 9/9/19.
//  Copyright © 2019 Iteevo. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <vector>
#include <stdio.h>
using namespace std;


struct rUV
{
    float x;
    float y;
};

struct rVertex
{
    float x;
    float y;
    float z;
    rVertex(float x,float y,float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    };
    rVertex()
    {
        x = 0;  y = 0;  z = 0;
    };
};

struct rLine
{
    rVertex startPos;
    rVertex endPos;
    
    rLine(rVertex start,rVertex end)
    {
        startPos = start;
        endPos = end;
    }
};

class Mesh
{
public:
    Mesh(vector<rVertex> vrt,vector<rUV>,vector<int32_t> ids);
    Mesh();
    vector<rVertex> GetVertices(){return _vertices;}
    vector<int32_t> GetIndices(){return _indices;}
    
    void AddTriangle(rVertex vertex,vector<rUV> vUV,vector<int32_t> inds);
    
    
private:
    vector<rVertex>     _vertices;
    vector<rUV>         _UV;
    vector<int32_t>     _indices;
};

#endif /* Mesh_hpp */
