//
//  Address+Create.h
//  AddressBook
//
//  Created by yiner on 2018/6/19.
//  Copyright © 2018年 yiner. All rights reserved.
//
//

#import "Address.h"

//NS_ASSUME_NONNULL_BEGIN

@interface Address (Create) 

+ (Address *)addressWithAddressInfo:(NSDictionary *)info
				inManagedObjectContext:(NSManagedObjectContext *)context;

+ (NSArray *) fetchDataWithName:(NSString *) name inManagedObjectContext:(NSManagedObjectContext *)context;

+ (void) insertDataWithAddressInfo:(NSDictionary *)info inManagedObjectContext:(NSManagedObjectContext *)context;

+ (BOOL) UpdateDataWithAddressInfo:(NSDictionary *)info andOldName:(NSString *)oldname inManagedObjectContext:(NSManagedObjectContext *)context returnAddress:(Address *)newAddress;

+ (BOOL) deleteDataWithName:(NSString *)name inManagedObjectContext:(NSManagedObjectContext *)context;

@end

//NS_ASSUME_NONNULL_END


