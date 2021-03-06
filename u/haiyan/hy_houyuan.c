// hy_houyuan.c 

inherit ROOM; 
#include <ansi.h>
#include <getconfig.h>
#include "/u/haiyan/menpai.h"

void create() 
{ 
     set("short", "后  院"); 
     set("long", @LONG 
这里是海燕家的后院，院里开满了各种各样的鲜花。蜜蜂和
蝴蝶在翩翩飞舞采蜜，一股淡淡的花香使你留连忘返。一张石桌
上摆着一副围棋。北面是一条长廊。
LONG); 
     set("exits", ([ 
         "out"      : __DIR__"workroom",  
         "north"    : __DIR__"hy_clang",
     ])); 
     set("no_sleep_room", "1"); 
     setup(); 
}

void init()
{
     add_action("do_skill", "skill");
}

int do_skill()
{
        string dir,filename, msg, mc, *kp;
        int i, j, l, s;
        mixed *all_file;

        seteuid(getuid());
        dir = "/kungfu/skill/";
        all_file = get_dir(dir);
        kp = keys(menpai);
        msg = HIC"  武功名称              武功ID           所属门派\n"NOR;
        msg += HIC"-------------------------------------------------\n"NOR;
        s = 0;
        for (i = 0;i < sizeof(all_file);i++)
        {
            filename = all_file[i];
            l = strlen(filename);
            if (filename[l - 1] == 'c' && filename[l - 2] == '.')
            {
               mc = to_chinese(filename[0..l-3]);
               msg += sprintf("%-20s ", mc);
               msg += sprintf("%-20s ", filename[0..l-3]);
               for (j = 0;j < sizeof(kp);j++)
               {
                   if (member_array(mc, menpai[kp[j]]) != -1)
                   {
                       s = 1;
                       msg += kp[j] + " ";
                   }
               }
               if (s == 1)  { s = 0;  msg += "\n"; }
               else msg += HIR"未知\n"NOR;
            }
        }
        this_player()->start_more(msg);
        return 1;
}

