## 使用外部的Googletest 指令
```
git clone https://github.com/google/googletest.git 
cd googletest
cmake CMakeLists.txt
make

cd .. #回到project目录下
cp -R googletest/googletest/include/ ./include #将googletest/googletest/include下的文件拷贝到当前目录的include文件夹
cp -R googletest/lib ./lib #将googletest/lib中的文件拷贝到当前目录下的lib文件夹下
```

# Windows 编程中

```
git clone https://github.com/google/googletest.git 
cd googletest
cmake CMakeLists.txt

使用visual studio打开googletest-distribution.sln工程，编译即可（debug和release都编译一下）
```
