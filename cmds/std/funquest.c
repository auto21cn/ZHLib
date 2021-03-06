// funquest.c  供查阅趣味任务完成情况的指令

#include <ansi.h>
 
inherit F_CLEAN_UP;

int main(object me)
{
        object ob;
        mapping q;
        int time1, time2;
        if ( me->query("xquest_total_ask/time") )
        {
           time1 = ( time() - me->query("xquest_total_ask/time") ) / 3600;
           time2 = (( time() - me->query("xquest_total_ask/time") ) % 3600 )/60;
           if (time2 < 0) time2 = 0;
           if ( time1 > 0 )
           {
             write("你这一轮趣味任务是" + time1 + "小时" + time2 +
                   "分钟前开始做的。\n");
           }  else
           {
             write("你这一轮趣味任务是" + time2 + "分钟前开始做的。\n");
           }
        }
        if (me->query("xquest_count"))
        write(sprintf("你已经连续完成了 %d 个趣味任务，继续加油努力啊！\n",
                     me->query("xquest_count")));

        if (! mapp(q = me->query("xquest")))
        {
                write("你现在没有领任何趣味任务！\n");
                return 1;
        }


        q =  me->query("xquest");

                switch (q["kind"])
        {

        case 0:
                write("目前"HIY + q["init_npc"] + NOR"让你去找" + q["place"] +
                "的"HIY + q["target_npc"] + NOR"打听线索。\n");
                return 1;

        case "send_letter":
                write("目前"HIY + q["init_npc"] + NOR"让你把一封信交到"HIY +
                q["place"] + NOR "的" HIY +  q["target_npc"]
                + NOR"手里。\n");
                return 1;

        case "bring_receipt":
                write("目前"HIY + q["init_npc"] + NOR"让你把回执交回给"HIY +
                q["target_npc"]+ NOR"。\n");
                return 1;

        case "buy_thing":
                write("目前"HIY + q["init_npc"] + NOR"让你帮他去找" +
                q["item"]+ "。\n");
                return 1;      
     /*   case "buy_thing":
             write("目前"HIY + q["init_npc"] + NOR"让你帮他去找一样东西。\n");
             return 1; */

        case "take_npc":
                write("目前"HIY + q["init_npc"] + NOR"让你把他的远房亲戚"HIY +
                q["target_npc"]+ NOR"带去"HIY + q["place1"] + NOR"的" HIY +
                q["place2"] + NOR"。\n");
                return 1;

        case "pay_gold":
                write("目前"HIY + q["init_npc"] + NOR"让你付给他"HIY +
                chinese_number(q["pay_amount"])+ NOR"两白银换线索。\n");
                return 1;

        case "do_drawing":
                write("目前" HIY + q["init_npc"] + NOR"让你把一个包裹埋到"HIY +
                q["place1"] + NOR "的" HIY +  q["place2"] + NOR "去，再把那里"
                "的地形画下来交给他。\n");
                return 1;
        case "guess_riddle":
                write("目前"HIY + q["init_npc"] + NOR"让你猜个谜语:" HIG +
                q["riddle"]+ NOR"你必须在五分钟内回答！\n");
                return 1;

        }

        write("你现在没有领任何趣味任务！\n");
        return 1;
}



int help(object me)
{
        write(@HELP
指令格式 : xquest  这个指令可以用来查阅你完成趣味任务的情况。
HELP );
        return 1;
}

