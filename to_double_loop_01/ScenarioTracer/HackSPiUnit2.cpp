#include "HackSPiUnit2.h"

HackSPiUnit2::HackSPiUnit2(ScenarioTracerWithStarter* scenariotracerwithstarter, ScenarioTracer* scenariotracer)
    : mScenarioTracerWithStarter(scenariotracerwithstarter), mScenarioTracer(scenariotracer)
{
    ;
}

HackSPiUnit2::eState HackSPiUnit2::getState()
{
    return state;
}

void HackSPiUnit2::capture()
{
    switch (state)
    {
        case INITIAL:
            exeInitial();
            break;
        case TO_LAP_GATE:
            toLAPGaterun();
            break;
        case DOUBLE_LOOP_NEO:
            doubleLoopNEOrun();
            break;
        default:
            break;
    }
}

void HackSPiUnit2::exeInitial()
{
    state = TO_LAP_GATE;
}

void HackSPiUnit2::toLAPGaterun()
{
    mScenarioTracerWithStarter->capture();

    if (mScenarioTracerWithStarter->getState() == ScenarioTracerWithStarter::STOP)
    {
        state = DOUBLE_LOOP_NEO;
    }
}

void HackSPiUnit2::doubleLoopNEOrun()
{
    mScenarioTracer->capture();

    if (mScenarioTracer->getState() == ScenarioTracer::STOP)
    {
        state = STOP;
    }
}
