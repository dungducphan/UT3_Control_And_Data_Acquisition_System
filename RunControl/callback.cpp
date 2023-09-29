#include <callback.h>

TriggerCallback::TriggerCallback(QObject *parent) : QObject{parent}, Timestamp(0) {
}

void TriggerCallback::push_event(Tango::EventData *data) {
    Tango::DevVarULong64Array *double_value;
    *(data->attr_value) >> double_value;
    Timestamp = (*double_value)[0];
    emit TriggerReceived();
}

WFSCallback::WFSCallback(QObject *parent) : QObject{parent} {
}

void WFSCallback::push_event(Tango::EventData *data) {
    emit WFSReceived();
}