// shade.c

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	int lvl,i;
	object env, *inv;
       string *can_perform;

       can_perform = me->query("can_perform/martial-cognize");

       if(!can_perform || 
          !arrayp(can_perform) || 
          !sizeof(can_perform) || 
          member_array("shade",can_perform) == -1
         )
		return notify_fail("你还没有学会使用［天龙之雾］！\n");

        if (me->is_busy())
                return notify_fail("你上一个动作还没有完成，无法使用天龙之雾。\n");

	lvl = (int)me->query_skill("martial-cognize",1);

       if(lvl < 250)
                return notify_fail("你的武学修养不够高深！\n");

	if( me->query("jingli") < 500 )
		return notify_fail("你的精力不够！\n");

	if( me->query("max_jingli") < 1000 )
		return notify_fail("你的精力还没有达到足够的层次！\n");

       if( me->query("jing") <= 300 )
                return notify_fail("你的精神状态不好！\n");

       if(me->query("env/invisibility"))
                return notify_fail("你正在施展［天龙之雾］\n");

       if (time() - me->query("last_shade_time") < 600)
                return notify_fail("你刚使用过［天龙之雾］不久，还没有完全恢复过来，先休息一会吧。\n");

       if (environment(me) && environment(me)->query("no_fight"))
                return notify_fail("这里不能使用［天龙之雾］!\n");

	me->add("jingli", -300);
	me->receive_damage("jing", 200);

	message_vision(HIW "$N面色凝重，两道精光从双目爆射而出，一阵白色雾气迅速涌出鼻孔，把自己浑身上下都包围着，整个人渐渐虚化．．．\n" NOR, me);
	        me->set("env/invisible", 1);

       me->set("last_shade_time",time());
       me->start_call_out( (: call_other, __FILE__, "remove_effect", me :), lvl/5);
       if( me->is_fighting() ) me->start_busy(3);
       return 1;

}
void remove_effect(object me)
{
        me->delete("env/invisible");
        tell_object(me,"你的天龙之雾失效了！\n");
        message_vision(HIW "一阵雾气突然出现，并且越来越浓，旋即又四散而却，$N显身了。\n" NOR,me);
}
