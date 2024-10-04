#ifndef ___CLASS_SCENARIO_TRACER_WITH_STARTER
#define ___CLASS_SCENARIO_TRACER_WITH_STARTER

#include "ScenarioTracer.h"
#include "SonarSensor.h"

class ScenarioTracerWithStarter {
public:
    enum eState { INITIAL, WAITING, RUN, STOP };

    ScenarioTracerWithStarter(ScenarioTracer* scenariotracer, const ev3api::SonarSensor& sonarsensor);
    eState getState();
    void capture();
    void exeInitial();
    void wait();
    void run();

private:
    eState state;

    ScenarioTracer* mScenarioTracer;
    const ev3api::SonarSensor& mSonarSensor;

    int dist;
};

#endif // ___CLASS_SCENARIO_TRACER_WITH_STARTER
