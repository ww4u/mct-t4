MRH-T开发者工具包使用说明

1 编译生成库
1.1 windows MSVC平台
	使用VS2015打开src/MegaGateway.sln
	生成的库文件会存放到lib/windows/msvclib/下
	其中*.dll为动态库，*.lib为静态库

1.2 windows MinGW平台
	打开MinGW的msys终端环境(即：双击C:\MinGW\msys\1.0\msys.bat)
	$ cd src/
	$ make
	$ make install
	生成的库文件会存放到lib/windows/下
	其中*.so.*.*为动态库，*.a为静态库

1.3 Linux平台
	打开终端
	$ cd src/
	$ make
	$ make install
	生成的库文件会存放到lib/linux/下
	其中*.so.*.*为动态库，*.a为静态库

1.4 嵌入式Linux平台
	在linux上打开终端
	$ cd src/
	修改Makefile第一行，去掉注释并配置交叉编译路径
	$ make
	$ make install
	生成的库文件会存放到lib/armlinux/下
	其中*.so.*.*为动态库，*.a为静态库

2 运行示例
2.1 C语言示例
	QtConsole为C语言的Qt工程示例，可在windows或Linux平台构建运行
	
	VC++为C语言示例的VS2015工程示例，在windows上运行
	
2.2 GUI示例
	QtGUI目录为采用Qt写的GUI示例程序
	在windows或者linux上使用QtCreater打开pro文件
	构建，运行
	
2.3 python示例
	当前目录进入到example/python下
	可以在终端中输入python3 ./demo_device.py运行测试