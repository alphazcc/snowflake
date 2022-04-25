# 示例程序

SnowFlake 软件包提供一个 获取 ID 示例程序, 用于演示使用软件包获取 ID 功能。

**示例文件**

| 示例程序路径                 | 说明  |
| ----                         | ----- |
| samples/snowflake_sample.c   | 获取 5000 个 ID |

## 准备工作

### 获取软件包

- menuconfig 配置获取软件包和示例代码

    打开 RT-Thread 提供的 ENV 工具，使用 **menuconfig** 配置软件包。

    启用 SnowFlake 软件包，并配置使能测试例程（snowflake_sample），如下所示：

```shell
RT-Thread online packages
	tools packages  --->
		[*] Snowflake algorithm is a distributed ID generation algorithm
		[*]   Enable snowflake samples 
              Version (latest)  --->
```

- 使用 `pkgs --update` 命令下载软件包

## 运行示例

- 调用 `snowflake_sample` 函数或使用 `Finsh` 组件运行程序。
