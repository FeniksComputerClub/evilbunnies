#include "sys.h"
#include "Bunny.h"
#include "MyArea.h"
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
  return true;
}

char const* Bunny::state_str_impl(state_type run_state) const
{
  switch(run_state)
  {
    AI_CASE_RETURN(start);
    AI_CASE_RETURN(move_right);
    AI_CASE_RETURN(move_left);
    AI_CASE_RETURN(done);
  }
  return "UNKNOWN";
}

void Bunny::multiplex_impl(state_type run_state)
{
  switch(run_state)
  {
    double previousx;
    case start:
      m_x += (rand() % 100 + 1) / 100.0;
      set_state(move_right);
    case move_right:
      m_x += 0.001;
      previousx = m_x;
      clamp(m_x, m_y);
      m_area.queue_draw();
      if (m_x != previousx)
        set_state(move_left);
      yield();
      break;
    case move_left:
      m_x -= 0.001;
      previousx = m_x;
      clamp(m_x, m_y);
      m_area.queue_draw();
      if (m_x != previousx)
        set_state(move_right);
      yield();
      break;
    case done:
      finish();
      break;
  }
}
