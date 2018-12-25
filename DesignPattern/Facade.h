//#pragma once
//
//#include <iostream.h>
//
//意图：为子系统中的一组接口提供一个一致的界面，外观模式定义了一个高层接口，这个接口使得这一子系统更加容易使用。
//
//主要解决：降低访问复杂系统的内部子系统时的复杂度，简化客户端与之的接口。
//
//何时使用： 1、客户端不需要知道系统内部的复杂联系，整个系统只需提供一个"接待员"即可。 2、定义系统的入口。
//
//如何解决：客户端不与系统耦合，外观类与系统耦合。
//
//关键代码：在客户端和复杂系统之间再加一层，这一层将调用顺序、依赖关系等处理好。
//
//应用实例： 1、去医院看病，可能要去挂号、门诊、划价、取药，让患者或患者家属觉得很复杂，如果有提供接待人员，只让接待人员来处理，就很方便。 2、JAVA 的三层开发模式。
//
//优点： 1、减少系统相互依赖。 2、提高灵活性。 3、提高了安全性。
//
//缺点：不符合开闭原则，如果要改东西很麻烦，继承重写都不合适。
//
//使用场景： 1、为复杂的模块或子系统提供外界访问的模块。 2、子系统相对独立。 3、预防低水平人员带来的风险。
//
//注意事项：在层次化结构中，可以使用外观模式定义系统中每一层的入口。
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