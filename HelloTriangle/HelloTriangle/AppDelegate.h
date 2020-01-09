//
//  AppDelegate.h
//  HelloTriangle
//
//  Created by dn on 22/5/18.
//  Copyright © 2018 Iteevo. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "GLView.h"

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property(strong,nonatomic) GLView* view;
@property (strong, nonatomic) UIWindow *window;

@end

