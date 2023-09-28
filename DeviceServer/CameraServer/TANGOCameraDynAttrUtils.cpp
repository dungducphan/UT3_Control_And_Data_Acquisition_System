/*----- PROTECTED REGION ID(TANGOCamera::DynAttrUtils.cpp) ENABLED START -----*/
//=============================================================================
//
// file :        TANGOCameraDynAttrUtils.cpp
//
// description : Dynamic attributes utilities file for the TANGOCamera class
//
// project :     
//
// This file is part of Tango device class.
// 
// Tango is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Tango is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Tango.  If not, see <http://www.gnu.org/licenses/>.
// 
//
//
//=============================================================================
//                This file is generated by POGO
//        (Program Obviously used to Generate tango Object)
//=============================================================================


#include <TANGOCamera.h>
#include <TANGOCameraClass.h>

/*----- PROTECTED REGION END -----*/	//	TANGOCamera::DynAttrUtils.cpp

//================================================================
//  Attributes managed is:
//================================================================
//  dynImage  |  Tango::DevUShort	Image  ( max = 3840 x 2160)
//================================================================

//	For compatibility reason, this file (TANGOCameraDynAttrUtils)
//	manage also the dynamic command utilities.
//================================================================
//  The following table gives the correspondence
//  between command and method names.
//
//  Command name  |  Method name
//================================================================
//================================================================

namespace TANGOCamera_ns
{
//=============================================================
//	Add/Remove dynamic attribute methods
//=============================================================

//--------------------------------------------------------
/**
 *	Add a dynImage dynamic attribute.
 *
 *  parameter attname: attribute name to be cretated and added.
 *  parameter ptr:     memory buffer used to set attribute value.
 *                     If NULL or not specified, buffer will be allocated.
 */
//--------------------------------------------------------
void TANGOCamera::add_dynImage_dynamic_attribute(string attname, Tango::DevUShort *ptr)
{
	//	Attribute : dynImage
	if (ptr==NULL)
		ptr = new Tango::DevUShort[3840*2160];
	dynImageAttrib	*dynimage = new dynImageAttrib(attname);
	Tango::UserDefaultAttrProp	dynimage_prop;
	//	description	not set for dynImage
	//	label	not set for dynImage
	//	unit	not set for dynImage
	//	standard_unit	not set for dynImage
	//	display_unit	not set for dynImage
	//	format	not set for dynImage
	//	max_value	not set for dynImage
	//	min_value	not set for dynImage
	//	max_alarm	not set for dynImage
	//	min_alarm	not set for dynImage
	//	max_warning	not set for dynImage
	//	min_warning	not set for dynImage
	//	delta_t	not set for dynImage
	//	delta_val	not set for dynImage
	
	/*----- PROTECTED REGION ID(TANGOCamera::att_dynImage_dynamic_attribute) ENABLED START -----*/
	
	
	/*----- PROTECTED REGION END -----*/	//	TANGOCamera::att_dynImage_dynamic_attribute
	dynimage->set_default_properties(dynimage_prop);
	//	Not Polled
	dynimage->set_disp_level(Tango::OPERATOR);
	//	Not Memorized
	dynimage->set_change_event(true, true);
	dynImage_data.insert(make_pair(attname, ptr));
	add_attribute(dynimage);
}
//--------------------------------------------------------
/**
 *	remove a dynImage dynamic attribute.
 *
 *  parameter attname: attribute name to be removed.
 *  parameter free_it: memory buffer will be freed if true or not specified.
 */
//--------------------------------------------------------
void TANGOCamera::remove_dynImage_dynamic_attribute(string attname, bool free_it)
{
	remove_attribute(attname, true, Tango::Util::instance()->_UseDb);
	map<string,Tango::DevUShort *>::iterator ite;
    if ((ite=dynImage_data.find(attname))!=dynImage_data.end())
    {
    	/*----- PROTECTED REGION ID(TANGOCamera::remove_dynImage_dynamic_attribute) ENABLED START -----*/
    	
    	/*----- PROTECTED REGION END -----*/	//	TANGOCamera::remove_dynImage_dynamic_attribute
		if (free_it)
			delete[] ite->second;
		dynImage_data.erase(ite);
	}
}


//============================================================
//	Tool methods to get pointer on attribute data buffer 
//============================================================
//--------------------------------------------------------
/**
 *	Return a pointer on dynImage data.
 *
 *  parameter attname: the specified attribute name.
 */
//--------------------------------------------------------
Tango::DevUShort *TANGOCamera::get_dynImage_data_ptr(string &name)
{
	map<string,Tango::DevUShort *>::iterator ite;
    if ((ite=dynImage_data.find(name))==dynImage_data.end())
    {
		TangoSys_OMemStream	tms;
		tms << "Dynamic attribute " << name << " has not been created";
		Tango::Except::throw_exception(
					(const char *)"ATTRIBUTE_NOT_FOUND",
					tms.str().c_str(),
					(const char *)"TANGOCamera::get_dynImage_data_ptr()");
    }
	return  ite->second;
}


//=============================================================
//	Add/Remove dynamic command methods
//=============================================================


} //	namespace
