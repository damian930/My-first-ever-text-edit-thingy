#ifndef NOTEPAD_H
#define NOTEPAD_H

#include "core/core_include.h"
#include "os/win32.h"
#include "render/render.h"
#include "draw/draw.h"
#include "font_provider/font_provider.h"

enum UI_Text_op_kind : U32 {  
  UI_Text_op_kind__NONE,
  UI_Text_op_kind__move_cursor,
  UI_Text_op_kind__delete_section,
  UI_Text_op_kind__copy_section,
  UI_Text_op_kind__paste_at_cursor,
  UI_Text_op_kind__insert_char_at_cursor, 
  UI_Text_op_kind__stop_editing, 
};

enum UI_Text_op_move_specifier : U32 {
  UI_Text_op_move_specifier___NONE,
  UI_Text_op_move_specifier___move_1_char_left,                     
  UI_Text_op_move_specifier___move_1_char_right,   
  UI_Text_op_move_specifier___move_1_word_left,  // todo: This shoud be called something that specifies that ctrl was down when the arrow got pushed down                     
  UI_Text_op_move_specifier___move_1_word_right, // todo: This shoud be called something that specifies that ctrl was down when the arrow got pushed down                    
  UI_Text_op_move_specifier___move_to_line_start,                   
  UI_Text_op_move_specifier___move_to_line_end,          
  UI_Text_op_move_specifier___move_specific_position,                     
  UI_Text_op_move_specifier___move_1_line_up,
  UI_Text_op_move_specifier___move_1_line_down,
  UI_Text_op_move_specifier___move_to_first_line,
  UI_Text_op_move_specifier___move_to_last_line,
};

struct UI_Text_op {
  UI_Text_op_kind kind;
  
  UI_Text_op* next;
  UI_Text_op* prev;

  OS_Event* opt_os_event;

  // Fat struct data
  U8 char_to_insert;               
  B32 keep_section_start_after_op; 
  B32 dont_move_if_section;  // This just canceles the move but does all the general things that are done for all ops (eg: section = cursor in the end)
  B32 discard_op_if_section; // This doesnt proced with the op if section is present
  B32 override_move_and_move_to_section_min_if_ending_section;
  B32 override_move_and_move_to_section_max_if_ending_section;/////////////////////////////////////////////////////////////////////
  V2U64 cursor_specific_pos;
  UI_Text_op_move_specifier move_specifier;
};

struct UI_Text_op_list {
  UI_Text_op* first;
  UI_Text_op* last;
  U64 count;
};

struct Text_coord {
  U64 x;
  U64 y; 
};

struct App_state {
  U8         buffer[1024];
  U64        buffer_count;
  Text_coord cursor_coord;
  Text_coord section_coord;
  
  FP_Font    font;
};




#endif