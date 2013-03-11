#include <v8.h>
#include <string.h>
#include <jni.h>
#define UNICODE
#include "nova.h"
#include "utf.cpp"
#include <android/log.h>
#define PRINTF(...) ((void)__android_log_print(ANDROID_LOG_INFO, "yaui", __VA_ARGS__))
#include "v8util.h"

#define jni(name) extern "C" jstring Java_tw_ksana_javacpp_Javacpp_##name

wstrings a2s(const v8::Arguments& args) {
	wstrings R;
	for (int i = 0; i < args.Length(); i++) {
		v8::HandleScope handle_scope;
		v8::String::Value stri(args[i]);
		wstr w =(wchar_t*)  "<string conversion failed>";
		if (*stri) w = (wchar_t*)(*stri);
		R << w;
	}
	return R;
}

#define function(name) v8::Handle<v8::Value> name(const v8::Arguments& a)

function(yaui_platform) {
	return String::New("android");
}

function(print) {
	wstrings L = a2s(a);
	str s = join(L, " ");
	PRINTF(*s);
	return v8::Undefined();
}

#include "v8file.h"

JNIEnv* Env = 0; jobject Obj; jclass cls = 0; jmethodID mid = 0;

wstr j_to_str(jstring s) {
	jchar *p = (jchar*) Env->GetStringChars(s , 0) ;
	int n = Env->GetStringLength(s);
	wstr R; R(n); 
	for (int i = 0; i < n; i++) R.p->p[i] = (wchar_t)p[i];
	Env->ReleaseStringChars(s, p);
	return R;
}

wstr control_ui(int code, wstrings &L) {
	wstr w = join(L, "\1");
	jstring J = (Env)->NewString((jchar*)*w, !w);
	jstring R = (jstring) (Env)->CallObjectMethod(Obj, mid, code, J);
	wstr s = j_to_str(R);
	Env->DeleteLocalRef(J);
	Env->DeleteLocalRef(R);
	return s;
}

function(yadroid) {
	wstrings L = a2s(a);
	int N = ~--L;
	wstr R = control_ui(N, L);
	return String::New((uint16_t*)*R, !R);
}

#undef function
#define function(name) G->Set(v8::String::New(#name), v8::FunctionTemplate::New(name));
Persistent<Context> context;
Context::Scope *context_scope;

jni(initJS)(JNIEnv* env, jobject thiz) {
	if (Env == 0) {
		Env = env; Obj = thiz;
		cls = (Env)->GetObjectClass(Obj);
		mid = (Env)->GetMethodID(cls, "control_ui", "(ILjava/lang/String;)Ljava/lang/String;");
	} else PRINTF("skip cls");
	HandleScope handle_scope;
	Handle<ObjectTemplate> G;
	G = ObjectTemplate::New();
	function(yaui_platform)
	function(print)
	function(yadroid)
	function(ijs_exec_js)
	function(ijs_exec_file_js)
	function(ijs_load)
	function(ijs_save)
	function(ijs_fileexists)
	function(ijs_fopen)
	function(ijs_fclose)
	function(ijs_fsize)
	function(ijs_fread)
	function(ijs_fread32)
	function(ijs_fread_utf)
	context = Context::New(0, G);
	context_scope = new Context::Scope(context);
	return (env)->NewStringUTF("v8 ready");
}

jni(execJS)(JNIEnv* env, jobject thiz, jstring script, jstring report_name, bool load_file) {
	wstr R = v8_exe(j_to_str(script), j_to_str(report_name), load_file);
	if (v8_exe_error) PRINTF("%s\n", *R.compat()), R = "";
	return (env)->NewString((jchar*)*R, !R);
}

