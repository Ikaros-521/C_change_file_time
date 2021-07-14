# 前言
由于看到一篇回答提到文件打开可能被发现的问题，所以有了本篇文章，用于解决t看文件后，修改文件访问时间等信息，达到不被发现的目的。那么话不多说，直接开始。
参考文章：
[Windows核心编程-CreateFile详解](https://blog.csdn.net/bxsec/article/details/76566011)
[Windows API](http://www.office-cn.net/t/api/index.html?web.htm)
[（C语言）修改文件时间程序（创建时间、修改时间、访问时间）](https://www.jianshu.com/p/9b7cf19b1886)
## 工程下载
码云 github
# 效果图
以**管理员权限**运行exe程序，输入文件绝对或相对路径，输入各个时间，回车即可。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210714104345264.gif#pic_center)

# 函数具体解析
## CreateFile
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210714104213290.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0lrYXJvc181MjE=,size_16,color_FFFFFF,t_70)
## SystemTimeToFileTime
![在这里插入图片描述](https://img-blog.csdnimg.cn/2021071410430157.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0lrYXJvc181MjE=,size_16,color_FFFFFF,t_70)
## LocalFileTimeToFileTime
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210714104541770.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0lrYXJvc181MjE=,size_16,color_FFFFFF,t_70)
## SetFileTime
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210714104604984.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0lrYXJvc181MjE=,size_16,color_FFFFFF,t_70)

