/*----- PROTECTED REGION ID(Newport8742Axis::ClassFactory.cpp) ENABLED START -----*/
static const char *RcsId = "$Id:  $";
//=============================================================================
//
// file :        ClassFactory.cpp
//
// description : C++ source for the class_factory method of the DServer
//               device class. This method is responsible for the creation of
//               all class singleton for a device server. It is called
//               at device server startup.
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


#include <tango.h>
#include <NewPort8742CtrlClass.h>
#include <Newport8742AxisClass.h>

//	Add class header files if needed


/**
 *	Create Newport8742Axis Class singleton and store it in DServer object.
 */

void Tango::DServer::class_factory()
{
	//	Add method class init if needed
	add_class(	NewPort8742Ctrl_ns::NewPort8742CtrlClass::init("NewPort8742Ctrl"));
	add_class(Newport8742Axis_ns::Newport8742AxisClass::init("Newport8742Axis"));
}

/*----- PROTECTED REGION END -----*/	//	Newport8742Axis::ClassFactory.cpp
