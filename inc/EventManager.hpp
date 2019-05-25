/*
 * EventManager.hpp
 *
 *  Created on: 2019年5月8日
 *      Author: d
 */
#ifndef EVENTMANAGER_HPP_
#define EVENTMANAGER_HPP_
#include "eventParsing.hpp"
#include "StateManger.h"

typedef struct{
	int status;
	float errx;
	float erry;
}Trkerr_t;


class CEventManager
{
public:
	CEventManager();
	~CEventManager();
	static void thread_ipcEvent();
private:
	MSGDRIV_Handle _Handle;
	CMessage* _Msg;
	StateManger* _StateManager;
	CIPCProc* m_ipc;
	static CEventManager* pThis;
	int *cfg_value;
	char *usr_value;
	bool exit_ipcthread;
	float winPos[2];
	int outtype;
	comtype_t outcomtype;
	void IPC_Creat();
	void MSG_register();

private:
	static void MSG_Trk(void* p);
	static void MSG_SwitchSensor(void* p);
	static void MSG_TrkSearch(void* p);
	static void MSG_CaptureMode(void* p);
	static void MSG_IrisAndFocus(void* p);
	static void MSG_WorkMode(void* p);
	static void MSG_JosPos(void* p);

	static void MSG_Com_SelfCheck(void* p);
	static void MSG_Com_TrkMovControl(void* p);
	static void MSG_Com_TrkMove(void* p);
	static void MSG_Com_SecTrkPos(void* p);
	static void MSG_Com_MtdSelect(void* p);
	static void MSG_Com_Gatemove(void* p);
	static void MSG_Com_ZoomCtrl(void* p);
	static void MSG_Com_IrisCtrl(void* p);
	static void MSG_Com_FocusCtrl(void* p);
	static void MSG_Com_SetPlatSpeed(void* p);
	static void MSG_Com_SetPlatAngle(void* p);
	static void MSG_Com_PreposHandle(void* p);
	static void MSG_Com_SetZoom(void* p);
	static void MSG_Com_QueryPtzPos(void* p);
	static void MSG_Com_GetZoom(void* p);
	static void MSG_Com_TrkOutput(void* p);
	static void MSG_Com_SetCfg(void* p);
	static void MSG_Com_GetCfg(void* p);
	static void MSG_Com_SetOsd(void* p);
	static void MSG_Com_DefaultCfg(void* p);
	static void MSG_Com_SaveCfg(void* p);
	

	int  ReadConfigFile();
	int SetConfig(comtype_t comtype, int block, int field, int value,char *inBuf);
	int GetConfig(comtype_t comtype, int block, int field);
	int DefaultConfig(comtype_t comtype, int blockId);
	int SaveConfig(comtype_t comtype);
	int IgnoreConfig(int block, int field);
	int updateparams(int block, int *cfg_value);
	void signalFeedBack(int argnum ...);
	void signalFeedBack_output(comtype_t comtype, int trkstat, int outtype, float x, float y);
	int is_float(int cfgid);
	string intip2string(unsigned int intip);
	unsigned int stringip2int(string str);
	vector<string> csplit(const string& str, const string& delim);

public:
	static void* answerPos(void* p);
	static void* answerZoom(void* p);
	static void* setPlatAngle(void* p);
	static void* preposHandle(void* p);
	static void* setZoom(void* p);
	

public:
	Trkerr_t m_pixelErr;
	SELF_SemHndl m_semSendpos,m_semSendZoom;
};



#endif /* EVENTMANAGER_HPP_ */
