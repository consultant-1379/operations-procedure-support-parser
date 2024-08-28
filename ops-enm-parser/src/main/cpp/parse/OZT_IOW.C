/*------------------------------------------------------------------------------
 *******************************************************************************
 * COPYRIGHT Ericsson 2018
 *
 * The copyright to the computer program(s) herein is the property of
 * Ericsson Inc. The programs may be used and/or copied only with written
 * permission from Ericsson Inc. or in accordance with the terms and
 * conditions stipulated in the agreement/contract under which the
 * program(s) have been supplied.
 *******************************************************************************
 *----------------------------------------------------------------------------*/


#include <OZT_IOW.H>


//*****************************************************************************


// trace
#include <trace.H>
static std::string trace ="OZT_IOW";


//*****************************************************************************


// file identifiers
static const char* fileId = "%File_what%";
static const char* rcsid = "@(#)rcsid:$Id: OZT_IOW.C,v 21.0 1996/08/23 12:44:08 ehsgrap Rel $";


//*****************************************************************************

//
//  The syntax of @DRAW is @DRAW(para1, para2, ...),
//  those special constants CUP, BOX etc syntactically conflicts
//  with variable names. To get around the problem, in the
//  rule of parsing variable access, those constants are
//  converted to a string value in the context of parsing @DRAW.
//  Therefore, CUP becomes a string with a particular value. The
//  question then becomes what value should we take. If we take the
//  string "CUP" for CUP, then @DRAW("CUP",...") will make the
//  code confused with the constant CUP.
//  As a result, the following "very unique" constants are defined.
//  The chance that the user needs to draw those string is almost
//  null.
//
//  Note: make sure they are in CAPITAL.

const char * OZT_IOW::drawBox = "XOBWARDTZO"; //oztdrawbox in reverse
const char * OZT_IOW::drawCup = "PUCWARDTZO"; //oztdrawcup in reverse
const char * OZT_IOW::drawInv = "VNIWARDTZO"; //oztdrawinv in reverse
const char * OZT_IOW::drawHigh = "HGIHWARDTZO"; //oztdrawhigh in reverse
const char * OZT_IOW::drawLow = "WOLWARDTZO"; //oztdrawlow in reverse
const char * OZT_IOW::styleBold = "DLOBELYTSTZO"; //oztstylebold in reverse
const char * OZT_IOW::styleItal = "LATIELYTSTZO"; //oztstyleital in reverse
const char * OZT_IOW::styleUndrln = "NLRDNUELYTSTZO"; //oztstyleundrln in reverse
const char * OZT_IOW::stylePlain = "NIALPELYTSTZO"; // oztstyleplain in reverse
const char * OZT_IOW::timeSec = "CESEMITTZO"; //ozttimesec in reverse
const char * OZT_IOW::timeMin = "NIMEMITTZO"; //ozttimemin in reverse
const char * OZT_IOW::timeHour = "RUOHEMITTZO"; //ozttimehour in reverse
const char * OZT_IOW::padLeft = "TFELDAPTZO"; //oztpadleft in reverse
const char * OZT_IOW::padRight = "THGIRDAPTZO"; //oztpadright in reverse
const char * OZT_IOW::padCenter = "RETNECDAPTZO"; //oztpadcenter in reverse
const char*  OZT_IOW::NOVARIABLE="ELBAIRAVONTZO"; //OZTNOVARIABLE inreverse


