
inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object obj;

        if (! arg)return notify_fail("你要帮助谁？\n");

        if (! objectp(obj = present(arg, environment(me))))
                return notify_fail("这里没有这个人。\n");

        if (obj->query_temp("need_accede/user") != me->query("id"))    
               return notify_fail("这个人不需要你帮助！\n");
        
        ULTRA_D->need_accede(obj, me);

	return 1;
}

int help(object me)
{
	write(@HELP
指令格式 : accede <id>

跟特定的ＮＰＣ比试或者帮助特定ＮＰＣ。

HELP
    );
    return 1;
}
 