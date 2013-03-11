using namespace v8; 
// Extracts a C string from a V8 Utf8Value.
const char* ToCString(const v8::String::Utf8Value& value) {
  return *value ? *value : "<string conversion failed>";
}

Handle<Object> v8_error_as_object(v8::TryCatch* try_catch) {
	v8::HandleScope handle_scope;
	Handle<Object> Result = Object::New();
	Result->Set(String::New("exception"), try_catch->Exception());
	v8::Handle<v8::Message> message = try_catch->Message();
	if (!message.IsEmpty()) {
		Result->Set(String::New("message"), message->Get());
		Result->Set(String::New("script"), message->GetScriptResourceName());
		Result->Set(String::New("line"), Number::New(message->GetLineNumber()));
		Result->Set(String::New("pos"), Number::New(message->GetStartColumn()));
		Result->Set(String::New("endpos"), Number::New(message->GetEndColumn()));
		Result->Set(String::New("stack"), try_catch->StackTrace());
	} else {
		Result->Set(String::New("message"), String::New("no data"));
		Result->Set(String::New("script"), String::New("no data"));
		Result->Set(String::New("line"), String::New("no data"));
		Result->Set(String::New("pos"), String::New("no data"));
		Result->Set(String::New("endpos"), String::New("no data"));
		Result->Set(String::New("stack"), String::New("no data"));
	}
	return handle_scope.Close(Result);
}

wstr cvt(Handle<Value> s) { String::Value c(s); return (wstr)(wchar_t*)*c; }

wstr v8_error_as_string(v8::TryCatch* t) {
	wstr R;
	v8::HandleScope handle_scope;
	R / cvt(t->Exception());
	v8::Handle<v8::Message> m = t->Message();
	if (!m.IsEmpty()) {
		wstr e; e / cvt(m->GetScriptResourceName()) / ":" / m->GetLineNumber();
		R = e + ", " + R;
//		m->GetStartColumn();
//		m->GetEndColumn();
//		t->StackTrace();
	}
	return R;
}

Handle<String> ReadFile(const char* name) {
	FILE* file = fopen(name, "rb");
	if (file == NULL) return v8::Handle<v8::String>();
	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	rewind(file);
	char* chars = new char[size + 1];
	chars[size] = '\0';
	for (int i = 0; i < size;) {
		int read = static_cast<int>(fread(&chars[i], 1, size - i, file));
		i += read;
	}
	fclose(file);
	v8::Handle<v8::String> result = v8::String::New(chars, size);
	delete[] chars;
	return result;
}

// v8_exe and v8_exec - do the same, but first returns error or result as wstr, and second as v8::Object
bool v8_exe_error;

wstr v8_exe(str src, str file_name, bool load_from_file = false) {
	HandleScope handle_scope;
	Handle<String> source = String::New(*src);
	if (load_from_file) source = ReadFile(*file_name);
	Handle<String> name = String::New(*file_name, !file_name);
	Handle<Object> Result = Object::New();
	v8_exe_error = true;
	v8::TryCatch t;
	Handle<Script> script = Script::Compile(source, name);
	if (script.IsEmpty()) return v8_error_as_string(&t);
	Handle<Value> result = script->Run();
	if (result.IsEmpty()) return v8_error_as_string(&t);
	v8_exe_error = false;
	return cvt(result);
}

Handle<Object> v8_exec(str src, str file_name, bool load_from_file = false) {
	HandleScope handle_scope;
	Handle<String> source = String::New(*src);
	if (load_from_file) source = ReadFile(*file_name);
	Handle<String> name = String::New(*file_name, !file_name);
	Handle<Object> Result = Object::New();
	v8::TryCatch try_catch;
	Handle<Script> script = Script::Compile(source, name);
	if (script.IsEmpty()) {
		Result->Set(String::New("success"), Boolean::New(false));
		Handle<Object> E = v8_error_as_object(&try_catch);
		E->Set(String::New("source"), source);
		Result->Set(String::New("error"), E);
		return handle_scope.Close(Result);
	}
	Handle<Value> result = script->Run();
	if (result.IsEmpty()) {
		Result->Set(String::New("success"), Boolean::New(false));
		Handle<Object> E = v8_error_as_object(&try_catch);
		E->Set(String::New("source"), source);
		Result->Set(String::New("error"), E);
		return handle_scope.Close(Result);
	}
	Result->Set(String::New("success"), Boolean::New(true));
	Result->Set(String::New("result"), result);
	return handle_scope.Close(Result);
}

