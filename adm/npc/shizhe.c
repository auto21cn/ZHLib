#include <ansi.h>
#include <command.h>
inherit NPC;

void create()
{
    set_name(HIC"安全使者"NOR, ({"xiao maike" }));
        set("title", ""HIR"［"HIG"安全使者"HIW"］"NOR"");   
    set("gender", "男性");
    set("age", 24);
    set("per", 70);
    set("str", 500000);
    set("int", 40);
    set("con", 40);
    set("dex", 40);
    set("qi",5000);
    set("jingli",5000);
    set("max_qi", 5000);
    set("max_jing", 5000);
    set("eff_jingli", 5000);
    set("jiali", 190);
    set("combat_exp", 5647645745754);
    set("shen", 25000);
    set("no_get",1);
    setup();
}
void init()
{object me;
::init();
        if( interactive(me = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, me);
        }
}
void greeting(object ob)
{
                object me;
                me=this_player();
        if (!ob || !present(ob, environment())) return;
        if(ob->query("id")=="gongping zi") {
           ob->revive();            
                     ob->set("eff_qi",ob->query("max_qi")); 
                    ob->set("eff_jing",ob->query("max_jing"));        
                    ob->set("jing",ob->query("max_jing"));        
                     ob->set("qi",ob->query("max_qi")); 
             ob->move("/d/city/leitai");
}
        if(ob->query_temp("disabled")){
                        message("vision", HIC "安全使者在你头你一按，你感觉舒服极了。\n" NOR,ob);

                        ob->revive();           
                        ob->set("eff_qi",ob->query("max_qi"));
                        ob->set("eff_jing",ob->query("max_jing"));              


                        ob->add("qi",50);
                        ob->add("jing",10);
}
             return ;
}

void unconcious()
{
        say( HIC"安全使者说道：“想搞我没那么容易。”说完就从怀里拿出一颗天王保命丸塞进嘴里嚼了起来。\n"NOR);
        say( HIC"片刻之间，安全使者又恢复了精神，“嘿嘿”奸笑了两声。\n"NOR);
        revive();
        set("eff_qi", query("max_qi"));
        set("qi", query("max_qi"));
        set("eff_jing", query("max_jing"));
        set("jing", query("max_jing"));
        set("jingli", query("eff_jingli"));
remove_all_enemy(1);
}
void die()
{
        unconcious();
}
