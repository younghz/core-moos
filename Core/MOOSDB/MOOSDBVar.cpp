///////////////////////////////////////////////////////////////////////////
//
//   This file is part of the MOOS project
//
//   MOOS : Mission Oriented Operating Suite A suit of 
//   Applications and Libraries for Mobile Robotics Research 
//   Copyright (C) Paul Newman
//    
//   This software was written by Paul Newman at MIT 2001-2002 and 
//   the University of Oxford 2003-2013 
//   
//   email: pnewman@robots.ox.ac.uk. 
//              
//   This source code and the accompanying materials
//   are made available under the terms of the GNU Public License
//   which accompanies this distribution, and is available at
//   http://www.gnu.org/licenses/gpl.txt
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of 
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
//
////////////////////////////////////////////////////////////////////////////
// MOOSDBVar.cpp: implementation of the CMOOSDBVar class.
//
//////////////////////////////////////////////////////////////////////
#ifdef _WIN32
#pragma warning(disable : 4786)
#endif

#include "MOOS/libMOOS/Utils/MOOSUtilityFunctions.h"
#include "MOOSDBVar.h"
#include <iostream>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMOOSDBVar::CMOOSDBVar()
{
    m_dfVal = -1.0;
    m_dfTime = -1.0;
    m_dfWriteFreq = 0.0;
    m_sVal = "";
    m_sWhoChangedMe = "";
    m_nWrittenTo = 0;
    m_dfWrittenTime = -1;
    m_nOverTicks = 0;
}


CMOOSDBVar::CMOOSDBVar(const string & sName)
{
    m_sName = sName;
    m_dfVal = -1.0;
    m_dfTime = -1.0;
    m_sVal = "";
	m_sSrcAux = "";
    m_sWhoChangedMe = "";
    m_nWrittenTo = 0;
    m_dfWriteFreq = 0;
    m_dfWrittenTime = -1;
    m_nOverTicks = 0;

}

CMOOSDBVar::~CMOOSDBVar()
{

}

bool CMOOSDBVar::AddSubscriber(const string &sClient, double dfPeriod)
{
    CMOOSRegisterInfo Info;

    if(sClient.empty())
    {
       MOOSTrace("[X] Failed to add subscription to \"%s\" for a client with empty name \n",m_sName.c_str());
       return false;
    }
    Info.m_dfPeriod = dfPeriod;
    Info.m_sClientName = sClient;

    m_Subscribers[sClient] = Info;

    MOOSTrace("+ subs of \"%s\" to \"%s\" every %.1f seconds\n",sClient.c_str(),m_sName.c_str(),dfPeriod);

    return true;

}

void CMOOSDBVar::RemoveSubscriber(string &sWho)
{

    REGISTER_INFO_MAP::iterator p = m_Subscribers.find(sWho);
    if(p!=m_Subscribers.end())
    {
    //MOOSTrace("MOOSDB: Removing \"%s\"'s subscription to \"%s\"\n",sWho.c_str(),m_sName.c_str());
    	m_Subscribers.erase(p);
    	MOOSTrace("- subs of \"%s\" to \"%s\" \n",sWho.c_str(),m_sName.c_str());

    }
}

bool CMOOSDBVar::Reset()
{
    m_dfTime = -1;
    m_dfVal = -1;
    m_sVal = "";
    m_sWhoChangedMe = "";
    m_Writers.clear();
    m_dfWrittenTime = -1;
    m_nWrittenTo = 0;
    m_dfWriteFreq = 0;

    return true;
}
