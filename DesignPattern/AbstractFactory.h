#pragma once
#include <iostream>

namespace DP_AF
{
	// �����ͣ����󹤳�������������
	// ��ͼ���ṩһ������һϵ����ػ��໥��������Ľӿڣ�������ָ�����Ǿ�����ࡣ
	// ��Ҫ�������Ҫ����ӿ�ѡ������⡣
	// ��ʱʹ�ã�ϵͳ�Ĳ�Ʒ�ж���һ���Ĳ�Ʒ�壬��ϵͳֻ��������ĳһ��Ĳ�Ʒ��
	// ��ν������һ����Ʒ�����棬��������Ʒ��
	// �ؼ����룺��һ��������ۺ϶��ͬ���Ʒ��
	// Ӧ��ʵ���������ˣ�Ϊ�˲μ�һЩ�ۻᣬ�϶������׻�����·��ɣ�����˵������װ�����ף�һϵ�о����Ʒ����
	//		ʱ��װ�����ף�һϵ�о����Ʒ������������һ����ͥ��˵������������Ůװ��������װ��ʱ��Ůװ��ʱ����װ��
	//		��ЩҲ���ǳ��׵ģ���һϵ�о����Ʒ������һ���������ʵ���ǲ����ڵģ�Ҫ��Ȼ��û�����빲�������ˣ�
	//		��������˵�����󹤳�ģʽ���������ļ��У�ĳһ���¹񣨾��幤����ֻ�ܴ��ĳһ���������·������ף�һϵ�о����Ʒ����
	//		ÿ�������ֳ��׵��·�ʱҲ��ȻҪ������¹���ȡ���ˡ���OO��˼��ȥ��⣬���е��¹񣨾��幤���������¹���ģ����󹤳���ĳһ����
	//		��ÿһ�����׵��·��ְ�����������£�ĳһ�����Ʒ�������ӣ�ĳһ�����Ʒ������Щ�����������ʵҲ�������£������Ʒ����
	//		����Ŀ���Ҳ���ǿ��ӣ���һ�������Ʒ����
	// �ŵ㣺��һ����Ʒ���еĶ��������Ƴ�һ����ʱ�����ܱ�֤�ͻ���ʼ��ֻʹ��ͬһ����Ʒ���еĶ���
	// ȱ�㣺��Ʒ����չ�ǳ����ѣ�Ҫ����һ��ϵ�е�ĳһ��Ʒ����Ҫ�ڳ���� Creator ��Ӵ��룬��Ҫ�ھ��������Ӵ��롣
	// ע�������Ʒ������չ����Ʒ�ȼ�����չ��

	// ��״������
	class Shape
	{
	public:
		virtual void Draw() = 0;
	};

	// ��״ʵ������1
	class Rectangle : public Shape
	{
	public:
		void Draw() override
		{
			std::cout << "Inside Rectangle::Draw() method." << std::endl;
		}
	};

	// ��״ʵ������2
	class Square : public Shape
	{
	public:
		void Draw() override
		{
			std::cout << "Inside Square::Draw() method." << std::endl;
		}
	};

	// ��״ʵ������3
	class Circle : public Shape
	{
	public:
		void Draw() override
		{
			std::cout << "Inside Circle::Draw() method." << std::endl;
		}
	};

	// ��ɫ������
	class Color
	{
	public:
		virtual void Fill() = 0;
	};

	// ��ɫʵ������1
	class Red : public Color
	{
	public:
		void Fill() override
		{
			std::cout << "Inside Red::Fill() method." << std::endl;
		}
	};

	// ��ɫʵ������2
	class Green : public Color
	{
	public:
		void Fill() override
		{
			std::cout << "Inside Green::Fill() method." << std::endl;
		}
	};

	// ��ɫʵ������3
	class Blue : public Color
	{
	public:
		void Fill() override
		{
			std::cout << "Inside Blue::Fill() method." << std::endl;
		}
	};

	// ����������
	class AbstractFactory
	{
	public:
		virtual Shape* MakeShape(std::string shapeType) = 0;
		virtual Color* MakeColor(std::string colorType) = 0;
	};

	// ������״ʵ������
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

	// ������ɫʵ������
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

	// ����һ������������/�������࣬ͨ��������״����ɫ��Ϣ����ȡ����
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