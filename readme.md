基于CTP接口开发的交易平台，目前尚在开发中，可以实现行情订阅、下单等功能，供学习参考使用<br>
目前效果图如下，已经完成订阅实时期货行情，动态显示价格交易量等信息。<br>

### 使用
代码大部分采用c++编写，编译如下
~~~bash
mkdir build
cd build && cmake ..
make
~~~
编译好之后需要在项目根目录下新建config文件夹，并在该目录下新建config.txt文件。文件内容如下，其中investorid和password为模拟账号的账号和密码，第四行为下单时设置的滑点（最小交易单位的多少倍）。
~~~txt
9999
investorid
password
2
~~~


### 行情获取及存储
行情获取通过上期ctp行情接口回报，保存至本地数据库，这里使用的是mysql数据库。

### 前端显示
为了实时显示行情数据及后续自定义交易信号，判断进场时机，使用pyecharts和flask显示数据。代码位于src\tools\flask

~~~bash
python3 server.py
~~~
显示效果如下：

![image](https://github.com/zhouhy0903/ctp_trader/blob/master/doc/1.jpg)


