log(' * * * bootstrap.js')

yaui = {
	//TODO: implement wrappers for events to report errors 
	on: { timers: [] }
}

if (yaui_platform() == "win") ijs_docdir = function () { return "." }
if (yaui_platform() == "android") ijs_docdir = function () { return "/sdcard/js" }

require_path = [ijs_docdir()]
if (yaui_platform() == "win") require_path.push('y:/ksana/yaui', 'y:/ksana/yaui/js', 'y:/ksana/yaui/win')

var logT = new Date().getTime()

function clear_time(s) { logT = new Date().getTime(); if (s != undefined) log.apply(this, arguments); }

function log() {
	var T0 = new Date().getTime()
	var T = T0 - logT
	var s = '> ';
	if (T > 1) s = '' + T + '> ';
	s = '~ ' // comment to enable timing
	print(s + Array.prototype.slice.call(arguments).join(' ') + '\n')
	logT = T0
}

yaui.find_empty_timer = function() {
	var L = yaui.on.timers, j = -1
	for (var i = 0; i < L.length; i++) if (L[i] == undefined) { j = i; break }
	if (j < 0) j = L.length
	return j
}

yaui.on.timer = function(id) {
	var T = yaui.on.timers
	if (T[id] == undefined) return
//	try {
	T[id].func(T[id].time)
//	} catch(e) { log('timer crash')}
	if (T[id].repeat) {
		yaui.set_timeout(id, T[id].time);
	} else {
		T[id] = undefined
	}
//	log('timer('+id+')!')
}

function setTimeout(f, t) {
	var j = yaui.find_empty_timer()
	yaui.on.timers[j] = { func:f, repeat:false, time: t }
//	log('setTimeout' + j)
	yaui.set_timeout(j, t);
	return j
}

function setInterval(f, t) {
	var id = setTimeout(f, t)
	yaui.on.timers[id].repeat = true
	return id
}

function clearTimeout(id) { yaui.on.timers[id] = undefined }
function clearInterval(id) { clearTimeout(id) }

var log_require = false // setto true to debug require() problems

function load_utf_file(fn) {
	var fs = ijs_fsize(fn)
	var f = ijs_fopen(fn)
	var fp = 0
	var bom = ijs_fread(f, 3, 0)
	if (bom[0] == 239 && bom[1] == 187 && bom[2] == 191) {
		fs -= 3, fp += 3;
		//log('bom removed from ' + fn)
	}
	var R = ijs_fread_utf(f, fs, fp)
	ijs_fclose(f)
	return R
}

function show_source_lines_of_error(E) {
	if (R.source != undefined) {
		var src = R.source.replace(/\r/g,'').split('\n')
		src = src.slice(E.line - 2).slice(0, 3)
		for (var i = 0; i < src.length; i++) src[i] = (i + E.line - 1) + ': '+ src[i]
		src[1] += '\n        <<< ' + E.message
		print('\n--'+src.join('\n--') + '\n---------\n')
		print('\n--'+src.join('\n--') + '\n---------\n')
	} else {
		print('no source code available for this error\n')
	}
}

function print_error(E) {
	print('_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n')
//print('>>>>>>>>' + JSON.stringify(E) + '<<<<<<<<<\n')
//	print('  at ' + E.script +' '+ E.line +':'+ E.pos +'-'+ E.endpos + '\n')
	var A = ''
	if (E.source) {
		var SRC = E.source.replace(/\r/g,'').split('\n')
		A = SRC[E.line-1]
	}
	var t = ''; while (t.length < E.pos) t += ' '
	while (t.length < E.endpos) t += '^'
	//show_source_lines_of_error() // uncomment this and comment next line to get more error lines
	print(A + '\n')
	print(t + ' ')
	print(E.message + '\n')
	if (E.stack != undefined)
	print(E.stack.split('\n').slice(1).join('\n') + '\n') // extra work to remove first line which is a copy of error message
	else log('no stack dump');
	print('^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^\n')
}

function require_once(file_name, R) { // return true if file was found, even if executing it cause error
	if (log_require) log('require_once(' + file_name + ')')
	var fn = file_name
	if (!ijs_fileexists(fn))
		if (fn.indexOf('.js') != (fn.length - 3))
			fn += '.js';
	if (log_require) log('looking for: ' + fn)
	if (ijs_fileexists(fn)) {
		SCRIPT = load_utf_file(fn)
		if (log_require) log('found: ' + fn)
		SCRIPT = '(function(){exports={};' + SCRIPT + ';return exports})()'
		if (yaui_platform() == 'ios') {
			var Ret = ijs_exec_js(SCRIPT, file_name)
			var E = ijs_exec_js_error()
			if (E.length > 0) print(E + '\n')
			else R.engine.result = Ret
		} else { // not ios
			R.engine = ijs_exec_js(SCRIPT, file_name)
			if (R.engine.success) return true
			print_error(R.engine.error)
		}
		return true
	}
    if (log_require) log(file_name + ' not found for require()')
	return false
}

function require_find(file_name, R) { // return true if file was found, even if executing it cause error
	if (log_require) log('require(' + file_name + ')')
	for (var i = 0; i < require_path.length; i++) {
		var ok = require_once(require_path[i] + '/' + file_name, R)
		if (ok) return true
	}
	return false
}

require = function(name) {
	var R = { engine: {} }
	var ok = require_find(name, R)
	if (!ok) throw new Error('require(' + name + ') - file not found')
	//if (!ok) { // uncomment if engine does not support throw
	//	print('require('+name+') - file not found\n')
	//	return undefined
	//}
	return R.engine.result
}

//log('yaui = ' + JSON.stringify(yaui))
//log('your platform is: ' + yaui_platform())
//yaui_platform()

function color_to_i32(c) {
	if (c[3] == undefined) c[3] = 1
	var N = 
		Math.round(c[3] * 255) * 0x1000000 
		+ Math.round(c[2] * 255) * 0x10000
		+ Math.round(c[1] * 255) * 0x100
		+ Math.round(c[0] * 255)
	return N
}

var main = './main'
if (yaui_platform() == 'win') require('boot_win')
if (yaui_platform() == 'android') {
	require('boot_droid')
	yaui.set_bgcolor(yaui.root_handle, 0.5, 0.5, 0.4, 1)
}
if (yaui_platform() == 'ios') require('boot_ios')
require('yaui.js')
require(main)
''
/*try {
	require('nothing')
} catch(e) {
	log('we do not support "nothing" yet.')
} */



