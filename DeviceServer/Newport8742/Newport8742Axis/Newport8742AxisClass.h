/*----- PROTECTED REGION ID(Newport8742AxisClass.h) ENABLED START -----*/
//=============================================================================
//
// file :        Newport8742AxisClass.h
//
// description : Include for the Newport8742AxisClass root class.
//               This class is the singleton class for.
//               the Newport8742Axis device class..
//               It contains all properties and methods which the .
//               Newport8742Axis requires only once e.g. the commands.
//
// project :     .
//
// $Author:  $
//
// $Revision:  $
// $Date:  $
//
// SVN only:
// $HeadURL:  $
//
// CVS only:
// $Source:  $
// $Log:  $
//
//=============================================================================
//                This file is generated by POGO
//        (Program Obviously used to Generate tango Object)
//=============================================================================


#ifndef NEWPORT8742AXISCLASS_H
#define NEWPORT8742AXISCLASS_H

#include <tango.h>
#include <Newport8742Axis.h>

/*----- PROTECTED REGION END -----*/	//	Newport8742AxisClass.h


namespace Newport8742Axis_ns
{
/*----- PROTECTED REGION ID(Newport8742AxisClass::classes for dynamic creation) ENABLED START -----*/

	/*----- PROTECTED REGION END -----*/	//	Newport8742AxisClass::classes for dynamic creation

//=========================================
//	Define classes for attributes
//=========================================
//	Attribute Conversion class definition
class ConversionAttrib: public Tango::Attr
{
public:
	ConversionAttrib():Attr("Conversion",
			Tango::DEV_DOUBLE, Tango::READ_WRITE) {};
	~ConversionAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<Newport8742Axis *>(dev))->read_Conversion(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<Newport8742Axis *>(dev))->write_Conversion(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<Newport8742Axis *>(dev))->is_Conversion_allowed(ty);}
};

//	Attribute Position class definition
class PositionAttrib: public Tango::Attr
{
public:
	PositionAttrib():Attr("Position",
			Tango::DEV_DOUBLE, Tango::READ_WRITE) {};
	~PositionAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<Newport8742Axis *>(dev))->read_Position(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<Newport8742Axis *>(dev))->write_Position(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<Newport8742Axis *>(dev))->is_Position_allowed(ty);}
};

//	Attribute UnitLimitMin class definition
class UnitLimitMinAttrib: public Tango::Attr
{
public:
	UnitLimitMinAttrib():Attr("UnitLimitMin",
			Tango::DEV_DOUBLE, Tango::READ_WRITE) {};
	~UnitLimitMinAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<Newport8742Axis *>(dev))->read_UnitLimitMin(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<Newport8742Axis *>(dev))->write_UnitLimitMin(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<Newport8742Axis *>(dev))->is_UnitLimitMin_allowed(ty);}
};

//	Attribute UnitLimitMax class definition
class UnitLimitMaxAttrib: public Tango::Attr
{
public:
	UnitLimitMaxAttrib():Attr("UnitLimitMax",
			Tango::DEV_DOUBLE, Tango::READ_WRITE) {};
	~UnitLimitMaxAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<Newport8742Axis *>(dev))->read_UnitLimitMax(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<Newport8742Axis *>(dev))->write_UnitLimitMax(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<Newport8742Axis *>(dev))->is_UnitLimitMax_allowed(ty);}
};

//	Attribute MotorType class definition
class MotorTypeAttrib: public Tango::Attr
{
public:
	MotorTypeAttrib():Attr("MotorType",
			Tango::DEV_SHORT, Tango::READ) {};
	~MotorTypeAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<Newport8742Axis *>(dev))->read_MotorType(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<Newport8742Axis *>(dev))->is_MotorType_allowed(ty);}
};

//	Attribute Speed class definition
class SpeedAttrib: public Tango::Attr
{
public:
	SpeedAttrib():Attr("Speed",
			Tango::DEV_LONG, Tango::READ_WRITE) {};
	~SpeedAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<Newport8742Axis *>(dev))->read_Speed(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<Newport8742Axis *>(dev))->write_Speed(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<Newport8742Axis *>(dev))->is_Speed_allowed(ty);}
};

//	Attribute Acceleration class definition
class AccelerationAttrib: public Tango::Attr
{
public:
	AccelerationAttrib():Attr("Acceleration",
			Tango::DEV_LONG, Tango::READ_WRITE) {};
	~AccelerationAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<Newport8742Axis *>(dev))->read_Acceleration(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<Newport8742Axis *>(dev))->write_Acceleration(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<Newport8742Axis *>(dev))->is_Acceleration_allowed(ty);}
};

//	Attribute StoredPosition class definition
class StoredPositionAttrib: public Tango::Attr
{
public:
	StoredPositionAttrib():Attr("StoredPosition",
			Tango::DEV_LONG, Tango::READ_WRITE) {};
	~StoredPositionAttrib() {};
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<Newport8742Axis *>(dev))->read_StoredPosition(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<Newport8742Axis *>(dev))->write_StoredPosition(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<Newport8742Axis *>(dev))->is_StoredPosition_allowed(ty);}
};


//=========================================
//	Define classes for commands
//=========================================
//	Command StopMove class definition
class StopMoveClass : public Tango::Command
{
public:
	StopMoveClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out,
				   const char        *in_desc,
				   const char        *out_desc,
				   Tango::DispLevel  level)
	:Command(name,in,out,in_desc,out_desc, level)	{};

	StopMoveClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out)
	:Command(name,in,out)	{};
	~StopMoveClass() {};
	
	virtual CORBA::Any *execute (Tango::DeviceImpl *dev, const CORBA::Any &any);
	virtual bool is_allowed (Tango::DeviceImpl *dev, const CORBA::Any &any)
	{return (static_cast<Newport8742Axis *>(dev))->is_StopMove_allowed(any);}
};

//	Command Calibrate class definition
class CalibrateClass : public Tango::Command
{
public:
	CalibrateClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out,
				   const char        *in_desc,
				   const char        *out_desc,
				   Tango::DispLevel  level)
	:Command(name,in,out,in_desc,out_desc, level)	{};

	CalibrateClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out)
	:Command(name,in,out)	{};
	~CalibrateClass() {};
	
	virtual CORBA::Any *execute (Tango::DeviceImpl *dev, const CORBA::Any &any);
	virtual bool is_allowed (Tango::DeviceImpl *dev, const CORBA::Any &any)
	{return (static_cast<Newport8742Axis *>(dev))->is_Calibrate_allowed(any);}
};


/**
 *	The Newport8742AxisClass singleton definition
 */

#ifdef _TG_WINDOWS_
class __declspec(dllexport)  Newport8742AxisClass : public Tango::DeviceClass
#else
class Newport8742AxisClass : public Tango::DeviceClass
#endif
{
	/*----- PROTECTED REGION ID(Newport8742AxisClass::Additionnal DServer data members) ENABLED START -----*/

	/*----- PROTECTED REGION END -----*/	//	Newport8742AxisClass::Additionnal DServer data members

	public:
		//	write class properties data members
		Tango::DbData	cl_prop;
		Tango::DbData	cl_def_prop;
		Tango::DbData	dev_def_prop;
	
		//	Method prototypes
		static Newport8742AxisClass *init(const char *);
		static Newport8742AxisClass *instance();
		~Newport8742AxisClass();
		Tango::DbDatum	get_class_property(string &);
		Tango::DbDatum	get_default_device_property(string &);
		Tango::DbDatum	get_default_class_property(string &);
	
	protected:
		Newport8742AxisClass(string &);
		static Newport8742AxisClass *_instance;
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

#endif   //	Newport8742Axis_H