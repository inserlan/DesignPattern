#pragma once
#include <iostream>

// 意图：保证一个类仅有一个实例，并提供一个访问它的全局访问点。
// 主要解决：一个全局使用的类频繁地创建与销毁。
// 何时使用：当您想控制实例数目，节省系统资源的时候。
// 如何解决：判断系统是否已经有这个单例，如果有则返回，如果没有则创建。
// 关键代码：构造函数是protected或private。
// 应用实例：Windows 是多进程多线程的，在操作一个文件的时候，就不可避免地出现多个进程或线程同时操作一个文件的现象，
//		所以所有文件的处理必须通过唯一的实例来进行。
// 优点： 1、在内存里只有一个实例，减少了内存的开销，尤其是频繁的创建和销毁实例（比如管理学院首页页面缓存）。
//		2、避免对资源的多重占用（比如写文件操作）。
// 缺点：没有接口，不能继承，与单一职责原则冲突，一个类应该只关心内部逻辑，而不关心外面怎么样来实例化。
// 注意事项：
//	1、单例类只能有一个实例。
//	2、单例类必须自己创建自己的唯一实例。
//	3、单例类必须给所有其他对象提供这一实例。
//	instance() 方法中需要使用同步锁, 防止多线程同时进入造成 instance 被多次实例化。

// before =========================================================
class GlobalClassBefore
{
	int m_value;
public:
	GlobalClassBefore(int v = 0) { m_value = v; }
	int get_value() { return m_value; }
	void set_value(int v) { m_value = v; }
};

// default initialization
GlobalClassBefore *global_ptr_before = nullptr;

void foo_before()
{
	// initialization on first use
	if (global_ptr_before == nullptr)
		global_ptr_before = new GlobalClassBefore;
	global_ptr_before->set_value(1);
	std::cout << "foo: global_ptr is " << global_ptr_before->get_value() << '\n';
}

void bar_before()
{
	// initialization on first use
	if (global_ptr_before == nullptr)
		global_ptr_before = new GlobalClassBefore;
	global_ptr_before->set_value(2);
	std::cout << "bar: global_ptr is " << global_ptr_before->get_value() << '\n';
}

void SingleTonBefore()
{
	if (global_ptr_before == nullptr)
		global_ptr_before = new GlobalClassBefore;
	std::cout << "main: global_ptr is " << global_ptr_before->get_value() << '\n';
	foo_before();
	bar_before();
}

// after =========================================================
class GlobalClassAfter
{
	int m_value;
	static GlobalClassAfter* s_instance;
	GlobalClassAfter(int v = 0) { m_value = v; }

public:
	int get_value() { return m_value; }
	void set_value(int v) { m_value = v; }
	static GlobalClassAfter* instance()
	{
		if (s_instance == nullptr)
			s_instance = new GlobalClassAfter;
		return s_instance;
	}
};

// Allocating and initializing GlobalClass's
// static data member.  The pointer is being
// allocated - not the object inself.
GlobalClassAfter* GlobalClassAfter::s_instance = nullptr;

void foo_after()
{
	GlobalClassAfter::instance()->set_value(1);
	std::cout << "foo: global_ptr is " << GlobalClassAfter::instance()->get_value() << '\n';
}

void bar_after()
{
	GlobalClassAfter::instance()->set_value(2);
	std::cout << "bar: global_ptr is " << GlobalClassAfter::instance()->get_value() << '\n';
}

void SingletonAfter()
{
	std::cout << "main: global_ptr is " << GlobalClassAfter::instance()->get_value() << '\n';
	foo_after();
	bar_after();
}
