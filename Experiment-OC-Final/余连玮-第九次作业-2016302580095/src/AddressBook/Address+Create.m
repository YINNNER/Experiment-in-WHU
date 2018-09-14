//
//  Address+Create.m
//  AddressBook
//
//  Created by yiner on 2018/6/19.
//  Copyright © 2018年 yiner. All rights reserved.
//
//

#import "Address+Create.h"

#define ADDRESS_NAME @"name"
#define ADDRESS_PHONE @"phone"
#define ADDRESS_EMAIL @"email"
#define ADDRESS_ADDRESS @"address"
#define ADDRESS_WECHAT @"weChat"
#define ADDRESS_IMAGE @"image"

@implementation Address (Create)

// create an address for the named person
+ (Address *)addressWithAddressInfo:(NSDictionary *)info inManagedObjectContext:(NSManagedObjectContext *)context
{
	Address *address = nil;
	
	// Build a fetch request to see if we can find the address of that named person in the database.
	NSFetchRequest *request = [NSFetchRequest fetchRequestWithEntityName:@"Address"];
	request.sortDescriptors = @[[NSSortDescriptor sortDescriptorWithKey:@"name" ascending:YES selector:@selector(localizedCaseInsensitiveCompare:)]];
	request.predicate = [NSPredicate predicateWithFormat:@"name = %@", info[ADDRESS_NAME]];
	
	// Execute the fetch
	NSError *error;
	NSArray *matches = [context executeFetchRequest:request error:&error];
	
	// Check what happened in the fetch
	if (!matches || ([matches count] > 1)) {  // nil means fetch failed; more than one impossible (unique!)
		// handle error
	} else if (![matches count]) {  // none found, so let's create a address for that named person
		address = [NSEntityDescription insertNewObjectForEntityForName:@"Address" inManagedObjectContext:context];
		address.name = info[ADDRESS_NAME];
		address.phone = [info[ADDRESS_PHONE] intValue];
		address.email = info[ADDRESS_EMAIL];
		address.address = info[ADDRESS_ADDRESS];
		address.weChat = info[ADDRESS_WECHAT];
		//address.image = info[ADDRESS_IMAGE];
		
	} else { // found the Photo, just return it from the list of matches (which there will only be one of)
		address = [matches lastObject];
	}
	
	return address;
}

+ (NSArray *) fetchDataWithName:(NSString *) name inManagedObjectContext:(NSManagedObjectContext *)context
{
	NSArray *matches = nil;
	// Build a fetch request to see if we can find the address of that named person in the database.
	NSFetchRequest *request = [NSFetchRequest fetchRequestWithEntityName:@"Address"];
	request.sortDescriptors = @[[NSSortDescriptor sortDescriptorWithKey:@"name" ascending:YES selector:@selector(localizedCaseInsensitiveCompare:)]];
	request.predicate = [NSPredicate predicateWithFormat:@"name = %@",name];
	
	// Execute the fetch
	NSError *error;
	matches = [context executeFetchRequest:request error:&error];
	
	return matches;
}


+ (void) insertDataWithAddressInfo:(NSDictionary *)info inManagedObjectContext:(NSManagedObjectContext *)context
{
	Address *address = nil;
	
	NSArray* matches = [self fetchDataWithName:info[ADDRESS_NAME] inManagedObjectContext:context];
	
	// Check what happened in the fetch
	if (!matches || ([matches count] > 1)) {  // nil means fetch failed; more than one impossible (unique!)
		// handle error
	} else if (![matches count]) {  // none found, so let's create a address for that named person
		address = [NSEntityDescription insertNewObjectForEntityForName:@"Address" inManagedObjectContext:context];
		address.name = info[ADDRESS_NAME];
		address.phone = [info[ADDRESS_PHONE] intValue];
		address.email = info[ADDRESS_EMAIL];
		address.address = info[ADDRESS_ADDRESS];
		address.weChat = info[ADDRESS_WECHAT];
		//address.image = info[ADDRESS_IMAGE];
		
	} else { // found the Photo, just return it from the list of matches (which there will only be one of)
		address = [matches lastObject];
	}
}

+ (BOOL) UpdateDataWithAddressInfo:(NSDictionary *)info andOldName:(NSString *)oldname inManagedObjectContext:(NSManagedObjectContext *)context returnAddress:(Address *)newAddress
{
	Address *address = nil;
	
	NSArray* matches = [self fetchDataWithName:oldname inManagedObjectContext:context];
	
	// Check what happened in the fetch
	if ([matches count] != 1) {
		// handle error
	} else  {
		address = [matches lastObject];
		
		address.name = info[ADDRESS_NAME];
		address.phone = [info[ADDRESS_PHONE] intValue];
		address.email = info[ADDRESS_EMAIL];
		address.address = info[ADDRESS_ADDRESS];
		address.weChat = info[ADDRESS_WECHAT];
		//address.image = info[ADDRESS_IMAGE];
	}
	
	// save
	NSError *error = nil;
	if ([context save:&error]) {
		NSLog(@"更新数据成功");
		newAddress = address;
		return YES;
	} else {
		NSLog(@"更新数据失败, %@", error);
		return NO;
	}

}

+ (BOOL) deleteDataWithName:(NSString *)name inManagedObjectContext:(NSManagedObjectContext *)context
{
	Address *address = nil;
	NSArray* matches = [self fetchDataWithName:name inManagedObjectContext:context];
	address = [matches lastObject];
	[context deleteObject:address];
	
	// save
	NSError *error = nil;
	if ([context save:&error]) {
		NSLog(@"删除数据成功");
		return YES;
	} else {
		NSLog(@"删除数据失败, %@", error);
		return NO;
	}
}

@end
