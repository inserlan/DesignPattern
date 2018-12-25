#pragma once
#include <iostream>
#include <vector>
using namespace std;

// ��ͼ����������ϳ����νṹ�Ա�ʾ"����-����"�Ĳ�νṹ�����ģʽʹ���û��Ե����������϶����ʹ�þ���һ���ԡ�
// ��Ҫ����������������ͽṹ�������У�ģ���˼�Ԫ�غ͸���Ԫ�صĸ���ͻ�������������Ԫ��һ����������Ԫ�أ��Ӷ�ʹ�ÿͻ������븴��Ԫ�ص��ڲ��ṹ���
// ��ʱʹ�ã� 1�������ʾ����Ĳ��� - �����νṹ�����νṹ���� 2����ϣ���û�������϶����뵥������Ĳ�ͬ���û���ͳһ��ʹ����Ͻṹ�е����ж���
// ��ν������֦��Ҷ��ʵ��ͳһ�ӿڣ���֦�ڲ���ϸýӿڡ�
// �ؼ����룺��֦�ڲ���ϸýӿڣ����Һ����ڲ����� List������� Component��
// Ӧ��ʵ���� 1���������ʽ����������������������һ�������������У���һ��������Ҳ�����ǲ�����������������һ���������� 
// 2���� JAVA AWT �� SWING �У����� Button �� Checkbox ����Ҷ��Container ����֦��
// �ŵ㣺 1���߲�ģ����ü򵥡� 2���ڵ��������ӡ�
// ȱ�㣺��ʹ�����ģʽʱ����Ҷ�Ӻ���֦����������ʵ���࣬�����ǽӿڣ�Υ������������ԭ��
// ʹ�ó��������֡����峡���������β˵����ļ����ļ��еĹ���
// ע���������ʱΪ�����ࡣ

namespace DP_Composite
{
	// 2. Create an "interface" (lowest common denominator)
	class Component
	{
	public:
		virtual void traverse() = 0;
	};

	class Leaf : public Component
	{
		// 1. Scalar class   3. "isa" relationship
		int value;
	public:
		Leaf(int val)
		{
			value = val;
		}
		void traverse()
		{
			cout << value << ' ';
		}
	};

	class Composite : public Component
	{
		// 1. Vector class   3. "isa" relationship
		vector <Component*> children; // 4. "container" coupled to the interface
	public:
		// 4. "container" class coupled to the interface
		void add(Component *ele)
		{
			children.push_back(ele);
		}
		void traverse()
		{
			for (size_t i = 0; i < children.size(); i++)
				// 5. Use polymorphism to delegate to children
				children[i]->traverse();
		}
	};

	void CompositeExample()
	{
		Composite containers[4];

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 3; j++)
				containers[i].add(new Leaf(i * 3 + j));

		for (int i = 1; i < 4; i++)
			containers[0].add(&(containers[i]));

		for (int i = 0; i < 4; i++)
		{
			containers[i].traverse();
			cout << endl;
		}
	}
}