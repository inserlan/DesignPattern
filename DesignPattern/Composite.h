#pragma once
#include <iostream>
#include <vector>
using namespace std;

// 意图：将对象组合成树形结构以表示"部分-整体"的层次结构。组合模式使得用户对单个对象和组合对象的使用具有一致性。
// 主要解决：它在我们树型结构的问题中，模糊了简单元素和复杂元素的概念，客户程序可以向处理简单元素一样来处理复杂元素，从而使得客户程序与复杂元素的内部结构解耦。
// 何时使用： 1、您想表示对象的部分 - 整体层次结构（树形结构）。 2、您希望用户忽略组合对象与单个对象的不同，用户将统一地使用组合结构中的所有对象。
// 如何解决：树枝和叶子实现统一接口，树枝内部组合该接口。
// 关键代码：树枝内部组合该接口，并且含有内部属性 List，里面放 Component。
// 应用实例： 1、算术表达式包括操作数、操作符和另一个操作数，其中，另一个操作符也可以是操作数、操作符和另一个操作数。 
// 2、在 JAVA AWT 和 SWING 中，对于 Button 和 Checkbox 是树叶，Container 是树枝。
// 优点： 1、高层模块调用简单。 2、节点自由增加。
// 缺点：在使用组合模式时，其叶子和树枝的声明都是实现类，而不是接口，违反了依赖倒置原则。
// 使用场景：部分、整体场景，如树形菜单，文件、文件夹的管理。
// 注意事项：定义时为具体类。

namespace DP_Composite
{
	// 2. Create an "interface" (lowest common denominator)
	class Component
	{
	public:
		virtual void traverse() = 0;
	};

	class Leaf : public Component
	{
		// 1. Scalar class   3. "isa" relationship
		int value;
	public:
		Leaf(int val)
		{
			value = val;
		}
		void traverse()
		{
			cout << value << ' ';
		}
	};

	class Composite : public Component
	{
		// 1. Vector class   3. "isa" relationship
		vector <Component*> children; // 4. "container" coupled to the interface
	public:
		// 4. "container" class coupled to the interface
		void add(Component *ele)
		{
			children.push_back(ele);
		}
		void traverse()
		{
			for (size_t i = 0; i < children.size(); i++)
				// 5. Use polymorphism to delegate to children
				children[i]->traverse();
		}
	};

	void CompositeExample()
	{
		Composite containers[4];

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 3; j++)
				containers[i].add(new Leaf(i * 3 + j));

		for (int i = 1; i < 4; i++)
			containers[0].add(&(containers[i]));

		for (int i = 0; i < 4; i++)
		{
			containers[i].traverse();
			cout << endl;
		}
	}
}