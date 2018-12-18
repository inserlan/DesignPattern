#pragma once
#include <iostream>

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

namespace DP_AbsFac
{
	// Abstract base product
	class Widget
	{
	public:
		virtual void draw() = 0;
	};

	// Concrete product family 1
	class LinuxButton : public Widget
	{
	public:
		void draw() override
		{
			std::cout << "LinuxButton\n";
		}
	};
	class LinuxMenu : public Widget
	{
	public:
		void draw() override
		{
			std::cout << "LinuxMenu\n";
		}
	};

	// Concrete product family 2
	class WindowsButton : public Widget
	{
	public:
		void draw() override
		{
			std::cout << "WindowsButton\n";
		}
	};
	class WindowsMenu : public Widget
	{
	public:
		void draw() override
		{
			std::cout << "WindowsMenu\n";
		}
	};

	// before ==================================================
	/**
	 * Here's a client, which uses concrete products directly.
	 * It's code filled up with nasty switch statements
	 * which check the product type before its use.
	 */
	class ClientBefore
	{
	public:
		void draw()
		{
#ifdef LINUX
			Widget *w = new LinuxButton;
#else
			Widget *w = new WindowsButton;
#endif // LINUX
			w->draw();
			display_window_one();
			display_window_two();
		}

		void display_window_one()
		{
#ifdef LINUX
			Widget *w[] = { new LinuxButton, new LinuxMenu };
#else
			Widget *w[] = { new WindowsButton, new WindowsMenu };
#endif // LINUX
			w[0]->draw();
			w[1]->draw();
		}
		void display_window_two()
		{
#ifdef LINUX
			Widget *w[] = { new LinuxMenu, new LinuxButton };
#else
			Widget *w[] = { new WindowsMenu, new WindowsButton };
#endif // LINUX
			w[0]->draw();
			w[1]->draw();
		}
	};

	void AbstractFactoryBefore()
	{
		ClientBefore *c = new ClientBefore();
		c->draw();
		delete c;
	}

	// after ==================================================
	// Abstract factory defines methods to create all related products
	class Factory
	{
	public:
		virtual Widget *create_button() = 0;
		virtual Widget *create_menu() = 0;
	};

	/**
	 * Each concrete factory corresponds to one product
	 * family. It creates all possible products of
	 * one kind.
	 */
	class LinuxFactory : public Factory {
	public:
		Widget *create_button() {
			return new LinuxButton;
		}
		Widget *create_menu() {
			return new LinuxMenu;
		}
	};

	/**
	 * Concrete factory creates concrete products, but
	 * returns them as abstract.
	 */
	class WindowsFactory : public Factory {
	public:
		Widget *create_button() {
			return new WindowsButton;
		}
		Widget *create_menu() {
			return new WindowsMenu;
		}
	};

	/**
	 * Client receives a factory object from its creator.
	 *
	 * All clients work with factories through abstract
	 * interface. They don't know concrete classes of
	 * factories. Because of this, you can interchange
	 * concrete factories without breaking clients.
	 *
	 * Clients don't know the concrete classes of created
	 * products either, since abstract factory methods
	 * returns abstract products.
	 */
	class ClientAfter
	{
	private:
		Factory* factory;

	public:
		ClientAfter(Factory* f)
		{
			factory = f;
		}

		void draw()
		{
			Widget* w = factory->create_button();
			w->draw();
			display_window_one();
			display_window_two();
		}

		void display_window_one()
		{
			Widget* w[] = { factory->create_button(), factory->create_menu() };
			w[0]->draw();
			w[1]->draw();
		}

		void display_window_two()
		{
			Widget* w[] = { factory->create_menu(), factory->create_button() };
			w[0]->draw();
			w[1]->draw();
		}
	};

	void AbstractFactoryAfter()
	{
		Factory* factory;
#ifdef LINUX
		factory = new LinuxFactory;
#else
		factory = new WindowsFactory;
#endif // LINUX
		ClientAfter* c = new ClientAfter(factory);
		c->draw();
	}
}