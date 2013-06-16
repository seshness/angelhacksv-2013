//
//  redis-objc.h
//  redis-sample
//
//  Created by Andreas Gerlach on 7/8/12.
//  Copyright (c) 2012 Appelgriebsch. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "hiredis.h"

#define REDIS_DEFAULT_PORT 6379

/*!
    objective-c wrapper to redis server API
 
    @author Andreas Gerlach
    @copyright Appelgriebsch
    @charset utf-8
    @encoding utf-8
    @version 0.2
 
 */
@interface APGRedisServer : NSObject

/*!
    connect to a running redis server
    
    @param host The name or IP address of the redis server
    @param port The port the redis server is listening on
 
    @return the initialized APGRedisServer object
 */
+ (id)connectTo:(NSString *)host onPort:(NSUInteger)port;

/*!
    tries to connect to a running redis server within the given time interval
 
    @param host The name or IP address of the redis server
    @param port The port the redis server is listening on
    @param interval The time interval to wait for the connection at maximum
 
    @return the initialized APGRedisServer object
 */
+ (id)connectTo:(NSString *)host onPort:(NSUInteger)port withTimeout:(NSTimeInterval)interval;

/*!
    connect to a running redis server using the given unix socket
 
    @param unixPath The full path name to the unix socket maintained by the redis server
 
    @return the initialized APGRedisServer object
 */
+ (id)connectTo:(NSString *)unixPath;

/*!
    disconnects from a redis server, closing any open connection to it
 */
- (void)disconnect;

/*!
    flag denoting if a connection to a redis server exists or not
 */
@property(nonatomic, readonly, getter=isConnected) BOOL connected;

/*!
    flag denoting if an authentication is required before executing commands
 */
@property(nonatomic, readonly) BOOL requiresAuthentication;

/*!
    holds and returns the error information of the last operation 
 */
@property(nonatomic, readonly) NSError *lastError;

/*!
    sends the PING command to the connected redis server
 
    @return The value replied by the redis server or NIL in case of an error @see lastError
 */
- (NSString *)ping;

/*!
    sends the ECHO command to the connected redis server
 
    @param value The string value that should be send to the redis server for echoing
    
    @return The value replied by the redis server or NIL in case of an error @see lastError
 */
- (NSString *)echo:(NSString *)value;

/*!
    sends the DBSIZE command to the connected redis server
 
    @return The value replied by the redis server or NIL in case of an error @see lastError
 */
- (NSNumber *)dbSize;

/*!
    selects the active database (0-n)
 
    @param db the database to use
 
    @return flag denoting if the database has been activated
 */
- (BOOL)setDatabase:(NSUInteger)db;

/*!
    authenticates the access to the database server

    @param pwd the password for connecting to the database server

    @return flag denoting if the access has been granted or not
 */
- (BOOL)authenticate:(NSString *)pwd;

/*!
    checks if a key is available in the system

    @param key the key that should be available

    @return flag denoting if the key has been found or not
 */
- (BOOL)hasKey:(NSString *)key;

/*!
    removes a key and the value associated with it

    @param key  the key to remove from the database

    @return flag denoting the success of the operation

 */
- (BOOL)deleteKey:(NSString *)key;

/*!
    increases the time-to-live for an existing key by the given amount of time

    @param timeInterval the time interval that the key's TTL should be enhanced with

    @param key the key which TTL should be updated

    @return flag denoting the success of the operation
 */
- (BOOL)increaseTTL:(NSTimeInterval)timeInterval forKey:(NSString *)key;

/*!
    removes any TTL constraint on a key

    @param key the key which TTL constraint should be removed

    @return flag denoting the success of the operation
 */
- (BOOL)persistKey:(NSString *)key;

/*!
    retrieves the TTL for the given key

    @param key the key which TTL is being examined

    @return the TTL for the key - if any
 */
- (NSTimeInterval)retrieveTTL:(NSString *)key;

/*!
    renames an existing key to a new value w/ optionally checking if the new key already exists

    @param key  the key that is to be renamed

    @param newKey the new value for the key

    @param bOverridingAllowed flag denoting if the renaming only should take place if the new key isn't used already

    @return flag denoting the success of the operation
 */
- (BOOL)renameKey:(NSString *)key toKey:(NSString *)newKey allowOverriding:(BOOL)bOverridingAllowed;

/*!
    returns a random generated key from the current database

    @return a random generated key or NIL if the current database is empty
 */
- (NSString *)randomKey;

/*!
    stores an alphanumeric value for a key into the database

    @param value the value to store

    @param key the key for this value to find it later

    @return flag denoting the success of the operation
 */
- (BOOL)set:(NSString *)value forKey:(NSString *)key;

/*!
    stores an alphanumeric value for a key into the database for a specific time

    @param value the value to store

    @param key the key for this value to find it later

    @param timeOut the timespan the value is valid in the database

    @return flag denoting the success of the operation
 */
- (BOOL)set:(NSString *)value forKey:(NSString *)key timeOut:(NSTimeInterval)timeOut;

/*!
    retrieves an alphanumeric value from the database by looking for the key

    @param key the key that should be used for looking up the value

    @return the value that is stored for this key in the database or NIL if not found
 */
- (NSString *)get:(NSString *)key;

/*!
    appends an alphanumeric string to the value stored for a key in the database

    @param value the string that should be append to the existing value

    @param key the key to lookup the existing value in the database

    @return flag denoting the success of the operation
 */
- (BOOL)append:(NSString *)value toKey:(NSString *)key;

/*!
    retrieves a part of the string stored for a key in the database

    @param key the key to lookup the existing value in the database

    @param range the part of the string to return

    @return the value that is stored in the database for this key cut down to the range
 */
- (NSString *)get:(NSString *)key forRange:(NSRange)range;

/*!
    replaces part of the string stored in the database for the given key with a new value starting at the stated position

    @param value the new string that should be written

    @param key the key that is used to lookup the existing value

    @param pos the position at which the new value is written to the existing value

    @return flag denoting the success of the operation
 */
- (BOOL)set:(NSString *)value forKey:(NSString *)key atIndex:(NSUInteger)pos;

/*!
    retrieves the length of the string that is stored for a key in the database

    @param key the key to lookup the existing value in the database

    @return the length of the value stored for this key
 */
- (NSUInteger)getLength:(NSString *)key;

/*!
    stores a numeric value into the database for a given key

    @param value the numerical value to store into the database

    @param key the key used to store the value into the database

    @return flag denoting the success of the operation
 */
- (BOOL)addCounter:(NSNumber *)value forKey:(NSString *)key;

/*!
    stores a numeric value into the database for a given key for the given time

    @param value the numerical value to store into the database

    @param key the key used to store the value into the database

    @param timeOut the timespan the value is valid in the database

    @return flag denoting the success of the operation
 */
- (BOOL)addCounter:(NSNumber *)value forKey:(NSString *)key timeOut:(NSTimeInterval)timeOut;

/*!
    retrieves a counter from the database

    @param key the key used to lookup the value from the database

    @return the numeric value that is stored in the database
 */
- (NSNumber *)getCounter:(NSString *)key;

/*!
    increases the existing counter by a given value

    @param value the value that the counter should be increased with

    @param key the key to lookup the existing counter from the database

    @return the new value for the counter after the increasing took place
 */
- (NSNumber *)increaseCounterBy:(NSNumber *)value forKey:(NSString *)key;

/*!
    decreases the existing counter by a given value

    @param value the value that the counter should be decreased with

    @param key the key to lookup the existing counter from the database

    @return the new value for the counter after the decreasing took place
 */
- (NSNumber *)decreaseCounterBy:(NSNumber *)value forKey:(NSString *)key;

/*!
    increases the existing counter by 1

    @param key the key to lookup the existing counter from the database

    @return the new value for the counter after the increasing took place
 */
- (NSNumber *)increaseCounter:(NSString *)key;

/*!
    decreases the existing counter by 1

    @param key the key to lookup the existing counter from the database

    @return the new value for the counter after the decreasing took place
 */
- (NSNumber *)decreaseCounter:(NSString *)key;

/*!
    creates a new stack with the given items stored under the given key in the database

    @param key the key to create the stack with

    @param items the items to initialize the stack with

    @return a flag denoting the success of the operation
 */
- (BOOL)createStack:(NSString *)key withItems:(NSArray *)items;

/*!
    creates a new stack with the given items stored under the given key in the database

    @param key the key to create the stack with

    @param items the items to initialize the stack with

    @param timeOut the timespan the stack is valid in the database

    @return a flag denoting the success of the operation
 */
- (BOOL)createStack:(NSString *)key withItems:(NSArray *)items timeOut:(NSTimeInterval)timeOut;

/*!
    pops an item from the stack with the given key

    @param key the key to lookup the stack in the database

    @return the top most item from the stack with the given key or nil
 */
- (id)popItemFromStack:(NSString *)key;

/*!
    push an item to the stack with the given key

    @param item the item to be placed on the stack

    @param key the key to lookup the stack in the database

    @return flag denoting the success of the operation
 */
- (BOOL)pushItem:(id)item toStack:(NSString *)key;

/*!
    creates a new queue with the given items stored under the given key in the database

    @param key the key to create the queue with

    @param items the items to initialize the queue with

    @return a flag denoting the success of the operation
 */
- (BOOL)createQueue:(NSString *)key withItems:(NSArray *)items;

/*!
    creates a new queue with the given items stored under the given key in the database

    @param key the key to create the queue with

    @param items the items to initialize the queue  with

    @param timeOut the timespan the queue is valid in the database

    @return a flag denoting the success of the operation
 */
- (BOOL)createQueue:(NSString *)key withItems:(NSArray *)items timeOut:(NSTimeInterval)timeOut;

/*!
    pops an item from the queue with the given key

    @param key the key to lookup the queue in the database

    @return the first item from the queue with the given key or nil
 */
- (id)popItemFromQueue:(NSString *)key;

/*!
    push an item to the queue with the given key

    @param item the item to be placed on the queue

    @param key the key to lookup the queue in the database

    @return flag denoting the success of the operation
 */
- (BOOL)pushItem:(id)item toQueue:(NSString *)key;

- (redisReply *)execute:(NSString *)command;

- (redisReply *)execute:(NSString *)command withParam:(id)param;

- (redisReply *)execute:(NSString *)command withKey:(NSString *)key value:(id)value;

- (redisReply *)execute:(NSString *)command withKey:(NSString *)key values:(id)firstValue, ... __attribute__((sentinel));


@end
