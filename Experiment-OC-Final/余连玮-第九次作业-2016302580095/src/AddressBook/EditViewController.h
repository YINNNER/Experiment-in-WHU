//
//  EditViewController.h
//  AddressBook
//
//  Created by yiner on 2018/6/22.
//  Copyright © 2018年 yiner. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Address.h"

@interface EditViewController : UIViewController
@property (nonatomic, strong) Address *address;
@property (nonatomic, strong) NSManagedObjectContext *managedObjectContext;
@property (nonatomic, strong) NSString *oldName;
@property (nonatomic, strong) NSString *sourceType; // decide segue from which VC
					  //add represent AddressTVC, edit represent DetailVC
@end
