## 1.2 函数与参数
形参：formal parameter； 实参：actual parameter； 引用参数：reference parameter；
签名（signature）： 是由这个函数的形参类型和形参个数决定的。同名函数不能有同样的签名；
Practice见代码；

## 1.3 异常

## 1.4 动态储存空间分配
二维数组列为5：

```cpp
char (*c)[5];
try{
    c = new char[n][5];
}
catch(bad_allc){
    cerr<<"out of memory"<<endl;
    exit(1);
}



```