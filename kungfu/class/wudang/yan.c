// yan.c �����

#include <ansi.h>
#include "wudang.h"

inherit NPC;
inherit F_MASTER;

string ask_lianzhen();
int accept_object(object who, object ob); 

void create()
{
        set_name("�����", ({ "yu daiyan", "yu" }));  
        set("nickname","�䵱����");
        set("long", 
                "�����������������������ҡ�\n"
                "����һ���ɸɾ����Ļ�ɫ���ۡ�\n"
                "���������ʮ�������ݳ����񵭳�ͣ���Ĭ���ԡ�\n");
        set("gender", "����");
        set("age",43);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 29);
        set("int", 28);
        set("con", 31);
        set("dex", 25);
        
        set("max_qi", 4400);
        set("max_jing", 2000);
        set("neili", 5200);
        set("max_neili", 5200);
        set("jiali", 100);
        set("combat_exp", 1450000);
        set("score", 45000);

        set_skill("force", 190);
        set_skill("wudang-xinfa", 190);
        set_skill("taiji-shengong", 190);
        set_skill("dodge", 165);
        set_skill("tiyunzong", 165);
        set_skill("cuff", 170);
        set_skill("taiji-quan", 170);
        set_skill("strike", 170);
        set_skill("wudang-zhang", 170);
        set_skill("hand", 170);
        set_skill("paiyun-shou", 170);
        set_skill("parry", 175);
        set_skill("sword", 180);
        set_skill("wudang-jian", 180);
        set_skill("taiji-jian", 180);
        set_skill("taoism", 160);
        set_skill("array", 180);
        set_skill("zhenwu-array", 180);
        set_skill("literate", 100);

        set("no_teach", ([
                "taiji-shengong" : "Ҫ��ѧϰ̫����������������̡�",
                "taiji-jian"     : "̫���������������״���",
                "taiji-quan"     : "̫��ȭ�����������״���",
        ]));

        set("inquiry", ([ 
                "���佣��" :  "���佣�������䵱�ɽ�����ħ֮�������䵱���������ڼӲ��ݡ�", 
                "����"     : (: ask_lianzhen :), 
        ])); 

        map_skill("force", "taiji-shengong");
        map_skill("dodge", "tiyunzong");
        map_skill("cuff", "taiji-quan");
        map_skill("array", "zhenwu-array");
        map_skill("parry", "taiji-quan");
        map_skill("sword", "taiji-jian");
        map_skill("strike", "wudang-zhang");

        prepare_skill("cuff", "taiji-quan");
        prepare_skill("strike", "wudang-zhang");

        create_family("�䵱��", 2, "����");
        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/wudang/obj/greyrobe")->wear();
}

void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting",2 , ob);
        }
}

void greeting(object ob)
{
   int i;
        if (!environment(this_object()) || base_name(environment(this_object())) != "/d/wudang/gaotai")
                return;
   if (((int)ob->query_skill("wudang-xinfa", 1) == 0))
   {
      message_vision(CYN"ʮ�����Ӷ�$N�����ȵ��������аħ������������佣��\n\n"NOR,ob);
      ob->set("qi",30);
      if ((int)ob->query("combat_exp") <2000) ob->set("combat_exp",1);
         else ob->add("combat_exp",-1000);
      message_vision(CYN"���佣���ʱ��������̨�Ͻ����ݺᣬ��$NΧ�����롣\n"NOR,ob);
      message_vision(CYN"ʮ���ڳ����������$N���ϻ�����ʮ�������ӣ���Ѫ���졣\n"NOR,ob);
      say(CYN"\n\n���������ŭ�ݣ���аħ�����Ҳ�Ҵ����佣�󣡡�\n");
      message_vision("����ҾӸ����£�����һ�ư�$N�����̨��\n\n\n"NOR,ob);
      ob->move("/d/wudang/nanyangong");
      CHANNEL_D->do_channel(this_object(),"chat",sprintf("%s ˽�����佣������ɳ����ף�����һ����",ob->name(1)));
   }
}

void attempt_apprentice(object me)
{
        if (! permit_recruit(me))
                return;

        if ((int)me->query_skill("wudang-xinfa", 1) < 30) {
                command("say ���䵱�����ڼ��书���������ڹ��ķ���");
                command("say " + RANK_D->query_respect(me) +
                        "�Ƿ�Ӧ����̫�����϶��µ㹦��");
                return;
        }

        if ((int)me->query("shen") < 10000) {
                command("say ���䵱���������������ɣ��Ե���Ҫ���ϡ�");
                command("say �ڵ��з��棬" + RANK_D->query_respect(me) +
                        "�Ƿ����ò�����");
                return;
        }

        if ((int)me->query_skill("wudang-xinfa", 1) < 70)
        {
                command("say ���䵱����ע���ڹ��ķ�" + RANK_D->query_respect(me)+
                        "�Ƿ�Ӧ�����䵱�ķ��϶��µ㹦��?");
                return;
        }

        if ((int)me->query_skill("taoism", 1) < 70)
        {
                command("say ϰ����Ϊ��ǿ�����壬һζ�������ǲ���ȡ�ģ�");
                command("say �ҿ��㻹��Ҫ���������Է�����������������"
                        "����ĵ����ķ���");
                return;
        }

        command("say �ðɣ��Ҿ��������ˡ�");
        command("recruit " + me->query("id"));
}

string ask_lianzhen() 
{ 
     string msg; 
     object me = this_player(); 
     if (me->query_skill("zhenwu-array", 1) < 180 ) 
     {
        command(":) " + me->query("id"));
        msg = "�㻹���Ⱥúø���ѧѧ�����ɡ�";
        return msg; 
     }
     if (query_temp("count", 1) >= 8 )
     {
        msg = "���ڽ��������ѹ�����Ȼ��������ɡ�";
        return msg; 
     }
     if (me->query_temp("lianzhen"))
     {
        msg = "���佣��ֻҪ�ڼ���ϰ�������ޱȡ�";
        return msg; 
     }
     me->set_temp("lianzhen", 1);
     add_temp("count", 1);
     msg = "�ܺã�������úø�ʦ�ֵ��ǲ���(caoyan)����ɡ�"; 
     return msg; 
}

int accept_fight(object ob) 
{
    command("say �ҿ�û���������棡\n"); 
    return notify_fail("������" + this_object()->name() + "��������������\n");  
}

int accept_hit(object ob) 
{
    command("say ���ǲ������������佣���������\n"); 
    command("cold "+ob->query("id")); 
    return 0;
}

int accept_kill(object ob) 
{
    command("say �����췴��\n"); 
    command("cold "+ob->query("id")); 
    return notify_fail("\n"); 
}

int accept_touxi(object ob) 
{ 
    tell_object(ob,"�����͵Ϯ��ͻȻ����" + this_object()->name() + "�������㡣\n"); 
    command("sigh "+ob->query("id")); 
    return 1; 
} 

int accept_ansuan(object ob) 
{ 
    return notify_fail("����밵�㣬���Ƿ���" + this_object()->name() + "�ǳ�С�Ľ����������޴����֡�\n");  
}  
