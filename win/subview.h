#include "hand_cur.h"
//If you got a strange blinking, change: create(self) -> create(self.b)
int DRAG_DELAY = 100;
struct inherit(SubBar, win) {
	 win *parent;
	 on_created { data["me"] = "SubBar"; }
	 str cmd(str s) { return owner->cmd(s); }
};

struct inherit(Sub, win) {
   int delta, z, track; bool vert, slide, control;
	  SubBar b;
	  on_created {
      //if (CURSOR == 0) load_cursor();
      if (CURSORH == 0) load_cursor_h();
      if (CURSORV == 0) load_cursor_v();
     	b.create(this); b.move(0, 0); b.show();	b.parent = this;
      delta = 0;
  	   add_timer(10, 0);
      track = -1;
      data["me"] = "Sub";
      control = slide = false;
		    vert = false;
      z = -1;
  	}
  void scroll_to(int n) {
     delta = n;
     if (vert) b.move(0, -delta); else b.move(-delta, 0);
  }
   on_cursor {
      if (control) { set_scroll_cursor();
	     if (slide) {
          int MAX = vert? b.H() - H() : b.W() - W();
          int D = (track - (vert?y:x))*3;
          delta += D; if (delta<0) delta=0; if (delta > MAX) delta = MAX;
          scroll_to(delta);
//          printf("%i %i %i\n", D, delta, MAX);
          track = vert?y:x;
      }}
   }
   on_mouse {
      if (!control) return;
      if (button == 0) {
         if (down) { slide=true ;track=vert?y:x, set_scroll_cursor(), say("scroll_begin"); }
         else slide=false, say("scroll_end");
      }
   }
  void say(str what) {
     owner->cmd((str)"subview_"+what+" " + (str)(int)&b);
  }
 	on_timer {
     int o = vert ? GetKeyState(VK_MENU) : GetKeyState(VK_CONTROL);
//     if (o & 0x80) ZCursor = 0, set_scroll_cursor();
     if (z != o)  {
        bool mine = false;
        POINT P; GetCursorPos(&P); void *p = WindowFromPoint(P);
//        printf("%s %i %i\n", *data["who"], handle, p);
        loop {
           if (p == handle) {
//             printf("* %s %i %i\n", *data["who"], handle, p);
             mine = true; break;
           }
           p = GetParent(p);
           if (!p) break;
        }
        if (true) {
           if (mine && (o & 0x80)) {
              start_mouse_capture(), control = true, set_scroll_cursor();
		if (vert) ZCursor = CURSORV; else ZCursor = CURSORH;
//              printf(">%s\n", *data["who"]);
              }
              else if (control) end_mouse_capture(), control = false;
        }
     }
     z = o;
	 }
  void set_scroll_area(int n) {
     int w, h;
//     printf("setting to %i\n", n);
     if (vert) { h = n;	if (h < H()) return; w = W();}
     else {w = n;	if (w < W()) return;	h = H(); }
//     printf("new size %i %i\n", w, h);
     b.size(w, h);
     b.move(0, 0);
  }
   void set_scroll_cursor() {
      if (vert) SetCursor(CURSORV); else SetCursor(CURSORH);
   }
};


