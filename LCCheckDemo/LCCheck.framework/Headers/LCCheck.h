//
//  LCCheck.h
//  VerifyDemo
//
//  Created by 伯明利 on 2017/6/23.
//  Copyright © 2017年 伯明利. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#pragma mark - 校验结果枚举
typedef NS_ENUM(NSInteger, LCCheckResult) {
    LCCheckResultValidated = 0,//校验通过
    LCCheckResultNonnull = 1,//输入非空
    LCCheckResultNull = 2,//输入为空
    LCCheckResultUnValidated = 3,//格式非法
};

#pragma mark - 正则表达式
typedef NSString *LCCheckRegular NS_EXTENSIBLE_STRING_ENUM;
UIKIT_EXTERN LCCheckRegular const LCCheckRegularPhone;//手机号
UIKIT_EXTERN LCCheckRegular const LCCheckRegularPassword;//密码
UIKIT_EXTERN LCCheckRegular const LCCheckRegularCaptcha;//验证码
UIKIT_EXTERN LCCheckRegular const LCCheckRegularIdentityCardNumber;//身份证号码
UIKIT_EXTERN LCCheckRegular const LCCheckRegularEmail;//邮箱
UIKIT_EXTERN LCCheckRegular const LCCheckRegularLicensePlateNumber;//车牌号
UIKIT_EXTERN LCCheckRegular const LCCheckRegularMoney;//金额

#pragma mark - 全局配置提示信息的key
typedef NSString *LCCheckMessage NS_EXTENSIBLE_STRING_ENUM;
UIKIT_EXTERN LCCheckMessage const LCCheckMessagePhone;//手机号
UIKIT_EXTERN LCCheckRegular const LCCheckMessagePassword;//密码
UIKIT_EXTERN LCCheckRegular const LCCheckMessageCaptcha;//验证码
UIKIT_EXTERN LCCheckRegular const LCCheckMessageIdentityCardNumber;//身份证号码
UIKIT_EXTERN LCCheckRegular const LCCheckMessageEmail;//邮箱
UIKIT_EXTERN LCCheckRegular const LCCheckMessageLicensePlateNumber;//车牌号
UIKIT_EXTERN LCCheckRegular const LCCheckMessageMoney;//金额

@interface LCCheck : NSObject

/********************************** 全局配置 **********************************/

+ (LCCheck *)check;

/**
 配置提示信息
 */
@property (nonatomic, strong) NSMutableDictionary <LCCheckMessage, NSString *>*messageConfigure;

/********************************** 校验 **********************************/

/**
 校验输入框输入是否合法

 @param block 回调函数，链式语法
 @param completion 回调函数，根据result和textField可以获取每一次校验的结果。当某一步校验失败后不会继续往下校验。result == LCCheckResultValidated 或 result == LCCheckResultNonnull 时，message为nil
 */
+ (void)lc_checkWith:(void(^)(LCCheck *check))block completion:(void(^)(LCCheckResult result, NSString *message, UITextField *textField))completion;

/**
 连接符
 */
- (LCCheck *)with;

/**
 输入框
 */
- (LCCheck *(^)(UITextField *))textField;

/**
 输入项名称
 */
- (LCCheck *(^)(NSString *name))name;

/**
 判空：(空)
 */
- (LCCheck *(^)())null;

/**
 校验：(正则表达式, 错误信息)
 */
- (LCCheck *(^)(LCCheckRegular regular, NSString *message))validate;

@end

/*
 使用示例
 
 //全局配置提示信息
 [[LCCheck check].messageConfigure setValue:@"密码为6-16位数字或字母" forKey:LCCheckMessagePassword];
 
 //依次校验手机号、密码
 [LCCheck lc_checkWith:^(LCCheck *check) {
 check.textField(self.phoneTextField).name(@"手机号").null().validate(LCCheckRegularPhone, nil);
 check.textField(self.passwordTextField).name(@"密码").null().validate(@"^[a-zA-Z0-9]{6,16}$", nil);
 
 //也可以按如下方式写
 //check.textField(self.phoneTextField).name(@"手机号").null().validate(LCCheckRegularPhone, nil).with.textField(self.passwordTextField).name(@"密码").null().validate(LCCheckRegularPassword, nil);
 
 } completion:^(LCCheckResult result, NSString *message, UITextField *textField) {
 if (result != LCCheckResultValidated) {
 [self toastWith:message];
 }
 }];
 */
