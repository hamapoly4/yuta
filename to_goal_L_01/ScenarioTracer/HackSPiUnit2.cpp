#include "HackSPiUnit2.h"

HackSPiUnit2::HackSPiUnit2(ScenarioTracerWithStarter* scenariotracerwithstarter, ScenarioTracer* scenariotracer[])
    : mScenarioTracerWithStarter(scenariotracerwithstarter)
{
    unsigned char i;
    for (i = 0; i < SIZE; i++)
    {
        mScenarioTracer[i] = scenariotracer[i];
    }
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
        case TO_GOAL:
            toGoalrun();
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
    mScenarioTracer[0]->capture();

    if (mScenarioTracer[0]->getState() == ScenarioTracer::STOP)
    {
        state = TO_GOAL;
    }
}

void HackSPiUnit2::toGoalrun()
{
    mScenarioTracer[1]->capture();

    if (mScenarioTracer[1]->getState() == ScenarioTracer::STOP)
    {
        state = STOP;
    }
}
