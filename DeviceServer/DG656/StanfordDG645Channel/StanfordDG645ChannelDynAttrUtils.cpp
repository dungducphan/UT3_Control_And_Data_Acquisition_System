/*----- PROTECTED REGION ID(StanfordDG645Channel::DynAttrUtils.cpp) ENABLED START -----*/
//=============================================================================
//
// file :        StanfordDG645ChannelDynAttrUtils.cpp
//
// description : Dynamic attributes utilities file for the StanfordDG645Channel class
//
// project :     StanfordDG645Channel
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


#include <StanfordDG645Channel.h>
#include <StanfordDG645ChannelClass.h>

/*----- PROTECTED REGION END -----*/	//	StanfordDG645Channel::DynAttrUtils.cpp

//================================================================
//  Attributes managed are:
//================================================================
//  TriggerPrescale  |  Tango::DevULong	Scalar
//  TriggerPhase     |  Tango::DevULong	Scalar
//  BurstMode        |  Tango::DevBoolean	Scalar
//================================================================

//	For compatibility reason, this file (StanfordDG645ChannelDynAttrUtils)
//	manage also the dynamic command utilities.
//================================================================
//  The following table gives the correspondence
//  between command and method names.
//
//  Command name  |  Method name
//================================================================
//================================================================

namespace StanfordDG645Channel_ns
{
//=============================================================
//	Add/Remove dynamic attribute methods
//=============================================================

//--------------------------------------------------------
/**
 *	Add a TriggerPrescale dynamic attribute.
 *
 *  parameter attname: attribute name to be cretated and added.
 */
//--------------------------------------------------------
void StanfordDG645Channel::add_TriggerPrescale_dynamic_attribute(string attname)
{
	//	Attribute : TriggerPrescale
	TriggerPrescaleAttrib	*triggerprescale = new TriggerPrescaleAttrib(attname);
	Tango::UserDefaultAttrProp	triggerprescale_prop;
	triggerprescale_prop.set_description("This is a divider to the original delay cyle frequency. If set to values > 1, only every Nth delay cyle will trigger the output. The valid range covers [1..2^30-1], 1 will disable the feature. Makes use of the advanced triggering mode.");
	//	label	not set for TriggerPrescale
	//	unit	not set for TriggerPrescale
	//	standard_unit	not set for TriggerPrescale
	//	display_unit	not set for TriggerPrescale
	triggerprescale_prop.set_format("%d");
	//	max_value	not set for TriggerPrescale
	//	min_value	not set for TriggerPrescale
	//	max_alarm	not set for TriggerPrescale
	//	min_alarm	not set for TriggerPrescale
	//	max_warning	not set for TriggerPrescale
	//	min_warning	not set for TriggerPrescale
	//	delta_t	not set for TriggerPrescale
	//	delta_val	not set for TriggerPrescale
	
	/*----- PROTECTED REGION ID(StanfordDG645Channel::att_TriggerPrescale_dynamic_attribute) ENABLED START -----*/
	
	
	/*----- PROTECTED REGION END -----*/	//	StanfordDG645Channel::att_TriggerPrescale_dynamic_attribute
	triggerprescale->set_default_properties(triggerprescale_prop);
	//	Not Polled
	triggerprescale->set_disp_level(Tango::OPERATOR);
	triggerprescale->set_memorized();
	triggerprescale->set_memorized_init(true);
	TriggerPrescale_data.insert(make_pair(attname, 0));
	add_attribute(triggerprescale);
}
//--------------------------------------------------------
/**
 *	remove a TriggerPrescale dynamic attribute.
 *
 *  parameter attname: attribute name to be removed.
 */
//--------------------------------------------------------
void StanfordDG645Channel::remove_TriggerPrescale_dynamic_attribute(string attname)
{
	remove_attribute(attname, true, Tango::Util::instance()->_UseDb);
	map<string,Tango::DevULong>::iterator ite;
    if ((ite=TriggerPrescale_data.find(attname))!=TriggerPrescale_data.end())
    {
    	/*----- PROTECTED REGION ID(StanfordDG645Channel::remove_TriggerPrescale_dynamic_attribute) ENABLED START -----*/
    	
    	/*----- PROTECTED REGION END -----*/	//	StanfordDG645Channel::remove_TriggerPrescale_dynamic_attribute
		TriggerPrescale_data.erase(ite);
	}
}
//--------------------------------------------------------
/**
 *	Add a TriggerPhase dynamic attribute.
 *
 *  parameter attname: attribute name to be cretated and added.
 */
//--------------------------------------------------------
void StanfordDG645Channel::add_TriggerPhase_dynamic_attribute(string attname)
{
	//	Attribute : TriggerPhase
	TriggerPhaseAttrib	*triggerphase = new TriggerPhaseAttrib(attname);
	Tango::UserDefaultAttrProp	triggerphase_prop;
	triggerphase_prop.set_description("This determines the phase at which the associated output is enabled. The output is enabled when the prescaler counter equals the phase factor.");
	//	label	not set for TriggerPhase
	//	unit	not set for TriggerPhase
	//	standard_unit	not set for TriggerPhase
	//	display_unit	not set for TriggerPhase
	triggerphase_prop.set_format("%d");
	//	max_value	not set for TriggerPhase
	//	min_value	not set for TriggerPhase
	//	max_alarm	not set for TriggerPhase
	//	min_alarm	not set for TriggerPhase
	//	max_warning	not set for TriggerPhase
	//	min_warning	not set for TriggerPhase
	//	delta_t	not set for TriggerPhase
	//	delta_val	not set for TriggerPhase
	
	/*----- PROTECTED REGION ID(StanfordDG645Channel::att_TriggerPhase_dynamic_attribute) ENABLED START -----*/
	
	
	/*----- PROTECTED REGION END -----*/	//	StanfordDG645Channel::att_TriggerPhase_dynamic_attribute
	triggerphase->set_default_properties(triggerphase_prop);
	//	Not Polled
	triggerphase->set_disp_level(Tango::OPERATOR);
	triggerphase->set_memorized();
	triggerphase->set_memorized_init(true);
	TriggerPhase_data.insert(make_pair(attname, 0));
	add_attribute(triggerphase);
}
//--------------------------------------------------------
/**
 *	remove a TriggerPhase dynamic attribute.
 *
 *  parameter attname: attribute name to be removed.
 */
//--------------------------------------------------------
void StanfordDG645Channel::remove_TriggerPhase_dynamic_attribute(string attname)
{
	remove_attribute(attname, true, Tango::Util::instance()->_UseDb);
	map<string,Tango::DevULong>::iterator ite;
    if ((ite=TriggerPhase_data.find(attname))!=TriggerPhase_data.end())
    {
    	/*----- PROTECTED REGION ID(StanfordDG645Channel::remove_TriggerPhase_dynamic_attribute) ENABLED START -----*/
    	
    	/*----- PROTECTED REGION END -----*/	//	StanfordDG645Channel::remove_TriggerPhase_dynamic_attribute
		TriggerPhase_data.erase(ite);
	}
}
//--------------------------------------------------------
/**
 *	Add a BurstMode dynamic attribute.
 *
 *  parameter attname: attribute name to be cretated and added.
 */
//--------------------------------------------------------
void StanfordDG645Channel::add_BurstMode_dynamic_attribute(string attname)
{
	//	Attribute : BurstMode
	BurstModeAttrib	*burstmode = new BurstModeAttrib(attname);
	Tango::UserDefaultAttrProp	burstmode_prop;
	burstmode_prop.set_description("If true, the T0 output is enabled for all delay cycles of the burst. Otherwise it is enabled for first delay cycle of the burst only.");
	//	label	not set for BurstMode
	//	unit	not set for BurstMode
	//	standard_unit	not set for BurstMode
	//	display_unit	not set for BurstMode
	//	format	not set for BurstMode
	//	max_value	not set for BurstMode
	//	min_value	not set for BurstMode
	//	max_alarm	not set for BurstMode
	//	min_alarm	not set for BurstMode
	//	max_warning	not set for BurstMode
	//	min_warning	not set for BurstMode
	//	delta_t	not set for BurstMode
	//	delta_val	not set for BurstMode
	
	/*----- PROTECTED REGION ID(StanfordDG645Channel::att_BurstMode_dynamic_attribute) ENABLED START -----*/
	
	
	/*----- PROTECTED REGION END -----*/	//	StanfordDG645Channel::att_BurstMode_dynamic_attribute
	burstmode->set_default_properties(burstmode_prop);
	//	Not Polled
	burstmode->set_disp_level(Tango::OPERATOR);
	burstmode->set_memorized();
	burstmode->set_memorized_init(true);
	BurstMode_data.insert(make_pair(attname, false));
	add_attribute(burstmode);
}
//--------------------------------------------------------
/**
 *	remove a BurstMode dynamic attribute.
 *
 *  parameter attname: attribute name to be removed.
 */
//--------------------------------------------------------
void StanfordDG645Channel::remove_BurstMode_dynamic_attribute(string attname)
{
	remove_attribute(attname, true, Tango::Util::instance()->_UseDb);
	map<string,Tango::DevBoolean>::iterator ite;
    if ((ite=BurstMode_data.find(attname))!=BurstMode_data.end())
    {
    	/*----- PROTECTED REGION ID(StanfordDG645Channel::remove_BurstMode_dynamic_attribute) ENABLED START -----*/
    	
    	/*----- PROTECTED REGION END -----*/	//	StanfordDG645Channel::remove_BurstMode_dynamic_attribute
		BurstMode_data.erase(ite);
	}
}


//============================================================
//	Tool methods to get pointer on attribute data buffer 
//============================================================
//--------------------------------------------------------
/**
 *	Return a pointer on TriggerPrescale data.
 *
 *  parameter attname: the specified attribute name.
 */
//--------------------------------------------------------
Tango::DevULong *StanfordDG645Channel::get_TriggerPrescale_data_ptr(string &name)
{
	map<string,Tango::DevULong>::iterator ite;
    if ((ite=TriggerPrescale_data.find(name))==TriggerPrescale_data.end())
    {
		TangoSys_OMemStream	tms;
		tms << "Dynamic attribute " << name << " has not been created";
		Tango::Except::throw_exception(
					(const char *)"ATTRIBUTE_NOT_FOUND",
					tms.str().c_str(),
					(const char *)"StanfordDG645Channel::get_TriggerPrescale_data_ptr()");
    }
	return  &(ite->second);
}
//--------------------------------------------------------
/**
 *	Return a pointer on TriggerPhase data.
 *
 *  parameter attname: the specified attribute name.
 */
//--------------------------------------------------------
Tango::DevULong *StanfordDG645Channel::get_TriggerPhase_data_ptr(string &name)
{
	map<string,Tango::DevULong>::iterator ite;
    if ((ite=TriggerPhase_data.find(name))==TriggerPhase_data.end())
    {
		TangoSys_OMemStream	tms;
		tms << "Dynamic attribute " << name << " has not been created";
		Tango::Except::throw_exception(
					(const char *)"ATTRIBUTE_NOT_FOUND",
					tms.str().c_str(),
					(const char *)"StanfordDG645Channel::get_TriggerPhase_data_ptr()");
    }
	return  &(ite->second);
}
//--------------------------------------------------------
/**
 *	Return a pointer on BurstMode data.
 *
 *  parameter attname: the specified attribute name.
 */
//--------------------------------------------------------
Tango::DevBoolean *StanfordDG645Channel::get_BurstMode_data_ptr(string &name)
{
	map<string,Tango::DevBoolean>::iterator ite;
    if ((ite=BurstMode_data.find(name))==BurstMode_data.end())
    {
		TangoSys_OMemStream	tms;
		tms << "Dynamic attribute " << name << " has not been created";
		Tango::Except::throw_exception(
					(const char *)"ATTRIBUTE_NOT_FOUND",
					tms.str().c_str(),
					(const char *)"StanfordDG645Channel::get_BurstMode_data_ptr()");
    }
	return  &(ite->second);
}


//=============================================================
//	Add/Remove dynamic command methods
//=============================================================


} //	namespace
