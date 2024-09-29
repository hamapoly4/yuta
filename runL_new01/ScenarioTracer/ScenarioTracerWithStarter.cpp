#include "ScenarioTracerWithStarter.h"

ScenarioTracerWithStarter::ScenarioTracerWithStarter(ScenarioTracer* scenariotracer, const ev3api::SonarSensor& sonarsensor)
    : state(WAITING), mScenarioTracer(scenariotracer), mSonarSensor(sonarsensor)
{
    ;
}

ScenarioTracer::eState ScenarioTracerWithStarter::getState()
{
    return state;
}

void ScenarioTracerWithStarter::capture()
{
    switch (state)
    {
        case INITIAL:
            exeInitial();
            break;
        case WAITING:
            wait();
            break;
        case RUN:
            run();
            break;
        default:
            break;
    }
}

void ScenarioTracerWithStarter::exeInitial()
{
    state = RUN;
}

void ScenarioTracerWithStarter::wait()
{
    dist = mSonarSensor.getDistance();
    if (-1 < dist && dist < 5)
    {
        state = RUN;
    }
}

void ScenarioTracerWithStarter::run()
{
    mScenarioTracer->capture();
    if (mScenarioTracer->getState() == ScenarioTracer::STOP)
    {
        state = STOP;
    }
}
