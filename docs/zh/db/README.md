# 数据库 :mag_right:


数据库不是凭空产生的，它们是为了解决实际使用中提出的问题，在RDBMS（关系数据库管理系统）出现的环境中，数据库插叙你的灵活性比灵活的模式更重要

## 数据库概述 

本节包含了9种数据库的信息

|      | MongoDB| counchDB  |Riak|Redis|PostgreSQL|Neo4J|HBase|Mysql|Clickhouse|
| ---- |:-----:| :-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|
|  类型    |文档 | 文档 |键-值 |键-值 |关系 |图 |列 |关系|列 |
|  数据类型 | 有类型  | 有类型 | Blob |半类型 | 预定义且有类型 |无类型|预定义且有类型 |:x: |:x: |
|  数据关系 | 无 | 无 | 自由定义的（链接） |无 | 预定义 |预定义的（边） |无 |:x: |:x: |
|  标准对象 | JSON | JSON | 文本| 字符串 |表 |哈希 |列 |:x: |:x: |
|  编写语言 | C++| Erlang | Erlang|C/C++ |C |JAVA |JAVA |:x: |:x: |
|  接口协议 | TCP上自定义 | HTTP | HTTP-Protobuf | TCP上的简单文本 |TCP上自定义 |HTTP |Thrift-HTTP |:x: |:x: |
|  HTTP/REST | :white_check_mark:  | :white_check_mark:  |:white_check_mark:  | :x: | :x: | :white_check_mark:  | :white_check_mark:  |:x: |:x: |
|  二级索引 |:white_check_mark:      |    :white_check_mark: |:white_check_mark:|:x:|:white_check_mark: |:white_check_mark: |:white_check_mark:|:x: |:x: |
|  版本化 | :x:   |   :white_check_mark:  |:white_check_mark:  |:x: |:x: |:x: |:white_check_mark:  |:x: |:x: |
|  Build Load | mongoimport      | Bulk Doc API |否 |否 |COPY命令 | 否 |否 |:x: |:x: |
|  非常大的文件 | GridFS  | 附件 |Luwak(已弃用) |无|BLOB |无 |无|:x: |:x: |
|  自由定义的查询 | 命令mapreduce |临时视图|弱支持Lucene |命令 |SQL |图遍历，Cypher，搜索 |弱|:x: |:x: |
|  mapreduce | JavaScript |JavaScript |JavaScript，Erlang |无|无 |无 |Hadoop|:x: |:x: |
|  伸缩性 | 数据中心     | 数据中心 |数据中心 |集群（主-从） |集群（通过一些扩展） |集群（通过HA） |数据中心 |:x: |:x: |
|  耐久性 | 写前日志安全模式 | 只在崩溃时 | 写入法定数则耐久 | 仅追加的日志 |ACID |ACID |写前日志|:x: |:x: |
|  请求压缩 |否      |  文件重写 |否|快照 |否 |否 |否 |:x: |:x: |
|  复制 | 主-从（通过复集）| 主-主|基于对等主-主|主-从 |主-从 |主-从（在企业版中） |主-从 |:x: |:x: |
|  并发 | 写锁  | 无锁的MVCC | 向量锁 | 无 | 表/行写锁 |写锁  |每行一段 |:x: |:x: |
|  分片 | 是 | 锁（通过BigCouch过滤器） |是|插件（客户端） | 扩展（PL/Proxy） |否|通过HDFS |:x: |:x: |
|  事务 | 无| 无|无 |多操作队列 |ACID | ACID |是 |:x: |:x: |
|  触发器 | 无 | 更新验证或改变API |提交前后 |无 |是 |事物事件处理程序 |无 |:x: |:x: |
|  安全性 | 用户| 用户 |无 | 口令 |用户/群 |无 |Kerberos,通过Hadoop的安全性 |:x: |:x: |
|  一主机多实例 | :white_check_mark:      |    :white_check_mark:|:x: |:x: |:white_check_mark:|:x: |:x: |:x: |:x: |
|  主要区别 | 容易查询大量数据   | 耐久的可嵌入的集群 | 高可用性 |非常非常快 |最好的OSS RDBMS模型 |灵活的图 |规模非常大，Hadoop基础设施 |:x: |:x: |
|  不足 | 嵌入能力 |查询能力 | 查询能力 |负责数据 |分布式高可用性 | Blob或TB级数据 |灵活增长查询能力 |:x: |:x: |


## 附录
* [数据库全球排名](https://db-engines.com/en/ranking)

