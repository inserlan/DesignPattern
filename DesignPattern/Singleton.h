#pragma once
#include <iostream>

// ��ͼ����֤һ�������һ��ʵ�������ṩһ����������ȫ�ַ��ʵ㡣
// ��Ҫ�����һ��ȫ��ʹ�õ���Ƶ���ش��������١�
// ��ʱʹ�ã����������ʵ����Ŀ����ʡϵͳ��Դ��ʱ��
// ��ν�����ж�ϵͳ�Ƿ��Ѿ������������������򷵻أ����û���򴴽���
// �ؼ����룺���캯����protected��private��
// Ӧ��ʵ����Windows �Ƕ���̶��̵߳ģ��ڲ���һ���ļ���ʱ�򣬾Ͳ��ɱ���س��ֶ�����̻��߳�ͬʱ����һ���ļ�������
//		���������ļ��Ĵ������ͨ��Ψһ��ʵ�������С�
// �ŵ㣺 1�����ڴ���ֻ��һ��ʵ�����������ڴ�Ŀ�����������Ƶ���Ĵ���������ʵ�����������ѧԺ��ҳҳ�滺�棩��
//		2���������Դ�Ķ���ռ�ã�����д�ļ���������
// ȱ�㣺û�нӿڣ����ܼ̳У��뵥һְ��ԭ���ͻ��һ����Ӧ��ֻ�����ڲ��߼�����������������ô����ʵ������
// ע�����
//	1��������ֻ����һ��ʵ����
//	2������������Լ������Լ���Ψһʵ����
//	3�������������������������ṩ��һʵ����
//	instance() ��������Ҫʹ��ͬ����, ��ֹ���߳�ͬʱ������� instance �����ʵ������

// before =========================================================
class GlobalClassBefore
{
	int m_value;
public:
	GlobalClassBefore(int v = 0) { m_value = v; }
	int get_value() { return m_value; }
	void set_value(int v) { m_value = v; }
};

// default initialization
GlobalClassBefore *global_ptr_before = nullptr;

void foo_before()
{
	// initialization on first use
	if (global_ptr_before == nullptr)
		global_ptr_before = new GlobalClassBefore;
	global_ptr_before->set_value(1);
	std::cout << "foo: global_ptr is " << global_ptr_before->get_value() << '\n';
}

void bar_before()
{
	// initialization on first use
	if (global_ptr_before == nullptr)
		global_ptr_before = new GlobalClassBefore;
	global_ptr_before->set_value(2);
	std::cout << "bar: global_ptr is " << global_ptr_before->get_value() << '\n';
}

void SingleTonBefore()
{
	if (global_ptr_before == nullptr)
		global_ptr_before = new GlobalClassBefore;
	std::cout << "main: global_ptr is " << global_ptr_before->get_value() << '\n';
	foo_before();
	bar_before();
}

// after =========================================================
class GlobalClassAfter
{
	int m_value;
	static GlobalClassAfter* s_instance;
	GlobalClassAfter(int v = 0) { m_value = v; }

public:
	int get_value() { return m_value; }
	void set_value(int v) { m_value = v; }
	static GlobalClassAfter* instance()
	{
		if (s_instance == nullptr)
			s_instance = new GlobalClassAfter;
		return s_instance;
	}
};

// Allocating and initializing GlobalClass's
// static data member.  The pointer is being
// allocated - not the object inself.
GlobalClassAfter* GlobalClassAfter::s_instance = nullptr;

void foo_after()
{
	GlobalClassAfter::instance()->set_value(1);
	std::cout << "foo: global_ptr is " << GlobalClassAfter::instance()->get_value() << '\n';
}

void bar_after()
{
	GlobalClassAfter::instance()->set_value(2);
	std::cout << "bar: global_ptr is " << GlobalClassAfter::instance()->get_value() << '\n';
}

void SingletonAfter()
{
	std::cout << "main: global_ptr is " << GlobalClassAfter::instance()->get_value() << '\n';
	foo_after();
	bar_after();
}
