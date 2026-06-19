#include "notepad.h"

#include "core/core_include.cpp"
#include "os/win32.cpp"
#include "render/render.cpp"
#include "font_provider/font_provider.cpp"
#include "draw/draw.cpp"

extern "C" __declspec( dllexport ) 
void app_draw_cursor_section(Notepad_dll_boundary_data_pass* dll_data_pass)
{
  set_thread_context(dll_data_pass->dll_caller_thread_context);
  os_set_state(dll_data_pass->dll_caller_os_state) ;
  r_set_state(dll_data_pass->dll_caller_render_state);
  d_set_state(dll_data_pass->dll_caller_draw_state);
  fp_set_state(dll_data_pass->dll_caller_font_provider_state);

  App_state* S = dll_data_pass->notepad_state;  

  d_draw_text(Str8FromC("SOME TEXT"), S->font, v2f32(50, 50), magenta());
}