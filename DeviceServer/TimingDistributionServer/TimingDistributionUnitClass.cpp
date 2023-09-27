/*----- PROTECTED REGION ID(TimingDistributionUnitClass.cpp) ENABLED START -----*/
//=============================================================================
//
// file :        TimingDistributionUnitClass.cpp
//
// description : C++ source for the TimingDistributionUnitClass.
//               A singleton class derived from DeviceClass.
//               It implements the command and attribute list
//               and all properties and methods required
//               by the TimingDistributionUnit once per process.
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


#include <TimingDistributionUnitClass.h>

/*----- PROTECTED REGION END -----*/	//	TimingDistributionUnitClass.cpp

//-------------------------------------------------------------------
/**
 *	Create TimingDistributionUnitClass singleton and
 *	return it in a C function for Python usage
 */
//-------------------------------------------------------------------
extern "C" {
#ifdef _TG_WINDOWS_

__declspec(dllexport)

#endif

	Tango::DeviceClass *_create_TimingDistributionUnit_class(const char *name) {
		return TimingDistributionUnit_ns::TimingDistributionUnitClass::init(name);
	}
}

namespace TimingDistributionUnit_ns
{
//===================================================================
//	Initialize pointer for singleton pattern
//===================================================================
TimingDistributionUnitClass *TimingDistributionUnitClass::_instance = NULL;

//--------------------------------------------------------
/**
 * method : 		TimingDistributionUnitClass::TimingDistributionUnitClass(string &s)
 * description : 	constructor for the TimingDistributionUnitClass
 *
 * @param s	The class name
 */
//--------------------------------------------------------
TimingDistributionUnitClass::TimingDistributionUnitClass(string &s):Tango::DeviceClass(s)
{
	cout2 << "Entering TimingDistributionUnitClass constructor" << endl;
	set_default_property();
	write_class_property();

	/*----- PROTECTED REGION ID(TimingDistributionUnitClass::constructor) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	TimingDistributionUnitClass::constructor

	cout2 << "Leaving TimingDistributionUnitClass constructor" << endl;
}

//--------------------------------------------------------
/**
 * method : 		TimingDistributionUnitClass::~TimingDistributionUnitClass()
 * description : 	destructor for the TimingDistributionUnitClass
 */
//--------------------------------------------------------
TimingDistributionUnitClass::~TimingDistributionUnitClass()
{
	/*----- PROTECTED REGION ID(TimingDistributionUnitClass::destructor) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	TimingDistributionUnitClass::destructor

	_instance = NULL;
}


//--------------------------------------------------------
/**
 * method : 		TimingDistributionUnitClass::init
 * description : 	Create the object if not already done.
 *                  Otherwise, just return a pointer to the object
 *
 * @param	name	The class name
 */
//--------------------------------------------------------
TimingDistributionUnitClass *TimingDistributionUnitClass::init(const char *name)
{
	if (_instance == NULL)
	{
		try
		{
			string s(name);
			_instance = new TimingDistributionUnitClass(s);
		}
		catch (bad_alloc &)
		{
			throw;
		}
	}
	return _instance;
}

//--------------------------------------------------------
/**
 * method : 		TimingDistributionUnitClass::instance
 * description : 	Check if object already created,
 *                  and return a pointer to the object
 */
//--------------------------------------------------------
TimingDistributionUnitClass *TimingDistributionUnitClass::instance()
{
	if (_instance == NULL)
	{
		cerr << "Class is not initialised !!" << endl;
		exit(-1);
	}
	return _instance;
}



//===================================================================
//	Command execution method calls
//===================================================================

//===================================================================
//	Properties management
//===================================================================
//--------------------------------------------------------
/**
 *	Method      : TimingDistributionUnitClass::get_class_property()
 *	Description : Get the class property for specified name.
 */
//--------------------------------------------------------
Tango::DbDatum TimingDistributionUnitClass::get_class_property(string &prop_name)
{
	for (unsigned int i=0 ; i<cl_prop.size() ; i++)
		if (cl_prop[i].name == prop_name)
			return cl_prop[i];
	//	if not found, returns  an empty DbDatum
	return Tango::DbDatum(prop_name);
}

//--------------------------------------------------------
/**
 *	Method      : TimingDistributionUnitClass::get_default_device_property()
 *	Description : Return the default value for device property.
 */
//--------------------------------------------------------
Tango::DbDatum TimingDistributionUnitClass::get_default_device_property(string &prop_name)
{
	for (unsigned int i=0 ; i<dev_def_prop.size() ; i++)
		if (dev_def_prop[i].name == prop_name)
			return dev_def_prop[i];
	//	if not found, return  an empty DbDatum
	return Tango::DbDatum(prop_name);
}

//--------------------------------------------------------
/**
 *	Method      : TimingDistributionUnitClass::get_default_class_property()
 *	Description : Return the default value for class property.
 */
//--------------------------------------------------------
Tango::DbDatum TimingDistributionUnitClass::get_default_class_property(string &prop_name)
{
	for (unsigned int i=0 ; i<cl_def_prop.size() ; i++)
		if (cl_def_prop[i].name == prop_name)
			return cl_def_prop[i];
	//	if not found, return  an empty DbDatum
	return Tango::DbDatum(prop_name);
}


//--------------------------------------------------------
/**
 *	Method      : TimingDistributionUnitClass::set_default_property()
 *	Description : Set default property (class and device) for wizard.
 *                For each property, add to wizard property name and description.
 *                If default value has been set, add it to wizard property and
 *                store it in a DbDatum.
 */
//--------------------------------------------------------
void TimingDistributionUnitClass::set_default_property()
{
	string	prop_name;
	string	prop_desc;
	string	prop_def;
	vector<string>	vect_data;

	//	Set Default Class Properties

	//	Set Default device Properties
}

//--------------------------------------------------------
/**
 *	Method      : TimingDistributionUnitClass::write_class_property()
 *	Description : Set class description fields as property in database
 */
//--------------------------------------------------------
void TimingDistributionUnitClass::write_class_property()
{
	//	First time, check if database used
	if (Tango::Util::_UseDb == false)
		return;

	Tango::DbData	data;
	string	classname = get_name();
	string	header;
	string::size_type	start, end;

	//	Put title
	Tango::DbDatum	title("ProjectTitle");
	string	str_title("");
	title << str_title;
	data.push_back(title);

	//	Put Description
	Tango::DbDatum	description("Description");
	vector<string>	str_desc;
	str_desc.push_back("");
	description << str_desc;
	data.push_back(description);

	//  Put inheritance
	Tango::DbDatum	inher_datum("InheritedFrom");
	vector<string> inheritance;
	inheritance.push_back("TANGO_BASE_CLASS");
	inher_datum << inheritance;
	data.push_back(inher_datum);

	//	Call database and and values
	get_db_class()->put_property(data);
}

//===================================================================
//	Factory methods
//===================================================================

//--------------------------------------------------------
/**
 *	Method      : TimingDistributionUnitClass::device_factory()
 *	Description : Create the device object(s)
 *                and store them in the device list
 */
//--------------------------------------------------------
void TimingDistributionUnitClass::device_factory(const Tango::DevVarStringArray *devlist_ptr)
{
	/*----- PROTECTED REGION ID(TimingDistributionUnitClass::device_factory_before) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	TimingDistributionUnitClass::device_factory_before

	//	Create devices and add it into the device list
	for (unsigned long i=0 ; i<devlist_ptr->length() ; i++)
	{
		cout4 << "Device name : " << (*devlist_ptr)[i].in() << endl;
		device_list.push_back(new TimingDistributionUnit(this, (*devlist_ptr)[i]));
	}

	//	Manage dynamic attributes if any
	erase_dynamic_attributes(devlist_ptr, get_class_attr()->get_attr_list());

	//	Export devices to the outside world
	for (unsigned long i=1 ; i<=devlist_ptr->length() ; i++)
	{
		//	Add dynamic attributes if any
		TimingDistributionUnit *dev = static_cast<TimingDistributionUnit *>(device_list[device_list.size()-i]);
		dev->add_dynamic_attributes();

		//	Check before if database used.
		if ((Tango::Util::_UseDb == true) && (Tango::Util::_FileDb == false))
			export_device(dev);
		else
			export_device(dev, dev->get_name().c_str());
	}

	/*----- PROTECTED REGION ID(TimingDistributionUnitClass::device_factory_after) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	TimingDistributionUnitClass::device_factory_after
}
//--------------------------------------------------------
/**
 *	Method      : TimingDistributionUnitClass::attribute_factory()
 *	Description : Create the attribute object(s)
 *                and store them in the attribute list
 */
//--------------------------------------------------------
void TimingDistributionUnitClass::attribute_factory(vector<Tango::Attr *> &att_list)
{
	/*----- PROTECTED REGION ID(TimingDistributionUnitClass::attribute_factory_before) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	TimingDistributionUnitClass::attribute_factory_before
	//	Attribute : TriggerCounter
	TriggerCounterAttrib	*triggercounter = new TriggerCounterAttrib();
	Tango::UserDefaultAttrProp	triggercounter_prop;
	//	description	not set for TriggerCounter
	triggercounter_prop.set_label("Trigger Counter");
	//	unit	not set for TriggerCounter
	//	standard_unit	not set for TriggerCounter
	//	display_unit	not set for TriggerCounter
	//	format	not set for TriggerCounter
	//	max_value	not set for TriggerCounter
	//	min_value	not set for TriggerCounter
	//	max_alarm	not set for TriggerCounter
	//	min_alarm	not set for TriggerCounter
	//	max_warning	not set for TriggerCounter
	//	min_warning	not set for TriggerCounter
	//	delta_t	not set for TriggerCounter
	//	delta_val	not set for TriggerCounter
	
	triggercounter->set_default_properties(triggercounter_prop);
	//	Not Polled
	triggercounter->set_disp_level(Tango::OPERATOR);
	//	Not Memorized
	triggercounter->set_data_ready_event(true);
	att_list.push_back(triggercounter);


	//	Create a list of static attributes
	create_static_attribute_list(get_class_attr()->get_attr_list());
	/*----- PROTECTED REGION ID(TimingDistributionUnitClass::attribute_factory_after) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	TimingDistributionUnitClass::attribute_factory_after
}
//--------------------------------------------------------
/**
 *	Method      : TimingDistributionUnitClass::pipe_factory()
 *	Description : Create the pipe object(s)
 *                and store them in the pipe list
 */
//--------------------------------------------------------
void TimingDistributionUnitClass::pipe_factory()
{
	/*----- PROTECTED REGION ID(TimingDistributionUnitClass::pipe_factory_before) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	TimingDistributionUnitClass::pipe_factory_before
	/*----- PROTECTED REGION ID(TimingDistributionUnitClass::pipe_factory_after) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	TimingDistributionUnitClass::pipe_factory_after
}
//--------------------------------------------------------
/**
 *	Method      : TimingDistributionUnitClass::command_factory()
 *	Description : Create the command object(s)
 *                and store them in the command list
 */
//--------------------------------------------------------
void TimingDistributionUnitClass::command_factory()
{
	/*----- PROTECTED REGION ID(TimingDistributionUnitClass::command_factory_before) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	TimingDistributionUnitClass::command_factory_before


	/*----- PROTECTED REGION ID(TimingDistributionUnitClass::command_factory_after) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	TimingDistributionUnitClass::command_factory_after
}

//===================================================================
//	Dynamic attributes related methods
//===================================================================

//--------------------------------------------------------
/**
 * method : 		TimingDistributionUnitClass::create_static_attribute_list
 * description : 	Create the a list of static attributes
 *
 * @param	att_list	the ceated attribute list
 */
//--------------------------------------------------------
void TimingDistributionUnitClass::create_static_attribute_list(vector<Tango::Attr *> &att_list)
{
	for (unsigned long i=0 ; i<att_list.size() ; i++)
	{
		string att_name(att_list[i]->get_name());
		transform(att_name.begin(), att_name.end(), att_name.begin(), ::tolower);
		defaultAttList.push_back(att_name);
	}

	cout2 << defaultAttList.size() << " attributes in default list" << endl;

	/*----- PROTECTED REGION ID(TimingDistributionUnitClass::create_static_att_list) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	TimingDistributionUnitClass::create_static_att_list
}


//--------------------------------------------------------
/**
 * method : 		TimingDistributionUnitClass::erase_dynamic_attributes
 * description : 	delete the dynamic attributes if any.
 *
 * @param	devlist_ptr	the device list pointer
 * @param	list of all attributes
 */
//--------------------------------------------------------
void TimingDistributionUnitClass::erase_dynamic_attributes(const Tango::DevVarStringArray *devlist_ptr, vector<Tango::Attr *> &att_list)
{
	Tango::Util *tg = Tango::Util::instance();

	for (unsigned long i=0 ; i<devlist_ptr->length() ; i++)
	{
		Tango::DeviceImpl *dev_impl = tg->get_device_by_name(((string)(*devlist_ptr)[i]).c_str());
		TimingDistributionUnit *dev = static_cast<TimingDistributionUnit *> (dev_impl);

		vector<Tango::Attribute *> &dev_att_list = dev->get_device_attr()->get_attribute_list();
		vector<Tango::Attribute *>::iterator ite_att;
		for (ite_att=dev_att_list.begin() ; ite_att != dev_att_list.end() ; ++ite_att)
		{
			string att_name((*ite_att)->get_name_lower());
			if ((att_name == "state") || (att_name == "status"))
				continue;
			vector<string>::iterator ite_str = find(defaultAttList.begin(), defaultAttList.end(), att_name);
			if (ite_str == defaultAttList.end())
			{
				cout2 << att_name << " is a UNWANTED dynamic attribute for device " << (*devlist_ptr)[i] << endl;
				Tango::Attribute &att = dev->get_device_attr()->get_attr_by_name(att_name.c_str());
				dev->remove_attribute(att_list[att.get_attr_idx()], true, false);
				--ite_att;
			}
		}
	}
	/*----- PROTECTED REGION ID(TimingDistributionUnitClass::erase_dynamic_attributes) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	TimingDistributionUnitClass::erase_dynamic_attributes
}

//--------------------------------------------------------
/**
 *	Method      : TimingDistributionUnitClass::get_attr_object_by_name()
 *	Description : returns Tango::Attr * object found by name
 */
//--------------------------------------------------------
Tango::Attr *TimingDistributionUnitClass::get_attr_object_by_name(vector<Tango::Attr *> &att_list, string attname)
{
	vector<Tango::Attr *>::iterator it;
	for (it=att_list.begin() ; it<att_list.end() ; ++it)
		if ((*it)->get_name()==attname)
			return (*it);
	//	Attr does not exist
	return NULL;
}


/*----- PROTECTED REGION ID(TimingDistributionUnitClass::Additional Methods) ENABLED START -----*/

/*----- PROTECTED REGION END -----*/	//	TimingDistributionUnitClass::Additional Methods
} //	namespace
