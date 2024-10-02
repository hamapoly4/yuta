#ifndef ___CLASS_HACK_SPI_UNIT2
#define ___CLASS_HACK_SPI_UNIT2

#include "ScenarioTracerWithStarter.h"
#include "ScenarioTracer.h"

class HackSPiUnit2 {
public:
    enum eState { INITIAL, TO_LAP_GATE, DOUBLE_LOOP_NEO, STOP, };

    HackSPiUnit2(ScenarioTracerWithStarter* scenariotracerwithstarter, ScenarioTracer* scenariotracer);
    eState getState();
    void capture();
    void exeInitial();
    void toLAPGaterun();
    void doubleLoopNEOrun();

private:
    eState state;

    ScenarioTracerWithStarter* mScenarioTracerWithStarter;
    ScenarioTracer* mScenarioTracer;

};

#endif // ___CLASS_HACK_SPI_UNIT2
