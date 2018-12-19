#pragma once
#include <iostream>
#include <string>

// ��ͼ�������󲿷���ʵ�ֲ��ַ��룬ʹ���Ƕ����Զ����ı仯��
// ��Ҫ��������ж��ֿ��ܻ�仯������£��ü̳л�����౬ը���⣬��չ��������
// ��ʱʹ�ã�ʵ��ϵͳ�����ж���Ƕȷ��࣬ÿһ�ֽǶȶ����ܱ仯��
// ��ν���������ֶ�Ƕȷ����������������Ƕ����仯����������֮����ϡ�
// �ؼ����룺����������ʵ���ࡣ
// Ӧ��ʵ���� 1����˽������Ԫ˧ת��Ͷ̥����ת��Ͷ̥�Ļ��ƽ���������Ϊ�����ȼ��������������壬ǰ���൱�ڳ��󻯣������൱��ʵ�ֻ���
// ����ͨ�����ܵ�ί�ɣ������������Ĺ��ܣ�ʹ��������Զ�̬��ѡ�� 2��ǽ�ϵĿ��أ����Կ����Ŀ����ǳ���ģ����ù����������ôʵ�ֵġ�
// �ŵ㣺 1�������ʵ�ֵķ��롣 2���������չ������ 3��ʵ��ϸ�ڶԿͻ�͸����
// ȱ�㣺�Ž�ģʽ�����������ϵͳ�����������Ѷȣ����ھۺϹ�����ϵ�����ڳ���㣬Ҫ�󿪷�����Գ������������̡�
// ʹ�ó����� 1�����һ��ϵͳ��Ҫ�ڹ����ĳ��󻯽�ɫ�;��廯��ɫ֮�����Ӹ��������ԣ��������������֮�佨����̬�ļ̳���ϵ��
// ͨ���Ž�ģʽ����ʹ�����ڳ���㽨��һ��������ϵ�� 2��������Щ��ϣ��ʹ�ü̳л���Ϊ���μ̳е���ϵͳ��ĸ����������ӵ�ϵͳ���Ž�ģʽ��Ϊ���á�
// 3��һ����������������仯��ά�ȣ���������ά�ȶ���Ҫ������չ��
// ע������������������仯��ά�ȣ�ʹ���Ž�ģʽ���ʺϲ����ˡ�

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