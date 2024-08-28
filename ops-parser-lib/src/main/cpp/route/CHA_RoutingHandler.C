// RCS handling
// $Id: CHA_RoutingHandler.C,v 22.0.1.1 1995/12/21 16:48:24 ehsphad Exp $

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
//      1994-04-25 by EHS/PXE Jan Grape (ehsgrap@ehs.ericsson.se)

// REVISION
//	XM2S1
//	1995-09-07

// CHANGES
//      RCS revision history
//      $Log: CHA_RoutingHandler.C,v $
//      Revision 22.0.1.1  1995/12/21 16:48:24  ehsphad
//      Added Instance of CHA_ResponseFwdReceiver and changed in setRespReceiver.
//
//      Revision 23.0  1995/09/07 17:46:12  ehscama
//      Made release XM2S1, ehscama.
//
//      Revision 22.0  1995/08/01  20:47:44  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:44:55  09:44:55  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//
//      Revision 20.0  95/06/08  08:36:21  08:36:21  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//
//      Revision 19.0  95/04/13  10:55:43  10:55:43  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 18.0  95/03/17  20:08:12  20:08:12  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//
//      Revision 17.0  95/03/16  14:09:13  14:09:13  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//
//      Revision 16.0  95/03/10  13:02:28  13:02:28  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//
//      Revision 15.0  95/03/09  15:06:51  15:06:51  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//
//      Revision 14.0  1995/02/25  16:36:23  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:08:14  14:08:14  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//
//      Revision 12.0  95/02/06  16:19:33  16:19:33  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//
//      Revision 11.0  1995/01/18  14:51:03  cmcha
//      Made release PREIT, N Länninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  09:05:52  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:32:24  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:52:28  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:25:08  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.0  1994/08/30  17:52:26  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:49:01  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.1  1994/08/16  06:16:26  ehsgrap
//      Corrected a trace message.
//
//      Revision 4.0  1994/07/18  13:41:18  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.0  1994/06/23  07:57:34  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.0  1994/06/12  07:59:57  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.8  1994/06/10  16:56:35  ehsgrap
//      Fixed doc. nr, creation date, header information and
//      changed #include "..." to #include <...> for a great
//      number of files.
//
//      Revision 1.7  1994/06/08  13:34:14  ehsgrap
//      Moved some #include statements from .C to .H file.
//
//      Revision 1.6  1994/05/25  06:53:55  ehsgrap
//      Deletion of routers in destructor.
//
//      Revision 1.5  1994/05/24  13:14:04  qhsmaun
//      Added use of CHA_WindowRouter (ehsgrap).
//
//      Revision 1.4  1994/05/04  09:07:37  xkknicl
//      Added use of CHA_PrinterRouter and CHA_FileRouter
//
//      Revision 1.3  1994/04/29  07:14:40  ehsgrap
//      Added use of CHA_MailRouter.
//
//      Revision 1.2  1994/04/26  14:47:56  ehsgrap
//      Added getRouter() method.
//
//      Revision 1.1  1994/04/25  10:58:50  cmcha
//      Initial revision
//
//
//      Release revision history
//	REV NO	DATE		NAME			DESCRIPTION
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


#include <CHA_Trace.H>
#include <CHA_RoutingHandler.H>


//**********************************************************************


//static CAP_TRC_trace trace = CAP_TRC_DEF((char*)"CHA_RoutingHandler", (char*)"C");


//**********************************************************************


CHA_RoutingHandler::CHA_RoutingHandler()
{
    //TRACE_IN(trace, CHA_RoutingHandler, "");

    // initialize the routing cases
    for(int respType = 0; respType <= CHA_RT_UNDEFINED; respType++)
    {

    // create a receiver for each type of responses
      receiver[respType] =
	new CHA_ResponseFwdReceiver((CHA_ResponseType) respType);

	routingCase[respType].setResponseType((CHA_ResponseType) respType);
	routingCase[respType].setResponseReceiver(receiver[respType]);


	// set all routing to be internal by default
	for(int destType = 0; destType <= CHA_DT_UNDEFINED; destType++)
	{
	    routingCase[respType].setExternallyRouted((CHA_DestinationType) destType, FALSE);
	}
    }

    // first, initialize all pointer to the routers to NULL
    for(int destType = 0; destType <= CHA_DT_UNDEFINED; destType++)
	router[destType] = NULL;

    // then, create those router types that exist
    router[CHA_DT_MAIL]    = new CHA_MailRouter(this);
    router[CHA_DT_PRINTER] = new CHA_PrinterRouter(this);
    router[CHA_DT_FILE]    = new CHA_FileRouter(this);
    router[CHA_DT_WINDOW]  = new CHA_WindowRouter(this);

}


//**********************************************************************


CHA_RoutingHandler::~CHA_RoutingHandler()
{
    // delete all routers
    for(int destType = 0; destType <= CHA_DT_UNDEFINED; destType++)
	if(router[destType] != NULL)
	    delete router[destType];

    for(int respType = 0; respType <= CHA_RT_UNDEFINED; respType++)
	if(receiver[respType]!= NULL)
	    delete receiver[respType];
}


//**********************************************************************


CHA_RoutingCase* CHA_RoutingHandler::getRoutingCase(CHA_ResponseType respType)
{
    return &routingCase[respType];
}


//**********************************************************************


CHA_DestinationRouter* CHA_RoutingHandler::getRouter(CHA_DestinationType destType)
{
    return router[destType];
}


//**********************************************************************


void CHA_RoutingHandler::setRespReceiver(CHA_ResponseType responseType,
					 CHA_ResponseReceiver* pReceiver)
{
    //TRACE_IN(trace, setRespReceiver, responseType << pReceiver);

    pReceiver->addDependent(receiver[responseType]);
}

//**********************************************************************
