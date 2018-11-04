// attribute.c
// From ES2
// Modified by Xiang for XKX (12/15/95)
// Updated by Lonely@nitan(1)

#include <dbase.h>
#include <skill.h>

int query_str()
{
        mapping sk;
        int tat;
        int str;
        int improve = 0;
        int lx = 0;

        tat = query("tattoo/tattoo_str");
        str = query("str");
        str += query("improve/str");
        
        if (! mapp(sk = query_skills()))
                return str;

        improve = (int)sk["unarmed"];
        if (improve < (int) sk["cuff"]) improve = sk["cuff"];
        if (improve < (int) sk["finger"]) improve = sk["finger"];
        if (improve < (int) sk["strike"]) improve = sk["strike"];
        if (improve < (int) sk["hand"]) improve = sk["hand"];
        if (improve < (int) sk["claw"]) improve = sk["claw"];

        lx = (int)sk["longxiang-banruo"] / 30;
        if (lx >= 13) lx = 15;

        return str + (improve / 10) + lx + query_temp("apply/str");
}

int query_int()
{
        mapping sk;
        int tat;
        int str;
        int improve = 0;

        tat = query("tattoo/tattoo_int");
        str = query("int");
        str+= query("improve/int");
        
        if (! mapp(sk = query_skills()))
                return str;

        improve = (int)sk["literate"];

        return str + (improve / 10) + query_temp("apply/int");
}

int query_con()
{
        mapping sk;
        int tat;
        int str;
        int improve = 0;

        tat = query("tattoo/tattoo_con");
        str = query("con");
        str += query("improve/con");
        
        if (! mapp(sk = query_skills()))
                return str;

        improve = (int)sk["force"];

        return str + (improve / 10) + query_temp("apply/con");
}

int query_dex()
{
        mapping sk;
        int tat;
        int str;
        int improve = 0;

        tat = query("tattoo/tattoo_dex");
        str = query("dex");
        str += query("improve/dex");
        
        if (! mapp(sk = query_skills()))
                return str;

        improve = (int)sk["dodge"];

        return str + (improve / 10) + query_temp("apply/dex");
}

int query_per()
{
        int per;
        int age;
        int tat;
        int ac;

        tat = query("tattoo/tattoo_per");
        per = (int)query("per") + query_temp("apply/per");
        if (query("special_skill/youth"))
                return per;

        age = query("age");

        ac = query_skill("art-cognize", 1);
        if (ac < 100)
        {
                if (age > 70) per -= 6; else
                if (age > 60) per -= 5; else
                if (age > 50) per -= 4; else
                if (age > 40) per -= 3; else
                if (age > 30) per -= 2;
        }

        per += ac / 20;
        return per;
}


