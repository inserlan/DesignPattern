// DesignPattern.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "FactoryMethod.h"
#include "AbstractFactory.h"

void FactoryMethodExample()
{
	// 使用工厂，通过传递类型信息来获取实体类的对象。
	DP_FM::ShapeFactory factory;
	DP_FM::Shape* shape1 = factory.MakeShape("Rectangle");
	if (shape1 != nullptr)
	{
		shape1->Draw();
		delete shape1;
	}
	DP_FM::Shape* shape2 = factory.MakeShape("Square");
	if (shape2 != nullptr)
	{
		shape2->Draw();
		delete shape2;
	}
	DP_FM::Shape* shape3 = factory.MakeShape("Circle");
	if (shape3 != nullptr)
	{
		shape3->Draw();
		delete shape3;
	}
}

void AbstractFactoryExample()
{
	// 获取形状工厂
	DP_AF::AbstractFactory* factoryShape = DP_AF::FactoryProducer::MakeFactory("Shape");
	DP_AF::Shape* shape1 = factoryShape->MakeShape("Rectangle");
	if (shape1 != nullptr)
	{
		shape1->Draw();
		delete shape1;
	}
	DP_AF::Shape* shape2 = factoryShape->MakeShape("Square");
	if (shape2 != nullptr)
	{
		shape2->Draw();
		delete shape2;
	}
	DP_AF::Shape* shape3 = factoryShape->MakeShape("Circle");
	if (shape3 != nullptr)
	{
		shape3->Draw();
		delete shape3;
	}

	// 获取颜色工厂
	DP_AF::AbstractFactory* factoryColor = DP_AF::FactoryProducer::MakeFactory("Color");
	DP_AF::Color* color1 = factoryColor->MakeColor("Red");
	if (color1 != nullptr)
	{
		color1->Fill();
		delete color1;
	}
	DP_AF::Color* color2 = factoryColor->MakeColor("Green");
	if (color2 != nullptr)
	{
		color2->Fill();
		delete color2;
	}
	DP_AF::Color* color3 = factoryColor->MakeColor("Blue");
	if (color3 != nullptr)
	{
		color3->Fill();
		delete color3;
	}

	delete factoryShape;
	delete factoryColor;
}

int main()
{
	// 工厂方法
	std::cout << "Design Pattern 1: Factory Method =>>" << std::endl;
	FactoryMethodExample();
	std::cout << std::endl;

	// 抽象工厂
	std::cout << "Design Pattern 2: Abstract Factory =>>" << std::endl;
	AbstractFactoryExample();
	std::cout << std::endl;
}