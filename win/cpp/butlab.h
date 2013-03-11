struct inherit(Label, win)
{
    Str caption;
    int align; // 0-1-2 |3|

    void create(win &parent, Str text)
    {
        inherited:: create(&parent);
        caption = text;
        S->bg_color = parent.S->bg_color;
        align = 0;
    }

    on_paint
    {
        inherited :: paint();
        if (align == 1)
        {
           int x = S->str_width(caption), y = S->char_height('a');
           if (W() < x)
             size(x + 2, H());
           S->print(caption, (W() - x) / 2, (H() - y) / 2);
        }
        else if (align == 0)
        {
           S->print(caption, 0, 0);
        }
    }
};

struct button_colors
{
   ints text, frame, back;
   button_colors()
   {
      text << 0;          //normal
      text << 0;          //pressed
      text << 0xffffff;   //hover
      text << 0xffffff;   //hover pressed
      frame << 0x808080;
      frame << 0x808080;
      frame << 0x505050;
      frame << 0;
      back << 0xa0a0a0;
      back << 0xf0f0f0;
      back << 0x808080;
      back << 0x808080;
   }
};

struct button : win
{
    Str title;
    bool Down, Over;
    int cmd_data, Switch;
    button_colors colors;
    cmd_obj* owner;
    str cmd_msg;
    dib *V;

    button()
    {
       V = 0;
       Down = false;
       Over = false;
       Switch = -1;
       cmd_data = 0;
    }

    on_created
    {
       S->font_name("arial");
       S->font_size(10);
       S->font_set();
    }

    on_paint
    {
        int c = 0;
        bool Pressed = Down || Switch == 1;
        if (Over && Pressed) c = 3;
        else
           if (Pressed) c = 1;
           else if (Over) c = 2;
        int
           text_color = colors.text[c],
           frame_color = colors.frame[c],
           back_color = colors.back[c];
        S->crect(0, 0, W(), H(), back_color);
        #ifdef UNDER_CE
        S->frame(0, 0, W() - 1, H() - 1, frame_color);
        #else
        S->frame(0, 0, W() - 1, H() - 1, frame_color);
        #endif
        int x, y;
        if (V)
        {
           x = (W() - ~*V) / 2, y = (H() - !*V) / 2;
        }
        else
        {
           x = S->str_width(title), y = S->char_height('a');
           if (W() < x) size(x + 2, H());
           int w = W();
           int h = H();
           x = (w - x) / 2;
           y = (h - y) / 2;
        }
        if (Down) { x++; y ++; };
        if (V)
        {
           S->blit(*V, x, y);
        }
        else
        {
           S->font_color(text_color);
           S->print(title, x, y);
        }
    }

    on_timer
    {
       #ifdef WIN32
       POINT P;
       GetCursorPos(&P);
       P.x -= LEFT();
       P.y -= TOP();
       if (P.x < 0 || P.y < 0 || P.x > w() || P.y > h())
       {
          del_timer(1);//2KillTimer(handle, 1);
          Over = false;
          Down = false;
          paint();
       }
       #endif
    }

    on_cursor
    {
        if (!Over)
        {
           Over = true;
           add_timer(10, 1);
           //2SetTimer(handle, 1, 10, 0);
           paint();
        }
    }

    on_mouse
    {
        if (Switch >= 0 && down) Switch = Switch == 1 ? 0 : 1;
        Down = down;
        paint();
        if (down)
        {
           if (owner)
             owner->cmd(cmd_msg + " " + (str)(int)this);
           //SendMessage(GetParent(handle), WM_COMMAND, cmdid, cmd_data);
        }
    }
};
