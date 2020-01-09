//
//  RenderEngine.cpp
//  HelloTriangle
//
//  Created by dn on 22/5/18.
//  Copyright © 2018 Iteevo. All rights reserved.
//


#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "RenderEngine.hpp"
#include "RenderCommonDefine.h"
#include "Shader.hpp"
#include "Camera.hpp"

using namespace std;
//#include "Shaders/Simple.frag"
//#include "Shaders/Simple.vert"


RenderEngine::RenderEngine()
{
//    glGenRenderbuffers(1, &_renderbuffer);
//    glBindRenderbuffer(GL_RENDERBUFFER, _renderbuffer);
}

void RenderEngine::DrawLine(int x1, int y1, int x2, int y2, TGAColor color)
{
    if(x1 == x2)
    {
        for(int i = y1;i < y2;i ++)
        {
            _imageBuffer->set(x1, i, color);
        }
    }
    else
    {
        if(abs(x2 - x1) >= abs(y2 - y1))
        {
            int delta = 0;
            int y = y1;
            for (int i = x1; i <= x2; i++) {
                
                delta += abs(y2 - y1) * 2;
                if(delta >= abs(x2 - x1))
                {
                    y = y + (x2 - x1)/abs(x2 - x1);
                    delta -= 2 * abs(x2 - x1);
                }
                _imageBuffer->set(i, y, color);
            }
        }
        
    }
}

void RenderEngine::ScanLine()
{
    vector<rVertex> verts = _mesh->GetVertices();
    vector<int32_t> indns = _mesh->GetIndices();
    vector<rVertex> triangle;
    for (int i = 0; i < 3; i++) {
        triangle.push_back(verts[indns[i]]);
    }
    Triangle(triangle);
    triangle.clear();
    for (int i = 3; i < 6; i++) {
        triangle.push_back(verts[indns[i]]);
    }
    Triangle(triangle);
    
    triangle.clear();
    for (int i=0; i<_model->nfaces(); i++) {
        std::vector<int> face = _model->face(i);
        Vec2i screen_coords[3];
        for (int j=0; j<3; j++) {
            Vec3f world_coords = _model->vert(face[j]);
            screen_coords[j] = Vec2i((world_coords.x+1.)*_width/2., (world_coords.y+1.)*_height/2);
        }
        oldtriangle(screen_coords, *_imageBuffer, TGAColor(rand()%255, rand()%255, rand()%255, 255));
    }
}



void RenderEngine::Initialize(int width,int height)
{
    _width = width;
    _height = height;
    Resource = CreateResourceManager();
    cout<<width << "\t" << height<< endl;
    _imageBuffer = new TGAImage(width,height,4);
    _zbuffer = new float*[width];
    for (int i = 0; i<width; i++) {
        _zbuffer[i] = new float[height];
    }
    _model = new Model((Resource->GetResourcePath() + "/obj/african_head.obj").c_str());
//    for (int i = 0; i < 110; i++) {
//        for (int j = 0; j < 110; j++) {
//            _imageBuffer->set(i, j, TGAColor(0,0,255,255));
//        }
//    }
    //_mesh = new Mesh();
    Render();
    //glGenFramebuffers(1, &_framebuffer);
//    glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
//    glFramebufferRenderbuffer(GL_FRAMEBUFFER,
//                              GL_COLOR_ATTACHMENT0,
//                              GL_RENDERBUFFER,
//                              _renderbuffer);
//    glViewport(0, 0, width, height);
//    _simpleProgram = BuildProgram(SimpleVertexShader, SimpleFragmentShader);
//    glUseProgram(_simpleProgram);
//    ApplyOrtho(2, 3);
    //auto matrix = glgetuniformma
}
void RenderEngine::Render()
{
    NShader shader;
    Camera camera;
    
    float model[16] = {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,3,1
    };
    shader.Model = mat4(model);
    shader.View = camera.GetViewMatrix();
    shader.Projection = camera.GetProjection(45.0f, (float)_width/_height, 1.0f, 100.0f);
    
    
    for (int i=0; i<_model->nfaces(); i++) {
        std::vector<int> face = _model->face(i);
        Vec2i screen_coords[3];
        for (int j=0; j<3; j++) {
            Vec3f localPos = _model->vert(face[j]);
            shader.pos = vec4(localPos.x,localPos.y,localPos.z,1);
            vec4 screenPos = shader.vertex();
            screenPos = vec4(screenPos.x /screenPos.w,screenPos.y/screenPos.w,screenPos.z/screenPos.w,1);
            if(abs(screenPos.x)  > 1 || abs(screenPos.y) > 1)
                break;
            //cout<< "X:" << screenPos.x << "  Y:"<<screenPos.y<<" Z:" << screenPos.z << " W:"<< screenPos.w<<endl;
            screen_coords[j] = Vec2i((screenPos.x + 1) * 0.5f * _width, (screenPos.y + 1)*0.5f*_height);
        }
        oldtriangle(screen_coords, *_imageBuffer, TGAColor(0, 0, 255, 255));
    }
}
//void RenderEngine::Render()
//{
    //DrawLine(110,110,290,200,TGAColor(0,0,255,255));
 //   ScanLine();
    
//    glClearColor(0.5, 0.5, 0.5, 0.5);
//    glClear(GL_COLOR_BUFFER_BIT);
//    ApplyRotation(0);
//    GLuint positionSlot = glGetAttribLocation(_simpleProgram, "Position");
//    GLuint colorSlot = glGetAttribLocation(_simpleProgram, "SourceColor");
//    glEnableVertexAttribArray(positionSlot);
//    glVertexAttribPointer(positionSlot, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), Vertices[0].Position);
//    glEnableVertexAttribArray(colorSlot);
//    glVertexAttribPointer(colorSlot, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), Vertices[0].Color);
//    GLsizei vcount = sizeof(Vertices)/sizeof(Vertex);
//    glDrawArrays(GL_TRIANGLES, 0, vcount);
//    glDisableVertexAttribArray(positionSlot);
//    glDisableVertexAttribArray(colorSlot);
    
    //glDrawArraysInstanced(GL_TRIANGLES, 0, 3, 3)(<#GLenum mode#>, <#GLsizei count#>, <#GLenum type#>, <#const GLvoid *indices#>, <#GLsizei instancecount#>)
    

    
    
//    GLuint positionSlot = glGetAttribLocation(_simpleProgram, "Position");
//    GLuint colorSlot = glGetAttribLocation(_simpleProgram, "SourceColor");
//
//    glEnableVertexAttribArray(positionSlot);
//    glEnableVertexAttribArray(colorSlot);
//
//    GLsizei stride = sizeof(Vertex);
//    const GLvoid* pCoords = &Vertices[0].Position[0];
//    const GLvoid* pColors = &Vertices[0].Color[0];
//
//    glVertexAttribPointer(positionSlot, 2, GL_FLOAT, GL_FALSE, stride, pCoords);
//    glVertexAttribPointer(colorSlot, 4, GL_FLOAT, GL_FALSE, stride, pColors);
//
//    GLsizei vertexCount = sizeof(Vertices) / sizeof(Vertex);
//    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
//
//    glDisableVertexAttribArray(positionSlot);
//    glDisableVertexAttribArray(colorSlot);
//}


void RenderEngine::UpdateAnimation(float delta)
{
    
}

void RenderEngine::OnRotate(Orientation rotate)
{
    
}


unsigned char * RenderEngine::GetRenderBuffer(int* dataLength)
{
    _imageBuffer->flip_vertically();
    return _imageBuffer->GetTotalBuffer(dataLength);
}


void RenderEngine::ApplyOrtho(float maxX, float maxY) const
{
    float a = 1.0f / maxX;
    float b = 1.0f / maxY;
    float ortho[16] = {
        a, 0,  0, 0,
        0, b,  0, 0,
        0, 0, -1, 0,
        0, 0,  0, 1
    };
    
    GLint projectionUniform = glGetUniformLocation(_simpleProgram, "Projection");
    glUniformMatrix4fv(projectionUniform, 1, 0, &ortho[0]);
}

void RenderEngine::ApplyRotation(float degrees) const
{
    float radians = degrees * 3.14159f / 180.0f;
    float s = sinf(radians);
    float c = cosf(radians);
    float zRotation[16] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    
    GLint _modelviewUniform = glGetUniformLocation(_simpleProgram, "_modelview");
    glUniformMatrix4fv(_modelviewUniform, 1, 0, &zRotation[0]);
}

GLuint RenderEngine::BuildShader(const char* source,GLenum shaderType)
{
    GLuint shaderHandle = glCreateShader(shaderType);
    glShaderSource(shaderHandle, 1, &source, 0);
    glCompileShader(shaderHandle);
    GLint success;
    glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &success);
    if(success == GL_FALSE)
    {
        std::cout<<"shader compile failed!";
        exit(0);
    }
    return shaderHandle;
}

GLuint RenderEngine::BuildProgram(const char* vertSource,const char* fragSource)
{
    GLuint vertShader = BuildShader(vertSource, GL_VERTEX_SHADER);
    GLuint fragShader = BuildShader(fragSource, GL_FRAGMENT_SHADER);
    GLuint programHandle = glCreateProgram();
    glAttachShader(programHandle, vertShader);
    glAttachShader(programHandle, fragShader);
    glLinkProgram(programHandle);
    return programHandle;
}

RenderEngine* RenderEngine::CreateEngine()
{
    return new RenderEngine;
}

RenderEngine::~RenderEngine()
{
    for (int i = 0; i < _width; i ++) {
        delete [] _zbuffer[i];
    }
    delete [] _zbuffer;
    
    if (_mesh != nullptr) {
        delete _mesh;
    }
}

void RenderEngine::FillTriangle(vector<rVertex>& verts)
{
    int minY = min(min(verts[0].y, verts[1].y),verts[2].y) * _height;
    int maxY = max(max(verts[0].y, verts[1].y), verts[2].y) * _height;
    float x1 = -1;
    float x2 = -1;
    
    for (int i = minY; i < maxY; i++) {
        float y = i * 1.0f / _height;
        float innerMinY = min(verts[0].y,verts[1].y);
        float innerMaxY = max(verts[0].y,verts[1].y);
        
        if(y >= innerMinY && y <= innerMaxY)
        {
            x1 = verts[0].x + (y - innerMinY)/(innerMaxY - innerMinY) * (verts[1].x - verts[0].x);
        }
        
        
        innerMinY = min(verts[1].y,verts[2].y);
        innerMaxY = max(verts[1].y,verts[2].y);
        if(y >= innerMinY && y <= innerMaxY)
        {
            if(x1 > -1 )
            {
                x2 = verts[1].x + (y - innerMinY)/(innerMaxY - innerMinY) * (verts[2].x - verts[1].x);
            }
            else
            {
                x1 = verts[1].x + (y - innerMinY)/(innerMaxY - innerMinY) * (verts[2].x - verts[1].x);
            }
            
        }
        
        innerMinY = min(verts[0].y,verts[2].y);
        innerMaxY = max(verts[0].y,verts[2].y);
        if(y >= innerMinY && y <= innerMaxY)
        {
            if(x1 > -1 )
            {
                x2 = verts[0].x + (y - innerMinY)/(innerMaxY - innerMinY) * (verts[2].x - verts[0].x);
            }
            else
            {
                x1 = verts[0].x + (y - innerMinY)/(innerMaxY - innerMinY) * (verts[2].x - verts[0].x);
            }
            
        }
        
        if(x1 > -1 && x2 > -1)
        {
            for (int innerx = (int)(min(x1,x2) * _width); innerx < (int)(max(x1,x2) * _width); innerx ++) {
                _imageBuffer->set(innerx + _width/2, i + _height/2, TGAColor(0,255,0,255));
            }
        }
    }
}


bool RenderEngine::GetCrossPoint(int height,vector<rVertex>& verts,vector<int32_t> inds)
{
//    vector<rLine> lines;
//    auto iter = inds.begin();
//    while(iter != inds.end())
//    {
//        lines.push_back(rLine(verts[*iter],verts[*(iter + 1)]));
//        lines.push_back(rLine(verts[*iter + 1],verts[*(iter + 2)]));
//        lines.push_back(rLine(verts[*iter + 2],verts[* (iter)]));
//        float minY = _height * min(lines[0]., lines[1].y, lines[2].y);
//        for (int i = 0; i < ; <#increment#>) {
//            <#statements#>
//        }
//        for (int i = 0; i< 3; i++) {
//            iter ++;
//            if(iter == inds.end())
//                break;
//        }
//        lines.clear();
//    }
    
    return false;
}

 Vec3f RenderEngine:: Cross(Vec3f a,Vec3f b)
{
    //abcdef
    float x = a[1] *b[2]-a[2]*b[1];//计算三阶行列式
    float y = a[2] * b[0] - a[0] * b[2];//c*d-a*f;
    float z = a[0] * b[1] - a[1] * b[0];//a*e-b*d;
    return Vec3f(x,y,z);
}

Vec3f RenderEngine:: Barycentric(Vec2i *pts, Vec2i P) {
    Vec3f u = Cross(Vec3f(pts[2][0]-pts[0][0], pts[1][0]-pts[0][0], pts[0][0]-P[0]), Vec3f(pts[2][1]-pts[0][1], pts[1][1]-pts[0][1], pts[0][1]-P[1]));
    /* `pts` and `P` has integer value as coordinates
     so `abs(u[2])` < 1 means `u[2]` is 0, that means
     triangle is degenerate, in this case return something with negative coordinates */
    if (std::abs(u[2])<1) return Vec3f(-1,1,1);
    return Vec3f(1.f-(u.x+u.y)/u.z, u.y/u.z, u.x/u.z);
}

void RenderEngine:: Triangle(vector<rVertex> triangle) {
    Vec2i pts[3];
    pts[0] = Vec2i((triangle[0].x + 0.5f) * _width ,(triangle[0].y + 0.5f) * _height);
    pts[1] = Vec2i((triangle[1].x + 0.5f) * _width, (triangle[1].y + 0.5f) * _height);
    pts[2] = Vec2i((triangle[2].x + 0.5f) * _width, (triangle[2].y + 0.5f) * _height);
    Vec2i bboxmin(_width-1,  _height-1);
    Vec2i bboxmax(0, 0);
    Vec2i clamp(_width-1, _height-1);
    for (int i=0; i<3; i++) {
        for (int j=0; j<2; j++) {
            if (j == 0) {
                bboxmin.x = std::max(0,        std::min(bboxmin[j], pts[i][j]));
                bboxmax.x = std::min(clamp[j], std::max(bboxmax[j], pts[i][j]));
            }
            else
            {
                bboxmin.y = std::max(0,        std::min(bboxmin[j], pts[i][j]));
                bboxmax.y = std::min(clamp[j], std::max(bboxmax[j], pts[i][j]));
            }
            
        }
    }
    Vec3i P;
    for (P.x=bboxmin.x; P.x<=bboxmax.x; P.x++) {
        for (P.y=bboxmin.y; P.y<=bboxmax.y; P.y++) {
            Vec3f bc_screen  = Barycentric(pts, Vec2i(P.x,P.y));
            if (bc_screen.x<0 || bc_screen.y<0 || bc_screen.z<0) continue;
            
            P.z = 0;
            for (int zIndex = 0;zIndex < 3;zIndex ++ ) {
                P.z += pts[zIndex][2];
                if(_zbuffer[P.x][P.y] < P.z)
                {
                    _zbuffer[P.x][P.y] = P.z;
                    _imageBuffer->set(P.x, P.y, TGAColor(255, 0, 0, 255));
                }
            }
        }
    }
}

void RenderEngine:: oldtriangle(Vec2i *pts, TGAImage &image, TGAColor color) {
    Vec2i bboxmin(image.get_width()-1,  image.get_height()-1);
    Vec2i bboxmax(0, 0);
    Vec2i clamp(image.get_width()-1, image.get_height()-1);
    for (int i=0; i<3; i++) {
        for (int j=0; j<2; j++) {
            if (j == 0) {
                bboxmin.x = std::max(0,        std::min(bboxmin[j], pts[i][j]));
                bboxmax.x = std::min(clamp[j], std::max(bboxmax[j], pts[i][j]));
            }
            else
            {
                bboxmin.y = std::max(0,        std::min(bboxmin[j], pts[i][j]));
                bboxmax.y = std::min(clamp[j], std::max(bboxmax[j], pts[i][j]));
            }
        }
    }
    Vec2i P;
    for (P.x=bboxmin.x; P.x<=bboxmax.x; P.x++) {
        for (P.y=bboxmin.y; P.y<=bboxmax.y; P.y++) {
            Vec3f bc_screen  = Barycentric(pts, P);
            if (bc_screen.x<0 || bc_screen.y<0 || bc_screen.z<0) continue;
            image.set(P.x, P.y, color);
            //cout<<"P.x = "<< P.x << "  P.y"<<P.y << endl;
        }
    }
}
