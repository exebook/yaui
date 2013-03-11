#define UNIX
#include "stone.h"
#include "monkey/jsapi.h"

//extern "C" void printf(const char*, ...);

JSRuntime *runtime=NULL;
JSContext *context=NULL;
JSObject  *global=NULL;

str DOCDIR = "...";
extern "C" {
   char * control_ui(int, char**);
  	void set_DOCDIR(const char *c) { DOCDIR = c; }
}

str monkey_last_error = "";

void reportError(JSContext *cx, const char *message, JSErrorReport *report) {
	//TODO: report as object back to javascript caller
   str msg = message;
   if (msg.pos("TypeError: bad surrogate char") >= 0) return;
  	str s = "";//"Monkey error report: ";
	str dir = (report->filename ? report->filename : "<no filename="">");
	dir.replace(DOCDIR, "~");
  	s / dir;
  	s / ":" / report->lineno;
  	s / "\n" / message;
	monkey_last_error = s;
//  	char *z[1] = {*s}; control_ui(1, z); // alternatively call alert()
}

str arg(JSContext *cx, jsval vp) {
   JSString *j = JS_ValueToString(cx, vp);
   if (j == 0) throw;
   char *c = JS_EncodeString(cx, j);
   if (c  == 0) throw;
   str s = c;
   JS_free(cx, c);
   if (!s == 0) throw;
   return s;
}
#define ARG(n) arg(cx, vp[n + 2])

JSBool out_double(JSContext *cx, jsval *vp, double d) {
    jsval v;
    JS_NewNumberValue(cx, d, &v);
    JS_SET_RVAL(cx, vp, v);
    return JS_TRUE;
}  

JSBool out_string(JSContext *cx, jsval *vp, str R) {
   JSString *j = JS_NewString(cx, *R, !R);
//   JSString *j = JS_NewUCString(cx, (jschar*)*R, !R);//wstr
   R.p->count++;
   jsval v = STRING_TO_JSVAL(j);
   JS_SET_RVAL(cx, vp, v);
   return JS_TRUE;
}

#define OUT_DOUBLE(d) out_double(cx, vp, d);
#define OUT_STRING(s) out_string(cx, vp, s);

static JSBool ijs_docdir(JSContext *cx, uintN argc, jsval *vp) {
   return OUT_STRING(DOCDIR);
}

static JSBool ijs_exit(JSContext *cx, uintN argc, jsval *vp) {
   return JS_FALSE;
}

jsval exec_js(str script, str report_name) {
	jsval R = JSVAL_FALSE;
	monkey_last_error = "";
	bool OK = JS_EvaluateScript(context, global,*script, !script, *report_name, 1, &R);
	JS_ReportPendingException(context); // TODO: think of various ways to report exception
	//if (!OK) return JSVAL_FALSE;
	//JS_GetProperty(cx, global, "bar", &rval);
	return R;
}

str report_file_name;

static JSBool ijs_exec_js(JSContext *cx, uintN argc, jsval *vp) {
	JS_SET_RVAL(cx, vp, exec_js(ARG(0), ARG(1)));
	return JS_TRUE;
}

static JSBool ijs_exec_js_error(JSContext *cx, uintN argc, jsval *vp) {
	return OUT_STRING(monkey_last_error);
}

static JSBool ijs_load(JSContext *cx, uintN argc, jsval *vp) {
   str fn = ARG(0);
   str R = load(fn);
   return OUT_STRING(R);
}

static JSBool ijs_save(JSContext *cx, uintN argc, jsval *vp) {
   str fn = ARG(0), data = ARG(1);
   data.save(fn);
   return JS_TRUE;
}

static JSBool ijs_fileexists(JSContext *cx, uintN argc, jsval *vp) {
   str fn = ARG(0);
   jsdouble R = fileexists(*fn);
   return OUT_DOUBLE(R);
}

static JSBool ijs_fopen(JSContext *cx, uintN argc, jsval *vp) {
    str P1 = ARG(0);
    int R = (int)fopen(*P1, "rb");
    return OUT_DOUBLE(R);
}

static JSBool ijs_fclose(JSContext *cx, uintN argc, jsval *vp) {
    int F = ~ARG(0);
			 int OK = fclose((FILE*)F);
    if (OK == 0) return JS_TRUE;
    else return JS_FALSE;
}

static JSBool ijs_fsize(JSContext *cx, uintN argc, jsval *vp) {
    str P1 = ARG(0);
    jsdouble R = filesize(*P1);
    return OUT_DOUBLE(R);
}

static JSBool ijs_test(JSContext *cx, uintN argc, jsval *vp) {
	  JSObject *A;
	  JS_ValueToObject(cx, vp[2], &A);
	  jsuint N;
 	 JS_GetArrayLength(cx, A, &N);
   jsval v;
		 JS_GetElement(cx, A, 0, &v);
   v = (333 << 1) | 1;
 	 JS_SetElement(cx, A, 0, &v);
   return JS_TRUE;
}

str read_data(JSContext *cx, uintN argc, jsval *vp, int unit_size) {
    int F = ~ARG(0);
    long size = ~ARG(1) * unit_size;
    long pos = ~ARG(2);
    str R; R(size);
    fseek((FILE*)F, pos, SEEK_SET);
    fread((void*)*R, (size_t)1, (size_t)!R, (FILE*)F);
    return R;
}

static JSBool ijs_fread(JSContext *cx, uintN argc, jsval *vp) {
    str R = read_data(cx, argc, vp, 1);
    jsval *V = new jsval[!R];
    JS_BeginRequest(cx);
    for (int i = 0; i < !R; i++) 
       JS_NewDoubleValue(cx, (double)(int)(byte)R[i], &V[i]);
    JSObject * A = JS_NewArrayObject(cx, !R, V);
    jsval RVAL = OBJECT_TO_JSVAL(A);
    JS_SET_RVAL(cx, vp, RVAL);
    JS_EndRequest(cx);
    return JS_TRUE;
}

static JSBool ijs_fread32(JSContext *cx, uintN argc, jsval *vp) {
	str R = read_data(cx, argc, vp, 4);
	JS_BeginRequest(cx);
	byte *Q = (byte*)*R;
	int N = !R / 4;
	jsval *V = new jsval[N];
	for (int i = 0; i < N; i++) {
		byte *A = &Q[i * 4];
		u32 N = A[3] + A[2]*256 + A[1]*256*256 + A[0]*256*256*256;
		JS_NewNumberValue(cx, (double)N, &V[i]);
	}
	JSObject * A = JS_NewArrayObject(cx, N, V);
	jsval RVAL = OBJECT_TO_JSVAL(A);
	JS_SET_RVAL(cx, vp, RVAL);
	JS_EndRequest(cx);
	return JS_TRUE;
}

static JSBool ijs_fread_utf(JSContext *cx, uintN argc, jsval *vp) {
    str R = read_data(cx, argc, vp, 1);
    JS_BeginRequest(cx);
    jschar *D;
    size_t Dlen;
    JS_DecodeBytes(cx, (const char*)*R, (size_t)!R, 0, &Dlen);
    D = (jschar*)malloc(sizeof(jschar)*Dlen);
    JS_DecodeBytes(cx, (const char*)*R, (size_t)!R, D, &Dlen);
    JSString *s = JS_NewUCString(cx, D, Dlen);
    //Dlen = JS_GetStringLength(s);
    jsval RVAL = STRING_TO_JSVAL(s);
    JS_SET_RVAL(cx, vp, RVAL);
    JS_EndRequest(cx);
    return JS_TRUE;
}


static JSBool yaui_platform(JSContext *cx, uintN argc, jsval *vp) {
   str R = "ios";
   return OUT_STRING(R);
}

void __log(str s) {
   char **datas = new char*[1];
	datas[0] = *s;
	control_ui(5555, datas);
}

static JSBool ijs_print(JSContext *cx, uintN argc, jsval *vp) {
	str s = ARG(0);
   char **datas = new char*[1];
	datas[0] = *s;
	control_ui(5555, datas);
//	s.append("print.log");
//	bool static first = true;
//	if (first)
//		first = false, setvbuf(stdout, NULL, _IONBF, 0);
//   printf("%s", *ARG(0));
   return JS_TRUE;
}

char CONTROL_MAX = 10;

static JSBool ijs_control_call(JSContext *cx, uintN argc, jsval *vp) {
   char **datas = new char*[argc];
   int CMD; JS_ValueToInt32(cx, vp[2], &CMD);
   strings L; 
   for (int i = 0; i < argc - 1; i++) {
	    JSString *p1 = JS_ValueToString(cx, vp[3 + i]);
     str h;
     char *k = JS_EncodeString(cx, p1);
     if (k == 0) k = "?";
	    str s = k;
     L << s;
     datas[i] = *L[i];
   }
   str R = control_ui(CMD, datas);
   return OUT_STRING(R);
}

static JSFunctionSpec myjs_global_functions[] = {
    JS_FN("yaui_platform", yaui_platform, 1, 0),
    JS_FN("print", ijs_print, 1, 0),
//    JS_FN("log", ijs_log, 1, 0),
    JS_FN("ijs_test", ijs_test, 1, 0),
    JS_FN("ijs_exec_js", ijs_exec_js, 2, 0),
    JS_FN("ijs_exec_js_error", ijs_exec_js_error, 0, 0),
    JS_FN("ijs_exit", ijs_exit, 0, 0),
    JS_FN("ijs_docdir", ijs_docdir, 1, 0),
    JS_FN("ijs_load", ijs_load, 1, 0),
    JS_FN("ijs_save", ijs_save, 2, 0),
    JS_FN("ijs_fileexists", ijs_fileexists, 1, 0),
    JS_FN("ijs_fopen", ijs_fopen, 1, 0),
    JS_FN("ijs_fclose", ijs_fclose, 1, 0),
    JS_FN("ijs_fsize", ijs_fsize, 1, 0),
    JS_FN("ijs_fread", ijs_fread, 3, 0),
    JS_FN("ijs_fread_utf", ijs_fread_utf, 3, 0),
    JS_FN("ijs_fread32", ijs_fread32, 3, 0),
    JS_FN("ijs_control_call", ijs_control_call, (uint16)(CONTROL_MAX + 1), 0),
    JS_FS_END
};

extern "C" char* call_cpp(int code, char *command, char *data = 0) {
	if (code == 1) {
		if ((!(runtime = JS_NewRuntime (200 * 1024L*1024L)))
			|| (!(context = JS_NewContext (runtime, 10*20*8192)))) throw ;
		JS_SetContextThread(context);
		JS_BeginRequest(context);
		global  = JS_NewObject  (context, NULL, NULL, NULL);
		if (!JS_InitStandardClasses(context, global)) return (char*)"EXIT_FAILURE";
		if (!JS_DefineFunctions(context, global, myjs_global_functions)) return JS_FALSE;
		JS_SetErrorReporter(context, reportError);
	}
	if (code == 2) {
		JS_EndRequest(context);
		JS_ClearContextThread(context);
		//JS_DestroyContext(context); JS_DestroyRuntime(runtime); JS_ShutDown();
	}
	if (code == 3) {
		exec_js(command, "internal");
	}
	if (code == 4) { // this is used to load bootstrap.js only, so we printf the error message if any
		str fpath = DOCDIR + (char*)"/" + command;
		str R = load(fpath);
		printf("%i bytes loaded\n", (int)!R);
		while (fpath.pos('/') >= 0) fpath.del(0, 1);
		exec_js(R, fpath);
		if (!monkey_last_error > 0) printf("Error executing BOOTSTRAP: %s\n", *monkey_last_error);
	}
	if (code == 5) { // for callbacks
		exec_js(command, command);
		if (!monkey_last_error > 0) printf("Callback error:\n%s\n", *monkey_last_error);
	}
	return (char*)"OK.";
}

int _main() {
	str s = "ready";
	printf("%s\n", *s);
	call_cpp(1, "");
	DOCDIR = ".";
	s = call_cpp(4, "bootstrap.js");
	call_cpp(2, "");
	printf("result: %s\n", *s);
	return 0;
} // end

