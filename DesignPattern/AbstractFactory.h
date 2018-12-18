#pragma once
#include <iostream>

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