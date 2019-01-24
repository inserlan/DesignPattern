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
#include "Composite.h"
#include "Decorator.h"
#include "Facade.h"
#include "Flyweight.h"
#include "Proxy.h"
#include "ChainOfResponsibility.h"
#include "Command.h"
#include "Interpreter.h"

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
	std::cout << "Design Pattern 8: Adapter =>>" << std::endl;
	DP_Bridge::BridgeExample();
	std::cout << std::endl;

	// 组合
	std::cout << "Design Pattern 9: Composite =>>" << std::endl;
	DP_Composite::CompositeExample();
	std::cout << std::endl;

	// 装饰者
	std::cout << "Design Pattern 10: Decorator =>>" << std::endl;
	DP_DecoratorBefore::DecoratorBefore();
	DP_DecoratorAfter::DecoratorAfter();
	std::cout << std::endl;

	// 外观
	std::cout << "Design Pattern 11: Facade =>>" << std::endl;
	DP_Facade::FacadeExample();
	std::cout << std::endl;

	// 享元
	std::cout << "Design Pattern 12: Flyweight =>>" << std::endl;
	DP_FlyweightBefore::FlyweightExampleBefore();
	DP_FlyweightAfter::FlyweightExampleAfter();
	std::cout << std::endl;

	// 代理
	std::cout << "Design Pattern 13: Proxy =>>" << std::endl;
	DP_ProxyBefore::ProxyExampleBefore();
	DP_ProxyAfter::ProxyExampleAfter();
	std::cout << std::endl;

	// 责任链
	std::cout << "Design Pattern 14: ChainOfResponsibility =>>" << std::endl;
	DP_ChainOfResponsibility::CORExample();
	std::cout << std::endl;

	// 命令
	std::cout << "Design Pattern 15: Command =>>" << std::endl;
	DP_CommandBefore::CommandExampleBefore();
	DP_CommandAfter::CommandExampleAfter();
	std::cout << std::endl;

	// 解释器
	std::cout << "Design Pattern 16: Interpreter =>>" << std::endl;
	DP_Interpreter::InterpreterExample();
	std::cout << std::endl;
}