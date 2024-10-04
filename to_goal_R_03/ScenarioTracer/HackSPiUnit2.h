#ifndef ___CLASS_HACK_SPI_UNIT2
#define ___CLASS_HACK_SPI_UNIT2

#include "ScenarioTracerWithStarter.h"
#include "ScenarioTracer.h"

class HackSPiUnit2 {
public:
    enum eState { INITIAL, TO_LAP_GATE, DOUBLE_LOOP_NEO, TO_GOAL, STOP, };

    static const unsigned char SIZE = 2;

    HackSPiUnit2(ScenarioTracerWithStarter* scenariotracerwithstarter, ScenarioTracer* scenariotracer[]);
    eState getState();
    void capture();
    void exeInitial();
    void toLAPGaterun();
    void doubleLoopNEOrun();
    void toGoalrun();

private:
    eState state;

    ScenarioTracerWithStarter* mScenarioTracerWithStarter;
    ScenarioTracer* mScenarioTracer[SIZE];

};

#endif // ___CLASS_HACK_SPI_UNIT2
