package tw.ksana.yaui;
import android.app.Activity;
import android.os.Bundle;
import android.view.Window;
import android.view.WindowManager;
//import android.widget.TextView;
import android.view.*;
import android.view.View.OnClickListener;
import android.view.View.*;
import android.widget.*;
import android.widget.TextView.BufferType;
import android.content.Context;
import android.text.*;
import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import android.os.Environment;
import java.util.ArrayList;
import java.util.Timer;
import java.util.TimerTask;
import java.io.BufferedReader;
import java.io.FileReader;
import android.util.Log;
import android.graphics.*;
import android.util.DisplayMetrics;
import android.net.Uri;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.widget.LinearLayout.LayoutParams;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.graphics.Typeface;
import android.text.method.ScrollingMovementMethod;
import android.text.style.*;//ForegroundColorSpan
import android.text.method.LinkMovementMethod;
import android.view.View.MeasureSpec;

class FileUtils { // TODO: get rid of this, just use /data/local/tmp on device to load .so
	public static boolean copyFile(File source, File dest) {
		BufferedInputStream i = null;BufferedOutputStream o = null;
		try {i = new BufferedInputStream(new FileInputStream(source));
		o = new BufferedOutputStream(new FileOutputStream(dest, false));
		byte[] buf = new byte[1024];i.read(buf);
		do {o.write(buf);} while(i.read(buf) != -1);} catch (IOException e) {return false;
		}finally{try{if(i!=null)i.close();if(o!=null)o.close();}catch(IOException e){return false;}}
		return true;
	}
}

@SuppressWarnings(value={"deprecation"})
public class Yaui extends Activity implements View.OnClickListener {
	TextView tv; 
	int id_count;
	AbsoluteLayout layout0;
	long init_millis = -1;
	long time1000() {
		if (init_millis < 0) init_millis = System.currentTimeMillis();
		return System.currentTimeMillis() - init_millis;
	}
	
	private class HSV extends HorizontalScrollView {
		public LinearLayout L;
		public AbsoluteLayout A;
		public HSV(Context context) {
			super(context);
			L = new LinearLayout(context);
			A = new AbsoluteLayout(context);
		}
		@Override public void addView(View child) { A.addView(child); }
		void update_scroll() {
			removeView(L); addView(L, 0); L.removeView(A); L.addView(A);
			A.invalidate(); L.invalidate(); invalidate(); requestLayout();
		}
	}

	private class VSV extends ScrollView {
		public LinearLayout L;
		public AbsoluteLayout A;
		public VSV(Context context) {
			super(context);
			L = new LinearLayout(context);
			A = new AbsoluteLayout(context);
		}
		@Override public void addView(View child) { A.addView(child); }
		void update_scroll() {
			removeView(L); addView(L, 0); L.removeView(A); L.addView(A);
			A.invalidate(); L.invalidate(); invalidate(); requestLayout();
		}
	}
	
	private class MyTextWatcher implements TextWatcher {
		private TextView E;
		public MyTextWatcher(TextView e) { E = e; }
		public void afterTextChanged(Editable e) {
		//					  if(e.length()==0){	lv.clearTextFilter(); }
		}
		public void beforeTextChanged(CharSequence e, int start, int count, int after) {
		}
		public void onTextChanged(CharSequence e, int start, int before, int count) {
			String s =  "yaui.on.text_change(" + E.getId() + ")";
			execJS(s, s, false);
		}
	}

	public void start_watcher() {
		int delay = 100; // delay for 5 sec.
		int period = 100; // repeat every sec.
		Timer timer = new Timer();
		timer.schedule(new TimerTask() {	@Override	public void run() {timerMethod();}}, delay, period);
	}
	private void timerMethod(){this.runOnUiThread(doSomething);}
	private Runnable doSomething = new Runnable() { public void run() {	
		try {
			String s = "/sdcard/kill";
			File x = new File(s);
			if (x.exists()) { x.delete(); System.exit(0); }
		}finally{}
	};};
	
	// /data/local/tmp/
	private void check_lib(String name) {
		String path = this.getFilesDir().getAbsolutePath() + "/" + name;
		File a = new File("/sdcard/" + name);
		File b = new File(path);
		int DO = 1;
		if (b.exists()) {
//			Log.d("yaui", "   sdcard: " + a.lastModified() + ", internal: " + b.lastModified());
			if  (a.lastModified() <= b.lastModified()) DO = 0;
		} else {		}
		if (DO == 1) { 
			//Log.d("yaui", "copying..." + name);
			FileUtils.copyFile(a, b);
			File c = new File(path);
			//Log.d("yaui", "new internal: " + c.lastModified());
			File d = new File("/sdcard/" + name);
			d.setLastModified(c.lastModified());
		} //else Log.d("yaui", "fast loading: " + name);
		System.load(path);
	}

	class LL extends LinearLayout {
		LL(Activity o) { super(o); }
	}
	
	@Override	protected void onCreate(Bundle savedInstanceState) {
		id_count = 2;
		Log.d("yaui", "\n\nstart");
		check_lib("libv8.so");
		check_lib("libdJS.so");
		super.onCreate(savedInstanceState);
		final Context context = getApplication();
		layout0 = new AbsoluteLayout(this);
		layout0.setId(1);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
//		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
		setContentView(layout0);
		start_watcher();
//		layout0.measure(MeasureSpec.UNSPECIFIED, MeasureSpec.UNSPECIFIED);
//		getMeasuredHeight
//		Log.d("yaui", "getMeasured: " + layout0.getMeasuredWidth());
		Log.d("yaui", "initJS::" + initJS());
		Log.d("yaui", "boot_droid::" + execJS("/sdcard/js/bootstrap.js","/sdcard/js/bootstrap.js",true));
		Rect r = new Rect();
		Window w = getWindow();
		w.getDecorView().getWindowVisibleDisplayFrame(r);
		int h = w.findViewById(Window.ID_ANDROID_CONTENT).getTop();
		int h1 = h - r.top;
	}
	
	ArrayList<String> font_names = null;
	ArrayList<Typeface> fonts = null;
	
	Typeface font_by_name(String name) {
		if (font_names == null) font_names = new ArrayList<String>(); 
		if (fonts == null) fonts = new ArrayList<Typeface>(); 
		int j = -1;
		for (int i = 0; i < font_names.size(); i++) {
			if (font_names.get(i).equals(name)) { j = i; break; }
		}
		if (j < 0) {
			j = font_names.size();
			font_names.add(name);
			fonts.add(Typeface.createFromFile(new File(name)));
		}
		Typeface T = fonts.get(j);
		return T;
	}
	
int 
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

String code_toString(int code) {
		if (code == ya_main_handle) return "ya_main_handle";
		if (code == ya_alert) return "ya_alert";
		if (code == ya_make_button) return "ya_make_button";
		if (code == ya_make_label) return "ya_make_label";
		if (code == ya_make_input) return "ya_make_input";
		if (code == ya_make_edit) return "ya_make_edit";
		if (code == ya_make_image) return "ya_make_image";
		if (code == ya_make_hview) return "ya_make_hview";
		if (code == ya_hide) return "ya_hide";
		if (code == ya_show) return "ya_show";
		if (code == ya_input_line) return "ya_input_line";
		if (code == ya_text_of_text) return "ya_text_of_text";
		if (code == ya_set_text) return "ya_set_text";
		if (code == ya_set_font) return "ya_set_font";
		if (code == ya_set_read_only) return "ya_set_read_only";
		if (code == ya_set_scroll_area) return "ya_set_scroll_area";
		if (code == ya_set_scroll_pos) return "ya_set_scroll_pos";
		if (code == ya_set_bgcolor) return "ya_set_bgcolor";
		if (code == ya_set_xywh) return "ya_set_xywh";
		if (code == ya_get_app_size) return "ya_get_app_size";
		if (code == ya_get_scroll_pos) return "ya_get_scroll_pos";
		if (code == ya_set_timeout) return "ya_set_timeout";
		return "unknown code";
}

	ViewGroup VG;
//	EditText ET;
	TextView TV;
	View V;

	@Override	protected void onResume() { super.onResume();
		execJS("yaui.on.activity('resume')", "yaui.on.activity('resume')", false);}
	@Override	protected void onDestroy() { super.onDestroy();
		execJS("yaui.on.activity('destroy')", "yaui.on.activity('destroy')", false); }
	@Override	protected void onPause() { super.onPause();
		execJS("yaui.on.activity('pause')", "yaui.on.activity('pause')", false); }
	@Override	protected void onRestart() { super.onRestart();
		execJS("yaui.on.activity('restart')", "yaui.on.activity('restart')", false); }
	@Override	protected void onStart() { super.onStart();
		execJS("yaui.on.activity('start')", "yaui.on.activity('start')", false); }
	@Override	protected void onStop() { super.onStop();
		execJS("yaui.on.activity('stop')", "yaui.on.activity('stop')", false); }

	int str_to_int(String s) {
		return (int)Double.parseDouble(s);
	}
	@Override public void onClick(View sender) {
		String s = "yaui.on.button(" + sender.getId() + ")";
		execJS(s, s, false);
	}
	
	ViewGroup CurrentlyScrolledSV = null;
	String init_SV(FrameLayout H) {
		int id2 = -1, id3 = -1;
		final int id1 = id_count++;
		H.setId(id1);
		VG.addView(H);
		H.setOnTouchListener(new OnTouchListener() {
			public boolean onTouch(View v, MotionEvent event) {
				if (CurrentlyScrolledSV == null) CurrentlyScrolledSV = (ViewGroup)v;
			int id = CurrentlyScrolledSV.getId();
				if (event.getAction() == 0) { //touch begin
					String s = "yaui.on.subview_scroll_begin(" + id + ")";
					execJS(s, s, false);		 				
				}
				if (event.getAction() == 1) { // touch end
					String s = "yaui.on.subview_scroll_end(" + id + ")";
					execJS(s, s, false);	
					CurrentlyScrolledSV = null;
				}
				if (event.getAction() == MotionEvent.ACTION_UP 
					|| event.getAction() == MotionEvent.ACTION_CANCEL) return true;
					return false;
			}
	  });
		return Integer.toString(id1);
	}

	public String control_ui(int code, String args) { 
		String ARG[] = args.split("\u0001");
		try{
		int ID = -1;
		if (code >= 0x100) ID = Integer.parseInt(ARG[0], 10);
		if ((code & ya_flag_view) > 0) V = (View) findViewById(ID);
		if ((code & ya_flag_parent) > 0) VG = (ViewGroup) findViewById(ID);
//		if ((code & ya_flag_button) > 0) B = (Button) findViewById(ID);
		if ((code & ya_flag_textview) > 0) TV = (TextView) findViewById(ID);

//		if ((code & ya_flag_view) > 0) Log.d("yaui", "V=" + V);
//		if ((code & ya_flag_parent) > 0) Log.d("yaui", "VG=" + VG);
//		if ((code & ya_flag_button) > 0) Log.d("yaui", "B=" + B);
//		if ((code & ya_flag_textview) > 0) Log.d("yaui", "TV=" + TV);

		if (code == ya_main_handle) { return "1"; };
		if (code == ya_make_button) {
			int id = -1;
			Button b = new Button(this); 
			if (b != null) {
				id = id_count++;
				b.setId(id);
				b.setVisibility(View.INVISIBLE)	;
				b.setOnClickListener(this);
				if (VG != null) VG.addView(b);
			}
//			You can click a button programatically by using the "button.perfomClick()" method.
			String R = Integer.toString(id);
			return R;
		}
		if (code == ya_make_label) {
			int id = -1;
			TextView t = new TextView(this); 
			if (t != null) {
				t.setGravity(Gravity.TOP);
				t.setMovementMethod(new ScrollingMovementMethod());
				id = id_count++;
				t.setId(id);
				VG.addView(t);
			}
			return Integer.toString(id);
		}
		if (code == ya_set_text) {
			TV.setText(ARG[1]);
		}
		if (code == ya_set_xywh) {
			int 
				w = str_to_int(ARG[3]), h = str_to_int(ARG[4]),
				x = str_to_int(ARG[1]), y = str_to_int(ARG[2]);
			V.setLayoutParams(new AbsoluteLayout.LayoutParams(w, h, x, y));
		}
		if (code == ya_set_font){
			Typeface T = font_by_name(ARG[1]);
			TV.setTypeface(T);
			TV.setTextSize(Float.parseFloat(ARG[2]));
			TV.setTextColor(Color.parseColor("#" + ARG[3]));
		}
		if (code == ya_hide) {
			V.setVisibility(View.INVISIBLE)	;//GONE
		}
		if (code == ya_show) {
			V.setVisibility(View.VISIBLE);
		}
		if (code == ya_get_app_size) {
			Display mDisplay = getWindowManager().getDefaultDisplay();
			Point p;
			//mDisplay.getSize(p);
			int width= mDisplay.getWidth();
			int height= mDisplay.getHeight();		
			String s = "" + width + ":" + height;
			return s;
		}
		if (code == ya_make_edit) {
			int id = -1;
			EditText t = new EditText(this); 
			if (t != null) {
				t.setGravity(Gravity.TOP);
				id = id_count++;
				t.setId(id);
				t.addTextChangedListener(new MyTextWatcher(t));
				VG.addView(t);
			}
			return Integer.toString(id);
		}
		if (code == ya_input_line) {
			TV.setLines(1);
		}
		if (code == ya_text_of_text) {
			return ((Editable) TV.getText()).toString();
		}
		if (code == ya_make_image) {
			int id = -1;
			ImageView i = new ImageView(this); 
			if (i != null) {
				id = id_count++;
				i.setId(id);
				VG.addView(i);
				Bitmap b = BitmapFactory.decodeFile(ARG[1]);
				i.setImageBitmap(b);
			} 
			return Integer.toString(id);
		}
// *** * * * *  *  *   *   *   *    *    *     *     *     *      *       *        *        *		
		if (code == ya_set_scroll_area) {
			if (findViewById(ID) instanceof HSV) {
				HSV S = (HSV) findViewById(ID);
				S.update_scroll();
			} else {
				VSV S = (VSV) findViewById(ID);
				S.update_scroll();
			}
		}
		if (code == ya_get_scroll_pos) {
			int n;
			if (findViewById(ID) instanceof HSV) {
				HSV S = (HSV) findViewById(ID);
				n = S.getScrollX();
			} else {
				VSV S = (VSV) findViewById(ID);
				n = S.getScrollY();
			}
			return Integer.toString(n);
		}
		if (code == ya_set_scroll_pos) {
				FrameLayout S = (FrameLayout) findViewById(ID);
				if (findViewById(ID) instanceof HSV) S.scrollTo(str_to_int(ARG[1]), 0);
				else S.scrollTo(0, str_to_int(ARG[1]));
		}
		if (code == ya_make_hview) {
			HSV H = new HSV(this);  
			H.L.addView(H.A);
			H.L.setLayoutParams(new LayoutParams(LayoutParams.FILL_PARENT,LayoutParams.FILL_PARENT));
//			H.addView(H.L, 0);// call non overriden addView!
			return init_SV(H);
		}
		if (code == ya_make_vview) {
			VSV H = new VSV(this);  
			H.L.addView(H.A);
			H.L.setLayoutParams(new LayoutParams(LayoutParams.FILL_PARENT,LayoutParams.FILL_PARENT));
//			H.addView(H.L, 0);// call non overriden addView!
			return init_SV(H);
		}
// *** * * * *  *  *   *   *   *    *    *     *     *     *      *       *        *        *		
		
		if (code == ya_set_read_only){
			TV.setKeyListener(null);
		}
		if (code == ya_set_timeout){
			final String id = ARG[0];
			final long F = (long) Float.parseFloat(ARG[1]);
			Timer T = new Timer();
			T.schedule(new TimerTask() { @Override	
				public void run() { timerMethod(); }
				private void timerMethod(){runOnUiThread(doSomething);}
				private Runnable doSomething = new Runnable() { public void run() {	
					try {
						String s = "yaui.on.timer(" + id + ")";
						execJS(s, s, false);		 				
					}finally{}
				};};
				}, F);
		}
// -----------------------------------------------------
// --
// --
// -- version split
// --
// --
// -----------------------------------------------------
		if (code == ya_set_bgcolor) {
			V.setBackgroundColor(Color.parseColor("#" + ARG[1]));
		}
		////  ----            ---                ---               ---

		if (code == ya_alert) { // alert box
			AlertDialog ad = new AlertDialog.Builder(this).create();
			ad.setCancelable(false); // This blocks the 'BACK' button
			ad.setMessage(ARG[0]);
			ad.setButton("OK", new DialogInterface.OnClickListener() {
				@Override
				public void onClick(DialogInterface dialog, int which) {
					dialog.dismiss();
				}
			});
			ad.show();
		}
		return "ok"; 
		} catch(Exception ex) {
			Log.d("yaui", "@ yadroid " + code_toString(code) + "["+ code +"]" + "("+args+")");
			Log.d("yaui", "   @@ " + ex.getMessage());
		}
		return "err";
	};
	
	public native String initJS();
	public native String execJS(String script, String report_name, boolean load_file);
}
