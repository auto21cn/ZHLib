// zazhi.c
#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIG "〖地狱〗杂志第三期总目录" NOR, ({ "zazhi mulu","zazhi","mulu" }));
	set_weight(100);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "册");
		set("long",HIW 
"这是2000年第三期"HIG"〖地狱〗"HIW"杂志的目录清单，你可以(kankan mulu)
从而可以从上面了解到本期"HIG"〖地狱〗"HIW"杂志的大概内容。阅读本期杂志详
细内容请到http://ultrahell.yeah.net"HIG"〖地狱〗"HIW"杂志社总部。\n" NOR);
		set("value", 1);
		set("material", "paper");
              set("no_sell", 1);		              
	}
   setup ();
}

void init()
{
	if( this_player() == environment() )
	{
		add_action("do_kankan", "kankan");
	}
}

int do_kankan(string arg)
{
	object me, magazine;
	
	if ( !arg )
	{
		return notify_fail("什么？\n");
	}

	me = this_player();

	if ( arg == "mulu" )
	{
		tell_object(me,HIW "本期〖地狱〗杂志目录：\n"
		                   "地狱之窗:《新手不该去的地方》 | 《四大宗师位置》\n"
		                   "泥友心声:《PKER心声》 | 《“高人”》 | 《倚天词》\n"
		                   "飞来文:《浅论mud中以及由此延伸到网络中的男女关系》\n"
		                   "长篇故事:《终极地狱之黑客事件》\n" NOR);
	}

	return 1;
}
