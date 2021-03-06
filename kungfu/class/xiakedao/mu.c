// mu.c
// Modified by Dumb, 2003-10-2, Insert leave xkd function.

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

#define REVIVE_ROOM             "/d/city/wumiao"

int ask_zhou();
int out_xiakedao();

void create()
{
        set_name("木丹凤", ({ "mu danfeng", "mu" }));
        set("long", "他就是天下闻之色变的侠客岛岛主，号称“叶上秋露”。\n"
                   +"只见他长须稀稀落落，兀自黑多白少，但一张脸却满是皱纹。\n"
                   +"看不出他的实际年纪。\n");
        set("title", HIB"侠客岛岛主"NOR);
        set("gender", "男性");
        set("age", 75);
        set("shen_type",1);
        set("attitude", "peaceful");

        set("str", 30);
        set("int", 29);
        set("con", 30);
        set("dex", 28);

        set("qi", 9000);
        set("max_qi", 9000);
        set("jing", 5000);
        set("max_jing", 5000);
        set("neili", 9000);
        set("max_neili", 9000);
        set("jiali", 200);

        set("combat_exp", 8000000);
        set("score", 200000);
        set_skill("force", 350);
        set_skill("unarmed", 350);
        set_skill("dodge", 350);
        set_skill("parry", 350);
        set_skill("sword", 350);
        set_skill("literate", 150);

        map_skill("force", "taixuan-shengong");
        map_skill("dodge", "taixuan-shengong");
        map_skill("unarmed", "taixuan-shengong");
        map_skill("parry", "taixuan-shengong");
        map_skill("sword", "taixuan-shengong");

        create_family("侠客岛",1, "岛主");
        set("inquiry",([
           "腊八粥" :   (: ask_zhou :),
           "侠客岛" :  "这个岛是我和龙兄弟无意中发现的。\n",
           "离岛"   :   (: out_xiakedao :),            
        ]));

        setup();
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
        add_money("gold", 2);
}

void attempt_apprentice(object ob)
{
        message_vision("木岛主拍拍$N的肩膀，微微摇了摇头。\n", ob);
        return;
}

int accept_object(object who, object ob)
{
        object obn;

        if ( !who || environment(who) != environment() ) return 0;
        if ( !objectp(ob) ) return 0;
        if ( !present(ob, who) ) return notify_fail("你没有这件东西。\n");

        if( (string)ob->query("name") == HIR"赏善罚恶令"NOR )
        {
            if (who->query_skill("taixuan-shengong", 1) > 0)
            {
                 message_vision("$N对$n微笑道：“这位" + RANK_D->query_respect(who) +
                                "与我侠客岛缘份不浅，老夫多谢了！\n",
                                this_object(), who);
                 return 1;
            }

            if( (string)ob->query("own") != (string)who->query("id") )
            {
                 message_vision("这不是你的东西，你从哪里得来的？\n", who);
                 return 0;
            }
            command("say  原来是" + (string)who->query("name") + "大侠" +
                "，欢迎光临本岛。");
            command("say 本岛洞内有一处石壁，上刻有太玄经，大侠可先去看看。" +
                    "随后可在二十四间石室随意观摩。");
            who->set_temp("xiakedao/think", 1);
            return 1;
        }
        else
        {
            message_vision("我不需要这东西。\n", who);
            return 0;
        }
}

int ask_zhou()
{
       object me = this_player();
       object ob;

       if (me->query_temp("xiakedao/think"))
       {
           if ( time() - me->query("zhou_time") > 1800 )
           {
                 message_vision("$N哈哈一笑，道：“好，这碗腊八粥刚刚煮好，" +
                                "这位" + RANK_D->query_respect(me) + "就请拿" +
                                "去吧。”\n", this_object(), me);
                 ob = new("/d/xiakedao/obj/zhou");
                 ob->move(me);
                 message_vision("$N拿出一碗" + ob->name() +
                                "给$n。\n", this_object(), me);
                 me->set("zhou_time", time());
                 return 1;
           } else
           {
                 message_vision("$N对$n道：“这位大侠，腊八粥的原料很难采到，" +
                                "现在还没有。”\n", this_object(), me);
                 return 1;
           }
       } else
       {
           message_vision("$N对$n道：“这是本岛特有的东西，它主要由一味" +
                          "「断肠蚀骨腐心草」构成，要开花后效力方著，\n" +
                          "但这种草每十年才开一次花，所以腊八粥很名贵，" +
                          "一般人很难得到的。\n" + RANK_D->query_respect(me) +
                          "想要，就要看你的缘分了！”\n", this_object(), me);
           return 1;
       }
}

int out_xiakedao()
{
   object me=this_player();
   if (me->query("baohu_xiakedao"))
   {
           message_vision("$N一声叹息，看着$n，慈祥的说道：“" + me->name(1) +
                          "你要记住，行走江湖，一切都靠小心谨慎，这次恰好老夫路过救你一命，" +
                          "下次，未必你我就有如此缘分，一切都自己保重了！”\n",
                                       this_object(), me);
           me->delete("baohu_xiakedao");
           me->move(REVIVE_ROOM);
           return 1;
   }
   message_vision("$N惊讶的看了你一眼，缓缓的说道：“" + me->name(1) +
                  "，你既然能来到侠客岛，还需要老夫告诉你怎么离岛么？虽然这里洞多路迷，" +
                  "相信也难你不倒啊！”\n",this_object(), me);
   return 1;   
}


