# 如何在开发板上安装HAP应用

以下以安装一个控制灯开关的应用为例讲解如何在开发板上安装HAP应用.

## 一、准备工作

- 准备一张SD卡(需要格式化成FAT32)，以及一个读卡器

## 二、安装HAP应用

1. 将tools/hap_tools/hap_example路径下的bm、LED.hap拷贝到SD卡中（Tips：bm文件和hap工程文件要拷贝到同一目录下）

2. 将SD卡插入到开发板中，并按开发板的RESET按键重启开发板

3. 在MobaXterm中输入以下命令，挂载SD卡
	```
    mount /dev/mmcblk0p0 /sdcard vfat
    ```
4. 输入以下命令，进入SD卡目录（进入文件所在的目录，以下代码示例是将文件拷贝到了根目录上）
	```
    cd /sdcard
    ```
5. 输入以下命令，打开调试模式
    ```
    ./bm set -s disable
    ./bm set -d enable
    ```
    
6.	安装应用
    ```
    ./bm install -p LED_1.0.0.hap
    ```

注: LED_1.0.0.hap为安装包名称，安装其他应用需要修改为对应的安装包名称。
