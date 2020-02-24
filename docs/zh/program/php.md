# PHP

PHP是一种跨平台[开源](https://github.com/php/php-src)语言，尤其适合Web开发，快速、灵活和实用是PHP最重要的特点。PHP自1995年由Lerdorf创建以来，在全球得到了非常广泛的应用。

在2000年5月22日，以Zend Engine 1.0为基础的PHP 4正式发布，2004年7月13日则发布了PHP 5，PHP 5则使用了第二代的Zend Engine。PHP包含了许多新特色:完全实现面向对象、引入PDO、以及许多性能方面的改进。目前PHP5.X仍然是应用非常广泛的一个版本。


默认读者已具备简单C语言功底，PHP功底，本篇用于记录学习及从编程语言本身实现上了解学习PHP，版本为PHP7


```shell
# 1. 下载源代码并解压
wget https://github.com/php/php-src/archive/php-7.4.3.tar.gz
tar -zxvf php-7.4.3.tar.gz
# 2. 创建一个docker环境
docker run -itd --privileged --name php-src -v $PWD:/app  centos:7  /usr/sbin/init
docker exec -it php-src /bin/bash
# 3. 构建源码编译环境
set -ex \
  && curl -o /etc/yum.repos.d/CentOS-Base.repo http://mirrors.aliyun.com/repo/Centos-7.repo \
  && rpm -Uvh http://nginx.org/packages/centos/7/noarch/RPMS/nginx-release-centos-7-0.el7.ngx.noarch.rpm \
  && yum makecache \
  && yum install -y make cmake gcc gcc-c++ autoconf automake libpng-devel libjpeg-devel zlib libxml2-devel ncurses-devel bison libtool-ltdl-devel libiconv libmcrypt mhash mcrypt pcre-devel openssl-devel freetype-devel libcurl-devel nginx
# 4. 编译源码
set -ex  \
  && cd /root \
  && ./configure --prefix=/root --enable-fpm \
  && make && make install
```

通过以上命令集大致搭建一下所需学习环境，也可以根据需要下载[Understand](https://blog.csdn.net/weixin_41143631/article/details/83351401)，[Source Insight](https://www.sourceinsight.com)等一些代码辅助分析工具


## 源码整体框架
<img :src="$withBase('/program/runtime/program-php-01.png')" alt="foo">

PHP7核心源码主要围绕

- **ext** : 官方扩展目录，可以用C/C++定义自己的功能，通过扩展嵌入到PHP中，灵活的扩展能力使得PHP拥有了大量、丰富的第三方组件，这些扩展很好的补充了PHP的功能、特性，使得PHP在web开发中得以大展身手。ext目录下有一个standard扩展，这个扩展提供了大量被大家所熟知的PHP函数：sleep()、usleep()、htmlspecialchars()、md5()、strtoupper()、substr()、array_merge()等等
- **main** : 最为核心的文件，实现PHP的基本设施，是SAPI层和Zend层的黏合剂，起到了承上启下的作用，承上，极细SAPI的请求，分析要执行的脚本文件和参数；启下，调用Zend引擎之前，完成必要的初始化等工作
- **spai** : 它有标准的输入、输出，而SAPI是PHP的接入层，它接收用户的请求，然后调用PHP内核提供的一些接口完成PHP脚本的执行，所以严格意义上讲SAPI并不算PHP内核的一部分
- **TSRM** : 线程安全资源管理器，线程安全机制主要为了保证共享资源的安全，PHP的线程安全机制简洁直观--再多线程环境下，为每个线程提供独立的全局变量副本。具体实施是通过TSRM为每个线程分配（分配钱加锁）一个独立ID（自增）作为当前线程的全局变量内存区索引，在以后的全局变量访问中，实现线程之间的完全独立
- **Zend** : Zend 引擎的实现目录。包括词法语法解析，OPCODE，提供语言运行环境
  - 编译器： 负责将PHP代码编译为抽象语法树，然后进一步编译为可执行的opcodes，这个过程相当于GCC的工作，编译器是一个语言实现的基础
  - 执行器： 负责执行编译器输出的opcodes，也就是执行PHP脚本中编写的代码逻辑

## 执行原理概述

在PHP7中，源代码首先进行`词法分析`,将源代码切割为多个字符串但愿，分割后的字符串称为token，而一个一个独立的token是无法表达完整语意的，需要经过语法分析阶段，将token转换为抽象语法树`AST`，之后，抽象语法树被转换为机器指令执行，在PHP中这些指令称为opcode

1. 词法分析将PHP代码转换为有意义的token，该步骤的词法分析器使用[Re2c](http://re2c.org/)实现。
2. 语法分析将Token和符合文法规则的代码生成抽象语法树，语法分析器给予[Bison](https://www.gnu.org/software/bison/)实现。语法分析使用BNF(backus-NaurForm,巴克斯范式)来表法文法规则，Bison借助状态机、状态转移表和压栈、出栈等一系列操作，生成抽象语法树
2. 上不到抽象语法树生成对应的opcode,并被虚拟机执行，指令对应着相应的handler(处理函数)。当虚拟机调用opcode会找到opcode背后的处理函数，执行真正的处理。以常见的echo语句为例，其对应的的opcode便是[ZEND_ECHO](https://github.com/php/php-src/blob/a66c60cce3cd8878284fb39388080cfb6bac8ff5/Zend/zend_vm_opcodes.h#L215)
3. 抽象语法树转换为opcodes,PHP解释执行opcodes

## Zend 虚拟机

编程语言的虚拟机是一种可以运行中间语言的程序，中间语言是抽象出的指令集，由原生语言编译而成，作为虚拟机执行阶段的输入，很多语言都实现了自己的虚拟机，Java、C#和lua，PHP也有自己的虚拟机，称为Zend虚拟机

PHP7完成基本的准备工作后，会启动Zend引擎，加载注册的扩展模块，然后读取独赢的脚本文件，Zend引擎会对文件进行词法和语法分析，生成AST，接着AST被编译成opode，如果开启了opcache，编译的环节会被跳过从opcache中直接读取opcode进行执行，在PHP中，进行词法和语法分析，生成AST，然后编译成opcode及被执行均有Zend虚拟机完成

Zend 虚拟机主要分为解释层，中间数据层和执行层

<img :src="$withBase('/program/runtime/program-php-02.png')" alt="foo">

1. **解释层**： 这一层主要负责对PHP代码进行语法和语法分析，生成对应的AST；另一个工作就是对AST进行编译，生成符号表和指令集
2. **中间数据层**： 这一层主要包含了虚拟机的核心部分--执行栈道维护、指令集和符号表的存储，而这些事执行引擎调度执行的基础
3. **执行层**：这一层是执行指令集的引擎，负责最终执行并生成记过，这一层实现了大量的底层函数

### 符号表
符号表是编译程序在编译过程中用来记录源程序中各种名字的特性信息，所以也称为**名字特性表**，名字一般包含程序名、过程名、函数名、用户定义类型名、变量名、常量名、枚举值名、标号名等。特性信息指的是名字的种类、类型、维数、参数个数、数值及目标地址等
1. 协助进行语义检查、比如检查一个名字的引用和之前的申明是否相符
2. 协助中间代码生成，最重要的是在目标代码生成阶段，当需要为名字分配地址时。符号表中的信息是地址分配的主要依据

符号表一般有3种构造和处理方法，分别是线性查找、二叉树hash技术，其中线性查找法是最简单的，按照符号出现的顺序填表，每次查找从第一个位置开始顺序查找。效率表较低；二叉树实现了对半查找。在一定程度上提高了效率；效率最高的方法是通过hash技术实现符号表

### 指令

Zend虚拟机的指令称为opline,每条指令对应一个opcode。PHP代码在编译后生成opline，Zend虚拟机根据不同的opline完成PHP代码的执行，opline由操作指令、操作数和返回值组成，与机器指令非常类似

#### opcode

opcode有时候被称为所谓的字节码，是被软件解释器解释执行的指令集，这些软件指令集通常会提供一些比对应硬件指令集更高级的数据类型和操作，Zend虚拟机有很多opcode，对应可以做非常多事情，并且随着PHP的发展，opcode也越来越多，意味着PHP可以做越来越多的事情。所有的opcode都在PHP的源代码文件[Zend/zend_vm_opcodes.h](https://github.com/php/php-src/blob/a66c60cce3cd8878284fb39388080cfb6bac8ff5/Zend/zend_vm_opcodes.h)种定义

#### 操作数

op1和op2都是操作数，但不一定全部使用，也就是说，每个opcode对应的handler最多可以使用两个操作数（也可以总使用其中一个，或者都不使用）。每个操作数都可以列结尾函数的参数，返回值result是hanlder函数对操作数op1和op2计算后的结果


## 生命周期

PHP7有多种模式运行，比如常用的CLI模式、FPM模式、以及CGI模式、embed模式、Apache2Handler模式、litespeed模式等

### SAPI

SAPI（server application programimginterface，服务端应用编程接口）相当于PHP外部环境等代理服务器，CLI和FPM都是基于SAPI的实现，都定义了sapi_module_struct结构

#### CLI模式
CLI（Command line interface）即命令行借口，该模块主要用于PHP的外壳应用开发，在CLI模式下，PHP的执行过程主要分为5大阶段，这五个阶段分别对应

1. php_module_startup 模块初始化阶段
2. php_request_startup 请求初始化阶段
3. php_execute_script 执行阶段
4. php_request_shutdown 请求关闭阶段
5. php_module_shutown 模块关闭阶段

#### FPM模式

FPM（FastCGI Process Manager）是一个FastCGI进程管理器，提供了更好的PHP进程管理方式，可以有效控制内存和进程，支持平滑重启PHP以及重载PHP配置，与CLI模式一样FPM模式的生命周期也有5个阶段，但是又与CLI模式不同，因为FPM是常驻内存的进程，所以其模块初始化只做一次，便进入循环，而模块关闭在进程退出时也只做一次

1. php_module_startup 加载所有模块
2. 进入循环，嗲用fcgi_accept_request十几调用的是accept，阻塞等待请求，如果有请求进来，会被唤起，进入php_request_startup，初始化请求。为防止多个进程对accept进行抢占，出现`惊群`情况，增加了锁机制
3. 进入php_execute_script，对脚本执行编译
4. 调用php_request_shutdown关闭请求，继续进入循环
5. 如果进程退出，调用php_module_shutdown关闭模块
6. 如果请求次数大于max_requests,则跳转5

::: tip
在Linux 2.6内核上，阻塞版本的accept系统调用已经不存在`惊群`了
:::

PHPfpm 是多进程的服务，其中一个master进程（管理工作）和多个worker进程（处理数据请求）,一个web请求，nginx会根据服务器的CPU内核数设置worker的进程数，而PHP-FPM的进程有三种设置方式。static、dynamic和ondemand

Client通过HTTP方式请求Nginx,请求由nginx的worker进行处理，专程对应的FastCGI，请求FPM，accept由FPM的worker进程处理，执行完毕再返回给nginx,nginx再一步返回给Client

1. **static**：始终会保持一个固定数量的子进程，这个数量由pm.max_children定义
2. **dynamic**：子进程的数量是动态变化，启动时会生成固定数量的子进程，可以理解成最小子进程数，通过pm.start_servers控制，而最大子进程数则由pm.max_children控制，子进程数会在pm.start_servers~pm.max_children范围内变化，另外，闲置的子进程数还可以由pm.min_spare_servers和pm.max_spare_servers两个配置参数控制。欢聚换说，闲置的子进程也可以有最小数目和最大数目，而如果闲置的子进程超过了pm.max_spare_servers,则会被杀掉
3. **ondemand** ：把内存放在第一位，每个闲置进程在持续闲置了pm.orocess_idle_timeout秒后就会被杀掉，有了这个模式，到了服务器低峰期，内存自然会降下来，如果服务器长时间没有请求，就只会有一个PHP-FPM主进程，当然其弊端是，遇到高峰期或者pm.process_idle_timeout的值太小的话，无法避免服务器频繁创建进程的问题


Worker创建完成后，对请求的处理工作都会由worker进程进行，而master进程负责对worker进程的监控和管理，比如php-fpm reload和php-fpm stop分别用来重新加载和停止FPM，这部分工作是通过信号机制进行的，比如执行reload命令，对主进程发送了SIGUSR2信号

1. 对于SIGCHLD信号，该信号是由worker推出时发送的，master进程收到这个信号后调用fpm_children_bury函数对worker进程进行善后，同时调用fpm_children_make函数按照不同模式启动worker进程
2. 对于SIGUSR1信号，调用的是fpm_log_open函数，重新打开日志文件，然后fpm_pctl_kill_all杀掉worker进程，这时候又会收到SIGCHILD，进行步骤1
3. 对于SIGINT、SIGTERM、SIGQUIT和SIGUSR2信号，调用的都是fpm_pctl函数，该函数有两个参数，一个表示状态值。一个表示操作类型

::: tip
在大流量请求的情况下，切分日志时，会向php-fpm发送SIGUSR1信号，此时会有批量的worker进程被杀死，在重启完毕前，worker的进程数会瞬间变少，这时候会出现请求响应变慢的请求
:::

#### CGI模式

CGI（Common Gateway Interface）即通用网关接口，通俗的讲CGI就是将web服务器和PHP执行程序连接起来，把接受的指令传递给PHP执行，在把PHP执行的结果返回给WEB服务器

对于每一个用户请求，都会先创建CGI的子进程，然后处理请求，处理完成后结束这个子进程，这就是fork-and-execute模式，用户请求数量非常多会大量挤占系统的资源（内存、CPU时间等），造成效率低下，所以对于采用CGI模式的服务器，有多少连接请求，就会有多少CGI子进程，子进程反复加载也是导致CGI性能低下的原因，这也是FastCGI出现的原理

#### Embed 模式

PHP提供了一个Embed SAPI，也就是说，PHP允许在C/C++语言种调用PHP/ZE提供的函数，编译时增加--enable-embed生成，该模块对外提供了两个API，即php_embed_init和php_embed_shutdown，php_embed_ini用于完成模块初始化和请求初始化，php_embed_shutdown用于完成请求关闭和模块关闭工作

#### PHPDBFG模式

PHPDBG是一个PHP的SAPI模块，可以在不修改代码和不影响性能的情况下控制PHP的运行环境，PHPDBG的目标是成为一个轻量级，强大，易用的PHP调试平台，从PHP5.6开始集成

PHPDBG提供了类似GDB的功能，支持单步调试，可以灵活的打断点，可以查看类方法、函数、文件的行、内存地址、opcode等，可直接调用PHP的eval，另外还支持远程debug

```phpdbg
prompt> exec ./test.php
prompt> b func#2
prompt> r
prompt> info break
```

## 内存管理

zend针对内存的操作封装了一层，用于替换直接的内存操作：malloc、free等，实现了更高效率的内存利用，其实现主要参考了tcmalloc的设计。

源码中emalloc、efree、estrdup等等就是内存池的操作。

内存池是内核中最底层的内存操作，定义了三种粒度的内存块：chunk、page、slot，每个chunk的大小为2M，page大小为4KB，一个chunk被切割为512个page，而一个或若干个page被切割为多个slot，所以申请内存时按照不同的申请大小决定具体的分配策略：

- **Huge(chunk)**: 申请内存大于2M，直接调用系统分配，分配若干个chunk
- **Large(page)**: 申请内存大于3092B(3/4 page_size)，小于2044KB(511 page_size)，分配若干个page
- **Small(slot)**: 申请内存小于等于3092B(3/4 page_size)，内存池提前定义好了30种同等大小的内存(8,16,24,32，...3072)，他们分配在不同的page上(不同大小的内存可能会分配在多个连续的page)，申请内存时直接在对应page上查找可用位置


## 垃圾回收
为了解决循环引用问题，PHP引入了垃圾回收机制，PHP7垃圾回收的实现主要包括`zend_gc.h`和`zend_gc.c`中

### 垃圾的产生
前面已经介绍过PHP变量的内存管理，即引用计数机制，当变量赋值、传递时并不会直接硬拷贝，而是增加value的引用数，unset、return等释放变量时再减掉引用数，减掉后如果发现refcount变为0则直接释放value，这是变量的基本gc过程，PHP正是通过这个机制实现的自动垃圾回收，但是有一种情况是这个机制无法解决的，从而因变量无法回收导致内存始终得不到释放，这种情况就是循环引用，简单的描述就是变量的内部成员引用了变量自身，比如数组中的某个元素指向了数组，这样数组的引用计数中就有一个来自自身成员，试图释放数组时因为其refcount仍然大于0而得不到释放，而实际上已经没有任何外部引用了，这种变量不可能再被使用，所以PHP引入了另外一个机制用来处理变量循环引用的问题。

下面看一个数组循环引用的例子：
```php
$a = [1];
$a[] = &$a;

unset($a);
```
`unset($a)`之前引用关系

可以看到，unset($a)之后由于数组中有子元素指向$a，所以refcount = 1，此时是无法通过正常的gc机制回收的，但是$a已经已经没有任何外部引用了，所以这种变量就是垃圾，垃圾回收器要处理的就是这种情况，这里明确两个准则：

1. 如果一个变量value的refcount减少到0， 那么此value可以被释放掉，不属于垃圾
2. 如果一个变量value的refcount减少之后大于0，那么此zval还不能被释放，此zval可能成为一个垃圾

针对第一个情况GC不会处理，只有第二种情况GC才会将变量收集起来。另外变量是否加入垃圾检查buffer并不是根据zval的类型判断的，而是与前面介绍的是否用到引用计数一样通过zval.u1.type_flag记录的，只有包含IS_TYPE_COLLECTABLE的变量才会被GC收集。

目前垃圾只会出现在array、object两种类型中，数组的情况上面已经介绍了，object的情况则是成员属性引用对象本身导致的，其它类型不会出现这种变量中的成员引用变量自身的情况，所以垃圾回收只会处理这两种类型的变量。

```c
#define IS_TYPE_COLLECTABLE

|     type       | collectable |
+----------------+-------------+
|simple types    |             |
|string          |             |
|interned string |             |
|array           |      Y      |
|immutable array |             |
|object          |      Y      |
|resource        |             |
|reference       |             |
```

### 回收过程

如果当变量的refcount减少后大于0，PHP并不会立即进行对这个变量进行垃圾鉴定，而是放入一个缓冲buffer中，等这个buffer满了以后(10000个值)再统一进行处理，加入buffer的是变量zend_value的zend_refcounted_h:

```c {2}
typedef struct _zend_refcounted_h {
    uint32_t         refcount; //记录zend_value的引用数
    union {
        struct {
            zend_uchar    type,  //zend_value的类型,与zval.u1.type一致
            zend_uchar    flags, 
            uint16_t      gc_info //GC信息，垃圾回收的过程会用到
        } v;
        uint32_t type_info;
    } u;
} zend_refcounted_h;
```

一个变量只能加入一次buffer，为了防止重复加入，变量加入后会把zend_refcounted_h.gc_info置为GC_PURPLE，即标为紫色，下次refcount减少时如果发现已经加入过了则不再重复插入。垃圾缓存区是一个双向链表，等到缓存区满了以后则启动垃圾检查过程：遍历缓存区，再对当前变量的所有成员进行遍历，然后把成员的refcount减1(如果成员还包含子成员则也进行递归遍历，其实就是深度优先的遍历)，最后再检查当前变量的引用，如果减为了0则为垃圾。这个算法的原理很简单，垃圾是由于成员引用自身导致的，那么就对所有的成员减一遍引用，结果如果发现变量本身refcount变为了0则就表明其引用全部来自自身成员。具体的过程如下：

1. 从buffer链表的roots开始遍历，把当前value标为灰色(zend_refcounted_h.gc_info置为GC_GREY)，然后对当前value的成员进行深度优先遍历，把成员value的refcount减1，并且也标为灰色；
2. 重复遍历buffer链表，检查当前value引用是否为0，为0则表示确实是垃圾，把它标为白色(GC_WHITE)，如果不为0则排除了引用全部来自自身成员的可能，表示还有外部的引用，并不是垃圾，这时候因为步骤(1)对成员进行了refcount减1操作，需要再还原回去，对所有成员进行深度遍历，把成员refcount加1，同时标为黑色；
3. 再次遍历buffer链表，将非GC_WHITE的节点从roots链表中删除，最终roots链表中全部为真正的垃圾，最后将这些垃圾清除。

### 垃圾收集的内部实现

接下来我们简单看下垃圾回收的内部实现，垃圾收集器的全局数据结构：

```c
typedef struct _zend_gc_globals {
    zend_bool         gc_enabled; //是否启用gc
    zend_bool         gc_active;  //是否在垃圾检查过程中
    zend_bool         gc_full;    //缓存区是否已满

    gc_root_buffer   *buf;   //启动时分配的用于保存可能垃圾的缓存区
    gc_root_buffer    roots; //指向buf中最新加入的一个可能垃圾
    gc_root_buffer   *unused;//指向buf中没有使用的buffer
    gc_root_buffer   *first_unused; //指向buf中第一个没有使用的buffer
    gc_root_buffer   *last_unused; //指向buf尾部

    gc_root_buffer    to_free;  //待释放的垃圾
    gc_root_buffer   *next_to_free;

    uint32_t gc_runs;   //统计gc运行次数
    uint32_t collected; //统计已回收的垃圾数
} zend_gc_globals;

typedef struct _gc_root_buffer {
    zend_refcounted          *ref; //每个zend_value的gc信息
    struct _gc_root_buffer   *next;
    struct _gc_root_buffer   *prev;
    uint32_t                 refcount;
} gc_root_buffer;
```

zend_gc_globals是垃圾回收过程中主要用到的一个结构，用来保存垃圾回收器的所有信息，比如垃圾缓存区；gc_root_buffer用来保存每个可能是垃圾的变量，它实际就是整个垃圾收集buffer链表的元素，当GC收集一个变量时会创建一个gc_root_buffer，插入链表。

zend_gc_globals这个结构中有几个关键成员：

1. buf: 前面已经说过，当refcount减少后如果大于0那么就会将这个变量的value加入GC的垃圾缓存区，buf就是这个缓存区，它实际是一块连续的内存，在GC初始化时一次性分配了10001个gc_root_buffer，插入变量时直接从buf中取出可用节点；
2. roots: 垃圾缓存链表的头部，启动GC检查的过程就是从roots开始遍历的；
3. first_unused: 指向buf中第一个可用的节点，初始化时这个值为1而不是0，因为第一个gc_root_buffer保留没有使用，有元素插入roots时如果first_unused还没有到达buf的尾部则返回first_unused给最新的元素，然后first_unused++，直到last_unused，比如现在已经加入了2个可能的垃圾变量，则对应的结构：
4. last_unused: 与first_unused类似，指向buf末尾
4. unused: GC收集变量时会依次从buf中获取可用的gc_root_buffer，这种情况直接取first_unused即可，但是有些变量加入垃圾缓存区之后其refcount又减为0了，这种情况就需要从roots中删掉，因为它不可能是垃圾，这样就导致roots链表并不是像buf分配的那样是连续的，中间会出现一些开始加入后面又删除的节点，这些节点就通过unused串成一个单链表，unused指向链表尾部，下次有新的变量插入roots时优先使用unused的这些节点，其次才是first_unused的，举个例子

```php
//示例1：
$a = array(); //$a ->  zend_array(refcount=1)
$b = $a;      //$a ->  zend_array(refcount=2)
              //$b ->

unset($b);    //此时zend_array(refcount=1)，因为refoucnt>0所以加入gc的垃圾缓存区：roots
unset($a);    //此时zend_array(refcount=0)且gc_info为GC_PURPLE，则从roots链表中删掉
```



## 扩展的构成及编译

### 扩展的构成
扩展首先需要创建一个`zend_module_entry`结构，这个变量必须是全局变量，且变量名必须是：`扩展名称_module_entry`，内核通过这个结构得到这个扩展都提供了哪些功能，换句话说，一个扩展可以只包含一个`zend_module_entry`结构，相当于定义了一个什么功能都没有的扩展。

```c
//zend_modules.h
struct _zend_module_entry {
    unsigned short size; //sizeof(zend_module_entry)
    unsigned int zend_api; //ZEND_MODULE_API_NO
    unsigned char zend_debug; //是否开启debug
    unsigned char zts; //是否开启线程安全
    const struct _zend_ini_entry *ini_entry;
    const struct _zend_module_dep *deps;
    const char *name; //扩展名称，不能重复
    const struct _zend_function_entry *functions; //扩展提供的内部函数列表
    int (*module_startup_func)(INIT_FUNC_ARGS); //扩展初始化回调函数，PHP_MINIT_FUNCTION或ZEND_MINIT_FUNCTION定义的函数
    int (*module_shutdown_func)(SHUTDOWN_FUNC_ARGS); //扩展关闭时回调函数
    int (*request_startup_func)(INIT_FUNC_ARGS); //请求开始前回调函数
    int (*request_shutdown_func)(SHUTDOWN_FUNC_ARGS); //请求结束时回调函数
    void (*info_func)(ZEND_MODULE_INFO_FUNC_ARGS); //php_info展示的扩展信息处理函数
    const char *version; //版本
    ...
    unsigned char type;
    void *handle;
    int module_number; //扩展的唯一编号
    const char *build_id;
};
```
这个结构包含很多成员，但并不是所有的都需要自己定义，经常用到的主要有下面几个：
* __name:__ 扩展名称，不能重复
* __functions:__ 扩展定义的内部函数entry
* __module_startup_func:__ PHP在模块初始化时回调的hook函数，可以使扩展介入module startup阶段
* __module_shutdown_func:__ 在模块关闭阶段回调的函数
* __request_startup_func:__ 在请求初始化阶段回调的函数
* __request_shutdown_func:__ 在请求结束阶段回调的函数
* __info_func:__ php_info()函数时调用，用于展示一些配置、运行信息
* __version:__ 扩展版本

除了上面这些需要手动设置的成员，其它部分可以通过`STANDARD_MODULE_HEADER`、`STANDARD_MODULE_PROPERTIES`宏统一设置，扩展提供的内部函数及四个执行阶段的钩子函数是扩展最常用到的部分，几乎所有的扩展都是基于这两部分实现的。有了这个结构还需要提供一个接口来获取这个结构变量，这个接口是统一的，扩展中通过`ZEND_GET_MODULE(extension_name)`完成这个接口的定义:
```
//zend_API.h
#define ZEND_GET_MODULE(name) \
    BEGIN_EXTERN_C()\
    ZEND_DLEXPORT zend_module_entry *get_module(void) { return &name##_module_entry; }\
    END_EXTERN_C()
```
展开后可以看到，实际就是定义了一个get_module()函数，返回扩展zend_module_entry结构的地址，这就是为什么这个结构的变量名必须是`扩展名称_module_entry`这种格式的原因。

有了扩展的zend_module_entry结构以及获取这个结构的接口一个合格的扩展就编写完成了，只是这个扩展目前还什么都干不了：
```c
#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"

zend_module_entry mytest_module_entry = {
    STANDARD_MODULE_HEADER,
    "mytest",
    NULL, //mytest_functions,
    NULL, //PHP_MINIT(mytest),
    NULL, //PHP_MSHUTDOWN(mytest),
    NULL, //PHP_RINIT(mytest),
    NULL, //PHP_RSHUTDOWN(mytest),
    NULL, //PHP_MINFO(mytest),
    "1.0.0",
    STANDARD_MODULE_PROPERTIES
};

ZEND_GET_MODULE(mytest)
```
编译、安装后执行`php -m`就可以看到my_test这个扩展了。

### 编译工具
PHP提供了几个脚本工具用于简化扩展的实现：ext_skel、phpize、php-config，后面两个脚本主要配合autoconf、automake生成Makefile。在介绍这几个工具之前，我们先看下PHP安装后的目录结构，因为很多脚本、配置都放置在安装后的目录中，比如PHP的安装路径为：/usr/local/php7，则此目录的主要结构：
```c
|---php7
|   |---bin //php编译生成的二进制程序目录
|       |---php //cli模式的php
|       |---phpize      
|       |---php-config
|       |---...
|   |---etc     //一些sapi的配置    
|   |---include //php源码的头文件
|       |---php
|           |---main    //PHP中的头文件
|           |---Zend    //Zend头文件
|           |---TSRM    //TSRM头文件
|           |---ext     //扩展头文件
|           |---sapi    //SAPI头文件
|           |---include
|   |---lib //依赖的so库
|       |---php
|           |---extensions  //扩展so保存目录
|           |---build       //编译时的工具、m4配置等，编写扩展是会用到
|               |---acinclude.m4    //PHP自定义的autoconf宏
|               |---libtool.m4      //libtool定义的autoconf宏，acinclude.m4、libtool.m4会被合成aclocal.m4
|               |---phpize.m4       //PHP核心configure.in配置
|               |---...
|           |---...
|   |---php
|   |---sbin //SAPI编译生成的二进制程序，php-fpm会放在这
|   |---var  //log、run日志
```

#### ext_skel
这个脚本位于PHP源码/ext目录下，它的作用是用来生成扩展的基本骨架，帮助开发者快速生成一个规范的扩展结构，可以通过以下命令生成一个扩展结构：
```c
./ext_skel --extname=扩展名称
```
执行完以后会在ext目录下新生成一个扩展目录，比如extname是mytest，则将生成以下文件：
```c
|---mytest 
|   |---config.m4     //autoconf规则的编译配置文件
|   |---config.w32    //windows环境的配置
|   |---CREDITS
|   |---EXPERIMENTAL
|   |---include       //依赖库的include头文件，可以不用
|   |---mytest.c      //扩展源码
|   |---php_mytest.h  //头文件
|   |---mytest.php    //用于在PHP中测试扩展是否可用，可以不用
|   |---tests         //测试用例，执行make test时将执行、验证这些用例
|       |---001.phpt
```
这个脚本主要生成了编译需要的配置以及扩展的基本结构，初步生成的这个扩展可以成功的编译、安装、使用，实际开发中我们可以使用这个脚本生成一个基本结构，然后根据具体的需要逐步完善。
### php-config
这个脚本为PHP源码中的/script/php-config.in，PHP安装后被移到安装路径的/bin目录下，并重命名为php-config，这个脚本主要是获取PHP的安装信息的，主要有：
* __PHP安装路径__
* __PHP版本__
* __PHP源码的头文件目录：__ main、Zend、ext、TSRM中的头文件，编写扩展时会用到这些头文件，这些头文件保存在PHP安装位置/include/php目录下
* __LDFLAGS：__ 外部库路径，比如：`-L/usr/bib -L/usr/local/lib`
* __依赖的外部库：__ 告诉编译器要链接哪些文件，`-lcrypt   -lresolv -lcrypt`等等
* __扩展存放目录：__ 扩展.so保存位置，安装扩展make install时将安装到此路径下
* __编译的SAPI：__ 如cli、fpm、cgi等
* __PHP编译参数：__ 执行./configure时带的参数
* ...

这个脚本在编译扩展时会用到，执行`./configure --with-php-config=xxx`生成Makefile时作为参数传入即可，它的作用是提供给configure.in获取上面几个配置，生成Makefile。

#### phpize
这个脚本主要是操作复杂的autoconf/automake/autoheader/autolocal等系列命令，用于生成configure文件，GNU auto系列的工具众多，这里简单介绍下基本的使用：

__(1)autoscan：__ 在源码目录下扫描，生成configure.scan，然后把这个文件重名为为configure.in，可以在这个文件里对依赖的文件、库进行检查以及配置一些编译参数等。

__(2)aclocal：__ automake中有很多宏可以在configure.in或其它.m4配置中使用，这些宏必须定义在aclocal.m4中，否则将无法被autoconf识别，aclocal可以根据configure.in自动生成aclocal.m4，另外，autoconf提供的特性不可能满足所有的需求，所以autoconf还支持自定义宏，用户可以在acinclude.m4中定义自己的宏，然后在执行aclocal生成aclocal.m4时也会将acinclude.m4加载进去。

__(3)autoheader：__ 它可以根据configure.in、aclocal.m4生成一个C语言"define"声明的头文件模板(config.h.in)供configure执行时使用，比如很多程序会通过configure提供一些enable/disable的参数，然后根据不同的参数决定是否开启某些选项，这种就可以根据编译参数的值生成一个define宏，比如：`--enabled-xxx`生成`#define ENABLED_XXX 1`，否则默认生成`#define ENABLED_XXX 0`，代码里直接使用这个宏即可。比如configure.in文件内容如下：
```sh
AC_PREREQ([2.63])
AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS])

AC_CONFIG_HEADERS([config.h])

AC_ARG_ENABLE(xxx, "--enable-xxx if enable xxx",[
    AC_DEFINE([ENABLED_XXX], [1], [enabled xxx])
],
[
    AC_DEFINE([ENABLED_XXX], [0], [disabled xxx])
])

AC_OUTPUT
```
执行autoheader后将生成一个config.h.in的文件，里面包含`#undef ENABLED_XXX`，最终执行`./configure --enable-xxx`后将生成一个config.h文件，包含`#define ENABLED_XXX 1`。

__(4)autoconf：__ 将configure.in中的宏展开生成configure、config.h，此过程会用到aclocal.m4中定义的宏。

__(5)automake：__ 将Makefile.am中定义的结构建立Makefile.in，然后configure脚本将生成的Makefile.in文件转换为Makefile。


编写PHP扩展时并不需要操作上面全部的步骤，PHP提供了两个编辑好的配置：configure.in、acinclude.m4，这两个配置是从PHP安装路径/lib/php/build目录下的phpize.m4、acinclude.m4复制生成的，其中configure.in中定义了一些PHP内核相关的配置检查项，另外这个文件会include每个扩展各自的配置:config.m4，所以编写扩展时我们只需要在config.m4中定义扩展自己的配置就可以了，不需要关心依赖的PHP内核相关的配置，在扩展所在目录下执行phpize就可以生成扩展的configure、config.h文件了。

configure.in(phpize.m4)：
```sh
AC_PREREQ(2.59)
AC_INIT(config.m4)
...
#--with-php-config参数
PHP_ARG_WITH(php-config,,
[  --with-php-config=PATH  Path to php-config [php-config]], php-config, no)

PHP_CONFIG=$PHP_PHP_CONFIG
...
#加载扩展配置
sinclude(config.m4)
...
AC_CONFIG_HEADER(config.h)

AC_OUTPUT()
```
__phpize中的主要操作：__

__(1)phpize_check_configm4:__ 检查扩展的config.m4是否存在。

__(2)phpize_check_build_files:__ 检查php安装路径下的lib/php/build/，这个目录下包含PHP自定义的autoconf宏文件acinclude.m4以及libtool；检查扩展所在目录。

__(3)phpize_print_api_numbers:__ 输出PHP Api Version、Zend Module Api No、Zend Extension Api No信息。
```sh
phpize_get_api_numbers()
{
  # extracting API NOs:
  PHP_API_VERSION=`grep '#define PHP_API_VERSION' $includedir/main/php.h|$SED 's/#define PHP_API_VERSION//'`
  ZEND_MODULE_API_NO=`grep '#define ZEND_MODULE_API_NO' $includedir/Zend/zend_modules.h|$SED 's/#define ZEND_MODULE_API_NO//'`
  ZEND_EXTENSION_API_NO=`grep '#define ZEND_EXTENSION_API_NO' $includedir/Zend/zend_extensions.h|$SED 's/#define ZEND_EXTENSION_API_NO//'`
}
```
__(4)phpize_copy_files:__ 将PHP安装位置/lib/php/build目录下的mkdep.awk scan_makefile_in.awk shtool libtool.m4四个文件拷到扩展的build目录下，然后将acinclude.m4 Makefile.global config.sub config.guess ltmain.sh run-tests*.php文件拷到扩展根目录，最后将acinclude.m4、build/libtool.m4合并到扩展目录下的aclocal.m4文件中。
```sh
phpize_copy_files()
{
  test -d build || mkdir build

  (cd "$phpdir" && cp $FILES_BUILD "$builddir"/build)
  (cd "$phpdir" && cp $FILES "$builddir")
  #acinclude.m4、libtool.m4合并到aclocal.m4
  (cd "$builddir" && cat acinclude.m4 ./build/libtool.m4 > aclocal.m4) 
}
```
__(5)phpize_replace_prefix:__ 将PHP安装位置/lib/php/build/phpize.m4拷贝到扩展目录下，将文件中的prefix替换为PHP安装路径，然后重命名为configure.in。
```sh
phpize_replace_prefix()
{
  $SED \
  -e "s#/usr/local/php7#$prefix#" \
  < "$phpdir/phpize.m4" > configure.in
}
```
__(6)phpize_check_shtool:__ 检查/build/shtool。

__(7)phpize_check_autotools:__ 检查autoconf、autoheader。

__(8)phpize_autotools__ 执行autoconf生成configure，然后再执行autoheader生成config.h。

### 编写扩展的基本步骤
编写一个PHP扩展主要分为以下几步：
* 通过ext目录下ext_skel脚本生成扩展的基本框架：`./ext_skel --extname`；
* 修改config.m4配置：设置编译配置参数、设置扩展的源文件、依赖库/函数检查等等；
* 编写扩展要实现的功能：按照PHP扩展的格式以及PHP提供的API编写功能；
* 生成configure：扩展编写完成后执行phpize脚本生成configure及其它配置文件；
* 编译&安装：./configure、make、make install，然后将扩展的.so路径添加到php.ini中。

最后就可以在PHP中使用这个扩展了。

### config.m4
config.m4是扩展的编译配置文件，它被include到configure.in文件中，最终被autoconf编译为configure，编写扩展时我们只需要在config.m4中修改配置即可，一个简单的扩展配置只需要包含以下内容：
```c
PHP_ARG_WITH(扩展名称, for mytest support,
Make sure that the comment is aligned:
[  --with-扩展名称             Include xxx support])

if test "$PHP_扩展名称" != "no"; then
    PHP_NEW_EXTENSION(扩展名称, 源码文件列表, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
```
PHP在acinclude.m4中基于autoconf/automake的宏封装了很多可以直接使用的宏，下面介绍几个比较常用的宏：

__(1)PHP_ARG_WITH(arg_name,check message,help info):__ 定义一个`--with-feature[=arg]`这样的编译参数，调用的是autoconf的AC_ARG_WITH，这个宏有5个参数，常用的是前三个，分别表示：参数名、执行./configure是展示信息、执行--help时展示信息，第4个参数为默认值，如果不定义默认为"no"，通过这个宏定义的参数可以在config.m4中通过`$PHP_参数名(大写)`访问，比如：
```sh
PHP_ARG_WITH(aaa, aaa-configure, help aa)

#后面通过$PHP_AAA就可以读取到--with-aaa=xxx设置的值了
```
__(2)PHP_ARG_ENABLE(arg_name,check message,help info):__ 定义一个`--enable-feature[=arg]`或`--disable-feature`参数，`--disable-feature`等价于`--enable-feature=no`，这个宏与PHP_ARG_WITH类似，通常情况下如果配置的参数需要额外的arg值会使用PHP_ARG_WITH，而如果不需要arg值，只用于开关配置则会使用PHP_ARG_ENABLE。

__(3)AC_MSG_CHECKING()/AC_MSG_RESULT()/AC_MSG_ERROR():__ ./configure时输出结果，其中error将会中断configure执行。

__(4)AC_DEFINE(variable, value, [description]):__ 定义一个宏，比如：`AC_DEFINE(IS_DEBUG, 1, [])`，执行autoheader时将在头文件中生成：`#define IS_DEBUG 1`。

__(5)PHP_ADD_INCLUDE(path):__ 添加include路径，即：`gcc -Iinclude_dir`，`#include "file";`将先在通过-I指定的目录下查找，扩展引用了外部库或者扩展下分了多个目录的情况下会用到这个宏。

__(6)PHP_CHECK_LIBRARY(library, function [, action-found [, action-not-found [, extra-libs]]]):__ 检查依赖的库中是否存在需要的function，action-found为存在时执行的动作，action-not-found为不存在时执行的动作，比如扩展里使用到线程pthread，检查pthread_create()，如果没找到则终止./configure执行：
```sh
PHP_CHECK_LIBRARY(pthread, pthread_create, [], [
    AC_MSG_ERROR([not find pthread_create() in lib pthread])
])
```
__(7)AC_CHECK_FUNC(function, [action-if-found], [action-if-not-found]):__ 检查函数是否存在。
__(8)PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $XXX_DIR/$PHP_LIBDIR, XXX_SHARED_LIBADD):__ 添加链接库。

__(9)PHP_NEW_EXTENSION(extname, sources [, shared [, sapi_class [, extra-cflags [, cxx [, zend_ext]]]]]):__ 注册一个扩展，添加扩展源文件，确定此扩展是动态库还是静态库，每个扩展的config.m4中都需要通过这个宏完成扩展的编译配置。

更多autoconf及PHP封装的宏大家可以在用到的时候再自行检索，同时ext目录下有大量的示例可供参考。
