// ANDROID YAUI BOOTSTRAP V1.0
print('boot_droid begin\n') 
platform = { os: 'android' }

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

yaui.root_handle = yadroid(ya_main_handle)

yaui.set_xywh = function(handle, x, y, w, h) { 
	yadroid(ya_set_xywh, handle, x, y, w, h) 
}
yaui.make_button = function(parent) {
	return yadroid(ya_make_button, parent); 
}
yaui.set_text = function(handle, caption) {yadroid(ya_set_text, handle, caption)}
yaui.set_font = function (handle, font_name, size, c) {
	var color = color_to_i32([c[2], c[1], c[0], c[3]]).toString(16)
	yadroid(ya_set_font, handle, '/sdcard/' + font_name + '.ttf', size, color)
}
yaui.show = function(handle) { yadroid(ya_show, handle) }
yaui.hide = function(handle) { yadroid(ya_hide, handle) }
yaui.get_app_size = function(handle) { 
	var A = yadroid(ya_get_app_size).split(':')
	for (var i = 0; i < A.length; i++) A[i] = parseInt(A[i])
	A[1] -= A[1] * 0.045 // substract android main status bar which is approx 5% of screen height
	return A
}
yaui.make_label = function(parent) {
	return yadroid(ya_make_label, parent)
}
yaui.make_input = function(parent) {
	var R = yadroid(ya_make_edit, parent)
	yadroid(ya_input_line, R) // make single line
	return R
}
yaui.make_edit = function(parent) {
	return yadroid(ya_make_edit, parent)
}
yaui.get_text = function(handle) {return yadroid(ya_text_of_text, handle)}
yaui.make_image = function(parent, file_name, w, h) {
	var R = yadroid(ya_make_image, parent, '/sdcard/' + file_name, w, h)
	return R
}
yaui.make_hview = function(parent) {
	return yadroid(ya_make_hview, parent).split(':')
}
yaui.make_vview = function(parent) {
	return yadroid(ya_make_vview, parent).split(':')
}
yaui.set_scroll_area = function(handle, w) { 
	yadroid(ya_set_scroll_area, handle)
}
yaui.set_scroll_pos = function(handle, x) { 
	yadroid(ya_set_scroll_pos, handle, x)
}
yaui.get_scroll_pos = function(handle) { 
	return parseInt(yadroid(ya_get_scroll_pos, handle))
}
yaui.set_read_only = function(handle){ yadroid(ya_set_read_only, handle) }
yaui.set_timeout = function(timer_id, time) { yadroid(ya_set_timeout, timer_id, time) }

yaui.on.activity = function (event) {
	if (event == 'resume'); //yaui_app_resume()
}


// -----------------------------------------------------
// --
// --
// -- version split
// --
// --
// -----------------------------------------------------

yaui.set_bgcolor = function(handle, r, g, b, a) {
	var N = 
		Math.round(a * 255) * 0x1000000 
		+ Math.round(r * 255) * 0x10000
		+ Math.round(g * 255) * 0x100
		+ Math.round(b * 255)
	yadroid(ya_set_bgcolor, handle, N.toString(16));
}

if (false) {
	function yaui_app_resume () {}
	function yaui_alert(text) {
		yadroid(ya_alert, Array.prototype.slice.call(arguments).join(' '))
	}
	function yaui_hide_keyboard(){}
}
print('boot_droid end\n')

