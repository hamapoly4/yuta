#include "ScenarioTracer.h"

ScenarioTracer::ScenarioTracer(Scenario* scenario, const ev3api::SonarSensor& sonarsensor)
    : mState(WAITING), mScenario(scenario), mSonarSensor(sonarsensor)
{
    ;
}

ScenarioTracer::eState ScenarioTracer::getState()
{
    return mState;
}

void ScenarioTracer::run()
{
    switch (mState)
    {
        case WAITING:
            exeWaiting();
            break;
        case RUN:
            exeRun();
            break;
        default:
            break;
    }
}

void ScenarioTracer::exeWaiting()
{
    mdist = mSonarSensor.getDistance();
    if (-1 < mdist && mdist < 5)
    {
        mState = RUN;
    }
}

void ScenarioTracer::exeRun()
{
    mScenario->run();
    if (mScenario->finish() == true)
    {
        mState = FIN;
    }
}

