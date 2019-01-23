#pragma once
#include <iostream>
using namespace std;

// ��ͼ��Ϊ���������ṩһ�ִ����Կ��ƶ��������ķ��ʡ�
// ��Ҫ�������ֱ�ӷ��ʶ���ʱ���������⣬����˵��Ҫ���ʵĶ�����Զ�̵Ļ����ϡ����������ϵͳ�У�
// ��Щ��������ĳЩԭ�򣨱�����󴴽������ܴ󣬻���ĳЩ������Ҫ��ȫ���ƣ�������Ҫ������ķ��ʣ���
// ֱ�ӷ��ʻ��ʹ���߻���ϵͳ�ṹ�����ܶ��鷳�����ǿ����ڷ��ʴ˶���ʱ����һ���Դ˶���ķ��ʲ㡣
// ��ʱʹ�ã����ڷ���һ����ʱ��һЩ���ơ�
// ��ν���������м�㡣
// �ؼ����룺ʵ���뱻��������ϡ�
// Ӧ��ʵ���� 1��Windows ����Ŀ�ݷ�ʽ�� 2����˽�ȥ�Ҹߴ������������ձ�ģ�����������⣺
// �Ѹߴ�������ò����������ߴ������˺�����ն�ʵ��������ӿڣ���˽���ʸߴ�����ʱ�򿴲��������������գ�
// ����˵������Ǹߴ��������ࡣ 3�����Ʊ��һ���ڻ�վ��Ҳ����ȥ���۵㡣 4��һ��֧Ʊ�����д浥���˻����ʽ�Ĵ���
// ֧Ʊ���г����������������ֽ𣬲��ṩ��ǩ�����˺����ʽ�Ŀ��ơ� 5��spring aop��
// �ŵ㣺 1��ְ�������� 2������չ�ԡ� 3�����ܻ���
// ȱ�㣺 1�������ڿͻ��˺���ʵ����֮�������˴�����������Щ���͵Ĵ���ģʽ���ܻ��������Ĵ����ٶȱ�����
// 2��ʵ�ִ���ģʽ��Ҫ����Ĺ�������Щ����ģʽ��ʵ�ַǳ����ӡ�
// ʹ�ó�������ְ�������֣�ͨ��������ʹ�ó����� 1��Զ�̴��� 2��������� 3��Copy - on - Write ���� 
// 4��������Protect or Access������ 5��Cache���� 6������ǽ��Firewall������ 
// 7��ͬ������Synchronization������ 8���������ã�Smart Reference������
// ע����� 1����������ģʽ������������ģʽ��Ҫ�ı������Ƕ���Ľӿڣ�������ģʽ���ܸı���������Ľӿڡ�
// 2����װ����ģʽ������װ����ģʽΪ����ǿ���ܣ�������ģʽ��Ϊ�˼��Կ��ơ�

namespace DP_ProxyBefore
{
	class Image
	{
		int m_id;
		static int s_next;
	public:
		Image()
		{
			m_id = s_next++;
			cout << "   $$ ctor: " << m_id << '\n';
		}
		~Image()
		{
			cout << "   dtor: " << m_id << '\n';
		}
		void draw()
		{
			cout << "   drawing image " << m_id << '\n';
		}
	};

	int Image::s_next = 1;

	void ProxyExampleBefore()
	{
		Image images[5];
		for (int i; true;)
		{
			cout << "Exit[0], Image[1-5]: ";
			cin >> i;
			if (i == 0)
				break;
			images[i - 1].draw();
		}
	}
}

namespace DP_ProxyAfter
{
	class RealImage
	{
		int m_id;
	public:
		RealImage(int i)
		{
			m_id = i;
			cout << "   $$ ctor: " << m_id << '\n';
		}
		~RealImage()
		{
			cout << "   dtor: " << m_id << '\n';
		}
		void draw()
		{
			cout << "   drawing image " << m_id << '\n';
		}
	};

	// 1. Design an "extra level of indirection" wrapper class
	class Image
	{
		// 2. The wrapper class holds a pointer to the real class
		RealImage *m_the_real_thing;
		int m_id;
		static int s_next;
	public:
		Image()
		{
			m_id = s_next++;
			// 3. Initialized to null
			m_the_real_thing = 0;
		}
		~Image()
		{
			delete m_the_real_thing;
		}
		void draw()
		{
			// 4. When a request comes in, the real object is
			//    created "on first use"
			if (!m_the_real_thing)
				m_the_real_thing = new RealImage(m_id);
			// 5. The request is always delegated
			m_the_real_thing->draw();
		}
	};
	int Image::s_next = 1;

	void ProxyExampleAfter()
	{
		Image images[5];

		for (int i; true;)
		{
			cout << "Exit[0], Image[1-5]: ";
			cin >> i;
			if (i == 0)
				break;
			images[i - 1].draw();
		}
	}
}