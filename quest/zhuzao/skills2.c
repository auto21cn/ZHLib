//星星（lywin）2000/8/29
 
#include <ansi.h>
 
inherit F_CLEAN_UP;
 
int main(object me, string arg)
{
        object ob;
        string rep,str;
 
        seteuid(getuid(me));
 
        if(!arg)
                ob = me;
        else if (wizardp(me)) {
                ob = present(arg, environment(me));
                if (!ob) ob = find_player(arg);
                if (!ob) ob = find_living(arg);
        if (!ob) return notify_fail("你要察看谁的状态？\n");
        } else
                return notify_fail("只有巫师能察看别人的状态。\n");
        rep = "\n";
        rep+= "┌──────────────────────┬─────────┐\n";
        rep+= sprintf("│生产技能总表                              │相应技能经验值    │\n");
        rep+= "├──────────────────────┴─────────┤\n";
        rep+= sprintf("│矿石挖掘技术                              │" + ob->query("work/wakuang") + "\n");              
        rep+= "├──────────────────────┴─────────┤\n";
        rep+= sprintf("│务农技术                                  │" + ob->query("work/wunon") + "\n");        
        rep+= "├──────────────────────┴─────────┤\n";
        rep+= sprintf("│烹饪技术                                  │" + ob->query("work/penlen") + "\n");       
        rep+= "├──────────────────────┴─────────┤\n";
        rep+= sprintf("│造剑技术                                  │" + ob->query("work/zhujian") + "\n");      
        rep+= "├──────────────────────┴─────────┤\n";
        rep+= sprintf("│造刀技术                                  │" + ob->query("work/zhudao") + "\n");       
        rep+= "├──────────────────────┴─────────┤\n";
        rep+= sprintf("│造板指技术                                │" + ob->query("work/zhubanzi") + "\n");     
        rep+= "├──────────────────────┴─────────┤\n";
        rep+= sprintf("│捕鱼技术                                  │" + ob->query("work/buyu") + "\n");        
        rep+= "├──────────────────────┴─────────┤\n";
        rep+= sprintf("│打猎技术                                  │" + ob->query("work/dalie") + "\n");        
        rep+= "├──────────────────────┴─────────┤\n";
        rep+= sprintf("│造酒技术                                  │" + ob->query("work/zhaojiu") + "\n");      
        rep+= "├──────────────────────┴─────────┤\n";
        rep+= sprintf("│盔甲铸造技术                              │" + ob->query("work/zhujia") + "\n");
        rep+= "└────────────────────────────────┘\n\n";
        write(rep);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : skills2
           skills2 <对象名称>                   (巫师专用)
这个指令用来查看你在浴血上的生产技能列表 

HELP
    );
    return 1;
}

