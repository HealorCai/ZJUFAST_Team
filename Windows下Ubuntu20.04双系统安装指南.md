# Windows下Ubuntu20.04双系统安装指南
本文档是Ubuntu双系统的操作指南。在电脑存在Windows情况下安装Ubuntu20.04作为第二操作系统     
本文参考"从零制作自主空中机器人"课程     
github链接: https://github.com/ZJU-FAST-Lab/Fast-Drone-250     
B站视频链接: https://www.bilibili.com/video/BV1WZ4y167me
## Step0: 前期准备
- 在电脑磁盘中清理出80G以上存储空间、准备一个8G以上空U盘
## Step1: 在Windows下载Ubuntu20.04镜像
- 镜像站地址：`http://mirrors.aliyun.com/ubuntu-releases/20.04/` 
- 下载 `ubuntu-20.04.4-desktop-amd64.iso`
## Step2: 下载镜像烧录软件UltraISO
- UltraISO官网：`https://cn.ultraiso.net/`
## Step3: 格式化U盘并制作Ubuntu启动盘
- U盘格式化
  注意不要在卷标上面输入符号等不合法的字符

  <img src="https://github.com/qtjdyx/ZJUS/assets/116424162/8baec5d3-9f08-482a-92e5-ea0b766539fb" width="25%">
- 打开UltraISO,选免费版继续试用

  <img src="https://github.com/qtjdyx/ZJUS/assets/116424162/6b73505c-15c4-4655-ad5a-bc30f677e38a" width="25%">
  
- 打开下载的镜像

  <img src="https://github.com/qtjdyx/ZJUS/assets/116424162/6850b18d-a1eb-4351-904a-c575317ee8d7" width="25%">    
  <img src="https://github.com/qtjdyx/ZJUS/assets/116424162/6027cc4e-4582-4b2e-beb2-8817be12cfd3" width="40%">   
- 写入硬盘镜像
  
  <img src="https://github.com/qtjdyx/ZJUS/assets/116424162/73ffea14-5cef-4ad2-bbe7-56efcfd19da6" width="25%">
- 选择U盘，等待写入  

  <img src="https://github.com/qtjdyx/ZJUS/assets/116424162/b027080d-b434-494d-9b17-5de1086984c1" width="25%">
## Step4: 释放磁盘空间
- 以管理员权限进入进入控制面板-系统和安全-创建并格式化硬盘分区

  <img src="https://github.com/qtjdyx/ZJUS/assets/116424162/ac7c0c0f-0d70-495d-8226-2b50b0c937c8" width="75%">
  <img src="https://github.com/qtjdyx/ZJUS/assets/116424162/82828ae2-a215-471c-9e9c-08c7239459e6" width="75%">
- 选择你要分割的分区（有80G以上空闲的分区），右键，选择压缩卷

  <img src="https://github.com/qtjdyx/ZJUS/assets/116424162/d7ec9268-7d6a-4a03-b27f-87be3fb2391f" width="50%">
- 输入要压缩的空间量（单位为MB），该大小为你希望分给Ubuntu系统的大小（图中用2000MB示意）

  <img src="https://github.com/qtjdyx/ZJUS/assets/116424162/7cbfe86b-2b96-4c04-bdf2-50ea2ab4a065" width="50%">
- 此时，在你压缩的磁盘后将会出现一块未分配的磁盘分区，大小为你输入的压缩空间量

  <img src="https://github.com/qtjdyx/ZJUS/assets/116424162/b38fc73d-8788-4e83-ac7d-63b7a9efbdd4" width="50%">
## Step5: 重启电脑进入BIOS界面，设置启动选项
- 首先查询你的电脑进入BIOS界面的方式

  <img src="https://github.com/qtjdyx/ZJUS/assets/116424162/131d8996-4b39-4fd8-b8d3-e811553a48b9" width="50%">
- 重启电脑，开机同时连续按F2（你的电脑进入BIOS界面的方式），当电脑品牌徽标出现后，电脑会进入BIOS界面/UEFI界面

  <img src="https://github.com/qtjdyx/ZJUS/assets/116424162/9a4c365c-c46b-4404-b77e-61809acf0b6f" width="50%">
- 进入Advance模式下，找到`Security`下的安全启动，关闭安全启动项     
  `Security（安全）`—`Secure Boot（安全启动）`—`Disabled（关闭）`     
  <img src="https://github.com/qtjdyx/ZJUS/assets/116424162/d1cca790-5420-4763-bd86-e193eec5acfc" width="50%">
- 有时要在启动项`Boot`中找到U盘启动项并允许从U盘启动
- ！！！！保存退出！！！！
- 重启电脑，插上启动盘，进入BIOS界面，此时在开机启动项上会出现两个以上启动选项，一个是默认启动项`Windows boot manager`,一个是你的U盘启动选项xxxxxx(一般为U盘厂家名字）（xxxx（你的启动盘卷标））
- 将U盘启动上移至第一启动选项，保存退出
- 备注：这一步非必须，视情况可以与上一步合并

## Step6: 插入Ubuntu启动盘并用U盘启动
- 确认你的笔记本在开机前处在以下状态
  1. 在磁盘中拥有一块大小足够的未分配空间
  2. 电脑的安全启动选项已经关闭，否则会禁止你从外部启动
  3. U盘启动选型被允许，否则会禁止你从U盘启动
  4. 最好U盘启动选项在第一顺位
  5. 电脑处在关机状态
- 插入启动盘并从U盘启动，选择`install ubuntu`

  <img src="https://github.com/qtjdyx/ZJUS/assets/116424162/6b5b5b5d-85f1-4a33-9854-beaed9dd5836" width="50%"> 
 
## Step7: 安装Ubuntu操作系统
- 最好选择英文安装，想用中文也行
- 选择键盘布局
- 不连接到无线网
- 选择正常安装 如有Nvidia独显或者一些特殊的网卡，可以尝试选择
  `为图形或无线硬件，以及其他媒体格式安装第三方软件`

  <img src="https://github.com/qtjdyx/ZJUS/assets/116424162/77897dad-de3a-4434-9145-ed31490ede38" width="50%">

- 选择其他安装选型！！一定**不能**选择清除整个磁盘！！

  <img src="https://github.com/qtjdyx/ZJUS/assets/116424162/44ffb729-469a-499e-a29a-919c541a8c2f" width="50%">

- 这时候，界面上将会显示你当前磁盘的分区表！！一定**不能**选择新建分区表！！否则将会格式化你的磁盘
- 视频中选择新建的原因是NUC是新机，固态硬盘上没有任何分区信息，才需要新建分区表
- 在磁盘的分区表中，应该有一块空闲区域，即为那块未分配的磁盘空间
- 选中空闲，点击`+`
  
  <img src="https://github.com/qtjdyx/ZJUS/assets/116424162/3f24a360-2110-40fc-a1d6-b0bccaba2614f" width="50%">
   
- 设置EFI系统分区 EFI system partition，格式为主分区，默认空间起始位置，大小512MB
- 选中空闲，点击`+`
- 设置交换空间swapping space，格式为逻辑分区，默认空间起始位置，大小为电脑内存两倍，8GRAM->16G,16GRAM->20G-30G左右
- 选中空闲，点击`+`
- 将剩下的空间挂载在主分区`/`下,格式为主分区，默认空间起始位置，大小所有空闲，用于Ext4日志文件系统       

 <img src="https://github.com/qtjdyx/ZJUS/assets/116424162/3974c486-6fd9-46aa-8bb5-c25d883ea2e7" width="27%">
 <img src="https://github.com/qtjdyx/ZJUS/assets/116424162/88137925-fa91-4f7a-8da2-37a6896fbde7" width="29%">
 <img src="https://github.com/qtjdyx/ZJUS/assets/116424162/cfc49587-3155-406d-9de1-2519a8425c71" width="26%">

- 选择时区
- 创建用户名
- 在ubuntu命令行中，每一行最开始的即为user@PC:(用户名@计算机名:)
- 密码可以设置一位，方便后续命令行中sudo的时候输入密码
- 安装完成
- 重启
## Step8: 设置默认启动选项
- 进入BIOS-启动项
- 选自Windows或者Ubuntu作为默认启动项
- 以后电脑开机时会弹出启动项选择界面，未选择则按照默认启动项启动。
  
