// /clone/board/wiz_b.c

inherit BULLETIN_BOARD;

void create()
{
	set_name("巫师留言簿", ({ "board" }) );
        set("location", "/u/sun/workroom");
	set("board_id", "wiz_b");
        set("long", "这是一个末日的留言板。\n" );
	setup();
	set("capacity", 1000);
	replace_program(BULLETIN_BOARD);
}

