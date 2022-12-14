# lv_desktop_gui 开发记录

  本套控件基于 lvgl 8.2 进行开发，主要完成一个能够运行在嵌入式系统上面的 GUI 系统。

  GUI 部分的设计工作前期在仿真器上面运行测试。

  GUI部分的代码将会参与到 RTT 举办的 嵌入式GUI设计大赛中。

## 开发日志记录





## lvgl 8.2 特性说明





## 硬件基础

  后续运行环境主要基于 STM32F469-Discovery 开发板，带有 4.3 寸 DSI-LCD 显示屏，像素密度 800*480。

  支持 FT6206/FT6336G 电容式触摸IC，支持单点触控。



## 主要功能

- GUI桌面管理器
  - 显示 app 图标
  - 显示 wifi 连接状态
  - 显示电池电量
  - 显示当前时间
  - 显示图片缩略图
- 桌面悬浮球设计(全局管理)
  - 通过桌面悬浮球返回上一级桌面目录
  - 悬浮球可拖拽
  - 悬浮球显示效果有一定的透明度
- benchmarktest
- 计算器
- 2048游戏 (移植)
- 画板(移植)
- 电子相册
  - 读取TF卡中的照片，并实时显示，实现简单的照片切换动画
- 网络相册
  - 读取服务器上面存储的照片，并实时显示
- 新闻客户端
- 时钟
- 天气预报
- 串口调试终端
- 摄像头拍照显示
- 物联网设备状态显示
- 系统配置
  - WIFI 配置(ssid 和 password)
  - 时间配置





### GUI 桌面管理器

​	设计一款方便易容，能够快速扩展的嵌入式GUI桌面管理器，用于对当前系统中的 APP 进行切换。



## 附录





### 主要参考项目

- 100ask lvgl 相关项目



### 比赛申请说明



嵌入式GUI挑战赛

DIY桌面电子相册

你会怎么来实现该作品？告诉我们细节吧

使用STM32F469开发板DIY一台桌面电子相册，该相册具备联网功能，能够从云服务器或者自己的NAS上面获取照片并实时显示出来，支持定时更新照片；作为功能扩展，也可以当作一个桌面电子时钟，能够显示当前的时间、天气、当天新闻等内容，支持获取其他物联网摄像头数据信息，并实时显示。

说说该作品的三个亮点，来帮助我们更快的了解你的作品

1、可以联网的电子相册，自动刷新照片；
2、可以联网的桌面时钟，支持获取当地天气信息，国内热点新闻等；
3、支持功能可扩展的框架，加入对通用物联网平台的支持，能够获取其他物联网设备上的信息，如摄像头上的照片等等。

