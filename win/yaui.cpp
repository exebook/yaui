#include <v8.h>
#define UNICODE
#include "win.h"
#include "butlab.h"
//#include "novavar.h"
#include "subview.h"
#include "v8util.h"
extern "C" {
	void gdiplus_startup();
	void* load_image(wchar_t*, int &, int &);
	void draw_image_on_dc(HDC, void*, int, int);
}
void load_image(dib_surface *v0, wstr name, int W, int H) {
	dib_surface &v = *v0;
	gdiplus_startup();
	int w, h;
	void* i = load_image(*name, w, h);
	if (W < 0) W = w, H = h;
	v.resize(W, H);
	v.clear(0xffffff);
	draw_image_on_dc(v.dc, i, W, H);
	//return v;
}

bool is_true(str s) {
	return (s == "true" || s == "yes" || s == "1");
}

struct inherit(win2, win) {
	on_paint {
		//v8_callback(this, "onpaint");
		if (!data["onpaint"] != 0) { 
			if (is_true(data["old_paint"])) inherited::paint();
			str s;
			s / data["onpaint"] / "("/ (int)this / ")";
			s = v8_exe(s, (str)"on_paint_event:" + data["onpaint"]);
			if (!s > 0 && s != "undefined") printf("%s\n", *s);
			// TODO: call some JavaScript to handle error if handler returned error
		} else inherited::paint();
	}
	on_mouse {
	//printf("button=%i, down=%i\n", (int)button, (int)down);
		//if (button == 0 && down) 
		if (!data["onclick"] != 0) { 
			str s;
			s / data["onclick"] / "("/(int)this/"," / x / "," / y / ","/(int)button/","/(int)down/")";
			s = v8_exe(s, (str)"on_click_event:" + data["onclick"]);
		}
	}
};
struct inherit(Yaui, win2) {
	on_created {
		SetWindowLong(handle, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN);
	}
	on_command {	}
	str cmd(str s) {
//	printf("------- %s\n", *s);
		//cmd_call C(s);
		str name = bite(s, ' ');
		str sender = s; 
		if (name == "subview_scroll_end" || name == "subview_scroll_begin") {
			str x = (str)"if (yaui.on."+name+" != undefined) yaui.on."+name+"(" + sender + ")";
			x = v8_exe(x, x);
			if (v8_exe_error) printf("%s\n", *x);
			return "";
		}
		str x = (str)"yaui.on.button(" + sender + ")";
		x = v8_exe(x, x);
		if (v8_exe_error) printf("%s\n", *x);
		return "";
	}
	on_timer {
		KillTimer(handle, id);
		str s = (str)"yaui.on.timer(" + id + ")";
		s = v8_exe(s, s);
		if (v8_exe_error) printf("%s\n", *s);
	}
} APPL;

extern "C" void* __stdcall CreateFontA(INT7, INT6, PTR);
struct edit : win {
	str callback;
	void create(win* parent, bool multiline) {
		winapi_create(parent, "EDIT", WS_BORDER | (multiline?ES_MULTILINE|WS_VSCROLL:0), WS_EX_CLIENTEDGE);
		both_handlers();
		init_sysfont(true);
	  }
	void set_text(wstr s) {
		s.replace("\r", "");
		s.replace("\n", "\r\n");
		caption(s);
	}
	on_key {
		if (down) {
			str s = "yaui.on.key_down(" ;
			s / (str)(int)this / ", " / (str)key / ")";
			s = v8_exe(s, s);
			if (v8_exe_error) printf("%s\n", *s);
		}
	}
	on_char {
		str s = "yaui.on.text_change(";
		s / (str)(int)this / ", " / ch / ")";
		s = v8_exe(s, s);
		if (v8_exe_error) printf("%s\n", *s);
	}
};
struct image : win {
	dib_surface V;
	void load(wstr name, int w, int h) { load_image(&V, name, w, h); }
	on_paint { S->blit(V, 0, 0); }
};

wstrings a2s(const v8::Arguments& args) {
	wstrings R;
	for (int i = 0; i < args.Length(); i++) {
		v8::HandleScope handle_scope;
		v8::String::Value stri(args[i]);
		wstr w =(wchar_t*)  L"<string conversion failed>";
		if (*stri) w = (wchar_t*)(*stri);
		R << w;
	}
	return R;
}
#define function(name) v8::Handle<v8::Value> name(const v8::Arguments& a)
function(yaui_platform) {
	return String::New("win");
}

wstr _join(wstrings &L, wstr D) {
	wstr R;
	each (i, L) { if (i > 0) R / D; R / L[i]; }
	return R;
}

function(print) {
	wstrings l = a2s(a);
	str s = _join(l, " ");
	printf("%s", *s);
	fflush(stdout);
	return v8::Undefined();
}

function(winapi_get_main_view) {
	static str ptr = (int)(void*)&APPL;
	return String::New(*ptr);
}

function(winapi_make_button) {
	wstrings L = a2s(a);
	button *B = 0;
	win * v = (win*) ~L[0];
	B = new button;
	B->create(v);	
	B->data["type"] = "button";
	B->owner = v;	
	B->name = (str)(int)B;	
	B->cmd_msg = "button";//L[2];
	return Number::New((int)B);
}

function(winapi_make_label) {
	wstrings L = a2s(a);
	win * v = (win*) ~--L;
	Label *B = new Label;
	B->data["type"] = "label";
	B->create(*v, "_undefined");//, --L);	
	B->owner = v;	
	return Number::New((int)B);
}

function(winapi_set_text) {
	wstrings L = a2s(a);
	win * w = (win*) ~--L;
	if (w->data["type"] == "button") {
		button * B = (button*) w;
		if (B) B->title = L[0], B->paint();
	} else if (w->data["type"] == "label") {
		Label * B = (Label*) w;
		if (B) B->caption = L[0], B->paint();
	} else if (w->data["type"] == "input") {
		edit * E = (edit*) w;
		E->set_text(L[0]);
	} else 
		if (w) w->caption(L[0]), w->paint();
	return v8::Undefined();
}

function(winapi_get_text) {
	wstrings L = a2s(a);
	win * w = (win*) ~--L;
	wstr s;
	if (w) s = w->caption();
	return String::New((uint16_t*)*s);
}

function(winapi_set_font) {
	wstrings L = a2s(a);
	win * w = (win*) ~--L;
	int C = ~L[2];
	w->S->apply_font(L[0], ~L[1], C);
	if (w->data["type"] == "button") {
		button * B = (button*) w;
		B->colors.text[0] = C;
		B->colors.text[1] = C;
		B->colors.text[2] = C;
		B->colors.text[3] = C;
	}
	else if (w->data["type"] == "input" || w->data["type"] == "edit") {
		HFONT hFont = CreateFontA (18,0,0,0,0, false, false, false, 0,4,0,0,0, *L[0].compat());
		SendMessage(w->handle, WM_SETFONT, (int)hFont, true);
		SetTextColor(w->handle, C);
	}
	return v8::Undefined();
}

function(winapi_get_app_size) {
	wstrings L = a2s(a);
	HandleScope handle_scope;
	Handle<Array> A = Array::New(2);
	A->Set(0, Integer::New(APPL.w()));
	A->Set(1, Integer::New(APPL.h()));
	return handle_scope.Close(A);
}

Handle<Value> create_edit_input(const Arguments &a, bool multi_line) {
	wstrings L = a2s(a);
	edit *E = 0;
	win * v = (win*) ~L[0];
	E = new edit;
	E->create(v, multi_line);
	E->data["type"] = "input";
	E->owner = v;	
	E->name = (str)(int)E;	
	//E->callback = L[2];
	return Number::New((int)E);
}

function(winapi_make_input) {
	return create_edit_input(a, false);
}

function(winapi_make_edit) {
	return create_edit_input(a, true);
}

function(winapi_make_image) {
	wstrings L = a2s(a);
	image *I = 0;
	win * v = (win*) ~L[0];
	I = new image;
	I->data["type"] = "image";
	I->create(v);
	I->owner = v;	
	I->name = (str)(int)I;
//	I->move(~L[2], ~L[3]);
	//I->size(~I->V, !I->V);	
//	I->size(~L[4], ~L[5]);	
	I->load(L[1], ~L[2], ~L[3]);
//	I->show();	// remove?
	return Number::New((int)I);
}

function(winapi_show) {
	wstrings L = a2s(a);
	win * w = (win*) ~--L;
	if (w->data["type"] == "hview") w = ((SubBar*)w)->parent;
	w->show();
	return v8::Undefined();
}

function(winapi_hide) {
	wstrings L = a2s(a);
	win * w = (win*) ~--L;
	if (w->data["type"] == "hview") w = ((SubBar*)w)->parent;
	w->hide();
	return v8::Undefined();
}

Sub * __make_scroll_view(const Arguments &a) {
	wstrings L = a2s(a);
	Sub *S = 0;
	win * v = (win*) ~L[0];
	S = new Sub;
	S->b.data["type"] = "hview";
	S->create(v);
//	S->show();	
	S->owner = &APPL;
	return S;
}

function(winapi_make_hview) {
	Sub *S = __make_scroll_view(a);
	return Number::New((int)&S->b);
}

function(winapi_make_vview) {
	Sub *S = __make_scroll_view(a);
	S->vert = true;
	return Number::New((int)&S->b);
}

bool __scroll_area(const Arguments &a, Sub *&b, wstrings &L) {
	L = a2s(a);
	SubBar * B = (SubBar*) ~--L;
	if (((int*)B)[1] != 0xDA0B1EC7 || ((int*)B->parent)[1] != 0xDA0B1EC7) {
		printf("Invalid pointer(s)\n");
		return false;
	}
	b = ((Sub*)B->parent);
	return true;
}

#define __scroll Sub *b; wstrings L; if (!__scroll_area(a, b, L)) return Undefined();

function(winapi_set_scroll_area) {
	__scroll
	int amount = ~L[0];
	b->set_scroll_area(amount);
//	b->b.paint();
//	b->paint();
	return v8::Undefined();
}

function(winapi_set_scroll_pos) {
	__scroll
	int x = ~L[0];
	if (x < 0) x = 0;
	b->delta = x;
//	b->sc.pos = x; 
//	b->sc.paint();
	b->scroll_to(x);
	return v8::Undefined();
}

function(winapi_get_scroll_pos) {
	__scroll
	return Number::New(b->delta);
}

//int get_scroll_pos() { 	return sc.pos;}
	
function(winapi_set_xywh) {
	wstrings L = a2s(a);
	win * w = (win*) ~--L;
	if (w->data["type"] == "hview") {
		w->size(~L[2], ~L[3]);
		w = ((SubBar*)w)->parent;
	}
	w->move(~L[0], ~L[1]);
	w->size(~L[2], ~L[3]);
	return v8::Undefined();
}

// -----------------------------------------------------
// --
// --
// -- version split
// --
// --
// -----------------------------------------------------

//  - -  - -  - - WINAPI ONLY - -  - -  - -  - -  - -
function(winapi_get_xywh) {
	wstrings L = a2s(a);
	win * w = (win*) ~--L;
	HandleScope handle_scope;
	Handle<Array> A = Array::New(4);
	A->Set(0, Integer::New(w->LEFT()));
	A->Set(1, Integer::New(w->TOP()));
	A->Set(2, Integer::New(w->W()));
	A->Set(3, Integer::New(w->H()));
	return handle_scope.Close(A);
}

function(winapi_create_window) {
	wstrings L = a2s(a);
	win *B = 0;
	if (!L >= 3) {
		B = new win2;
		B->create();
		B->data["type"] = "win";
		//B->style(WS_OVERLAPPEDWINDOW);
		B->caption(L[0]);	
//		B->S->apply_font("HanaMinB", 22);
		B->size(~L[1], ~L[2]);	
		B->show();
	}
	return Number::New((int)B);
}

// - -  - -  - -  - -  - -  - -  - -  - -  - -  - -

function(winapi_alert) {
	wstrings L = a2s(a);
	MessageBoxW(0, *_join(L, " "), L"Message", MB_OK);
	return v8::Undefined();
}

function(winapi_get_client_area) {
	wstrings L = a2s(a);
	Sub * S = (Sub*) ~--L;
	HandleScope handle_scope;
	Handle<Array> A = Array::New(2);
	A->Set(0, Integer::New(S->W()));
	A->Set(1, Integer::New(S->H()));
	return handle_scope.Close(A);
}
function(winapi_set_read_only) {
	wstrings L = a2s(a);
	win * w = (win*) ~--L;
	SendMessage(w->handle, 0x00CF, 1, 0);
	return v8::Undefined();
}
function(winapi_set_bg_color) {
	return v8::Undefined();
}
function(winapi_set_timer) {
	wstrings L = a2s(a);
	int id = ~L[0], T = ~L[1];
	SetTimer(APPL.handle, id, T, 0);
/*	APPL.timer_callbacks << --L;
	int id = 0, T = ~--L;
	ints &I = APPL.timers; each (i, I) if (I[i] >= id) id = I[i] + 1; L << id;
	APPL.timers << id;
	SetTimer(APPL.handle, id, T, 0);*/
	return Number::New(id);
}
function(winapi_clear_view) {
	wstrings L = a2s(a);
	win * w = (win*) ~--L;
	(*(win*)w).paint();
	return v8::Undefined();
}

#include "v8file.h"

extern "C" {
	int __stdcall AllocConsole();
	int __stdcall FreeConsole();
	bool __stdcall AttachConsole(int);
}
function(winapi_free_console) {
	FreeConsole();
	return v8::Undefined();
}

function(winapi_alloc_console) {
	AllocConsole();
	//AttachConsole(-1);
	return v8::Undefined();
}

function(winapi_get_command_line) {
	wstr R = (wchar_t*)GetCommandLineW();
	return String::New((uint16_t*)*R, !R);
}

bool console_only = false;

function(winapi_console_only) {
	console_only = true;
	return v8::Undefined();
}

function(winapi_set_onpaint) {
	wstrings L = a2s(a);
	win * w = (win*) ~--L;
	w->data["onpaint"] = --L;
	if (!L > 0) w->data["old_paint"] = --L;
	return v8::Undefined();
}

function(winapi_set_onclick) {
	wstrings L = a2s(a);
	win * w = (win*) ~--L;
	w->data["onclick"] = --L;
	return v8::Undefined();
}

int blend_pix(u32 a, u32 b) {
	if (a == b) return a;
	return ((a & 0xFEFEFEFE) >> 1) + ((b & 0xFEFEFEFE) >> 1);
}

void blend_dib_tv_effect(dib &V) {
	static dib Z; 
	if (~Z != ~V || !Z != !V) Z.resize(~V, !V);
	move(V.p->bits, Z.p->bits, ~V * !V * 4);
	u32 a, b, c, d;
	for (int Y = 1; Y < !V - 1; Y++)
	for (int X = 1; X < ~V - 1; X++) {
		Z.seek(X, Y); V.seek(X, Y);
		a = blend_pix(*((u32*)Z.data - 1), *((u32*)Z.data + 1));
		b = blend_pix(*((u32*)Z.data - ~V), *((u32*)Z.data + ~V));
		*(u32*)V.data = blend_pix(a, b);
	}
}

function(winapi_blit) {
	v8::HandleScope handle_scope;
	win *W = (win*)(int)Handle<Number>::Cast(a[0])->Value();
	int x = (int)Handle<Number>::Cast(a[1])->Value();
	int y = (int)Handle<Number>::Cast(a[2])->Value();
	int w = (int)Handle<Number>::Cast(a[3])->Value();
	int h = (int)Handle<Number>::Cast(a[4])->Value();
	Handle<Array> A = Handle<Array>::Cast(a[5]);
	dib V; V.resize(w, h);
	int n = 0;
	for (int Y = 0; Y < h; Y++)
	for (int X = 0; X < w; X++) {
		int C = (int)Handle<Number>::Cast(A->Get(n++))->Value();
		V.pixel(X, Y) = C;
	}
	blend_dib_tv_effect(V);
	W->S->blit(V, x, y);

	//printf("main view: %i %i\n", (int)&APPL, (int) Ww->Value());
	//win * w = (win*)(int) W->Value();
	//W->S->crect(0, 0, 200, 200, 0xff);
	return v8::Undefined();
}

function(winapi_set_focus) {
	wstrings L = a2s(a);
	win * w = (win*) ~--L;
	w->set_focus();
	return v8::Undefined();
}

function (winapi_scroll_to_bottom) {
	wstrings L = a2s(a);
	win * w = (win*) ~--L;
	SendMessage(w->handle, LOWORD(WM_VSCROLL), SB_BOTTOM, 0);
	return v8::Undefined();
}

function (example) {
	v8::HandleScope handle_scope;
	Handle<Object> Result = Object::New();
	Result->Set(String::New("name"), String::New("Stackoverflow"));
	Result->Set(String::New("url"), String::New("http://stackoverflow.com"));
	Result->Set(String::New("javascript_tagged"), Number::New(317566));
	return handle_scope.Close(Result);
}

Handle<Value> native_example(const Arguments& a) {
	return String::New("it works");
}

/*	Handle<Function> F = Handle<Function>::Cast(context->Global()->Get(String::New("Array")));
	Handle<Object> P = Handle<Object>::Cast (F->GetPrototype());
	P = Handle<Object>::Cast(P->GetPrototype());
	P->Set(String::New("example"), FunctionTemplate::New(native_example)->GetFunction(), None); */
	
	
//	str SCRIPT = *load(exe_dir("bootstrap.js"));
//	wstr r = v8_exe((str)"(function(){exports={};" + SCRIPT + ";return exports})()", exe_dir("bootstrap.js"));

Persistent<Context> context;

#undef function
int main(int argc, char* argv[]) {
//WINMAIN {
	APPL.create();
	APPL.size(320+2, 480+2);
	APPL.caption("YAUI");
	HandleScope handle_scope;
	Handle<ObjectTemplate> G = ObjectTemplate::New();
	#define function(name) G->Set(v8::String::New(#name), v8::FunctionTemplate::New(name));
	#include "yaui_functions.h"
	#undef function
	context = Context::New(0, G);
	Context::Scope context_scope(context);
	str bootstrap = "bootstrap.js";
	if (!fileexists(*bootstrap)) bootstrap = exe_dir("../bootstrap.js");
	wstr r;
try {
	r = v8_exe(bootstrap, bootstrap, true);
	printf("%s\n\n", *r.compat());
} catch (int e) {
	printf("Yaui.cpp:%i unhandled exception, terminating\n", __LINE__);
}
	if (console_only) return 0;
	APPL.show();
	APPL.run();
}



