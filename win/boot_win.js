var winapi_objects = []

platform = { os: 'windows' }
yaui.root_handle = parseInt(winapi_get_main_view(), 10)

function yaui_alert(text) {
	winapi_alert(Array.prototype.slice.call(arguments).join(' '))
}
yaui.make_button = function(parent) {
	return winapi_make_button(parent)
}
yaui.set_text = function(b, title) {
	winapi_set_text(b, title)
}
yaui.set_xywh = function (id, x, y, w, h) {
	winapi_set_xywh(id, x, y, w, h)
}
yaui.show = function(id) { winapi_show(id) }
yaui.hide = function(id) { winapi_hide(id) }
yaui.set_font = function (id, font_name, size, color) {
	color[3] = 0
	color = color_to_i32(color)
	winapi_set_font(id, font_name, size, color)
}
yaui.get_app_size = function(id) { 
	return winapi_get_app_size()
}
yaui.make_label = function(parent) {
	return winapi_make_label(parent)
}
yaui.make_input = function(parent) {
	return winapi_make_input(parent)
}
yaui.make_edit = function(parent) {
	return winapi_make_edit(parent)
}
yaui.get_text = function(id) { return winapi_get_text(id) }
yaui.make_image = function(parent, file_name, w, h) { 
	if (w == undefined) w = -1, h = -1
	return winapi_make_image(parent, file_name, w, h) 
}
yaui.make_hview = function(parent) { return winapi_make_hview(parent) }
yaui.make_vview = function(parent) { return winapi_make_vview(parent) }
yaui.set_scroll_area = function(id, width) { return winapi_set_scroll_area(id, width) }
yaui.set_scroll_pos = function(id, pos) { return winapi_set_scroll_pos(id, pos) }
yaui.get_scroll_pos = function(id) { return winapi_get_scroll_pos(id) }
yaui.set_read_only = function(id) { winapi_set_read_only(id) }
yaui.set_timeout = function(timer_id, t) { winapi_set_timer(timer_id, t) }
 //                                                  -----------------------------------------------------
 //                                                  --                                                 --
 //                                                  --                                                 --
 //                                                  -- version split                                   --
 //                                                  --                                                 --
 //                                                  --                                                 --
 //                                                  -----------------------------------------------------

function yaui_set_bgcolor (id, r, g, b, a) {
	//not implemented due to complexity of setting bg color to existing controls in winapi
}
function yaui_set_focus(id) { winapi_set_focus(id) }
function yaui_hide_keyboard(){}
function yaui_get_wh(id) {  return [parseInt(winapi_get_w(id),10), parseInt(winapi_get_h(id), 10)] } 
function yaui_get_client_area(id) { return winapi_get_client_area(id) }

// ~   ~   ~   ~  not crossplatform WINDOWS ONLY API  ~   ~   ~   ~   ~   ~   ~   ~   ~   ~   ~   ~   ~

function parse_args(s) { // winapi_get_command_line returns string, we need to parse to array
	var A = ['']
	var quote = false
	for (var i = 0; i < s.length; i++) {
		var C = s.charAt(i)
		if (C == '"') { quote = !quote; continue }
		if (C == ' ' && !quote) A.push('')
		else A[A.length - 1] += C
	}
	return A
}

// ------------------------------ END OF BOOTSTRAP -----------------------------
	var cmd = parse_args(winapi_get_command_line())
	if (cmd.length > 1 && cmd[1].length > 0) main = cmd[1]


//require('lib')

//winapi_alloc_console()
