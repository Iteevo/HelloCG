//
//  GLView.m
//  HelloTriangle
//
//  Created by dn on 22/5/18.
//  Copyright © 2018 Iteevo. All rights reserved.
//

#import "GLView.h"


@implementation GLView
-(id)initWithFrame:(CGRect)frame
{
    if(self = [super initWithFrame:frame])
    {
//        CAEAGLLayer* layer = (CAEAGLLayer*)super.layer;
//        layer.opaque = YES;
//        _context = [[EAGLContext alloc]initWithAPI:kEAGLRenderingAPIOpenGLES3];
//        if(!_context || ![EAGLContext setCurrentContext:_context])
//        {
//            return nil;
//        }
        //IResourceManager mgr = createres
        _renderEngine = RenderEngine::CreateEngine();
        //[_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:layer];
        _renderEngine->Initialize(CGRectGetWidth(frame),CGRectGetHeight(frame) );
        
        int lenth = 0;
        unsigned char* imagedata = _renderEngine->GetRenderBuffer(&lenth);
        //NSData* data = [NSData dataWithBytes:(const void*)imagedata length:lenth];
        _image = [GLView imageWithRawRGBAData:imagedata width:CGRectGetWidth(frame) height:CGRectGetHeight(frame)];
        //[_image drawAtPoint:CGPointMake(100,100)];
        
        _imageview = [[UIImageView alloc]initWithImage:_image];
        [self addSubview:_imageview];
        
        [self drawView: nil];
        _timerStamp = CACurrentMediaTime();
        //_image = nullptr;
        
        CADisplayLink* displayLink;
        displayLink = [CADisplayLink displayLinkWithTarget:self
                                                  selector:@selector(drawView:)];
        
        [displayLink addToRunLoop:[NSRunLoop currentRunLoop]
                          forMode:NSDefaultRunLoopMode];
    }
    return self;
}

-(void)drawView: (CADisplayLink*) displayLink
{
//    _renderEngine->Render();
//    int lenth = 0;
//    unsigned char* imagedata = _renderEngine->GetRenderBuffer(&lenth);
//    //NSData* data = [NSData dataWithBytes:(const void*)imagedata length:lenth];
//    _image = [GLView imageWithRawRGBAData:imagedata width:CGRectGetWidth(self.frame) height:CGRectGetHeight(self.frame)];
//    int lenth = 0;
//    unsigned char* imagedata = _renderEngine->GetRenderBuffer(&lenth);
//    NSData* data = [NSData dataWithBytes:(const void*)imagedata length:lenth];
//    _image = [UIImage imageWithData:data];
//    [_image drawAtPoint:CGPointMake(100,100)];
    //_renderEngine->Render();
    //[_context presentRenderbuffer:GL_RENDERBUFFER];
    //drawim
}

+(Class)layerClass
{
    return [CAEAGLLayer class];
}

void releaseImageData(void *info, const void *data, size_t size)
{
    //free((void *)data);
}

//+(id)imageFromTGAFile:(NSString *)filename{
//    NSData *data = [[NSData alloc] initWithContentsOfFile:filename];
//    id ret = [self imageFromTGAData:data];
//    [data release];
//    return ret;
//}
//+(id)imageFromTGAData:(NSData *)data{
//    
//    short       imageHeight;
//    short       imageWidth;
//    unsigned    char        bitDepth;
//    unsigned    char        imageType;
//    int         colorMode;
//    long        imageSize;
//    unsigned    char        *imageData;
//    
//    unsigned    char *bytes = (unsigned char *)[data bytes]+2; // skip first two bytes
//    memcpy(&imageType, bytes,  sizeof(unsigned char));
//    
//    if (imageType != 2 && imageType != 3)
//    {
//        NSException *exception = [NSException exceptionWithName:@"Unsupported File Format"
//                                                         reason:@"Compressed TGA files are not supported yet"
//                                                       userInfo:nil];
//        [exception raise];
//    }
//    bytes += ( (sizeof(unsigned char) * 2) + (sizeof(short) * 4));
//    memcpy(&imageWidth, bytes, sizeof(short));
//    bytes += 2;
//    memcpy(&imageHeight, bytes, sizeof(short));
//    bytes += 2;
//    memcpy(&bitDepth, bytes, sizeof(char));
//    bytes+=2;
//    
//    colorMode = bitDepth / 8;
//    imageSize = imageWidth * imageHeight * colorMode;
//    
//    long newDataLength = imageWidth * imageHeight * 4;
//    imageData = (unsigned char *)malloc(newDataLength);
//    memcpy(imageData, bytes, imageSize * sizeof(unsigned char));
//    
//    // Targa is BGR, swap to RGB    long byteCounter = 0;
//    for (long i = 0; i < imageSize; i += colorMode)
//    {
//        long start = (byteCounter++ * 4);
//        imageData[start] = bytes[i+2];
//        imageData[start+1] = bytes[i+1];
//        imageData[start+2] = bytes[i];
//        imageData[start+3] = (colorMode == 4) ? bytes[i+3] : 1.0;
//    }
//    
//    // Targa uses more standard Y axis, so need to swap top & bottom bytes    // We can swap 32 bits at a time rather than going byte by byte    uint32_t *imageDataAsInts = (uint32_t *)imageData;
//    for (int y = 0; y < imageHeight / 2; y++)
//    {
//        for (int x = 0; x < imageWidth; x++)
//        {
//            uint32_t top = imageDataAsInts[y * imageWidth + x];
//            uint32_t bottom = imageDataAsInts[(imageHeight - 1 - y) * imageWidth + x];
//            imageDataAsInts[(imageHeight - 1 - y) * imageWidth + x] = top;
//            imageDataAsInts[y * imageWidth + x] = bottom;
//        }
//    }
//    
//    NSData *swappedData = [[NSData alloc] initWithBytes:imageData length:newDataLength];
//    return [self imageWithRawRGBAData:swappedData width:imageWidth height:imageHeight];
//}
+(id)imageWithRawRGBAData:(const void *)data width:(int)width height:(int)height{
    //const void * buffer = [data bytes];
    int imageSize = width * height * 4;
//    long byteCounter = 0;
//    for (long i = 0; i < imageSize; i += 4)
//    {
//        long start = (byteCounter++ * 4);
//        imageData[start] = bytes[i+2];
//        imageData[start+1] = bytes[i+1];
//        imageData[start+2] = bytes[i];
//        imageData[start+3] = (colorMode == 4) ? bytes[i+3] : 1.0;
//    }
    CGDataProviderRef provider = CGDataProviderCreateWithData(NULL, data, imageSize, releaseImageData);
    
    const int bitsPerComponent = 8;
    const int bitsPerPixel = 4 * bitsPerComponent;
    const int bytesPerRow = 4 * width;
    CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
    CGBitmapInfo bitmapInfo = kCGImageAlphaLast;
    CGColorRenderingIntent renderingIntent = kCGRenderingIntentDefault;
    
    CGImageRef imageRef = CGImageCreate(width, height, bitsPerComponent, bitsPerPixel, bytesPerRow, colorSpaceRef, bitmapInfo, provider, NULL, NO, renderingIntent);
    CGDataProviderRelease(provider);
    
    UIImage *myImage = [UIImage imageWithCGImage:imageRef];
    CGImageRelease(imageRef);
    
    return myImage;
}
/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

@end
