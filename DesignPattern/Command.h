#pragma once
#include <iostream>
using namespace std;

// ��ͼ����һ�������װ��һ�����󣬴Ӷ�ʹ�������ò�ͬ������Կͻ����в�������
// ��Ҫ����������ϵͳ�У���Ϊ����������Ϊʵ����ͨ����һ�ֽ���ϵĹ�ϵ����ĳЩ���ϣ�
// ������Ҫ����Ϊ���м�¼������������������ȴ���ʱ�������޷������仯�Ľ���ϵ���ƾͲ�̫���ʡ�
// ��ʱʹ�ã���ĳЩ���ϣ�����Ҫ����Ϊ����"��¼������/����������"�ȴ��������޷������仯�Ľ�����ǲ����ʵġ�
// ����������£���ν�"��Ϊ������"��"��Ϊʵ����"�����һ����Ϊ����Ϊ���󣬿���ʵ�ֶ���֮�������ϡ�
// ��ν����ͨ�������ߵ��ý�����ִ�����˳�򣺵����ߡ������ߡ����
// �ؼ����룺����������ɫ��1��received ����������ִ�ж��� 2��Command 3��invoker ʹ�������������
// Ӧ��ʵ����struts 1 �е� action ���Ŀ����� ActionServlet ֻ��һ�����൱�� Invoker����ģ�Ͳ��������Ų�ͬ��Ӧ���в�ͬ��ģ���࣬�൱�ھ���� Command��
// �ŵ㣺 1��������ϵͳ��϶ȡ� 2���µ�������Ժ�������ӵ�ϵͳ��ȥ��
// ȱ�㣺ʹ������ģʽ���ܻᵼ��ĳЩϵͳ�й���ľ��������ࡣ
// ʹ�ó�������Ϊ������ĵط�������ʹ������ģʽ�����磺 1��GUI ��ÿһ����ť����һ����� 2��ģ�� CMD��
// ע�����ϵͳ��Ҫ֧������ĳ���(Undo)�����ͻָ�(Redo)������Ҳ���Կ���ʹ������ģʽ��������ģʽ����չ��

namespace DP_CommandBefore
{
// the client has to query the "type" of each object, and manually invoke the desired method. 
	class Giant
	{
	public:
		enum Type
		{
			Fee, Phi, Pheaux
		};
		Giant()
		{
			m_id = s_next++;
			m_type = (Type)(m_id % 3);
		}
		Type get_type()
		{
			return m_type;
		}
		void fee()
		{
			cout << m_id << "-fee  ";
		}
		void phi()
		{
			cout << m_id << "-phi  ";
		}
		void pheaux()
		{
			cout << m_id << "-pheaux  ";
		}
	private:
		Type m_type;
		int m_id;
		static int s_next;
	};

	int Giant::s_next = 0;

	template<typename T, int size = 8> 
	class Queue
	{
	public:
		Queue()
		{
			m_add = m_remove = 0;
		}
		void enque(T* c)
		{
			m_array[m_add] = c;
			m_add = (m_add + 1) % size;
		}
		T* deque()
		{
			int temp = m_remove;
			m_remove = (m_remove + 1) % size;
			return m_array[temp];
		}

	private:
		T* m_array[size];
		int m_add, m_remove;
	};

	void CommandExampleBefore()
	{
		Queue<Giant> que;
		Giant input[6], *bad_guy;

		for (int i = 0; i < 6; i++)
		{
			que.enque(&input[i]);
		}

		for (int i = 0; i < 6; i++)
		{
			bad_guy = que.deque();
			if (bad_guy->get_type() == Giant::Fee)
				bad_guy->fee();
			else if (bad_guy->get_type() == Giant::Phi)
				bad_guy->phi();
			else if (bad_guy->get_type() == Giant::Pheaux)
				bad_guy->pheaux();
		}

		cout << '\n';
	}
}

namespace DP_CommandAfter
{
	class Giant
	{
	public:
		Giant()
		{
			m_id = s_next++;
		}
		void fee()
		{
			cout << m_id << "-fee  ";
		}
		void phi()
		{
			cout << m_id << "-phi  ";
		}
		void pheaux()
		{
			cout << m_id << "-pheaux  ";
		}
	private:
		int m_id;
		static int s_next;
	};
	int Giant::s_next = 0;

	class Command
	{
	public:
		typedef void(Giant::*Action)();
		Command(Giant* object, Action method)
		{
			m_object = object;
			m_method = method;
		}
		void execute()
		{
			(m_object->*m_method)();
		}

	private:
		Giant* m_object;
		Action m_method;
	};

	template<typename T, int size = 8>
	class Queue
	{
	public:
		Queue()
		{
			m_add = m_remove = 0;
		}
		void enque(T* c)
		{
			m_array[m_add] = c;
			m_add = (m_add + 1) % size;
		}
		T* deque()
		{
			int temp = m_remove;
			m_remove = (m_remove + 1) % size;
			return m_array[temp];
		}

	private:
		T* m_array[size];
		int m_add, m_remove;
	};

	void CommandExampleAfter()
	{
		Queue<Command> que;
		Command *input[] =
		{
			new Command(new Giant, &Giant::fee),
			new Command(new Giant, &Giant::phi),
			new Command(new Giant, &Giant::pheaux),
			new Command(new Giant, &Giant::fee),
			new Command(new Giant, &Giant::phi),
			new Command(new Giant,&Giant::pheaux)
		};

		for (int i = 0; i < 6; i++)
		{
			que.enque(input[i]);
		}

		for (int i = 0; i < 6; i++)
		{
			que.deque()->execute();
		}

		for (auto v : input)
		{
			delete v;
		}
	}
}