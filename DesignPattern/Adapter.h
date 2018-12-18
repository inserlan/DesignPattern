#pragma once
#include <iostream>	

// ��ͼ����һ����Ľӿ�ת���ɿͻ�ϣ��������һ���ӿڡ�������ģʽʹ��ԭ�����ڽӿڲ����ݶ�����һ��������Щ�����һ������
// ��Ҫ�������Ҫ��������ϵͳ�У�����Ҫ��һЩ"�ִ�Ķ���"�ŵ��µĻ����У����»���Ҫ��Ľӿ����ֶ���������ġ�
// ��ʱʹ�ã� 1��ϵͳ��Ҫʹ�����е��࣬������Ľӿڲ�����ϵͳ����Ҫ��
//    2����Ҫ����һ�������ظ�ʹ�õ��࣬������һЩ�˴�֮��û��̫�������һЩ�࣬����һЩ�����ڽ�����������һ��������ЩԴ�಻һ����һ�µĽӿڡ�
//    3��ͨ���ӿ�ת������һ���������һ����ϵ�С��������ϻ��ͷ��ݣ����ڶ���һ���ɻ����ڲ�����ʵ��������£�����һ�������������������һ��������ʵ�ַɵĽӿڡ���
// ��ν�����̳л��������Ƽ�����
// �ؼ����룺�������̳л��������еĶ���ʵ����Ҫ��Ŀ��ӿڡ�
// Ӧ��ʵ���� 1���������� 110V���й� 220V����Ҫ��һ���������� 110V ת��Ϊ 220V��
//    2��JAVA JDK 1.1 �ṩ�� Enumeration �ӿڣ����� 1.2 ���ṩ�� Iterator �ӿڣ���Ҫʹ�� 1.2 �� JDK��
//    ��Ҫ����ǰϵͳ�� Enumeration �ӿ�ת��Ϊ Iterator �ӿڣ���ʱ����Ҫ������ģʽ�� 
//    3���� LINUX ������ WINDOWS ���� 4��JAVA �е� jdbc��
// �ŵ㣺 1���������κ�����û�й�������һ�����С� 2���������ĸ��á� 3�����������͸���ȡ� 4������Ժá�
// ȱ�㣺 1�������ʹ��������������ϵͳ�ǳ����ң�����������а��ա����磬�����������õ��� A �ӿڣ�
// ��ʵ�ڲ���������� B �ӿڵ�ʵ�֣�һ��ϵͳ���̫��������������������һ�����ѡ����������Ǻ��б�Ҫ�����Բ�ʹ��������������ֱ�Ӷ�ϵͳ�����ع���
// 2.���� JAVA ����̳�һ���࣬��������ֻ������һ���������࣬����Ŀ��������ǳ����ࡣ
// ʹ�ó������ж������޸�һ���������е�ϵͳ�Ľӿڣ���ʱӦ�ÿ���ʹ��������ģʽ��
// ע�������������������ϸ���ʱ��ӵģ����ǽ�����ڷ��۵���Ŀ�����⡣

namespace DP_Adapter1
{
	typedef int Coordinate;
	typedef int Dimension;

	// Desired interface
	class Rectangle
	{
	public:
		virtual void draw() = 0;
	};

	// Legacy component
	class LegacyRectangle
	{
	public:
		LegacyRectangle(Coordinate x1, Coordinate y1, Coordinate x2, Coordinate y2)
		{
			x1_ = x1;
			y1_ = y1;
			x2_ = x2;
			y2_ = y2;
			std::cout << "LegacyRectangle:  create.  (" << x1_ << "," << y1_ << ") => ("
				<< x2_ << "," << y2_ << ")" << std::endl;
		}

		void oldDraw()
		{
			std::cout << "LegacyRectangle:  oldDraw.  (" << x1_ << "," << y1_ <<
				") => (" << x2_ << "," << y2_ << ")" << std::endl;
		}

	private:
		Coordinate x1_;
		Coordinate y1_;
		Coordinate x2_;
		Coordinate y2_;
	};

	// Adapter wrapper
	class RectangleAdapter : public Rectangle, private LegacyRectangle
	{
	public:
		RectangleAdapter(Coordinate x, Coordinate y, Dimension w, Dimension h)
			: LegacyRectangle(x, y, x + w, y + h)
		{
			std::cout << "RectangleAdapter: create.  (" << x << "," << y <<
				"), width = " << w << ", height = " << h << std::endl;
		}
		virtual void draw()
		{
			std::cout << "RectangleAdapter: draw." << std::endl;
			oldDraw();
		}
	};

	void AdapterExample()
	{
		Rectangle *r = new RectangleAdapter(120, 200, 60, 40);
		r->draw();
	}
}


// 1. Specify the new desired interface
// 2. Design a ��wrapper�� class that can ��impedance match�� the old to the new
// 3. The client uses(is coupled to) the new interface
// 4. The adapter / wrapper ��maps�� to the legacy implementation
namespace DP_Adapter2
{
	class ExecuteInterface
	{
	public:
		// 1. Specify the new interface
		virtual ~ExecuteInterface() {}
		virtual void execute() = 0;
	};

	// 2. Design a "wrapper" or "adapter" class
	template<typename TYPE>
	class ExecuteAdapter : public ExecuteInterface
	{
	public:
		ExecuteAdapter(TYPE *o, void(TYPE:: *m)())
		{
			object = o;
			method = m;
		}
		~ExecuteAdapter()
		{
			delete object;
		}

		// 4. The adapter/wrapper "maps" the new to the legacy implementation
		void execute() override
		{
			(object->*method)();
		}
	private:
		TYPE *object;		// ptr-to-object attribute
		void(TYPE:: *method)();	/* the old */     // ptr-to-member-function attribute
	};

	// The old: three totally incompatible classes
	// no common base class
	class Fea 
	{
	public:
		// no hope of polymorphism
		~Fea() 
		{
			std::cout << "Fea::dtor" << std::endl;
		}
		void doThis() 
		{
			std::cout << "Fea::doThis()" << std::endl;
		}
	};

	class Feye
	{
		public:~Feye()
		{
			std::cout << "Feye::dtor" << std::endl;
		}
		void doThat()
		{
			std::cout << "Feye::doThat()" << std::endl;
		}
	};

	class Pheau 
	{
	public:
		~Pheau()
		{
			std::cout << "Pheau::dtor" << std::endl;
		}
		void doTheOther()
		{
			std::cout << "Pheau::doTheOther()" << std::endl;
		}
	};

	// the new is returned
	ExecuteInterface **initialize()
	{
		ExecuteInterface **array = new ExecuteInterface*[3];
		// the old is below
		array[0] = new ExecuteAdapter<Fea>(new Fea(), &Fea::doThis);
		array[1] = new ExecuteAdapter<Feye>(new Feye(), &Feye::doThat);
		array[2] = new ExecuteAdapter<Pheau>(new Pheau(), &Pheau::doTheOther);
		return array;
	}

	void AdapterExample()
	{
		ExecuteInterface **objects = initialize();
		for (size_t i = 0; i < 3; i++)
		{
			objects[i]->execute();
		}

		// 3. Client uses the new (polymporphism)
		for (size_t i = 0; i < 3; i++)
		{
			delete objects[i];
		}

		delete objects;
	}
}