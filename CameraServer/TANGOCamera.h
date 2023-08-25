/*----- PROTECTED REGION ID(TANGOCamera.h) ENABLED START -----*/
//=============================================================================
//
// file :        TANGOCamera.h
//
// description : Include file for the TANGOCamera class
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


#ifndef TANGOCamera_H
#define TANGOCamera_H

#include <tango.h>
#include <CameraDriverFactory.h>


/*----- PROTECTED REGION END -----*/	//	TANGOCamera.h

/**
 *  TANGOCamera class description:
 *    
 */

namespace TANGOCamera_ns
{
/*----- PROTECTED REGION ID(TANGOCamera::Additional Class Declarations) ENABLED START -----*/

//	Additional Class Declarations

/*----- PROTECTED REGION END -----*/	//	TANGOCamera::Additional Class Declarations

class TANGOCamera : public TANGO_BASE_CLASS
{

/*----- PROTECTED REGION ID(TANGOCamera::Data Members) ENABLED START -----*/

//	Add your own data members

    CameraDriver* cameraDriverPtr;

/*----- PROTECTED REGION END -----*/	//	TANGOCamera::Data Members

//	Device property data members
public:
	//	serialNumber:	
	string	serialNumber;
	//	vendor:	
	string	vendor;

	bool	mandatoryNotDefined;

//	Attribute data members
public:
	Tango::DevString	*attr_baseOutputPath_read;
	Tango::DevDouble	*attr_image_read;

//	Constructors and destructors
public:
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device Name
	 */
	TANGOCamera(Tango::DeviceClass *cl,string &s);
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device Name
	 */
	TANGOCamera(Tango::DeviceClass *cl,const char *s);
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device name
	 *	@param d	Device description.
	 */
	TANGOCamera(Tango::DeviceClass *cl,const char *s,const char *d);
	/**
	 * The device object destructor.
	 */
	~TANGOCamera() {delete_device();};


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
	 *	Read the device properties from database
	 */
	void get_device_property();
	/*
	 *	Always executed method before execution command method.
	 */
	virtual void always_executed_hook();

	/*
	 *	Check if mandatory property has been set
	 */
	 void check_mandatory_property(Tango::DbDatum &class_prop, Tango::DbDatum &dev_prop);

//	Attribute methods
public:
	//--------------------------------------------------------
	/*
	 *	Method      : TANGOCamera::read_attr_hardware()
	 *	Description : Hardware acquisition for attributes.
	 */
	//--------------------------------------------------------
	virtual void read_attr_hardware(vector<long> &attr_list);
	//--------------------------------------------------------
	/*
	 *	Method      : TANGOCamera::write_attr_hardware()
	 *	Description : Hardware writing for attributes.
	 */
	//--------------------------------------------------------
	virtual void write_attr_hardware(vector<long> &attr_list);

/**
 *	Attribute baseOutputPath related methods
 *	Description: The base directory to save the images from the camera.
 *
 *	Data type:	Tango::DevString
 *	Attr type:	Scalar
 */
	virtual void read_baseOutputPath(Tango::Attribute &attr);
	virtual void write_baseOutputPath(Tango::WAttribute &attr);
	virtual bool is_baseOutputPath_allowed(Tango::AttReqType type);
/**
 *	Attribute image related methods
 *	Description: An image acquired by the camera
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Image max = 1440 x 1080
 */
	virtual void read_image(Tango::Attribute &attr);
	virtual bool is_image_allowed(Tango::AttReqType type);


	//--------------------------------------------------------
	/**
	 *	Method      : TANGOCamera::add_dynamic_attributes()
	 *	Description : Add dynamic attributes if any.
	 */
	//--------------------------------------------------------
	void add_dynamic_attributes();




//	Command related methods
public:
	/**
	 *	Command StartAcquisition related method
	 *	Description: Start image acquisition
	 *
	 */
	virtual void start_acquisition();
	virtual bool is_StartAcquisition_allowed(const CORBA::Any &any);
	/**
	 *	Command StopAcquisition related method
	 *	Description: Stop image acquisition
	 *
	 */
	virtual void stop_acquisition();
	virtual bool is_StopAcquisition_allowed(const CORBA::Any &any);
	/**
	 *	Command ManualTrigger related method
	 *	Description: Issue manual trigger
	 *
	 */
	virtual void manual_trigger();
	virtual bool is_ManualTrigger_allowed(const CORBA::Any &any);


	//--------------------------------------------------------
	/**
	 *	Method      : TANGOCamera::add_dynamic_commands()
	 *	Description : Add dynamic commands if any.
	 */
	//--------------------------------------------------------
	void add_dynamic_commands();

/*----- PROTECTED REGION ID(TANGOCamera::Additional Method prototypes) ENABLED START -----*/

//	Additional Method prototypes

/*----- PROTECTED REGION END -----*/	//	TANGOCamera::Additional Method prototypes
};

/*----- PROTECTED REGION ID(TANGOCamera::Additional Classes Definitions) ENABLED START -----*/

//	Additional Classes Definitions

/*----- PROTECTED REGION END -----*/	//	TANGOCamera::Additional Classes Definitions

}	//	End of namespace

#endif   //	TANGOCamera_H
