//
//  AppDelegate.h
//  HungryChameleon
//
//  Created by Alexander Kuznietsov on 12/9/13.
//  Copyright (c) 2013 Alexander Kuznietsov. All rights reserved.
//

#import <UIKit/UIKit.h>

@class RootViewController;

@interface AppDelegateIos : UIResponder <UIApplicationDelegate>
{
    UIWindow *window;
    RootViewController* viewController;
}

@end
