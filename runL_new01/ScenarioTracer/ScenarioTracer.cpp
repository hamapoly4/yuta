#include "ScenarioTracer.h"
#include <stdio.h>

ScenarioTracer::ScenarioTracer(DeviceManage* devicemanage, Scenario* scenario,
                                    CountMonitor* countmonitor, HSVMonitor* hsvmonitor)
    : mDeviceManage(devicemanage), mScenario(scenario),
        mCountMonitor(countmonitor), mHSVMonitor(hsvmonitor), state(INITIAL)
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
        printf("can reset!!\n");
    }
}

void ScenarioTracer::run()
{
    /* デバイスの値を取得する */
    mCountMonitor->Measure();
    mHSVMonitor->convHSV();

    mScenario->execute();

    switch (mScenario->getState())
    {
        case Scenario::SWITCH_SCENE:
            printf("swith_scene so reset!!\n");
            state = RESET;
            break;
        case Scenario::FINISH:
            state = STOP;
            break;
        default:
            break;
    }
}
