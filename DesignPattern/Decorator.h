//#pragma once
//#include <iostream>
//using namespace std;
//
//// 意图：动态地给一个对象添加一些额外的职责。就增加功能来说，装饰器模式相比生成子类更为灵活。
//// 主要解决：一般的，我们为了扩展一个类经常使用继承方式实现，由于继承为类引入静态特征，并且随着扩展功能的增多，子类会很膨胀。
//// 何时使用：在不想增加很多子类的情况下扩展类。
//// 如何解决：将具体功能职责划分，同时继承装饰者模式。
//// 关键代码： 1、Component 类充当抽象角色，不应该具体实现。 2、修饰类引用和继承 Component 类，具体扩展类重写父类方法。
//// 应用实例： 1、孙悟空有 72 变，当他变成"庙宇"后，他的根本还是一只猴子，但是他又有了庙宇的功能。
//// 2、不论一幅画有没有画框都可以挂在墙上，但是通常都是有画框的，并且实际上是画框被挂在墙上。在挂在墙上之前，画可以被蒙上玻璃，装到框子里；这时画、玻璃和画框形成了一个物体。
//// 优点：装饰类和被装饰类可以独立发展，不会相互耦合，装饰模式是继承的一个替代模式，装饰模式可以动态扩展一个实现类的功能。
//// 缺点：多层装饰比较复杂。
//// 使用场景： 1、扩展一个类的功能。 2、动态增加功能，动态撤销。
//// 注意事项：可代替继承。
//
//// before
//class A {
//public:
//	virtual void do_it() {
//		cout << 'A';
//	}
//};
//
//class AwithX : public A {
//public:
//	/*virtual*/
//	void do_it() {
//		A::do_it();
//		do_X();
//	};
//private:
//	void do_X() {
//		cout << 'X';
//	}
//};
//
//class AwithY : public A {
//public:
//	/*virtual*/
//	void do_it() {
//		A::do_it();
//		do_Y();
//	}
//protected:
//	void do_Y() {
//		cout << 'Y';
//	}
//};
//
//class AwithZ : public A {
//public:
//	/*virtual*/
//	void do_it() {
//		A::do_it();
//		do_Z();
//	}
//protected:
//	void do_Z() {
//		cout << 'Z';
//	}
//};
//
//class AwithXY : public AwithX, public AwithY
//{
//public:
//	/*virtual*/
//	void do_it() {
//		AwithX::do_it();
//		AwithY::do_Y();
//	}
//};
//
//class AwithXYZ : public AwithX, public AwithY, public AwithZ
//{
//public:
//	/*virtual*/
//	void do_it() {
//		AwithX::do_it();
//		AwithY::do_Y();
//		AwithZ::do_Z();
//	}
//};
//
//int main() {
//	AwithX anX;
//	AwithXY anXY;
//	AwithXYZ anXYZ;
//	anX.do_it();
//	cout << '\n';
//	anXY.do_it();
//	cout << '\n';
//	anXYZ.do_it();
//	cout << '\n';
//}
//
//// after
//
//class I {
//public:
//	virtual ~I() {}
//	virtual void do_it() = 0;
//};
//
//class A : public I {
//public:
//	~A() {
//		cout << "A dtor" << '\n';
//	}
//	/*virtual*/
//	void do_it() {
//		cout << 'A';
//	}
//};
//
//class D : public I {
//public:
//	D(I *inner) {
//		m_wrappee = inner;
//	}
//	~D() {
//		delete m_wrappee;
//	}
//	/*virtual*/
//	void do_it() {
//		m_wrappee->do_it();
//	}
//private:
//	I *m_wrappee;
//};
//
//class X : public D {
//public:
//	X(I *core) : D(core) {}
//	~X() {
//		cout << "X dtor" << "   ";
//	}
//	/*virtual*/
//	void do_it() {
//		D::do_it();
//		cout << 'X';
//	}
//};
//
//class Y : public D {
//public:
//	Y(I *core) : D(core) {}
//	~Y() {
//		cout << "Y dtor" << "   ";
//	}
//	/*virtual*/
//	void do_it() {
//		D::do_it();
//		cout << 'Y';
//	}
//};
//
//class Z : public D {
//public:
//	Z(I *core) : D(core) {}
//	~Z() {
//		cout << "Z dtor" << "   ";
//	}
//	/*virtual*/
//	void do_it() {
//		D::do_it();
//		cout << 'Z';
//	}
//};
//
//int main() {
//	I *anX = new X(new A);
//	I *anXY = new Y(new X(new A));
//	I *anXYZ = new Z(new Y(new X(new A)));
//	anX->do_it();
//	cout << '\n';
//	anXY->do_it();
//	cout << '\n';
//	anXYZ->do_it();
//	cout << '\n';
//	delete anX;
//	delete anXY;
//	delete anXYZ;
//}