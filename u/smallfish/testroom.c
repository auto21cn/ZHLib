#include <ansi.h>
#include <command.h>;

inherit ROOM;

void create()
{
        set("short", "乌鸦巢");
        set("long", @LONG
一个用树枝搭成的大鸟巢，里面寄居着不少乌鸦，看来似乎是乌鸦专门
做的巢。不停的有乌鸦飞进来歇息，同时也有不少乌鸦飞到外面觅食。在
鸟巢底下有一条天然形成的石道(dong)，似乎可以让人钻进去，但是石道
通向哪里就只有乌鸦们知道了。
LONG
        );
        
        
        set("sleep_room",1);
	set("objects",([
	]));

set("exits", ([ /* sizeof() == 1 */
//    "south" : "/u/kyy/rose",
//    "west" : __DIR__"dmyuan2",
]));
        setup();
}

void init()
{
        add_action("do_zuan", "zuan");
        add_action("do_fei", "fei");
        add_action("do_check","jiuyang");
        add_action("do_sleep","shuijiao");
        add_action("do_test","test");
}

int do_check(string arg)
{
         object obj;
         if (!arg) 
         {
                 obj = "/adm/daemons/story/jiuyang"->select_character();
                 if (obj) 
                 {
                         write(obj->query("id")+"\n");
			return 1;
                 }
                 return notify_fail("没人\n");
         }
         obj = find_player(arg);
         if (!obj) return notify_fail("这个人不在线。\n");
         if (SKILL_D("jiuyang-shengong")->valid_learn(obj)) return notify_fail("这个人可以学。\n"); 
         return notify_fail("这个人不可以学。\n");
}
int do_zuan(string arg)
{
   object me;
   me = this_player();
   if ( !arg )
   {
      message_vision("你想干什么？\n",me);
      return 1;
   }

   if (arg == "dong") 
   {
        message_vision("$N没有别的办法可想，只好猫着腰钻进石道里面。\n",me);
        me->start_busy(1);
        message_vision("$N不知钻了多久，只觉眼前一亮，来到了外面。\n",me);
        me->start_busy(1);
        me->move("/d/city/guangchang");
        return 1;
   }

}

int do_fei(string arg)
{
        object me;
        me = this_player();
        if ((string)me->query("id") != "smallfish")
        return notify_fail("你有翅膀吗？\n");
        
        message_vision("$N拍拍翅膀飞走了。\n",me);
        me->move("d/city/kedian");
        return 1;
}

int do_sleep(string arg)
{
        object me;
        me= this_player();
//      if ((time()-me->query("last_sleep"))<0)
//        return notify_fail("你刚睡过一觉，先活动活动吧。 \n");
        message_vision("$N往乌鸦巢中一躺，迷迷糊糊就睡着了。\n",me);
        me->set_temp("sleeped",1);
        me->set_temp("block_msg/all",1);
        me->set("last_sleep",time());
        me->set("no_get", 1);
        me->set("no_get_from", 1);
        me->disable_player("<睡梦中>");
        call_out("wakeup",0,me);
        return 1;
}
void wakeup(object me)
{
        if(!me) return;
        me->set("qi",    2*me->query("eff_qi"));
        me->set("jing",  2*me->query("eff_jing"));
        me->set("jingli", 2*me->query("eff_jingli"));
        me->set("neili", 2*me->query("max_neili"));
        me->enable_player();
        call_out("del_sleeped", 0, me);
        message_vision("$N被一阵乌鸦的叫声吵醒了。\n",me);
        me->set_temp("block_msg/all", 0);
        write("你被乌鸦的叫声吵醒了。\n");
        me->delete("no_get");
        me->delete("no_get_from");

}

void del_sleeped(object me)
{
        if (objectp(me) &&  me->query_temp("sleeped"))
                me->delete_temp("sleeped");
}

int do_test()
{
        int i;
        string index,temp_index;
        object ob,me;
        me = this_player();
        ob = present("sword",me);
        if (objectp(ob))
                index = base_name(ob);

        temp_index = index;
        if (objectp(ob) && strlen(temp_index) > 21 && temp_index[0..20] == "/data/gaoshou/weapon/")
        {
                i = strsrch(temp_index,"-");
                if (i != -1) temp_index = temp_index[0..i-1];
                i = strsrch(temp_index,"/",-1);
                if (i != -1) temp_index = temp_index[i+1..strlen(temp_index)-1];
                if (temp_index && strlen(temp_index) > 1)
                        index = "/data/item/" + temp_index[0..0] + "/" + temp_index + "-" + ob->query("id");
        }
        if (file_size(index+".c") > 0)
                tell_object(me,index + "\n");
        return 1;
}
