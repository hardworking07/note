# github学习笔记
## git的作用
git是一个版本控制工具，每当文件修改到一定程度，就保存一个快照commit, 如果以后发现有问题，可以从最近的一个commit恢复。

## linux git install
```
sudo apt-get install git
git config --global usr.name "hardworking07"
git config --global usr.email "yaolongyun2012@gmail.com"
```
## 注册github
+ 注册github
+ 需要一个ssh key
+ ssh-keygen -t rsa -C "yaolongyun2012@gmail.com"
+ gtihub上的setting页面add ssh key

## 下载别人的项目
git clone ...

## 创建自己的项目

## 创建并提交文件
```
mkdir learngit
cd ./learngit
git init
git add git.md
git commit -m "write a git.md" // 暂存区文件提交到版本库
```
git有三个地点，工作区，暂存区，分支。在这里learngit文件夹就是工作区，
执行add之后，文件被交到暂存区即stage, commit后文件被交到分支。

## 查看仓库的状态
```
git status
git diff: 查看工作区和暂存区的不同
git diff HEAD -- git.md: 比较工作区和版本库git.md的不同
vimdiff file1 file2: 用vim打开并显示不同
```

## 时光穿梭
```
git log: 查看提交历史，以便回到哪个版本
git reset --hard commit_id: 回到的版本号
git reset --hard HEAD^: 上一个版本
git reflog: 查看命令历史，以便回到未来

git checkout -- git.md: 放弃工作区的修改，回到最近的状态（暂存区或版本库）
git reset HEAD git.md: 放弃暂存区的修改，文件就是当前工作区的样子
git reset --hard commit_id: 放弃版本库的修改
```

## 删除文件
只要记住删除也是一种修改操作, 但要小心，因为只能回到最近的一个版本了
```
rm git.md
git rm git.md // like git add git.md
git commit -m "delete a file"
git reset HEAD git.md
git checkout -- git.md // 只能回到最近的一个版本了
```

## 建立远程仓库

## 添加远程库
+ 在github上建立一个仓库，如learngit
+ `git remote add origin git@github.com:hardworking07/learngit.git`
+ `git push -u origin master` // -u 关联本地和远程库
+ 以后推送`git push origin master`

## 从远程库clone
`git clone git@.....`

## 创建与合并分支
比如你有一个程序1.0, 现在你正在进2.0开发，但不能马上提交到github, 因为未完成的版本会让使用1.0的人出问题，可是如果不提交代码版本如何管理？

方法就是：创建一个分支，就像个平行宇宙，互不干扰。完成后再合并。

```
git brank dev : create a branch named dev
git checkout dev: 接下的修改都是在dev分支下进行的，不影响master
.........
git checkout master
git merge dev: 合并dev到当前分支，即master
git branch -d dev: delete branch dev
git branch: 查看branch
git merge --no-ff -m "merge with no-ff" dev: 可以看出合并过
```

如果发生冲突呢？比如dev, master都修改了一句话，但不一样怎么办？
```
发生冲突时，就打开冲突文件修改
git add git.md
git commit -m "..."
git log --graph --pretty=oneline : 查看分支合并图
```

当前分支的工作没有提交，却要切换到另一个分支，会出错提示.
```
git stash
git stash pop
git stash list
```

## 标签
所谓打标签，其实也是一种快照。发布一个版本时打个快照.
```
git tag v1.0 : 建一个标签，默认HEAD, 也可指定commit_id
git tag -a v1.0 -m "version 1.0": 带说明的标签
git tag : 查看标签
git tag -d v1.0: delete
git show v1.0
```