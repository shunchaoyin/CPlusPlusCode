以上实现一个单例的模板基类，使用方法如例子所示意，子类需要将自己作为模板参数T 传递给 Singleton<T> 模板; 同时需要将基类声明为友元，这样才能调用子类的私有构造函数。

基类模板的实现要点是：

1、基类构造函数需要是 protected，这样子类才能继承；

2、使用了奇异递归模板模式CRTP(Curiously recurring template pattern

3、)get instance 方法和 2.2.3 的static local方法一个原理。

4、在这里基类的析构函数可以不需要 virtual ，因为子类在应用中只会用 Derived 类型，保证了析构时和构造时的类型一致

参考链接：
https://blog.csdn.net/wteruiycbqqvwt/article/details/124852912
