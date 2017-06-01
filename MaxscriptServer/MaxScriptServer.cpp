//**************************************************************************/
// Copyright (c) 1998-2007 Autodesk, Inc.
// All rights reserved.
// 
// These coded instructions, statements, and computer programs contain
// unpublished proprietary information written by Autodesk, Inc., and are
// protected by Federal copyright law. They may not be disclosed to third
// parties or copied or duplicated in any form, in whole or in part, without
// the prior written consent of Autodesk, Inc.
//**************************************************************************/
// DESCRIPTION: Appwizard generated plugin
// AUTHOR: 
//***************************************************************************/

#include "MaxScriptServer.h"
#include "Server_Rollup_Wrapper.h"
#include <QtWidgets>

#define MaxScriptServer_CLASS_ID	Class_ID(0x850bdae6, 0xb57a2611)


class MaxScriptServer : public UtilityObj 
{
public:
	virtual void DeleteThis() { }
	
	virtual void BeginEditParams(Interface *ip,IUtil *iu);
	virtual void EndEditParams(Interface *ip,IUtil *iu);

	virtual void Init(HWND hWnd);
	virtual void Destroy(HWND hWnd);
	
	// Singleton access
	static MaxScriptServer* GetInstance() { 
		static MaxScriptServer theMaxScriptServer;
		return &theMaxScriptServer; 
	}

private:
	QPointer<QWidget> m_Widget;
	Interface *ip;
	//Constructor/Destructor, private for singleton access
	MaxScriptServer();
	virtual ~MaxScriptServer();
};


class MaxScriptServerClassDesc : public ClassDesc2 
{
public:
	virtual int IsPublic() 							{ return TRUE; }
	virtual void* Create(BOOL /*loading = FALSE*/) 	{ return MaxScriptServer::GetInstance(); }
	virtual const TCHAR *	ClassName() 			{ return GetString(IDS_CLASS_NAME); }
	virtual SClass_ID SuperClassID() 				{ return UTILITY_CLASS_ID; }
	virtual Class_ID ClassID() 						{ return MaxScriptServer_CLASS_ID; }
	virtual const TCHAR* Category() 				{ return GetString(IDS_CATEGORY); }

	virtual const TCHAR* InternalName() 			{ return _T("MaxScriptServer"); }	// returns fixed parsable name (scripter-visible name)
	virtual HINSTANCE HInstance() 					{ return hInstance; }					// returns owning module handle
	

};


ClassDesc2* GetMaxScriptServerDesc() { 
	static MaxScriptServerClassDesc MaxScriptServerDesc;
	return &MaxScriptServerDesc; 
}




//--- MaxScriptServer -------------------------------------------------------
MaxScriptServer::MaxScriptServer()
{
	
}

MaxScriptServer::~MaxScriptServer()
{

}

void MaxScriptServer::BeginEditParams(Interface* ip,IUtil* iu) 
{
	// This version of AddRollupPage() takes a QtWidget to add to the command panel
	Q_UNUSED(iu);
	MaxScriptServer::ip = ip;
	m_Widget = new Server_Rollup_Wrapper();
	ip->AddRollupPage(*m_Widget, L"Script Server");
}
	
void MaxScriptServer::EndEditParams(Interface* ip,IUtil*)
{
	// Delete the rollup on exit
	ip->DeleteRollupPage(*m_Widget);
}

void MaxScriptServer::Init(HWND /*handle*/)
{

}

void MaxScriptServer::Destroy(HWND /*handle*/)
{

}


