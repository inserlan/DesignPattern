#pragma once

#include <iostream>
#include <string>
#include <list>

// 对象池概述：对象池模型创建并拥有固定数量的对象，当程序需要一个新的对象时，如果对象池中有空闲对象，则立即返回，否则才创建新的该类对象。
//	当一个对象不再被使用时，应该将其放回对象池，以便后来的程序使用。由于系统资源有限，一个对象池模型应该指定其可容纳的最大对象数量。
//	当达到该数量时，如果仍然有对象创建请求，则抛出异常或者阻塞当前调用线程，直到一个对象被放回对象池中。
// 对象池模型适用的场景： (1)需要使用大量对象		(2)这些对象的实例化开销比较大且生存期比较短
// 对象池优势：一个对象池可以在可容忍时间内创建成功并投入使用。但是创建对象时并不总是这样，尤其是当这些对象的创建过程比较耗时，
// 而且创建和销毁频率又比较大时更是如此。比如数据库连接、网络套接字连接、线程对象、诸如字体或位图等图像对象等。
// 对象池的缺点: 现在Java的对象分配操作不比c语言的malloc调用慢, 对于轻中量级的对象, 分配 / 释放对象的开销可以忽略不计;
//	并发环境中, 多个线程可能(同时)需要获取池中对象, 进而需要在堆数据结构上进行同步或者因为锁竞争而产生阻塞, 这种开销要比创建销毁对象的开销高数百倍;
//	由于池中对象的数量有限, 势必成为一个可伸缩性瓶颈; 很难正确的设定对象池的大小, 如果太小则起不到作用, 如果过大, 则占用内存资源高,
//对象池有其特定的适用场景: 受限的, 不需要可伸缩性的环境(cpu\内存等物理资源有限) : cpu性能不够强劲, 内存比较紧张, 垃圾收集, 
//	内存抖动会造成比较大的影响, 需要提高内存管理效率, 响应性比吞吐量更为重要; 数量受限的资源, 比如数据库连接;
//	创建成本高昂的对象, 可斟酌是否池化, 比较常见的有线程池（ThreadPoolExecutor）, 字节数组池等;

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