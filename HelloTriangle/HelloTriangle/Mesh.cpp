//
//  Mesh.cpp
//  HelloTriangle
//
//  Created by dn on 9/9/19.
//  Copyright © 2019 Iteevo. All rights reserved.
//

#include "Mesh.hpp"

Mesh::Mesh()
{
    rVertex vert1(-0.5f,-0.5f,0.5f);
    rVertex vert2(0.0f,0.5f,0.5f);
    rVertex vert3(0,0,0);
    rVertex vert4(0.5f,-0.5f,0.5f);
    
    _vertices.push_back(vert1);
    _vertices.push_back(vert2);
    _vertices.push_back(vert3);
    _vertices.push_back(vert4);
    
    _indices.push_back(0);
    _indices.push_back(1);
    _indices.push_back(2);
    _indices.push_back(1);
    _indices.push_back(3);
    _indices.push_back(2);
}

Mesh::Mesh(vector<rVertex> vrt,vector<rUV>,vector<int32_t> ids)
{
    
}

void Mesh::AddTriangle(rVertex vertex, vector<rUV> vUV, vector<int32_t> inds)
{
    _vertices.push_back(vertex);
    _UV.insert(_UV.end(), vUV.begin(), vUV.end());
    _indices.insert(_indices.end(), inds.begin(),inds.end());
}
