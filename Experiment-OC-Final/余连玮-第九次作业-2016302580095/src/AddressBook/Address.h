//
//  Address.h
//  AddressBook
//
//  Created by yiner on 2018/6/21.
//  Copyright © 2018年 yiner. All rights reserved.
//
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>

//NS_ASSUME_NONNULL_BEGIN

@interface Address : NSManagedObject

+ (NSFetchRequest<Address *> *)fetchRequest;

@property (nullable, nonatomic, copy) NSString *address;
@property (nullable, nonatomic, copy) NSString *email;
@property (nullable, nonatomic, retain) NSData *image;
@property (nonatomic, copy) NSString *name;
@property (nonatomic) int32_t phone;
@property (nullable, nonatomic, copy) NSString *weChat;

@end

//NS_ASSUME_NONNULL_END
