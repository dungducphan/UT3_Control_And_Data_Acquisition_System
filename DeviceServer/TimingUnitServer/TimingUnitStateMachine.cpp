/*----- PROTECTED REGION ID(TimingUnitStateMachine.cpp) ENABLED START -----*/
//=============================================================================
//
// file :        TimingUnitStateMachine.cpp
//
// description : State machine file for the TimingUnit class
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

#include <TimingUnit.h>

/*----- PROTECTED REGION END -----*/	//	TimingUnit::TimingUnitStateMachine.cpp

//================================================================
//  States   |  Description
//================================================================
//  ON       |  
//  OFF      |  
//  RUNNING  |  


namespace TimingUnit_ns
{
//=================================================
//		Attributes Allowed Methods
//=================================================

//--------------------------------------------------------
/**
 *	Method      : TimingUnit::is_DelayPortB_allowed()
 *	Description : Execution allowed for DelayPortB attribute
 */
//--------------------------------------------------------
bool TimingUnit::is_DelayPortB_allowed(TANGO_UNUSED(Tango::AttReqType type))
{
	//	Check access type.
	if ( type!=Tango::READ_REQ )
	{
		//	Compare device state with not allowed states for WRITE 
		if (get_state()==Tango::OFF ||
			get_state()==Tango::RUNNING)
		{
		/*----- PROTECTED REGION ID(TimingUnit::DelayPortBStateAllowed_WRITE) ENABLED START -----*/
		
		/*----- PROTECTED REGION END -----*/	//	TimingUnit::DelayPortBStateAllowed_WRITE
			return false;
		}
		return true;
	}
	else

	//	Check access type.
	if ( type==Tango::READ_REQ )
	{
		//	Compare device state with not allowed states for READ 
		if (get_state()==Tango::OFF ||
			get_state()==Tango::RUNNING)
		{
		/*----- PROTECTED REGION ID(TimingUnit::DelayPortBStateAllowed_READ) ENABLED START -----*/
		
		/*----- PROTECTED REGION END -----*/	//	TimingUnit::DelayPortBStateAllowed_READ
			return false;
		}
		return true;
	}
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : TimingUnit::is_DelayPortD_allowed()
 *	Description : Execution allowed for DelayPortD attribute
 */
//--------------------------------------------------------
bool TimingUnit::is_DelayPortD_allowed(TANGO_UNUSED(Tango::AttReqType type))
{
	//	Not any excluded states for DelayPortD attribute in Write access.
	/*----- PROTECTED REGION ID(TimingUnit::DelayPortDStateAllowed_WRITE) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	TimingUnit::DelayPortDStateAllowed_WRITE

	//	Not any excluded states for DelayPortD attribute in read access.
	/*----- PROTECTED REGION ID(TimingUnit::DelayPortDStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	TimingUnit::DelayPortDStateAllowed_READ
	return true;
}


//=================================================
//		Commands Allowed Methods
//=================================================

//--------------------------------------------------------
/**
 *	Method      : TimingUnit::is_Configure_allowed()
 *	Description : Execution allowed for Configure attribute
 */
//--------------------------------------------------------
bool TimingUnit::is_Configure_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
	//	Compare device state with not allowed states.
	if (get_state()==Tango::OFF ||
		get_state()==Tango::RUNNING)
	{
	/*----- PROTECTED REGION ID(TimingUnit::ConfigureStateAllowed) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	TimingUnit::ConfigureStateAllowed
		return false;
	}
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : TimingUnit::is_Start_allowed()
 *	Description : Execution allowed for Start attribute
 */
//--------------------------------------------------------
bool TimingUnit::is_Start_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
	//	Compare device state with not allowed states.
	if (get_state()==Tango::OFF ||
		get_state()==Tango::RUNNING)
	{
	/*----- PROTECTED REGION ID(TimingUnit::StartStateAllowed) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	TimingUnit::StartStateAllowed
		return false;
	}
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : TimingUnit::is_Stop_allowed()
 *	Description : Execution allowed for Stop attribute
 */
//--------------------------------------------------------
bool TimingUnit::is_Stop_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
	//	Compare device state with not allowed states.
	if (get_state()==Tango::ON ||
		get_state()==Tango::OFF)
	{
	/*----- PROTECTED REGION ID(TimingUnit::StopStateAllowed) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	TimingUnit::StopStateAllowed
		return false;
	}
	return true;
}


/*----- PROTECTED REGION ID(TimingUnit::TimingUnitStateAllowed.AdditionalMethods) ENABLED START -----*/

//	Additional Methods

/*----- PROTECTED REGION END -----*/	//	TimingUnit::TimingUnitStateAllowed.AdditionalMethods

}	//	End of namespace
