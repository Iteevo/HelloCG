//
//  RenderCommonDefine.h
//  HelloTriangle
//
//  Created by linhe on 3/6/18.
//  Copyright © 2018 Iteevo. All rights reserved.
//

#ifndef RenderCommonDefine_h
#define RenderCommonDefine_h

struct Vertex
{
    float Position[2];
    float Color[4];
};

const Vertex Vertices[] = {
    {{-0.5, -0.866}, {1, 1, 0.5f, 1}},
    {{0.5, -0.866},  {1, 1, 0.5f, 1}},
    {{0, 1},         {1, 1, 0.5f, 1}},
    {{-0.5, -0.866}, {0.5f, 0.5f, 0.5f}},
    {{0.5, -0.866},  {0.5f, 0.5f, 0.5f}},
    {{0, -0.4f},     {0.5f, 0.5f, 0.5f}},
};

//const Vertex Vertices[] = {
//    {{100, 100}, {1, 1, 0.5f, 1}},
//    {{200, 100},  {1, 1, 0.5f, 1}},
//    {{200, 200},         {1, 1, 0.5f, 1}},
//    {{200, 200}, {0.5f, 0.5f, 0.5f}},
//    {{100, 200},  {0.5f, 0.5f, 0.5f}},
//    {{100, 100},     {0.5f, 0.5f, 0.5f}},
//};

#define STRINGIFY(A) #A

#endif /* RenderCommonDefine_h */
