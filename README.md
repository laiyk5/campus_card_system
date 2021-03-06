# 校园卡管理系统

## 作者

- 姓名：赖奕恺
- 学号：19335093
- 所属院系：中山大学数据科学与计算机学院![image-20200629021516861](C:\Users\Alex\AppData\Roaming\Typora\typora-user-images\image-20200629021516861.png)

## 校园卡管理系统

校园卡管理系统将校园卡功能和学生的使用需求、管理者的管理需求结合在一起。

它为学生提供了消费、查余、挂失、身份证明等功能，为管理者提供了简洁且人性化的增删改查功能。

本系统只是提供了一个基本框架，但设计模式易于扩展。如消费终端可经超级管理员授权，具有免登录消费功能；自助充值机可以仅提供充值功能，在检测到入账后，帮助学生完成自助充值。

## 功能介绍（超级管理员版本）

### 管理员（分发给普通管理员的说明部分）

- 运行程序后，遵循程序的输入规则，选择进入管理员菜单，并输入账号和密码，系统会自动识别普通管理员和超级管理员（超级管理员账号：001，密码：628，请在分发此说明时删除括号内信息）
- 在菜单内，单次操作都是针对单张卡或单位学生的。
- 只有超级管理员才有管理管理员信息的权限。
- 需注意以下几点：
  - 删除学生的同时会同时删除绑定的卡
  - 为学生绑定新卡会创建新卡，会复制除卡号外的所有信息，并会删除旧卡。

### 学生（分发给学生的说明部分）

- 运行程序后，遵循程序的输入规则，选择进入学生菜单，并输入**学生**账号和密码。
- 在菜单内，只能对与自己绑定的校园卡进行操作。
- 功能解释：
  - **充值**权限属于管理员权限，请到管理员处或有管理员权限的机器处充值。
  - 你可以将卡置为**挂失**状态，挂失状态的卡将无法进行充值和消费，但仍可查询个人信息。
  - 你也可以随时激活**未激活**（处于挂失状态）的卡，未激活的卡在改密后方可激活。
  - 新密码需在6位以内，不可为默认密码（0），也不可为旧密码
- 其他提示：
  - 默认密码为0，补办的新卡默认密码为0。

