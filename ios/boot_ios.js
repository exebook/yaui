log('boot_ios begin')
var 
ya_flag_ = 0x100,
ya_flag_parent = 0x200,
ya_flag_view = 0x400,
ya_flag_textview = 0x800,
ya_main_handle          = 0,
ya_alert                = 1,
ya_make_button          = 2 + ya_flag_parent,
ya_make_label           = 3 + ya_flag_parent,
ya_make_input           = 4 + ya_flag_parent,
ya_make_edit            = 5 + ya_flag_parent,
ya_make_image           = 6 + ya_flag_parent,
ya_make_hview           = 7 + ya_flag_parent,
ya_make_vview           = 8 + ya_flag_parent,
ya_hide                 = 9 + ya_flag_view,
ya_show                 = 10 + ya_flag_view,
ya_input_line           = 11 + ya_flag_textview,
ya_text_of_text         = 12 + ya_flag_textview,
ya_set_text             = 13 + ya_flag_textview,
ya_set_font             = 14 + ya_flag_textview,
ya_set_read_only        = 15 + ya_flag_textview,
ya_set_scroll_area      = 16 + ya_flag_view,
ya_set_scroll_pos       = 17 + ya_flag_view,
ya_set_bgcolor          = 18 + ya_flag_view,
ya_set_xywh             = 19 + ya_flag_view,
ya_get_app_size         = 20,
ya_get_scroll_pos       = 21 + ya_flag_view,
ya_set_timeout          = 22;

yaui.root_handle = ijs_control_call(0)

yaui.make_button = function(parent) {
	return ijs_control_call(ya_make_button, parent)
}
yaui.make_label = function(parent) {
	return ijs_control_call(ya_make_label, parent)
}
yaui.set_text = function(id, caption) {
	ijs_control_call(ya_set_text, id, caption)
}

yaui.set_xywh = function(id, x, y, w, h) {
   ijs_control_call(ya_set_xywh, id, [x, y, w, h].join(':'))
}
yaui.set_font = function(id, font_name, size, color) {
	ijs_control_call(ya_set_font, id, font_name, size, color.join(':'))
}
yaui.show = function(id) { ijs_control_call(ya_show, id) }
yaui.hide = function(id) { ijs_control_call(ya_hide, id) }
yaui.get_app_size = function(id) { 
	var A = ijs_control_call(ya_get_app_size).split(':')
	for (var i = 0; i < A.length; i++) A[i] = parseInt(A[i])
	A[1] -= A[1] * 0.04 // substract height of iphone status bar which is approx 4%
	return A
}

yaui.make_input = function(parent) {
	return ijs_control_call(ya_make_input, parent)
}
yaui.make_edit = function(parent) {
	return ijs_control_call(ya_make_edit, parent)
}
yaui.get_text = function(id, caption) { return ijs_control_call(ya_text_of_text, id) }
yaui.make_image = function(parent, image_file_name) {
	return ijs_control_call(ya_make_image, parent, image_file_name)
}
yaui.make_hview = function(parent) {
	return ijs_control_call(ya_make_hview, parent)
}
yaui.make_vview = function(parent) {
	return ijs_control_call(ya_make_vview, parent)
}
yaui.set_scroll_area = function(id, n) {
   ijs_control_call(ya_set_scroll_area, id, n)
}
yaui.set_scroll_pos = function(id, n) {
   ijs_control_call(ya_set_scroll_pos, id, n)
}
yaui.get_scroll_pos = function(id) {
   return parseInt(ijs_control_call(ya_get_scroll_pos, id))
}
yaui.set_read_only = function(id) { ijs_control_call(ya_set_read_only, id) }
yaui.set_timeout = function(timer_id, time) { ijs_control_call(ya_set_timeout, timer_id, time) }

if (Function.prototype.bind == null) { 
// spidermonkey supports function.bind from 1.8.5 (and we have 1.8.0)
	Function.prototype.bind = (function (slice) {
		function bind (context) {
			var self = this
			if (1 < arguments.length) {
				var $arguments = slice.call(arguments, 1)
				return function () {
					return self.apply(context,
					arguments.length ? $arguments.concat(slice.call(arguments)) : $arguments)
				}
			}
			return function () {
				return arguments.length ? self.apply(context, arguments) : self.call(context);
			}
		}
		return bind
	}(Array.prototype.slice))
}

log('boot_ios end')
 //                                                  -----------------------------------------------------
 //                                                  --                                                 --
 //                                                  --                                                 --
 //                                                  -- version split                                   --
 //                                                  --                                                 --
 //                                                  --                                                 --
 //                                                  -----------------------------------------------------

if (false) {
	function yaui_alert(text) { ijs_control_call(1, Array.prototype.slice.call(arguments).join(' ')) }
	yaui_set_bgcolor = function(id, r, g, b, a) { ijs_control_call(11, id, r+':'+g+':'+b+':'+a) }
	yaui_hide_keyboard = function() { return ijs_control_call(2) }
}







