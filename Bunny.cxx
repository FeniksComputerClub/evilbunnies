#include "sys.h"
#include "Bunny.h"
#include <thread>
#include <chrono>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

bool Bunny::on_draw(Cairo::RefPtr<Cairo::Context> const& cr, time_point const& /*time*/)
{
  cr->set_source(m_pattern);
  cr->arc(m_x, m_y, m_radius, 0.0, 2 * M_PI);
  cr->fill_preserve();
  
  //move bunny
  m_x += 0.01;
  clamp(m_x, m_y);
  return true;
}

char const* Bunny::state_str_impl(state_type run_state) const
{
  switch(run_state)
  {
    AI_CASE_RETURN(Task_start);
    AI_CASE_RETURN(Task_done);
  }
  return "UNKNOWN";
}

void Bunny::multiplex_impl(state_type run_state)
{
  switch(run_state)
  {
    case Task_start:
      if (!m_do_finish)
      {
        wait(1);
        break;
      }
      set_state(Task_done);
      /*fall-through*/
    case Task_done:
      finish();
      break;
  }
}
