//Room: leidongping.c 雷洞坪
//Date: Oct. 2 1997 by That
#include <ansi.h>
inherit ROOM;

void create()
{
      set("short","雷洞坪");
      set("long",@LONG
雷洞坪一带，道路艰险骇人，路左是蔽日遮天的冷杉林，路右是深不见底
的绝壁峡谷。这里长年云遮雾罩，空蒙黑暗。岩上建有雷神殿，旁边竖一铁碑。
由此往上是「八十四盘」至接引殿，北下到洗象池。
LONG);
      set("outdoors", "emei");
      set("exits",([ /* sizeof() == 1 */
          "northdown"  : __DIR__"lingyunti",
          "southup"    : __DIR__"bashisipan1",
          "east"       : __DIR__"lengsl1",
      ]));
      setup();
}

int valid_leave(object me, string dir)
{
        int c_exp,c_skill;
        me = this_player();
        if (dir == "southup" )
        {
                c_exp   = me->query("combat_exp");
                c_skill = me->query_skill("dodge",1);
                if (me->query("qi") > 10)
                {
                        if (((c_skill*c_skill*c_skill/10) < c_exp) &&
                            (c_skill<101))
                           me->improve_skill("dodge",
                                             (int)me->query_skill("dodge", 1) / 5);
                        tell_object(me,"你爬上八十四盘，有些累了。\n");
                } else
                {
                        me->set("qi", 0);
                        tell_object(me, "你太累了，再也走不动了。\n");
                        return notify_fail("还是歇歇脚再走路吧。\n");
                }
      }
      return 1;
}

