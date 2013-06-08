//
//  AppDelegate.m
//  GoBang_IOS
//
//  Created by su xinde on 13-1-22.
//  Copyright (c) 2013年 su xinde. All rights reserved.
//

#import "AppDelegate.h"
#import "GoBangViewController.h"

@implementation AppDelegate
@synthesize window = _window;

- (void)dealloc
{
    [_window release];
    [super dealloc];
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    self.window = [[[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]] autorelease];
    // Override point for customization after application launch.
    self.window.backgroundColor = [UIColor whiteColor];
    GoBangViewController *controller = [[GoBangViewController alloc] init];
    self.window.rootViewController = controller;
    [controller release];
    
    [self.window makeKeyAndVisible];
    return YES;
}
//endIgnoringInteractionEvents

@end
