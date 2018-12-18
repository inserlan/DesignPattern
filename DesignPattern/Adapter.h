#pragma once
#include <iostream>	

// 意图：将一个类的接口转换成客户希望的另外一个接口。适配器模式使得原本由于接口不兼容而不能一起工作的那些类可以一起工作。
// 主要解决：主要解决在软件系统中，常常要将一些"现存的对象"放到新的环境中，而新环境要求的接口是现对象不能满足的。
// 何时使用： 1、系统需要使用现有的类，而此类的接口不符合系统的需要。
//    2、想要建立一个可以重复使用的类，用于与一些彼此之间没有太大关联的一些类，包括一些可能在将来引进的类一起工作，这些源类不一定有一致的接口。
//    3、通过接口转换，将一个类插入另一个类系中。（比如老虎和飞禽，现在多了一个飞虎，在不增加实体的需求下，增加一个适配器，在里面包容一个虎对象，实现飞的接口。）
// 如何解决：继承或依赖（推荐）。
// 关键代码：适配器继承或依赖已有的对象，实现想要的目标接口。
// 应用实例： 1、美国电器 110V，中国 220V，就要有一个适配器将 110V 转化为 220V。
//    2、JAVA JDK 1.1 提供了 Enumeration 接口，而在 1.2 中提供了 Iterator 接口，想要使用 1.2 的 JDK，
//    则要将以前系统的 Enumeration 接口转化为 Iterator 接口，这时就需要适配器模式。 
//    3、在 LINUX 上运行 WINDOWS 程序。 4、JAVA 中的 jdbc。
// 优点： 1、可以让任何两个没有关联的类一起运行。 2、提高了类的复用。 3、增加了类的透明度。 4、灵活性好。
// 缺点： 1、过多地使用适配器，会让系统非常零乱，不易整体进行把握。比如，明明看到调用的是 A 接口，
// 其实内部被适配成了 B 接口的实现，一个系统如果太多出现这种情况，无异于一场灾难。因此如果不是很有必要，可以不使用适配器，而是直接对系统进行重构。
// 2.由于 JAVA 至多继承一个类，所以至多只能适配一个适配者类，而且目标类必须是抽象类。
// 使用场景：有动机地修改一个正常运行的系统的接口，这时应该考虑使用适配器模式。
// 注意事项：适配器不是在详细设计时添加的，而是解决正在服役的项目的问题。

namespace DP_Adapter1
{
	typedef int Coordinate;
	typedef int Dimension;

	// Desired interface
	class Rectangle
	{
	public:
		virtual void draw() = 0;
	};

	// Legacy component
	class LegacyRectangle
	{
	public:
		LegacyRectangle(Coordinate x1, Coordinate y1, Coordinate x2, Coordinate y2)
		{
			x1_ = x1;
			y1_ = y1;
			x2_ = x2;
			y2_ = y2;
			std::cout << "LegacyRectangle:  create.  (" << x1_ << "," << y1_ << ") => ("
				<< x2_ << "," << y2_ << ")" << std::endl;
		}

		void oldDraw()
		{
			std::cout << "LegacyRectangle:  oldDraw.  (" << x1_ << "," << y1_ <<
				") => (" << x2_ << "," << y2_ << ")" << std::endl;
		}

	private:
		Coordinate x1_;
		Coordinate y1_;
		Coordinate x2_;
		Coordinate y2_;
	};

	// Adapter wrapper
	class RectangleAdapter : public Rectangle, private LegacyRectangle
	{
	public:
		RectangleAdapter(Coordinate x, Coordinate y, Dimension w, Dimension h)
			: LegacyRectangle(x, y, x + w, y + h)
		{
			std::cout << "RectangleAdapter: create.  (" << x << "," << y <<
				"), width = " << w << ", height = " << h << std::endl;
		}
		virtual void draw()
		{
			std::cout << "RectangleAdapter: draw." << std::endl;
			oldDraw();
		}
	};

	void AdapterExample()
	{
		Rectangle *r = new RectangleAdapter(120, 200, 60, 40);
		r->draw();
	}
}


// 1. Specify the new desired interface
// 2. Design a “wrapper” class that can “impedance match” the old to the new
// 3. The client uses(is coupled to) the new interface
// 4. The adapter / wrapper “maps” to the legacy implementation
namespace DP_Adapter2
{
	class ExecuteInterface
	{
	public:
		// 1. Specify the new interface
		virtual ~ExecuteInterface() {}
		virtual void execute() = 0;
	};

	// 2. Design a "wrapper" or "adapter" class
	template<typename TYPE>
	class ExecuteAdapter : public ExecuteInterface
	{
	public:
		ExecuteAdapter(TYPE *o, void(TYPE:: *m)())
		{
			object = o;
			method = m;
		}
		~ExecuteAdapter()
		{
			delete object;
		}

		// 4. The adapter/wrapper "maps" the new to the legacy implementation
		void execute() override
		{
			(object->*method)();
		}
	private:
		TYPE *object;		// ptr-to-object attribute
		void(TYPE:: *method)();	/* the old */     // ptr-to-member-function attribute
	};

	// The old: three totally incompatible classes
	// no common base class
	class Fea 
	{
	public:
		// no hope of polymorphism
		~Fea() 
		{
			std::cout << "Fea::dtor" << std::endl;
		}
		void doThis() 
		{
			std::cout << "Fea::doThis()" << std::endl;
		}
	};

	class Feye
	{
		public:~Feye()
		{
			std::cout << "Feye::dtor" << std::endl;
		}
		void doThat()
		{
			std::cout << "Feye::doThat()" << std::endl;
		}
	};

	class Pheau 
	{
	public:
		~Pheau()
		{
			std::cout << "Pheau::dtor" << std::endl;
		}
		void doTheOther()
		{
			std::cout << "Pheau::doTheOther()" << std::endl;
		}
	};

	// the new is returned
	ExecuteInterface **initialize()
	{
		ExecuteInterface **array = new ExecuteInterface*[3];
		// the old is below
		array[0] = new ExecuteAdapter<Fea>(new Fea(), &Fea::doThis);
		array[1] = new ExecuteAdapter<Feye>(new Feye(), &Feye::doThat);
		array[2] = new ExecuteAdapter<Pheau>(new Pheau(), &Pheau::doTheOther);
		return array;
	}

	void AdapterExample()
	{
		ExecuteInterface **objects = initialize();
		for (size_t i = 0; i < 3; i++)
		{
			objects[i]->execute();
		}

		// 3. Client uses the new (polymporphism)
		for (size_t i = 0; i < 3; i++)
		{
			delete objects[i];
		}

		delete objects;
	}
}