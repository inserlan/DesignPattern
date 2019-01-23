#pragma once
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

// ��ͼ��������������������������һ���ö�������п��ܽ������󣬽���Щ�������ӳ�һ����
// ������������������������ֱ���ж�������Ϊֹ��
// ��Ҫ�����ְ�����ϵĴ����߸��������󣬿ͻ�ֻ��Ҫ�������͵�ְ�����ϼ��ɣ�
// �����������Ĵ���ϸ�ں�����Ĵ��ݣ�����ְ����������ķ����ߺ�����Ĵ����߽����ˡ�
// ��ʱʹ�ã��ڴ�����Ϣ��ʱ���Թ��˺ܶ����
// ��ν�������ص��඼ʵ��ͳһ�ӿڡ�
// �ؼ����룺Handler ����ۺ����Լ����� HandlerRequest ���ж��Ƿ���ʣ����û�ﵽ���������´��ݣ���˭����֮ǰ set ��ȥ��
// Ӧ��ʵ���� 1����¥���е�"���Ĵ���"�� 2��JS �е��¼�ð�ݡ� 3��JAVA WEB �� Apache Tomcat �� Encoding �Ĵ���Struts2 ����������jsp servlet �� Filter��
// �ŵ㣺 1��������϶ȡ���������ķ����ߺͽ����߽�� 2�����˶���ʹ�ö�����Ҫ֪�����Ľṹ�� 
// 3����ǿ������ָ��ְ�������ԡ�ͨ���ı����ڵĳ�Ա���ߵ������ǵĴ�������̬����������ɾ�����Ρ� 4�������µ���������ܷ��㡣
// ȱ�㣺 1�����ܱ�֤����һ�������ա� 2��ϵͳ���ܽ��ܵ�һ��Ӱ�죬�����ڽ��д������ʱ��̫���㣬���ܻ����ѭ�����á�3�����ܲ����׹۲�����ʱ���������а��ڳ���
// ʹ�ó����� 1���ж��������Դ���ͬһ�����󣬾����ĸ������������������ʱ���Զ�ȷ����
// 2���ڲ���ȷָ�������ߵ�����£����������е�һ���ύһ������ 3���ɶ�ָ̬��һ�����������
// ע������� JAVA WEB �������ܶ�Ӧ�á�

namespace DP_ChainOfResponsibility
{
	class Base
	{
		Base *next; // 1. "next" pointer in the base class
	public:
		Base()
		{
			next = 0;
		}
		void setNext(Base *n)
		{
			next = n;
		}
		void add(Base *n)
		{
			if (next)
				next->add(n);
			else
				next = n;
		}
		// 2. The "chain" method in the base class always delegates to the next obj
		virtual void handle(int i)
		{
			next->handle(i);
		}
	};
	class Handler1 : public Base
	{
	public:
		/*virtual*/void handle(int i)
		{
			if (rand() % 3)
			{
				// 3. Don't handle requests 3 times out of 4
				cout << "H1 passed " << i << "  ";
				Base::handle(i); // 3. Delegate to the base class
			}
			else
				cout << "H1 handled " << i << "  ";
		}
	};
	class Handler2 : public Base
	{
	public:
		/*virtual*/void handle(int i)
		{
			if (rand() % 3)
			{
				cout << "H2 passed " << i << "  ";
				Base::handle(i);
			}
			else
				cout << "H2 handled " << i << "  ";
		}
	};
	class Handler3 : public Base
	{
	public:
		/*virtual*/void handle(int i)
		{
			if (rand() % 3)
			{
				cout << "H3 passed " << i << "  ";
				Base::handle(i);
			}
			else
				cout << "H3 handled " << i << "  ";
		}
	};
	void CORExample()
	{
		srand((unsigned int)time(0));
		Handler1 root;
		Handler2 two;
		Handler3 thr;
		root.add(&two);
		root.add(&thr);
		thr.setNext(&root);
		for (int i = 1; i < 10; i++)
		{
			root.handle(i);
			cout << '\n';
		}
	}
}
