MUDB��<l*=� include/globals.h include/net/macros.h include/mudlib.h include/net/daemons.h include/net/dns.h include/net/daemons.h include/net/daemons.h include/net/macros.h ' adm/daemons/network/services/remote_q.c�  ��        d   �  0��������  �  �  $  $  $  �  �  �  �  ����        "    '     < �    	
zƇ .;  ]<� .�B;B    	
z�^^ ^^;�^^;^^;^^;^^ ..�Bh$ �Bh .�B  �B�B �B�B�B ]<� .�B� . !�B�A "$; B##;AA .%�&+ . �    �      ȟ  �                                 	   
                            @    @       ��(�0O�K�OY�������PX`� �8ڷ��0{q �~PɁH�B��`x�07h7p��D`������~���H���H�<X�@����s        ��       feature/dbase.c feature/clean_up.c' adm/daemons/network/services/remote_q.c include/globals.h include/net/macros.h include/mudlib.h include/net/daemons.h include/net/dns.h /adm/daemons/network/dns_master query_mud_name     . query_mud_info HOSTADDRESS PORTUDP @@@remote_q||NAME:
 ||PORTUDP: query_udp_port	 ||TARGET:	 ||ASKWIZ:
 ||CHANNEL: ||EMOTE: @@@
 send_udp NAME$ /adm/daemons/network/services/ping_q send_ping_q /adm/daemons/emoted ASKWIZ EMOTE TARGET do_intermud_emote CHANNEL /adm/daemons/channeld
 do_channel& /adm/daemons/network/services/gchannel gchannel send_msg Root
 channel_id create send_remote_q incoming_request� � $    �                    5        '  0  '������$�����������
����
�  