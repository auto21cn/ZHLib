
/********************************************************************************
             The Voting System For Yhonline(HERO) By Rcwiz On 1 June 2003

This System can gain the result that players decided.
All Public functions in this file ard called by command which defined in 
"/cmds/std/poll.c" and the result of the Voting will be loged in the 
"/log/voting/log", so you can view the history of voting using command "poll history"

*********************************************************************************/

#pragma optimize
#pragma save_binary

inherit F_DBASE;

#include <ansi.h>

mapping voting = ([]);

public int query_now_voting_class(string now);
public mixed query_now_voting_target();
public int show_voting(object me, string para);
public int start_voting(object me, string target, string kind);
public int end_voting(object me);
public int shot_target(object me, string kind);
private string show_process(int i);

#define LOG_FILE "/log/voting/log"

void create()
{
        seteuid(getuid());
        set("no_clean_up", 1);
}

public int start_voting(object me, string target, string kind)
{
        string* kinds;

        int i;

        if (wiz_level(me) < 4)
        {
              write("你没有足够权限发起投票。\n");
              return 0;
        }

        if (sizeof(voting))
        {
              write(HIC "目前正在进行投票！必须先取消当前投票才能开始新的投票。\n");
              return 0;
        }

        kinds = explode(kind, ":");
        if (sizeof(kinds) <= 1)
        {
              write("这样的话还不如不投票。\n");
              return 0;
        }

        write(HIW "将对" + HIR + target + HIW + "进行投票，"
              "投票分类为：\n" NOR);

        voting = ([
                    "name"     :  me->name(),
                    "id"       :  me->query("id"),
                    "time"     :  time(),
                    "target"   :  target,
                    "kind"     :  kind,
                    "ips"      :  ({}),
                    "user_list":  ({}),
                 ]);

        for (i = 0; i < sizeof(kinds); i ++)
        {
              write(HIR "\t\t\t" + kinds[i] + "\n" NOR);
              voting += ([ kinds[i] : "init" ]);
        }

	message("vision", HIW "【系统提示】：有新的投票内容，请用 " HIY 
                "poll now" HIW " 查看！\n" NOR, all_interactive());

        return 1;
}

public int end_voting(object me)
{
        string str;
        string* kinds;
        int i;

        if (wiz_level(me) < 4)
        {
              write("你没有足够权限结束投票。\n");
              return 0;
        }

        if (sizeof(voting))
        {
              write("OK\n");
              message("vision", HIW "【系统提示】：当前投票 " HIR + voting["target"] + 
                      HIW " 结束了！以后请使用 " HIY "poll history" HIW 
                      " 查看！\n" NOR, all_interactive());

              kinds = explode(voting["kind"], ":");
              str = "";
              for (i = 0; i < sizeof(kinds); i ++)
              {
                      str += kinds[i] + "  " + (string)(voting[kinds[i]] == "init" ? 
                                                0 : voting[kinds[i]]) + " 票 | ";                      
              }

              log_file("voting/log", sprintf(HIC "%-20s：    %-20s\n" NOR, voting["target"], str));
              voting = ([]);
              return 1;
        }

        else 
        {
              write("当前没有投票。\n");
              return 0;
        }
}

public int query_now_voting_class(string kind)
{
        if (sizeof(voting))
        {
             if (voting[kind] == "init" || voting[kind] > 0)
                     return 1;
 
             else return 0;
        }

        else return 0;
}

public mixed query_now_voting_target()
{
        if (! sizeof(voting) || ! stringp(voting["target"]))
              return 0;

        return voting["target"];
}

public int show_voting(object me, string para)
{
        string* kinds;
        int nCount, nKinds;
        string str;

        if (para == "history")
        {
             if (file_size(LOG_FILE) == -1)
             {
                     write("目前没有历史投票记录！\n");
                     return 0;
             }
             nCount = 1;
             if (me->is_busy())
             {
                     write("等你忙完了再说吧！\n");
                     return 0;
             }
             me->start_busy(2);

             write(NOR + WHT "\n------------------------------------------------------------"
                   "-------------\n" NOR);
             while (str = read_file(LOG_FILE, nCount, 1))
             {
                     write(str);
                     nCount ++;
             }
             write(NOR + WHT "\n------------------------------------------------------------"
                   "-------------\n" NOR);

             return 1;
        }

        if (sizeof(voting) <= 0)
        {
            write(HIG "当前没有进行投票！\n");

            return 0;
        }

        kinds = explode(voting["kind"], ":");
        if (me->is_busy())
        {
             write("等你忙完了再说吧！\n");
             return 0;
        }
        me->start_busy(1);
        if (para == "now")
        {
             write(HIY "\n当前对 " + HIR + voting["target"] + HIY + " 投票情况如下：\n\n" NOR);
             for (nKinds = 0; nKinds < sizeof(kinds); nKinds ++)
             {
                     nCount = (voting[kinds[nKinds]] == "init" ? 0 : voting[kinds[nKinds]]);
                     write(sprintf(HIR "%-20s  %-20s  %-2d\n",  
                           kinds[nKinds], show_process(nCount),nCount));
             }
             write(HIG "\n请使用" HIY + "poll shot<种类>" + HIG "进行投票！\n" NOR);
             return 1;
        }

}

public int shot_target(object me, string kind)
{       
        string *user_list, *ips, my_ip;

        if (wizardp(me) && wiz_level(me) < 5)
        {
               write("巫师不能投票哦！\n");
               return 0;
        }

        if (me->is_busy())
        {
               write("等你忙完了再说吧！\n");
               return 0;
        }

        if (! arrayp(user_list = voting["user_list"]))
               user_list = ({});


        if (! arrayp(ips = voting["ips"]))
               ips = ({});

        if (member_array(me->query("id"), user_list) != -1)
        {
               write("你已经投过票了！\n");
               me->start_busy(1);
               return 0;
        }

        // 验证IP
        my_ip = query_ip_number(me);

        if (member_array(my_ip, ips) != -1)
        {
               write("你所在IP已经投过票了！\n");
               me->start_busy(1);
               return 0;
        }

        if (voting[kind] == "init")
               voting[kind] = 1;

        else
               voting[kind] += 1;

        voting["user_list"] += ({ me->query("id") });
        voting["ips"] += ({ my_ip });

        write(HIG "【投票系统】：你成功投了 " + HIR + kind + HIG " 一票！\n" NOR);
        return 1;
}

private string show_process(int i)
{
       string s = "";
       int nCount;

       for (nCount = 0; nCount <= i; nCount ++)
               s += " ";
       
       return BBLU + s + NOR;
}
