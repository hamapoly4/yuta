#ifndef ___CLASS_SCENARIOTRACER
#define ___CLASS_SCENARIOTRACER

#include "DeviceManage.h"
#include "Scenario.h"

#include "CountMonitor.h"
#include "AngleMonitor.h"
#include "HSVMonitor.h"

class ScenarioTracer {
public:
    enum eState { INITIAL, RESET, RUN, STOP, };

    ScenarioTracer(DeviceManage* devicemanage, Scenario* scenario,
                        CountMonitor* countmonitor, AngleMonitor* anglemonitor, HSVMonitor* hsvmonitor);
    eState getState();
    void capture();
    void exeInitial();
    void reset();
    void run();

private:
    DeviceManage* mDeviceManage;
    Scenario* mScenario;

    CountMonitor* mCountMonitor;
    AngleMonitor* mAngleMonitor;
    HSVMonitor* mHSVMonitor;

    eState state;
};

#endif // ___CLASS_SCENARIOTRACER
