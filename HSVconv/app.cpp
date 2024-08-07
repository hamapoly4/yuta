#include "app.h" // <1>
#include "Tracer.h" // <2>
#include "HSVconv.h"
#include "Clock.h"  // <3>

#include <stdio.h>

using namespace ev3api;

ColorSensor gcolorSensor(PORT_2);
HSVconv gHSVconv(gcolorSensor);
Tracer tracer(gHSVconv);  // <4>
Clock clock;    // <5>

void tracer_task(intptr_t exinf) { // <1
  tracer.run();
  ext_tsk();
}

void main_task(intptr_t unused) { // <1>
  const uint32_t duration = 100*1000; // <2>

  sta_cyc(TRACER_CYC); // <4>
  
  while (!ev3_button_is_pressed(LEFT_BUTTON)) { // <1>
      clock.sleep(duration);   // <2>
  }

  stp_cyc(TRACER_CYC); // <3>
  tracer.terminate(); // <4>
  ext_tsk(); // <5>
}
