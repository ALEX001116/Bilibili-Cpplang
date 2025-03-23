/*************************************************************************
    > File Name: 7.initialize_list.cpp
    > Author: hug
    > Mail: hug@haizeix.com
    > Created Time: 六  7/ 6 14:59:56 2024
 /************************************************************************/
 
 //初始化列表的注意事项：初始化列表中变量的执行顺序，只和这些变量在类中的定义顺序有关
 
 //为什么要使用初始化列表？*看下面test3
 
 /*为什么一定要使用初始化列表：效率问题。省去了赋值过程，调用的直接就是相关字段的构造函数*/
 

#include <iostream>
using namespace std;

namespace test1 {

class A {
public :
    A() : A(1, 1) {}//委托构造，默认赋值
    A(int x, int y) : x(x), y(y) {}//初始化列表
    void output() {
        cout << "(" << x << ", " << y << ")" << endl;
    }

private:
    int x, y;
};

int main() {
    A a(3, 4), b(101, 202), c;
    a.output();
    b.output();
    c.output();//（1，1）
    return 0;
}
} // test1


/********************************************/


namespace test2 {

class B {
public :
    B(int x) : x(x) {
        cout << this << " : Class B constructor" << endl;
    }
    int x;
};

class A {
public :
    A() : A(1, 1) {}
    A(int z) : y(z), x(z) {
        cout << "x : " << &x << endl;
        cout << "y : " << &y << endl;
    }
    A(int x, int y) : x(x), y(y) {}
    void output() {
        cout << "(" << x.x << ", " << y.x << ")" << endl;
    }

private:
    B x, y;//调用B类构造了x和y对象，类的组合
};

int main() {
    A a(5); // x = 6, y = 5
    a.output();
    return 0;
}

} // test2

/********************************************/

 /*为什么要使用初始化列表？*/
namespace test3 {

class B {
public :
    B() {
        cout << this << " default constructor" << endl;//①
    }
    B(int x) : x(x) {
        cout << this << " : Class B constructor" << endl;
    }
    int x;
};

class A {
public :
    A() : A(1, 1) {}
    A(int x, int y) : x(x), y(y) {}
    //初始化列表不只是对x和y进行了赋值，更重要的是完成了他俩的构造过程。系统直接调用了x和y相关的有参构造。即上面的Class B constructor
    
    //如果不用初始化列表，这里改用为this->x.x=z和this->y.x=z，会怎么样呢？编译不通过。为什么？
    //1.前面已经出现了有参构造，默认构造就会被删除
    //2.对象的生命周期，一定要先经历构造过程。但是在{}这个大括号里面，已经使用了this->x这个对象，但又没有显示地去调用有参构造，对于系统而言就一定会去调用有参构造的呀。
    //解决方法：①给上面的B类添加一个默认构造，看上面①
    //解决方法二（重点）：初始化列表
    void output() {
        cout << "(" << x.x << ", " << y.x << ")" << endl;
    }

private:
    B x, y;//通过B类创建了对象
};

int main() {
    A a(3, 4);
    a.output();
    return 0;
}

} // test3

int main() {
    // test1::main();
    // test2::main();
    test3::main();
    return 0;
}
