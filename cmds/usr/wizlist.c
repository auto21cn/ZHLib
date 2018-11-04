#include <ansi.h>
inherit F_CLEAN_UP;
string get_job(string arg);
mapping wizhood=([
//"(root)":       HIY" 创世者 "HIB,   
        "(admin)":      HIY"【 创世者 】"HIB,
        "(arch)":       HIG"【 大  神 】"HIB,
        "(wizard)":     HIY"【 巫  师 】"HIB,
        "(apprentice)": HIC"【 学  徒 】"HIB,
        "(immortal)":   HIB"【 精  灵 】"HIB,
        "(elder)":      HIM"【荣誉玩家】"HIB,
]);
mapping wizlevel=([
        //0:      "(root)",
        1:      "(admin)",
        2:      "(arch)",
        3:      "(wizard)",
        4:      "(apprentice)",
        5:      "(immortal)",
        6:      "(elder)",
]);
int main(object me, string arg)
{
        string *list, ch,job;
        int my_level,b, i, j, number,a,mark,lev;
        object ob;
        number = 0;
        job="";
        list = sort_array(SECURITY_D->query_wizlist(), 1);
        write(HIR"★"+HIY+""+MUD_NAME +""HIR"★"HIG"巫师列表:\n"NOR);
        write(HIR"★"HIW"≡"HIB"──────────────────────────────"HIW"≡"HIR"★\n"NOR);
        write(HIB"  【"HIW" 等  级 "HIB"】  【"HIW"巫师ID"HIB"】  【"HIW"状态"HIB"】     【"HIW"负责区域"HIB"】\n"NOR);
        write(HIR"★"HIW"≡"HIB"──────────────────────────────"HIW"≡"HIR"★\n"NOR);
        my_level=wiz_level(me);
if (wizardp(me)) {
lev=7;
}
else{
lev=5;
}
        for (b=0;b<lev;b++)
        {
        mark=0;
        for(i=0, j=0; i<sizeof(list); i++)
        if(SECURITY_D->get_status(list[i])==wizlevel[b]) mark=1;
        if(mark){
        printf(HIB"\n  "+wizhood[wizlevel[b]]+"  "+NOR);
        for(i=0, j=0; i<sizeof(list); i++)
        if(SECURITY_D->get_status(list[i])==wizlevel[b])
        {
                ch = HIR"  离线"NOR;
                a = 0;
                job=get_job(list[i]);
                if(!job) job="中华总监";
                if(ob=find_player(list[i])&&!find_player(list[i])->query("env/invisibility"))
                {
                ch = HIG"  在线"NOR ;
                a = 1;
                number = number + 1;
                 }
             else if (ob = find_player(list[i]) && wizardp(me) && find_player(list[i])->query("env/invisibility") )
              {
                    ch = HIB"  隐身"NOR;
                  a = 1;
                     number = number + 1;
                 }
           if( list[i]=="xhuarong" ) {}
         else printf(HIY"  %-10s"" %s    "HIW"    %s\n                ",list[i],ch,job," " ? "\n " : " ");
        }
        }
        }
        write(HIR"\n★"HIW"≡"HIB"──────────────────────────────"HIW"≡"HIR"★\n"NOR);
                if (wizardp(me)) {
      printf(HIR"★"+HIY+MUD_NAME+HIG"目前共有:"BLINK HIR"%s"NOR HIG"个巫师。\n"NOR,chinese_number(sizeof(list)) );
                }
        printf(HIR"★"+HIY+MUD_NAME+HIG"目前共有:"BLINK HIR"%s"NOR HIG"位巫师在线上"NOR,chinese_number(number));
        write("\n");
        return 1;
}
string get_job(string arg)
{
        string str;
        switch(arg)
   {
          case "dvunix":   {str=HIM"情景策划"NOR;break;}

            }
        return str;
}
int help(object me)
{
  write(@HELP
指令格式：wizlist
指令说明：
           本指令用来查看目前总共有多少个巫师。
HELP
    );
    return 1;
}
