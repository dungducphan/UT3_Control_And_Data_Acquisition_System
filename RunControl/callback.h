#pragma once

#include <QObject>

#include <tango.h>

class TriggerCallback : public QObject, public Tango::CallBack {
    Q_OBJECT
public:
    explicit TriggerCallback(QObject *parent = nullptr);
    void push_event(Tango::EventData* data) override;

public:
    Tango::DevULong64 Timestamp;

signals:
    void TriggerReceived();
};

class WFSCallback : public QObject, public Tango::CallBack {
Q_OBJECT
public:
    explicit WFSCallback(QObject *parent = nullptr);
    void push_event(Tango::EventData* data) override;

signals:
    void WFSReceived();
};


