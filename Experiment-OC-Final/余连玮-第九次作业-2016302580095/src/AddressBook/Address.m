//
//  Address.m
//  AddressBook
//
//  Created by yiner on 2018/6/21.
//  Copyright © 2018年 yiner. All rights reserved.
//
//

#import "Address.h"

@implementation Address

+ (NSFetchRequest<Address *> *)fetchRequest {
	return [NSFetchRequest fetchRequestWithEntityName:@"Address"];
}

@dynamic address;
@dynamic email;
@dynamic image;
@dynamic name;
@dynamic phone;
@dynamic weChat;

@end
