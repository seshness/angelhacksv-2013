//
//  CSAppDelegate.h
//  GazeTrackerInfoPipe
//
//  Created by Seshadri Mahalingam on 6/15/13.
//  Copyright (c) 2013 The Careless Shrug. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <ObjCHiredis/ObjCHiredis.h>

@interface CSAppDelegate : NSObject <NSApplicationDelegate>

@property (assign) IBOutlet NSWindow *window;
@property (nonatomic) ObjCHiredis *redis;

@end
