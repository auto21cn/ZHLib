

#include <ansi.h>
#include <login.h> 
inherit NPC;


void create()
{
     //  reload("guanshi");
       set_name("李师悯", ({"guanshi","guan shi"}));
       set("gender", "男性");
       set("title", HIC"银行管事"NOR);
       set("combat_exp", 100000);
       set("age", 26);
       set("per", 24);
       set("attitude", "friendly");
       set("long","李师悯原本文武双全，但因名字和大唐国唐太宗的名字谐音，\n所以得不到朝廷的重用。后来被李作乐所赏识，提为银行管事。\n");
       set("shen_type", 1);
      
       set("max_qi", 1100);
       set("max_jing", 1100);
       set("qi", 1100);
       set("jing", 1100);
       set("neili", 2300);
       set("max_neili", 1200);
       set("jiali", 80);
       set("max_jingli", 1200);
       set("jingli", 2300);
       set("combat_exp", 800000);

       set_skill("literate", 500);
       set_skill("unarmed", 500);
       set_skill("dodge", 500);
       set_skill("parry", 500);

       
       setup();


}

void init()
{
        object ob;

        ::init();
        set("chat_chance", 12);
        set("inquiry", ([
                "name" : "在下不才，正是李师悯。",
                "here" : "这是由饮风客栈天下有雪所开的潜能银行。\n",
                "dvunix" : "我们公子武功虽然不是很好，可是他的朋友遍天下，这会儿不知道又到哪个朋友那去云游了。不过我们少奶奶在家。\n",
                "天下有雪" : "我们公子武功虽然不是很好，可是他的朋友遍天下，这会儿不知道又到哪个朋友那去云游了。不过我们少奶奶在家。\n",
                "公子" : "我们公子武功虽然不是很好，可是他的朋友遍天下，这会儿不知道又到哪个朋友那去云游了。不过我们少奶奶在家。\n",
                "xueer" : "我们少奶奶在后面歇着呢！",
                "雪儿" : "我们少奶奶在后面歇着呢！",
                "少奶奶" : "我们少奶奶在后面歇着呢！",
   ]) );

        set("chat_msg", ({
                "李师悯高声说：我们少爷最爱结交朋友了。\n",   
                "李师悯上上下下打量了你几眼。\n",
                "李师悯高声说：外面跑的老妖精，很多都是我们公子的朋友。\n",
                "李师悯高声说：江湖上的朋友都会给我们少爷一些薄面。所以很少有人来捣乱。\n",
                "李师悯骄傲的说道：提起我们哦公子，可以说是无人不晓。连当今皇上都跟他很熟。\n"
                
       }) );
      
    ob = this_player();
    ::init();
    if (userp(ob))
    if(random(10)>3)
       remove_call_out("greeting");
       call_out("greeting", 1, ob);
}

void accept_kill(object me)
{       

        me->add("daoluan",1);
        command("sigh2");
        command("chat 救命啊！");
          
        me->add("daoluan",1);
        me->save();
        return;

}

void greeting(object ob)
{
if( !ob || environment(ob) != environment() ) return;
if(!userp(ob)) return;
message_vision( "$N对$n抱拳行礼.\n\n",this_object(),ob );
if(ob->query("id")=="yuchang")
  {
          command("say 噢，"+ob->query("name")+"公子,您回来了。");
  }
else
  {
command("say 这位" + RANK_D->query_respect(ob)
+ "，又要出去冒险，所以来存潜能吧？\n");
if (ob->query("gender") == "男性"||ob->query("gender") == "无性")
    {
        command("say "+"这位" + RANK_D->query_respect(ob)+"，欢迎你有空来坐坐。");
        command("xixi");
    }
else
    {
        command("say 平常总是有男子来我这，不想今日却来了一位" + RANK_D->query_respect(ob)+"\n");
        command("say 看来我下辈子的幸福有望了！\n"); 
        command("grin");
    }
  }
}

