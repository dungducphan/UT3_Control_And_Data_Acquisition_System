/*----- PROTECTED REGION ID(TimingUnitClass.h) ENABLED START -----*/
//=============================================================================
//
// file :        TimingUnitClass.h
//
// description : Include for the TimingUnit root class.
//               This class is the singleton class for
//                the TimingUnit device class.
//               It contains all properties and methods which the 
//               TimingUnit requires only once e.g. the commands.
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


#ifndef TimingUnitClass_H
#define TimingUnitClass_H

#include <tango.h>
#include <TimingUnit.h>


/*----- PROTECTED REGION END -----*/	//	TimingUnitClass.h


namespace TimingUnit_ns
{
/*----- PROTECTED REGION ID(TimingUnitClass::classes for dynamic creation) ENABLED START -----*/


/*----- PROTECTED REGION END -----*/	//	TimingUnitClass::classes for dynamic creation

//=========================================
//	Define classes for attributes
//=========================================
//	Attribute DelayPortB class definition
class DelayPortBAttrib: public Tango::Attr
{
public:
	DelayPortBAttrib():Attr("DelayPortB",
			Tango::DEV_USHORT, Tango::READ_WRITE) {};
	~DelayPortBAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<TimingUnit *>(dev))->read_DelayPortB(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<TimingUnit *>(dev))->write_DelayPortB(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<TimingUnit *>(dev))->is_DelayPortB_allowed(ty);}
};

//	Attribute DelayPortD class definition
class DelayPortDAttrib: public Tango::Attr
{
public:
	DelayPortDAttrib():Attr("DelayPortD",
			Tango::DEV_USHORT, Tango::READ_WRITE) {};
	~DelayPortDAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<TimingUnit *>(dev))->read_DelayPortD(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<TimingUnit *>(dev))->write_DelayPortD(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<TimingUnit *>(dev))->is_DelayPortD_allowed(ty);}
};


//=========================================
//	Define classes for commands
//=========================================
//	Command Start class definition
class StartClass : public Tango::Command
{
public:
	StartClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out,
				   const char        *in_desc,
				   const char        *out_desc,
				   Tango::DispLevel  level)
	:Command(name,in,out,in_desc,out_desc, level)	{};

	StartClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out)
	:Command(name,in,out)	{};
	~StartClass() {};
	
	virtual CORBA::Any *execute (Tango::DeviceImpl *dev, const CORBA::Any &any);
	virtual bool is_allowed (Tango::DeviceImpl *dev, const CORBA::Any &any)
	{return (static_cast<TimingUnit *>(dev))->is_Start_allowed(any);}
};

//	Command Stop class definition
class StopClass : public Tango::Command
{
public:
	StopClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out,
				   const char        *in_desc,
				   const char        *out_desc,
				   Tango::DispLevel  level)
	:Command(name,in,out,in_desc,out_desc, level)	{};

	StopClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out)
	:Command(name,in,out)	{};
	~StopClass() {};
	
	virtual CORBA::Any *execute (Tango::DeviceImpl *dev, const CORBA::Any &any);
	virtual bool is_allowed (Tango::DeviceImpl *dev, const CORBA::Any &any)
	{return (static_cast<TimingUnit *>(dev))->is_Stop_allowed(any);}
};


/**
 *	The TimingUnitClass singleton definition
 */

#ifdef _TG_WINDOWS_
class __declspec(dllexport)  TimingUnitClass : public Tango::DeviceClass
#else
class TimingUnitClass : public Tango::DeviceClass
#endif
{
	/*----- PROTECTED REGION ID(TimingUnitClass::Additionnal DServer data members) ENABLED START -----*/
	
	
	/*----- PROTECTED REGION END -----*/	//	TimingUnitClass::Additionnal DServer data members

	public:
		//	write class properties data members
		Tango::DbData	cl_prop;
		Tango::DbData	cl_def_prop;
		Tango::DbData	dev_def_prop;
	
		//	Method prototypes
		static TimingUnitClass *init(const char *);
		static TimingUnitClass *instance();
		~TimingUnitClass();
		Tango::DbDatum	get_class_property(string &);
		Tango::DbDatum	get_default_device_property(string &);
		Tango::DbDatum	get_default_class_property(string &);
	
	protected:
		TimingUnitClass(string &);
		static TimingUnitClass *_instance;
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

#endif   //	TimingUnit_H
