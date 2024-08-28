// RCS handling
// $Id: CHA_WindowTarget.C,v 22.0.1.1 1996/01/05 14:29:26 ehsphad Exp $

//**********************************************************************

// COPYRIGHT
//      COPYRIGHT Ericsson Hewlett-Packard Telecommunications AB 1994
//
//      The Copyright to the computer program(s) herein is the
//      property of Ericsson Hewlett-Packard Telecommunications AB,
//      Sweden.  The program(s) may be used and/or copied with the
//      written permission from Ericsson Hewlett-Packard
//      Telecommunications AB or in accordance with the terms and
//      conditions stipulated in the agreement/contract under which
//      the program(s) have been supplied.

// DOCUMENT NO
//	190 89-CAA 134 1519

// AUTHOR
//      1994-05-10 by EHS/PXE Jan Grape (ehsgrap@ehs.ericsson.se)

// REVISION
//	TB53_OZ
//	1995-11-28

// CHANGES
//      RCS revision history
//      $Log: CHA_WindowTarget.C,v $
//      Revision 22.0.1.1  1996/01/05 14:29:26  ehsphad
//      Changed all RWModel to CHA_Model.
//
//      Revision 24.0  1995/11/28 16:58:20  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:46:17  17:46:17  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//
//      Revision 22.0  1995/08/01  20:47:48  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:45:02  09:45:02  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//
//      Revision 20.0  95/06/08  08:36:25  08:36:25  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//
//      Revision 19.0  95/04/13  10:55:47  10:55:47  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 18.0  95/03/17  20:08:17  20:08:17  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//
//      Revision 17.0  95/03/16  14:09:25  14:09:25  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//
//      Revision 16.0  95/03/10  13:02:33  13:02:33  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//
//      Revision 15.0  95/03/09  15:07:00  15:07:00  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//
//      Revision 14.0  1995/02/25  16:36:28  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:08:22  14:08:22  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//
//      Revision 12.0  95/02/06  16:19:40  16:19:40  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//
//      Revision 11.0  1995/01/18  14:51:09  cmcha
//      Made release PREIT, N Länninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  09:05:58  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:32:31  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:52:42  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:25:14  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.0  1994/08/30  17:52:31  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:49:10  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.0  1994/07/18  13:41:28  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.1  1994/07/15  11:39:56  ehsgrap
//      Now handles break response.
//
//      Revision 3.0  1994/06/23  07:57:45  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.0  1994/06/12  08:00:04  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.6  1994/06/10  16:57:31  ehsgrap
//      Fixed doc. nr, creation date, header information and
//      changed #include "..." to #include <...> for a great
//      number of files.
//
//      Revision 1.5  1994/06/09  15:27:01  ehsgrap
//      Fixed typo in getStoredResponse()
//
//      Revision 1.4  1994/06/08  13:43:45  ehsgrap
//      Added Event STORED_REMOVED.
//
//      Revision 1.3  1994/05/25  17:03:34  ehscama
//      Changed to tmpRcvr in updateFrom()
//
//      Revision 1.2  1994/05/19  08:24:18  ehsgrap
//      Added trace.
//
//      Revision 1.1  1994/05/18  08:30:44  ehsgrap
//      Initial version.
//
//
//      Release revision history
//	REV NO	DATE		NAME			DESCRIPTION
//	TB53_OZ 1995-11-28      J Grape (EHSGRAP)       RCS rev 24.0
//	XM2S1   1995-09-07      ehscama                 RCS rev 23.0
//	EC2_OZ  1995-08-01      Jan Sandquist (EHSJAASA)RCS rev 22.0
//	EC1_OZ  1995-06-29      J Grape (EHSGRAP)       RCS rev 21.0
//	TB5_2_OZ1995-06-08      J Grape (ehsgrap)       RCS rev 20.0
//	TB5_1_OZ1995-04-13      J Grape (EHSGRAP)       RCS rev 19.0
//	TB51_OZ 1995-03-17      ehscama                 RCS rev 18.0
//	TB5_OZ  1995-03-16      ehscama                 RCS rev 17.0
//	TB6_B1C_B1995-03-10      N.Lanninge (XKKNICL)    RCS rev 16.0
//	TB6_B1C 1995-03-09      N.Lanninge (XKKNICL)    RCS rev 15.0
//	TB4_OZ  1995-02-25      J Grape (EHSGRAP)       RCS rev 14.0
//	CHUI_TB61995-02-15      N.Lanninge (XKKNICL)    RCS rev 13.5
//	TB3     1995-02-06      J Grape (EHSGRAP)       RCS rev 12.0
//	PREIT   1995-01-18      N Länninge (XKKNICL)    RCS rev 11.0
//	TB2     1994-12-22      J Grape (EHSGRAP)       RCS rev 10.0
//	E       1994-10-24      ehscama                 RCS rev 9.0
//	D       1994-10-05      EHSCAMA                 RCS rev 8.0
//	R1C     1994-09-22      J Grape (EHSGRAP)       RCS rev 7.0
//	R1B     1994-08-30      J Grape (EHSGRAP)       RCS rev 6.0
//	R1A     1994-08-16      J Grape (EHSGRAP)       RCS rev 5.0
//	P1C     1994-07-18      J Grape (EHSGRAP)       RCS rev 4.0
//	P1B     1994-06-23      J Grape (EHSGRAP)       RCS rev 3.0
//	P1A     1994-06-12      J Grape (EHSGRAP)       RCS rev 2.0

//**********************************************************************


#include <CHA_WindowTarget.H>
#include <CHA_LibGlobals.H>
#include <CHA_Trace.H>


//**********************************************************************


//static CAP_TRC_trace trace = CAP_TRC_DEF((char*)"CHA_WindowTarget", (char*)"C");


//**********************************************************************


CHA_WindowTarget::CHA_WindowTarget()
: pCurrentRespRcvr(NULL),
  pRespBuffer(NULL),
  lastEvent(CHA_WindowTarget::NOTHING)
{
    //TRACE_IN(trace, CHA_WindowTarget, "");

    for(int i = 0; i <= CHA_RT_UNDEFINED; i++)
	isStored[i] = FALSE;

    isStored[CHA_RT_DELAYED] = TRUE;
    isStored[CHA_RT_SPONTANEOUS] = TRUE;

}


//**********************************************************************


CHA_WindowTarget::~CHA_WindowTarget()
{
}


//**********************************************************************


RWBoolean CHA_WindowTarget::isStoredType(CHA_ResponseType respType) const
{
    //TRACE_RETURN(trace, isStoredType, respType << ":" << isStored[respType]);
    return isStored[respType];
}


//**********************************************************************


void CHA_WindowTarget::setTypeStored(CHA_ResponseType respType, RWBoolean on)
{
    //TRACE_IN(trace, setTypeStored, respType << ", " << on);

    // Ths is a temporary solution. A more careful treatment is
    // necessary here, beacuse this could happen in the middle of a
    // response and it is a possibility that buffers are lost or
    // received twice. The solution might be a "pending change" where
    // a change is made when the response is complete, but in that
    // case every response type must have a state (receiving, not
    // receiving).
    isStored[respType] = on;
}


//**********************************************************************


size_t CHA_WindowTarget::availableStored() const
{
    //TRACE_RETURN(trace, availableStored, stored.entries());
    return stored.entries();
}


//**********************************************************************


RWCString CHA_WindowTarget::getStoredResponse()
{
    if(stored.entries() > 0)
    {
	//TRACE_RETURN(trace, getStoredResponse, "a stored response");
	RWCString tmp = stored.get();
	announceEvent(STORED_REMOVED);
	return tmp;
    }
    else
    {
	//TRACE_RETURN(trace, getStoredResponse, "''");
	return RWCString("");
    }
}


//**********************************************************************


RWCString CHA_WindowTarget::getBuffer()
{
    if(pRespBuffer != NULL)
    {
	// a normal response buffer
	//TRACE_RETURN(trace, getBuffer, "a buffer");
	return pRespBuffer->getText();
    }
    else if(respToFwd.entries() > 0)
    {
	// we are forwarding temporarily stored responses
	//TRACE_RETURN(trace, getBuffer, "a tmp stored buffer");
	return respToFwd.get();
    }
    else
    {
	// we have nothing to return
	//TRACE_RETURN(trace, getBuffer, "an empty buffer");
	return RWCString("");
    }
}

//**********************************************************************

const CHA_ResponseBuffer* CHA_WindowTarget::getRespBuffer()
{
  //TRACE_IN(trace, getRespBuffer, "");
  return pRespBuffer;
}

//**********************************************************************


void CHA_WindowTarget::breakCurrentResponse()
{
    //TRACE_IN(trace, breakCurrentResponse, "");

    if(pCurrentRespRcvr != NULL)
	pCurrentRespRcvr->cancelResponse();
}


//**********************************************************************


RWBoolean CHA_WindowTarget::isCompleteResponse() const
{
    if(pCurrentRespRcvr != NULL)
    {
	//TRACE_RETURN(trace, isCompleteResponse,
	//	     pCurrentRespRcvr->isCompleteResponse());
	return pCurrentRespRcvr->isCompleteResponse();
    }
    else
    {
	//TRACE_RETURN(trace, isCompleteResponse,
	//	     TRUE << " (resp rcvr == NULL)");
	return TRUE;
    }
}


//**********************************************************************


void CHA_WindowTarget::updateFrom(CHA_Model* p, void* d)
{
    //TRACE_IN(trace, updateFrom, p << ", " << d);

    // assume that it is a response receiver calling
    CHA_ResponseReceiver* tmpRcvr = (CHA_ResponseReceiver*) p;
    const CHA_ResponseBuffer* tmpBuffer = tmpRcvr->getBuffer();

    if(isStored[tmpBuffer->getRespType()])
    {
	if(tmpRcvr->isCompleteResponse())
	{
	    // store response and announce it
	    stored.append(tmpRcvr->getAccumulatedResponse()->getText());
	    announceEvent(NEW_STORED_AVAILABLE);
	}
    }
    else
    {
	// handle not stored type
	if(pCurrentRespRcvr == NULL)
	{
	    // was "idle" before, catch up with this receiver
	    pCurrentRespRcvr = tmpRcvr;
	    pRespBuffer = tmpRcvr->getAccumulatedResponse();
	    announceEvent(NEW_BUFFER);
	    pRespBuffer = NULL;

	    if(pCurrentRespRcvr->isCompleteResponse())
		fwdFromList();
	}
	else if(pCurrentRespRcvr == tmpRcvr)
	{
	    // same type as before, forward buffer
	    pRespBuffer = tmpBuffer;
	    announceEvent(NEW_BUFFER);
	    pRespBuffer = NULL;

	    if(pCurrentRespRcvr->isCompleteResponse())
		fwdFromList();
	}
	else if(tmpRcvr->isCompleteResponse())
	{
	    // store the buffer temporarily before it gets lost
	    respToFwd.append(tmpRcvr->getAccumulatedResponse()->getText());
	}
    }
}


//**********************************************************************


void CHA_WindowTarget::detachFrom(CHA_Model* p)
{
    //TRACE_IN(trace, detachFrom, p);

    if(p == (CHA_Model*)pCurrentRespRcvr)
	pCurrentRespRcvr = NULL;

    // call corresponding function in super class
    CHA_RoutingTarget::detachFrom(p);
}


//**********************************************************************


CHA_WindowTarget::Event CHA_WindowTarget::getLastEvent()
{
    //TRACE_RETURN(trace, getLastEvent, lastEvent);
    return lastEvent;
}


//**********************************************************************


void CHA_WindowTarget::doRouting(const CHA_ResponseBuffer* response)
{
    //TRACE_FLOW(trace, doRouting, "THIS METHOD SHOULD NEVER BE CALLED!");
}


//**********************************************************************


void CHA_WindowTarget::fwdFromList()
{
    //TRACE_IN(trace, fwdFromList, "");

    // This is necessary, because we don't have a response receiver
    // for these temporarily stored responses. Also
    // isCompleteResponse() will return always TRUE when this variable
    // is NULL.
    pCurrentRespRcvr = NULL;

    // This is necessary, because we don't have a real response
    // buffer. Setting this to NULL will make getBuffer() pick from
    // respToFwd list instead.
    pRespBuffer = NULL;

    // A regular while loop is not possible here because if we don't
    // have any model clients, no responses will be read out, causing
    // an infinite loop.
    const int entries = respToFwd.entries();
    for(int i = 0; i < entries; i++)
	announceEvent(NEW_BUFFER);

    // Now the list has to be cleared, so that we don't announce the
    // same response twice.
    respToFwd.clear();
}


//**********************************************************************


void CHA_WindowTarget::announceEvent(CHA_WindowTarget::Event evt)
{
    //TRACE_IN(trace, announceEvent, evt);

    lastEvent = evt;
    changed();
}


//**********************************************************************


