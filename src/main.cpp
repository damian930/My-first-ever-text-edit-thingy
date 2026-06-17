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


// U8 u8_from_key(Key key, B32 is_shift_down, B32* out_is_printable)
// {
//   static B32 is_initialised = false;
//   static struct {
//     U8 ch;
//     U8 ch_shift;
//     B8 printable;
//   } key_print_data_arr[Key__COUNT];

//   if (!is_initialised) 
//   {
//     is_initialised = true;

//     for (U32 i = 0; i < Key__COUNT; i++) {
//       key_print_data_arr[i] = {'\0', '\0', false};
//     }

//     key_print_data_arr[Key__space]         = {' ',  ' ',  true};
//     key_print_data_arr[Key__a]             = {'a',  'A',  true};
//     key_print_data_arr[Key__b]             = {'b',  'B',  true};
//     key_print_data_arr[Key__c]             = {'c',  'C',  true};
//     key_print_data_arr[Key__d]             = {'d',  'D',  true};
//     key_print_data_arr[Key__e]             = {'e',  'E',  true};
//     key_print_data_arr[Key__f]             = {'f',  'F',  true};
//     key_print_data_arr[Key__g]             = {'g',  'G',  true};
//     key_print_data_arr[Key__h]             = {'h',  'H',  true};
//     key_print_data_arr[Key__i]             = {'i',  'I',  true};
//     key_print_data_arr[Key__j]             = {'j',  'J',  true};
//     key_print_data_arr[Key__k]             = {'k',  'K',  true};
//     key_print_data_arr[Key__l]             = {'l',  'L',  true};
//     key_print_data_arr[Key__m]             = {'m',  'M',  true};
//     key_print_data_arr[Key__n]             = {'n',  'N',  true};
//     key_print_data_arr[Key__o]             = {'o',  'O',  true};
//     key_print_data_arr[Key__p]             = {'p',  'P',  true};
//     key_print_data_arr[Key__q]             = {'q',  'Q',  true};
//     key_print_data_arr[Key__r]             = {'r',  'R',  true};
//     key_print_data_arr[Key__s]             = {'s',  'S',  true};
//     key_print_data_arr[Key__t]             = {'t',  'T',  true};
//     key_print_data_arr[Key__u]             = {'u',  'U',  true};
//     key_print_data_arr[Key__v]             = {'v',  'V',  true};
//     key_print_data_arr[Key__w]             = {'w',  'W',  true};
//     key_print_data_arr[Key__x]             = {'x',  'X',  true};
//     key_print_data_arr[Key__y]             = {'y',  'Y',  true};
//     key_print_data_arr[Key__z]             = {'z',  'Z',  true};
//     key_print_data_arr[Key__0]             = {'0',  ')',  true};
//     key_print_data_arr[Key__1]             = {'1',  '!',  true};
//     key_print_data_arr[Key__2]             = {'2',  '@',  true};
//     key_print_data_arr[Key__3]             = {'3',  '#',  true};
//     key_print_data_arr[Key__4]             = {'4',  '$',  true};
//     key_print_data_arr[Key__5]             = {'5',  '%',  true};
//     key_print_data_arr[Key__6]             = {'6',  '^',  true};
//     key_print_data_arr[Key__7]             = {'7',  '&',  true};
//     key_print_data_arr[Key__8]             = {'8',  '*',  true};
//     key_print_data_arr[Key__9]             = {'9',  '(',  true};
//     key_print_data_arr[Key__backtick]      = {'`',  '~',  true};
//     key_print_data_arr[Key__minus]         = {'-',  '_',  true};
//     key_print_data_arr[Key__equals]        = {'=',  '+',  true};
//     key_print_data_arr[Key__left_bracket]  = {'[',  '{',  true};
//     key_print_data_arr[Key__right_bracket] = {']',  '}',  true};
//     key_print_data_arr[Key__backslash]     = {'\\', '|',  true};
//     key_print_data_arr[Key__semicolon]     = {';',  ':',  true};
//     key_print_data_arr[Key__apostrophe]    = {'\'', '"',  true};
//     key_print_data_arr[Key__comma]         = {',',  '<',  true};
//     key_print_data_arr[Key__period]        = {'.',  '>',  true};
//     key_print_data_arr[Key__slash]         = {'/',  '?',  true};
//     key_print_data_arr[Key__enter]         = {'\n',  '\n',  true};
//   }
  
//   if (out_is_printable) { *out_is_printable = key_print_data_arr[key].printable; } ;
//   U8 ch = key_print_data_arr[key].ch;
//   if (is_shift_down) { ch = key_print_data_arr[key].ch_shift; }
//   return ch;
// }

// enum UI_Text_op_kind : U32 {  
//   UI_Text_op_kind__NONE,
//   UI_Text_op_kind__move_cursor,
//   UI_Text_op_kind__delete_section,
//   UI_Text_op_kind__copy_section,
//   UI_Text_op_kind__paste_at_cursor,
//   UI_Text_op_kind__insert_char_at_cursor, 
//   UI_Text_op_kind__stop_editing, 
// };

// enum UI_Text_op_move_specifier : U32 {
//   UI_Text_op_move_specifier___NONE,
//   UI_Text_op_move_specifier___move_1_char_left,                     
//   UI_Text_op_move_specifier___move_1_char_right,   
//   UI_Text_op_move_specifier___move_1_word_left,                     
//   UI_Text_op_move_specifier___move_1_word_right,                    
//   UI_Text_op_move_specifier___move_to_line_start,                   
//   UI_Text_op_move_specifier___move_to_line_end,          
//   UI_Text_op_move_specifier___move_specific_position,                     
//   UI_Text_op_move_specifier___move_1_line_up,          
// };

// struct UI_Text_op {
//   UI_Text_op_kind kind;
  
//   UI_Text_op* next;
//   UI_Text_op* prev;

//   OS_Event* opt_os_event;

//   // Fat struct data
//   U8 char_to_insert;               
//   B8 keep_section_start_after_op; 
//   B8 dont_move_if_section;
//   B8 override_move_and_move_to_section_min_if_ending_section;
//   B8 override_move_and_move_to_section_max_if_ending_section;
//   V2U64 cursor_specific_pos;
//   UI_Text_op_move_specifier move_specifier;
// };

// struct UI_Text_op_list {
//   UI_Text_op* first;
//   UI_Text_op* last;
//   U64 count;
// };

// Str8 __ui_get_text_line_from_text(Str8 text, U64 line_index, B32* opt_out_has_line)
// {
//   Scratch scratch = get_scratch(0, 0);

//   Str8 result_line    = {};
//   Str8_list lines     = str8_split_ex(scratch.arena, text, Str8FromC("\n"), 0, true);
//   U64 test_line_index = 0;
//   for (Str8_node* node = lines.first; node; node = node->next, test_line_index += 1)
//   {
//     if (test_line_index == line_index)
//     {
//       result_line = node->str;
//       if (opt_out_has_line) { *opt_out_has_line = true; }
//       break;
//     }
//   }
  
//   end_scratch(&scratch);
//   return result_line; 
// }

// U64 __ui_get_index_in_text_for_text_pos(Str8 test, V2U64 text_pos)
// {
//   B32 found           = false;
//   U64 result_index    = 0;
//   V2U64 following_pos = {};
//   for EachIndex(i, test.count)
//   {
//     U8 ch = test.data[i];
//     if (ch == '\n')
//     {
//       following_pos.y += 1;
//       following_pos.x  = 0;
//     } 
//     else 
//     {
//       following_pos.x += 1;
//     }

//     if (v2u64_match(text_pos, following_pos))
//     {
//       found = true;
//       result_index = i + 1; // I dont like this algo here at all
//       break;
//     }
//   }
//   return result_index;
// }

// V2U64 __ui_move_1_char_left(Str8 str, V2U64 text_pos)
// {
//   Str8 line = __ui_get_text_line_from_text(str, text_pos.y, Null);
//   Assert(0 <= text_pos.x && text_pos.x <= line.count);

//   if (text_pos.x == 0) 
//   { 
//     if (text_pos.y > 0) 
//     {
//       text_pos.y -= 1;
//       Str8 prev_line = __ui_get_text_line_from_text(str, text_pos.y, Null);
//       text_pos.x = prev_line.count;
//       line = prev_line;
//     }
//   }
//   else 
//   {
//     text_pos.x -= 1;
//   }

//   return text_pos;
// }

// V2U64 __ui_move_1_char_right(Str8 str, V2U64 text_pos)
// {
//   Str8 line = __ui_get_text_line_from_text(str, text_pos.y, Null);
//   Assert(0 <= text_pos.x && text_pos.x <= line.count);

//   if (text_pos.x == line.count)
//   {
//     B32 next_line_exists = false;
//     Str8 next_line = __ui_get_text_line_from_text(str, text_pos.y + 1, &next_line_exists);

//     if (next_line_exists)
//     {
//       text_pos.x = 0;
//       text_pos.y += 1;
//     }
//   }
//   else 
//   {
//     text_pos.x += 1;
//   }

//   return text_pos;
// }

// V2U64 __ui_move_with_control_left(Str8 str, V2U64 pos) 
// {
//   Str8 line = __ui_get_text_line_from_text(str, pos.y, 0);
//   Assert(pos.x <= line.count);

//   B32 go_to_prev_word_left_boundary_on_line = true;

//   // At the start of the line
//   if (pos.x == 0)
//   {
//     if (pos.y > 0)
//     {
//       pos.y -= 1;
//       Str8 prev_line = __ui_get_text_line_from_text(str, pos.y, Null);
//       pos.x = prev_line.count;
//       line = prev_line;
//     } 
//     else {
//       go_to_prev_word_left_boundary_on_line = false;
//     }
//   }

//   if (go_to_prev_word_left_boundary_on_line)
//   {
//     B32 is_done = false;
    
//     if (!is_done)
//     {
//       // Might be outside a word, have to move to the word end
//       for (;;)
//       {
//         if (pos.x == 0) { is_done = true; break; }                 
//         if (char_is_word_char(line.data[pos.x - 1])) { break; } 
//         pos.x -= 1;
//       }
//     }

//     if (!is_done)
//     {
//       // Migth be inside a word now, have to move to the start of it
//       for (;;)
//       {
//         if (pos.x == 0) { is_done = true; break; }                 
//         if (!char_is_word_char(line.data[pos.x - 1])) { is_done = true; break; } 
//         pos.x -= 1;
//       }
//     }
//   }

//   return pos;
// }

// V2U64 __ui_move_with_control_right(Str8 str, V2U64 pos) 
// {
//   Str8 line = __ui_get_text_line_from_text(str, pos.y, 0);
//   Assert(pos.x <= line.count);

//   B32 go_to_next_word_right_boundary_on_line = true;

//   // At the end of the line
//   if (pos.x == line.count)
//   {
//     B32 next_line_exists = false;
//     Str8 next_line = __ui_get_text_line_from_text(str, pos.y + 1, &next_line_exists);
//     if (next_line_exists)
//     {
//       line = next_line;
//       pos.y += 1;
//       pos.x = 0;
//     }
//     else {
//       go_to_next_word_right_boundary_on_line = false;
//     }
//   }

//   if (go_to_next_word_right_boundary_on_line)
//   {
//     B32 is_done = false;
    
//     if (!is_done)
//     {
//       // Might be outside a word, have to move to the start of the word
//       for (;;)
//       {
//         if (pos.x == line.count) { is_done = true; break; }                 
//         if (char_is_word_char(line.data[pos.x])) { break; } 
//         pos.x += 1;
//       }
//     }

//     if (!is_done)
//     {
//       // Migth be inside a word now, have to move to the end of it
//       for (;;)
//       {
//         if (pos.x == line.count) { is_done = true; break; }                 
//         if (!char_is_word_char(line.data[pos.x])) { is_done = true; break; } 
//         pos.x += 1;
//       }
//     }
//   }

//   return pos;
// }

// V2U64 smaller_text_pos(V2U64 pos, V2U64 other)
// {
//   V2U64 smaller = pos;
//   if (other.y < smaller.y)
//   {
//     smaller = other;
//   }
//   else if (other.y == smaller.y)
//   {
//     smaller.x = Min(smaller.x, other.x);
//   }
//   return smaller;
// }

// V2U64 larger_text_pos(V2U64 pos, V2U64 other)
// {
//   V2U64 larger = pos;
//   if (other.y > larger.y)
//   {
//     larger = other;
//   }
//   else if (other.y == larger.y)
//   {
//     larger.x = Max(larger.x, other.x);
//   }
//   return larger;
// }

// void __ui_get_line_section_parts(
//   Str8 text, U64 line_index, V2U64 section_first_boundary, V2U64 section_other_boundary, 
//   Str8* part_before_section, Str8* part_inside_section, Str8* part_after_section // THESE ARE MANDATORY 
// ) {
//   V2U64 section_start = smaller_text_pos(section_first_boundary, section_other_boundary);
//   V2U64 section_end   = larger_text_pos(section_first_boundary, section_other_boundary);

//   Str8 line = __ui_get_text_line_from_text(text, line_index, 0);

//   U64 section_left_boundary_for_line  = 0;
//   U64 section_right_boundary_for_line = 0;
//   if (0) {}
//   else if (line_index < section_start.y) {}
//   else if (line_index > section_end.y) {}
//   else { 
//     if (line_index == section_start.y)
//     {
//       section_left_boundary_for_line = section_start.x;
//     } 
    
//     if (line_index == section_end.y)
//     {
//       section_right_boundary_for_line = section_end.x;
//     }
//     else 
//     {
//       section_right_boundary_for_line = line.count;
//     }
//   }

//   *part_before_section = str8_substring(line, 0, section_left_boundary_for_line);
//   *part_inside_section = str8_substring(line, section_left_boundary_for_line, section_right_boundary_for_line);
//   *part_after_section  = str8_substring(line, section_right_boundary_for_line, line.count);
// }

// UI_Text_op* ui_text_op_list_push(Arena* arena, UI_Text_op_list* list, UI_Text_op_kind kind)
// {
//   // The idea here is this. 
//   // We only pass in the kind in here, since it is the only part that is shared by all the permutations
//   // of this data structure. The fat part might be present and it might not be. 
//   // So we leave it out to be then manually filled in by the caller. 
//   // Kind of makes perfect sense.
//   UI_Text_op* op = ArenaPush(arena, UI_Text_op);
//   op->kind = kind;
//   DllPushBack(list, op);
//   list->count += 1;
//   return op;
// }

// UI_Text_op_list ui_text_op_list_from_os_event_list(Arena* arena, OS_Event_list* event_list)
// {
//   UI_Text_op_list result_op_list = {};
  
//   for (OS_Event* ev = event_list->first; ev; ev = ev->next)
//   {
//     if (ev->kind == OS_Event_kind__key && (ev->key_event.went_down || ev->key_event.repeat_down))
//     {
//       switch (ev->key_event.key)
//       {
//         case Key__arrow_left:
//         {
//           UI_Text_op* move = ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__move_cursor);
//           move->opt_os_event = ev;
//           if (ev->key_event.modifiers & OS_Event_modifier__shift) { move->keep_section_start_after_op = true; }
//           if (ev->key_event.modifiers & OS_Event_modifier__control) { 
//             move->move_specifier = UI_Text_op_move_specifier___move_1_word_left; 
//           } 
//           else {  
//             move->move_specifier = UI_Text_op_move_specifier___move_1_char_left;
//             move->override_move_and_move_to_section_min_if_ending_section = true;
//           } 
//         } break;

//         case Key__arrow_right:
//         {
//           UI_Text_op* move = ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__move_cursor);
//           move->opt_os_event = ev; 
//           if (ev->key_event.modifiers & OS_Event_modifier__shift) { move->keep_section_start_after_op = true; }
//           if (ev->key_event.modifiers & OS_Event_modifier__control) { 
//             move->move_specifier = UI_Text_op_move_specifier___move_1_word_right; 
//           } 
//           else {  
//             move->move_specifier = UI_Text_op_move_specifier___move_1_char_right;
//             move->override_move_and_move_to_section_max_if_ending_section = true;
//           } 
//         } break;

//         case Key__arrow_up:
//         {
//           UI_Text_op* move = ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__move_cursor);
//           move->opt_os_event = ev; 
//           move->move_specifier = UI_Text_op_move_specifier___move_1_line_up;
//           if (ev->key_event.modifiers & OS_Event_modifier__shift) { move->keep_section_start_after_op = true; }
//         } break;

//         case Key__home:
//         {
//           UI_Text_op* op = ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__move_cursor);
//           op->opt_os_event = ev;
//           op->move_specifier = UI_Text_op_move_specifier___move_to_line_start;
//           if (ev->key_event.modifiers & OS_Event_modifier__shift) { op->keep_section_start_after_op = true; }
//         } break;

//         case Key__end:
//         {
//           UI_Text_op* op = ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__move_cursor);
//           op->opt_os_event = ev;
//           op->move_specifier = UI_Text_op_move_specifier___move_to_line_end;
//           if (ev->key_event.modifiers & OS_Event_modifier__shift) { op->keep_section_start_after_op = true; }
//         } break;

//         case Key__backspace:
//         {
//           // Section creation op 
//           {
//             UI_Text_op* move_op = ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__move_cursor);
//             move_op->dont_move_if_section = true;
//             move_op->keep_section_start_after_op = true;
//             move_op->move_specifier = (ev->key_event.modifiers & OS_Event_modifier__control ? 
//                                        UI_Text_op_move_specifier___move_1_word_left : 
//                                        UI_Text_op_move_specifier___move_1_char_left); 
//           }

//           // Section deletion op
//           UI_Text_op* final_delete_op = ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__delete_section);
//           final_delete_op->opt_os_event = ev;
//         } break;

//         case Key__delete:
//         {
//           // Section creation op 
//           {
//             UI_Text_op* move_op = ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__move_cursor);
//             move_op->dont_move_if_section = true;
//             move_op->keep_section_start_after_op = true;
//             move_op->move_specifier = (ev->key_event.modifiers & OS_Event_modifier__control ? 
//                                        UI_Text_op_move_specifier___move_1_word_right : 
//                                        UI_Text_op_move_specifier___move_1_char_right);
//           }

//           // Section deletion op
//           UI_Text_op* final_delete_op = ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__delete_section);
//           final_delete_op->opt_os_event = ev;
//         } break;

//         // note: This is test code here, added this on 9th of June 2026
//         case Key__escape:
//         {
//           UI_Text_op* stop_edit_op = ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__stop_editing);
//           stop_edit_op->opt_os_event = ev;
//         } break;

//         default:
//         {
//           if (ev->key_event.key == Key__c && ev->key_event.modifiers & OS_Event_modifier__control) // Copy
//           {
//             UI_Text_op* copy_op = ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__copy_section);
//             copy_op->opt_os_event = ev;
//             copy_op->keep_section_start_after_op = true;
//           }
//           else if (ev->key_event.key == Key__v && ev->key_event.modifiers & OS_Event_modifier__control) // Paste
//           {
//             UI_Text_op* ______________ = ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__delete_section);
//             UI_Text_op* final_paste_op = ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__paste_at_cursor);
//             final_paste_op->opt_os_event = ev;
//           }
//           else if (ev->key_event.key == Key__x && ev->key_event.modifiers & OS_Event_modifier__control) // Cut
//           {
//             UI_Text_op* copy_op = ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__copy_section);
//             copy_op->keep_section_start_after_op = true;
//             UI_Text_op* final_delete_op = ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__delete_section);
//             final_delete_op->opt_os_event = ev;
//           }
//           else if (ev->key_event.key == Key__a && ev->key_event.modifiers & OS_Event_modifier__control) // Select all
//           {
//             UI_Text_op* move_1 = ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__move_cursor);
//             move_1->move_specifier = UI_Text_op_move_specifier___move_to_line_start;

//             UI_Text_op* move_2 = ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__move_cursor);
//             move_2->opt_os_event = ev;
//             move_2->move_specifier = UI_Text_op_move_specifier___move_to_line_end;
//             move_2->keep_section_start_after_op = true;
//           }
//           else 
//           {
//             B32 is_printable = false;
//             // todo: This shoud be a separate event in the win32 WM_CHAR and not this manual from key down shit
//             U8 ch = u8_from_key(ev->key_event.key, ev->key_event.modifiers & OS_Event_modifier__shift, &is_printable); 
//             if (is_printable && (ev->key_event.went_down || ev->key_event.repeat_down))
//             {
//               ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__delete_section);
              
//               UI_Text_op* insert_op = ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__insert_char_at_cursor);
//               insert_op->opt_os_event = ev;
//               insert_op->char_to_insert = ch;
            
//               UI_Text_op* cursor_move_op = ui_text_op_list_push(arena, &result_op_list, UI_Text_op_kind__move_cursor);
//               cursor_move_op->move_specifier = UI_Text_op_move_specifier___move_1_char_right;
//             }
//           }
//         } break;
//       }
//     }
//   }
//   return result_op_list;
// }
 
// void ui_aply_text_ops(UI_Text_op_list text_op_list, U8* text_buffer, U64 max_text_size, U64* current_text_size, V2U64* cursor_pos, V2U64* section_start, B32* opt_out_did_text_change, B32* opt_out_escaped, FP_Font font)
// {
//   if (opt_out_did_text_change) { *opt_out_did_text_change = false; }
//   if (opt_out_escaped) { *opt_out_escaped = false; }

//   B32 stop_editing = false;
//   for (UI_Text_op* text_op = text_op_list.first; text_op != 0; text_op = text_op->next)
//   {
//     switch (text_op->kind)
//     { 
//       default: {} break;

//       case UI_Text_op_kind__move_cursor:
//       {
//         if (text_op->dont_move_if_section && !v2u64_match(*section_start, *cursor_pos)) { goto end_of_move_op_processing; }
        
//         if (text_op->override_move_and_move_to_section_min_if_ending_section && !v2u64_match(*section_start, *cursor_pos) && !text_op->keep_section_start_after_op) {
//           if      (cursor_pos->y < section_start->y) { /* cursor is already min */ }
//           else if (section_start->y < cursor_pos->y) { *cursor_pos = *section_start; }
//           else                                       { cursor_pos->x = Min(cursor_pos->x, section_start->x); }
//           goto end_of_move_op_processing;
//         }
        
//         if (text_op->override_move_and_move_to_section_max_if_ending_section && !v2u64_match(*section_start, *cursor_pos) && !text_op->keep_section_start_after_op) {
//           if      (cursor_pos->y < section_start->y) { *cursor_pos = *section_start; }
//           else if (cursor_pos->y > section_start->y) { /* cursor is already min */ }
//           else                                       { cursor_pos->x = Max(cursor_pos->x, section_start->x); }
//           goto end_of_move_op_processing;
//         }

//         switch (text_op->move_specifier)
//         {
//           case UI_Text_op_move_specifier___move_1_char_left:  { *cursor_pos = __ui_move_1_char_left(str8_manual(text_buffer, *current_text_size), *cursor_pos); } break;
//           case UI_Text_op_move_specifier___move_1_char_right: { *cursor_pos = __ui_move_1_char_right(str8_manual(text_buffer, *current_text_size), *cursor_pos); } break;

//           case UI_Text_op_move_specifier___move_1_word_left:  { *cursor_pos = __ui_move_with_control_left(str8_manual(text_buffer, *current_text_size), *cursor_pos); } break;
//           case UI_Text_op_move_specifier___move_1_word_right: { *cursor_pos = __ui_move_with_control_right(str8_manual(text_buffer, *current_text_size), *cursor_pos); } break;

//           case UI_Text_op_move_specifier___move_to_line_start: { cursor_pos->x = 0; } break;
//           case UI_Text_op_move_specifier___move_to_line_end:   { cursor_pos->x = __ui_get_text_line_from_text(str8_manual(text_buffer, *current_text_size), cursor_pos->y, 0).count; } break;

//           case UI_Text_op_move_specifier___move_specific_position: { *cursor_pos = text_op->cursor_specific_pos;  }

//           case UI_Text_op_move_specifier___move_1_line_up: 
//           { 
//             // If top line then move 1 left
//             if (cursor_pos->y == 0) { 
//               if (cursor_pos->x > 0) {
//                 cursor_pos->x -= 1; 
//               }
//             }
//             else 
//             {
//               Str8 line = __ui_get_text_line_from_text(str8_manual(text_buffer, *current_text_size), cursor_pos->y, Null);
//               Str8 line_part_before_cursor = str8_substring(line, 0, cursor_pos->x);
//               F32 x_offset = fp_measure_text(line_part_before_cursor, font).x;

//               if (cursor_pos->y > 0)
//               {
//                 cursor_pos->y -= 1;
//                 line = __ui_get_text_line_from_text(str8_manual(text_buffer, *current_text_size), cursor_pos->y, Null);

//                 U64 result_cursor_x = 0;
//                 F32 range_start_pos = 0.0f;
//                 for EachIndex(i, line.count)
//                 {
//                   Str8 char_str       = str8_substring(line, i, i + 1);
//                   F32 char_width      = fp_measure_text(char_str, font).x;
//                   RangeF32 char_range = rangeF32(range_start_pos, range_start_pos + char_width);
//                   range_start_pos += char_width;
                  
//                   if (rangeF32_within(char_range, x_offset))
//                   {
//                     result_cursor_x = i;
//                     if (x_offset > rangeF32_center(char_range)) {
//                       result_cursor_x += 1;
//                     }
//                     break;
//                   }
//                 }
  
//                 if (result_cursor_x == 0 && x_offset >= range_start_pos) { 
//                   result_cursor_x = line.count;
//                 } 
//               }
//             }
//           } break;
          
//           default: { InvalidCodePath(); } break;
//         }

//         end_of_move_op_processing: {}
//       } break;

//       case UI_Text_op_kind__delete_section:
//       {
//         if (!v2u64_match(*cursor_pos, *section_start))
//         {
//           Scratch scratch = get_scratch(0, 0);

//           Str8_list line_parts = {};

//           U64 line_index = 0;
//           for (;; line_index += 1)
//           {
//             B32 is_line = false; 
//             Str8 line   = __ui_get_text_line_from_text(str8_manual(text_buffer, *current_text_size), line_index, &is_line);
//             if (!is_line) { break; }
            
//             Str8 part_before_section = {};
//             Str8 part_inside_section = {};
//             Str8 part_after_section  = {};
//             __ui_get_line_section_parts(
//               str8_manual(text_buffer, *current_text_size),
//               line_index, 
//               *cursor_pos, *section_start,
//               &part_before_section, &part_inside_section, &part_after_section
//             );

//             str8_list_append(scratch.arena, &line_parts, part_before_section);
//             str8_list_append(scratch.arena, &line_parts, part_after_section);
//             str8_list_append(scratch.arena, &line_parts, Str8FromC("\n"));
//           }
          
//           Str8 new_str = str8_from_list(scratch.arena, &line_parts);
//           for EachIndex(i, new_str.count) { text_buffer[i] = new_str.data[i]; }
//           *current_text_size = new_str.count;
          
//           *cursor_pos = smaller_text_pos(*cursor_pos, *section_start); // This might also be just set by the special position by the user
//           if (opt_out_did_text_change) { *opt_out_did_text_change = true; }
          
//           end_scratch(&scratch);
//         }
//       } break;

//       /*
//       case UI_Text_op_kind__copy_section:
//       {
//         BP;
//         // todo: No raylib any more, have to use clipboard from win32 now buddy
//         // Scratch scratch = get_scratch(0, 0);
//         // Str8 text_to_copy = str8_substring(str8_manuall(text_buffer, *current_text_size), Min(*cursor_pos, *section_start), Max(*cursor_pos, *section_start));
//         // Str8 text_to_copy_nt = str8_copy_alloc(scratch.arena, text_to_copy);
//         // if (text_to_copy_nt.count != 0) { SetClipboardText((char*)text_to_copy_nt.data); }
//         // end_scratch(&scratch);
//       } break;
//       */

//       /*
//       case UI_Text_op_kind__paste_at_cursor:
//       {
//         BP;
//         // todo: No raylib any more, have to use clipboard from win32 now buddy

//         // Pasting 
//         // Str8 buffer_as_str = str8_manuall(text_buffer, *current_text_size);
//         // Scratch scratch = get_scratch(0, 0);
//         // Str8_list str_parts = {};
//         // Str8 str_part_before_insert = str8_substring(buffer_as_str, 0, *cursor_pos);
//         // Str8 str_part_after_insert = str8_substring(buffer_as_str, *cursor_pos, *current_text_size);
//         // Str8 str_to_insert = {};
//         // {
//         //   char* clb_text = const_cast<char*>(GetClipboardText()); // todo: Remove this cpp shit here
//         //   str_to_insert = str8_from_cstr(scratch.arena, (U8*)clb_text);
//         // }
//         // str8_list_append(scratch.arena, &str_parts, str_part_before_insert);
//         // str8_list_append(scratch.arena, &str_parts, str_to_insert);
//         // str8_list_append(scratch.arena, &str_parts, str_part_after_insert);
//         // Str8 new_str = str8_from_list(scratch.arena, &str_parts);
//         // Assert(new_str.count > *current_text_size);  
//         // for EachIndex(i, Min(new_str.count, max_text_size) ) { text_buffer[i] = new_str.data[i]; }
//         // *current_text_size = Min(new_str.count, max_text_size);
//         // end_scratch(&scratch);
      
//         // // Moving the cursor
//         // *cursor_pos += str_to_insert.count; // todo: This will be wrong if overflow, fix this
      
//         if (opt_out_did_text_change) { *opt_out_did_text_change = true; }
        
//       } break;
//       */

//       case UI_Text_op_kind__insert_char_at_cursor:
//       {
//         Scratch scratch              = get_scratch(0, 0);
//         Str8 buffer_as_str           = str8_manual(text_buffer, *current_text_size);
        
//         U64 in_text_index_for_cursor = __ui_get_index_in_text_for_text_pos(buffer_as_str, *cursor_pos);
        
//         Str8_list str_parts          = {};
//         Str8 str_part_before_insert  = str8_substring(buffer_as_str, 0, in_text_index_for_cursor);
//         Str8 str_part_after_insert   = str8_substring(buffer_as_str, in_text_index_for_cursor, *current_text_size);
//         Str8 str_to_insert           = str8_from_cstr_len(scratch.arena, &text_op->char_to_insert, 1);
//         str8_list_append(scratch.arena, &str_parts, str_part_before_insert);
//         str8_list_append(scratch.arena, &str_parts, str_to_insert);
//         str8_list_append(scratch.arena, &str_parts, str_part_after_insert);
        
//         Str8 new_str = str8_from_list(scratch.arena, &str_parts);
//         for EachIndex(i, Min(new_str.count, max_text_size) ) { text_buffer[i] = new_str.data[i]; }
//         *current_text_size = Min(new_str.count, max_text_size);
        
//         end_scratch(&scratch);

//         if (opt_out_did_text_change) { *opt_out_did_text_change = true; }
//       } break;

//       /*
//       case UI_Text_op_kind__stop_editing:
//       {
//         if (opt_out_escaped) { *opt_out_escaped = true; }
//         stop_editing = true;
//       } break;
//       */
//     }
    
//     // Just in case
//     // TODO: Assert the section as well
//     U64 cursor_index = __ui_get_index_in_text_for_text_pos(str8_manual(text_buffer, *current_text_size), *cursor_pos);
//     Assert(0 <= cursor_index && cursor_index <= *current_text_size);
//     // clamp_u64_inplace(cursor_pos, 0, *current_text_size);
    
//     if (!text_op->keep_section_start_after_op) { *section_start = *cursor_pos; }

//     // TODO: This might fuck up the list there
//     if (text_op->opt_os_event) { os_consume_frame_event(text_op->opt_os_event); }

//     if (stop_editing) { break; }
//   }
// }

// struct App_state {
//   U8 buffer[1024];
//   U64 count;
//   V2U64 cursor_pos;
//   V2U64 section_pos;

//   B32 last_event_was_char_selection;
// };

// void app_update(App_state* S, FP_Font font)
// {
//   Scratch scratch = get_scratch(0, 0);
//   UI_Text_op_list text_ops = ui_text_op_list_from_os_event_list(scratch.arena, os_get_frame_event_list());

//   ui_aply_text_ops(
//     text_ops, 
//     S->buffer, ArrayCount(S->buffer), &S->count, 
//     &S->cursor_pos, &S->section_pos, 
//     0, 0,
//     font
//   );
//   if (text_ops.count != 0) { 
//     if (S->last_event_was_char_selection)
//     {
//       S->last_event_was_char_selection = false; 
//     }
//   }
  
//   end_scratch(&scratch);
// }

// U64 char_index_in_line_from_offset_pos(Str8 text, F32 offset_pos, FP_Font font, F32 text_offset, F32 min_on_screen_pos)
// {
//   U64 result_cursor_pos = 0;

//   F32 range_start_pos = text_offset;

//   for EachIndex(i, text.count)
//   {
//     Str8 char_str       = str8_substring(text, i, i + 1);
//     F32 char_width      = fp_measure_text(char_str, font).x;
//     RangeF32 char_range = rangeF32(range_start_pos, range_start_pos + char_width);
//     range_start_pos += char_width;
    
//     if (rangeF32_within(char_range, offset_pos))
//     {
//       result_cursor_pos = i;
//       if (offset_pos > rangeF32_center(char_range)) {
//         result_cursor_pos += 1;
//       }
//       break;
//     }
//   }

//   if (result_cursor_pos == 0 && offset_pos >= range_start_pos) { 
//     result_cursor_pos = text.count;
//   } 

//   return result_cursor_pos;
// }

// void app_render(App_state* S, FP_Font font)
// {
//   // This is state fro the rendering part, kind of like state for the ui widget i guess
//   static F32   stored_offset        = 0.0f;
//   static B32   mouse_was_down       = false;
//   static B32   mouse_is_down        = false;
//   static V2U64 cursor_at_mouse_down = {};
  
//   mouse_was_down = mouse_is_down;

//   Scratch scratch = get_scratch(0, 0);
  
//   Rect clip_rect        = rect_make_v(v2f32(0, 0), os_get_client_area_dims());
//   Str8 str              = str8_manual(S->buffer, S->count);
//   F32 cursor_width      = 2.0f;
//   Str8_list line_splits = str8_split(scratch.arena, str, Str8FromC("\n"), 0); 

//   // Getting the line at which the cursor is
//   Str8 cursor_line_str = {};
//   U64 node_index = 0;
//   for (Str8_node* node = line_splits.first; node; node = node->next)
//   {
//     if (node_index == S->cursor_pos.y)
//     {
//       cursor_line_str = node->str;
//       break;
//     }
//     node_index += 1;
//   }

//   Str8 cursor_substring_on_cursor_line = str8_substring(cursor_line_str, 0, S->cursor_pos.x);
//   F32 x_offset_on_line = fp_measure_text(cursor_substring_on_cursor_line, font).x;

//   F32 y_offset_on_line = S->cursor_pos.y * fp_font_height(font);

//   // U64 text_index_for_cursor_pos  = __ui_get_index_in_text_for_text_pos(str, S->cursor_pos);
//   // U64 text_index_for_section_pos = __ui_get_index_in_text_for_text_pos(str, S->section_pos);

//   // RangeU64 section_index_range = rangeU64_sorted(text_index_for_cursor_pos, text_index_for_section_pos);
//   // Str8 str_before_section      = str8_substring(str, 0, section_index_range.min);
//   // Str8 str_inside_section      = str8_substring(str, section_index_range.min, section_index_range.max);
//   // Str8 str_after_section       = str8_substring(str, section_index_range.max, str.count);

//   // we have 2 text position, 
//   // get the line for the start of it
//   // get the line for the end of it
//   // have the space before be the space 

//   // get pos for the section stat on this line
//   // measure that and then get the offset for x

//   // todo: fp_measure text measured text in x onlye
//   // F32 space_before_section = fp_measure_text(str_before_section, font).x;
//   // F32 space_inside_section = fp_measure_text(str_inside_section, font).x;
//   // F32 space_after_section  = fp_measure_text(str_after_section, font).x;

//   for (OS_Event* ev = os_get_frame_event_list()->first; ev; ev = ev->next)
//   {
//     if (ev->kind == OS_Event_kind__mouse && ev->mouse_event.button == Mouse_button__left && ev->mouse_event.went_down)
//     {
//       mouse_is_down   = true;
//       os_consume_frame_event(ev);
//     }
//     else if (ev->kind == OS_Event_kind__mouse && ev->mouse_event.button == Mouse_button__left && ev->mouse_event.went_up)
//     {
//       mouse_is_down = false;
//       os_consume_frame_event(ev);
//     }
//   }

//   // Cursor placement from mouse down or selection
//   /*
//   if (!mouse_was_down && mouse_is_down)
//   {
//     V2F32 mouse_pos  = os_get_mouse_pos();
//     V2U64 new_cursor = cursor_pos_in_text_from_mouse_pos(str, mouse_pos.x, font, stored_offset, 0);
//     S->cursor_pos    = new_cursor;
//     S->section_pos   = new_cursor;
//     S->last_event_was_char_selection = true;

//     cursor_at_mouse_down = new_cursor;
//   }
//   else if (mouse_is_down)
//   {
//     V2F32 mouse_pos = os_get_mouse_pos();
//     V2U64 new_cursor = cursor_pos_in_text_from_mouse_pos(str, mouse_pos.x, font, stored_offset, 0);

//     if (!v2u64_match(cursor_at_mouse_down, new_cursor))
//     {
//       S->cursor_pos = new_cursor;
//     }
//   }
//   */

//   // TODO: What is this for
//   F32 offset_before_cursor_on_x = x_offset_on_line;
//   // F32 offset_before_cursor_on_y = ;
//   // if (S->cursor_pos == section_range.max) { offset_before_cursor += space_inside_section; }

//   // TODO: This is fro the current line 
//   /*
//   F32 buffer_zone_end_width = 20.0f;
//   {
//     U64 chars_to_use_as_buffer = 3;
//     if (S->cursor_pos <= u64_max - chars_to_use_as_buffer)
//     {
//       Str8 buffer_zone  = str8_substring(str, S->cursor_pos, S->cursor_pos + 3); 
//       if (buffer_zone.count != 0)
//       {
//         buffer_zone_end_width = fp_measure_text(buffer_zone, font).x;
//       }
//     }
//   }
//   */

//   // TODO: This is fro the current line 
//   /*
//   F32 buffer_zone_start_width = 0.0f;
//   {
//     U64 chars_to_use_as_buffer = 3;
//     if (S->cursor_pos.x >= 3)
//     {
//       Str8 buffer_zone = str8_substring(str, S->cursor_pos - chars_to_use_as_buffer, S->cursor_pos);
//       if (buffer_zone.count != 0)
//       {
//         buffer_zone_start_width = fp_measure_text(buffer_zone, font).x;
//       }
//     }
//   }
//   */

//   RangeF32 visible_range        = rect_get_range_x(clip_rect);
//   RangeF32 cursor_visible_range = visible_range;
  
//   // If we select then we dont want to have the buffer spacing done
//   /*
//   if (!S->last_event_was_char_selection)
//   {
//     cursor_visible_range.max -= buffer_zone_end_width;
//     if (offset_before_cursor > visible_range.min) { cursor_visible_range.min += buffer_zone_start_width; }
//   }
//   */

//   // Adjusting the offset
//   /*
//   F32 cursor_offset_adjusted = offset_before_cursor + stored_offset;
//   if (0) {}
//   else if (cursor_offset_adjusted < cursor_visible_range.min) 
//   {
//     F32 diff = cursor_visible_range.min - cursor_offset_adjusted;
//     stored_offset += diff;
//   }
//   else if (cursor_offset_adjusted + cursor_width > cursor_visible_range.max) 
//   {
//     F32 diff = cursor_offset_adjusted + cursor_width - cursor_visible_range.max;
//     stored_offset += (-1 * diff);
//   }
//   */

//   d_draw_rect_inset_borders(clip_rect, black(), 1, v4f32_all(0), 0);
//   D_Offset(stored_offset, 0)
//   D_ScissorRect(clip_rect)
//   {
//     V2U64 section_min_pos = smaller_text_pos(S->cursor_pos, S->section_pos);
//     V2U64 section_max_pos = larger_text_pos(S->cursor_pos, S->section_pos);

//     // Drawing complete text
//     Str8 cursor_line = {};
//     Str8 section_line = {};
//     U64 line_index = 0;
//     for (Str8_node* line_node = line_splits.first; line_node; line_node = line_node->next)
//     {
//       if (line_index == S->cursor_pos.y) { cursor_line = line_node->str; }
//       if (line_index == S->section_pos.y) { section_line = line_node->str; }

//       Str8 line = line_node->str;
//       d_draw_text(line, font, v2f32(0, (F32)line_index * fp_font_height(font)), black());
//       line_index += 1;
//     }

//     F32 cursor_offset_y = S->cursor_pos.y * fp_font_height(font);
//     F32 cursor_offset_x = fp_measure_text(str8_substring(cursor_line, 0, S->cursor_pos.x), font).x;

//     F32 section_offset_y = S->section_pos.y * fp_font_height(font);
//     F32 section_offset_x = fp_measure_text(str8_substring(section_line, 0, S->section_pos.x), font).x;

//     if (v2u64_match(S->section_pos, S->cursor_pos))
//     {
//       d_draw_rect(rect_make(cursor_offset_x, cursor_offset_y, 2, fp_font_height(font)), blue());
//     }
//     else 
//     {
//       F32 line_width  = 10;
//       F32 line_height = 2;

//       // Cursor
//       {
//         Rect top_line_rect = rect_make(cursor_offset_x, cursor_offset_y, line_width, line_height);
//         Rect bottom_line_rect = rect_make(cursor_offset_x, cursor_offset_y + fp_font_height(font) - line_height, line_width, line_height);
//         if (v2u64_match(S->cursor_pos, larger_text_pos(S->cursor_pos, S->section_pos)))
//         {
//           top_line_rect.x -= line_width; 
//           bottom_line_rect.x -= line_width; 
//         } 
//         d_draw_rect(top_line_rect, blue());
//         d_draw_rect(bottom_line_rect, blue());
//         d_draw_rect(rect_make(cursor_offset_x, cursor_offset_y, 2, fp_font_height(font)), blue());
//       }

//       // Section
//       {
//         Rect top_line_rect = rect_make(section_offset_x, section_offset_y, line_width, line_height);
//         Rect bottom_line_rect = rect_make(section_offset_x, section_offset_y + fp_font_height(font) - line_height, line_width, line_height);
//         if (v2u64_match(S->section_pos, larger_text_pos(S->cursor_pos, S->section_pos)))
//         {
//           top_line_rect.x -= line_width; 
//           bottom_line_rect.x -= line_width; 
//         } 
//         d_draw_rect(top_line_rect, blue());
//         d_draw_rect(bottom_line_rect, blue());
//         d_draw_rect(rect_make(section_offset_x, section_offset_y, 2, fp_font_height(font)), blue());
//       }
//     }

//   }

//   end_scratch(&scratch);
// }

// */

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
  FP_Font font = fp_load_font(Str8FromC("../data/Roboto.ttf"), 32, rangeU64(0, (U64)u8_max + 1));;

  App_state S = {};
  S.font = font;

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
              