#ifndef CHA_ESLIST_H
#define CHA_ESLIST_H

#include <rw/cstring.h>
#include <rw/tvsrtvec.h>
#include <CHA_Model.H>
#include <CHA_IgnoreCaseString.H>
//TORF-241666
//#include <dbslib.H>

//class EAC_ESI_Info;

class CHA_EsList : public CHA_Model
{
public:

    enum ReturnCode {
	OKAY,
	NOT_AUTHORIZED,
	NO_CONTACT_AUTHDB,
	NO_IMH
    };


    enum NeSource {
      EA,
      IMHAPI
    };
  
    CHA_EsList();
    // Description:
    //     Constructor.
    
    virtual ~CHA_EsList();
    // Description:
    //     Destructor.
    
    RWCString operator[](size_t i) const;
    // Description:
    //     Returns the entry at position i.
    // Parameters:
    //     i			IN: the index
    // Return value:
    //     RWCString	        the item
    
    RWBoolean contains(const RWCString& name) const;
    // Description:
    //     Returns true if the list contains the name of
    //     the external system in question.
    // Parameters:
    //     name			IN: the name of the ES
    // Return value:
    //     TRUE			list contains name
    //     FALSE		list does not contain name

    size_t entries() const;
    // Description:
    //     Returns the number of entries in the list.
    // Return value:
    //     size_t	        the number of entries

    RWCString first() const;
    // Description:
    //     Returns the first entry in the list.
    // Return value:
    //     RWCString	        the item

    virtual size_t index(const RWCString& name) const;
    // Description:
    //     Returns the index for an entry in the list.
    // Parameters:
    //     name			the name of the ES

    RWBoolean isEmpty() const;
    // Description:
    //     Returns true if the list is empty.
    // Return value:
    //     TRUE			list is empty
    //     FALSE		list is not empty

    RWCString last() const;
    // Description:
    //     Returns the last entry in the list.
    // Return value:
    //     RWCString	        the item

    size_t length() const;
    // Description:
    //     Returns the number of entries in the list.
    // Return value:
    //     size_t	        the length

    virtual size_t occurrencesOf(const RWCString& name) const;
    // Description:
    //     Returns the number occurences of the name.
    // Parameters:
    //     name			IN: the name of the ES

    ReturnCode update(NeSource ne_src = EA);
    // Description:
    //     Updates the list.
    // Parameters:
    //     ne_src			IN: Used to select from which source the 
    //                                      list should be read.
    //                                      EA     - Use EA only
    // Return value:
    //     OK			Succesful
    //     NOT_AUTHORIZED	The user is not authorized
    //     NO_CONTACT_AUTHDB 	Problems with authority data base
    
    ReturnCode updateUsingEA(); 
    // Description:
    //      Updates the list using EA.

protected:

    ReturnCode updateUsingIMHAPI();
    // NOT USED
    // Description: 
    //      Updates the list using IMH and distinguished names.

    void updateIMHDatabase();
    // Description:
    //      Updates the IMH database by removing all IM_equipment object with Object_symbol EQ_PROT
    //      and adding new CR_PROT objects containing the communication proticol
 
    //void getIMHObject( IMH_instance* inst, IM_object* object, RWTValSortedVector<CHA_IgnoreCaseString>* tmp_list );
    // Description:
    //      Help method used by updateUsingIMHAPI

    
    RWTValSortedVector<CHA_IgnoreCaseString> myEsList;
    				// the list of external system names
    				
private:
  
    //void getCpsForES(EAC_ESI_Info& eacInfo, const char* neName);
};

#endif
