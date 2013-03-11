function(ijs_exec_js) {
	wstrings L = a2s(a);
	str s = w2utf(L[0]);
	return v8_exec(s, L[1]);
//	return v8::Undefined(); // TODO 1) return value 2) avoid conversion
}
function(ijs_exec_file_js) {
	wstrings L = a2s(a);
	str s = load(L[0]);
	return v8_exec("", L[0], true);
//	return v8::Undefined(); // TODO 1) return value 2) avoid conversion
}
function(ijs_load) {
	wstrings L = a2s(a);
	wstr R = utf2w(load(L[0]));
	return String::New((uint16_t*)*R, !R);
}
function(ijs_save) {
	wstrings L = a2s(a);
	w2utf(L[1]).save(L[0]);
	return Undefined();
}
function(ijs_fileexists) {
	wstrings L = a2s(a);
	str fn = L[0];
	int R = fileexists(*fn);
	return Number::New(R);
}
function(ijs_fopen) {
	wstrings L = a2s(a);
	str P1 = L[0];
	int R = (int)fopen(*P1, "rb");
	return Number::New(R);
}
function(ijs_fclose) {
	wstrings L = a2s(a);
	int F = ~L[0];
	int OK = fclose((FILE*)F);
	if (OK == 0) return Boolean::New(true);
	else return Boolean::New(false);
}
function(ijs_fsize) {
	wstrings L = a2s(a);
	str P1 = L[0];
	double R = filesize(*P1);
	return Number::New(R);
}
str read_data(const v8::Arguments& a, int unit_size) {
	wstrings L = a2s(a);
	int F = ~L[0];
	long size = ~L[1] * unit_size;
	long pos = ~L[2];
	str R; R(size);
	fseek((FILE*)F, pos, SEEK_SET);
	fread((void*)*R, (size_t)1, (size_t)!R, (FILE*)F);
	return R;
}
function(ijs_fread) {
	HandleScope handle_scope;
	str R = read_data(a, 1);
	Handle<Array> A = Array::New(!R);
	for (int i = 0; i < !R; i++) A->Set(i, Integer::New((int)(byte)R[i]));
	return handle_scope.Close(A);
}
function (ijs_fread32) {
	HandleScope handle_scope;
	str R = read_data(a, 4);
	byte *Q = (byte*)*R;
	int N = !R / 4;
	Handle<Array> A = Array::New(N);
	for (int i = 0; i < N; i++) {
		byte *q = &Q[i * 4];
		u32 N = q[3] + q[2]*256 + q[1]*256*256 + q[0]*256*256*256;
		A->Set(i, Integer::New(N));
	}
	return handle_scope.Close(A);
}
function(ijs_fread_utf) {
	str R = read_data(a, 1);
	return String::New(*R, !R);
}
function(v8_exit) {
	V8::TerminateExecution();
	return Undefined();
}

