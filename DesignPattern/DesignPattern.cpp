// DesignPattern.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "FactoryMethod.h"
#include "AbstractFactory.h"
#include "Singleton.h"

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

	// 抽象工厂
	std::cout << "Design Pattern 3: Singleton =>>" << std::endl;
	SingletonAfter();
	std::cout << std::endl;
}