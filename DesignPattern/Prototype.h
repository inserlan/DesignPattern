#pragma once
#include <iostream>	

// ��ͼ����ԭ��ʵ��ָ��������������࣬����ͨ��������Щԭ�ʹ����µĶ���
// ��Ҫ������������ڽ�����ɾ��ԭ�͡�
// ��ʱʹ�ã� 1����һ��ϵͳӦ�ö��������Ĳ�Ʒ���������ɺͱ�ʾʱ�� 
//	2����Ҫʵ����������������ʱ��ָ��ʱ�����磬ͨ����̬װ�ء� 
//	3��Ϊ�˱��ⴴ��һ�����Ʒ����ƽ�еĹ�������ʱ�� 
//	4����һ�����ʵ��ֻ���м�����ͬ״̬����е�һ��ʱ��������Ӧ��Ŀ��ԭ�Ͳ���¡���ǿ��ܱ�ÿ���ú��ʵ�״̬�ֹ�ʵ�������������һЩ��
// ��ν�����������е�һ��ԭ�Ͷ��󣬿��ٵ����ɺ�ԭ�Ͷ���һ����ʵ����
// �ؼ����룺 1��ʵ�ֿ�¡�������� JAVA �̳� Cloneable����д clone()��
//	��.NET �п���ʹ�� Object ��� MemberwiseClone() ������ʵ�ֶ����ǳ������ͨ�����л��ķ�ʽ��ʵ�������
//	2��ԭ��ģʽͬ�����ڸ���������ʹ���ߺ;������ͣ��ױ��ࣩ֮�����Ϲ�ϵ����ͬ��Ҫ����Щ"�ױ���"ӵ���ȶ��Ľӿڡ�
// Ӧ��ʵ���� 1��ϸ�����ѡ� 2��JAVA �е� Object clone() ������
// �ŵ㣺 1��������ߡ� 2���ӱܹ��캯����Լ����
// ȱ�㣺 1���䱸��¡������Ҫ����Ĺ��ܽ���ͨ�̿��ǣ������ȫ�µ��಻�Ǻ��ѣ����������е��಻һ�������ף�
//	�ر�һ�������ò�֧�ִ��л��ļ�Ӷ��󣬻������ú���ѭ���ṹ��ʱ�� 2������ʵ�� Cloneable �ӿڡ�
// ʹ�ó����� 1����Դ�Ż������� 2�����ʼ����Ҫ�����ǳ������Դ�������Դ�������ݡ�Ӳ����Դ�ȡ�
//	3�����ܺͰ�ȫҪ��ĳ����� 4��ͨ�� new ����һ��������Ҫ�ǳ�����������׼�������Ȩ�ޣ������ʹ��ԭ��ģʽ��
//	5��һ���������޸��ߵĳ����� 6��һ��������Ҫ�ṩ������������ʣ����Ҹ��������߿��ܶ���Ҫ�޸���ֵʱ��
//	���Կ���ʹ��ԭ��ģʽ����������󹩵�����ʹ�á� 7����ʵ����Ŀ�У�ԭ��ģʽ���ٵ������֣�һ���Ǻ͹�������ģʽһ����֣�
//	ͨ�� clone �ķ�������һ������Ȼ���ɹ��������ṩ�������ߡ�ԭ��ģʽ�Ѿ��� Java ��Ϊ��Ȼһ�壬��ҿ�����������ʹ�á�
// ע�������ͨ����һ�������ʵ�����������¶���ͬ���ǣ�ԭ��ģʽ��ͨ������һ�����ж��������¶���ġ�
//	ǳ����ʵ�� Cloneable����д�������ͨ��ʵ�� Serializable ��ȡ����������

namespace DP_Prototype
{
	enum imageType { LSAT, SPOT };

	class Image
	{
	public:
		virtual void draw() = 0;
		static Image *findAndClone(imageType);
	protected:
		virtual imageType returnType() = 0;
		virtual Image *clone() = 0;
		// As each subclass of Image is declared, it registers its prototype
		static void addPrototype(Image* image)
		{
			_prototypes[_nextSlot++] = image;
		}
	private:
		// addPrototype() saves each registered prototype here
		static Image* _prototypes[10];
		static int _nextSlot;
	};

	Image* Image::_prototypes[];
	int Image::_nextSlot;

	// Client calls this public static member function when it needs an instance
	// of an Image subclass
	Image* Image::findAndClone(imageType type)
	{
		for (int i = 0; i < _nextSlot; i++)
			if (_prototypes[i]->returnType() == type)
				return _prototypes[i]->clone();
		return nullptr;
	}

	class LandSatImage : public Image
	{
	public:
		imageType returnType() { return LSAT; }
		void draw()
		{
			std::cout << "LandSatImage::draw " << _id << std::endl;
		}
		// when clone() is called, call the one-argument ctor with a dummy arg
		Image* clone()
		{
			return new LandSatImage(1);
		}
	protected:
		// This is only call from clone()
		LandSatImage(int dummy)
		{
			_id = _count++;
		}
	private:
		// Mechanism for initializing an Image subclass - this causes the
		// default ctor to be called, which registers the subclass's prototype
		static LandSatImage _landSatImage;
		// This is only called when the private static data member is initiated
		LandSatImage()
		{
			addPrototype(this);
		}
		// Nominal "state" per instance mechanism
		int _id;
		static int _count;
	};

	// Register the subclass's prototype
	LandSatImage LandSatImage::_landSatImage;
	// Initialize the "state" per instance mechanism
	int LandSatImage::_count = 1;

	class SpotImage : public Image
	{
	public:
		imageType returnType()
		{
			return SPOT;
		}
		void draw()
		{
			std::cout << "SpotImage::draw " << _id << std::endl;
		}
		Image *clone()
		{
			return new SpotImage(1);
		}
	protected:
		SpotImage(int dummy)
		{
			_id = _count++;
		}
	private:
		SpotImage()
		{
			addPrototype(this);
		}
		static SpotImage _spotImage;
		int _id;
		static int _count;
	};

	SpotImage SpotImage::_spotImage;
	int SpotImage::_count = 1;

	// Simulated stream of creation requests
	const int NUM_IMAGES = 8;
	imageType input[NUM_IMAGES] =
	{
		LSAT, LSAT, LSAT, SPOT, LSAT, SPOT, SPOT, LSAT
	};

	void PrototypeExample()
	{
		Image* images[NUM_IMAGES];
		// Given an image type, find the right prototype, and return a clone
		for (int i = 0; i < NUM_IMAGES; i++)
		{
			images[i] = Image::findAndClone(input[i]);
		}

		// Demonstrate that correct image objects have been cloned
		for (int i = 0; i < NUM_IMAGES; i++)
		{
			images[i]->draw();
		}

		// Free the dynamic memory
		for (int i = 0; i < NUM_IMAGES; i++)
		{
			delete images[i];
		}
	}
}