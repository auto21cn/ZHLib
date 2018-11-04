// chuanfu.c 船夫

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("船夫", ({ "chuan fu", "fu" }));
        set("gender", "男性");
        set("age", 36);
        set("long",
        "这是一个松花江上的船夫。饱经风霜的脸上透出东北人的豪爽。\n"
        );

        set("combat_exp", 10000);
        set("shen_type", 1);

	set("eff_qi",800);
	set("qi",800);
        set("max_neili", 100);
        set("neili", 100);
        set("jiali", 10);

        setup();
	carry_object("/clone/misc/cloth")->wear();
}

int accept_object(object who, object ob)
{
    object myenv ;
    if (ob->query("money_id") && ob->value() >= 100)
    {
        message_vision("船夫对$N说：好！既然这位" + RANK_D->query_respect(who) +
        "要过江，\n那我就送你上这条船吧！\n" , who);
        message_vision("船夫和$N上了船，一声「起锚」船就张帆离岸了......\n", who);
        who->move ("/d/guanwai/songhuajiang");
        tell_object(who, BLU "你在江上一路漂流.......\n" NOR ) ;
        call_out("goto_songhua",10,who) ;
       	return 1;
    }
    else  
    {
	message_vision("船夫皱眉对$N说：就这点？怎么也的一两银子吧！\n", who);
	return 0;
    }
}

void goto_songhua(object ob)
{
    if (! objectp(ob))
	return;
    tell_object(ob , "\n船很快停靠彼岸。你抬脚跨出船来。\n\n" ) ;
    ob->move ("/d/guanwai/damenkan") ;
}

