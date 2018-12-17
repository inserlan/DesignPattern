#pragma once
#include <iostream>

// �����ͣ���������
// ��ͼ������һ����������Ľӿڣ����������Լ�����ʵ������һ�������࣬����ģʽʹ�䴴�������ӳٵ�������С�
// ��Ҫ�������Ҫ����ӿ�ѡ������⡣
// ��ʱʹ�ã�������ȷ�ؼƻ���ͬ�����´�����ͬʵ��ʱ��
// ��ν������������ʵ�ֹ����ӿڣ����ص�Ҳ��һ������Ĳ�Ʒ��
// �ؼ����룺����������������ִ�С�
// Ӧ��ʵ���� ����Ҫһ������������ֱ�Ӵӹ������������������ȥ��������������ô�������ģ��Լ������������ľ���ʵ�֡�
// �ŵ㣺 1��һ���������봴��һ������ֻҪ֪�������ƾͿ����ˡ�
//		2����չ�Ըߣ����������һ����Ʒ��ֻҪ��չһ��������Ϳ��ԡ�
//		3�����β�Ʒ�ľ���ʵ�֣�������ֻ���Ĳ�Ʒ�Ľӿڡ�
// ȱ�㣺ÿ������һ����Ʒʱ������Ҫ����һ��������Ͷ���ʵ�ֹ�����ʹ��ϵͳ����ĸ����ɱ����ӣ�
//		��һ���̶���������ϵͳ�ĸ��Ӷȣ�ͬʱҲ������ϵͳ��������������Ⲣ����ʲô���¡�
// ע�������Ϊһ�ִ�����ģʽ�����κ���Ҫ���ɸ��Ӷ���ĵط���������ʹ�ù�������ģʽ��
//		��һ����Ҫע��ĵط����Ǹ��Ӷ����ʺ�ʹ�ù���ģʽ�����򵥶����ر���ֻ��Ҫͨ�� new �Ϳ�����ɴ����Ķ���
//		����ʹ�ù���ģʽ�����ʹ�ù���ģʽ������Ҫ����һ�������࣬������ϵͳ�ĸ��Ӷȡ�

// ������
class Shape
{
public:
	virtual void Draw() = 0;
	// �����ڸ����д���static������Ϊ����������Ҳ�����¿�һ��������
	static Shape* MakeShape(std::string shapeType);
};

// ʵ������1
class Rectangle : public Shape
{
public:
	void Draw() override
	{
		std::cout << "Inside Rectangle::Draw() method." << std::endl;
	}
};

// ʵ������2
class Square : public Shape
{
public:
	void Draw() override
	{
		std::cout << "Inside Square::Draw() method." << std::endl;
	}
};

// ʵ������3
class Circle : public Shape
{
public:
	void Draw() override
	{
		std::cout << "Inside Circle::Draw() method." << std::endl;
	}
};

Shape* Shape::MakeShape(std::string shapeType)
{
	if (shapeType == "Rectangle")
		return new Rectangle();
	else if (shapeType == "Square")
		return new Square();
	else
		return new Circle();
}

// ����һ�����������ɻ��ڸ�����Ϣ��ʵ����Ķ���
class ShapeFactory
{
public:
	Shape* MakeShape(std::string shapeType)
	{
		if (shapeType == "Rectangle")
			return new Rectangle();
		else if (shapeType == "Square")
			return new Square();
		else
			return new Circle();
	}
};

void FactoryMethodBefore()
{
	Rectangle* shape1 = new Rectangle();
	shape1->Draw();
	Square* shape2 = new Square();
	shape2->Draw();
	Circle* shape3 = new Circle();
	shape3->Draw();
}

void FactoryMethodAfter()
{
	// ʹ�ù�����ͨ������������Ϣ����ȡʵ����Ķ���
	// ���������̳���Shape������	
	Shape* shape1 = Shape::MakeShape("Rectangle");
	shape1->Draw();
	ShapeFactory factory;
	Shape* shape2 = factory.MakeShape("Square");
	shape2->Draw();
	Shape* shape3 = factory.MakeShape("Circle");
	shape3->Draw();
}