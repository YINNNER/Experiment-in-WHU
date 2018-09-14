//
//  CallViewController.m
//  AddressBook
//
//  Created by yiner on 2018/6/24.
//  Copyright © 2018年 yiner. All rights reserved.
//

#import "CallViewController.h"


@implementation CallViewController
@synthesize phoneNumber = _phoneNumber;
@synthesize text = _text;

- (void)viewWillAppear:(BOOL)animated
{
	self.phoneNumber.text = self.text;
}

- (IBAction)ClickRingOff:(id)sender {
	[self.navigationController popViewControllerAnimated:YES];
}

@end
