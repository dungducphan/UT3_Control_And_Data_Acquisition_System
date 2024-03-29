/*----- PROTECTED REGION ID(TestTimingDistributionUnitClass.h) ENABLED START -----*/
//=============================================================================
//
// file :        TestTimingDistributionUnitClass.h
//
// description : Include for the TestTimingDistributionUnit root class.
//               This class is the singleton class for
//                the TestTimingDistributionUnit device class.
//               It contains all properties and methods which the 
//               TestTimingDistributionUnit requires only once e.g. the commands.
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


#ifndef TestTimingDistributionUnitClass_H
#define TestTimingDistributionUnitClass_H

#include <tango.h>
#include <TestTimingDistributionUnit.h>


/*----- PROTECTED REGION END -----*/	//	TestTimingDistributionUnitClass.h


namespace TestTimingDistributionUnit_ns
{
/*----- PROTECTED REGION ID(TestTimingDistributionUnitClass::classes for dynamic creation) ENABLED START -----*/


/*----- PROTECTED REGION END -----*/	//	TestTimingDistributionUnitClass::classes for dynamic creation

//=========================================
//	Define classes for attributes
//=========================================
//	Attribute Timestamp class definition
class TimestampAttrib: public Tango::Attr
{
public:
	TimestampAttrib():Attr("Timestamp",
			Tango::DEV_ULONG64, Tango::READ) {};
	~TimestampAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<TestTimingDistributionUnit *>(dev))->read_Timestamp(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<TestTimingDistributionUnit *>(dev))->is_Timestamp_allowed(ty);}
};


/**
 *	The TestTimingDistributionUnitClass singleton definition
 */

#ifdef _TG_WINDOWS_
class __declspec(dllexport)  TestTimingDistributionUnitClass : public Tango::DeviceClass
#else
class TestTimingDistributionUnitClass : public Tango::DeviceClass
#endif
{
	/*----- PROTECTED REGION ID(TestTimingDistributionUnitClass::Additionnal DServer data members) ENABLED START -----*/
	
	
	/*----- PROTECTED REGION END -----*/	//	TestTimingDistributionUnitClass::Additionnal DServer data members

	public:
		//	write class properties data members
		Tango::DbData	cl_prop;
		Tango::DbData	cl_def_prop;
		Tango::DbData	dev_def_prop;
	
		//	Method prototypes
		static TestTimingDistributionUnitClass *init(const char *);
		static TestTimingDistributionUnitClass *instance();
		~TestTimingDistributionUnitClass();
		Tango::DbDatum	get_class_property(string &);
		Tango::DbDatum	get_default_device_property(string &);
		Tango::DbDatum	get_default_class_property(string &);
	
	protected:
		TestTimingDistributionUnitClass(string &);
		static TestTimingDistributionUnitClass *_instance;
		void command_factory();
		void attribute_factory(vector<Tango::Attr *> &);
		void pipe_factory();
		void write_class_property();
		void set_default_property();
		void get_class_property();
		string get_cvstag();
		string get_cvsroot();
	
	private:
		void device_factory(const Tango::DevVarStringArray *);
		void create_static_attribute_list(vector<Tango::Attr *> &);
		void erase_dynamic_attributes(const Tango::DevVarStringArray *,vector<Tango::Attr *> &);
		vector<string>	defaultAttList;
		Tango::Attr *get_attr_object_by_name(vector<Tango::Attr *> &att_list, string attname);
};

}	//	End of namespace

#endif   //	TestTimingDistributionUnit_H
