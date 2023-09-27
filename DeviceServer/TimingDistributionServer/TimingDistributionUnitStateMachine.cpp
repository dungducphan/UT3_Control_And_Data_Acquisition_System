/*----- PROTECTED REGION ID(TimingDistributionUnitStateMachine.cpp) ENABLED START -----*/
//=============================================================================
//
// file :        TimingDistributionUnitStateMachine.cpp
//
// description : State machine file for the TimingDistributionUnit class
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

#include <TimingDistributionUnit.h>

/*----- PROTECTED REGION END -----*/	//	TimingDistributionUnit::TimingDistributionUnitStateMachine.cpp

//================================================================
//  States  |  Description
//================================================================


namespace TimingDistributionUnit_ns
{
//=================================================
//		Attributes Allowed Methods
//=================================================

//--------------------------------------------------------
/**
 *	Method      : TimingDistributionUnit::is_Timestamp_allowed()
 *	Description : Execution allowed for Timestamp attribute
 */
//--------------------------------------------------------
bool TimingDistributionUnit::is_Timestamp_allowed(TANGO_UNUSED(Tango::AttReqType type))
{

	//	Not any excluded states for Timestamp attribute in read access.
	/*----- PROTECTED REGION ID(TimingDistributionUnit::TimestampStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	TimingDistributionUnit::TimestampStateAllowed_READ
	return true;
}


//=================================================
//		Commands Allowed Methods
//=================================================


/*----- PROTECTED REGION ID(TimingDistributionUnit::TimingDistributionUnitStateAllowed.AdditionalMethods) ENABLED START -----*/

//	Additional Methods

/*----- PROTECTED REGION END -----*/	//	TimingDistributionUnit::TimingDistributionUnitStateAllowed.AdditionalMethods

}	//	End of namespace