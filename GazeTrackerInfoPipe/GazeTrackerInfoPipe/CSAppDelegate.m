//
//  CSAppDelegate.m
//  GazeTrackerInfoPipe
//
//  Created by Seshadri Mahalingam on 6/15/13.
//  Copyright (c) 2013 The Careless Shrug. All rights reserved.
//

#import "CSAppDelegate.h"
#import "LCGazeFoundation.h"

@implementation CSAppDelegate

@synthesize redis=_redis;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    _redis = [ObjCHiredis redis:@"localhost" on:[NSNumber numberWithInt:6379]];
    
    [[NSDistributedNotificationCenter defaultCenter] postNotificationName:kGazeTrackerCalibrationRequestStart
                                                                   object:kGazeSenderID
                                                                 userInfo:nil
                                                       deliverImmediately:YES];

    [[NSDistributedNotificationCenter defaultCenter] addObserver:self
                                                        selector:@selector(gazePointBroadcasted:)
                                                            name:kGazePointNotification
                                                          object:kGazeSenderID];
}

-(void)gazePointBroadcasted:(NSNotification*)note{
    NSDictionary* userInfo = [note userInfo];
    NSPoint point;
    point.x = [(NSNumber*)[userInfo objectForKey:kGazePointXKey] floatValue];
    point.y = [(NSNumber*)[userInfo objectForKey:kGazePointYKey] floatValue];
    
    NSLog(@"%f, %f", point.x, point.y);
    [_redis command:[NSString stringWithFormat:@"PUBLISH location \"%f, %f\"", point.x, point.y]];
}

@end
