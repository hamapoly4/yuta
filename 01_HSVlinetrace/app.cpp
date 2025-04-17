#include "app.h" // <1>
#include "Tracer.h" // <2>
#include "HSVconv.h"
#include "Motor.h"
#include "RunDistDetect.h"

#include <stdio.h>

using namespace spikeapi;

ColorSensor gcolorSensor(PORT_2);
HSVconv gHSVconv(gcolorSensor);

Motor gLeftMotor(PORT_C);
Motor gRightMotor(PORT_B);
RunDistDetect gRunDistDetect(gLeftMotor, gRightMotor);

Tracer tracer(gLeftMotor, gRightMotor, gRunDistDetect, gHSVconv);  // <4>

void tracer_task(intptr_t exinf) { // <1>
  static bool flag = false;
  if (ev3_button_is_pressed(ENTER_BUTTON) || flag == true)
  {
    wup_tsk(MAIN_TASK);
  }
  
  flag = tracer.run();
  ext_tsk();
}

void main_task(intptr_t unused) { // <1>

  sta_cyc(TRACER_CYC); // <4>
  
  slp_tsk();

  stp_cyc(TRACER_CYC); // <3>
  tracer.terminate(); // <4>
  ext_tsk(); // <5>
}
