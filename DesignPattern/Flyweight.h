#pragma once
#include <iostream>
using namespace std;

// 意图：运用共享技术有效地支持大量细粒度的对象。
// 主要解决：在有大量对象时，有可能会造成内存溢出，我们把其中共同的部分抽象出来，如果有相同的业务请求，直接返回在内存中已有的对象，避免重新创建。
// 何时使用： 1、系统中有大量对象。 2、这些对象消耗大量内存。
// 3、这些对象的状态大部分可以外部化。 4、这些对象可以按照内蕴状态分为很多组，当把外蕴对象从对象中剔除出来时，每一组对象都可以用一个对象来代替。
// 5、系统不依赖于这些对象身份，这些对象是不可分辨的。
// 如何解决：用唯一标识码判断，如果在内存中有，则返回这个唯一标识码所标识的对象。
// 关键代码：用 HashMap 存储这些对象。
// 应用实例： 1、JAVA 中的 String，如果有则返回，如果没有则创建一个字符串保存在字符串缓存池里面。 2、数据库的数据池。
// 优点：大大减少对象的创建，降低系统的内存，使效率提高。
// 缺点：提高了系统的复杂度，需要分离出外部状态和内部状态，而且外部状态具有固有化的性质，不应该随着内部状态的变化而变化，否则会造成系统的混乱。
// 使用场景： 1、系统有大量相似对象。 2、需要缓冲池的场景。
// 注意事项： 1、注意划分外部状态和内部状态，否则可能会引起线程安全问题。 2、这些类必须有一个工厂对象加以控制。

namespace DP_FlyweightBefore
{
	class Gazillion
	{
	public:
		Gazillion()
		{
			m_value_one = s_num / Y;
			m_value_two = s_num % Y;
			++s_num;
		}
		void report()
		{
			cout << m_value_one << m_value_two << ' ';
		}
		static const int X, Y;
	private:
		int m_value_one;
		int m_value_two;
		static int s_num;
	};

	const int Gazillion::X = 6, Gazillion::Y = 10;
	int Gazillion::s_num = 0;

	void FlyweightExampleBefore()
	{
		Gazillion matrix[Gazillion::X][Gazillion::Y];
		for (int i = 0; i < Gazillion::X; i++)
		{
			for (int j = 0; j < Gazillion::Y; j++)
			{
				matrix[i][j].report();
			}
			cout << '\n';
		}
	}
}

namespace DP_FlyweightAfter
{
	class Gazillion
	{
	public:
		Gazillion(int value_one)
		{
			m_value_one = value_one;
			cout << "ctor: " << m_value_one << '\n';
		}
		~Gazillion()
		{
			cout << m_value_one << ' ';
		}
		void report(int value_two)
		{
			cout << m_value_one << value_two << ' ';
		}
	private:
		int m_value_one;
	};

	class Factory
	{
	public:
		static Gazillion *get_fly(int in)
		{
			if (!s_pool[in])
				s_pool[in] = new Gazillion(in);
			return s_pool[in];
		}
		static void clean_up()
		{
			cout << "dtors: ";
			for (int i = 0; i < X; i++)
			{
				if (s_pool[i])
					delete s_pool[i];
			}
			cout << '\n';
		}
		static const int X, Y;
	private:
		static Gazillion *s_pool[];
	};

	const int Factory::X = 6, Factory::Y = 10;
	Gazillion *Factory::s_pool[] =
	{
	  0, 0, 0, 0, 0, 0
	};

	void FlyweightExampleAfter()
	{
		for (int i = 0; i < Factory::X; ++i)
		{
			for (int j = 0; j < Factory::Y; ++j)
				Factory::get_fly(i)->report(j);
			cout << '\n';
		}
		Factory::clean_up();
	}
}
