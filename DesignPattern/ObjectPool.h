#pragma once

#include <iostream>
#include <string>
#include <list>

// ����ظ����������ģ�ʹ�����ӵ�й̶������Ķ��󣬵�������Ҫһ���µĶ���ʱ�������������п��ж������������أ�����Ŵ����µĸ������
//	��һ�������ٱ�ʹ��ʱ��Ӧ�ý���Żض���أ��Ա�����ĳ���ʹ�á�����ϵͳ��Դ���ޣ�һ�������ģ��Ӧ��ָ��������ɵ�������������
//	���ﵽ������ʱ�������Ȼ�ж��󴴽��������׳��쳣����������ǰ�����̣߳�ֱ��һ�����󱻷Żض�����С�
// �����ģ�����õĳ����� (1)��Ҫʹ�ô�������		(2)��Щ�����ʵ���������Ƚϴ��������ڱȽ϶�
// ��������ƣ�һ������ؿ����ڿ�����ʱ���ڴ����ɹ���Ͷ��ʹ�á����Ǵ�������ʱ�������������������ǵ���Щ����Ĵ������̱ȽϺ�ʱ��
// ���Ҵ���������Ƶ���ֱȽϴ�ʱ������ˡ��������ݿ����ӡ������׽������ӡ��̶߳������������λͼ��ͼ�����ȡ�
// ����ص�ȱ��: ����Java�Ķ�������������c���Ե�malloc������, �������������Ķ���, ���� / �ͷŶ���Ŀ������Ժ��Բ���;
//	����������, ����߳̿���(ͬʱ)��Ҫ��ȡ���ж���, ������Ҫ�ڶ����ݽṹ�Ͻ���ͬ��������Ϊ����������������, ���ֿ���Ҫ�ȴ������ٶ���Ŀ��������ٱ�;
//	���ڳ��ж������������, �Ʊس�Ϊһ����������ƿ��; ������ȷ���趨����صĴ�С, ���̫С���𲻵�����, �������, ��ռ���ڴ���Դ��,
//����������ض������ó���: ���޵�, ����Ҫ�������ԵĻ���(cpu\�ڴ��������Դ����) : cpu���ܲ���ǿ��, �ڴ�ȽϽ���, �����ռ�, 
//	�ڴ涶������ɱȽϴ��Ӱ��, ��Ҫ����ڴ����Ч��, ��Ӧ�Ա���������Ϊ��Ҫ; �������޵���Դ, �������ݿ�����;
//	�����ɱ��߰��Ķ���, �������Ƿ�ػ�, �Ƚϳ��������̳߳أ�ThreadPoolExecutor��, �ֽ�����ص�;

class Resource
{
	int value;
public:
	Resource() { value = 0; }
	void reset() { value = 0; }
	int getValue() { return value; }
	void setValue(int number) { value = number; }
};

// Note, that this class is a singleton
class ObjectPool
{
private:
	std::list<Resource*> resources;
	static ObjectPool* instance;
	ObjectPool() {}
public:
	/**
		* Static method for accessing class instance.
		* Part of Singleton design pattern.
		*
		* @return ObjectPool instance.
		*/
	static ObjectPool* getInstance()
	{
		if (instance == 0)
		{
			instance = new ObjectPool;
		}
		return instance;
	}
	/**
		* Returns instance of Resource.
		*
		* New resource will be created if all the resources
		* were used at the time of the request.
		*
		* @return Resource instance.
		*/
	Resource* getResource()
	{
		if (resources.empty())
		{
			std::cout << "Creating new." << std::endl;
			return new Resource;
		}
		else
		{
			std::cout << "Reusing existing." << std::endl;
			Resource* resource = resources.front();
			resources.pop_front();
			return resource;
		}
	}
	/**
		 * Return resource back to the pool.
		 *
		 * The resource must be initialized back to
		 * the default settings before someone else
		 * attempts to use it.
		 *
		 * @param object Resource instance.
		 * @return void
		 */
	void returnResource(Resource* object)
	{
		object->reset();
		resources.push_back(object);
	}
};

ObjectPool* ObjectPool::instance = nullptr;

void ObjectPoolExample()
{
	ObjectPool* pool = ObjectPool::getInstance();
	Resource* one;
	Resource* two;
	// resource will be created
	one = pool->getResource();
	one->setValue(10);
	std::cout << "one = " << one->getValue() << " [" << one << "]" << std::endl;
	two = pool->getResource();
	two->setValue(20);
	std::cout << "two = " << two->getValue() << " [" << two << "]" << std::endl;
	pool->returnResource(one);
	pool->returnResource(two);
	/* Resources will be reused.
	 * Notice that the value of both resources were reset back to zero.
	 */
	one = pool->getResource();
	std::cout << "one = " << one->getValue() << " [" << one << "]" << std::endl;
	two = pool->getResource();
	std::cout << "two = " << two->getValue() << " [" << two << "]" << std::endl;
}