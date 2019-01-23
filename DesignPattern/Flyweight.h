#pragma once
#include <iostream>
using namespace std;

// ��ͼ�����ù�������Ч��֧�ִ���ϸ���ȵĶ���
// ��Ҫ��������д�������ʱ���п��ܻ�����ڴ���������ǰ����й�ͬ�Ĳ��ֳ���������������ͬ��ҵ������ֱ�ӷ������ڴ������еĶ��󣬱������´�����
// ��ʱʹ�ã� 1��ϵͳ���д������� 2����Щ�������Ĵ����ڴ档
// 3����Щ�����״̬�󲿷ֿ����ⲿ���� 4����Щ������԰�������״̬��Ϊ�ܶ��飬�������̶���Ӷ������޳�����ʱ��ÿһ����󶼿�����һ�����������档
// 5��ϵͳ����������Щ������ݣ���Щ�����ǲ��ɷֱ�ġ�
// ��ν������Ψһ��ʶ���жϣ�������ڴ����У��򷵻����Ψһ��ʶ������ʶ�Ķ���
// �ؼ����룺�� HashMap �洢��Щ����
// Ӧ��ʵ���� 1��JAVA �е� String��������򷵻أ����û���򴴽�һ���ַ����������ַ�����������档 2�����ݿ�����ݳء�
// �ŵ㣺�����ٶ���Ĵ���������ϵͳ���ڴ棬ʹЧ����ߡ�
// ȱ�㣺�����ϵͳ�ĸ��Ӷȣ���Ҫ������ⲿ״̬���ڲ�״̬�������ⲿ״̬���й��л������ʣ���Ӧ�������ڲ�״̬�ı仯���仯����������ϵͳ�Ļ��ҡ�
// ʹ�ó����� 1��ϵͳ�д������ƶ��� 2����Ҫ����صĳ�����
// ע����� 1��ע�⻮���ⲿ״̬���ڲ�״̬��������ܻ������̰߳�ȫ���⡣ 2����Щ�������һ������������Կ��ơ�

namespace DP_FlyweightBefore
{
	class Gazillion
	{
	public:
		Gazillion()
		{
			m_value_one = s_num / Y;
			m_value_two = s_num % Y;
			++s_num;
		}
		void report()
		{
			cout << m_value_one << m_value_two << ' ';
		}
		static const int X, Y;
	private:
		int m_value_one;
		int m_value_two;
		static int s_num;
	};

	const int Gazillion::X = 6, Gazillion::Y = 10;
	int Gazillion::s_num = 0;

	void FlyweightExampleBefore()
	{
		Gazillion matrix[Gazillion::X][Gazillion::Y];
		for (int i = 0; i < Gazillion::X; i++)
		{
			for (int j = 0; j < Gazillion::Y; j++)
			{
				matrix[i][j].report();
			}
			cout << '\n';
		}
	}
}

namespace DP_FlyweightAfter
{
	class Gazillion
	{
	public:
		Gazillion(int value_one)
		{
			m_value_one = value_one;
			cout << "ctor: " << m_value_one << '\n';
		}
		~Gazillion()
		{
			cout << m_value_one << ' ';
		}
		void report(int value_two)
		{
			cout << m_value_one << value_two << ' ';
		}
	private:
		int m_value_one;
	};

	class Factory
	{
	public:
		static Gazillion *get_fly(int in)
		{
			if (!s_pool[in])
				s_pool[in] = new Gazillion(in);
			return s_pool[in];
		}
		static void clean_up()
		{
			cout << "dtors: ";
			for (int i = 0; i < X; i++)
			{
				if (s_pool[i])
					delete s_pool[i];
			}
			cout << '\n';
		}
		static const int X, Y;
	private:
		static Gazillion *s_pool[];
	};

	const int Factory::X = 6, Factory::Y = 10;
	Gazillion *Factory::s_pool[] =
	{
	  0, 0, 0, 0, 0, 0
	};

	void FlyweightExampleAfter()
	{
		for (int i = 0; i < Factory::X; ++i)
		{
			for (int j = 0; j < Factory::Y; ++j)
				Factory::get_fly(i)->report(j);
			cout << '\n';
		}
		Factory::clean_up();
	}
}
