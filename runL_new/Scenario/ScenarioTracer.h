#include "Scenario.h"
#include "SonarSensor.h"

class ScenarioTracer {
public:
    enum eState { WAITING, RUN, FIN };

private:
    eState mState;

    Scenario* mScenario;
    const ev3api::SonarSensor& mSonarSensor;

    int mdist;

public:
    ScenarioTracer(Scenario* scenario, const ev3api::SonarSensor& sonarsensor);
    eState getState();
    void run();
    void exeWaiting();
    void exeRun();
};