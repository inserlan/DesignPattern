// DesignPattern.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "FactoryMethod.h"
#include "AbstractFactory.h"
#include "Singleton.h"
#include "Builder.h"
#include "Prototype.h"
#include "ObjectPool.h"

int main()
{
	// 工厂方法
	std::cout << "Design Pattern 1: Factory Method =>>" << std::endl;
	FactoryMethodAfter();
	std::cout << std::endl;

	// 抽象工厂
	std::cout << "Design Pattern 2: Abstract Factory =>>" << std::endl;
	AbstractFactoryAfter();
	std::cout << std::endl;

	// 单件
	std::cout << "Design Pattern 3: Singleton =>>" << std::endl;
	SingletonAfter();
	std::cout << std::endl;

	// 建造者
	std::cout << "Design Pattern 4: Builder =>>" << std::endl;
	BuliderExample();
	std::cout << std::endl;

	// 原型
	std::cout << "Design Pattern 5: Prototype =>>" << std::endl;
	PrototypeExample();
	std::cout << std::endl;

	// 对象池
	std::cout << "Design Pattern 6: Object Pool =>>" << std::endl;
	ObjectPoolExample();
	std::cout << std::endl;
}