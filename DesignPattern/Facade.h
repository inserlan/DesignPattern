//#pragma once
//
//#include <iostream.h>
//
//��ͼ��Ϊ��ϵͳ�е�һ��ӿ��ṩһ��һ�µĽ��棬���ģʽ������һ���߲�ӿڣ�����ӿ�ʹ����һ��ϵͳ��������ʹ�á�
//
//��Ҫ��������ͷ��ʸ���ϵͳ���ڲ���ϵͳʱ�ĸ��Ӷȣ��򻯿ͻ�����֮�Ľӿڡ�
//
//��ʱʹ�ã� 1���ͻ��˲���Ҫ֪��ϵͳ�ڲ��ĸ�����ϵ������ϵͳֻ���ṩһ��"�Ӵ�Ա"���ɡ� 2������ϵͳ����ڡ�
//
//��ν�����ͻ��˲���ϵͳ��ϣ��������ϵͳ��ϡ�
//
//�ؼ����룺�ڿͻ��˺͸���ϵͳ֮���ټ�һ�㣬��һ�㽫����˳��������ϵ�ȴ���á�
//
//Ӧ��ʵ���� 1��ȥҽԺ����������Ҫȥ�Һš�������ۡ�ȡҩ���û��߻��߼������úܸ��ӣ�������ṩ�Ӵ���Ա��ֻ�ýӴ���Ա�������ͺܷ��㡣 2��JAVA �����㿪��ģʽ��
//
//�ŵ㣺 1������ϵͳ�໥������ 2���������ԡ� 3������˰�ȫ�ԡ�
//
//ȱ�㣺�����Ͽ���ԭ�����Ҫ�Ķ������鷳���̳���д�������ʡ�
//
//ʹ�ó����� 1��Ϊ���ӵ�ģ�����ϵͳ�ṩ�����ʵ�ģ�顣 2����ϵͳ��Զ����� 3��Ԥ����ˮƽ��Ա�����ķ��ա�
//
//ע������ڲ�λ��ṹ�У�����ʹ�����ģʽ����ϵͳ��ÿһ�����ڡ�
//
//class MisDepartment
//{
//public:
//	void submitNetworkRequest()
//	{
//		_state = 0;
//	}
//	bool checkOnStatus()
//	{
//		_state++;
//		if (_state == Complete)
//			return 1;
//		return 0;
//	}
//private:
//	enum States
//	{
//		Received, DenyAllKnowledge, ReferClientToFacilities,
//		FacilitiesHasNotSentPaperwork, ElectricianIsNotDone,
//		ElectricianDidItWrong, DispatchTechnician, SignedOff, DoesNotWork,
//		FixElectriciansWiring, Complete
//	};
//	int _state;
//};
//
//class ElectricianUnion
//{
//public:
//	void submitNetworkRequest()
//	{
//		_state = 0;
//	}
//	bool checkOnStatus()
//	{
//		_state++;
//		if (_state == Complete)
//			return 1;
//		return 0;
//	}
//private:
//	enum States
//	{
//		Received, RejectTheForm, SizeTheJob, SmokeAndJokeBreak,
//		WaitForAuthorization, DoTheWrongJob, BlameTheEngineer, WaitToPunchOut,
//		DoHalfAJob, ComplainToEngineer, GetClarification, CompleteTheJob,
//		TurnInThePaperwork, Complete
//	};
//	int _state;
//};
//
//class FacilitiesDepartment
//{
//public:
//	void submitNetworkRequest()
//	{
//		_state = 0;
//	}
//	bool checkOnStatus()
//	{
//		_state++;
//		if (_state == Complete)
//			return 1;
//		return 0;
//	}
//private:
//	enum States
//	{
//		Received, AssignToEngineer, EngineerResearches, RequestIsNotPossible,
//		EngineerLeavesCompany, AssignToNewEngineer, NewEngineerResearches,
//		ReassignEngineer, EngineerReturns, EngineerResearchesAgain,
//		EngineerFillsOutPaperWork, Complete
//	};
//	int _state;
//};
//
//class FacilitiesFacade
//{
//public:
//	FacilitiesFacade()
//	{
//		_count = 0;
//	}
//	void submitNetworkRequest()
//	{
//		_state = 0;
//	}
//	bool checkOnStatus()
//	{
//		_count++;
//		/* Job request has just been received */
//		if (_state == Received)
//		{
//			_state++;
//			/* Forward the job request to the engineer */
//			_engineer.submitNetworkRequest();
//			cout << "submitted to Facilities - " << _count <<
//				" phone calls so far" << endl;
//		}
//		else if (_state == SubmitToEngineer)
//		{
//			/* If engineer is complete, forward to electrician */
//			if (_engineer.checkOnStatus())
//			{
//				_state++;
//				_electrician.submitNetworkRequest();
//				cout << "submitted to Electrician - " << _count <<
//					" phone calls so far" << endl;
//			}
//		}
//		else if (_state == SubmitToElectrician)
//		{
//			/* If electrician is complete, forward to technician */
//			if (_electrician.checkOnStatus())
//			{
//				_state++;
//				_technician.submitNetworkRequest();
//				cout << "submitted to MIS - " << _count <<
//					" phone calls so far" << endl;
//			}
//		}
//		else if (_state == SubmitToTechnician)
//		{
//			/* If technician is complete, job is done */
//			if (_technician.checkOnStatus())
//				return 1;
//		}
//		/* The job is not entirely complete */
//		return 0;
//	}
//	int getNumberOfCalls()
//
//	{
//		return _count;
//	}
//private:
//	enum States
//	{
//		Received, SubmitToEngineer, SubmitToElectrician, SubmitToTechnician
//	};
//	int _state;
//	int _count;
//	FacilitiesDepartment _engineer;
//	ElectricianUnion _electrician;
//	MisDepartment _technician;
//};
//
//int main()
//{
//	FacilitiesFacade facilities;
//
//	facilities.submitNetworkRequest();
//	/* Keep checking until job is complete */
//	while (!facilities.checkOnStatus())
//		;
//	cout << "job completed after only " << facilities.getNumberOfCalls() <<
//		" phone calls" << endl;
//}