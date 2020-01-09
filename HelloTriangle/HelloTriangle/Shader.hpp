//
//  Shader.hpp
//  HelloTriangle
//
//  Created by dn on 6/10/19.
//  Copyright © 2019 Iteevo. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>
#include "Vector.hpp"
#include "tgaimage.h"
#include "Matrix.hpp"

struct IShader
{
    virtual vec4 vertex() = 0;
    virtual bool fragment(vec3 bar) = 0;
};

struct NShader:IShader
{
    //in
    vec4 pos;
    mat4 Model;
    mat4 View;
    mat4 Projection;
    //vec2 UV;
    
    //out
    
    
    virtual vec4 vertex()
    {
        mat4 posMat;
        posMat.x = pos;
        //vec4 vec = (Projection * View * Model * posMat).x;
        vec4 vec = (posMat * Model * View * Projection).x;
        return vec;
    }
    
    virtual  bool fragment(vec3 bar)
    {
        return true;
    }
    
    //NShader(mat4 Model,)
};

#endif /* Shader_hpp */
