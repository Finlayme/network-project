### HTTP服务器实现原理
#### 前言：
+ *本项目用最简洁的语言，最轻松友好的方式，向你娓娓道来了一个http服务器的运行实现，简单易懂，彻底告别网上其他复杂冗余的程序，为了描述清楚知识点，我还无耻的抄了几篇别人的博客，哈哈～～*
#### 项目简介：
+ 实现一个http服务器，客户端通过浏览器发送请求，服务器接收并分析客户端的请求方法和资源，从而执行相应的逻辑处理，最终将客户请求的资源以 HTML 页面的形式呈现，并能进行差错处理。
#### 项目思路：
+ 首先实现两个主机不同进程间的通信，当服务器收到请求后，要进行分析请求方法，当方法确定后应该拿到请求的资源，接下来要根据资源是否存在执行相应的逻辑处理。
+ GET 方法：如果没有参数，进入非 cgi 模式运行；否则，进入 cgi 模式运行；只要是 POST 方法就一定要支持 cgi：直接进入
+ cgi 模式运行。
#### 项目特点：
1. 支持客户端/服务器模式，客户端能够使用 GET、POST 方法请求资源
2. 简单快速：客户向服务器请求服务时，只需传送请求方法和路径
3. 灵活：HTTP 允许传输任意类型的数据对象，正在传输的类型由 Content-Type 加以标记。
#### 项目具体实现
+ 主要流程为：服务器获得请求–>响应并处理请求–>返回结果。
完整的HTTP过渡到TCP实现客户端与服务器的交互过程
1. 当客户端执行网络请求的时候，从url中解析出url的主机名，并将主机地址转换成ip
2. 从url解析出服务器的所用端口号
3. 客户端用TCP连接服务器
4. 连接成功后 获取输出流，将数据以报文的形式传递给服务器
5. 当服务器接收到数据之后，进行判断和解析码，并回应一条响应报文
6. 客户端从输入流中获取报文，然后进行解析
7. 关闭网络连接

+ HTTP的特点


1. 支持客户端/服务器的模式
2. 简单快捷 客户向服务器发送请求服务时，只需要传送请求方法和路径，每种方法规定了客户与服务器联系的类型的不同，由于HTTP协议简单，使得HTTP服务器的规模小，因此通信速度很快.
3. 灵活  允许传送各种类型的数据,数据类型用Content-Type标记
4. 无连接：限制每次连接只处理一个请求，服务器处理完客户的请求，收到客户的应答后，随即断开连接，这种方式节省传输时间，请求应答机制会断开
5. 无状态  HTTP协议是无状态的协议，即对事务处理没有记忆功能

+ 关于URL

- 即统一资源定位符，每个网页都对应一个URL地址（俗称网址），具有全球唯一性。它包含的信息指出文件的位置以及浏览器应该怎么处理它。 一个完整的URL包括协议类型、主机类型、路径和文件名。 
http协议的URL格式： http: //host[:port][abs_path] ，http表示使用http协议来进行资源定位；host是主机域名；port是端口号，一般有默认的；abs_path代表资源的路径。 
这里我主要介绍项目中涉及的URL的两种格式—URL带参数和不带参数的。
![url解析](https://img-blog.csdn.net/20180912174431420?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5MzgwNTkw/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)
+ HTTP的请求与响应格式
![HTTP格式图](https://img-blog.csdn.net/20180912174333308?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5MzgwNTkw/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)
+ 响应报头中的状态码和状态码描述，例如：当请求的资源不存在时，会收到“404 NotFound”的页面，404就是状态码，“NotFound”就是状态码描述，即请求的文件不存在。
  - 实现支持GET和POST方法的小型http服务器
  GET方法：如果GET方法只是简单的请求一份资源,而不传递参数的话则由服务器直接将资源返回即可。如果GET方法的url中带有参数的话，则就要使用CGI模式进行处理。 
  POST方法：POST方法要使用CGI模式进行处理，POST的参数在消息中文中出现。
  使用GET方法使用的是带参数的url，传递的参数会使用?连接在资源后面POST方法使用的是不带参数的url 它的参数是通过http请求正文传递给服务器的，http的请求和响应模式  
+ 响应报头中的状态码和状态码描述，举个例子，当请求的资源不存在的时，会收到"404 NotFound"的页面，404就是状态码，"NotFound"就是状态码描述，既请求的文件不存在
  状态码表示响应类型
  
  状态码|技能|
  --|:--:|
  1××|保留
  2××|表示请求成功地接收
  3××|为完成请求客户需进一步细化请求
  4××|客户错误
  5××|服务器错误 

响应头的信息包括：服务程序名，通知客户请求的URL需要认证，请求的资源何时能使用

#### HTTP服务器实现框架
1. 面向链接：http协议是基于TCP通信协议，因此实现web服务器的第一步至少要能实现两个主机不同进程之间的TCP通信，并且需要解决高并发问题所以这里推荐使用多线程服务器来构建，每次创建出来一个新线程出来的时候将线程分离，然后让这个新线程去处理这个请求.但是我好像不太会epoll所以就没写多线程．．．
2. 分析出请求行: 当服务器接收到请求后，首先知道的是HTTP服务器版本号，和请求方法。web服务器是要支持cgi模式: 请求的方法不同，cgi可能也不同，我们实现的知识比较简单单的处理GET和POST方法
3. 判断cgi模式

    1.当我们判断出来是GET请求时候，并且url中没有参数的话，就用非CGI模式，非CGI模式处理//起来比较简单，首先解析出来请求路径，判断是不是合法资源，如果是就直接返回这个资源。

    2. 当是CGI模式处理请求的时候，我们要fork一个子进程，对子进程exec替换CGI程序，这个
过程中使用pipe进行父子进程之间的通信。所有需要的参数在exec之前，都将这些参数导出为环境变量，就算exec的话，子进程还是能够通过环境变量获取所需的参数。
+  响应客户端：此时我们已经知道了方法以及是否为cgi模式，然后开始读取URL，这里有一个细节非cgi模式 请求参数会跟在url当中，如果cgi模式的话，参数在消息正文中，然后我们读取到路径，判断路径当中资源是否存在，如果存在判断这个资源是一个目录，普通文件还是一个可执行程序

+ 这里分情况分析

1. 如果是cgi模式，直接进入cgi内部运行;只要是POST方法就需要支持cgi,直接进入cgi函数内部运行.
2.  如果是非cgi模式时一定是GET方法并且没有参数，此时进入wwwroot()函数内部即可，该函数会将所请求的资源以html的格式返回给浏览器.


+ 接下来是解释运行cgi模式，首先服务器要从浏览器读取参数，然后创建出来一个子进程去执行cgi部分的可执行资源，父进程通过环境变量的方式传递给子进程，子进程运行完成之后呢，将结果交给父进程，父进程再将数据输出给浏览器. 所以父进程在这个例子当中就向是一个中介，只进行参数和结果的转交实际上并不会执行任何资源，因此将子进程的输入输出文件描述符重定向，就可以让子进程直接与浏览器"联系".
![通信图](https://img-blog.csdn.net/20180912175657833?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5MzgwNTkw/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

+ 父进程做的事情
  
  1.创建两个管道，并关闭相应的文件描述符 
  2.POST方法：继续读取数据，直到读完POST的参数部分GET方法：直接从子进程读取结果
  3.将数据和方法全部交给子进程后等待子进程的结果
  + 子进程做的事情
  
  1.关闭管道适当的文件描述符
  2.对标准输入输出进行重定向
  3.通过环境变量传递参数
  4.进行exec程序替换
+ 关于数据库

+ 因为动态连接库太大，所以没有传，如果需要实现这个服务器，请读者自行下载，
 （[mysql对应的lib库下载地址](https://dev.mysql.com/downloads/mysql/)） 
    要注意的是你的笔记本的操作系统，不要下错了，下载完以后解压出来就好，注意位置，路径不对可能引入不到而报错
---
+ 一次完整的http请求的流程
![流程](https://img-blog.csdn.net/20180912180046844?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5MzgwNTkw/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

+ 附：

 
这里是我遇到的一些问题，粘出来，也可能是你遇到的问题： 
1. 本地环回测试ok，Linux下的浏览器测试也可以，但不能接外部的浏览器访问（没有设置桥接模式）嗯~要是在外部浏览器测试的话千万别忘记关闭防火墙 
2. 这个问题比较扯，在我显示html网页的时候，发现怎么都显示不出来，查了几遍代码，都对着，我很头疼，然后开始了漫长的调试，我没用gcc,我是直接打印法判断程序走到哪崩溃了，我还是发现都好好的，最后检查的时候发现html文件名，我多打了一个空格。。。。这个算是我遇到的第一个坎
3. 不能显示图片（这个问题是没有将所有发送的情况考虑完全，只考虑到目录、可执行程序，但没有考虑到如果请求的是一个路径明确的普通文件） 
解决：测试请求一个路径明确的test.html文件，加入调试信息 ，将问题定位在：如果请求的资源存在，应该如何处理。对于普通文件，找到后并回显给浏览器；如果是目录，应答的是默认页面；如果是可执行程序，执行后返回结果 
4. 能显示图片后，文字部分显示为乱码，这个问题是charset格式问题，后来改成了utf-8,问题解决
5. 在我加入电子书以后，我发现请求总是不成功，但是在本地可以打开电子书，这里我找了好久找到个合适的插件，就在我用插件后，我发现还是不成功，心灰意冷。。。。突然我想到以前返回的是html网页，现在我要返回的pdf格式啊，我就去把content-type改成返回pdf格式的了，在资源路径path，后面加判断，遇到pdf结尾的，就更改content-type,如此一来，大功告成。

+ 再一个，提醒一下各位，想在你虚拟机实现的朋友，lib库，自己在mysql官网上下载啊，不要从windows下载好往进拉，这样子容易出问题，看好你MySQL的版本，下准确，注意还有的同学下了windows的 ，我也是醉了

+ 有任何问题记得留言哦～，觉得好的话帮我点个星星吧，么么哒～
