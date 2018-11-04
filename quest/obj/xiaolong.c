
//小笼包 (特殊force,force,dodge,parry)各加1级  pot + 5w


#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "小笼包" NOR, ({ "xiaolong baozi", "xiaolong", "baozi" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "这是瞎三笨从家乡杭州带来的特产小笼包。\n" NOR);
                set("unit", "个");
                set("no_sell",1);
                set("weight", 10);                
             }
        setup();
}

void init()
        {
                add_action("do_eat","eat");
        }
                

int do_eat( string arg )
{       
        if (arg == "xiaolong baozi" || arg == "xiaolong" || arg == "baozi")

        {
         string mapsk;   
         object me;
         int i;
        
         me = this_player();

        if ( me->query("liwu/2005random/eat") )
        {write(HIR"这次的礼物你已经吃过了呀！\n"NOR);return 1;}

        message_vision(HIY "$N将小笼包一口吞了，满嘴流油。\n" NOR, me);

         log_file("static/wuyi", sprintf("%s(%s) eat 小笼包 at %s.\n",
                 me->name(1), me->query("id"), ctime(time())));

        me->set("liwu/2005random/eat", 1);

         me->add("potential", 50000);
          for(i=0; i<5; i++)
         {
         mapsk = me->query_skill_mapped("force");
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 120000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 120000);

                mapsk = me->query_skill_mapped("parry");
                if (me->can_improve_skill("parry"))
                        me->improve_skill("parry", 120000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 120000);

                mapsk = me->query_skill_mapped("dodge");
                if (me->can_improve_skill("dodge"))
                        me->improve_skill("dodge", 120000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 120000);
          }
                destruct(this_object());
                return 1;
        }
else {  return 0;}
}
                
