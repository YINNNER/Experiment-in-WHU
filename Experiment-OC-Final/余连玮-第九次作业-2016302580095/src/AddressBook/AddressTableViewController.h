//
//  AddressTableViewController.h
//  AddressBook
//
//  Created by yiner on 2018/6/20.
//  Copyright © 2018年 yiner. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CoreDataTableViewController.h"

@interface AddressTableViewController : CoreDataTableViewController <UISearchResultsUpdating>

//@property (nonatomic, strong) UIManagedDocument *addressDatabase;

// The Model for this class.
// Essentially specifies the database to look in to find all addresses to display in this table.
@property (nonatomic, strong) NSManagedObjectContext *managedObjectContext;

@end
