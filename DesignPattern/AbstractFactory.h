#pragma once
#include <iostream>

namespace DP_AF
{
	// 创建型：抽象工厂（超级工厂）
	// 意图：提供一个创建一系列相关或相互依赖对象的接口，而无需指定它们具体的类。
	// 主要解决：主要解决接口选择的问题。
	// 何时使用：系统的产品有多于一个的产品族，而系统只消费其中某一族的产品。
	// 如何解决：在一个产品族里面，定义多个产品。
	// 关键代码：在一个工厂里聚合多个同类产品。
	// 应用实例：工作了，为了参加一些聚会，肯定有两套或多套衣服吧，比如说有商务装（成套，一系列具体产品）、
	//		时尚装（成套，一系列具体产品），甚至对于一个家庭来说，可能有商务女装、商务男装、时尚女装、时尚男装，
	//		这些也都是成套的，即一系列具体产品。假设一种情况（现实中是不存在的，要不然，没法进入共产主义了，
	//		但有利于说明抽象工厂模式），在您的家中，某一个衣柜（具体工厂）只能存放某一种这样的衣服（成套，一系列具体产品），
	//		每次拿这种成套的衣服时也自然要从这个衣柜中取出了。用OO的思想去理解，所有的衣柜（具体工厂）都是衣柜类的（抽象工厂）某一个，
	//		而每一件成套的衣服又包括具体的上衣（某一具体产品），裤子（某一具体产品），这些具体的上衣其实也都是上衣（抽象产品），
	//		具体的裤子也都是裤子（另一个抽象产品）。
	// 优点：当一个产品族中的多个对象被设计成一起工作时，它能保证客户端始终只使用同一个产品族中的对象。
	// 缺点：产品族扩展非常困难，要增加一个系列的某一产品，既要在抽象的 Creator 里加代码，又要在具体的里面加代码。
	// 注意事项：产品族难扩展，产品等级易扩展。

	// 形状抽象父类
	class Shape
	{
	public:
		virtual void Draw() = 0;
	};

	// 形状实体子类1
	class Rectangle : public Shape
	{
	public:
		void Draw() override
		{
			std::cout << "Inside Rectangle::Draw() method." << std::endl;
		}
	};

	// 形状实体子类2
	class Square : public Shape
	{
	public:
		void Draw() override
		{
			std::cout << "Inside Square::Draw() method." << std::endl;
		}
	};

	// 形状实体子类3
	class Circle : public Shape
	{
	public:
		void Draw() override
		{
			std::cout << "Inside Circle::Draw() method." << std::endl;
		}
	};

	// 颜色抽象父类
	class Color
	{
	public:
		virtual void Fill() = 0;
	};

	// 颜色实体子类1
	class Red : public Color
	{
	public:
		void Fill() override
		{
			std::cout << "Inside Red::Fill() method." << std::endl;
		}
	};

	// 颜色实体子类2
	class Green : public Color
	{
	public:
		void Fill() override
		{
			std::cout << "Inside Green::Fill() method." << std::endl;
		}
	};

	// 颜色实体子类3
	class Blue : public Color
	{
	public:
		void Fill() override
		{
			std::cout << "Inside Blue::Fill() method." << std::endl;
		}
	};

	// 工厂抽象父类
	class AbstractFactory
	{
	public:
		virtual Shape* MakeShape(std::string shapeType) = 0;
		virtual Color* MakeColor(std::string colorType) = 0;
	};

	// 工厂形状实体子类
	class ShapeFactory : public AbstractFactory
	{
	public:
		Shape* MakeShape(std::string shapeType) override
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

		Color* MakeColor(std::string colorType) override
		{
			return nullptr;
		}
	};

	// 工厂颜色实体子类
	class ColorFactory : public AbstractFactory
	{
	public:
		Shape* MakeShape(std::string shapeType) override
		{
			return nullptr;
		}

		Color* MakeColor(std::string colorType) override
		{
			if (colorType == "Red")
			{
				return new Red();
			}
			else if (colorType == "Green")
			{
				return new Green();
			}
			else if (colorType == "Blue")
			{
				return new Blue();
			}
			else
			{
				return nullptr;
			}
		}
	};

	// 创建一个工厂创造器/生成器类，通过传递形状或颜色信息来获取工厂
	class FactoryProducer
	{
	public:
		static AbstractFactory* MakeFactory(std::string factoryType)
		{
			if (factoryType == "Shape")
			{
				return new ShapeFactory();
			}
			else if (factoryType == "Color")
			{
				return new ColorFactory();
			}
			else
			{
				return nullptr;
			}
		}
	};
}