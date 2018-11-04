// hufei.c

#include <ansi.h>;

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

string ask_me();
string ask_book();
string ask_hujia_book();

void create()
{
    set_name("胡斐", ({"hu fei", "hu", "fei"}));
    set("gender", "男性");
    set("nickname", "雪山飞"HIG"狐"NOR);
    set("age", 25);
    set("long", @LONG
他就是胡一刀之子，因其武功高强神出鬼没。在江湖上人送外号「雪山飞狐」。
他身穿一件白色长衫，腰间别着一把看起来很旧的刀。满腮虬髯，根根如铁，
一头浓发，却不结辫。
LONG);
    set("attitude", "peaceful");
    set("str", 45);
    set("int", 30);
    set("con", 30);
    set("dex", 30);
    set("chat_chance", 10);
    set("chat_msg", ({
        "胡斐叹了口气道：“不知什么时候还能再见到若兰姑娘。\n",
        "胡斐切齿恨道：“阎基老贼暗中下毒，我必手刃此獠！”\n",
    }));

    set("qi", 4200);
    set("max_qi", 4200);
    set("jing", 2100);
    set("max_jing", 2100);
    set("neili", 5800);
    set("max_neili", 5800);
    set("jiali", 80);
    set("combat_exp", 2300000);
    set("score", 20000);
     
    set_skill("force", 210);            // 基本内功
    set_skill("lengyue-shengong", 210); // 冷月神功
    set_skill("blade", 240);            // 基本刀法
    set_skill("hujia-daofa", 240);      // 胡家刀法
    set_skill("dodge", 240);            // 基本躲闪
    set_skill("taxue-wuhen", 240);      // 踏雪无痕
    set_skill("parry", 220);            // 基本招架
    set_skill("throwing", 240);         // 基本暗器
    set_skill("mantian-xing", 240);     // 满天星
    set_skill("strike", 180);           // 基本掌法
    set_skill("tianchang-zhang", 180);  // 天长掌法
    set_skill("cuff", 180);             // 基本拳法
    set_skill("hujia-quan", 180);       // 胡家拳法
    set_skill("literate", 180);       // 读书写字
    map_skill("force", "lengyue-shengong");
    map_skill("blade", "hujia-daofa");
    map_skill("dodge", "taxue-wuhen");
    map_skill("parry", "hujia-daofa");
    map_skill("throwing", "mantian-xing");
    map_skill("strike", "tianchang-zhang");
    map_skill("cuff", "hujia-quan");

    prepare_skill("strike", "tianchang-zhang");
    prepare_skill("cuff",   "hujia-quan");

    create_family("关外胡家", 7, "传人");

    set("inquiry",([
        "宝刀":     (: ask_me :),
        "刀谱":     (: ask_book :),
        "胡家刀谱": (: ask_book :),
        "总诀":     (: ask_hujia_book :),
        "刀谱总诀": (: ask_hujia_book :),
        "阎基":     "阎基这个狗贼我非杀了他不可。\n",
        "胡一刀":   "辽东大侠胡一刀是我爹。不过我从没见过他。\n",
        "苗人凤":   "苗人凤和家父齐名，本可成为知交好友，然而家父却死在他的剑下。\n",
        "苗若兰":   "不知什么时候还能再见到若兰姑娘。\n",
        "若兰":     "不知什么时候还能再见到若兰姑娘。\n",
        "若兰姑娘": "不知什么时候还能再见到若兰姑娘。\n",
        "程灵素":   "现在我也不知道她在哪里，只是曾经听她说过好像要去襄阳。\n",
        "赵半山":   "我赵三哥啊！他刚来关外看我呢。 \n",
        "袁紫衣":   "算了，别提这伤心事了。\n"
    ]));

    set("baodao_count", 1);
    set("book_count", 1);
    set("hujia_book_count", 1);

    set_temp("apply/damage", 50);
    set_temp("apply/armor", 100);
    set_temp("apply/attack", 40);
    set_temp("apply/dodge", 40);
    set_temp("apply/parry", 40);

    setup();
    carry_object("/d/guanwai/obj/lengyue")->wield();
    carry_object("/clone/cloth/cloth")->wear();
}

string ask_me()
{
    object ob, me;

    me = this_player();
    if (me->query("family/family_name") !=
        query("family/family_name"))
    {
        command("shake");
        return "先入我门来再谈这些事。\n";
    }

    if ((int)me->query("shen") < 0)
    {
        command("sigh");
        return "你怎能走上邪路？败坏我胡家一世声名。\n";
    }

    if ((int)me->query("combat_exp") < 100000)
        return "以你目前的本领还不配使用闯王宝刀。\n";

    if ((int)me->query("shen") < 100000)
        return "以你目前的名望还不配使用闯王宝刀。\n";

    if ((int)query("baodao_count") > 0)
    {       
        add("baodao_count", -1);
        ob = new ("/d/guanwai/obj/cwbdao");
        ob->move(me);
        return " 好吧，这把闯王宝刀你先拿去用，希望你好好利用它。\n";
    }
    else
        return "你来晚了，现在这把刀已不在此处。\n";
}

string ask_book()
{
    object ob, me;

    me = this_player();
    if (me->query("family/family_name") !=
        query("family/family_name"))
    {
        command("shake");
        return "先入我门来再谈这些事。\n";
    }

    if ((int)me->query("shen") < 0)
    {
        command("sigh");
        return "你怎能走上邪路？败坏我胡家一世声名。\n";
    }

    if ((int)me->query("combat_exp") < 5000)
        return "你先好好学习武功，刀谱我自然会交给你。\n";

    if ((int)query("book_count") > 0)
    {       
        add("book_count", -1);
        ob = new ("/clone/book/blade-book");
        ob->move(me);
        return " 好吧，这本胡家刀谱你拿去用心研读吧。\n";
    }
    else
        return "你来晚了，现在刀谱已不在此处。\n";
}

string ask_hujia_book()
{
    object ob, me;

    me = this_player();
    if (me->query("family/family_name") !=
        query("family/family_name"))
    {
        command("shake");
        return "先入我门来再谈这些事。\n";
    }

    if ((int)me->query("shen") < 0)
    {
        command("sigh");
        return "你怎能走上邪路？败坏我胡家一世声名。\n";
    }

    if ((int)me->query("combat_exp") < 50000)
        return "你的武功太差，先练好武功再说。\n";

    if ((int)me->query_skill("blade", 1) < 40)
        return "你先在刀法上好好下下功夫，然后再研读刀谱总诀不迟。\n";

    if ((int)me->query_skill("hujia-daofa", 1) < 40)
        return "你先在胡家刀法上好好下下功夫，然后再研读刀谱总诀不迟。\n";

    if ((int)query("hujia_book_count") > 0)
    {       
        add("hujia_book_count", -1);
        ob = new ("/clone/book/hujia-book");
        ob->move(me);
        return " 好吧，这本刀谱总诀你拿去用心研读吧。\n";
    }
    else
        return "你来晚了，现在刀谱总诀已不在此处。\n";
}

void attempt_apprentice(object ob)
{
    object me;

    me = this_object();
    if (ob->query("name") == "胡一刀")
    {
        message_vision("$N大怒：我操！你想做我的老子啊？\n", me);
        return;
    }

    if (ob->query("name") == "胡斐")
    {
        message_vision("$N大怒：他奶奶的！你咋也起这个名字？\n", me);
        return;
    }

    if (ob->query("born_family") != "关外胡家")
    {
        message_vision("$N对$n道：你不是我们胡家的人，我怎能收你为徒？\n",
                       me, ob);
        return;
    }

    if (ob->query("detach/关外胡家") ||
        ob->query("betrayer/times"))
    {
        message_vision("$N摇摇头对$n说：你反复无常，我不能收你为徒！\n",
                       me, ob);
        return;
    }

    if (ob->query("family/family_name") &&
        ob->query("family/family_name") != me->query("family/family_name"))
    {
        message_vision("$N对$n道：你虽然是胡家的人，但你入了其他门派，我不能收你为徒！\n",
                       me, ob);
        return;
    }

    message_vision("$N感叹道：我们胡家还要靠你们来发扬光大啦！\n",
                   me, ob);
    command("recruit " + ob->query("id"));
    return;
}
