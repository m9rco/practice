# IO

> 注：将所有看到的多路复用知识整合，彻底搞清楚Linux IO模式及 select、poll、epoll

在UNIX的世界中一切皆文件，文件本质上是一串二进制流。在数据交换过程中，需要对流进行数据的收发操作也就是I/O输入输出操作（Input/Output）。

由于程序和运行时数据在内存中驻留，由CPU的计算核心来执行，涉及到数据交换在磁盘、网络时也需要IO。

同步IO和异步IO，阻塞IO和非阻塞IO分别是什么，到底有什么区别？不同的人在不同的上下文下给出的答案是不同的。所以先限定一下本文的上下文。

## 概念

<center>
<img :src="$withBase('/os_cp/os/os-io-01.png')" alt="foo"> 
</center>

现在操作系统都是采用虚拟存储器，那么对32位操作系统而言，它的寻址空间（虚拟存储空间）为4G（2的32次方）。操作系统的核心是内核，独立于普通的应用程序，可以访问受保护的内存空间，也有访问底层硬件设备的所有权限。为了保证用户进程不能直接操作内核（kernel），保证内核的安全，操心系统将虚拟空间划分为两部分，一部分为内核空间，一部分为用户空间。针对linux操作系统而言，将最高的1G字节（从虚拟地址0xC0000000到0xFFFFFFFF），供内核使用，称为内核态，而将较低的3G字节（从虚拟地址0x00000000到0xBFFFFFFF），供各个进程使用，称为用户态。

当一个进程在执行用户自己的代码时处于用户运行态（用户态），此时特权级最低，为3级，是普通的用户进程运行的特权级，大部分用户直接面对的程序都是运行在用户态。Ring3状态不能访问Ring0的地址空间，包括代码和数据；当一个进程因为系统调用陷入内核代码中执行时处于内核运行态（内核态），此时特权级最高，为0级。执行的内核代码会使用当前进程的内核栈，每个进程都有自己的内核栈。

用户运行一个程序，该程序创建的进程开始时运行自己的代码，处于用户态。如果要执行文件操作、网络数据发送等操作必须通过write、send等系统调用，这些系统调用会调用内核的代码。进程会切换到Ring0，然后进入3G-4G中的内核地址空间去执行内核代码来完成相应的操作。内核态的进程执行完后又会切换到Ring3，回到用户态。这样，用户态的程序就不能随意操作内核地址空间，具有一定的安全保护作用。这说的保护模式是指通过内存页表操作等机制，保证进程间的地址空间不会互相冲突，一个进程的操作不会修改另一个进程地址空间中的数据。


### 用户态切换到内核态

用户态到内核态具体的切换步骤：

1. 从当前进程的描述符中提取其内核栈的ss0及esp0信息。
2. 使用ss0和esp0指向的内核栈将当前进程的cs,eip,eflags,ss,esp信息保存起来，这个过程也完成了由用户栈到内核栈的切换过程，同时保存了被暂停执行的程序的下一条指令。
3. 将先前由中断向量检索得到的中断处理程序的cs,eip信息装入相应的寄存器，开始执行中断处理程序，这时就转到了内核态的程序执行了。


### 进程的结构-PCB

进程都是由一系列操作(动作)所组成，通过这些操作来完成其任务。因此，不同的进程，其内部操作也不相同。在操作系统中，描述一个进程除了需要程序和私有数据之外，最主要的是需要一个与动态过程相联系的数据结构，该数据结构用来描述进程的外部特性(名字、状态等)以及与其它进程的联系(通信关系)等信息，该数据结构称为进程控制块(**PCB，Process Control Block**)。

进程控制块PCB与进程一一对应，PCB中记录了系统所需的全部信息、用于描述进程情况所需的全部信息和控制进程运行所需的全部信息。因此，系统可以通过进程的PCB来对进程进行管理。

### 进程切换
为了控制进程的执行，内核必须有能力挂起正在CPU上运行的进程，并恢复以前挂起的某个进程的执行。这种行为被称为**进程切换**。因此可以说，任何进程都是在操作系统内核的支持下运行的，是与内核紧密相关的。

从一个进程的运行转到另一个进程上运行，这个过程中经过下面这些变化：

1. 保存处理机上下文，包括程序计数器和其他寄存器
2. 更新[PCB](./io.html#进程的结构-pcb)信息
3. 把进程的[PCB](./io.html#进程的结构-pcb)移入相应的队列，如就绪、在某事件阻塞等队列
4. 选择另一个进程执行，并更新其[PCB](./io.html#进程的结构-pcb)
5. 更新内存管理的数据结构
6. 恢复处理机上下文

### 创建进程
1. 申请空白[PCB](./io.html#进程的结构-pcb)
2. 为新进程分配资源 (主要是内存资源的处理)
3. 初始化进程控制块 - 标识符（包括父进程的）、程序计数器指向程序入口地址，就绪态、优先级等信息的填写。
4. 将新进程插入就绪队列

> 注：os通过调用进程创建原语Create()创建新进程

### 进程的阻塞
正在执行的进程由于期待的某些事件未发生，比如请求系统资源失败、等待操作的完成、新数据尚未到达、无新工作做等时会由操作系统自动执行阻塞原语Block，使自己由运行状态变为阻塞状态。由此可见，进程的阻塞是进程自身的一种主动行为，也因此只有处于运行态的进程（获得CPU）才可以转变为阻塞状态。当进程进入阻塞状态后是不会占用CPU资源的。通俗来说，就是要等别人做完后你才能继续工作

### 同步与异步

由于CPU和内存的速度远高于外设，所以IO编程中存在严重不匹配的问题。比如将100M数据写入磁盘，CPU输出100M数据只需0.01秒，磁盘接收却需要10秒，怎么办？有两种办法可以解决这个问题：

- 让CPU等着，也就是程序暂停执行后续代码，等写入完成后再接着后续执行，这种模式称为同步IO。
- CPU不等待只是告诉磁盘：“你慢慢写不着急，我先干别的事儿去了！”，于是后续代码立即执行，这种模式称为异步IO。
- 同步和异步关注的是消息通信机制
- 同步与异步描述的是用户线程与内核的交互方式
- 同步synchronous是指用户线程发起IO请求后需要等待或轮询内核IO操作完成后才能继续执行。
- 异步asynchronous是指用户线程发起IO请求后仍然继续执行，当内核IO操作完成后会通知用户线程或调用用户线程注册的回调函数

### 同步与异步的区别

- 数据从“内核缓存区-用户内存”这个过程是否需要用户进程等待，实际IO读写是否阻塞请求进程。
- 是否等待IO执行的结果，使用异步IO来编写程序性能会远远高于同步IO，但异步IO的缺点是编程模型复杂。

### 阻塞与非阻塞

- 阻塞与非阻塞关注的是调用者在等待结果返回之前所处的状态
- 阻塞与非阻塞描述的是用户线程调用内核IO操作的方式
- 阻塞blocking是指IO操作需要彻底完成后才返回到用户空间，调用结果返回之前调用者被挂起。
- 非阻塞noblocking是指IO操作被调用后立即返回给用户一个状态值，无需等到IO操作彻底完成。
- 阻塞与非阻塞是函数或方法的实现方式，在数据就绪之前是立即返回还是等待，发起IO请求是否会被阻塞


### 文件描述符fd
文件描述符（File descriptor）是计算机科学中的一个术语，是一个用于表述指向文件的引用的抽象化概念。

文件描述符在形式上是一个非负整数。实际上，它是一个索引值，指向内核为每一个进程所维护的该进程打开文件的记录表。当程序打开一个现有文件或者创建一个新文件时，内核向进程返回一个文件描述符。在程序设计中，一些涉及底层的程序编写往往会围绕着文件描述符展开。但是文件描述符这一概念往往只适用于UNIX、Linux这样的操作系统。

## 缓存 I/O
缓存 I/O 又被称作标准 I/O，大多数文件系统的默认 I/O 操作都是缓存 I/O。在 Linux 的缓存 I/O 机制中，操作系统会将 I/O 的数据缓存在文件系统的页缓存（ page cache ）中，也就是说，数据会先被拷贝到操作系统内核的缓冲区中，然后才会从操作系统内核的缓冲区拷贝到应用程序的地址空间。

> 缺点：数据在传输过程中需要在应用程序地址空间和内核进行多次数据拷贝操作，这些数据拷贝操作所带来的 CPU 以及内存开销是非常大的。


## 网络 I/O

网络应用需要处理的两大类问题是网络IO和数据计算。相对于数据计算，网络IO的延迟会给应用带来性能上的瓶颈大于后者。

网路IO的本质是socket的读取操作，socket在Linux操作系统中被抽象为流stream。IO可以理解为对流的操作。IO编程中Stream流是一个重要的概念，可以把流想象成水管中的水，只能单向流向。`Input Stream`是数据从外部（如磁盘、网络等）流进内存，`Output Steam`是数据从内存流到外设。

<center>
<img :src="$withBase('/os_cp/os/os-io-02.png')" alt="foo"> 
</center>

对于一次磁盘IO访问，比如以read为例，数据会先被拷贝到操作系统内核的缓冲区，然后才会从系统内核缓冲区拷贝到应用程序的地址空间中。所以说，当一个read读操作发生时，它会经历两个阶段：等待数据准备、将数据从内核拷贝到进程中

网络IO除了转入内核调用外，与传统的磁盘IO不同的是，网络IO的读写对于socket流而言大致可分为两个阶段：

1. 等待：等待网络上的数据分组到达，然后复制到内核的某个缓冲区。
2. 复制：将数据从内核缓冲区复制到应用进程缓冲区

如果内核空间缓冲区中已经有数据了就可以省略掉第一步，为什么不能直接让磁盘控制器将数据送到应用程序的地址空间中呢？因为应用程序不能直接操作底层硬件。

相比于传统的网络IO，普通文件描述符的操作可分为两步，以read读操作为例，利用read()函数从socket中同步阻塞的读取数据。

需要注意的是不要使用操作磁盘文件IO的经验去看待网络IO，为什么呢？

因为实际上在磁盘IO中等待阶段是不存在的，因为磁盘文件并不像网络IO那样，需要等待远程传输数据。所以，习惯操作磁盘IO的开发者开始无法理解同步阻塞IO的工作过程，也无法理解为什么read()方法不会返回。

**客户端发起一个HTTP请求，服务器处理响应HTTP请求，此过程再服务器以网络IO的角度看经历了哪些阶段？**

<center>
<img :src="$withBase('/os_cp/os/os-io-03.png')" alt="foo"> 
<p>服务器构建网络数据包触发IO的过程</p>
</center>

1. 用户空间进程通过[recvfrom](https://github.com/torvalds/linux/blob/6f0d349d922ba44e4348a17a78ea51b7135965b1/include/uapi/linux/net.h#L38)函数接收等待接收数据包，并将接收到的数据包在内核中通过[四表五链](http://www.mikewootc.com/wiki/linux/usage/linux_firewall_iptables_intro.html)检查网络状态，若通过网络检查则提交给用户空间的HTTP进程。
2. HTTP进程解析请求并发起系统调用read函数，到达内核空间。
3. 内核空间执行read函数读取磁盘内容并将此内容加载到内存
4. 内核空间提交给用户空间HTTP进程并告知数据已经read完毕
5. 用户空间HTTP进程根据请求报文进行构建响应报文
6. 构建完HTTP响应报文后通知内核空间构建网络封装
7. 内核空间再次通过[四表五链](http://www.mikewootc.com/wiki/linux/usage/linux_firewall_iptables_intro.html)网络状态，通过网卡发送构建好的HTTP响应报文。

单纯根据流程可得到以下信息

1. 单进程接收响应数据报文调用[recvfrom](https://github.com/torvalds/linux/blob/6f0d349d922ba44e4348a17a78ea51b7135965b1/include/uapi/linux/net.h#L38)函数时，与此同时不执行其它函数调用，此时严重影响效率。
2. 当内核空间执行read函数后提交给用户空间进行HTTP封装，最后调用内核空间进行网络封装构建并发送报文。

根据上述流程可发现一次网络IO在逻辑上实际上是处于两种状态的，在这两种状态上进行优化IO才可以优化整体的性能。这两种形态在Linux网络编程中定义如下：

<center>
<img :src="$withBase('/os_cp/os/os-io-04.png')" alt="foo"> 
</center>

1. 等待数据准备

从逻辑上看是内核网络驱动等待接收网络数据包，表现在内核形态上，同时也是数据流可得信息的第一步。在用户空间封装完毕后如何通知内核再次进行网络报文的构建，在此状态下诞生了两种状态**同步synchronous**和**异步asynchronous**，同步是为进程自己主动等待函数执行成功并返回消息后才能继续执行其它函数，异步为函数执行完毕后主动通知进程执行其它流程，最后内核空间对网络IO进行解封装。

2. 将数据从内核拷贝到进程中

逻辑意义上是内核空间调用并执行系统调用函数后，将执行的结果反馈给用户空间，让用户空间进行构建响应报文。用户空间的进程能够执行其它函数，从而提升整体性能。在此状态下诞生了两种状态**阻塞blocking**和**非阻塞nonblocking**，阻塞状态是指IO操作需要彻底完成后才能返回到用户空间，调用结果返回之前调用者被挂起，即进程调用函数后被挂起直到函数返回结果后才能执行其它操作，非阻塞状态是指IO操作被调用后立即返回给用户一个状态值，无需等到IO操作彻底完成，最终的调用结果返回之前调用者不会被挂起，即进程在执行函数后无需等待执行结果仍可继续执行其它函数。


## IO模式

IO操作根据设备类型一般分为[内存IO](https://blog.csdn.net/seanyxie/article/details/5946219)、[网络IO](https://zhuanlan.zhihu.com/p/54580385)、[磁盘IO](https://blog.csdn.net/letterwuyu/article/details/53542291)，其中内存IO的速度是最快的，计算机的性能瓶颈一般不在内存IO上。尽管网络IO可通过购买独享带宽和高速网卡来提升速度，磁盘IO可使用RAID磁盘整列来提升磁盘IO的速度。但是由于IO操作都是由系统内核调用来完成的，系统调用是又通过CPU来调度的。由于CPU的速度远远快于IO操作，导致浪费CPU宝贵的时间来等待慢速的IO操作。为了让快速的CPU和慢速IO设备能更好的协调工作，减少CPU在IO调用的上的消耗，逐渐发展出各种IO模型。

对于一次IO访问（以read举例），数据会先被拷贝到操作系统内核的缓冲区中，然后才会从操作系统内核的缓冲区拷贝到应用程序的地址空间。
所以说，当一个read操作发生时，它会经历两个阶段：
1. 等待数据准备 (Waiting for the data to be ready)
2. 将数据从内核拷贝到进程中 (Copying the data from the kernel to the process)

正式因为这两个阶段，linux系统产生了下面五种网络模式的方案。
- **阻塞 I/O** [Blocking I/O]
- **非阻塞 I/O** [Nonblocking I/O]
- **I/O 多路复用** [IO multiplexing]
- **信号驱动 I/O** [Signal driven IO]
- **异步 I/O** [Asynchronous IO]

## 阻塞 I/O <Badge text="blocking IO" type="tip" vertical="middle"/>

同步阻塞IO模型是最常用也是最简单的IO模型，在Linux系统中默认情况下，所有的套接字socket都是阻塞的。这里的阻塞是指当前发起IO操作的进程会被阻塞，同步阻塞IO是指当进程调用某些IO操作的系统调用或库函数时，比如accept()、send()、recv()等时进程会暂停下来等待IO操作结束后再继续运行。

<center>
<img :src="$withBase('/os_cp/os/os-io-05.png')" alt="foo"> 
</center>

在读写数据过程中会发生阻塞现象。当用户线程发出IO请求后，内核会去查看数据是否就绪，如果没有就绪就会等待数据就绪，而用户线程会处于阻塞状态，用户线程交出CPU。当数据就绪后内核会将数据拷贝到用户线程，并返回结果给用户线程，用户线程才结束阻塞状态。

在内核将数据准备好之前，系统调用会一直等待所有的socket，默认是阻塞方式

一个典型的读操作流程大概是这样：

1. 当用户线程调用了[recvfrom](https://github.com/torvalds/linux/blob/6f0d349d922ba44e4348a17a78ea51b7135965b1/include/uapi/linux/net.h#L38)这个系统调用，kernel就开始了IO的第一个阶段：准备数据（对于网络IO来说，很多时候数据在一开始还没有到达。比如，还没有收到一个完整的UDP包。这个时候kernel就要等待足够的数据到来，磁盘IO的情况就是等待磁盘数据从磁盘上读取到内核态内存中。这个过程需要等待，也就是说数据被拷贝到操作系统内核的缓冲区中是需要一个过程的）。这个过程需要等待，也就是说数据被拷贝到操作系统内核的缓冲区中是需要一个过程的。而在用户进程这边，整个进程会被阻塞（当然，是线程自己选择的阻塞）
2. 当内核一直等到数据准备就绪后，就会将数据从内核中拷贝到用户内存中，处于系统安全考虑，用户态的程序是没有权限直接读取内核态内存，因此内核负责将内核态内存中的数据拷贝一份到用户态内存中。然后内核返回结果，用户进程才会接触阻塞block的状态，重新运行起来

所以，阻塞时IO的特点就是在IO执行的两个阶段都被阻塞了。

#### 优缺点

- 优点：实时性高能够及时返回数据，响应及时无延迟。
- 缺点：需要阻塞等待且性能差，对用户来说等待就要付出性能代价。

#### 适用场景

BIO方式（Blocking IO 同步阻塞编程）适用于连接数量较少且固定的架构，这种方式对服务器资源要求比较高，服务器实现模式为一个连接一个线程，即客户端有连接请求时服务端就需要启动一个线程进行处理。如果这个连接不做任何事情则会造成不必要的线程开销，当然可以通过线程池机制加以改善。

### 非阻塞 I/O <Badge text="nonblocking IO" type="tip" vertical="middle"/>

同步非阻塞IO对比同步阻塞IO而言，它不会去等待数据的就绪，如果数据不可读或不可写，相关的系统调用会立即高速进程并立即返回。这样做的好处是结合反复轮询来尝试数据是否就绪，那么在一个进程中就可以同时处理多个IO操作。

<center>
<img :src="$withBase('/os_cp/os/os-io-06.png')" alt="foo"> 
</center>

非阻塞IO一般只针对网络IO有效，当在socket的选项中设置O_NONBLOCK时，此时socket的send()或recv()就会采用**非阻塞方式**。

对于磁盘IO非阻塞IO并不会产生效果
- 文件描述符fd在read之前有可能会重新进入不可读的状态，要么被其他人都走了（惊群问题），还有可能被内核抛弃了。总的来说，fd因为在read之前数据被其它方式读走，fd重新变为不可读。此时使用阻塞时IO的read函数就会阻塞整个线程。
- epoll只是返回了可读事件并没有返回可以读多少数据量，因此非阻塞IO的做法是都多次直到不能读。而阻塞式IO却只能读一次，因为万一一次就读完了缓冲区的所有数据，第二次读的时候read就会有阻塞了。对于epoll的ET模式来说，缓冲区的数据只会在改变时通知一次，如果此次没有消费完，在下次数据到来之前，可读事件再就也不会通知。这对只能调用一次的read的阻塞式IO来说，未读完的数据就有可能永远读不到了。


当用户线程发起一个read读操作后并不需要等待，而是马上就得到一个结果。如果结果是一个error错误，就表示数据还没有准备好，于是可以再次发送read读操作。一旦内存中的数据准备好了并且又再次收到用户线程的请求，那么会马上就将数据拷贝到用户线程然后返回。事实上，在非阻塞IO模型中，用户线程需要不断询问内核数据是否就绪，换句话说**非阻塞IO不会交出CPU而会一直占用CPU**

与阻塞时I/O不同的是，非阻塞的[recvfrom](https://github.com/torvalds/linux/blob/6f0d349d922ba44e4348a17a78ea51b7135965b1/include/uapi/linux/net.h#L38)系统调用执行后，进程并不会被阻塞，内核会立即返回给进程。如果数据还未就绪（准备好），此时会返回一个错误error（EAGAIN或EWOULDBLOCK）。

进程在返回之后可以处理其它业务逻辑，过会儿再发起recvfrom系统调用。采用这种轮询的方式不断检查内核数据，直到数据准备就绪，再拷贝数据到进程进行数据处理。

内核每次都返回一个错误errno（EWOULDBLOCK）,但并不会阻塞进程。当第四次调用recvfrom时数据已经准备就绪，则将其从内核空间拷贝到程序空间进行处理数据。

值得注意的是，在非阻塞状态下，IO执行的等待阶段并不是完全阻塞的，但第二个阶段依然处于一个阻塞状态。

对于非阻塞IO有一个非常严重的问题是在while循环中需要不断地去询问内核数据是否就绪，这样会导致CPU占用率非常高，因此一般情况下很少使用while循环这种方式来读取数据。

### 优缺点

- 优点：能够在等待的事件里去做其它的事情
- 缺点：任务完成得响应延迟增大了，因为每过一段时间去轮询一次read读操作 ，而任务可能在两次轮询之间的任意时间完成，这将导致整体数据吞吐量的降低。

### 同步非阻塞与同步阻塞之间有什么优缺点呢？

- 优点：同步非阻塞能够在等待任务完成得时间里做其它事情，包括提交其它任务，也就是说“后台”可以有多个任务在同时执行。
- 缺点：同步非阻塞任务完成得响应时间延迟增大了，因为每过一段时间需要去轮询一次read读操作，任务可能在两次轮询之间的任意时间中已经完成了。这将导致整体数据吞吐量的降低。


## I/O 多路复用 <Badge text="IO multiplexing" type="tip" vertical="middle"/>

多路复用IO模型是目前使用较多的一种模型,IO复用也叫做多路IO就绪通知，是一种进程预先告知内核的能力，内核发现进程指定的一个或多个IO条件就绪了，就会去通知进程，使得一个进程能在一连串的事件上等待。

简单来说，就是指定一个线程，通过记录IO流的状态来同时管理多个IO，以提高服务器的吞吐能力。IO多路复用的好处在于单个进程就可以同时处理多个网络连接的IO

<center>
<img :src="$withBase('/os_cp/os/os-io-07.png')" alt="foo"> 
</center>

IO多路复用的基本原理是不再由应用程序自己监视连接，取而代之由内核替应用程序监视文件描述符。

多路IO就绪通知模型允许进程通过一种方法同时监视所有的文件描述符，并能快速获得所有就绪的文件描述符，然后针对这些文件描述符进行数据访问。简单来说，就是提供了对大量文件描述符就绪检查的高性能方案。

需要注意的是，IO就绪模型只是解决了快速获取就绪的文件描述符的问题，在得知数据就绪后，就数据访问本身而言，还是需要选择阻塞或非阻塞的访问方式。

实现方式有select，poll，epoll，有些地方也称这种IO方式为`event driven IO`。select/epoll的好处就在于单个process就可以同时处理多个网络连接的IO。它的基本原理就是select，poll，epoll这个function会不断的轮询所负责的所有socket，当某个socket有数据到达了，就通知用户进程。

#### select

```c
int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
```

select最早出现于1934年BSD4.2中，通过一个select()系统调用来监视包含多个文件描述符的数组，当select()返回后这个数组中就绪的文件描述符会被内核修改标志位，使得进程可以获得这些文件描述符，从而进行后续的读写操作。

select的缺点在于单进程能够监视的文件描述符的数量存在最大限制，在Linux上一般是32 * 32bit = 1024位（取决于FD_SET，它底层实现实现是bitmap），不过可以通过修改宏定义或重新编译内核的方式来提升限制。所以，如果使用select()的服务器已经维持了1024个连接，后续的请求可能会被拒绝。

另外，select()维护着存储大量文件描述符的数据结构，随着文件描述符数量的增加，复制开销也线性增长。

另一方面，由于网络延迟使大量TCP连接处于非活跃状态，调用select()会对所有的socket进行一次线性扫描，也会浪费一定的开销。

```c
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <wait.h>
#include <signal.h>
#include <errno.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
 
#define MAXBUF 256
 
void child_process(void)
{
  sleep(2);
  char msg[MAXBUF];
  struct sockaddr_in addr = {0};
  int n, sockfd,num=1;
  srandom(getpid());
  /* Create socket and connect to server */
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  addr.sin_family = AF_INET;
  addr.sin_port = htons(2000);
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");
 
  connect(sockfd, (struct sockaddr*)&addr, sizeof(addr));
  printf("child {%d} connected \n", getpid());
  while(1){
        int sl = (random() % 10 ) +  1;
        num++;
      sleep(sl);
    sprintf (msg, "Test message %d from client %d", num, getpid());
    n = write(sockfd, msg, strlen(msg));  /* Send message */
  }
}
 
int main()
{
  char buffer[MAXBUF];
  int fds[5];
  struct sockaddr_in addr;
  struct sockaddr_in client;
  int addrlen, n,i,max=0;;
  int sockfd, commfd;
  fd_set rset;
  for(i=0;i<5;i++)
  {
    if(fork() == 0)
    {
      child_process();
      exit(0);
    }
  }
 
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  memset(&addr, 0, sizeof (addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(2000);
  addr.sin_addr.s_addr = INADDR_ANY;
  bind(sockfd,(struct sockaddr*)&addr ,sizeof(addr));
  listen (sockfd, 5); 
 
  for (i=0;i<5;i++) 
  {
    memset(&client, 0, sizeof (client));
    addrlen = sizeof(client);
    fds[i] = accept(sockfd,(struct sockaddr*)&client, &addrlen);
    if(fds[i] > max)
      max = fds[i];
  }
  
  while(1){
  FD_ZERO(&rset);
    for (i = 0; i< 5; i++ ) {
      FD_SET(fds[i],&rset);
    }
 
    puts("round again");
   select(max+1, &rset, NULL, NULL, NULL);
 
  for(i=0;i<5;i++) {
    if (FD_ISSET(fds[i], &rset)){
      memset(buffer,0,MAXBUF);
      read(fds[i], buffer, MAXBUF);
      puts(buffer);
    }
  } 
  }
  return 0;
}
```


### poll

```c
int poll (struct pollfd *fds, unsigned int nfds, int timeout);
```
poll诞生于1986年的System V Release3，显然UNIX不愿意直接沿用BSD的select，而是重新实现了一遍。poll和select本质上没有太多区别，只是poll没有最大文件描述符数量的限制。

select和poll的原理基本相同：

1. 注册待监听的文件描述符fd，这里的fd创建时最好是**非阻塞**的。
2. 每次调用都去检查fd文件描述符的状态，当有一个或多个fd就绪时返回。
3. 返回结果中包含已就绪和未就绪的文件描述符fd

相比select，poll解决了单进程能够打开文件描述符数量有限的问题，由于select受限于`FD_SIZE`的限制，若修改`FD_SIZE`宏需重新编译内核。poll通过一个pollfd数组向内核传递需要关注的事件，避开了文件描述符的数量限制。

```c
struct pollfd {
      int fd;
      short events; 
      short revents;
};
```
修改上面select代码，更改FD_SET部分

```c
  for (i=0;i<5;i++) 
  {
    memset(&client, 0, sizeof (client));
    addrlen = sizeof(client);
    pollfds[i].fd = accept(sockfd,(struct sockaddr*)&client, &addrlen);
    pollfds[i].events = POLLIN;
  }
  sleep(1);
  while(1){
    puts("round again");
  poll(pollfds, 5, 50000);
 
  for(i=0;i<5;i++) {
    if (pollfds[i].revents & POLLIN){
      pollfds[i].revents = 0;
      memset(buffer,0,MAXBUF);
      read(pollfds[i].fd, buffer, MAXBUF);
      puts(buffer);
    }
  }
  }
```
此外，select和poll共同具有一个很大的缺点是包含大量文件描述符fd的数组会被整体复制到用户态和内核态地址空间之间，不论这些文件描述符fd是否就绪，其开销会随着文件描述符fd数量增多而线性增大。

另外，select()和poll()将就绪的文件描述符fd告诉进程后，如果进程没有对其进行IO操作，那么下次调用select()或poll()时会再次报告这些文件描述符，所以它们一般不会丢失就绪的消息，这种方式称为水平触发（Level Triggered）。

#### Select 还是 Poll

- poll不需要用户计算编号最大的文件描述符的值+1
- poll对于大值文件描述符更有效。想象一下，通过select观察值为900的单个文件描述符—内核将必须检查每个传入集合的每个位，直到第900位。
- select的文件描述符集是静态大小的。
- select的超时参数在返回时未定义。可移植代码需要重新初始化它
- 由于某些Unix系统不支持poll，因此select具有更高的可移植性。


###  epoll

Epoll *系统调用可帮助我们在内核中创建和管理上下文。通常3个步骤：

```c
int epoll_create(int size)；//创建一个epoll的句柄，size用来告诉内核这个监听的数目一共有多大
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event)；
int epoll_wait(int epfd, struct epoll_event * events, int maxevents, int timeout);
```


1. `int epoll_create(int size);`

创建一个epoll的句柄，size用来告诉内核这个监听的数目一共有多大，这个参数不同于select()中的第一个参数，给出最大监听的fd+1的值，参数size并不是限制了epoll所能监听的描述符最大个数，只是对内核初始分配内部数据结构的一个建议。
当创建好epoll句柄后，它就会占用一个fd值，在linux下如果查看/proc/进程id/fd/，是能够看到这个fd的，所以在使用完epoll后，必须调用close()关闭，否则可能导致fd被耗尽。

2. `int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event)；`
函数是对指定描述符fd执行op操作。
- epfd：是epoll_create()的返回值。
- op：表示op操作，用三个宏来表示：添加EPOLL_CTL_ADD，删除EPOLL_CTL_DEL，修改EPOLL_CTL_MOD。分别添加、删除和修改对fd的监听事件。
- fd：是需要监听的fd（文件描述符）
- epoll_event：是告诉内核需要监听什么事，struct epoll_event结构如下：

```c
struct epoll_event {
  __uint32_t events;  /* Epoll events */
  epoll_data_t data;  /* User data variable */
};
```

events可以是以下几个宏的集合：
- EPOLLIN ：表示对应的文件描述符可以读（包括对端SOCKET正常关闭）；
- EPOLLOUT：表示对应的文件描述符可以写；
- EPOLLPRI：表示对应的文件描述符有紧急的数据可读（这里应该表示有带外数据到来）；
- EPOLLERR：表示对应的文件描述符发生错误；
- EPOLLHUP：表示对应的文件描述符被挂断；
- EPOLLET： 将EPOLL设为边缘触发(Edge Triggered)模式，这是相对于水平触发(Level Triggered)来说的。
- EPOLLONESHOT：只监听一次事件，当监听完这次事件之后，如果还需要继续监听这个socket的话，需要再次把这个socket加入到EPOLL队列里

3. `int epoll_wait(int epfd, struct epoll_event * events, int maxevents, int timeout);`
等待epfd上的io事件，最多返回maxevents个事件。
参数events用来从内核得到事件的集合，maxevents告之内核这个events有多大，这个maxevents的值不能大于创建epoll_create()时的size，参数timeout是超时时间（毫秒，0会立即返回，-1将不确定，也有说法说是永久阻塞）。该函数返回需要处理的事件数目，如返回0表示已超时。


将上面改为epoll 实现方式

```c
struct epoll_event events[5];
  int epfd = epoll_create(10);
  ...
  ...
  for (i=0;i<5;i++) 
  {
    static struct epoll_event ev;
    memset(&client, 0, sizeof (client));
    addrlen = sizeof(client);
    ev.data.fd = accept(sockfd,(struct sockaddr*)&client, &addrlen);
    ev.events = EPOLLIN;
    epoll_ctl(epfd, EPOLL_CTL_ADD, ev.data.fd, &ev); 
  }
  
  while(1){
    puts("round again");
    nfds = epoll_wait(epfd, events, 5, 10000);
  
  for(i=0;i<nfds;i++) {
      memset(buffer,0,MAXBUF);
      read(events[i].data.fd, buffer, MAXBUF);
      puts(buffer);
  }
  }
```

而epoll的出现解决select和poll的缺点：

1. epoll基于事件驱动的方式避免了每次都要将所有fd都扫描一遍
2. epoll_wait只返回就绪的fd
3. epoll使用nmap内存映射技术避免了内存复制的开销
4. epoll的fd数量上限是操作系统的最大文件句柄数量，此数量和内存相关，通常大于1024。

目前epoll是Linux2.6下最高效的IO复用方式，也是Nginx、Node的IO实现方式。

#### 水平触发与边缘触发
此外，对于IO复用还有一个水平触发和边缘触发的概念：

1. 水平触发：当就绪的fd未被用户进程处理后，下一次查询依旧会返回，这是select和poll的触发方式。
2. 边缘触发：无论就绪的fd是否被处理，下一次不再返回。

理论上边缘触发的性能更高，但是实现相当复杂，任何以外的丢失事件都会造成请求处理错误。epoll默认采用水平触发的方式，可通过配置选项可使用边缘触发。

### 实现原理

1. 当进程调用select时会被阻塞
2. 此时内核会监视所有select负责的socket，当socket的数据准备就绪后立即返回
3. 进程再次调用read读操作，数据从内核中拷贝到进程。

在多路复用IO模型中会有一个线程不断去轮询多个socket的状态，只有当socket真正有读写事件时，才真正调用实际的IO读写操作。

在多路复用IO模型中，只需要使用一个线程就可以管理多个socket，系统不需要建立新的线程或进程，也不必维护这些进程和线程，只有在真正有socket读写事件进行时才会使用IO资源，所以它大大减少了资源占用。

#### Select poll 还是 Epoll

- 我们可以在等待时添加和删除文件描述符
- epoll_wait仅返回具有就绪文件描述符的对象
- epoll具有更好的性能-O（1）代替O（n）
- epoll可以表现为水平触发或边沿触发
- epoll是特定于Linux的，因此不可移植 （win iocp）
- 监听的描述符数量不受限制，它所支持的FD上限是最大可以打开文件的数目
- IO的效率不会随着监视fd的数量的增长而下降。epoll不同于select和poll轮询的方式，而是通过每个fd定义的回调函数来实现的。只有就绪的fd才会执行回调函数。

如果没有大量的idle-connection或者dead-connection，epoll的效率并不会比select/poll高很多，但是当遇到大量的idle-connection，就会发现epoll的效率大大高于select/poll。

最后，阻塞IO只调用了一个系统调用[recvfrom](https://github.com/torvalds/linux/blob/6f0d349d922ba44e4348a17a78ea51b7135965b1/include/uapi/linux/net.h#L38)。如果处理的连接数不是很高的话，使用IO复用的服务器并不一定比使用“多线程+非阻塞IO”的性能更好，可能延迟还更大。

IO复用的优势并不是对于单个连接能处理的更快，而是单个进程就可以同时处理多个网络连接的IO。实际使用时，对于每个socket都可以设置为非阻塞的。

用户进程其实是一直被阻塞的。只不过进程是被select函数阻塞，而不是被IO操作给阻塞。所以IO多路复用是阻塞在select、epoll这样的系统调用之上，而没有阻塞在整整的IO系统调用如[recvfrom](https://github.com/torvalds/linux/blob/6f0d349d922ba44e4348a17a78ea51b7135965b1/include/uapi/linux/net.h#L38)上

#### 异步IO与同步IO的区别

同步IO是需要应用程序主动地循环去询问是否有数据，异步IO是通过像`select`等IO多路复用函数来同时检测多个事件句柄来告知应用程序是否有数据。

高并发的程序一般使用`同步非阻塞`模式，而不是`多线程+同步阻塞`模式。要理解这一点需要先弄清楚并发和并行的区别。并发数是同时进行的任务数，并行数是可以同时工作的物理资源数量（如CPU核数）。

通过合理调度任务的不同阶段，并发数可以远远大于并行数。这就是区区几个CPU可以支持上万用户并发请求的原因。在这种高并发的情况下，为每个用户请求创建一个进程或线程的开销非常大，而同步非阻塞方式可以把多个IO请求丢到后台去，这样CPU就可以服务大量的并发IO请求了。

#### IO多路复用究竟是同步阻塞还是异步阻塞模型呢？

同步是需要主动等待消息通知，异步则是被动接受消息通知，通过回调、通知、状态等方式来被动获取消息。IO多路复用在阻塞到`select`阶段时，用户进程是主动等待并调用`select`函数来获取就绪状态消息，并且其进程状态为阻塞。所以IO多路复用是同步阻塞模式。

#### 优势

与传统的多进程或多线程模型相比，IO多路复用的最大优势是系统开销小，系统无需创建新的进程或线程，也无需维护这些进程和线程的运行，因此降低了系统的维护工作量并节省了系统资源。

#### 应用场景

- 服务器需要同时处理多个处于监听状态或多个连接状态的套接字
- 服务器需要同时处理多种网络协议的套接字
- 服务器需要监听多个端口或处理多种服务
- 服务器需要同时处理用户输入和网络连接

## 信号驱动 I/O <Badge text="signal driven IO" type="tip" vertical="middle"/>

在信号驱动IO模型中，当用户线程发起一个IO请求操作，会给对应的socket注册一个信号函数，然后用户线程会继续执行，当内核数据就绪时会发送一个信号给用户线程，用户线程接收到信号后，便在信号函数中调用IO读写操作来进行实际的IO请求操作。

<center>
<img :src="$withBase('/os_cp/os/os-io-08.png')" alt="foo"> 
</center>

#### 业务流程
```c
int sigaction(int sig, const struct sigaction *restrict act,struct sigaction *restrict oact);
```

1. 开启套接字信号驱动IO功能
2. 系统调用sigaction执行信号处理函数，信号处理函数是非阻塞的会立即返回。
3. 数据就绪并生成sigio信号，通过信号回调通知应用读取数据。

#### 网络模型

应用程序提交read读请求后调用system call，然后内核开始处理相应的IO操作。同时应用程序并不等内核返回响应就会开始执行其它的处理操作（应用程序没有被IO阻塞）。

当内核执行完毕返回read响应，会产生一个信号或执行一个基于回调函数来完成这次IO处理过程。在这里IO的读写操作是在IO事件发生之后由应用程序来完成的。异步IO读写操作总是立即返回，不论IO是否阻塞，因为真正的读写操作已经由内核掌管。

也就是说，同步IO模型要求用户自行执行IO操作（将数据从内核缓冲区移动到用户缓冲区，或相反），异步操作机制则由内核来执行IO操作。简单来说，同步IO向应用程序通知的是IO就绪事件，而异步IO向应用程序通知的是IO完成事件。

信号驱动IO模型中应用程序告诉内核，当数据包准备好的时候，给我发送一个信号，对SIGIO信号进行捕捉，并且调用我的信号处理函数来获取数据报。

问题缺陷

信号驱动IO模式存在一个很大的问题是Linux中信号队列是有限的，如果超过限制则无法读取数据。


## 异步 I/O <Badge text="asynchronous IO" type="tip" vertical="middle"/>

异步IO又叫做事件驱动IO，异步IO操作是需要操作系统底层支持。

<center>
<img :src="$withBase('/os_cp/os/os-io-09.png')" alt="foo"> 
</center>


异步IO模型是最理想的IO模型，在异步IO模型中当用户线程发起read读操作后立即就可以开始去做其它的事情。从内核角度看，当内核收到一个`asynchronous read`之后会立即返回，说明read请求已经成功发起了，因此不会对用户线程产生任何阻塞block。

```c
int aio_read(struct aiocb *aiocbp);
```

然后，内核会等待数据准备完成，然后将数据拷贝到用户线程，当这一切都完成之后，内核会给用户线程发送一个信号，告诉它read读操作完成了。也就是说用户线程完全不需要知道实际整个IO操作是如何进行的，只需要先发起一个请求，当接收内核返回的成功信号时，表示IO操作已经完成可以直接去使用数据了。


在异步IO模型中，IO操作的两个阶段都不会阻塞用户线程，这两个阶段都是由内核自动完成的，然后发送一个信号告知用户线程操作已经完成。用户线程中不需要再次调用IO函数进行具体的读写。这点和信号驱动模型有所不同。在信号驱动模型中，当用户线程接收到信号表示数据已经就绪，然后需要用户线程调用IO函数进行实际的读写操作，在异步IO模型中，收到信号表示IO操作已经完成，不需要再在用户线程中调用IO函数进行实际读写操作

异步IO和异步概念一样，当一个异步过程调用发出后，调用者不能立即得到结果，实际处理这个调用的函数在完成后，通过状态、通知、回调函数来通知调用者的IO操作。

异步IO的工作机制是告知内核启动某个操作，并让内核在整个操作完成后通知我们，这种模型与信号驱动的IO区域在于，信号驱动IO是由内核通知我们何时可以启动一个IO操作，这个IO操作由用户自定义的信号函数来实现，而异步IO模型是由内核告知我们IO操作何时完成。

### 小结

前四种IO模型实际上都属于同步IO，只有最后一种是真正的异步IO，因为无论是多路复用IO还是信号驱动模型，IO操作的第二阶段都会引起用户线程阻塞，也就是内核进行数据拷贝的过程会让用户线程阻塞。


<center>
<img :src="$withBase('/os_cp/os/os-io-10.png')" alt="foo"> 
<p>
根据阻塞程度效率由低到高的顺序是：阻塞IO > 非阻塞IO > 多路复用IO > 信号驱动IO > 异步IO
  </p>
</center>

## IO设计模式

### 传统IO设计模式
在传统网路服务设计模式中，有两种经典的模式：多线程、线程池

### 多线程模式
多线程模式简单来说就是来了客户端服务器就会建立一个线程来处理该客户端的读写事件
<center>
<img :src="$withBase('/os_cp/os/os-io-11.png')" alt="foo"> 
</center>

多线程模型虽然处理简单但由于服务器为每个客户端的连接都建立一个线程去处理，资源占用非常大。因此当连接数达到上限时，后续的用户连接请求将会直接导致资源瓶颈，严重的可能会直接导致服务器崩溃。


### 线程池模式

为了解决这种“一个线程对应一个客户端”模式带来的弊端，提出了线程池的方式，也就是说创建一个固定大小的线程池，来一个客户端就从线程池中获取一个空闲的线程来处理，当客户端处理完读写操作之后就交出对线程的占用。这样就避免为每个客户端创建线程带来的资源浪费，使得线程可以复用。
<center>
<img :src="$withBase('/os_cp/os/os-io-12.png')" alt="foo"> 
</center>

线程池的弊端在于如果连接池中大多是长连接可能会导致一段时间内，线程池中的线程都被占用，再有用户请求连接时由于没有可用的空闲线程来处理，会导致客户端连接失败，从而影响用户体验，因此线程持比较适合大量的短连接的应用。

### 高性能IO设计模式

### Reactor
在Reactor模式中会先对每个客户端注册感兴趣的事件，然后有一个线程专门去轮询每个客户端是否有事件发生，当有事件发生时便顺序处理每个事件，当所有事件都处理完毕后便再转去继续轮询。
<center>
<img :src="$withBase('/os_cp/os/os-io-13.png')" alt="foo"> 
<p>IO模型中的多路复用IO模型采用的就时Reactor模式</p>
</center>

### Proactor
在Proactor模式中当检测到有事件发生时会新起一个异步操作，然后交由内核线程去处理，当内核线程完成IO操作之后，发送一个通知告知操作已经完成。IO模型中的异步IO模型采用的就时Proactor模式。

