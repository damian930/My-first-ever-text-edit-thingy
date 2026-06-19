void OutputDebugStringF(const char* fmt, ...);

#include "core/core_include.h"
#include "core/core_include.cpp"

#include "os/win32.h"
#include "os/win32.cpp"

#include "render/render.h"
#include "render/render.cpp"

#include "draw/draw.h"
#include "draw/draw.cpp"

#include "font_provider/font_provider.h"
#include "font_provider/font_provider.cpp"

#include "notepad.h"
#include "notepad.cpp"

// OS_Handle os_load_dll(Str8 path_to_dll)
// {  
  
// }

int WinMain(HINSTANCE app_instance, HINSTANCE __not_used__, LPSTR cmd, int show)
{
  // Layers we allocate for the runtime 
  allocate_thread_context();
  os_init();
  r_init(); 
  d_init();
  fp_init();

  // TODO: Clear up the window from the os state, the os state should be the shared part and should not have this in there fsdfsdfsdfsdfsdfsdf
  //       The win proc from the os file should then also be removed since it is not general but os specific
  OS_State* win32_state = os_get_state();

  ///////////////////////////////////////////////////////////
  // - Window  
  //
  {
    win32_state->window.window_class.cbSize        = sizeof(WNDCLASSEXA);
    win32_state->window.window_class.style         = CS_HREDRAW|CS_VREDRAW/*| CS_DBLCLKS*/; // todo: Look into hredraw and vredraw
    win32_state->window.window_class.lpfnWndProc   = win32_proc;
    win32_state->window.window_class.hInstance     = app_instance;
    win32_state->window.window_class.hIcon         = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(1));
    win32_state->window.window_class.hCursor       = LoadCursorA(0, IDC_ARROW);
    win32_state->window.window_class.hbrBackground = Null;
    win32_state->window.window_class.lpszMenuName  = Null;
    win32_state->window.window_class.lpszClassName = "pencil_app_flopper_class_name";
    win32_state->window.window_class.hIconSm       = Null;

    ATOM wc_atom = RegisterClassExA(&win32_state->window.window_class);
    Assert(wc_atom != 0);
    
    win32_state->window.is_transparent = false;
    win32_state->window.handle = CreateWindowExA(
      WS_EX_NOREDIRECTIONBITMAP,
      win32_state->window.window_class.lpszClassName,
      "Pencil",
      WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT,
      800, 600,
      Null,
      Null,
      app_instance, 
      Null
    );
    Handle(win32_state->window.handle != 0);
    ShowWindow(win32_state->window.handle, SW_NORMAL);
  }

  ///////////////////////////////////////////////////////////
  // - App loop
  //
  R_Target window_frame_buffer_target = r_attach_window(win32_state->window);

  App_state S = {};
  app_init(&S);

  F64 frame_start_time_in_sec = 0.0;
  for (;!os_window_should_close();)
  {
    F64 prev_frame_start_time_in_sec = frame_start_time_in_sec;
    frame_start_time_in_sec          = os_get_time_for_timing_sec();

    os_frame_begin();
    r_prepare_canvas(&window_frame_buffer_target);
    d_begin_batching(window_frame_buffer_target);

    { // Frame update
      app_update(&S);
    }

    { // Rendering
      r_clear_target(window_frame_buffer_target, black());

      app_render(&S);

      U64 fps = (U64)(1.0 / (frame_start_time_in_sec - prev_frame_start_time_in_sec));
      OutputDebugStringF("FPS: %lld \n", fps);
    }

    r_submit(window_frame_buffer_target, d_get_batch_list());

    d_end_batching();
    os_frame_end();

    r_present(window_frame_buffer_target, false);
  }

  // Not releasing anything since who cares, the system will release all the stuff

  return 0;
}

///////////////////////////////////////////////////////////
// - Main helpers
//
// todo: Code for this is bad
void OutputDebugStringF(const char* fmt, ...)
{
  #if DEBUG_MODE
  va_list argptr;
  va_start(argptr, fmt);
  Scratch scratch = get_scratch(0, 0);
  Data_buffer buffer = data_buffer_make(scratch.arena, 128);
  int ret = vsprintf_s((char*)buffer.data, buffer.count, fmt, argptr);
  if (ret >= 0 && ret < buffer.count)
  {
    OutputDebugStringA((char*)buffer.data);
  } else { InvalidCodePath(); }
  end_scratch(&scratch);
  va_end(argptr);
  #endif
}
              