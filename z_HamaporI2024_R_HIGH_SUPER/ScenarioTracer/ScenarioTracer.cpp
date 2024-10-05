#include "ScenarioTracer.h"

ScenarioTracer::ScenarioTracer(DeviceManage* devicemanage, Scenario* scenario,
                                    CountMonitor* countmonitor, AngleMonitor* anglemonitor, HSVMonitor* hsvmonitor)
    : mDeviceManage(devicemanage), mScenario(scenario),
        mCountMonitor(countmonitor), mAngleMonitor(anglemonitor), mHSVMonitor(hsvmonitor), state(INITIAL)
{
    ;
}

ScenarioTracer::eState ScenarioTracer::getState()
{
    return state;
}

void ScenarioTracer::capture()
{
    switch (state)
    {
        case INITIAL:
            exeInitial();
            break;
        case RESET:
            reset();
            break;
        case RUN:
            run();
            break;
        default:
            break;
    }
}

void ScenarioTracer::exeInitial()
{
    state = RESET;
}

void ScenarioTracer::reset()
{
    mDeviceManage->reset();

    if (mDeviceManage->getState() == DeviceManage::INITIAL)
    {
        state = RUN;
    }
}

void ScenarioTracer::run()
{
    /* デバイスの値を取得する */
    mCountMonitor->Measure();
    mAngleMonitor->Measure();
    mHSVMonitor->convHSV();

    mScenario->execute();

    switch (mScenario->getState())
    {
        case Scenario::SWITCH_SCENE:
            state = RESET;
            break;
        case Scenario::FINISH:
            state = STOP;
            break;
        default:
            break;
    }
}
