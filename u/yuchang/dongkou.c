//room: dongkou.c BY Yuchang

#include <ansi.h> 
inherit ROOM;

void init();
int do_zou(string);

void create()
{
  set("short","绝壁");
  set("long",@LONG
山道到此突然消失，在你面前是一条绝壁，往下看去云雾缭绕，你根
本无法看清谷底。绝壁边有个山洞（hole)，旁边有一块石碑(bei)。
LONG
     );
  set("outdoors", "chengdu");
  set("item_desc",([
      "bei" : "『麒麟窟』内有怪兽，小心啊！\n" ,
      "hole" : "这是麒麟窟，你不想活了可以(enter)进去。\n" ,
     ]));
  setup();
}

void init()
{
        add_action("do_enter", "enter");
}

int do_enter(string arg)
{
    object me;
string msg; 
object ob; 
    me = this_player();
foreach (ob in deep_inventory(me)) 
              if (ob->is_character()) 
             { 
                            command("say 进麒麟窟，生死由天，就不要带其他人进去了！"); 
                             return 1; 
                     } 
        if( !arg || arg=="" ) return 0;
        if( arg=="hole" ) 
    {
        message("vision",
            me->name() + "一弯腰往洞里走了进去。\n",
            environment(me), ({me}) );
                me->move("/u/yuchang/dong1");
                message("vision",
            me->name() + "从洞里走了进来。\n",
                    environment(me), ({me}) );
        return 1;
    }
}   
