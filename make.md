# Makefile读书笔记
## 程序的编绎和链接
1. cpp文件首先编绎成中间文件(.o .obj), 这一步只进行预处理和语法检查
2. 中间文件经过链接，成为目标文件，这一步是在寻找函数的实现，如果找不到就报错

## Makefile的目标
1. 如果工程没有编绎过，那么所有c文件都要编绎并链接
2. 如果有一个c文件改变了，那么就只编绎这个改过的文件, 并链接目标程序
3. 如果头文件发生改变， 那么编绎所有包含这个头文件的文件，并链接目标程序

## Makefile的工作原理
```
target:prerequisites
    command
```

Make会先找到第一个目标文件(最终目标, 有且仅有一个），如果不存在，或是依赖文件比目标文件新，就会执行编绎命令。如果依赖文件不存在，就会寻找该文件的依赖关系。

总之，Make在自项向下地递归地寻找依赖关系，并决定是否执行commmand。最后生成目标文件。

### Makefile实例1
```
edit:main.o kbd.o command.o display.o \
	insert.o search.o files.o utils.o
	gcc -o edit main.o kbd.o command.o display.o \
	insert.o search.o files.o utils.o

main.o:main.c defs.h
	gcc -c main.c
kbd.o: kbd.c defs.h command.h
	gcc -c kbd.c
command.o: command.c defs.h command.h
	gcc -c command.c
display.o: display.c defs.h buffer.h
	gcc -c display.c
insert.o: insert.c defs.h buffer.h
	gcc -c insert.c
search.o: search.c defs.h buffer.h
	gcc -c search.c
files.o: files.c defs.h buffer.h command.h
	gcc -c files.c
utils.o: utils.c defs.h
	gcc -c utils.c

.PHONY:clean  # .PHONY表示这里是伪目标
clean:
	-rm edit main.o kbd.o command.o display.o \
	insert.o search.o files.o utils.o
```

### Makefile实例2
如果文件很多，那你不可能把每一个都写出来，于是就要用到变量，Makefile中的变量其实就是C中的宏。

同时Make有自动推导的能力，它看到一个file.o， 就会自动把file.c放入依赖文件中。


```
object = main.o kbd.o command.o display.o \
	insert.o search.o files.o utils.o

edit: $(object)
	gcc -o edit $(object)

main.o:defs.h
kbd.o: defs.h command.h
command.o: defs.h command.h
display.o: defs.h buffer.h
insert.o: defs.h buffer.h
search.o: defs.h buffer.h
files.o: defs.h buffer.h command.h
utils.o: defs.h

.PHONY:clean
clean:
	-rm edit $(object) # -表示如果有问题，不要管，go ahead
```

## Makefile组成
make -h: 显示相关帮助信息

Makefile中有5个部分：显式规则，隐式规则，变量，文件指示，注释   
文件指示：1. 引用另一个Makefile，2.指定Makefile的有效部分， 3.定义一个多行的命令  
+ 引用：include foo.make a.mk
+ 或者 make执行时，加-I, 指定目录

### Makefile的工作步骤：
1. 读入所有Makefile
2. 读入被include的其他Makefile
3. 初始化文件中的变量
4. 推导隐晦规则，并分析所有规则
5. 为所有目标创建依赖关系链
6. 根据依赖关系，决定哪些目标要重新生成
7. 执行生成命令

## Makefile书写规则
### 在哪里寻找文件的依赖文件
Makefile永远首先在当前目录找依赖文件，找不到才去其他地方。  

在一个工程中，有大量的源文件，不同的源文件可能要在不同目录下云找依赖关系。Makefile有个特殊变量VPATH：  
`VPATH = SRC:../headers`  
上面指定了2个目录，src, ../headers， Makefile会按这个顺序去找  

还有一个更细的办法：  
`vpath <pattern> <directories>`  
`vpath %.h ../headers`  
%.h 要在../headers中去找

`vpath <pattern>`  
清除pattern模式的搜寻目录

`vpath`  
清除所有搜寻目录

如果同一pattern有多个搜寻目录，那就按先后顺序来

### 伪目标
有时候我们想要生成多个目标，或者实现不同的编绎目的，就要用到伪目标了  
```
.PHONEY: pack clean
pack: main.o kbd.o

main.o: defs.h
kbd.o: defs.h command.h

clean:
    -rm *.o
```

### 静态规则
### 自动生成依赖关系

### 书写命令
#### 显示命令
调试Makefile时，想要它输出命令但不执行   
`make --just-print`  `make -n`  

用来跟踪Makefile执行情况: @表示不显示命令，只输出qwert   
`@echo qwert`

#### 命令执行
如果要让下一条命令在上一条的结果基础上执行，那这两条命令要放在一行  
`cd ~/Downloads; pwd`

#### 嵌套执行Make

### 变量
变量在使用时要加`$`, 最好用`() {}`括起来。如果要用`$`, 可以`$$`  

x = bar  
bar = y  
那么`$($(x))` 是y  
`=`， 定义变量的时候，右边可以是一个字符串，也可以是一个定义过的变量，甚至是一个未定义过的变量。这样，存在循环定义的风险。  

`x := $(y) bar`  
`y := go`  
那么`$($(x))` 是 bar. `:=` 的右边必须是一个字符串，或定义过的变量，这是推荐用法。  

x ?= bar  
如果x定义过了，那么什么也不做，没定义过就定义为bar  

x = a.c b.c  
x += d.c  
追加

#### 变量值替换
```
foo := a.o b.o c.o
FOO := $(foo:.o = .c)
clean:
    @echo $(FOO)
```
将foo中以.o结尾的字串换成以.c结尾的字串  

#### 目标变量
作用范围只在规则及连带规则内。  
```
prog: CFLAGS = -g
prog: a.o b.o
    gcc $(CFLAGS) -c $@ a.o b.o

a.o: a.c
    gcc $(CFLAGS) -c $@ a.c
```

#### 模式变量
把变量定义在符合某种模式的目标上  
```
%.o: CFLAGS = -g
...
```

#### 自动化变量
`$@ $<`这种就是自动化变量。与一般变量的区别是：一般变量在Makefile被读取的时候就初始化了，而自动化变量是在运行的时候才有。

#### override指示符
#### 多行变量与命令包


### 语法
#### 条件选择
```
ifeq ($(CC), gcc)
    objects = $(x)
else
    objects = $(y)
endif
```
类似的关键词还有ifneq, ifdef, ifndef  

#### 函数调用
`$(function variable1,variable2,...)`这是函数调用的基本形式。函数名与变量之间用空格分开，变量之间用`,`分开。注意不要有多余的空格

#### subst替换函数
```
comma = ,
empty = 
space = $(empty) $(empty)
foo := a.o b.o c.o
var := $(subst $(comma),$(space),$(foo))
echo $(var)
```

#### patsubst模式替换
```
$(patsubst %.o,%.c,a.o.o b.o)
```

#### strip
去掉str开头和结尾的空格

#### findstring
`$(findstring a,a b c)`
查找字符串，如是找到，返回a, 找不到返回空


#### filter
```
foo := a.c b.c c.s d.h
$(filter %.c %.s,$(foo))
```
用模式去过滤字符串，（可以有多个模式）， 返回符合模式的字符串。上面就返回`a.c b.c c.s`

#### filter-out
返过滤函数，返回去除pattern之后的字符串

#### sort
`$(sort a c d d b e)`  
按升序排，会去除重复。 a b c d e

##### word
`$(word 2,bar foo get)`  
取第2个单词

#### wordlist
`$(wordlist 2,3,bar foo get word)`  
取单词串，`foo get`

#### word
`$(word bar foo get word)` 统计单词个数为4

#### dir/notdir
`$(dir src/foo.c hacks)` 结果是`src/ ./`  
`$(notdir src/foo.c hacks)` 结果是`foo.c hacks`

#### basename/suffix
取前缀、后缀函数  
`$(basename src/foo.c hacks)` 结果是：src/foo hacks  
`$(suffix src/foo.c hacks)`   结果是：.c

#### addprefix/addsuffix
`$(addprefix src/,foo bar)` 结果：src/foo src/bar  
`$(addsuffix .c,foo bar)`   结果：foo.c bar.c

#### join连接函数
`$(join aaa bbb,111 222 333)` 把后面的单词相应地加入到前面的单词后面。结果是：aaa111 bbb222 333

#### foreach
`$(foreach n,$(list),$(text))` 把list中的每个字串取出赋给n, 用n去执行text表达式，结果是一个字符串。每次返回的字符串，组成一个新的字符串作为最后的结果。  
```
list := a b c
$(foreach n,$(list),$(n).o)
```
结果是：a.o b.o c.o

#### if
`$(if <condition>, <then>, <else then>)`

#### call
`$(call <exp>,<parm1>,<parm2>,<parm3>...)`  
将后面的各个参数传入exp中，exp的返回值就是call函数的返回值  
```
reverse := $(2) $(1)
$(call reverse,a,b)
```
结果：b a

#### origin
`$(origin var)` 告诉你变量是从哪来的。  

+ undefined：未定义
+ default:  
+ environment: 环境变量（并且-e参数没有找开）
+ file：     定义在makefile中
+ command line：定义在命令行中
+ override：    被override重新定义了
+ automatic：   自动化变量

```
bletch := foo
ifdef bletch
ifeq ($(origin bletch), file)
    bletch := FOO
endif
endif
```
结果：FOO

#### shell函数
就是在Makefile中执行shell函数  
`content := $(shell pwd)`

### make
+ make -n: 只找印命令，但不执行
+ make -q: 寻找目标，找不到，报错
+ make -t: 修改目标文件的日期，假装目标已经编绎过了
+ make -C: makefile的目录
+ make -d: 输出debug信息
+ make -e: 指明环境变量的值覆盖makefile中定义的变量的值
+ make -I: 指定一个目录，搜索被包含的makefile文件
+ make -r: 禁用隐式规则

## 隐式规则builtin-rule
Make有一个隐含规则库，如果我们没有写出生成目标的命令，它会去规则库中按顺序找合适的命令。有时候会有一些错误，比如对同一目标有多条隐含命令，但你想执行的命令更靠后。如果你不想执行隐含命令，就要显式写出来。

### 编绎C程序的隐含规则
.o目标文件会自动推导依赖文件.c， 并用
`$(CC) -c $(CPPFLAGS) $(CFLAGS)`

### 编绎CPP程序的隐含规则
.o文件会自动推导依赖文件.cc， 并用
`$(CXX) -c $(CPPFLAGS) $(CFLAGS)`














