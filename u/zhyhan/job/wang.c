#include <ansi.h>
inherit NPC;
int ask_job();
int ask_peichang();

void create()
{
        set_name("王元霸", ({ "wang yuanba", "wang", "yuanba" }));
        set("nickname",HIY "金刀" NOR);
        set("gender", "男性");
        set("age", 45);
        set("long", "他就是赫赫有名镖师－－王元霸。\n");

        set("combat_exp", 300000);
        set("shen_type", 1);

        set("max_force", 500);
        set("force", 500);
        set("jiali", 10);

        set_skill("force", 40);
        set_skill("sword", 50);
        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_skill("parry", 50);

        set("inquiry", ([
                "赔偿" : (:ask_peichang:),
                "job" : (:ask_job:),
        ]) );


        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        set_temp("apply/damage", 15);

        setup();
        carry_object(__DIR__"obj/gangjian")->wield();
        carry_object(__DIR__"obj/jinduan")->wear();
}
int ask_job()
{
        object me = this_player(), ob; 
        
        if (file_name(environment(this_object())) !="/d/luoyang/wang") {
                command("shrug");
                command("whisper "+me->query("id")+" 不在王家，我无法调动镖师啊");
                return 1;
                }                               

        if (me->query("combat_exp") < 2500000) {
                command("say "+ me->query("name")+"真不知廉耻，这点身手还来要差使？！");
                return 1;
                }
       
        if (me->query("combat_exp") > 50000000) {
                command("say "+ me->query("name")+"大侠，您名声太大了，我们小镖局可请不起你了！");
                return 1;
                }

        if (me->query("quest2/yunbiao")==1) {
                command("whisper "+me->query("id")+" 我不是叫你护送一位镖师吗？你不保护镖头，回来做什么？");
                return 1;
                }
        me->set("quest2/yunbiao",1);
        ob = new(__DIR__"biaotou");
        ob->move(environment(me));
        ob->set_temp("owner/id", me->query("id"));
        ob->set("combat_exp", me->query("combat_exp"));

        ob->set("max_qi",me->query("max_qi") * 5);
        ob->set("eff_qi",me->query("eff_qi") * 5);
        ob->set("qi", me->query("qi") * 5); 
        ob->set("max_jing",me->query("max_jing") * 5);
        ob->set("eff_jing",me->query("eff_jing") * 5);
        ob->set("jing", me->query("jing") * 5);
        ob->set("max_neili",me->query("max_neili"));
        ob->set("neili",me->query("neili"));
        ob->set("max_jingli",me->query("max_jingli"));
        ob->set("jingli",me->query("jingli"));
        ob->set("jiali",me->query("jiali"));
        ob->set_skill("force",me->query_skill("force"));
        ob->set_skill("dodge",me->query_skill("force"));
        ob->set_skill("parry",me->query_skill("force"));
        ob->set_skill("sword",me->query_skill("force"));
        ob->set_skill("taiji-quan",me->query_skill("unarmed"));
        ob->set_skill("tiyunzong",me->query_skill("unarmed"));
        ob->set_skill("taiji-shengong",me->query_skill("unarmed"));
        ob->set_skill("taiji-jian",me->query_skill("unarmed"));
        ob->map_skill("force", "taiji-shengong");
        ob->map_skill("sword", "taiji-jian");
        ob->map_skill("parry", "taiji-quan");
        ob->map_skill("dodge", "tiyunzong");
        if(random(2)==0){
                command("whisper "+me->query("id")+" "+ RANK_D->query_respect(me) +"来得正好，我有一宗镖要运到「福威镖局 —— 总镖头」林震南手中。");
       command("chat "+ me->query("name") + "替老夫运镖到福威镖局，各路英雄豪杰给点薄面，多多关照。");
                ob->set_temp("fuzhou",1);
                }
        else    {
                command("whisper "+me->query("id")+" " + RANK_D->query_respect(me) +"来得正好，我有一宗镖要运到「铁公鸡」钱眼开手中。");
       command("chat "+ me->query("name") + "替老夫运镖到扬州钱庄，各路英雄豪杰给点薄面，多多关照。");
                ob->set_temp("yangzhou",1);
                }         
                command("whisper "+me->query("id")+" 你就同这位镖师一同前往吧。");
                return 1;
}       

int ask_peichang()
{
        object me = this_player();
        int kar, dot, balance;
        kar = (20 + random(20));
        dot = (50 - random(kar)) * (50 - random(kar)) * 250;
        balance = me->query("balance");
        
        if (me->query("quest2/yunbiao"))  {
                command("sigh");
                me->set("quest2/yunbiao",0);                
                command("nod");
        command("tell " + me->query("id") + " 你的赔偿手续已经办妥了。");
                }
        return 1;
}
                

