#pragma once
#include <iostream>
#include <vector>
#include <string>

// ��ͼ����һ�����ӵĹ��������ʾ����룬ʹ��ͬ���Ĺ������̿��Դ�����ͬ�ı�ʾ��
// ��Ҫ�������Ҫ��������ϵͳ�У���ʱ��������"һ�����Ӷ���"�Ĵ�����������ͨ���ɸ������ֵ��Ӷ�����һ�����㷨���ɣ�
//		��������ı仯��������Ӷ���ĸ������־��������ž��ҵı仯�����ǽ����������һ����㷨ȴ����ȶ���
// ��ʱʹ�ã�һЩ������������䣬������Ͼ����仯��ʱ��
// ��ν���������벻����뿪��
// �ؼ����룺�����ߣ��������ṩʵ�������ݣ������������ʵ����������ϵ��
// Ӧ��ʵ���� 1��ȥ�ϵ»������������֡�������ը������ǲ���ģ���������Ǿ����仯�ģ����ɳ���ν��"�ײ�"�� 2��JAVA �е� StringBuilder��
// �ŵ㣺 1�������߶���������չ�� 2�����ڿ���ϸ�ڷ��ա�
// ȱ�㣺 1����Ʒ�����й�ͬ�㣬��Χ�����ơ� 2�����ڲ��仯���ӣ����кܶ�Ľ����ࡣ
// ʹ�ó����� 1����Ҫ���ɵĶ�����и��ӵ��ڲ��ṹ�� 2����Ҫ���ɵĶ����ڲ����Ա����໥������
// ע������빤��ģʽ�������ǣ�������ģʽ���ӹ�ע�����װ���˳��

//���Ǽ���һ����͵����ҵ���������У�һ�����͵��ײͿ�����һ��������Burger����һ��������Cold drink����
//������Burger����������ʳ������Veg Burger�����⺺����Chicken Burger����
//�����ǰ���ֽ���С�������Cold drink�������ǿɿڿ��֣�coke������¿��֣�pepsi����������װ��ƿ���С�
//���ǽ�����һ����ʾʳ����Ŀ�����纺������������ Item �ӿں�ʵ�� Item �ӿڵ�ʵ���࣬
//�Լ�һ����ʾʳ���װ�� Packing �ӿں�ʵ�� Packing �ӿڵ�ʵ���࣬�����ǰ���ֽ���У�������װ��ƿ���С�
//Ȼ�����Ǵ���һ�� Meal �࣬���� Item �� ArrayList ��һ��ͨ����� Item ��������ͬ���͵� Meal ����� MealBuilder��
//BuilderPatternDemo�����ǵ���ʾ��ʹ�� MealBuilder ������һ�� Meal��

namespace DP_Builder
{
	// ��װ�������
	class Packing
	{
	public:
		virtual std::string pack() = 0;
	};

	// �����װ1��ֽ��
	class Warpper : public Packing
	{
	public:
		std::string pack() override
		{
			return "Warpper";
		}
	};

	// �����װ2��ƿ��
	class Bottle : public Packing
	{
	public:
		std::string pack() override
		{
			return "Bottle";
		}
	};

	// ʳ����Ŀ�������
	class Item
	{
	public:
		virtual std::string name() = 0;
		virtual Packing* packing() = 0;
		virtual float price() = 0;
	};

	// ����ʳ����Ŀ1������
	class Burger : public Item
	{
	public:
		Packing* packing() override
		{
			return new Warpper;
		}
	};

	// ����ʳ����Ŀ2������
	class ColdDrink : public Item
	{
	public:
		Packing* packing() override
		{
			return new Bottle;
		}
	};

	// ���庺��1
	class VegBurger : public Burger
	{
	public:
		std::string name() override
		{
			return "Veg Burger";
		}

		float price() override
		{
			return 25.0f;
		}
	};

	// ���庺��2
	class ChickenBurger : public Burger
	{
	public:
		std::string name() override
		{
			return "Chicken Burger";
		}

		float price() override
		{
			return 50.0f;
		}
	};

	// ��������1
	class Coke : public ColdDrink
	{
	public:
		std::string name() override
		{
			return "Coke";
		}

		float price() override
		{
			return 30.0f;
		}
	};

	// ��������2
	class Pepsi : public ColdDrink
	{
	public:
		std::string name() override
		{
			return "Pepsi";
		}

		float price() override
		{
			return 35.0f;
		}
	};

	// �ײ���
	class Meal
	{
	private:
		std::vector<Item*> m_vtItem;

	public:
		void addItem(Item* it)
		{
			m_vtItem.push_back(it);
		}

		float cost()
		{
			float cost = 0.0f;
			for (auto it : m_vtItem)
				cost += it->price();
			return cost;
		}

		void showItem()
		{
			for (auto it : m_vtItem)
			{
				std::cout << "Item: " << it->name() << ", Packing: " << it->packing()->pack() << ", Price: " << it->price() << "\n";
			}
		}
	};

	// ��������
	class MealBuilder
	{
	public:
		Meal* prepareVegMeal()
		{
			Meal* meal = new Meal;
			meal->addItem(new VegBurger);
			meal->addItem(new Coke);
			return meal;
		}

		Meal* prepareNonVegMeal()
		{
			Meal* meal = new Meal;
			meal->addItem(new ChickenBurger);
			meal->addItem(new Pepsi);
			return meal;
		}
	};

	void BuliderExample()
	{
		MealBuilder* bulider = new MealBuilder;

		Meal* verMeal = bulider->prepareVegMeal();
		std::cout << "Ver Meal" << "\n";
		verMeal->showItem();
		std::cout << "Total Price: " << verMeal->cost() << "\n";

		Meal* nonVerMeal = bulider->prepareNonVegMeal();
		std::cout << "Non-Ver Meal" << "\n";
		nonVerMeal->showItem();
		std::cout << "Total Price: " << nonVerMeal->cost() << "\n";
	}
}