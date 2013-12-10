//
//  AppDelegate.m
//  HungryChameleon
//
//  Created by Alexander Kuznietsov on 12/9/13.
//  Copyright (c) 2013 Alexander Kuznietsov. All rights reserved.
//

#import "AppDelegateIos.h"
#import <EAGLView.h>
#import "RootViewController.h"
#import "AppDelegate.h"

static AppDelegate s_sharedApplication;

@implementation AppDelegateIos

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    // Override point for customization after application launch.
    EAGLView* __glView = [EAGLView viewWithFrame:[window bounds]
                          pixelFormat: kEAGLColorFormatRGBA8
                          depthFormat:GL_DEPTH_COMPONENT16
                          preserveBackbuffer:NO
                                      sharegroup:Nil
                                   multiSampling:NO
                                 numberOfSamples:0];
    
    viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    viewController.wantsFullScreenLayout = YES;
    viewController.view = __glView;
    
    [window addSubview:viewController.view];
    
    [window makeKeyAndVisible];
    
    [[UIApplication sharedApplication] setStatusBarHidden:YES];
    
    CCApplication::sharedApplication()->run();
    
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

@end
