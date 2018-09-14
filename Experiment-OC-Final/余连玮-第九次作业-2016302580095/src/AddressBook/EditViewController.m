//
//  EditViewController.m
//  AddressBook
//
//  Created by yiner on 2018/6/22.
//  Copyright © 2018年 yiner. All rights reserved.
//

#import "EditViewController.h"
#import "Address+Create.h"

@interface EditViewController ()
@property (weak, nonatomic) IBOutlet UITextField *name;
@property (weak, nonatomic) IBOutlet UITextField *phone;
@property (weak, nonatomic) IBOutlet UITextField *email;
@property (weak, nonatomic) IBOutlet UITextField *anAddress;
@property (weak, nonatomic) IBOutlet UITextField *weChat;

@end

@implementation EditViewController
@synthesize name = _name;
@synthesize phone = _phone;
@synthesize email = _email;
@synthesize anAddress = _anAddress;
@synthesize weChat = _weChat;
@synthesize address = _address;
@synthesize sourceType = _sourceType;
@synthesize managedObjectContext = _managedObjectContext;
@synthesize oldName = _oldName;

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
	
	if (self.address != nil) {
		self.name.text = self.address.name;
		self.phone.text = [NSString stringWithFormat:@"%d",self.address.phone];
		self.email.text = self.address.email;
		self.anAddress.text = self.address.address;
		self.weChat.text = self.address.weChat;
		//set image
		// save oldname for update's argument
		self.oldName = self.name.text;
	}
	
}

// show alert message and segue
- (void)showAlertView:(NSString *)message
{
	// 1.创建UIAlertController
	UIAlertController *alertController = [UIAlertController alertControllerWithTitle:message message:nil preferredStyle:UIAlertControllerStyleAlert];
	
	// 2.创建并添加按钮
	UIAlertAction *okAction = [UIAlertAction actionWithTitle:@"确定" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
		// 返回上一个页面
		if ([message isEqualToString:@"更新联系人成功！"]){
			if ([self.navigationController.topViewController respondsToSelector:@selector(setAddress:)]) {
				[self.navigationController.topViewController performSelector:@selector(setAddress:) withObject:self.address];
			}
		}
		
		[self.navigationController popViewControllerAnimated:YES];
	}];
	
	[alertController addAction:okAction];
	
	// 3.呈现UIAlertContorller
	[self presentViewController:alertController animated:YES completion:nil];
}


// cancel and back
- (IBAction)pressCancel:(id)sender {
	[self.navigationController popViewControllerAnimated:YES];
}


- (IBAction)confirmAddOrUpdateContact:(id)sender {
	BOOL isSuccess = YES;
	NSString *message = nil;
	NSDictionary *info= nil;
	info = @{
				@"name" : self.name.text,
				@"phone" : self.phone.text,
				@"email" : self.email.text,
				@"address" : self.anAddress.text,
				@"weChat" : self.weChat.text,
				//@"image" : nil
				};
	
	if ([self.sourceType  isEqual: @"add"]) { // add
		[Address insertDataWithAddressInfo:info inManagedObjectContext:self.managedObjectContext];
		message = @"添加联系人成功！";
	} else { // update
		Address * newAddress = nil;
		isSuccess = [Address UpdateDataWithAddressInfo:info andOldName:self.oldName inManagedObjectContext:self.managedObjectContext returnAddress:newAddress];
		if (isSuccess == YES) {
			// return updated address
			self.address = newAddress;
			message = @"更新联系人成功！";
		} else {
			message = @"更新联系人失败！";
		}
	}
	// show alert and back
	[self showAlertView:message];
}

@end
