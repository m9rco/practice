# PostgreSQL

<center><img :src="$withBase('/db/postgresql/postgresql-01.png')" alt="foo"></center>
20世纪70年代初，最初的项目产生于加州大学伯克利分校，叫做交互式图形和检索系统（Interactive Graphincs and Retrieval System）,简称Ingres，在20世纪80年代，推出了一个改进版，post-ingres,简称为Postgres,虽然后面这个项目让伯克利大学中介，但开源社区拿到了源码，并将其改名为PostgreSQL95，后来在1996年更名为PostgreSQL,表示对心的SQL标准的支持，此后就一直用这个名字

## 初始化

PostgreSQL不仅支持关系数据库的各种功能，而且还具备类、继承等对象数据库的特征。它是目前功能最强大、特性最丰富和结构最复杂的开源数据库管理系统，其中有些特性甚至连商业数据库都不具备。这个起源于加州大学伯克利分校（UCB）的数据库研究计划，现在已经衍生成一项国际开发项目，并且拥有广泛的用户群。PostgreSQL主要运行在Unix和Linux操作系统上（从8.0版本开始推出了Windows平台上的版本），并且免费开放源代码，用户可以在其[官方网站](www.postgresql.org)上下载各种安装程序和文档


### 数学关系

关系数据库的名称源于它们包含关系（即表），它们是元组（即行）的集合，元组又将属性映射到原子值，可用的属性通过头部的属性元组来定义，这些属性映射啊都某个域或限制的类型，这是关系结构的要点

### 准备环境


1. 安装环境，并进入环境

```sh
set -ex \
  && docker run --name pgsql -e POSTGRES_PASSWORD=marco -d postgres:9.6 \
  && docker exec -it -u postgres pgsql /bin/bash 
```

2. 创建`book`数据库

```sh
 createdb book # pg套件里自带的命令
```

### 从SQL开始

一个简单的CURD

```sql
CREATE TABLE students (id SERIAL PRIMARY KEY,name VARCHAR(10) UNIQUE,hobby VARCHAR(255)); 
INSERT INTO students(name,hobby) VALUES ('marco','foo'),('jack','bar'); 
UPDATE students SET hobby="bar" WHERE name='marco' ; 
DELETE FROM students WHERE name='jack';
SELECT * FROM students;
```

获得结果集

```sh
book=# SELECT * FROM students;
 id | name  | hobby
----+-------+-------
  1 | marco | bar
(1 row)
```

关于外键

```sql
CREATE TABLE class (student_id int REFERENCES "students"("id"), title VARCHAR(10) CHECK(title <> ''),PRIMARY KEY(title,student_id));
INSERT INTO class(student_id,title) VALUES (1,'boss');
```

查看当前数据库里所有表类似mysql的`SHOW TABLES;`

```sh
book=# \d
               List of relations
 Schema |      Name       |   Type   |  Owner
--------+-----------------+----------+----------
 public | class           | table    | postgres
 public | students        | table    | postgres
 public | students_id_seq | sequence | postgres
(3 rows)

```

## 体系结构
<img :src="$withBase('/db/postgresql/postgresql-02.png')" alt="foo">

PostgreSQL数据库由连接管理系统（系统控制器）、编译执行系统、存储管理系统、事务系统、系统表五大部分组成，

- **连接管理系统** 接受外部操作对系统的请求，对操作请求进行预处理和分发，起系统逻辑控制作用；
- **编译执行系统** 由查询编译器、查询执行器组成，完成操作请求在数据库中的分析处理和转化工作，最终实现物理存储介质中数据的操作；
- **存储管理系统** 由索引管理器、内存管理器、外存管理器组成，负责存储和管理物理数据，提供对编译查询系统的支持；
- **事务系统** 由事务管理器、日志管理器、并发控制、锁管理器组成，日志管理器和事务管理器完成对操作请求处理的事务一致性支持，锁管理器-和并发控制提供对并发访问数据的一致性支持；
- **系统表** 是PostgreSQL数据库的元信息管理中心，包括数据库对象信息和数据库管理控制信息。系统表管理元数据信息，将PostgreSQL数据库的各个模块有机地连接在一起，形成一个高效的数据管理系统。


## MVCC
