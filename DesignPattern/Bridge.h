#pragma once
#include <iostream>
#include <string>

// 意图：将抽象部分与实现部分分离，使它们都可以独立的变化。
// 主要解决：在有多种可能会变化的情况下，用继承会造成类爆炸问题，扩展起来不灵活。
// 何时使用：实现系统可能有多个角度分类，每一种角度都可能变化。
// 如何解决：把这种多角度分类分离出来，让它们独立变化，减少它们之间耦合。
// 关键代码：抽象类依赖实现类。
// 应用实例： 1、猪八戒从天蓬元帅转世投胎到猪，转世投胎的机制将尘世划分为两个等级，即：灵魂和肉体，前者相当于抽象化，后者相当于实现化。
// 生灵通过功能的委派，调用肉体对象的功能，使得生灵可以动态地选择。 2、墙上的开关，可以看到的开关是抽象的，不用管里面具体怎么实现的。
// 优点： 1、抽象和实现的分离。 2、优秀的扩展能力。 3、实现细节对客户透明。
// 缺点：桥接模式的引入会增加系统的理解与设计难度，由于聚合关联关系建立在抽象层，要求开发者针对抽象进行设计与编程。
// 使用场景： 1、如果一个系统需要在构件的抽象化角色和具体化角色之间增加更多的灵活性，避免在两个层次之间建立静态的继承联系，
// 通过桥接模式可以使它们在抽象层建立一个关联关系。 2、对于那些不希望使用继承或因为多层次继承导致系统类的个数急剧增加的系统，桥接模式尤为适用。
// 3、一个类存在两个独立变化的维度，且这两个维度都需要进行扩展。
// 注意事项：对于两个独立变化的维度，使用桥接模式再适合不过了。

namespace DP_Bridge
{
	class TimeImp
	{
	public:
		TimeImp(int hr, int min)
		{
			hr_ = hr;
			min_ = min;
		}
		virtual void tell()
		{
			std::cout << "time is " << hr_ << ":" << min_ << std::endl;
		}
	protected:
		int hr_;
		int min_;
	};

	class CivilianTimeImp : public TimeImp
	{
	public:
		CivilianTimeImp(int hr, int min, int pm) : TimeImp(hr, min)
		{
			if (pm)
			{
				strcpy_s(whichM_, " PM");
			}
			else
			{
				strcpy_s(whichM_, " AM");
			}
		}

		/* virtual */
		void tell() override
		{
			std::cout << "time is " << hr_ << ":" << min_ << whichM_ << std::endl;
		}
	protected:
		char whichM_[4];
	};

	class ZuluTimeImp : public TimeImp 
	{
	public:
		ZuluTimeImp(int hr, int min, int zone) : TimeImp(hr, min) 
		{
			if (zone == 5)
				strcpy_s(zone_, " Eastern Standard Time");
			else if (zone == 6)
				strcpy_s(zone_, " Central Standard Time");
		}

		/* virtual */
		void tell() override
		{
			std::cout << "time is " << hr_ << ":" << min_ << zone_ <<
				std::endl;
		}
	protected:
		char zone_[30];
	};

	class Time
	{
	public:
		Time() {}
		Time(int hr, int min)
		{
			imp_ = new TimeImp(hr, min);
		}
		virtual void tell()
		{
			imp_->tell();
		}
	protected:
		TimeImp *imp_;
	};

	class CivilianTime : public Time
	{
	public:
		CivilianTime(int hr, int min, int pm)
		{
			imp_ = new CivilianTimeImp(hr, min, pm);
		}
	};

	class ZuluTime : public Time 
	{
	public:
		ZuluTime(int hr, int min, int zone) 
		{
			imp_ = new ZuluTimeImp(hr, min, zone);
		}
	};

	void BridgeExample()
	{
		Time* times[3];
		times[0] = new Time(14, 30);
		times[1] = new CivilianTime(2, 30, 1);
		times[2] = new ZuluTime(14, 30, 6);
		for (size_t i = 0; i < 3; i++)
		{
			times[i]->tell();
		}
	}
}