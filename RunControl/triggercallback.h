#pragma once

#include <QObject>

#include <tango.h>

class TriggerCallback : public QObject, public Tango::CallBack {
    Q_OBJECT
public:
    explicit TriggerCallback(QObject *parent = nullptr);
    Tango::DevULong64 Timestamp;

    void push_event(Tango::EventData* data) override {
        Tango::DevVarULong64Array *double_value;
        *(data->attr_value) >> double_value;
        Timestamp = (*double_value)[0];
    }

signals:
};

