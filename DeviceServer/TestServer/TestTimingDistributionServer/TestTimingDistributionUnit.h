/*----- PROTECTED REGION ID(TestTimingDistributionUnit.h) ENABLED START -----*/
//=============================================================================
//
// file :        TestTimingDistributionUnit.h
//
// description : Include file for the TestTimingDistributionUnit class
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


#ifndef TestTimingDistributionUnit_H
#define TestTimingDistributionUnit_H

#include <tango.h>


/*----- PROTECTED REGION END -----*/	//	TestTimingDistributionUnit.h

/**
 *  TestTimingDistributionUnit class description:
 *    
 */

namespace TestTimingDistributionUnit_ns
{
/*----- PROTECTED REGION ID(TestTimingDistributionUnit::Additional Class Declarations) ENABLED START -----*/

//	Additional Class Declarations

/*----- PROTECTED REGION END -----*/	//	TestTimingDistributionUnit::Additional Class Declarations

class TestTimingDistributionUnit : public TANGO_BASE_CLASS
{

/*----- PROTECTED REGION ID(TestTimingDistributionUnit::Data Members) ENABLED START -----*/

//	Add your own data members

/*----- PROTECTED REGION END -----*/	//	TestTimingDistributionUnit::Data Members


//	Attribute data members
public:
	Tango::DevULong64	*attr_Timestamp_read;

//	Constructors and destructors
public:
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device Name
	 */
	TestTimingDistributionUnit(Tango::DeviceClass *cl,string &s);
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device Name
	 */
	TestTimingDistributionUnit(Tango::DeviceClass *cl,const char *s);
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device name
	 *	@param d	Device description.
	 */
	TestTimingDistributionUnit(Tango::DeviceClass *cl,const char *s,const char *d);
	/**
	 * The device object destructor.
	 */
	~TestTimingDistributionUnit() {delete_device();};


//	Miscellaneous methods
public:
	/*
	 *	will be called at device destruction or at init command.
	 */
	void delete_device();
	/*
	 *	Initialize the device
	 */
	virtual void init_device();
	/*
	 *	Always executed method before execution command method.
	 */
	virtual void always_executed_hook();


//	Attribute methods
public:
	//--------------------------------------------------------
	/*
	 *	Method      : TestTimingDistributionUnit::read_attr_hardware()
	 *	Description : Hardware acquisition for attributes.
	 */
	//--------------------------------------------------------
	virtual void read_attr_hardware(vector<long> &attr_list);

/**
 *	Attribute Timestamp related methods
 *	Description: 
 *
 *	Data type:	Tango::DevULong64
 *	Attr type:	Scalar
 */
	virtual void read_Timestamp(Tango::Attribute &attr);
	virtual bool is_Timestamp_allowed(Tango::AttReqType type);


	//--------------------------------------------------------
	/**
	 *	Method      : TestTimingDistributionUnit::add_dynamic_attributes()
	 *	Description : Add dynamic attributes if any.
	 */
	//--------------------------------------------------------
	void add_dynamic_attributes();




//	Command related methods
public:


	//--------------------------------------------------------
	/**
	 *	Method      : TestTimingDistributionUnit::add_dynamic_commands()
	 *	Description : Add dynamic commands if any.
	 */
	//--------------------------------------------------------
	void add_dynamic_commands();

/*----- PROTECTED REGION ID(TestTimingDistributionUnit::Additional Method prototypes) ENABLED START -----*/

//	Additional Method prototypes

/*----- PROTECTED REGION END -----*/	//	TestTimingDistributionUnit::Additional Method prototypes
};

/*----- PROTECTED REGION ID(TestTimingDistributionUnit::Additional Classes Definitions) ENABLED START -----*/

//	Additional Classes Definitions

/*----- PROTECTED REGION END -----*/	//	TestTimingDistributionUnit::Additional Classes Definitions

}	//	End of namespace

#endif   //	TestTimingDistributionUnit_H
