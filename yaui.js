//winapi_console_only()
log(" * * * yaui.js")	
//    *    *    *    *    *    *    *    *    *    *    *    *    *    *    *    *

ya_object = function(H, P) {
	this.handle = H
	this.parent = P
	this.items = []
	this.id = ''
	this.api = ''
	this.text = '...'
	this.pos = {x:0, y:0, w:0, h:0}
	this.visible = false
	this.cls = []
	this.scroll = { area: 0 }
	this.font = { color:[0,0,1], size: undefined, name: undefined }
	if (yaui_platform() == 'android') this.font.name = "arialuni"
	this.on = {button: undefined, text_change: undefined}
}

ya_object.prototype.get_text = function() { return yaui.get_text(this.handle) }
//
ya_object.prototype.set_id = function(id) { this.id = id; return this }
ya_object.prototype.set_cls = function(cls) { this.cls = cls; return this }
ya_object.prototype.add_cls = function(cls) { this.cls = this.cls.concat(cls); return this }
ya_object.prototype.set_visibility = function(visible) { this.visible = visible; return this }
ya_object.prototype.show = function() { this.visible = true; return this }
ya_object.prototype.hide = function() { this.visible = false; return this }
ya_object.prototype.set_text = function(text) { this.text = text; return this }
//ya_object.prototype.set_read_only = function(text) { this.text = text; return this }
ya_object.prototype.set_xy = function(x, y) { 
	if (typeof x !== undefined) this.pos.x = x
	if (typeof y !== undefined) this.pos.y = y; 
	return this
}
ya_object.prototype.inc_xy = function(x, y) { 
	if (typeof x !== undefined) this.pos.x += x
	if (typeof y !== undefined) this.pos.y += y; 
	return this
}
ya_object.prototype.set_wh = function(w, h) {
	if (typeof w !== undefined) this.pos.w = w
	if (typeof h !== undefined) this.pos.h = h; 
	return this
}
ya_object.prototype.inc_wh = function(w, h) {
	if (typeof w !== undefined) this.pos.w += w
	if (typeof h !== undefined) this.pos.h += h; 
	return this
}
ya_object.prototype.apply_pos = function() {
	with(this.pos) yaui.set_xywh(this.handle, x, y, w, h); 
	return this 
}
ya_object.prototype.apply_text = function() {
	yaui.set_text(this.handle, this.text); 
	return this 
}
ya_object.prototype.set_font = function(name, size, color) {
	if (name != undefined) this.font.name = name 
	if (size != undefined) this.font.size = size
	if (color != undefined) this.font.color = color
	return this
}
ya_object.prototype.set_scroll_area = function(size) {
	this.scroll.area = size
	return this
}
ya_object.prototype.bind = function(name, f) {
	this.on[name] = f
	return this
}
ya_object.prototype.apply_scroll_area = function() {
	yaui.set_scroll_area(this.handle, this.scroll.area)
	return this
}
ya_object.prototype.apply_visibility = function() {
	if (this.visible) yaui.show(this.handle) ;else yaui.hide(this.handle); 
	return this 
}
ya_object.prototype.apply_font = function() {
	if (this.font.name == undefined) return
	if (this.font.color.length == 3) this.font.color.push(1)
	yaui.set_font(this.handle, this.font.name, this.font.size, this.font.color); 
	return this 
}
ya_object.prototype.apply = function() {
	this.apply_pos()
	if (0 <= ['button', 'label', 'input', 'edit'].indexOf(this.api.valueOf())) {
		this.apply_font()
		this.apply_text()
	}
	if (0 <= ['hview', 'vview'].indexOf(this.api.valueOf())) {
		this.apply_scroll_area()
		//this.set_scroll_pos()
	}
	this.apply_visibility()
	return this
}

yaui.main_object = new ya_object(yaui.root_handle, undefined)
yaui.main_object.api = 'view'
yaui.main_object.id = 'main_view'
yaui.objects = [ yaui.main_object ]

yaui.find_object = function(handle) {
	var O = yaui.objects
	for (var i = 0; i < O.length; i++) {
		if (O[i].handle == handle) return O[i]
	}
	return undefined
}

yaui.create = function(what, parent) {
	if (parent == undefined) parent = yaui.main_object
	var O
	if (what == 'button') {
		var H = yaui.make_button(parent.handle)
		O = new ya_object(H, parent)
	}
	else if (what == 'label') {
		var H = yaui.make_label(parent.handle)
		O = new ya_object(H, parent)
	}
	else if (what == 'input') {
		var H = yaui.make_input(parent.handle)
		O = new ya_object(H, parent)
	}
	else if (what == 'edit') {
		var H = yaui.make_edit(parent.handle)
		O = new ya_object(H, parent)
	}
	else if (what == 'hview') {
		var H = yaui.make_hview(parent.handle)
		O = new ya_object(H, parent)
	} 
	else if (what == 'vview') {
		var H = yaui.make_vview(parent.handle)
		O = new ya_object(H, parent)
	} else {
		throw ("unknown yaui.create('"+ what +"')")
	}
	O.api = what
	yaui.objects.push(O)
	parent.items.push(O)
	return O
}

select = function(what) {
	var R = [], O = yaui.objects
	function cls_in_cls(A, B) {
		if (!A || !B) return false
		return A.some(function(n){ return B.indexOf(n.valueOf()) >= 0 })
	}
	for (var i = 0; i < O.length; i++) {
		var yes = false
		var id = O[i].id.valueOf()
		if (O[i].id.valueOf() == what.id) yes = true
		if (cls_in_cls(what.cls, O[i].cls)) yes = true
		if (yes) R.push(O[i])
	}
	R.print = function() {
		for (var i = 0; i < R.length; i++) {
			Z = [R[i].id, R[i].api, R[i].cls, R[i].pos, R[i].font]
			log(JSON.stringify(Z))
		}
		return this
	}
	R.get_text = function() { if (R.length > 0) return R[0].get_text() }
	R.set_id = function(id) { R.some(function(a){a.set_id(id)});return R }
	R.set_cls = function(c) { R.some(function(a){a.set_cls(c)});return R }
	R.add_cls = function(c) { R.some(function(a){a.add_cls(c)});return R }
	R.set_text = function(t) { R.some(function(a){a.set_text(t)});return R }
	R.set_xy = function(x, y) { R.some(function(a){a.set_xy(x, y)});return R }
	R.set_wh = function(w, h) { R.some(function(a){a.set_wh(w, h)});return R }
	R.inc_xy = function(x, y) { R.some(function(a){a.inc_xy(x, y)});return R }
	R.inc_wh = function(w, h) { R.some(function(a){a.inc_wh(w, h)});return R }
	R.apply = function() { R.some(function(a){a.apply()});return R }
	R.apply_pos = function() { R.some(function(a){a.apply_pos()});return R }
	R.apply_text = function() { R.some(function(a){a.apply_text()});return R }
	R.apply_visibility = function() { R.some(function(a){a.apply_visibility()});return R }
	R.apply_font = function() { R.some(function(a){a.apply_font()});return R }
	R.show = function() { R.some(function(a){a.show()});return R }
	R.hide = function() { R.some(function(a){a.hide()});return R }
	R.set_visibility = function(visible) { R.some(function(a){a.set_visibility(visible)});return R }
	R.set_font=function(name,size,color){R.some(function(a){a.set_font(name,size,color)});return R }
	R.set_scroll_area = function(size) { R.some(function(a){a.set_scroll_area(size)});return R }
	R.apply_scroll_area = function() { R.some(function(a){a.apply_scroll_area()});return R }
	R.bind = function(name, f) { R.some(function(a){a.bind(name, f)});return R }
	R.each = function(f) { R.some(function(a){f.apply(R,[a])}); return R }
	return R
}

yaui.on.button = function(handle) {
	yaui.dispatch('button', handle)
}

yaui.on.key_down = function(handle) { 	// windows only
	yaui.dispatch('key_down', handle)
}

yaui.on.text_change = function(handle) {
	yaui.dispatch('text_change', handle)
}

yaui.dispatch = function(func_name, handle) {
	var O = yaui.objects
	for (var i = 0; i < O.length; i++) {
		if (O[i].handle == handle) {
			if (O[i].on[func_name] != undefined) O[i].on[func_name](O[i])
			return
		}
	}
}

// Pager implementation on top of HVIEW
yaui.on.subview_scroll_begin = function(sender) {
//	log('subview_scroll_begin')
	var o = yaui.find_object(sender)
	o.start = undefined
}

yaui.on.subview_scroll_end = function(sender) {
	var o = yaui.find_object(sender)
	if (o.snap == undefined) return
	o.start = yaui.get_scroll_pos(sender)
	var min_d = -1
	for (var i = 0; i < o.snap.length; i++) {
		var d = Math.abs(o.snap[i] - o.start)
		if (min_d < 0 || d < min_d) o.dest = o.snap[i], min_d = d
	}
	o.speed = o.start > o.dest ? -1 : 1
	o.snap_pos = o.start
//	log('subview_scroll_end: ' + o.start + ' ' + pager.start + ' ' + o.dest)
}

make_pager = function(p) {
	if (p.snap == undefined) p.snap = [0]
	yaui.set_scroll_pos(p.handle, p.snap[0])
	setInterval(function() {
		if (p.start != undefined) {
			p.snap_pos += p.speed
			var done = false
			if (p.speed < 0) { 
				if (p.snap_pos < p.dest) done = true
			} else { 
				if (p.snap_pos > p.dest) done = true
			}
			if (done) p.snap_pos = p.dest, p.start = undefined
			p.speed *= 2
			yaui.set_scroll_pos(p.handle, p.snap_pos)
		}
	}, 20)
}

