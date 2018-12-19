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
#include "Adapter.h"
#include "Bridge.h"

int main()
{
	// 工厂方法
	std::cout << "Design Pattern 1: Factory Method =>>" << std::endl;
	DP_Factory::FactoryMethodAfter();
	std::cout << std::endl;

	// 抽象工厂
	std::cout << "Design Pattern 2: Abstract Factory =>>" << std::endl;
	DP_AbsFac::AbstractFactoryAfter();
	std::cout << std::endl;

	// 单件
	std::cout << "Design Pattern 3: Singleton =>>" << std::endl;
	DP_Singleton::SingletonAfter();
	std::cout << std::endl;

	// 建造者
	std::cout << "Design Pattern 4: Builder =>>" << std::endl;
	DP_Builder::BuliderExample();
	std::cout << std::endl;

	// 原型
	std::cout << "Design Pattern 5: Prototype =>>" << std::endl;
	DP_Prototype::PrototypeExample();
	std::cout << std::endl;

	// 对象池
	std::cout << "Design Pattern 6: Object Pool =>>" << std::endl;
	DP_ObjPool::ObjectPoolExample();
	std::cout << std::endl;

	// 适配器
	std::cout << "Design Pattern 7: Adapter =>>" << std::endl;
	DP_Adapter1::AdapterExample();
	DP_Adapter2::AdapterExample();
	std::cout << std::endl;

	// 桥接
	std::cout << "Design Pattern 7: Adapter =>>" << std::endl;
	DP_Bridge::BridgeExample();
	std::cout << std::endl;
}