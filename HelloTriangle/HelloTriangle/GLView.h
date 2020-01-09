//
//  GLView.h
//  HelloTriangle
//
//  Created by dn on 22/5/18.
//  Copyright © 2018 Iteevo. All rights reserved.
//
#import "RenderEngine.hpp"
#import <UIKit/UIKit.h>
#import <OpenGLES/ES3/gl.h>
#import <OpenGLES/ES3/glext.h>
#import <OpenGLES/EAGL.h>



@interface GLView : UIView
{
@private
    EAGLContext* _context;
    RenderEngine* _renderEngine;
    float _timerStamp;
    UIImage *_image;
    UIImageView* _imageview;
}

-(void)drawView;

-(id) initWithFrame:(CGRect)frame;
//+(id)imageFromTGAFile:(NSString *)filename;
//+(id)imageFromTGAData:(NSData *)data;
+(id)imageWithRawRGBAData:(const void *)data width:(int)width height:(int)height;

@end
