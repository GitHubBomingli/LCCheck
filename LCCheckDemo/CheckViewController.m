//
//  CheckViewController.m
//  VerifyDemo
//
//  Created by 伯明利 on 2017/6/23.
//  Copyright © 2017年 伯明利. All rights reserved.
//

#import "CheckViewController.h"
#import <LCCheck/LCCheck.h>
#import "UITextField+LCWordLimit.h"

@interface CheckViewController ()
@property (weak, nonatomic) IBOutlet UITextField *phoneTextField;
@property (weak, nonatomic) IBOutlet UITextField *passwordTextField;

@end

@implementation CheckViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    //全局配置提示信息
    [[LCCheck check].messageConfigure setValue:@"密码为6-16位数字或字母" forKey:LCCheckMessagePassword];
    
    [self.phoneTextField lc_wordLimit:11];
    [self.passwordTextField lc_wordLimit:16];
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)complete:(UIButton *)sender {
    //依次校验手机号、密码
    [LCCheck lc_checkWith:^(LCCheck *check) {
        check.textField(self.phoneTextField).name(@"手机号").null().validate(LCCheckRegularPhone, nil);
        check.textField(self.passwordTextField).name(@"密码").null().validate(LCCheckRegularPassword, nil);
        //也可以按如下方式写
        //check.textField(self.phoneTextField).name(@"手机号").null().validate(LCCheckRegularPhone, nil).with.textField(self.passwordTextField).name(@"密码").null().validate(LCCheckRegularPassword, nil);
        
    } completion:^(LCCheckResult result, NSString *message, UITextField *textField) {
        if (result == LCCheckResultUnValidated || result == LCCheckResultNull) {
            [self toastWith:message];
        }
    }];
}

- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    [super touchesEnded:touches withEvent:event];
    
    [self.view endEditing:YES];
}

- (void)toastWith:(NSString *)message {
    [self.view endEditing:YES];
    UILabel *label = [[UILabel alloc] init];
    label.backgroundColor = [[UIColor darkGrayColor] colorWithAlphaComponent:0.75];
    label.layer.cornerRadius = 4;
    label.layer.masksToBounds = YES;
    label.text = message;
    label.textColor = [UIColor whiteColor];
    label.font = [UIFont systemFontOfSize:14];
    label.textAlignment = NSTextAlignmentCenter;
    CGSize size = [label sizeThatFits:CGSizeMake(0, 40)];
    if (size.width > CGRectGetWidth([UIScreen mainScreen].bounds) - 52) {
        size.width = CGRectGetWidth([UIScreen mainScreen].bounds) - 52;
    }
    size.width += 20;
    label.frame = CGRectMake(CGRectGetWidth([UIScreen mainScreen].bounds) / 2.f - size.width / 2.f, CGRectGetMaxY([UIScreen mainScreen].bounds) - 100, size.width,40);
    [[UIApplication sharedApplication].keyWindow addSubview:label];
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [label removeFromSuperview];
    });
}

@end
