#define _CRT_SECURE_NO_WARNINGS

#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "__third_party/stb/stb_image_write.h"
#endif

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

#include "render/render.h"
#include "render/render.cpp"

#include "ui/ui_core.h"
#include "ui/ui_core.cpp"

#include "ui/widgets/ui_widgets.h"
#include "ui/widgets/ui_widgets.cpp"

int main()
{
  allocate_thread_context();
  os_init();
  r_init(); 
  d_init();
  fp_init();

  Arena* arena = arena_alloc(Kilobytes(64), 0, 0);
  // todo: When splitter is longer than the string error
  // todo: When the splitte is "" we get error
  Str8 str = Str8FromC("");

  Str8* tokens    = {};
  U64 token_count =  {};
  str8_split_into_array(arena, str, Str8FromC(""), 0, true, &tokens, &token_count);

  for EachIndex(i, token_count)
  {
    Str8 nt = str8_copy_alloc(arena, tokens[i]);
    printf("%s \n", nt.count == 0 ? "NONE" : (char*)nt.data);
  }

  return 0;
}