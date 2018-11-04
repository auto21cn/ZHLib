// zhang.c ������

#include <ansi.h>
#include "wudang.h"

#define ZHENWU_SWORD    "/clone/weapon/zhenwu"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

mixed ask_jian();
mixed ask_me();
mixed ask_tu();
mixed ask_tao();
mixed ask_an();

void create()
{
        set_name("������", ({ "zhang sanfeng", "zhang" }));
        set("nickname", HIG "��������" NOR);
        set("long", 
                "�������䵱�ɿ�ɽ���桢�������ֵ�̩ɽ�������������ˡ�\n"
                "����һ���ۻ�Ļ�ɫ���ۣ����ޱ߷���\n"
                "���ĸߴ��������꣬������⣬��ü�԰ס�\n");
        set("gender", "����");
        set("age", 100);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 31);
        set("int", 39);
        set("con", 40);
        set("dex", 32);
        
        set("max_qi", 7500);
        set("max_jing", 5000);
        set("max_jingli", 4000);
        set("jingli", 4000);
        set("max_neili", 9999);
        set("neili", 9999);
        set("jiali", 150);
        set("combat_exp", 3200000);
        set("score", 1200000);

        set_skill("force", 300);
        set_skill("taiji-shengong", 300);
        set_skill("wudang-xinfa", 300);
        set_skill("dodge", 260);
        set_skill("tiyunzong", 260);
        set_skill("cuff", 300);
        set_skill("taiji-quan", 300);
        set_skill("strike", 300);
        set_skill("wudang-zhang", 290);
        set_skill("hand", 290);
        set_skill("paiyun-shou", 290);
        set_skill("parry", 300);
        set_skill("sword", 300);
        set_skill("wudang-jian", 300);
        set_skill("taiji-jian", 300);
        set_skill("taoism", 300);
        set_skill("literate", 180);
        set_skill("medical", 270);
        set_skill("liandan-shu", 270);

        map_skill("force", "taiji-shengong");
        map_skill("dodge", "tiyunzong");
        map_skill("cuff", "taiji-quan");
        map_skill("hand", "paiyun-shou");
        map_skill("strike", "wudang-zhang");
        map_skill("parry", "taiji-quan");
        map_skill("sword", "taiji-jian");

        prepare_skill("cuff", "taiji-quan");
        prepare_skill("strike", "wudang-zhang");

        create_family("�䵱��", 1, "��ɽ��ʦ");
        set("class", "taoist");

        set("inquiry", ([
                "���佣" : (: ask_jian :),
                "����"   : "����ѧʲô���У�",
                "����"   : "����ѧʲô������",
                "�����а": (: ask_me :),
                "̫��ͼ"  : (: ask_tu :),
                "���־�"  : (: ask_tao:),
                "���־�"  : (: ask_an :),
        ]));

        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: perform_action, "sword.lian" :),
                (: perform_action, "sword.chan" :),
                (: perform_action, "sword.sui" :),
                (: perform_action, "cuff.tu" :),
                (: perform_action, "cuff.tao" :),
                (: perform_action, "cuff.po" :),
                (: perform_action, "cuff.zhan" :),
                (: exert_function, "recover" :),
        }) );

        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/wudang/obj/greyrobe")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if ((int)ob->query_skill("wudang-xinfa", 1) < 120)
        {
                command("say ���䵱�����ڼ��书���������ڹ��ķ���"); 
                command("say " + RANK_D->query_respect(ob) + 
                        "�Ƿ�Ӧ�����䵱�ķ��϶��µ㹦��");
                return;
        }

        if ((int)ob->query("shen") < 60000)
        {
                command("say ѧ��֮�ˣ�����Ϊ�ȣ�����ĸߵ͵�������Σ�δ���䣬Ҫ��ѧ���ˡ�");
                command("say �ڵ��з��棬" + RANK_D->query_respect(ob) +
                        "�Ƿ����ò�����");
                return;
        }

        if ((int)ob->query("combat_exp") < 300000)
        {
                command("say �����ھ�����ǳ��������������书���ȶ���Ҫ����");
                return;
        }

        if (ob->query_skill("taoism", 1) < 120)
        {
                command("say ���䵱���书ȫ�ӵ��������");
                command("say ��Ե����ķ������򻹲�����");
                command("say " + RANK_D->query_respect(ob) + "���Ƕ��о��о���ѧ�ķ��ɡ�");
                return;
        }

        if (ob->query_int() < 32)
        {
                command("say ���䵱���书���迿�Լ�����");
                command("say Ҫ�ܴﵽ¯����֮��������ʲô�ĵ����޹ؽ�Ҫ������ȴ�ǰ��Ҳ�������á�");
                command("say " + RANK_D->query_respect(ob) + "�����Ի�����Ǳ�����ڣ�������ذɡ�");
                return;
        }

        command("chat ����������������");
        command("chat �벻���ϵ��ڴ���֮�꣬���ٵ�һ������֮�ţ����ǿ�ϲ�ɺء�");
        command("recruit " + ob->query("id"));
}

mixed ask_jian()
{
        object me;
        object ob;
        object owner;

        me = this_player();
        if (me->is_bad())
        {
                if (me->query("family/family_name") == "�䵱��")
                        message_vision("$N��ŭ����$n����������Ϊ�䵱���ӣ�"
                                       "��������ħ�������������ת����\n",
                                       this_object(), me);
                else
                        message_vision("$N��ŭ����$n�ȵ�������һ��аħ��"
                                       "������Ȼ�ҿ������佣����\n",
                                       this_object(), me);
                return 1;
        }

        if (me->query("family/family_name") != "�䵱��")
                return "���佣�������䵱����֮�������������ʲô��";

        if (me->query("family/master_id") != query("id"))
                return "ֻ���ҵĵ��Ӳ��������佣���㻹����ذɡ�";

        if (me->query("shen") < 60000)
                return "������������������ò������Ҳ��ܰ����佣�����㡣";

        ob = find_object(ZHENWU_SWORD);
        if (! ob) ob = load_object(ZHENWU_SWORD);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "���佣�������������ô����ô�����������أ�";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "���Ѿ������佣���ȥ�ˡ�";

                if (owner->query("family/master_id") == query("id"))
                        return "���佣������" + owner->query("name") +
                               "���У���Ҫ���þ�ȥ�����ɡ�";
                else
                        return "���佣��������" + owner->query("name") +
                               "���У���ȥ�����һ����ɡ�";
        }

        ob->move(this_object());
        message_vision("$N���ͷ�������ã����������佣Ҫ����һЩ��"
                       "����������飡��\n", this_object(), me);
        command("give zhenwu jian to " + me->query("id"));
        return 1;
}

mixed ask_me()
{
        object me;

        me = this_player();
        if (me->query("can_perform/taiji-jian/zhenwu"))
                return "�Լ��úö���ϰ�ɣ�";

        if (me->query("family/family_name") != query("family/family_name"))
                return RANK_D->query_respect(me) + "���������䵱�ɵ��ˣ��γ����ԣ�";

        if (me->query("shen") < 120000)
                return "������������������Ļ��ܲ������Ҳ��ܴ�����У�";

        if (me->query_skill("taiji-jian", 1) < 180)
                return "���̫�������������ң�Ҫ��������";

        message_vision(HIY "$n" HIY "΢΢��ף����ּ���һ����֦��$N" HIY
                       HIY "ɨ����$N" HIY "������ƽ�����棬��Ϊ�ɻ�ֻ������һ����\n"
                       "��Ȼ$p" HIY "���ƴ�䣬���ȷǷ����仯���$P"
                       HIY "���һ�������Ҳ�����\n" NOR,
                       me, this_object());
        command("smile");
        command("say ��������ˣ�");
        tell_object(me, HIG "��ѧ���������а��\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 160000);
        me->set("can_perform/taiji-jian/zhenwu", 1);
        return 1;
}

mixed ask_tu()
{
        object me;

        me = this_player();
        if (me->query("can_perform/taiji-quan/tu") >= 10)
                return "��ѧ���㶼�Ѿ�ѧ�ˣ��Ժ�Ҫ�Ƽ����ã�";

        if (me->query("family/family_name") != query("family/family_name"))
                return RANK_D->query_respect(me) + "���������䵱�ɵ��ˣ��γ����ԣ�";

        if (me->query("shen") < 250000)
                return "������������������û������࣬�Ҳ��ܷ��Ĵ�����У�";

        if (me->query_skill("taiji-quan", 1) < 250)
                return "���̫��ȭ���������ң�Ҫ��������";

        if (me->query_skill("taiji-shengong", 1) < 300)
                return "���̫���񹦻������ң��ú����аɣ�";

        if (me->query_skill("taoism", 1) <300)
                return "��ĵ�ѧ�ķ��о��Ļ��������ף�Ҫ�¹����ѧ���ǣ�";

        if (me->query("max_jing") < 1000)
                return "��ľ������ã����㴫����̫��ͼ��Ҳ�������á�";

        message_vision(HIY "$n" HIY "���ͷ��˫�����Ữ��һ��Ȧ�ӣ�"
                       "���ϵ������޶����𣬽��������¡�\n" NOR,
                       me, this_object());
        command("smile");
        command("say �㿴���˶��٣�");

        if (me->query("potential") < me->query("learned_points") + 100)
        {
                write("�㿴�˰��죬û���о���ʲô��"
                      "�Ķ�����������Ǳ�ܻ�������\n");
                return 1;
        }

        me->add("learned_points", 100);

        if (me->add("can_perform/taiji-quan/tu", 1) < 10)
        {
                message_vision(HIY "$N" HIY "����ãã�ĵ���"
                               "��ͷ����˼���á�\n" NOR, me);
                tell_object(me, HIG "���̫��ͼ����һ������\n" NOR);
        } else
        {
                message_vision(HIY "$N" HIY "��¶Ц�ݣ�ϲ�������Ѿ�"
                               "�����ˣ���ν���������ʵ���޷ֱ𰡣�\n"
                               "$n������Ц�������׾ͺã����׾ͺã���"
                               "���������ʹ�ã���ȥ�ɣ�\n",
                               me, this_object());
                               
                tell_object(me, HIG "��ѧ���˵����ܼ�̫��ͼ��\n" NOR);
                if (me->can_improve_skill("taoism"))
                        me->improve_skill("taoism", 160000);
                if (me->can_improve_skill("taiji-shengong"))
                        me->improve_skill("taiji-shengong", 160000);
                if (me->can_improve_skill("unarmed"))
                        me->improve_skill("unarmed", 160000);
        }
        me->set("can_perform/taiji-jian/zhenwu", 1);
        return 1;
}

mixed ask_tao()
{
        object me;

        me = this_player();
        if (me->query("can_perform/taiji-quan/tao"))
                return "�Լ��úö���ϰ�ɣ�";

        if (me->query("family/family_name") != query("family/family_name"))
                return RANK_D->query_respect(me) + "���������䵱�ɵ��ˣ��γ����ԣ�";

        if (me->query("shen") < 120000)
                return "������������������Ļ��ܲ������Ҳ��ܴ�����У�";

        if (me->query_skill("taiji-quan", 1) < 300)
                return "���̫��ȭ������⻹������������Ҳ�����ã�";

        message_vision(HIY "$n" HIY "΢΢һЦ��˫�ֻ���ԲȦ��$N" HIY
                       HIY "ֻ��һ��ǿ������$N" HIY "��ס��˫�۲��ܶ�����\n"
                       "$p" HIY "����һ�£�$P" HIY "�ٸ���Ѫ��ӿ���ŵŵ�����������\n" NOR,
                       me, this_object());
        command("smile");
        command("say ��������ˣ�");
        tell_object(me, HIG "��ѧ����̫��ȭ�������־���\n" NOR);
        if (me->can_improve_skill("cuff"))
                me->improve_skill("cuff", 200000);
        me->set("can_perform/taiji-quan/tao", 1);
        return 1;
}

mixed ask_an()
{
        object me;

        me = this_player();
        if (me->query("can_perform/taiji-quan/an"))
                return "�Լ��úö���ϰ�ɣ�";

        if (me->query("family/family_name") != query("family/family_name"))
                return RANK_D->query_respect(me) + "���������䵱�ɵ��ˣ��γ����ԣ�";

        if (me->query("shen") < 120000)
                return "������������������Ļ��ܲ������Ҳ��ܴ�����У�";

        if (me->query_skill("taiji-quan", 1) < 400)
                return "�������־���̫��ȭ��֮���裬���̫��ȭ������⻹��һ�㣡";

        message_vision(HIY "$n" HIY "����һЦ��˫�ִ���������һ����$N" HIY
                       HIY "ѹ����$N" HIY "�е�һ��������ȫ����ס���������ڵ��ء�\n"
                       "$p" HIY "˫������һ����$P" HIY "������Ϣ�����������쳣��"
                       HIY "�������ۡ������һ��" HIR "��Ѫ" HIY "��\n" NOR,
                       me, this_object());
        command("smile");
        command("say ��������ˣ�");
        tell_object(me, HIG "��ѧ����̫��ȭ���İ��־���\n" NOR);
        me->receive_damage("qi", 1000); 
        me->receive_wound("qi", 300);  
        if (me->can_improve_skill("cuff"))
                me->improve_skill("cuff", 200000);
        me->set("can_perform/taiji-quan/an", 1);
        return 1;
}

int accept_object(object me, object ob)
{
        int r;
        if (r = ::accept_object(me, ob))
                return r;

        if (base_name(ob) != ZHENWU_SWORD)
        {
                command("say ��������ֶ�����ʲô��");
                return 0;
        }

        if (me->query("family/master_id") != query("id"))
                command("say ��л��λ" + RANK_D->query_respect(me) + "�����佣���ء�");
        else
                command("say �ܺã��ܺã�");
        destruct(ob);
        return 1;
}
