// pkd.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object *obs;
        string msg;
        string sht;
        int i;

	if (PK_D->is_ready())
		return notify_fail("现在正在报名呢，等会儿再说。\n");

        if (! PK_D->is_pking())
                return notify_fail("现在并没有在举行屠人大赛。\n");

        obs = PK_D->query_all_competitor();
        if (! obs)
                return notify_fail("无法和 PK DAEMON 进行正常的联系。\n");

        obs -= ({ me, 0 });
        msg = HIR "现在屠人场中除了你还剩下" + chinese_number(sizeof(obs)) +
              "人，他们是：\n" NOR;
        msg += HIC "≡" HIY "───────────────────────────────────" HIC "≡\n" NOR;
        for (i = 0; i < sizeof(obs); i++)
        {
                sht = obs[i]->name(1) + "(" + obs[i]->query("id") + ")";
                msg += (obs[i]->query("gender") == "女性" ? HIC : WHT) +
                        sprintf("%-20s", sht) + NOR;
                if (! ((i + 1) % 4))
                        msg += "\n";
        }

        if (i % 4)
                msg += "\n";
        msg += HIC "≡" HIY "───────────────────────────────────" HIC "≡\n" NOR;
        write(msg);
        return 1;
}

int help(object me)
{
write(@HELP
指令格式 : pkd

当屠人大赛开始的时候，可以用这条指令查看目前还有谁在屠人场中。
 
HELP );
        return 1;
}
