MUDB��<l*=� include/globals.h include/net/macros.h include/mudlib.h include/net/daemons.h include/net/dns.h include/net/daemons.h include/net/daemons.h include/net/services.h & adm/daemons/network/services/gwizmsg.c�  ��	        d   R�  ��`�����  �  <  �  �  �  �  �  �  �  ����        �    5     �.th$ uh$ u�/h .	 ]
 ];];]<�]<w]� ��B    z�$     z� �� ��B<B]	<	�h$ ��B<B�h$ ��B<BB
ch g �B�B    z�^^ ^^<z^^<^^<^^< ^<  ^^ #� .uh$ u�/ .�BX�B    z� .�B ]<h$  �Bwh$ !�B h "#�B�B .�B�B� $�B  �B%^�B^^&�B^]  �B%^�B^'^&�B^]*()>��B<B �B�B+    z�^,^<^-^�B^^ ..�B� /0 �B�BB+  /1.�B �B�BB+ 243&�B$�B .2m�    	h�   @P�  C                         	  
                     @    @      ��	(�`�@�����X�@����'(����(���P ��������E (�< 	x�@-���� F�' ��*Pr��* 8� ��`�`�H�0:p���"������������	H��qM	        �%�        feature/clean_up.c feature/dbase.c& adm/daemons/network/services/gwizmsg.c include/globals.h include/net/macros.h include/mudlib.h include/net/daemons.h include/net/dns.h include/net/services.h Root /adm/daemons/network/dns_master
 query_muds	 query_svc |   @@@ query_mud_name   . gwizmsg HOSTADDRESS PORTUDP @@@gwizmsg||NAME:
 ||PORTUDP: query_udp_port
 ||WIZNAME: ||CNAME: ||GWIZ:
 ||CHANNEL:	 ||EMOTE:1 @@@
 send_udp NAME query_mud_info WIZNAME dns_mudp$ /adm/daemons/network/services/ping_q send_ping_q EMOTE @ GWIZ :  dns_fake Gwiz: %s %s
%s aux_log @@@warning||NAME: ||MSG: Fake gwiz msg:  ||FAKEHOST: CNAME
 channel_id %s@%s	 %s(%s@%s) /adm/daemons/channeld gwiz
 do_channel create send_msg incoming_request� � $    �                    5          a  ���	�	�����V�
������$����������(���
���� $
	  