// group_quest:family 群组任务——门派入侵

#include <ansi.h>
#include "family.h"

#define GROUP_QUEST_D   "/adm/daemons/group_questd"

void create()
{
    seteuid(getuid());

    if (!select_quest())
    {
        destruct(this_object());
        return;
    }
}

string prompt() { return HIR "【门派入侵】" NOR; }

int select_quest()
{
    int i;
    object *all_user;
    object ob, the_user;
    string p, *kp;
    mapping fam_map = ([]);

    kp = GROUP_QUEST_D->get_family();
    for(i = 0; i < sizeof (kp); i++)
    {
        p = kp[i];
        all_user = users();
        all_user = filter_array(all_user, (: $1->query("family/family_name") == $2 :), p);
        all_user = filter_array(all_user, (: not_wizard :));
        if(!sizeof(all_user)) continue;    //该门派没有玩家在线
        if(sizeof(all_user) < 3) continue;    //在线人数过少的门派跳过
        fam_map += ([ p:sizeof(all_user) ]);
    }
    if(!sizeof(fam_map)) return 0;     //MUD中没有属于任何一个门派的玩家
    kp = keys(fam_map);
    p = kp[random(sizeof(kp))];
    all = fam_map[p];
    if (all < 5) all = 5;
    if (all > 20) all = 30 - random(10);

    the_family = p;

    all_user = users();
    all_user = filter_array(all_user, (: $1->query("family/family_name") == $2 :), p);
    all_user = filter_array(all_user, (: not_wizard :));
    the_user = all_user[random(sizeof(all_user))];
    name1 = the_user->name(1);
    all_user -= ({ the_user });
    the_user = all_user[random(sizeof(all_user))];
    name2 = the_user->name(1);
    all_user -= ({ the_user });
    the_user = all_user[random(sizeof(all_user))];
    name3 = the_user->name(1);
    all_user = 0;

    the_nation = "中国";
    the_enemy = GROUP_QUEST_D->get_enemy();
    story = all_story[random(sizeof(all_story))];

    return 1;
}

string create_tiaoxin()
{
    object ob;
    int i,lvl;
    string title;

    title = HIY + the_family + NOR + HIW + "仇家" + NOR + " " + HIY +
            the_enemy + NOR;

    for(i = 0;i < all;i ++)
    {
        lvl = random(15) + 1;
       ob = GROUP_QUEST_D->create_npc(the_nation, lvl);
        GROUP_QUEST_D->place_npc(ob, "门派", the_family, lvl);
        ob->set("title", title);
        ob->random_move();
        ob->random_move();
        ob->random_move();
        ob->random_move();
    }
    GROUP_QUEST_D->set_enemy(all);
    return "大小喽罗高呼：『" + HIY + "【" + the_family + "】" + NOR + WHT + "的人快给我滚出来，大爷们今天要你们的好看！！』";
}

mixed query_quest_message(int step)
{
    mixed msg;

    if(step >= sizeof(story))
        return 0;

    msg = story[step];
    if(stringp(msg))
    {
        msg = replace_string(msg, "name1", name1);
        msg = replace_string(msg, "name2", name2);
        msg = replace_string(msg, "name3", name3);
        msg = replace_string(msg, "the_enemy", HIY + the_enemy + NOR + WHT);
        msg = replace_string(msg, "the_family", HIY + "【" + the_family + "】" + NOR + WHT);
    }
    return msg;
}

int not_wizard(object ob)
{
    if(wizardp(ob))
        return 0;

    return 1;
}

