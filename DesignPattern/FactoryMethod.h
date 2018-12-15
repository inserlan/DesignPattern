#pragma once
#include <iostream>

namespace DP_FM
{
	// 创建型：工厂方法
	// 意图：定义一个创建对象的接口，让其子类自己决定实例化哪一个工厂类，工厂模式使其创建过程延迟到子类进行。
	// 主要解决：主要解决接口选择的问题。
	// 何时使用：我们明确地计划不同条件下创建不同实例时。
	// 如何解决：让其子类实现工厂接口，返回的也是一个抽象的产品。
	// 关键代码：创建过程在其子类执行。
	// 应用实例： 您需要一辆汽车，可以直接从工厂里面提货，而不用去管这辆汽车是怎么做出来的，以及这个汽车里面的具体实现。
	// 优点： 1、一个调用者想创建一个对象，只要知道其名称就可以了。
	//		2、扩展性高，如果想增加一个产品，只要扩展一个工厂类就可以。
	//		3、屏蔽产品的具体实现，调用者只关心产品的接口。
	// 缺点：每次增加一个产品时，都需要增加一个具体类和对象实现工厂，使得系统中类的个数成倍增加，
	//		在一定程度上增加了系统的复杂度，同时也增加了系统具体类的依赖。这并不是什么好事。
	// 注意事项：作为一种创建类模式，在任何需要生成复杂对象的地方，都可以使用工厂方法模式。
	//		有一点需要注意的地方就是复杂对象适合使用工厂模式，而简单对象，特别是只需要通过 new 就可以完成创建的对象，
	//		无需使用工厂模式。如果使用工厂模式，就需要引入一个工厂类，会增加系统的复杂度。

	// 抽象父类
	class Shape
	{
	public:
		virtual void Draw() = 0;
	};

	// 实体子类1
	class Rectangle : public Shape
	{
	public:
		void Draw() override
		{
			std::cout << "Inside Rectangle::Draw() method." << std::endl;
		}
	};

	// 实体子类2
	class Square : public Shape
	{
	public:
		void Draw() override
		{
			std::cout << "Inside Square::Draw() method." << std::endl;
		}
	};

	// 实体子类3
	class Circle : public Shape
	{
	public:
		void Draw() override
		{
			std::cout << "Inside Circle::Draw() method." << std::endl;
		}
	};

	// 创建一个工厂，生成基于给定信息的实体类的对象。
	class ShapeFactory
	{
	public:
		Shape* MakeShape(std::string shapeType)
		{
			if (shapeType == "Rectangle")
			{
				return new Rectangle();
			}
			else if (shapeType == "Square")
			{
				return new Square();
			}
			else if (shapeType == "Circle")
			{
				return new Circle();
			}
			else
			{
				return nullptr;
			}
		}
	};
}