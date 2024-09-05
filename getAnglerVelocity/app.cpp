#include "app.h" // <1>
#include "Tracer.h" // <2>
using namespace ev3api;

Tracer tracer;  // <4>

void main_task(intptr_t unused) { // <1>

  sta_cyc(TRACER_CYC); // <4>

  slp_tsk();

  stp_cyc(TRACER_CYC); // <3>

  ext_tsk(); // <5>
}

void tracer_task(intptr_t exinf) { // <1>
  if (ev3_button_is_pressed(ENTER_BUTTON))
  {
    wup_tsk(MAIN_TASK);
  }
  else
  {
    tracer.run(); // <2>
  }

  ext_tsk();
}

