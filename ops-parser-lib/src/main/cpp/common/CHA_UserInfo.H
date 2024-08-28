// RCS handling
// $Id: CHA_UserInfo.H,v 24.0 1995/11/28 16:55:15 ehsgrap Rel $

//**********************************************************************
// 
// .NAME    CHA_UserInfo - information about current process owner
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_UserInfo.H

// .COPYRIGHT
// 	COPYRIGHT Ericsson Hewlett-Packard Telecommunications AB 1995
//
// 	The Copyright to the computer program(s) herein is the
// 	property of Ericsson Hewlett-Packard Telecommunications AB,
// 	Sweden.  The program(s) may be used and/or copied with the
// 	written permission from Ericsson Hewlett-Packard
// 	Telecommunications AB or in accordance with the terms and
// 	conditions stipulated in the agreement/contract under which
// 	the program(s) have been supplied.


// .DESCRIPTION 
//      The CHA_UserInfo class is an interface to the information
//      about the process owner (current user) found in the passwd
//      file. Static member variables stores the information, which
//      means that multiple instances of this class will always give
//      the same information and that there is little penalty in
//      creating multiple instances.
//
//      The added value of using this class is that the same method
//      for retrieving the user ID and related information is always
//      the same. This class uses the real user (and not the effective
//      user). The operating system also returns references to static
//      memory areas when using getpwuid() which are reused in
//      subsequent calls. This can give unexpected results in
//      applications referring to that memory. This class copies the
//      contents after one initial call to getpwuid().

// DOCUMENT NO
//	190 89-CAA 134 1515

// AUTHOR 
// 	1995-01-04 by EHS/PXE Jan Grape (ehsgrap@ehs.ericsson.se)

// .REVISION
//	TB53_OZ
//	1995-11-28

// CHANGES
// 	RCS revision history
//      $Log: CHA_UserInfo.H,v $
//      Revision 24.0  1995/11/28 16:55:15  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:41:36  17:41:36  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//      
//      Revision 22.0  1995/08/01  20:44:23  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:40:07  09:40:07  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//      
//      Revision 20.0  95/06/08  08:32:48  08:32:48  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//      
//      Revision 19.0  95/04/13  10:52:12  10:52:12  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//      
//      Revision 18.0  95/03/17  20:04:27  20:04:27  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 17.0  95/03/16  14:02:54  14:02:54  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 16.0  95/03/10  12:58:20  12:58:20  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//      
//      Revision 15.0  95/03/09  15:00:27  15:00:27  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//      
//      Revision 14.0  1995/02/25  16:33:12  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:02:46  14:02:46  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//      
//      Revision 12.1  95/02/14  16:02:01  16:02:01  ehsgrap (Jan Grape (9 9073) VK/EHS/PXE)
//      Made static copies of all fields in the pw record.
//      
//      Revision 12.0  1995/02/06  16:13:39  cmcha
//      Made release TB3, J Grape (EHSGRAP).
//
//      Revision 11.1  1995/01/19  16:04:14  ehscama
//      Added include of sys/types.h to fix compilation on SunOS.
//
//      Revision 11.0  1995/01/18  14:45:18  cmcha
//      Made release PREIT, N Länninge (XKKNICL).
//
//      Revision 1.2  1995/01/05  07:41:53  ehsgrap
//      Corrections after first compilation.
//
//      Revision 1.1  1995/01/04  12:20:56  ehsgrap
//      Initial revision
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

// .SEE ALSO 
// 	

//**********************************************************************

#ifndef CHA_USERINFO_H
#define CHA_USERINFO_H

#include <sys/types.h> // For uid_t and gid_t on SunOS4
#include <pwd.h>
#include <rw/cstring.h>

class CHA_UserInfo
{
public:
    CHA_UserInfo();
    // Description:
    //     Constructor. If this is the first instance of this class
    //     the static passwd struct will be initialized.

    virtual ~CHA_UserInfo();
    // Description:
    //     Since this class doesn't have any non static member the
    //     destructor doesn't do anything.

    RWCString loginName() const;
    // Description:
    //     Returns a string containin the login name (user name) of
    //     the current process owner, i.e. th name of the one who is
    //     running this program.

    RWCString fullName() const;
    // Description:
    //     Returns a string with the full name and possibly other
    //     information about the user.

    uid_t userID() const;
    // Description:
    //     Returns the user identity number.

    gid_t groupID() const;
    // Description:
    //     Returns the number of the user's primary group.

    RWCString homeDir() const;
    // Description:
    //     Returns a string containing the path to the user's home
    //     directory. 

    RWCString loginShell() const;
    // Description:
    //     Returns a string containing the path to the user's initial
    //     shell program.
    
private:
    static RWBoolean isInitialized;
    static RWCString myLoginName;
    static RWCString myFullName;
    static uid_t myUserID;
    static gid_t myGroupID;
    static RWCString myHomeDir;
    static RWCString myLoginShell;
};

#endif
