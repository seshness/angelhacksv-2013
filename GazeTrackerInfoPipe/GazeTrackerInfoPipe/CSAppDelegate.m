//
//  CSAppDelegate.m
//  GazeTrackerInfoPipe
//
//  Created by Seshadri Mahalingam on 6/15/13.
//  Copyright (c) 2013 The Careless Shrug. All rights reserved.
//

#import "CSAppDelegate.h"
#import "LCGazeFoundation.h"
#import <redis-objc/hiredis.h>

@implementation CSAppDelegate

@synthesize redis=_redis;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    _redis = [APGRedisServer connectTo:@"localhost" onPort:REDIS_DEFAULT_PORT];
    if (_redis.connected) {
        NSLog(@"Connected.");
    } else {
        NSLog(@"Not connected: %@", [_redis lastError]);
    }

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

    NSString* command = @"PUBLISH";
    NSString* key = @"location";
    NSString* value = [NSString stringWithFormat:@"{'x':%f,'y':%f}",point.x,point.y];
    
    NSLog(@"%@", value);
    redisReply* reply = [_redis execute:command withKey:key value:value];
}

@end
