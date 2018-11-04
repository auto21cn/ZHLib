//Room: qunyulou.c



#include <ansi.h>



inherit ROOM;



int check_container(object ob);



void create()

{

        set("short", "群玉楼");

        set("long", 

"群玉楼是长安城首屈一指的大妓院。这里不是普通人能来的地方，\n"

"如果你不是富甲一方的财主，如果你不是雄霸一方的帮主掌门，如果你\n"

"不是王公贵族，就连进这个门也别想。楼中雇的打手便有四名在这儿守\n"

"着，不是有头有脸的见了这阵仗早就绕开了去。大门贴着告示(gaoshi)\n"

"一张，又高挂两幅长联：\n"

HIR"             销"HIG"              春\n\n"NOR

HIR"             魂"HIG"              色\n\n"NOR

HIR"             蚀"HIG"              无\n\n"NOR

HIR"             骨"HIG"              边\n"NOR  	

        );

        set("exits", ([ /* sizeof() == 2 */

        	"north" : __DIR__"qixiang4",

        	"south" : __DIR__"qunyulou1",

        ]));

        set("item_desc", ([

        	"gaoshi": HIY @TEXT

规定:

１．不可以带武器上楼。

２．不许闹事，否则后果自负。

TEXT NOR

        ]) );

        set("objects", ([

        	__DIR__"npc/dashou" : 4,

        ]) );



        set("NONPC",1);

        setup();

}




