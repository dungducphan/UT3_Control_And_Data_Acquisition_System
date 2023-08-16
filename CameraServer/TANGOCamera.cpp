/*----- PROTECTED REGION ID(TANGOCamera.cpp) ENABLED START -----*/
//=============================================================================
//
// file :        TANGOCamera.cpp
//
// description : C++ source for the TANGOCamera class and its commands.
//               The class is derived from Device. It represents the
//               CORBA servant object which will be accessed from the
//               network. All commands which can be executed on the
//               TANGOCamera are implemented in this file.
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

/*----- PROTECTED REGION END -----*/	//	TANGOCamera.cpp

/**
 *  TANGOCamera class description:
 *    
 */

//================================================================
//  The following table gives the correspondence
//  between command and method names.
//
//  Command name      |  Method name
//================================================================
//  State             |  Inherited (no method)
//  Status            |  Inherited (no method)
//  StartAcquisition  |  start_acquisition
//  StopAcquisition   |  stop_acquisition
//  ManualTrigger     |  manual_trigger
//  Configure         |  configure
//================================================================

//================================================================
//  Attributes managed is:
//================================================================
//================================================================

namespace TANGOCamera_ns
{
/*----- PROTECTED REGION ID(TANGOCamera::namespace_starting) ENABLED START -----*/

//	static initializations

/*----- PROTECTED REGION END -----*/	//	TANGOCamera::namespace_starting

//--------------------------------------------------------
/**
 *	Method      : TANGOCamera::TANGOCamera()
 *	Description : Constructors for a Tango device
 *                implementing the classTANGOCamera
 */
//--------------------------------------------------------
TANGOCamera::TANGOCamera(Tango::DeviceClass *cl, string &s)
 : TANGO_BASE_CLASS(cl, s.c_str())
{
	/*----- PROTECTED REGION ID(TANGOCamera::constructor_1) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	TANGOCamera::constructor_1
}
//--------------------------------------------------------
TANGOCamera::TANGOCamera(Tango::DeviceClass *cl, const char *s)
 : TANGO_BASE_CLASS(cl, s)
{
	/*----- PROTECTED REGION ID(TANGOCamera::constructor_2) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	TANGOCamera::constructor_2
}
//--------------------------------------------------------
TANGOCamera::TANGOCamera(Tango::DeviceClass *cl, const char *s, const char *d)
 : TANGO_BASE_CLASS(cl, s, d)
{
	/*----- PROTECTED REGION ID(TANGOCamera::constructor_3) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	TANGOCamera::constructor_3
}

//--------------------------------------------------------
/**
 *	Method      : TANGOCamera::delete_device()
 *	Description : will be called at device destruction or at init command
 */
//--------------------------------------------------------
void TANGOCamera::delete_device()
{
	DEBUG_STREAM << "TANGOCamera::delete_device() " << device_name << endl;
	/*----- PROTECTED REGION ID(TANGOCamera::delete_device) ENABLED START -----*/

	//	Delete device allocated objects

	/*----- PROTECTED REGION END -----*/	//	TANGOCamera::delete_device
}

//--------------------------------------------------------
/**
 *	Method      : TANGOCamera::init_device()
 *	Description : will be called at device initialization.
 */
//--------------------------------------------------------
void TANGOCamera::init_device()
{
	DEBUG_STREAM << "TANGOCamera::init_device() create device " << device_name << endl;
	/*----- PROTECTED REGION ID(TANGOCamera::init_device_before) ENABLED START -----*/
	
	//	Initialization before get_device_property() call
	
	/*----- PROTECTED REGION END -----*/	//	TANGOCamera::init_device_before
	

	//	Get the device properties from database
	get_device_property();
	
	//	No longer if mandatory property not set. 
	if (mandatoryNotDefined)
		return;

	/*----- PROTECTED REGION ID(TANGOCamera::init_device) ENABLED START -----*/
	
	//	Initialize device
    cameraDriverPtr = CameraDriverCreator::FactoryMethod(vendor, ipaddress);
	
	/*----- PROTECTED REGION END -----*/	//	TANGOCamera::init_device
}

//--------------------------------------------------------
/**
 *	Method      : TANGOCamera::get_device_property()
 *	Description : Read database to initialize property data members.
 */
//--------------------------------------------------------
void TANGOCamera::get_device_property()
{
	/*----- PROTECTED REGION ID(TANGOCamera::get_device_property_before) ENABLED START -----*/
	
	//	Initialize property data members
	
	/*----- PROTECTED REGION END -----*/	//	TANGOCamera::get_device_property_before

	mandatoryNotDefined = false;

	//	Read device properties from database.
	Tango::DbData	dev_prop;
	dev_prop.push_back(Tango::DbDatum("ipaddress"));
	dev_prop.push_back(Tango::DbDatum("vendor"));

	//	is there at least one property to be read ?
	if (dev_prop.size()>0)
	{
		//	Call database and extract values
		if (Tango::Util::instance()->_UseDb==true)
			get_db_device()->get_property(dev_prop);
	
		//	get instance on TANGOCameraClass to get class property
		Tango::DbDatum	def_prop, cl_prop;
		TANGOCameraClass	*ds_class =
			(static_cast<TANGOCameraClass *>(get_device_class()));
		int	i = -1;

		//	Try to initialize ipaddress from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  ipaddress;
		else {
			//	Try to initialize ipaddress from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  ipaddress;
		}
		//	And try to extract ipaddress value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  ipaddress;
		//	Property StartDsPath is mandatory, check if has been defined in database.
		check_mandatory_property(cl_prop, dev_prop[i]);

		//	Try to initialize vendor from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  vendor;
		else {
			//	Try to initialize vendor from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  vendor;
		}
		//	And try to extract vendor value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  vendor;
		//	Property StartDsPath is mandatory, check if has been defined in database.
		check_mandatory_property(cl_prop, dev_prop[i]);

	}

	/*----- PROTECTED REGION ID(TANGOCamera::get_device_property_after) ENABLED START -----*/
	
	//	Check device property data members init
	
	/*----- PROTECTED REGION END -----*/	//	TANGOCamera::get_device_property_after
}
//--------------------------------------------------------
/**
 *	Method      : TANGOCamera::check_mandatory_property()
 *	Description : For mandatory properties check if defined in database.
 */
//--------------------------------------------------------
void TANGOCamera::check_mandatory_property(Tango::DbDatum &class_prop, Tango::DbDatum &dev_prop)
{
	//	Check if all properties are empty
	if (class_prop.is_empty() && dev_prop.is_empty())
	{
		TangoSys_OMemStream	tms;
		tms << endl <<"Property \'" << dev_prop.name;
		if (Tango::Util::instance()->_UseDb==true)
			tms << "\' is mandatory but not defined in database";
		else
			tms << "\' is mandatory but cannot be defined without database";
		append_status(tms.str());
		mandatoryNotDefined = true;
		/*----- PROTECTED REGION ID(TANGOCamera::check_mandatory_property) ENABLED START -----*/
		cerr << tms.str() << " for " << device_name << endl;
		
		/*----- PROTECTED REGION END -----*/	//	TANGOCamera::check_mandatory_property
	}
}


//--------------------------------------------------------
/**
 *	Method      : TANGOCamera::always_executed_hook()
 *	Description : method always executed before any command is executed
 */
//--------------------------------------------------------
void TANGOCamera::always_executed_hook()
{
	DEBUG_STREAM << "TANGOCamera::always_executed_hook()  " << device_name << endl;
	if (mandatoryNotDefined)
	{
		Tango::Except::throw_exception(
					(const char *)"PROPERTY_NOT_SET",
					get_status().c_str(),
					(const char *)"TANGOCamera::always_executed_hook()");
	}
	/*----- PROTECTED REGION ID(TANGOCamera::always_executed_hook) ENABLED START -----*/
	
	//	code always executed before all requests
	
	/*----- PROTECTED REGION END -----*/	//	TANGOCamera::always_executed_hook
}

//--------------------------------------------------------
/**
 *	Method      : TANGOCamera::read_attr_hardware()
 *	Description : Hardware acquisition for attributes
 */
//--------------------------------------------------------
void TANGOCamera::read_attr_hardware(TANGO_UNUSED(vector<long> &attr_list))
{
	DEBUG_STREAM << "TANGOCamera::read_attr_hardware(vector<long> &attr_list) entering... " << endl;
	/*----- PROTECTED REGION ID(TANGOCamera::read_attr_hardware) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	TANGOCamera::read_attr_hardware
}


//--------------------------------------------------------
/**
 *	Method      : TANGOCamera::add_dynamic_attributes()
 *	Description : Create the dynamic attributes if any
 *                for specified device.
 */
//--------------------------------------------------------
void TANGOCamera::add_dynamic_attributes()
{
	/*----- PROTECTED REGION ID(TANGOCamera::add_dynamic_attributes) ENABLED START -----*/
	
	//	Add your own code to create and add dynamic attributes if any
	
	/*----- PROTECTED REGION END -----*/	//	TANGOCamera::add_dynamic_attributes
}

//--------------------------------------------------------
/**
 *	Command StartAcquisition related method
 *	Description: Start image acquisition
 *
 */
//--------------------------------------------------------
void TANGOCamera::start_acquisition()
{
	DEBUG_STREAM << "TANGOCamera::StartAcquisition()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(TANGOCamera::start_acquisition) ENABLED START -----*/
	
	//	Add your own code
    cameraDriverPtr->start_acquisition();
	
	/*----- PROTECTED REGION END -----*/	//	TANGOCamera::start_acquisition
}
//--------------------------------------------------------
/**
 *	Command StopAcquisition related method
 *	Description: Stop image acquisition
 *
 */
//--------------------------------------------------------
void TANGOCamera::stop_acquisition()
{
	DEBUG_STREAM << "TANGOCamera::StopAcquisition()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(TANGOCamera::stop_acquisition) ENABLED START -----*/
	
	//	Add your own code
    cameraDriverPtr->stop_acquisition();
	
	/*----- PROTECTED REGION END -----*/	//	TANGOCamera::stop_acquisition
}
//--------------------------------------------------------
/**
 *	Command ManualTrigger related method
 *	Description: Reset camera if in FAULT state
 *
 */
//--------------------------------------------------------
void TANGOCamera::manual_trigger()
{
	DEBUG_STREAM << "TANGOCamera::ManualTrigger()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(TANGOCamera::manual_trigger) ENABLED START -----*/
	
	//	Add your own code
    cameraDriverPtr->manual_trigger();
	
	/*----- PROTECTED REGION END -----*/	//	TANGOCamera::manual_trigger
}
//--------------------------------------------------------
/**
 *	Command Configure related method
 *	Description: 
 *
 */
//--------------------------------------------------------
void TANGOCamera::configure()
{
	DEBUG_STREAM << "TANGOCamera::Configure()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(TANGOCamera::configure) ENABLED START -----*/
	
	//	Add your own code
    cameraDriverPtr->configure();
	
	/*----- PROTECTED REGION END -----*/	//	TANGOCamera::configure
}
//--------------------------------------------------------
/**
 *	Method      : TANGOCamera::add_dynamic_commands()
 *	Description : Create the dynamic commands if any
 *                for specified device.
 */
//--------------------------------------------------------
void TANGOCamera::add_dynamic_commands()
{
	/*----- PROTECTED REGION ID(TANGOCamera::add_dynamic_commands) ENABLED START -----*/
	
	//	Add your own code to create and add dynamic commands if any
	
	/*----- PROTECTED REGION END -----*/	//	TANGOCamera::add_dynamic_commands
}

/*----- PROTECTED REGION ID(TANGOCamera::namespace_ending) ENABLED START -----*/

/*----- PROTECTED REGION END -----*/	//	TANGOCamera::namespace_ending
} //	namespace
