#ifndef NOTEPAD_CPP
#define NOTEPAD_CPP

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
 
///////////////////////////////////////////////////////////
// - General text op things
//

B32 text_coord_eq(Text_coord coord, Text_coord other)
{
  return (coord.x == other.x && coord.y == other.y);
}

Text_coord text_coord_smaller(Text_coord coord, Text_coord other)
{
  Text_coord smaller = coord;
  if (0) {}
  else if (other.y < smaller.y)  { smaller = other; }
  else if (other.y == smaller.y) { smaller.x = Min(smaller.x, other.x); }
  else if (other.y > smaller.y)  { /* smaller is already smaller */ }
  return smaller;
}

Text_coord text_coord_larger(Text_coord coord, Text_coord other)
{
  Text_coord larger = coord;
  if (0) {}
  else if (other.y > larger.y)  { larger = other; }
  else if (other.y == larger.y) { larger.x = Max(larger.x, other.x); }
  else if (other.y < larger.y)  { /* larger is already larger */ }
  return larger;
}

U8 u8_from_key(Key key, B32 is_shift_down, B32* out_is_printable)
{
  static B32 is_initialised = false;
  static struct {
    U8 ch;
    U8 ch_shift;
    B8 printable;
  } key_print_data_arr[Key__COUNT];

  if (!is_initialised) 
  {
    is_initialised = true;

    for (U32 i = 0; i < Key__COUNT; i++) {
      key_print_data_arr[i] = {'\0', '\0', false};
    }

    key_print_data_arr[Key__space]         = {' ',  ' ',  true};
    key_print_data_arr[Key__a]             = {'a',  'A',  true};
    key_print_data_arr[Key__b]             = {'b',  'B',  true};
    key_print_data_arr[Key__c]             = {'c',  'C',  true};
    key_print_data_arr[Key__d]             = {'d',  'D',  true};
    key_print_data_arr[Key__e]             = {'e',  'E',  true};
    key_print_data_arr[Key__f]             = {'f',  'F',  true};
    key_print_data_arr[Key__g]             = {'g',  'G',  true};
    key_print_data_arr[Key__h]             = {'h',  'H',  true};
    key_print_data_arr[Key__i]             = {'i',  'I',  true};
    key_print_data_arr[Key__j]             = {'j',  'J',  true};
    key_print_data_arr[Key__k]             = {'k',  'K',  true};
    key_print_data_arr[Key__l]             = {'l',  'L',  true};
    key_print_data_arr[Key__m]             = {'m',  'M',  true};
    key_print_data_arr[Key__n]             = {'n',  'N',  true};
    key_print_data_arr[Key__o]             = {'o',  'O',  true};
    key_print_data_arr[Key__p]             = {'p',  'P',  true};
    key_print_data_arr[Key__q]             = {'q',  'Q',  true};
    key_print_data_arr[Key__r]             = {'r',  'R',  true};
    key_print_data_arr[Key__s]             = {'s',  'S',  true};
    key_print_data_arr[Key__t]             = {'t',  'T',  true};
    key_print_data_arr[Key__u]             = {'u',  'U',  true};
    key_print_data_arr[Key__v]             = {'v',  'V',  true};
    key_print_data_arr[Key__w]             = {'w',  'W',  true};
    key_print_data_arr[Key__x]             = {'x',  'X',  true};
    key_print_data_arr[Key__y]             = {'y',  'Y',  true};
    key_print_data_arr[Key__z]             = {'z',  'Z',  true};
    key_print_data_arr[Key__0]             = {'0',  ')',  true};
    key_print_data_arr[Key__1]             = {'1',  '!',  true};
    key_print_data_arr[Key__2]             = {'2',  '@',  true};
    key_print_data_arr[Key__3]             = {'3',  '#',  true};
    key_print_data_arr[Key__4]             = {'4',  '$',  true};
    key_print_data_arr[Key__5]             = {'5',  '%',  true};
    key_print_data_arr[Key__6]             = {'6',  '^',  true};
    key_print_data_arr[Key__7]             = {'7',  '&',  true};
    key_print_data_arr[Key__8]             = {'8',  '*',  true};
    key_print_data_arr[Key__9]             = {'9',  '(',  true};
    key_print_data_arr[Key__backtick]      = {'`',  '~',  true};
    key_print_data_arr[Key__minus]         = {'-',  '_',  true};
    key_print_data_arr[Key__equals]        = {'=',  '+',  true};
    key_print_data_arr[Key__left_bracket]  = {'[',  '{',  true};
    key_print_data_arr[Key__right_bracket] = {']',  '}',  true};
    key_print_data_arr[Key__backslash]     = {'\\', '|',  true};
    key_print_data_arr[Key__semicolon]     = {';',  ':',  true};
    key_print_data_arr[Key__apostrophe]    = {'\'', '"',  true};
    key_print_data_arr[Key__comma]         = {',',  '<',  true};
    key_print_data_arr[Key__period]        = {'.',  '>',  true};
    key_print_data_arr[Key__slash]         = {'/',  '?',  true};
    key_print_data_arr[Key__enter]         = {'\n',  '\n',  true};
  }
  
  if (out_is_printable) { *out_is_printable = key_print_data_arr[key].printable; } ;
  U8 ch = key_print_data_arr[key].ch;
  if (is_shift_down) { ch = key_print_data_arr[key].ch_shift; }
  return ch;
}

UI_Text_op* ui_text_op_list_push(Arena* arena, UI_Text_op_list* list, UI_Text_op_kind kind)
{
  // The idea here is this. 
  // We only pass in the kind in here, since it is the only part that is shared by all the permutations
  // of this data structure. The fat part might be present and it might not be. 
  // So we leave it out to be then manually filled in by the caller. 
  // Kind of makes perfect sense.
  UI_Text_op* op = ArenaPush(arena, UI_Text_op);
  op->kind = kind;
  DllPushBack(list, op);
  list->count += 1;
  return op;
}

UI_Text_op_list ui_text_op_list_from_os_event_list(Arena* arena, OS_Event_list* event_list)
{
  UI_Text_op_list result_op_list = {};
  
  for (OS_Event* ev = event_list->first; ev; ev = ev->next)
  {
    if (ev->kind == OS_Event_kind__key && (ev->key_event.went_down || ev->key_event.repeat_down))
    {
      switch (ev->key_event.key)
      {
        case Key__arrow_left:
        {
          UI_Text_op* move = ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__move_cursor);
          move->opt_os_event = ev;
          if (ev->key_event.modifiers & OS_Event_modifier__shift) { move->keep_section_start_after_op = true; }
          if (ev->key_event.modifiers & OS_Event_modifier__control) { 
            move->move_specifier = UI_Text_op_move_specifier___move_1_word_left; 
          } 
          else {  
            move->move_specifier = UI_Text_op_move_specifier___move_1_char_left;
            move->override_move_and_move_to_section_min_if_ending_section = true;
          } 
        } break;

        case Key__arrow_right:
        {
          UI_Text_op* move = ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__move_cursor);
          move->opt_os_event = ev; 
          if (ev->key_event.modifiers & OS_Event_modifier__shift) { move->keep_section_start_after_op = true; }
          if (ev->key_event.modifiers & OS_Event_modifier__control) { 
            move->move_specifier = UI_Text_op_move_specifier___move_1_word_right; 
          } 
          else {  
            move->move_specifier = UI_Text_op_move_specifier___move_1_char_right;
            move->override_move_and_move_to_section_max_if_ending_section = true;
          } 
        } break;

        case Key__arrow_up:
        {
          UI_Text_op* move = ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__move_cursor);
          move->opt_os_event = ev; 
          move->move_specifier = UI_Text_op_move_specifier___move_1_line_up;
          if (ev->key_event.modifiers & OS_Event_modifier__shift) { move->keep_section_start_after_op = true; }
        } break;

        case Key__home:
        {
          UI_Text_op* op = ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__move_cursor);
          op->opt_os_event = ev;
          op->move_specifier = UI_Text_op_move_specifier___move_to_line_start;
          if (ev->key_event.modifiers & OS_Event_modifier__shift) { op->keep_section_start_after_op = true; }
        } break;

        case Key__end:
        {
          UI_Text_op* op = ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__move_cursor);
          op->opt_os_event = ev;
          op->move_specifier = UI_Text_op_move_specifier___move_to_line_end;
          if (ev->key_event.modifiers & OS_Event_modifier__shift) { op->keep_section_start_after_op = true; }
        } break;

        case Key__backspace:
        {
          // Section creation op 
          {
            UI_Text_op* move_op = ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__move_cursor);
            move_op->dont_move_if_section = true;
            move_op->keep_section_start_after_op = true;
            move_op->move_specifier = (ev->key_event.modifiers & OS_Event_modifier__control ? 
                                       UI_Text_op_move_specifier___move_1_word_left : 
                                       UI_Text_op_move_specifier___move_1_char_left); 
          }

          // Section deletion op
          UI_Text_op* final_delete_op = ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__delete_section);
          final_delete_op->opt_os_event = ev;
        } break;

        case Key__delete:
        {
          // Section creation op 
          {
            UI_Text_op* move_op = ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__move_cursor);
            move_op->dont_move_if_section = true;
            move_op->keep_section_start_after_op = true;
            move_op->move_specifier = (ev->key_event.modifiers & OS_Event_modifier__control ? 
                                       UI_Text_op_move_specifier___move_1_word_right : 
                                       UI_Text_op_move_specifier___move_1_char_right);
          }

          // Section deletion op
          UI_Text_op* final_delete_op = ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__delete_section);
          final_delete_op->opt_os_event = ev;
        } break;

        // note: This is test code here, added this on 9th of June 2026
        case Key__escape:
        {
          UI_Text_op* stop_edit_op = ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__stop_editing);
          stop_edit_op->opt_os_event = ev;
        } break;

        default:
        {
          if (ev->key_event.key == Key__c && ev->key_event.modifiers & OS_Event_modifier__control) // Copy
          {
            UI_Text_op* copy_op = ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__copy_section);
            copy_op->opt_os_event = ev;
            copy_op->keep_section_start_after_op = true;
          }
          else if (ev->key_event.key == Key__v && ev->key_event.modifiers & OS_Event_modifier__control) // Paste
          {
            UI_Text_op* ______________ = ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__delete_section);
            UI_Text_op* final_paste_op = ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__paste_at_cursor);
            final_paste_op->opt_os_event = ev;
          }
          else if (ev->key_event.key == Key__x && ev->key_event.modifiers & OS_Event_modifier__control) // Cut
          {
            UI_Text_op* copy_op = ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__copy_section);
            copy_op->keep_section_start_after_op = true;
            UI_Text_op* final_delete_op = ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__delete_section);
            final_delete_op->opt_os_event = ev;
          }
          else if (ev->key_event.key == Key__a && ev->key_event.modifiers & OS_Event_modifier__control) // Select all
          {
            UI_Text_op* move_1 = ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__move_cursor);
            move_1->move_specifier = UI_Text_op_move_specifier___move_to_line_start;

            UI_Text_op* move_2 = ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__move_cursor);
            move_2->opt_os_event = ev;
            move_2->move_specifier = UI_Text_op_move_specifier___move_to_line_end;
            move_2->keep_section_start_after_op = true;
          }
          else 
          {
            B32 is_printable = false;
            // todo: This shoud be a separate event in the win32 WM_CHAR and not this manual from key down shit
            U8 ch = u8_from_key(ev->key_event.key, ev->key_event.modifiers & OS_Event_modifier__shift, &is_printable); 
            if (is_printable && (ev->key_event.went_down || ev->key_event.repeat_down))
            {
              ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__delete_section);
              
              UI_Text_op* insert_op = ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__insert_char_at_cursor);
              insert_op->opt_os_event = ev;
              insert_op->char_to_insert = ch;
            
              UI_Text_op* cursor_move_op = ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__move_cursor);
              cursor_move_op->move_specifier = UI_Text_op_move_specifier___move_1_char_right;
            }
          }
        } break;
      }
    }
  }
  return result_op_list;
}

///////////////////////////////////////////////////////////
// - Text editing state thing to be able to modify based on text ops
//

// TODO: Might be a good idea to decouple it from S
Str8 app_get_text_line_for_coord(Str8 text, Text_coord coord, B32* opt_out_has_line)
{
  Scratch scratch  = get_scratch(0, 0);
  Str8 result_line = {};
  
  Str8_list lines     = str8_split_ex(scratch.arena, text, Str8FromC("\n"), 0, true);
  U64 test_line_index = 0;
  for (Str8_node* node = lines.first; node; node = node->next, test_line_index += 1)
  {
    if (test_line_index == coord.y)
    {
      result_line = node->str;
      if (opt_out_has_line) { *opt_out_has_line = true; }
      break;
    }
  }
  
  end_scratch(&scratch);
  return result_line; 
}

Str8 app_get_text_line_for_line_index(Str8 text, U64 line_index, B32* opt_out_has_line)
{
  return app_get_text_line_for_coord(text, { 0, line_index }, opt_out_has_line);
}

Text_coord app_move_text_coord_1_char_left(Str8 str, Text_coord coord)
{
  Str8 line = app_get_text_line_for_coord(str, coord, Null);
  if (coord.x == 0) 
  { 
    if (coord.y > 0) 
    {
      coord.y -= 1;
      Str8 prev_line = app_get_text_line_for_coord(str, coord, Null);
      coord.x = prev_line.count;
      line = prev_line;
    }
  } else {
    coord.x -= 1;
  }
  return coord;
}

Text_coord app_move_text_coord_1_char_right(Str8 str, Text_coord coord)
{
  Str8 line = app_get_text_line_for_coord(str, coord, Null);
  if (coord.x == line.count)
  {
    B32 next_line_exists = false;
    Str8 next_line = app_get_text_line_for_coord(str, { coord.x, coord.y + 1 }, &next_line_exists);
    if (next_line_exists)
    {
      coord.x = 0;
      coord.y += 1;
    }
  } else {
    coord.x += 1;
  }
  return coord;
}

U64 app_str_index_from_text_coord(Str8 str, Text_coord coord)
{
  Scratch scratch = get_scratch(0, 0);

  Str8* lines    = 0;
  U64 line_count = 0;
  str8_split_into_array(scratch.arena, str, Str8FromC("\n"), 0, true, &lines, &line_count);
  Assert(line_count != 0);

  if (coord.y >= line_count)
  {
    InvalidCodePath();
    coord.y = line_count - 1; // Line count is always at least 1
    Str8 line = lines[coord.y];
    if (coord.x > line.count) // Here it might be == .count since cursor might be in the end of the line
    {
      InvalidCodePath();
      coord.x = line.count;
    }
  }

  U64 result_index = 0;
  for EachIndex(i, str.count)
  {
    if (i == coord.y)
    {
      result_index += coord.x;
      break;
    }
    else
    {
      result_index += lines[i].count;
      result_index += Str8FromC("\n").count;
    }
  }
  
  end_scratch(&scratch);
  return result_index;
}

void app_get_line_section_parts(
  Str8 text, U64 line_index, Text_coord section_first_boundary, Text_coord section_other_boundary, 
  Str8* part_before_section, Str8* part_inside_section, Str8* part_after_section // THESE ARE MANDATORY 
) {
  Text_coord section_start = text_coord_smaller(section_first_boundary, section_other_boundary);
  Text_coord section_end   = text_coord_larger(section_first_boundary, section_other_boundary);

  Str8 line = app_get_text_line_for_line_index(text, line_index, 0);

  U64 section_left_boundary_for_line  = 0;
  U64 section_right_boundary_for_line = 0;
  if (0) {}
  else if (line_index < section_start.y) {}
  else if (line_index > section_end.y) {}
  else { 
    if (line_index == section_start.y)
    {
      section_left_boundary_for_line = section_start.x;
    } 
    
    if (line_index == section_end.y)
    {
      section_right_boundary_for_line = section_end.x;
    }
    else 
    {
      section_right_boundary_for_line = line.count;
    }
  }

  *part_before_section = str8_substring(line, 0, section_left_boundary_for_line);
  *part_inside_section = str8_substring(line, section_left_boundary_for_line, section_right_boundary_for_line);
  *part_after_section  = str8_substring(line, section_right_boundary_for_line, line.count);
}


void app_aply_text_ops_to_state(App_state* S, UI_Text_op_list text_op_list)
{
  U8* text_buffer        = S->buffer;
  U64* text_buffer_count = &S->buffer_count;
  Text_coord* cursor     = &S->cursor_coord;
  Text_coord* section    = &S->section_coord;

  for (UI_Text_op* text_op = text_op_list.first; text_op != 0; text_op = text_op->next)
  {
    switch (text_op->kind)
    { 
      default: {} break;

      case UI_Text_op_kind__move_cursor:
      {
        if ( text_op->dont_move_if_section 
          && !text_coord_eq(*cursor, *section)
        ) { 
          goto end_of_move_op_processing; 
        }
        
        if ( text_op->override_move_and_move_to_section_min_if_ending_section 
          && !text_coord_eq(*cursor, *section)
          && !text_op->keep_section_start_after_op
        ) {
          *cursor = text_coord_smaller(*cursor, *section);
          goto end_of_move_op_processing;
        }
        
        if (  text_op->override_move_and_move_to_section_max_if_ending_section 
          && !text_coord_eq(*cursor, *section) 
          && !text_op->keep_section_start_after_op
        ) {
          *cursor = text_coord_larger(*cursor, *section);
          goto end_of_move_op_processing;
        }

        Str8 text_buffer_str = str8_manual(text_buffer, *text_buffer_count);

        switch (text_op->move_specifier)
        {
          case UI_Text_op_move_specifier___move_1_char_left:  
          { 
            *cursor = app_move_text_coord_1_char_left(text_buffer_str, *cursor); 
          } break;

          case UI_Text_op_move_specifier___move_1_char_right: 
          { 
            *cursor = app_move_text_coord_1_char_right(text_buffer_str, *cursor); 
          } break;

          /*
          case UI_Text_op_move_specifier___move_1_word_left:  { *cursor_pos = __ui_move_with_control_left(str8_manual(text_buffer, *current_text_size), *cursor_pos); } break;
          case UI_Text_op_move_specifier___move_1_word_right: { *cursor_pos = __ui_move_with_control_right(str8_manual(text_buffer, *current_text_size), *cursor_pos); } break;

          case UI_Text_op_move_specifier___move_to_line_start: { cursor_pos->x = 0; } break;
          case UI_Text_op_move_specifier___move_to_line_end:   { cursor_pos->x = __ui_get_text_line_from_text(str8_manual(text_buffer, *current_text_size), cursor_pos->y, 0).count; } break;

          case UI_Text_op_move_specifier___move_specific_position: { *cursor_pos = text_op->cursor_specific_pos;  }

          case UI_Text_op_move_specifier___move_1_line_up: 
          { 
            // If top line then move 1 left
            if (cursor_pos->y == 0) { 
              if (cursor_pos->x > 0) {
                cursor_pos->x -= 1; 
              }
            }
            else 
            {
              Str8 line = __ui_get_text_line_from_text(str8_manual(text_buffer, *current_text_size), cursor_pos->y, Null);
              Str8 line_part_before_cursor = str8_substring(line, 0, cursor_pos->x);
              F32 x_offset = fp_measure_text(line_part_before_cursor, font).x;

              if (cursor_pos->y > 0)
              {
                cursor_pos->y -= 1;
                line = __ui_get_text_line_from_text(str8_manual(text_buffer, *current_text_size), cursor_pos->y, Null);

                U64 result_cursor_x = 0;
                F32 range_start_pos = 0.0f;
                for EachIndex(i, line.count)
                {
                  Str8 char_str       = str8_substring(line, i, i + 1);
                  F32 char_width      = fp_measure_text(char_str, font).x;
                  RangeF32 char_range = rangeF32(range_start_pos, range_start_pos + char_width);
                  range_start_pos += char_width;
                  
                  if (rangeF32_within(char_range, x_offset))
                  {
                    result_cursor_x = i;
                    if (x_offset > rangeF32_center(char_range)) {
                      result_cursor_x += 1;
                    }
                    break;
                  }
                }
  
                if (result_cursor_x == 0 && x_offset >= range_start_pos) { 
                  result_cursor_x = line.count;
                } 
              }
            }
          } break;
          */
          
          default: { InvalidCodePath(); } break;
        }

        end_of_move_op_processing: {}
      } break;

      case UI_Text_op_kind__delete_section:
      {
        Str8 text_buffer_str = str8_manual(text_buffer, *text_buffer_count);

        if (!text_coord_eq(*cursor, *section))
        {
          Scratch scratch = get_scratch(0, 0);

          Str8_list line_parts = {};

          U64 line_index = 0;
          for (;; line_index += 1)
          {
            B32 is_line = false; 
            Str8 line   = app_get_text_line_for_line_index(text_buffer_str, line_index, &is_line);
            if (!is_line) { break; }
            
            Str8 part_before_section = {};
            Str8 part_inside_section = {};
            Str8 part_after_section  = {};
            app_get_line_section_parts(
              text_buffer_str,
              line_index, 
              *cursor, *section,
              &part_before_section, &part_inside_section, &part_after_section
            );

            str8_list_append(scratch.arena, &line_parts, part_before_section);
            str8_list_append(scratch.arena, &line_parts, part_after_section);
            str8_list_append(scratch.arena, &line_parts, Str8FromC("\n"));
          }
          
          Str8 new_str = str8_from_list(scratch.arena, &line_parts);
          for EachIndex(i, new_str.count) { text_buffer[i] = new_str.data[i]; }
          *text_buffer_count = new_str.count;
          
          *cursor = text_coord_smaller(*cursor, *section); // This might also be just set by the special position by the user
          
          end_scratch(&scratch);
        }
      } break;

      /*
      case UI_Text_op_kind__copy_section:
      {
        BP;
        // todo: No raylib any more, have to use clipboard from win32 now buddy
        // Scratch scratch = get_scratch(0, 0);
        // Str8 text_to_copy = str8_substring(str8_manuall(text_buffer, *current_text_size), Min(*cursor_pos, *section_start), Max(*cursor_pos, *section_start));
        // Str8 text_to_copy_nt = str8_copy_alloc(scratch.arena, text_to_copy);
        // if (text_to_copy_nt.count != 0) { SetClipboardText((char*)text_to_copy_nt.data); }
        // end_scratch(&scratch);
      } break;
      */

      /*
      case UI_Text_op_kind__paste_at_cursor:
      {
        BP;
        // todo: No raylib any more, have to use clipboard from win32 now buddy

        // Pasting 
        // Str8 buffer_as_str = str8_manuall(text_buffer, *current_text_size);
        // Scratch scratch = get_scratch(0, 0);
        // Str8_list str_parts = {};
        // Str8 str_part_before_insert = str8_substring(buffer_as_str, 0, *cursor_pos);
        // Str8 str_part_after_insert = str8_substring(buffer_as_str, *cursor_pos, *current_text_size);
        // Str8 str_to_insert = {};
        // {
        //   char* clb_text = const_cast<char*>(GetClipboardText()); // todo: Remove this cpp shit here
        //   str_to_insert = str8_from_cstr(scratch.arena, (U8*)clb_text);
        // }
        // str8_list_append(scratch.arena, &str_parts, str_part_before_insert);
        // str8_list_append(scratch.arena, &str_parts, str_to_insert);
        // str8_list_append(scratch.arena, &str_parts, str_part_after_insert);
        // Str8 new_str = str8_from_list(scratch.arena, &str_parts);
        // Assert(new_str.count > *current_text_size);  
        // for EachIndex(i, Min(new_str.count, max_text_size) ) { text_buffer[i] = new_str.data[i]; }
        // *current_text_size = Min(new_str.count, max_text_size);
        // end_scratch(&scratch);
      
        // // Moving the cursor
        // *cursor_pos += str_to_insert.count; // todo: This will be wrong if overflow, fix this
      
        if (opt_out_did_text_change) { *opt_out_did_text_change = true; }
        
      } break;
      */

      case UI_Text_op_kind__insert_char_at_cursor:
      {
        Scratch scratch    = get_scratch(0, 0);
        Str8 buffer_as_str = str8_manual(text_buffer, *text_buffer_count);
        
        U64 in_text_index_for_cursor = app_str_index_from_text_coord(buffer_as_str, *cursor);
        
        Str8_list str_parts          = {};
        Str8 str_part_before_insert  = str8_substring(buffer_as_str, 0, in_text_index_for_cursor);
        Str8 str_part_after_insert   = str8_substring(buffer_as_str, in_text_index_for_cursor, *text_buffer_count);
        Str8 str_to_insert           = str8_from_cstr_len(scratch.arena, &text_op->char_to_insert, 1);
        str8_list_append(scratch.arena, &str_parts, str_part_before_insert);
        str8_list_append(scratch.arena, &str_parts, str_to_insert);
        str8_list_append(scratch.arena, &str_parts, str_part_after_insert);
        
        Str8 new_str = str8_from_list(scratch.arena, &str_parts);
        for EachIndex(i, Min(new_str.count, ArrayCount(S->buffer)) ) { text_buffer[i] = new_str.data[i]; }
        *text_buffer_count = Min(new_str.count, ArrayCount(S->buffer));
        
        end_scratch(&scratch);
      } break;

      /*
      case UI_Text_op_kind__stop_editing:
      {
        if (opt_out_escaped) { *opt_out_escaped = true; }
        stop_editing = true;
      } break;
      */
    }
    
    // TODO: here you shoud make you are in the valid place for the state to be in 
    //       with regard to all the text positions

    // Just in case
    // TODO: Assert the section as well
    // U64 cursor_index = __ui_get_index_in_text_for_text_pos(str8_manual(text_buffer, *current_text_size), *cursor_pos);
    // Assert(0 <= cursor_index && cursor_index <= *current_text_size);
    // clamp_u64_inplace(cursor_pos, 0, *current_text_size);
    
    if (!text_op->keep_section_start_after_op) { *section = *cursor; }

    if (text_op->opt_os_event) { os_consume_frame_event(text_op->opt_os_event); }
  }
}

void app_update(App_state* S)
{
  Scratch scratch = get_scratch(0, 0);
  
  OS_Event_list* event_list = os_get_frame_event_list();
  UI_Text_op_list text_ops = ui_text_op_list_from_os_event_list(scratch.arena, os_get_frame_event_list());
  app_aply_text_ops_to_state(S, text_ops);

  end_scratch(&scratch);
}

void app_render(App_state* S)
{
  Scratch scratch = get_scratch(0, 0);

  FP_Font font = S->font;
  Str8 text_str = str8_manual(S->buffer, S->buffer_count);

  F32 cursor_width = 2;

  Str8* lines    = 0;
  U64 line_count = 0;
  str8_split_into_array(scratch.arena, text_str, Str8FromC("\n"), 0, true, &lines, &line_count);

  // Drawing the lines
  for EachIndex(line_index, line_count)
  {
    Str8 line = lines[line_index];

    F32 line_offset_y = line_index * (fp_font_height(font) + fp_font_line_gap(font));
    d_draw_text(line, font, v2f32(0, line_offset_y), white());
  }

  // Drawing cursor
  {
    Text_coord cursor_coord      = S->cursor_coord;
    Str8 cursor_line             = app_get_text_line_for_coord(text_str, cursor_coord, Null);
    Str8 line_part_before_cursor = str8_substring(cursor_line, 0, cursor_coord.x);

    V2F32 cursor_offset = {};
    cursor_offset.x = fp_measure_text(line_part_before_cursor, font).x;
    cursor_offset.y = (cursor_coord.y * (fp_font_height(font) + fp_font_line_gap(font)));
  
    d_draw_rect(rect_make(cursor_offset.x, cursor_offset.y, cursor_width, fp_font_height(font)), nice_blue());
  }

  // Drawing section
  {
    Text_coord section_coord      = S->section_coord;
    Str8 section_line             = app_get_text_line_for_coord(text_str, section_coord, Null);
    Str8 line_part_before_section = str8_substring(section_line, 0, section_coord.x);

    V2F32 section_offset = {};
    section_offset.x = fp_measure_text(line_part_before_section, font).x;
    section_offset.y = (section_coord.y * (fp_font_height(font) + fp_font_line_gap(font)));
  
    d_draw_rect(rect_make(section_offset.x, section_offset.y, cursor_width, fp_font_height(font)), red());
  }

  end_scratch(&scratch);
}

#endif