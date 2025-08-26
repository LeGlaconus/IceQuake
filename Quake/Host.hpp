//#pragma once

//#include "common.h"
//
//namespace host
//{
//
//class IHost
//{
//	DECLARE_CLASS_NOBASE(IHost);
//public:
//	virtual void Init() = 0;
//	virtual void RunFrame() = 0;
//protected:
//	double oldtime, time, newtime;
//};
//
//class BaseQuakeHost : public IHost
//{
//	DECLARE_CLASS(BaseQuakeHost, IHost);
//public:
//	BaseQuakeHost(int argc, char** argv);
//	~BaseQuakeHost();
//
//	virtual void Init();
//	virtual void RunFrame();
//
//	inline QuakeHostParams* GetParams() { return &m_Params; }
//protected:
//	QuakeHostParams m_Params;
//};
//
//class DefaultQuakeHost : public BaseQuakeHost
//{
//	DECLARE_CLASS(DefaultQuakeHost, BaseQuakeHost);
//};
//
//class DedicatedQuakeHost : public BaseQuakeHost
//{
//	DECLARE_CLASS(DedicatedQuakeHost, BaseQuakeHost);
//};
//
//}