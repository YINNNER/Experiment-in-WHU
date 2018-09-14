//
//  DetailViewController.h
//  AddressBook
//
//  Created by yiner on 2018/6/19.
//  Copyright © 2018年 yiner. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Address.h"

@interface DetailViewController : UIViewController
@property (nonatomic, strong) Address *address;
@property (nonatomic, strong) NSManagedObjectContext *managedObjectContext;
@end

