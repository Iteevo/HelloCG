//
//  RenderEngine.hpp
//  HelloTriangle
//
//  Created by dn on 22/5/18.
//  Copyright © 2018 Iteevo. All rights reserved.
//
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>
#include "tgaimage.h"
#include "Mesh.hpp"
#include "geometry.h"
#include "model.h"
#include "Interfaces.hpp"


#ifndef RenderEngine_hpp
#define RenderEngine_hpp

enum  Orientation
{
    UnKown,
    Portait,
    PortraitUpsideDown,
    LandscapeLeft,
    LandscapeRight,
    FaceUp,
    FaceDown
};

class RenderEngine
{
public:
    RenderEngine();
    void Initialize(int width,int height);
    void Render();
    void UpdateAnimation(float delta);
    void OnRotate(Orientation rotate);
    void ApplyOrtho(float maxX, float maxY) const;
    void ApplyRotation(float degrees) const;
    unsigned char * GetRenderBuffer(int* dataLength);
    void DrawLine(int x1,int y1,int x2,int y2,TGAColor color);
    void ScanLine();
    int GetBufferLength();
    GLuint BuildShader(const char* source,GLenum shaderType);
    GLuint BuildProgram(const char* vertSource,const char* fragSource);
    Vec3f Barycentric(Vec2i *pts, Vec2i P);
    void Triangle(vector<rVertex> triangle);
    Vec3f Cross(Vec3f a,Vec3f b);
    //string GetResourcePath() const;
    ~RenderEngine();
    
    static RenderEngine* CreateEngine();
    
    
private:
    bool GetCrossPoint(int height,vector<rVertex>& verts,vector<int32_t> indns);
    void FillTriangle(vector<rVertex>& verts);
    void oldtriangle(Vec2i *pts, TGAImage &image, TGAColor color);
    
private:
    int32_t _height;
    int32_t _width;
    GLuint  _renderbuffer;
    GLuint  _framebuffer;
    
    GLuint _simpleProgram;
    
    TGAImage*   _imageBuffer;
    Mesh*       _mesh;
    float**     _zbuffer;
    Model*      _model;
    
public:
    IResourceManager* Resource;
    
};

#endif /* RenderEngine_hpp */
