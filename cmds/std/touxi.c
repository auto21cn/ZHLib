// touxi.c 偷袭
// by King 97.05

#include <ansi.h>

int main(object me, string arg)
{
	object obj;
        int skill, count,my_exp,sb_exp;

	if (environment(me)->query("no_fight"))
		return notify_fail("这里禁止战斗。\n");

	if (! arg || ! objectp(obj = present(arg, environment(me))))
		return notify_fail("你想偷袭谁？\n");

	if (me->is_chatter())
		return notify_fail("你这个样子有什么好偷袭的？\n");

	if (! obj->is_character())
		return notify_fail("看清楚一点，那并不是生物。\n");

	if (obj->is_fighting(me))
		return notify_fail("你已经在战斗中了，还想偷袭？\n");

        my_exp = me->query("combat_exp");
        sb_exp = obj->query("combat_exp");
        if(my_exp < sb_exp / 10)
                return notify_fail("你不是"+obj->query("name")+"的对手，不要白白去送死了。\n");
        if (wizardp(obj))
                return notify_fail(obj->query("name")+"瞪了你一眼，你突然吓得两腿发抖，几乎跪了下来。\n");

	if (! living(obj))
		return notify_fail(obj->name() + "都已经这样了，你还用"
				   "得着偷袭吗？\n"); 

	if (obj == me)
		return notify_fail("偷袭自己？别这么想不开。\n");

	if (me->is_busy())
		return notify_fail("你的动作还没有完成，不能偷袭。\n");

	if (obj->query_competitor())
		return notify_fail("人家比武你要偷袭？真是太不要脸了。\n");

	if (base_name(obj) == "/kungfu/class/generate/player_npc" )
		return notify_fail("那个人你无法偷袭。\n");

       notify_fail("你无从下手。\n");
       switch (obj->accept_touxi(me))
	{
	        case 1:
                       return 0;
	        case -1:
		         return 1;
	        default:
	}

	tell_object(me, "你飞身纵起，扑向" + obj->name() +"！\n");
	tell_object(obj, CYN "\n" + me->name() + "忽然向你扑来！\n\n"NOR);
	message("vision", CYN "\n" + me->name() + "忽然向" + obj->name() +
			  "扑去！\n\n"NOR, environment(me), ({me, obj}) );

	count = me->query_str();

	me->want_kill(obj);
	me->kill_ob(obj);

	if (random(me->query("combat_exp")) < (int)obj->query("combat_exp") / 2)
	{
		me->add_temp("str", count * 4);
		COMBAT_D->do_attack(me, obj, me->query_temp("weapon") );
		me->add_temp("str", - count * 4);
	} else
	{
		COMBAT_D->do_attack(me, obj, me->query_temp("weapon"));
		COMBAT_D->do_attack(me, obj, me->query_temp("weapon"));
		COMBAT_D->do_attack(me, obj, me->query_temp("weapon"));
	}

	me->start_busy(3);
	obj->kill_ob(me);

	return 1;
}

int help(object me)
{
  write(@HELP
指令格式 : touxi <人物>
 
这个指令用来向敌人偷袭。偷袭不成时，则会招至反击。
特别适合于经验低的玩家向经验高的玩家拚命。:)

其他相关指令: fight, kill, hit
HELP
    );
    return 1;
}
