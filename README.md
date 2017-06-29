# LCCheck
Check the textField input

## 引用
LCCheck.framework

## 示例
```
//全局配置提示信息
    [[LCCheck check].messageConfigure setValue:@"密码为6-16位数字或字母" forKey:LCCheckMessagePassword];
```

```
//依次校验手机号、密码
    [LCCheck lc_checkWith:^(LCCheck *check) {
        check.textField(self.phoneTextField).name(@"手机号").null().validate(LCCheckRegularPhone, nil);
        check.textField(self.passwordTextField).name(@"密码").null().validate(LCCheckRegularPassword, nil);
    } completion:^(LCCheckResult result, NSString *message, UITextField *textField) {
        if (result == LCCheckResultUnValidated || result == LCCheckResultNull) {
            [self toastWith:message];
        }
    }];
```
或者
```
//依次校验手机号、密码
    [LCCheck lc_checkWith:^(LCCheck *check) {
        check.textField(self.phoneTextField).name(@"手机号").null().validate(LCCheckRegularPhone, nil).with.textField(self.passwordTextField).name(@"密码").null().validate(LCCheckRegularPassword, nil);
    } completion:^(LCCheckResult result, NSString *message, UITextField *textField) {
        if (result == LCCheckResultUnValidated || result == LCCheckResultNull) {
            [self toastWith:message];
        }
    }];
```
### .textField(参数1)
参数1：校验对象，必须为UITextField类型，非空

### .name(参数1)
参数1：校验对象的名称，用于返回错误信息

### .null()
判断输入是否为空

### .validate(参数1, 参数2)
判断输入格式<br>
参数1：正则表达式，可以使用枚举参数，也可以直接传正则表达式的字符串。非空<br>
参数2：格式校验错误的提示文字，通过message返回，可以为空。优先级：参数2 > 全局配置 > 默认提示

### result
枚举类型，校验结果

### message
错误信息

### textField
校验对象

## note
note：每一步的校验结果都会通过completion回调，如果result == LCCheckResultUnValidated || result == LCCheckResultNull，则校验失败
