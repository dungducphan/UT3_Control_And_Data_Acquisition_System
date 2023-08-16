/*----- PROTECTED REGION ID(TANGOCameraStateMachine.cpp) ENABLED START -----*/
//=============================================================================
//
// file :        TANGOCameraStateMachine.cpp
//
// description : State machine file for the TANGOCamera class
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

/*----- PROTECTED REGION END -----*/	//	TANGOCamera::TANGOCameraStateMachine.cpp

//================================================================
//  States   |  Description
//================================================================
//  ON       |  
//  RUNNING  |  
//  FAULT    |  
//  OFF      |  


namespace TANGOCamera_ns
{
//=================================================
//		Attributes Allowed Methods
//=================================================


//=================================================
//		Commands Allowed Methods
//=================================================

//--------------------------------------------------------
/**
 *	Method      : TANGOCamera::is_StartAcquisition_allowed()
 *	Description : Execution allowed for StartAcquisition attribute
 */
//--------------------------------------------------------
bool TANGOCamera::is_StartAcquisition_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
	//	Compare device state with not allowed states.
	if (get_state()==Tango::RUNNING ||
		get_state()==Tango::FAULT ||
		get_state()==Tango::OFF)
	{
	/*----- PROTECTED REGION ID(TANGOCamera::StartAcquisitionStateAllowed) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	TANGOCamera::StartAcquisitionStateAllowed
		return false;
	}
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : TANGOCamera::is_StopAcquisition_allowed()
 *	Description : Execution allowed for StopAcquisition attribute
 */
//--------------------------------------------------------
bool TANGOCamera::is_StopAcquisition_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
	//	Compare device state with not allowed states.
	if (get_state()==Tango::FAULT ||
		get_state()==Tango::OFF)
	{
	/*----- PROTECTED REGION ID(TANGOCamera::StopAcquisitionStateAllowed) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	TANGOCamera::StopAcquisitionStateAllowed
		return false;
	}
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : TANGOCamera::is_ManualTrigger_allowed()
 *	Description : Execution allowed for ManualTrigger attribute
 */
//--------------------------------------------------------
bool TANGOCamera::is_ManualTrigger_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
	//	Compare device state with not allowed states.
	if (get_state()==Tango::ON ||
		get_state()==Tango::FAULT ||
		get_state()==Tango::OFF)
	{
	/*----- PROTECTED REGION ID(TANGOCamera::ManualTriggerStateAllowed) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	TANGOCamera::ManualTriggerStateAllowed
		return false;
	}
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : TANGOCamera::is_Configure_allowed()
 *	Description : Execution allowed for Configure attribute
 */
//--------------------------------------------------------
bool TANGOCamera::is_Configure_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
	//	Compare device state with not allowed states.
	if (get_state()==Tango::RUNNING ||
		get_state()==Tango::FAULT ||
		get_state()==Tango::OFF)
	{
	/*----- PROTECTED REGION ID(TANGOCamera::ConfigureStateAllowed) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	TANGOCamera::ConfigureStateAllowed
		return false;
	}
	return true;
}


/*----- PROTECTED REGION ID(TANGOCamera::TANGOCameraStateAllowed.AdditionalMethods) ENABLED START -----*/

//	Additional Methods

/*----- PROTECTED REGION END -----*/	//	TANGOCamera::TANGOCameraStateAllowed.AdditionalMethods

}	//	End of namespace
