// /u/haiyan/hybook.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("海燕的笔记本", ({ "board" }) );
        set("location", "/u/haiyan/workroom");
        set("board_id", "hybook");
        set("long", "这是海燕平时记录的一些学习心得。\n" );
	setup();
        set("capacity", 100);
	replace_program(BULLETIN_BOARD);
}

