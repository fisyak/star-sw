#!/usr/bin/perl
use strict;
use warnings;
our @Runs = ( # onl CURRENT | SortRun.pl 
'0000'=> {trig=>'2007Production1',       	field => 'FF',	first=> '8093046',	 last => '8093046',	 list => '',  beginTime => '20070403.203735'}, # 	2007-04-03	20:37:35	2007-04-04	05:38:54	timestamp = 2007Production1_FF
'0001'=> {trig=>'2007Production1',       	field => 'FF',	first=> '8094008',	 last => '8094009',	 list => '',  beginTime => '20070404.053854'}, # 	2007-04-04	05:38:54	2007-04-05	01:54:10
'0002'=> {trig=>'2007Production1',       	field => 'FF',	first=> '8094081',	 last => '8094082',	 list => '',  beginTime => '20070405.015410'}, # 	2007-04-05	01:54:10	2007-04-05	01:58:12
'0003'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8094083',	 last => '8094083',	 list => '',  beginTime => '20070405.015812'}, # 	2007-04-05	01:58:12	2007-04-05	04:28:54	timestamp = 2007Production2_FF
'0004'=> {trig=>'2007Production1',       	field => 'FF',	first=> '8095003',	 last => '8095003',	 list => '',  beginTime => '20070405.042854'}, # 	2007-04-05	04:28:54	2007-04-05	10:58:39	timestamp = 2007Production1_FF
'0005'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8095063',	 last => '8095063',	 list => '',  beginTime => '20070405.105839'}, # 	2007-04-05	10:58:39	2007-04-05	11:38:05	timestamp = 2007Production2_FF
'0006'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8095065',	 last => '8095066',	 list => '',  beginTime => '20070405.113805'}, # 	2007-04-05	11:38:05	2007-04-05	13:13:27
'0007'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8095075',	 last => '8095075',	 list => '',  beginTime => '20070405.131327'}, # 	2007-04-05	13:13:27	2007-04-05	19:54:29
'0008'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8095148',	 last => '8095148',	 list => '',  beginTime => '20070405.195429'}, # 	2007-04-05	19:54:29	2007-04-05	20:14:18
'0009'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8095150',	 last => '8095150',	 list => '',  beginTime => '20070405.201418'}, # 	2007-04-05	20:14:18	2007-04-05	21:18:32
'0010'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8095159',	 last => '8095162',	 list => '',  beginTime => '20070405.211832'}, # 	2007-04-05	21:18:32	2007-04-05	21:42:07
'0011'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8095164',	 last => '8095167',	 list => '',  beginTime => '20070405.214207'}, # 	2007-04-05	21:42:07	2007-04-05	21:57:10
'0012'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8095169',	 last => '8095172',	 list => '',  beginTime => '20070405.215710'}, # 	2007-04-05	21:57:10	2007-04-05	22:19:00
'0013'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8095174',	 last => '8095189',	 list => '',  beginTime => '20070405.221900'}, # 	2007-04-05	22:19:00	2007-04-06	01:42:37
'0014'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8095212',	 last => '8095212',	 list => '',  beginTime => '20070406.014237'}, # 	2007-04-06	01:42:37	2007-04-06	01:49:21
'0015'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8095214',	 last => '8095216',	 list => '',  beginTime => '20070406.014921'}, # 	2007-04-06	01:49:21	2007-04-06	02:45:32
'0016'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8095228',	 last => '8095231',	 list => '',  beginTime => '20070406.024532'}, # 	2007-04-06	02:45:32	2007-04-06	03:57:57
'0017'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8095237',	 last => '8095237',	 list => '',  beginTime => '20070406.035757'}, # 	2007-04-06	03:57:57	2007-04-06	04:51:12
'0018'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8096006',	 last => '8096006',	 list => '',  beginTime => '20070406.045112'}, # 	2007-04-06	04:51:12	2007-04-06	06:09:36
'0019'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8096010',	 last => '8096010',	 list => '',  beginTime => '20070406.060936'}, # 	2007-04-06	06:09:36	2007-04-06	08:32:48
'0020'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8096019',	 last => '8096022',	 list => '',  beginTime => '20070406.083248'}, # 	2007-04-06	08:32:48	2007-04-06	09:29:28
'0021'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8096024',	 last => '8096024',	 list => '',  beginTime => '20070406.092928'}, # 	2007-04-06	09:29:28	2007-04-06	10:08:59
'0022'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8096026',	 last => '8096031',	 list => '',  beginTime => '20070406.100859'}, # 	2007-04-06	10:08:59	2007-04-06	13:54:14
'0023'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8096039',	 last => '8096040',	 list => '',  beginTime => '20070406.135414'}, # 	2007-04-06	13:54:14	2007-04-06	19:12:48
'0024'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8096088',	 last => '8096088',	 list => '',  beginTime => '20070406.191248'}, # 	2007-04-06	19:12:48	2007-04-06	19:38:16
'0025'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8096090',	 last => '8096090',	 list => '',  beginTime => '20070406.193816'}, # 	2007-04-06	19:38:16	2007-04-06	19:46:38
'0026'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8096092',	 last => '8096092',	 list => '',  beginTime => '20070406.194638'}, # 	2007-04-06	19:46:38	2007-04-06	21:09:46
'0027'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8096105',	 last => '8096106',	 list => '',  beginTime => '20070406.210946'}, # 	2007-04-06	21:09:46	2007-04-06	21:22:26
'0028'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8096107',	 last => '8096108',	 list => '',  beginTime => '20070406.212226'}, # 	2007-04-06	21:22:26	2007-04-06	21:31:03	timestamp = 2007ProductionMinBias_FF
'0029'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8096110',	 last => '8096110',	 list => '',  beginTime => '20070406.213103'}, # 	2007-04-06	21:31:03	2007-04-06	21:58:50
'0030'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8096115',	 last => '8096115',	 list => '',  beginTime => '20070406.215850'}, # 	2007-04-06	21:58:50	2007-04-06	22:02:52
'0031'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8096118',	 last => '8096118',	 list => '',  beginTime => '20070406.220252'}, # 	2007-04-06	22:02:52	2007-04-06	22:39:39
'0032'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8096120',	 last => '8096121',	 list => '',  beginTime => '20070406.223939'}, # 	2007-04-06	22:39:39	2007-04-07	00:18:13
'0033'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8096123',	 last => '8096123',	 list => '',  beginTime => '20070407.001813'}, # 	2007-04-07	00:18:13	2007-04-07	04:33:07
'0034'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8097009',	 last => '8097009',	 list => '',  beginTime => '20070407.043307'}, # 	2007-04-07	04:33:07	2007-04-07	04:39:31	timestamp = 2007Production2_FF
'0035'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8097011',	 last => '8097012',	 list => '',  beginTime => '20070407.043931'}, # 	2007-04-07	04:39:31	2007-04-07	04:54:08
'0036'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8097014',	 last => '8097014',	 list => '',  beginTime => '20070407.045408'}, # 	2007-04-07	04:54:08	2007-04-07	05:11:54
'0037'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8097018',	 last => '8097018',	 list => '',  beginTime => '20070407.051154'}, # 	2007-04-07	05:11:54	2007-04-07	05:34:53
'0038'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8097021',	 last => '8097021',	 list => '',  beginTime => '20070407.053453'}, # 	2007-04-07	05:34:53	2007-04-07	05:57:48
'0039'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8097023',	 last => '8097024',	 list => '',  beginTime => '20070407.055748'}, # 	2007-04-07	05:57:48	2007-04-07	06:55:50
'0040'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8097027',	 last => '8097028',	 list => '',  beginTime => '20070407.065550'}, # 	2007-04-07	06:55:50	2007-04-07	07:39:30
'0041'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8097031',	 last => '8097031',	 list => '',  beginTime => '20070407.073930'}, # 	2007-04-07	07:39:30	2007-04-07	08:25:57
'0042'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8097032',	 last => '8097034',	 list => '',  beginTime => '20070407.082557'}, # 	2007-04-07	08:25:57	2007-04-07	09:52:54	timestamp = 2007ProductionMinBias_FF
'0043'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8097037',	 last => '8097037',	 list => '',  beginTime => '20070407.095254'}, # 	2007-04-07	09:52:54	2007-04-07	11:18:08
'0044'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8097047',	 last => '8097049',	 list => '',  beginTime => '20070407.111808'}, # 	2007-04-07	11:18:08	2007-04-07	16:05:54	timestamp = 2007Production2_FF
'0045'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8097070',	 last => '8097070',	 list => '',  beginTime => '20070407.160554'}, # 	2007-04-07	16:05:54	2007-04-07	16:19:10	timestamp = 2007ProductionMinBias_FF
'0046'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8097071',	 last => '8097071',	 list => '',  beginTime => '20070407.161910'}, # 	2007-04-07	16:19:10	2007-04-07	16:41:09	timestamp = 2007Production2_FF
'0047'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8097073',	 last => '8097074',	 list => '',  beginTime => '20070407.164109'}, # 	2007-04-07	16:41:09	2007-04-07	17:29:35
'0048'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8097078',	 last => '8097079',	 list => '',  beginTime => '20070407.172935'}, # 	2007-04-07	17:29:35	2007-04-07	18:37:37
'0049'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8097084',	 last => '8097086',	 list => '',  beginTime => '20070407.183737'}, # 	2007-04-07	18:37:37	2007-04-07	19:41:54
'0050'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8097088',	 last => '8097091',	 list => '',  beginTime => '20070407.194154'}, # 	2007-04-07	19:41:54	2007-04-07	20:39:10	timestamp = 2007ProductionMinBias_FF
'0051'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8097094',	 last => '8097098',	 list => '',  beginTime => '20070407.203910'}, # 	2007-04-07	20:39:10	2007-04-07	21:07:06
'0052'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8097100',	 last => '8097101',	 list => '',  beginTime => '20070407.210706'}, # 	2007-04-07	21:07:06	2007-04-08	03:26:09
'0053'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8097121',	 last => '8097124',	 list => '',  beginTime => '20070408.032609'}, # 	2007-04-08	03:26:09	2007-04-08	04:24:49	timestamp = 2007Production2_FF
'0054'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8098001',	 last => '8098003',	 list => '',  beginTime => '20070408.042449'}, # 	2007-04-08	04:24:49	2007-04-08	05:17:56
'0055'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8098007',	 last => '8098007',	 list => '',  beginTime => '20070408.051756'}, # 	2007-04-08	05:17:56	2007-04-08	05:33:51
'0056'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8098009',	 last => '8098011',	 list => '',  beginTime => '20070408.053351'}, # 	2007-04-08	05:33:51	2007-04-08	07:09:54
'0057'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8098012',	 last => '8098013',	 list => '',  beginTime => '20070408.070954'}, # 	2007-04-08	07:09:54	2007-04-08	08:29:30	timestamp = 2007ProductionMinBias_FF
'0058'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8098015',	 last => '8098016',	 list => '',  beginTime => '20070408.082930'}, # 	2007-04-08	08:29:30	2007-04-09	04:01:55
'0059'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8099001',	 last => '8099001',	 list => '',  beginTime => '20070409.040155'}, # 	2007-04-09	04:01:55	2007-04-09	04:39:10	timestamp = 2007Production2_FF
'0060'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8099005',	 last => '8099005',	 list => '',  beginTime => '20070409.043910'}, # 	2007-04-09	04:39:10	2007-04-09	05:03:05
'0061'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8099007',	 last => '8099011',	 list => '',  beginTime => '20070409.050305'}, # 	2007-04-09	05:03:05	2007-04-09	06:33:12
'0062'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8099012',	 last => '8099012',	 list => '',  beginTime => '20070409.063312'}, # 	2007-04-09	06:33:12	2007-04-09	06:49:37	timestamp = 2007ProductionMinBias_FF
'0063'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8099014',	 last => '8099019',	 list => '',  beginTime => '20070409.064937'}, # 	2007-04-09	06:49:37	2007-04-09	08:10:12
'0064'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8099021',	 last => '8099023',	 list => '',  beginTime => '20070409.081012'}, # 	2007-04-09	08:10:12	2007-04-10	06:33:25
'0065'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8100011',	 last => '8100011',	 list => '',  beginTime => '20070410.063325'}, # 	2007-04-10	06:33:25	2007-04-10	06:45:27	timestamp = 2007Production2_FF
'0066'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8100013',	 last => '8100014',	 list => '',  beginTime => '20070410.064527'}, # 	2007-04-10	06:45:27	2007-04-10	07:02:24
'0067'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8100016',	 last => '8100016',	 list => '',  beginTime => '20070410.070224'}, # 	2007-04-10	07:02:24	2007-04-10	07:14:59
'0068'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8100021',	 last => '8100022',	 list => '',  beginTime => '20070410.071459'}, # 	2007-04-10	07:14:59	2007-04-10	07:28:14
'0069'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8100025',	 last => '8100026',	 list => '',  beginTime => '20070410.072814'}, # 	2007-04-10	07:28:14	2007-04-10	07:52:19
'0070'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8100029',	 last => '8100029',	 list => '',  beginTime => '20070410.075219'}, # 	2007-04-10	07:52:19	2007-04-10	08:11:35
'0071'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8100035',	 last => '8100035',	 list => '',  beginTime => '20070410.081135'}, # 	2007-04-10	08:11:35	2007-04-10	08:24:51
'0072'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8100039',	 last => '8100039',	 list => '',  beginTime => '20070410.082451'}, # 	2007-04-10	08:24:51	2007-04-10	08:37:46
'0073'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8100042',	 last => '8100048',	 list => '',  beginTime => '20070410.083746'}, # 	2007-04-10	08:37:46	2007-04-10	09:26:14
'0074'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8100054',	 last => '8100056',	 list => '',  beginTime => '20070410.092614'}, # 	2007-04-10	09:26:14	2007-04-10	09:38:09
'0075'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8100059',	 last => '8100061',	 list => '',  beginTime => '20070410.093809'}, # 	2007-04-10	09:38:09	2007-04-10	09:48:28
'0076'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8100063',	 last => '8100069',	 list => '',  beginTime => '20070410.094828'}, # 	2007-04-10	09:48:28	2007-04-10	10:32:20
'0077'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8100075',	 last => '8100076',	 list => '',  beginTime => '20070410.103220'}, # 	2007-04-10	10:32:20	2007-04-10	10:41:29	timestamp = 2007ProductionMinBias_FF
'0078'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8100079',	 last => '8100079',	 list => '',  beginTime => '20070410.104129'}, # 	2007-04-10	10:41:29	2007-04-10	10:50:46
'0079'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8100082',	 last => '8100082',	 list => '',  beginTime => '20070410.105046'}, # 	2007-04-10	10:50:46	2007-04-10	11:06:23
'0080'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8100084',	 last => '8100085',	 list => '',  beginTime => '20070410.110623'}, # 	2007-04-10	11:06:23	2007-04-10	11:16:46
'0081'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8100089',	 last => '8100090',	 list => '',  beginTime => '20070410.111646'}, # 	2007-04-10	11:16:46	2007-04-10	11:26:24
'0082'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8100093',	 last => '8100094',	 list => '',  beginTime => '20070410.112624'}, # 	2007-04-10	11:26:24	2007-04-10	12:02:54
'0083'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8100100',	 last => '8100100',	 list => '',  beginTime => '20070410.120254'}, # 	2007-04-10	12:02:54	2007-04-10	12:32:07
'0084'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8100107',	 last => '8100107',	 list => '',  beginTime => '20070410.123207'}, # 	2007-04-10	12:32:07	2007-04-10	13:00:01
'0085'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8100117',	 last => '8100119',	 list => '',  beginTime => '20070410.130001'}, # 	2007-04-10	13:00:01	2007-04-10	15:32:49
'0086'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8100145',	 last => '8100145',	 list => '',  beginTime => '20070410.153249'}, # 	2007-04-10	15:32:49	2007-04-10	15:57:25	timestamp = 2007Production2_FF
'0087'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8100153',	 last => '8100155',	 list => '',  beginTime => '20070410.155725'}, # 	2007-04-10	15:57:25	2007-04-10	16:38:01
'0088'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8100158',	 last => '8100160',	 list => '',  beginTime => '20070410.163801'}, # 	2007-04-10	16:38:01	2007-04-10	17:56:18
'0089'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8100170',	 last => '8100170',	 list => '',  beginTime => '20070410.175618'}, # 	2007-04-10	17:56:18	2007-04-10	18:09:23
'0090'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8100172',	 last => '8100172',	 list => '',  beginTime => '20070410.180923'}, # 	2007-04-10	18:09:23	2007-04-12	06:20:07	timestamp = 2007ProductionMinBias_FF
'0091'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8102009',	 last => '8102012',	 list => '',  beginTime => '20070412.062007'}, # 	2007-04-12	06:20:07	2007-04-12	07:04:13	timestamp = 2007Production2_FF
'0092'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8102014',	 last => '8102014',	 list => '',  beginTime => '20070412.070413'}, # 	2007-04-12	07:04:13	2007-04-12	07:39:27
'0093'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8102016',	 last => '8102016',	 list => '',  beginTime => '20070412.073927'}, # 	2007-04-12	07:39:27	2007-04-12	07:50:14
'0094'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8102018',	 last => '8102019',	 list => '',  beginTime => '20070412.075014'}, # 	2007-04-12	07:50:14	2007-04-12	08:07:35
'0095'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8102021',	 last => '8102021',	 list => '',  beginTime => '20070412.080735'}, # 	2007-04-12	08:07:35	2007-04-12	08:11:30
'0096'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8102023',	 last => '8102026',	 list => '',  beginTime => '20070412.081130'}, # 	2007-04-12	08:11:30	2007-04-12	09:06:19
'0097'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8102029',	 last => '8102029',	 list => '',  beginTime => '20070412.090619'}, # 	2007-04-12	09:06:19	2007-04-12	09:51:45
'0098'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8102034',	 last => '8102036',	 list => '',  beginTime => '20070412.095145'}, # 	2007-04-12	09:51:45	2007-04-12	10:47:31	timestamp = 2007ProductionMinBias_FF
'0099'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8102045',	 last => '8102045',	 list => '',  beginTime => '20070412.104731'}, # 	2007-04-12	10:47:31	2007-04-12	10:57:39
'0100'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8102047',	 last => '8102047',	 list => '',  beginTime => '20070412.105739'}, # 	2007-04-12	10:57:39	2007-04-12	11:03:38
'0101'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8102049',	 last => '8102051',	 list => '',  beginTime => '20070412.110338'}, # 	2007-04-12	11:03:38	2007-04-12	11:54:48
'0102'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8102053',	 last => '8102053',	 list => '',  beginTime => '20070412.115448'}, # 	2007-04-12	11:54:48	2007-04-12	12:18:53
'0103'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8102055',	 last => '8102057',	 list => '',  beginTime => '20070412.121853'}, # 	2007-04-12	12:18:53	2007-04-12	12:52:32
'0104'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8102059',	 last => '8102059',	 list => '',  beginTime => '20070412.125232'}, # 	2007-04-12	12:52:32	2007-04-12	13:09:56
'0105'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8102062',	 last => '8102062',	 list => '',  beginTime => '20070412.130956'}, # 	2007-04-12	13:09:56	2007-04-13	03:48:30
'0106'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8102113',	 last => '8102113',	 list => '',  beginTime => '20070413.034830'}, # 	2007-04-13	03:48:30	2007-04-13	20:09:39
'0107'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8103029',	 last => '8103029',	 list => '',  beginTime => '20070413.200939'}, # 	2007-04-13	20:09:39	2007-04-13	20:16:59	timestamp = 2007Production2_FF
'0108'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8103032',	 last => '8103033',	 list => '',  beginTime => '20070413.201659'}, # 	2007-04-13	20:16:59	2007-04-13	20:23:28
'0109'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8103034',	 last => '8103034',	 list => '',  beginTime => '20070413.202328'}, # 	2007-04-13	20:23:28	2007-04-13	22:42:11	timestamp = 2007ProductionMinBias_FF
'0110'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8103048',	 last => '8103049',	 list => '',  beginTime => '20070413.224211'}, # 	2007-04-13	22:42:11	2007-04-13	22:50:00	timestamp = 2007Production2_FF
'0111'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8103050',	 last => '8103051',	 list => '',  beginTime => '20070413.225000'}, # 	2007-04-13	22:50:00	2007-04-14	16:03:32	timestamp = 2007ProductionMinBias_FF
'0112'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8104025',	 last => '8104026',	 list => '',  beginTime => '20070414.160332'}, # 	2007-04-14	16:03:32	2007-04-14	16:18:56
'0113'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8104028',	 last => '8104028',	 list => '',  beginTime => '20070414.161856'}, # 	2007-04-14	16:18:56	2007-04-14	16:32:27
'0114'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8104029',	 last => '8104030',	 list => '',  beginTime => '20070414.163227'}, # 	2007-04-14	16:32:27	2007-04-14	16:53:53	timestamp = 2007Production2_FF
'0115'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8104032',	 last => '8104033',	 list => '',  beginTime => '20070414.165353'}, # 	2007-04-14	16:53:53	2007-04-14	17:25:22
'0116'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8104035',	 last => '8104035',	 list => '',  beginTime => '20070414.172522'}, # 	2007-04-14	17:25:22	2007-04-14	17:45:52
'0117'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8104036',	 last => '8104037',	 list => '',  beginTime => '20070414.174552'}, # 	2007-04-14	17:45:52	2007-04-14	18:02:44	timestamp = 2007ProductionMinBias_FF
'0118'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8104039',	 last => '8104040',	 list => '',  beginTime => '20070414.180244'}, # 	2007-04-14	18:02:44	2007-04-14	18:25:08	timestamp = 2007Production2_FF
'0119'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8104041',	 last => '8104042',	 list => '',  beginTime => '20070414.182508'}, # 	2007-04-14	18:25:08	2007-04-14	18:49:46	timestamp = 2007ProductionMinBias_FF
'0120'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8104043',	 last => '8104043',	 list => '',  beginTime => '20070414.184946'}, # 	2007-04-14	18:49:46	2007-04-14	19:09:54	timestamp = 2007Production2_FF
'0121'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8104044',	 last => '8104044',	 list => '',  beginTime => '20070414.190954'}, # 	2007-04-14	19:09:54	2007-04-14	19:20:27	timestamp = 2007ProductionMinBias_FF
'0122'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8104045',	 last => '8104045',	 list => '',  beginTime => '20070414.192027'}, # 	2007-04-14	19:20:27	2007-04-14	19:42:26	timestamp = 2007Production2_FF
'0123'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8104046',	 last => '8104047',	 list => '',  beginTime => '20070414.194226'}, # 	2007-04-14	19:42:26	2007-04-14	20:23:39	timestamp = 2007ProductionMinBias_FF
'0124'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8104051',	 last => '8104052',	 list => '',  beginTime => '20070414.202339'}, # 	2007-04-14	20:23:39	2007-04-14	21:09:21
'0125'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8104054',	 last => '8104055',	 list => '',  beginTime => '20070414.210921'}, # 	2007-04-14	21:09:21	2007-04-14	22:00:13
'0126'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8104059',	 last => '8104059',	 list => '',  beginTime => '20070414.220013'}, # 	2007-04-14	22:00:13	2007-04-15	00:33:13
'0127'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8104067',	 last => '8104069',	 list => '',  beginTime => '20070415.003313'}, # 	2007-04-15	00:33:13	2007-04-15	00:53:33	timestamp = 2007Production2_FF
'0128'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8104071',	 last => '8104075',	 list => '',  beginTime => '20070415.005333'}, # 	2007-04-15	00:53:33	2007-04-15	01:41:38
'0129'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8104077',	 last => '8104078',	 list => '',  beginTime => '20070415.014138'}, # 	2007-04-15	01:41:38	2007-04-15	02:28:29
'0130'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8104080',	 last => '8104080',	 list => '',  beginTime => '20070415.022829'}, # 	2007-04-15	02:28:29	2007-04-15	02:45:37
'0131'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8104082',	 last => '8104085',	 list => '',  beginTime => '20070415.024537'}, # 	2007-04-15	02:45:37	2007-04-15	04:44:18
'0132'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8105010',	 last => '8105011',	 list => '',  beginTime => '20070415.044418'}, # 	2007-04-15	04:44:18	2007-04-15	08:03:52	timestamp = 2007ProductionMinBias_FF
'0133'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8105019',	 last => '8105019',	 list => '',  beginTime => '20070415.080352'}, # 	2007-04-15	08:03:52	2007-04-15	08:23:25	timestamp = 2007Production2_FF
'0134'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8105022',	 last => '8105023',	 list => '',  beginTime => '20070415.082325'}, # 	2007-04-15	08:23:25	2007-04-15	09:54:49
'0135'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8105025',	 last => '8105026',	 list => '',  beginTime => '20070415.095449'}, # 	2007-04-15	09:54:49	2007-04-15	10:29:57
'0136'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8105028',	 last => '8105029',	 list => '',  beginTime => '20070415.102957'}, # 	2007-04-15	10:29:57	2007-04-15	12:06:20
'0137'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8105030',	 last => '8105030',	 list => '',  beginTime => '20070415.120620'}, # 	2007-04-15	12:06:20	2007-04-15	12:26:13	timestamp = 2007ProductionMinBias_FF
'0138'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8105034',	 last => '8105034',	 list => '',  beginTime => '20070415.122613'}, # 	2007-04-15	12:26:13	2007-04-15	12:37:02
'0139'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8105036',	 last => '8105037',	 list => '',  beginTime => '20070415.123702'}, # 	2007-04-15	12:37:02	2007-04-15	13:11:22
'0140'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8105041',	 last => '8105042',	 list => '',  beginTime => '20070415.131122'}, # 	2007-04-15	13:11:22	2007-04-15	17:19:43
'0141'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8105059',	 last => '8105059',	 list => '',  beginTime => '20070415.171943'}, # 	2007-04-15	17:19:43	2007-04-15	17:35:30	timestamp = 2007Production2_FF
'0142'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8105061',	 last => '8105061',	 list => '',  beginTime => '20070415.173530'}, # 	2007-04-15	17:35:30	2007-04-15	18:11:48
'0143'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8105065',	 last => '8105067',	 list => '',  beginTime => '20070415.181148'}, # 	2007-04-15	18:11:48	2007-04-15	19:51:32
'0144'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8105068',	 last => '8105071',	 list => '',  beginTime => '20070415.195132'}, # 	2007-04-15	19:51:32	2007-04-15	21:17:51	timestamp = 2007ProductionMinBias_FF
'0145'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8105073',	 last => '8105073',	 list => '',  beginTime => '20070415.211751'}, # 	2007-04-15	21:17:51	2007-04-15	21:53:20
'0146'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8105078',	 last => '8105078',	 list => '',  beginTime => '20070415.215320'}, # 	2007-04-15	21:53:20	2007-04-16	00:28:08
'0147'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8105087',	 last => '8105087',	 list => '',  beginTime => '20070416.002808'}, # 	2007-04-16	00:28:08	2007-04-16	00:42:16	timestamp = 2007Production2_FF
'0148'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8105089',	 last => '8105090',	 list => '',  beginTime => '20070416.004216'}, # 	2007-04-16	00:42:16	2007-04-16	01:43:56
'0149'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8105093',	 last => '8105100',	 list => '',  beginTime => '20070416.014356'}, # 	2007-04-16	01:43:56	2007-04-16	04:28:46
'0150'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8106001',	 last => '8106001',	 list => '',  beginTime => '20070416.042846'}, # 	2007-04-16	04:28:46	2007-04-16	05:15:42
'0151'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8106004',	 last => '8106004',	 list => '',  beginTime => '20070416.051542'}, # 	2007-04-16	05:15:42	2007-04-16	17:55:35
'0152'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8106050',	 last => '8106051',	 list => '',  beginTime => '20070416.175535'}, # 	2007-04-16	17:55:35	2007-04-16	18:20:09
'0153'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8106059',	 last => '8106059',	 list => '',  beginTime => '20070416.182009'}, # 	2007-04-16	18:20:09	2007-04-16	18:34:48
'0154'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8106061',	 last => '8106061',	 list => '',  beginTime => '20070416.183448'}, # 	2007-04-16	18:34:48	2007-04-16	18:49:55
'0155'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8106066',	 last => '8106066',	 list => '',  beginTime => '20070416.184955'}, # 	2007-04-16	18:49:55	2007-04-16	19:07:50
'0156'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8106068',	 last => '8106072',	 list => '',  beginTime => '20070416.190750'}, # 	2007-04-16	19:07:50	2007-04-16	20:12:37
'0157'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8106075',	 last => '8106076',	 list => '',  beginTime => '20070416.201237'}, # 	2007-04-16	20:12:37	2007-04-16	21:01:29
'0158'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8106078',	 last => '8106082',	 list => '',  beginTime => '20070416.210129'}, # 	2007-04-16	21:01:29	2007-04-16	22:03:59
'0159'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8106086',	 last => '8106087',	 list => '',  beginTime => '20070416.220359'}, # 	2007-04-16	22:03:59	2007-04-16	23:25:43
'0160'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8106090',	 last => '8106090',	 list => '',  beginTime => '20070416.232543'}, # 	2007-04-16	23:25:43	2007-04-17	01:23:00
'0161'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8106097',	 last => '8106099',	 list => '',  beginTime => '20070417.012300'}, # 	2007-04-17	01:23:00	2007-04-17	02:04:58
'0162'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8106102',	 last => '8106103',	 list => '',  beginTime => '20070417.020458'}, # 	2007-04-17	02:04:58	2007-04-17	02:54:49
'0163'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8106108',	 last => '8106108',	 list => '',  beginTime => '20070417.025449'}, # 	2007-04-17	02:54:49	2007-04-17	03:27:19
'0164'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8106112',	 last => '8106113',	 list => '',  beginTime => '20070417.032719'}, # 	2007-04-17	03:27:19	2007-04-17	04:04:44
'0165'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8107001',	 last => '8107004',	 list => '',  beginTime => '20070417.040444'}, # 	2007-04-17	04:04:44	2007-04-17	05:53:48
'0166'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8107006',	 last => '8107008',	 list => '',  beginTime => '20070417.055348'}, # 	2007-04-17	05:53:48	2007-04-17	09:11:35
'0167'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8107017',	 last => '8107017',	 list => '',  beginTime => '20070417.091135'}, # 	2007-04-17	09:11:35	2007-04-17	10:09:32
'0168'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8107019',	 last => '8107022',	 list => '',  beginTime => '20070417.100932'}, # 	2007-04-17	10:09:32	2007-04-17	12:09:59
'0169'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8107026',	 last => '8107027',	 list => '',  beginTime => '20070417.120959'}, # 	2007-04-17	12:09:59	2007-04-17	13:49:37
'0170'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8107029',	 last => '8107029',	 list => '',  beginTime => '20070417.134937'}, # 	2007-04-17	13:49:37	2007-04-17	18:51:42
'0171'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8107045',	 last => '8107045',	 list => '',  beginTime => '20070417.185142'}, # 	2007-04-17	18:51:42	2007-04-17	18:58:38	timestamp = 2007ProductionMinBias_FF
'0172'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8107046',	 last => '8107046',	 list => '',  beginTime => '20070417.185838'}, # 	2007-04-17	18:58:38	2007-04-17	20:02:56	timestamp = 2007Production2_FF
'0173'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8107060',	 last => '8107063',	 list => '',  beginTime => '20070417.200256'}, # 	2007-04-17	20:02:56	2007-04-17	21:34:59
'0174'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8107066',	 last => '8107069',	 list => '',  beginTime => '20070417.213459'}, # 	2007-04-17	21:34:59	2007-04-17	23:57:06
'0175'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8107072',	 last => '8107072',	 list => '',  beginTime => '20070417.235706'}, # 	2007-04-17	23:57:06	2007-04-18	01:43:28
'0176'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8107080',	 last => '8107081',	 list => '',  beginTime => '20070418.014328'}, # 	2007-04-18	01:43:28	2007-04-18	03:05:11
'0177'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8107083',	 last => '8107084',	 list => '',  beginTime => '20070418.030511'}, # 	2007-04-18	03:05:11	2007-04-18	04:01:16
'0178'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8108001',	 last => '8108004',	 list => '',  beginTime => '20070418.040116'}, # 	2007-04-18	04:01:16	2007-04-18	07:46:59
'0179'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8108012',	 last => '8108012',	 list => '',  beginTime => '20070418.074659'}, # 	2007-04-18	07:46:59	2007-04-18	08:09:22
'0180'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8108014',	 last => '8108014',	 list => '',  beginTime => '20070418.080922'}, # 	2007-04-18	08:09:22	2007-04-19	05:01:58
'0181'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8109015',	 last => '8109017',	 list => '',  beginTime => '20070419.050158'}, # 	2007-04-19	05:01:58	2007-04-19	05:38:03
'0182'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8109019',	 last => '8109019',	 list => '',  beginTime => '20070419.053803'}, # 	2007-04-19	05:38:03	2007-04-19	05:52:31	timestamp = 2007ProductionMinBias_FF
'0183'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8109021',	 last => '8109022',	 list => '',  beginTime => '20070419.055231'}, # 	2007-04-19	05:52:31	2007-04-19	10:17:32
'0184'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8109038',	 last => '8109040',	 list => '',  beginTime => '20070419.101732'}, # 	2007-04-19	10:17:32	2007-04-19	11:08:28	timestamp = 2007Production2_FF
'0185'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8109042',	 last => '8109045',	 list => '',  beginTime => '20070419.110828'}, # 	2007-04-19	11:08:28	2007-04-19	12:00:32	timestamp = 2007ProductionMinBias_FF
'0186'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8109047',	 last => '8109051',	 list => '',  beginTime => '20070419.120032'}, # 	2007-04-19	12:00:32	2007-04-19	13:27:51
'0187'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8109059',	 last => '8109060',	 list => '',  beginTime => '20070419.132751'}, # 	2007-04-19	13:27:51	2007-04-19	22:22:18
'0188'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8109090',	 last => '8109090',	 list => '',  beginTime => '20070419.222218'}, # 	2007-04-19	22:22:18	2007-04-19	23:23:57	timestamp = 2007Production2_FF
'0189'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8109092',	 last => '8109092',	 list => '',  beginTime => '20070419.232357'}, # 	2007-04-19	23:23:57	2007-04-20	00:04:05	timestamp = 2007ProductionMinBias_FF
'0190'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8109096',	 last => '8109103',	 list => '',  beginTime => '20070420.000405'}, # 	2007-04-20	00:04:05	2007-04-20	04:29:04
'0191'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8110009',	 last => '8110010',	 list => '',  beginTime => '20070420.042904'}, # 	2007-04-20	04:29:04	2007-04-20	05:28:27	timestamp = 2007Production2_FF
'0192'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8110012',	 last => '8110016',	 list => '',  beginTime => '20070420.052827'}, # 	2007-04-20	05:28:27	2007-04-20	06:28:38	timestamp = 2007ProductionMinBias_FF
'0193'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8110018',	 last => '8110018',	 list => '',  beginTime => '20070420.062838'}, # 	2007-04-20	06:28:38	2007-04-20	06:44:22
'0194'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8110021',	 last => '8110026',	 list => '',  beginTime => '20070420.064422'}, # 	2007-04-20	06:44:22	2007-04-20	08:20:49
'0195'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8110030',	 last => '8110032',	 list => '',  beginTime => '20070420.082049'}, # 	2007-04-20	08:20:49	2007-04-20	10:12:20
'0196'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8110041',	 last => '8110041',	 list => '',  beginTime => '20070420.101220'}, # 	2007-04-20	10:12:20	2007-04-20	10:30:24	timestamp = 2007Production2_FF
'0197'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8110043',	 last => '8110045',	 list => '',  beginTime => '20070420.103024'}, # 	2007-04-20	10:30:24	2007-04-20	11:25:46
'0198'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8110047',	 last => '8110053',	 list => '',  beginTime => '20070420.112546'}, # 	2007-04-20	11:25:46	2007-04-20	12:53:16	timestamp = 2007ProductionMinBias_FF
'0199'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8110056',	 last => '8110056',	 list => '',  beginTime => '20070420.125316'}, # 	2007-04-20	12:53:16	2007-04-20	13:22:10
'0200'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8110058',	 last => '8110058',	 list => '',  beginTime => '20070420.132210'}, # 	2007-04-20	13:22:10	2007-04-20	13:53:59
'0201'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8110060',	 last => '8110060',	 list => '',  beginTime => '20070420.135359'}, # 	2007-04-20	13:53:59	2007-04-20	14:11:36
'0202'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8110062',	 last => '8110064',	 list => '',  beginTime => '20070420.141136'}, # 	2007-04-20	14:11:36	2007-04-20	16:35:29
'0203'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8110092',	 last => '8110095',	 list => '',  beginTime => '20070420.163529'}, # 	2007-04-20	16:35:29	2007-04-20	17:32:53	timestamp = 2007Production2_FF
'0204'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8110097',	 last => '8110100',	 list => '',  beginTime => '20070420.173253'}, # 	2007-04-20	17:32:53	2007-04-20	18:39:41	timestamp = 2007ProductionMinBias_FF
'0205'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8110104',	 last => '8110105',	 list => '',  beginTime => '20070420.183941'}, # 	2007-04-20	18:39:41	2007-04-20	20:03:14
'0206'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8110112',	 last => '8110113',	 list => '',  beginTime => '20070420.200314'}, # 	2007-04-20	20:03:14	2007-04-20	21:12:41
'0207'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8110115',	 last => '8110115',	 list => '',  beginTime => '20070420.211241'}, # 	2007-04-20	21:12:41	2007-04-20	23:21:09	timestamp = 2007Production2_FF
'0208'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8110127',	 last => '8110129',	 list => '',  beginTime => '20070420.232109'}, # 	2007-04-20	23:21:09	2007-04-21	00:37:45
'0209'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8110131',	 last => '8110136',	 list => '',  beginTime => '20070421.003745'}, # 	2007-04-21	00:37:45	2007-04-21	03:19:56	timestamp = 2007ProductionMinBias_FF
'0210'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8110138',	 last => '8110139',	 list => '',  beginTime => '20070421.031956'}, # 	2007-04-21	03:19:56	2007-04-21	04:14:11
'0211'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8111001',	 last => '8111001',	 list => '',  beginTime => '20070421.041411'}, # 	2007-04-21	04:14:11	2007-04-21	07:58:43
'0212'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8111024',	 last => '8111027',	 list => '',  beginTime => '20070421.075843'}, # 	2007-04-21	07:58:43	2007-04-21	08:43:21	timestamp = 2007Production2_FF
'0213'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8111030',	 last => '8111030',	 list => '',  beginTime => '20070421.084321'}, # 	2007-04-21	08:43:21	2007-04-21	09:04:05	timestamp = 2007ProductionMinBias_FF
'0214'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8111032',	 last => '8111032',	 list => '',  beginTime => '20070421.090405'}, # 	2007-04-21	09:04:05	2007-04-21	09:39:30
'0215'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8111042',	 last => '8111043',	 list => '',  beginTime => '20070421.093930'}, # 	2007-04-21	09:39:30	2007-04-21	10:35:42
'0216'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8111045',	 last => '8111045',	 list => '',  beginTime => '20070421.103542'}, # 	2007-04-21	10:35:42	2007-04-21	11:14:13
'0217'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8111047',	 last => '8111048',	 list => '',  beginTime => '20070421.111413'}, # 	2007-04-21	11:14:13	2007-04-21	13:49:16
'0218'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8111065',	 last => '8111066',	 list => '',  beginTime => '20070421.134916'}, # 	2007-04-21	13:49:16	2007-04-21	14:45:56	timestamp = 2007Production2_FF
'0219'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8111068',	 last => '8111068',	 list => '',  beginTime => '20070421.144556'}, # 	2007-04-21	14:45:56	2007-04-21	15:12:51	timestamp = 2007ProductionMinBias_FF
'0220'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8111070',	 last => '8111074',	 list => '',  beginTime => '20070421.151251'}, # 	2007-04-21	15:12:51	2007-04-21	21:02:32
'0221'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8111083',	 last => '8111083',	 list => '',  beginTime => '20070421.210232'}, # 	2007-04-21	21:02:32	2007-04-21	22:09:14	timestamp = 2007Production2_FF
'0222'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8111088',	 last => '8111088',	 list => '',  beginTime => '20070421.220914'}, # 	2007-04-21	22:09:14	2007-04-21	22:56:16
'0223'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8111091',	 last => '8111092',	 list => '',  beginTime => '20070421.225616'}, # 	2007-04-21	22:56:16	2007-04-21	23:48:53
'0224'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8111093',	 last => '8111095',	 list => '',  beginTime => '20070421.234853'}, # 	2007-04-21	23:48:53	2007-04-22	00:24:30	timestamp = 2007ProductionMinBias_FF
'0225'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8111097',	 last => '8111098',	 list => '',  beginTime => '20070422.002430'}, # 	2007-04-22	00:24:30	2007-04-22	06:03:02
'0226'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8112007',	 last => '8112008',	 list => '',  beginTime => '20070422.060302'}, # 	2007-04-22	06:03:02	2007-04-22	11:45:14	timestamp = 2007Production2_FF
'0227'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8112017',	 last => '8112020',	 list => '',  beginTime => '20070422.114514'}, # 	2007-04-22	11:45:14	2007-04-22	12:42:01
'0228'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8112022',	 last => '8112022',	 list => '',  beginTime => '20070422.124201'}, # 	2007-04-22	12:42:01	2007-04-22	13:08:19
'0229'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8112025',	 last => '8112026',	 list => '',  beginTime => '20070422.130819'}, # 	2007-04-22	13:08:19	2007-04-22	14:14:22
'0230'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8112027',	 last => '8112027',	 list => '',  beginTime => '20070422.141422'}, # 	2007-04-22	14:14:22	2007-04-22	14:44:00	timestamp = 2007ProductionMinBias_FF
'0231'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8112029',	 last => '8112030',	 list => '',  beginTime => '20070422.144400'}, # 	2007-04-22	14:44:00	2007-04-22	15:29:04
'0232'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8112032',	 last => '8112034',	 list => '',  beginTime => '20070422.152904'}, # 	2007-04-22	15:29:04	2007-04-22	18:35:02
'0233'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8112048',	 last => '8112049',	 list => '',  beginTime => '20070422.183502'}, # 	2007-04-22	18:35:02	2007-04-22	19:33:29	timestamp = 2007Production2_FF
'0234'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8112051',	 last => '8112053',	 list => '',  beginTime => '20070422.193329'}, # 	2007-04-22	19:33:29	2007-04-22	20:57:53
'0235'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8112054',	 last => '8112054',	 list => '',  beginTime => '20070422.205753'}, # 	2007-04-22	20:57:53	2007-04-22	21:09:52	timestamp = 2007ProductionMinBias_FF
'0236'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8112059',	 last => '8112060',	 list => '',  beginTime => '20070422.210952'}, # 	2007-04-22	21:09:52	2007-04-22	21:53:30
'0237'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8112062',	 last => '8112062',	 list => '',  beginTime => '20070422.215330'}, # 	2007-04-22	21:53:30	2007-04-22	22:05:09
'0238'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8112064',	 last => '8112064',	 list => '',  beginTime => '20070422.220509'}, # 	2007-04-22	22:05:09	2007-04-22	22:49:09
'0239'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8112067',	 last => '8112067',	 list => '',  beginTime => '20070422.224909'}, # 	2007-04-22	22:49:09	2007-04-23	02:34:48
'0240'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8112076',	 last => '8112077',	 list => '',  beginTime => '20070423.023448'}, # 	2007-04-23	02:34:48	2007-04-23	04:28:51	timestamp = 2007Production2_FF
'0241'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8113001',	 last => '8113002',	 list => '',  beginTime => '20070423.042851'}, # 	2007-04-23	04:28:51	2007-04-23	05:32:36	timestamp = 2007ProductionMinBias_FF
'0242'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8113007',	 last => '8113007',	 list => '',  beginTime => '20070423.053236'}, # 	2007-04-23	05:32:36	2007-04-23	06:13:35
'0243'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8113009',	 last => '8113009',	 list => '',  beginTime => '20070423.061335'}, # 	2007-04-23	06:13:35	2007-04-23	06:37:32
'0244'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8113012',	 last => '8113012',	 list => '',  beginTime => '20070423.063732'}, # 	2007-04-23	06:37:32	2007-04-23	08:25:23
'0245'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8113023',	 last => '8113024',	 list => '',  beginTime => '20070423.082523'}, # 	2007-04-23	08:25:23	2007-04-23	09:23:36	timestamp = 2007Production2_FF
'0246'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8113028',	 last => '8113029',	 list => '',  beginTime => '20070423.092336'}, # 	2007-04-23	09:23:36	2007-04-23	10:12:11
'0247'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8113030',	 last => '8113030',	 list => '',  beginTime => '20070423.101211'}, # 	2007-04-23	10:12:11	2007-04-23	10:25:35	timestamp = 2007ProductionMinBias_FF
'0248'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8113034',	 last => '8113036',	 list => '',  beginTime => '20070423.102535'}, # 	2007-04-23	10:25:35	2007-04-23	10:38:14
'0249'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8113037',	 last => '8113038',	 list => '',  beginTime => '20070423.103814'}, # 	2007-04-23	10:38:14	2007-04-23	11:21:42	timestamp = 2007Production2_FF
'0250'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8113041',	 last => '8113041',	 list => '',  beginTime => '20070423.112142'}, # 	2007-04-23	11:21:42	2007-04-23	12:01:45	timestamp = 2007ProductionMinBias_FF
'0251'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8113044',	 last => '8113044',	 list => '',  beginTime => '20070423.120145'}, # 	2007-04-23	12:01:45	2007-04-23	12:35:06
'0252'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8113046',	 last => '8113046',	 list => '',  beginTime => '20070423.123506'}, # 	2007-04-23	12:35:06	2007-04-23	15:23:09
'0253'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8113059',	 last => '8113060',	 list => '',  beginTime => '20070423.152309'}, # 	2007-04-23	15:23:09	2007-04-23	15:31:26	timestamp = 2007Production2_FF
'0254'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8113062',	 last => '8113063',	 list => '',  beginTime => '20070423.153126'}, # 	2007-04-23	15:31:26	2007-04-23	16:26:42
'0255'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8113065',	 last => '8113065',	 list => '',  beginTime => '20070423.162642'}, # 	2007-04-23	16:26:42	2007-04-23	17:06:20
'0256'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8113068',	 last => '8113068',	 list => '',  beginTime => '20070423.170620'}, # 	2007-04-23	17:06:20	2007-04-23	17:30:39
'0257'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8113071',	 last => '8113072',	 list => '',  beginTime => '20070423.173039'}, # 	2007-04-23	17:30:39	2007-04-23	18:08:49	timestamp = 2007ProductionMinBias_FF
'0258'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8113074',	 last => '8113074',	 list => '',  beginTime => '20070423.180849'}, # 	2007-04-23	18:08:49	2007-04-23	18:34:40
'0259'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8113077',	 last => '8113077',	 list => '',  beginTime => '20070423.183440'}, # 	2007-04-23	18:34:40	2007-04-23	19:38:54
'0260'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8113087',	 last => '8113089',	 list => '',  beginTime => '20070423.193854'}, # 	2007-04-23	19:38:54	2007-04-23	22:01:53
'0261'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8113102',	 last => '8113103',	 list => '',  beginTime => '20070423.220153'}, # 	2007-04-23	22:01:53	2007-04-24	03:10:55	timestamp = 2007Production2_FF
'0262'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8113111',	 last => '8113112',	 list => '',  beginTime => '20070424.031055'}, # 	2007-04-24	03:10:55	2007-04-24	03:42:29
'0263'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8113113',	 last => '8113117',	 list => '',  beginTime => '20070424.034229'}, # 	2007-04-24	03:42:29	2007-04-24	04:18:24	timestamp = 2007ProductionMinBias_FF
'0264'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8114003',	 last => '8114003',	 list => '',  beginTime => '20070424.041824'}, # 	2007-04-24	04:18:24	2007-04-24	04:20:18
'0265'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8114004',	 last => '8114007',	 list => '',  beginTime => '20070424.042018'}, # 	2007-04-24	04:20:18	2007-04-24	05:20:04	timestamp = 2007Production2_FF
'0266'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8114012',	 last => '8114012',	 list => '',  beginTime => '20070424.052004'}, # 	2007-04-24	05:20:04	2007-04-24	06:02:32	timestamp = 2007ProductionMinBias_FF
'0267'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8114018',	 last => '8114019',	 list => '',  beginTime => '20070424.060232'}, # 	2007-04-24	06:02:32	2007-04-24	06:55:01
'0268'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8114021',	 last => '8114022',	 list => '',  beginTime => '20070424.065501'}, # 	2007-04-24	06:55:01	2007-04-24	12:01:30
'0269'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8114031',	 last => '8114032',	 list => '',  beginTime => '20070424.120130'}, # 	2007-04-24	12:01:30	2007-04-24	12:42:54
'0270'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8114034',	 last => '8114034',	 list => '',  beginTime => '20070424.124254'}, # 	2007-04-24	12:42:54	2007-04-24	18:44:59
'0271'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8114077',	 last => '8114078',	 list => '',  beginTime => '20070424.184459'}, # 	2007-04-24	18:44:59	2007-04-24	19:30:57	timestamp = 2007Production2_FF
'0272'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8114080',	 last => '8114080',	 list => '',  beginTime => '20070424.193057'}, # 	2007-04-24	19:30:57	2007-04-24	20:06:58
'0273'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8114081',	 last => '8114082',	 list => '',  beginTime => '20070424.200658'}, # 	2007-04-24	20:06:58	2007-04-24	20:57:42	timestamp = 2007ProductionMinBias_FF
'0274'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8114084',	 last => '8114084',	 list => '',  beginTime => '20070424.205742'}, # 	2007-04-24	20:57:42	2007-04-24	21:16:32
'0275'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8114086',	 last => '8114086',	 list => '',  beginTime => '20070424.211632'}, # 	2007-04-24	21:16:32	2007-04-24	21:50:27
'0276'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8114090',	 last => '8114090',	 list => '',  beginTime => '20070424.215027'}, # 	2007-04-24	21:50:27	2007-04-24	22:28:57
'0277'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8114094',	 last => '8114094',	 list => '',  beginTime => '20070424.222857'}, # 	2007-04-24	22:28:57	2007-04-24	22:38:32
'0278'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8114097',	 last => '8114097',	 list => '',  beginTime => '20070424.223832'}, # 	2007-04-24	22:38:32	2007-04-26	05:34:01
'0279'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8116016',	 last => '8116016',	 list => '',  beginTime => '20070426.053401'}, # 	2007-04-26	05:34:01	2007-04-26	05:38:54
'0280'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8116018',	 last => '8116019',	 list => '',  beginTime => '20070426.053854'}, # 	2007-04-26	05:38:54	2007-04-26	06:12:36
'0281'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8116026',	 last => '8116028',	 list => '',  beginTime => '20070426.061236'}, # 	2007-04-26	06:12:36	2007-04-26	06:51:47
'0282'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8116031',	 last => '8116032',	 list => '',  beginTime => '20070426.065147'}, # 	2007-04-26	06:51:47	2007-04-26	07:31:33
'0283'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8116034',	 last => '8116034',	 list => '',  beginTime => '20070426.073133'}, # 	2007-04-26	07:31:33	2007-04-26	08:06:28
'0284'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8116036',	 last => '8116036',	 list => '',  beginTime => '20070426.080628'}, # 	2007-04-26	08:06:28	2007-04-26	11:50:42
'0285'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8116053',	 last => '8116054',	 list => '',  beginTime => '20070426.115042'}, # 	2007-04-26	11:50:42	2007-04-26	12:23:24	timestamp = 2007Production2_FF
'0286'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8116058',	 last => '8116058',	 list => '',  beginTime => '20070426.122324'}, # 	2007-04-26	12:23:24	2007-04-26	12:55:23
'0287'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8116060',	 last => '8116060',	 list => '',  beginTime => '20070426.125523'}, # 	2007-04-26	12:55:23	2007-04-26	23:49:25
'0288'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8116086',	 last => '8116086',	 list => '',  beginTime => '20070426.234925'}, # 	2007-04-26	23:49:25	2007-04-27	00:45:24
'0289'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8116097',	 last => '8116098',	 list => '',  beginTime => '20070427.004524'}, # 	2007-04-27	00:45:24	2007-04-27	01:28:29
'0290'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8116099',	 last => '8116101',	 list => '',  beginTime => '20070427.012829'}, # 	2007-04-27	01:28:29	2007-04-27	02:40:18	timestamp = 2007ProductionMinBias_FF
'0291'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8116104',	 last => '8116104',	 list => '',  beginTime => '20070427.024018'}, # 	2007-04-27	02:40:18	2007-04-27	03:05:56	timestamp = 2007Production2_FF
'0292'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8116107',	 last => '8116109',	 list => '',  beginTime => '20070427.030556'}, # 	2007-04-27	03:05:56	2007-04-27	04:17:14	timestamp = 2007ProductionMinBias_FF
'0293'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8117001',	 last => '8117001',	 list => '',  beginTime => '20070427.041714'}, # 	2007-04-27	04:17:14	2007-04-27	06:14:29
'0294'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8117011',	 last => '8117011',	 list => '',  beginTime => '20070427.061429'}, # 	2007-04-27	06:14:29	2007-04-27	06:40:37	timestamp = 2007Production2_FF
'0295'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8117013',	 last => '8117013',	 list => '',  beginTime => '20070427.064037'}, # 	2007-04-27	06:40:37	2007-04-27	06:52:20
'0296'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8117016',	 last => '8117016',	 list => '',  beginTime => '20070427.065220'}, # 	2007-04-27	06:52:20	2007-04-27	07:07:13	timestamp = 2007ProductionMinBias_FF
'0297'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8117017',	 last => '8117017',	 list => '',  beginTime => '20070427.070713'}, # 	2007-04-27	07:07:13	2007-04-28	04:21:01	timestamp = 2007Production2_FF
'0298'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8118005',	 last => '8118010',	 list => '',  beginTime => '20070428.042101'}, # 	2007-04-28	04:21:01	2007-04-28	05:32:38
'0299'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8118012',	 last => '8118013',	 list => '',  beginTime => '20070428.053238'}, # 	2007-04-28	05:32:38	2007-04-28	06:29:02
'0300'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8118015',	 last => '8118017',	 list => '',  beginTime => '20070428.062902'}, # 	2007-04-28	06:29:02	2007-04-28	07:39:23	timestamp = 2007ProductionMinBias_FF
'0301'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8118019',	 last => '8118020',	 list => '',  beginTime => '20070428.073923'}, # 	2007-04-28	07:39:23	2007-04-28	08:08:33
'0302'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8118022',	 last => '8118025',	 list => '',  beginTime => '20070428.080833'}, # 	2007-04-28	08:08:33	2007-04-28	10:10:44
'0303'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8118040',	 last => '8118042',	 list => '',  beginTime => '20070428.101044'}, # 	2007-04-28	10:10:44	2007-04-28	11:26:29	timestamp = 2007Production2_FF
'0304'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8118044',	 last => '8118044',	 list => '',  beginTime => '20070428.112629'}, # 	2007-04-28	11:26:29	2007-04-28	11:55:58
'0305'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8118045',	 last => '8118048',	 list => '',  beginTime => '20070428.115558'}, # 	2007-04-28	11:55:58	2007-04-28	13:05:08	timestamp = 2007ProductionMinBias_FF
'0306'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8118050',	 last => '8118052',	 list => '',  beginTime => '20070428.130508'}, # 	2007-04-28	13:05:08	2007-04-29	02:38:20
'0307'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8118074',	 last => '8118078',	 list => '',  beginTime => '20070429.023820'}, # 	2007-04-29	02:38:20	2007-04-29	03:34:24	timestamp = 2007Production2_FF
'0308'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8118080',	 last => '8118080',	 list => '',  beginTime => '20070429.033424'}, # 	2007-04-29	03:34:24	2007-04-29	03:47:21	timestamp = 2007ProductionMinBias_FF
'0309'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8118083',	 last => '8118085',	 list => '',  beginTime => '20070429.034721'}, # 	2007-04-29	03:47:21	2007-04-29	04:21:28	timestamp = 2007Production2_FF
'0310'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8119001',	 last => '8119002',	 list => '',  beginTime => '20070429.042128'}, # 	2007-04-29	04:21:28	2007-04-29	10:33:59	timestamp = 2007ProductionMinBias_FF
'0311'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8119015',	 last => '8119017',	 list => '',  beginTime => '20070429.103359'}, # 	2007-04-29	10:33:59	2007-04-29	11:50:32	timestamp = 2007Production2_FF
'0312'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8119021',	 last => '8119023',	 list => '',  beginTime => '20070429.115032'}, # 	2007-04-29	11:50:32	2007-04-29	12:53:10
'0313'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8119024',	 last => '8119025',	 list => '',  beginTime => '20070429.125310'}, # 	2007-04-29	12:53:10	2007-04-29	13:31:08	timestamp = 2007ProductionMinBias_FF
'0314'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8119027',	 last => '8119027',	 list => '',  beginTime => '20070429.133108'}, # 	2007-04-29	13:31:08	2007-04-29	14:06:47
'0315'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8119029',	 last => '8119030',	 list => '',  beginTime => '20070429.140647'}, # 	2007-04-29	14:06:47	2007-04-29	14:37:50
'0316'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8119032',	 last => '8119032',	 list => '',  beginTime => '20070429.143750'}, # 	2007-04-29	14:37:50	2007-04-29	16:26:40
'0317'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8119050',	 last => '8119052',	 list => '',  beginTime => '20070429.162640'}, # 	2007-04-29	16:26:40	2007-04-29	17:00:51	timestamp = 2007Production2_FF
'0318'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8119056',	 last => '8119057',	 list => '',  beginTime => '20070429.170051'}, # 	2007-04-29	17:00:51	2007-04-29	19:33:07
'0319'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8119074',	 last => '8119075',	 list => '',  beginTime => '20070429.193307'}, # 	2007-04-29	19:33:07	2007-04-29	20:10:56
'0320'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8119078',	 last => '8119079',	 list => '',  beginTime => '20070429.201056'}, # 	2007-04-29	20:10:56	2007-04-29	20:35:57
'0321'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8119082',	 last => '8119083',	 list => '',  beginTime => '20070429.203557'}, # 	2007-04-29	20:35:57	2007-04-29	21:12:44
'0322'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8119084',	 last => '8119085',	 list => '',  beginTime => '20070429.211244'}, # 	2007-04-29	21:12:44	2007-04-29	22:38:47	timestamp = 2007ProductionMinBias_FF
'0323'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8119088',	 last => '8119088',	 list => '',  beginTime => '20070429.223847'}, # 	2007-04-29	22:38:47	2007-04-29	23:17:02
'0324'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8119090',	 last => '8119092',	 list => '',  beginTime => '20070429.231702'}, # 	2007-04-29	23:17:02	2007-04-30	02:07:24
'0325'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8119105',	 last => '8119106',	 list => '',  beginTime => '20070430.020724'}, # 	2007-04-30	02:07:24	2007-04-30	02:14:41	timestamp = 2007Production2_FF
'0326'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8119108',	 last => '8119110',	 list => '',  beginTime => '20070430.021441'}, # 	2007-04-30	02:14:41	2007-04-30	02:51:28
'0327'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8119112',	 last => '8119112',	 list => '',  beginTime => '20070430.025128'}, # 	2007-04-30	02:51:28	2007-04-30	03:12:47
'0328'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8119115',	 last => '8119115',	 list => '',  beginTime => '20070430.031247'}, # 	2007-04-30	03:12:47	2007-04-30	03:24:52
'0329'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8119116',	 last => '8119116',	 list => '',  beginTime => '20070430.032452'}, # 	2007-04-30	03:24:52	2007-04-30	03:33:44	timestamp = 2007ProductionMinBias_FF
'0330'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8119117',	 last => '8119120',	 list => '',  beginTime => '20070430.033344'}, # 	2007-04-30	03:33:44	2007-04-30	04:08:44	timestamp = 2007Production2_FF
'0331'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8120001',	 last => '8120004',	 list => '',  beginTime => '20070430.040844'}, # 	2007-04-30	04:08:44	2007-04-30	05:17:37	timestamp = 2007ProductionMinBias_FF
'0332'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8120006',	 last => '8120006',	 list => '',  beginTime => '20070430.051737'}, # 	2007-04-30	05:17:37	2007-04-30	05:50:30
'0333'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8120008',	 last => '8120009',	 list => '',  beginTime => '20070430.055030'}, # 	2007-04-30	05:50:30	2007-04-30	08:55:10
'0334'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8120027',	 last => '8120028',	 list => '',  beginTime => '20070430.085510'}, # 	2007-04-30	08:55:10	2007-04-30	09:55:23	timestamp = 2007Production2_FF
'0335'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8120030',	 last => '8120030',	 list => '',  beginTime => '20070430.095523'}, # 	2007-04-30	09:55:23	2007-04-30	10:06:25	timestamp = 2007ProductionMinBias_FF
'0336'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8120032',	 last => '8120036',	 list => '',  beginTime => '20070430.100625'}, # 	2007-04-30	10:06:25	2007-04-30	12:23:20
'0337'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8120038',	 last => '8120038',	 list => '',  beginTime => '20070430.122320'}, # 	2007-04-30	12:23:20	2007-04-30	17:26:42
'0338'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8120067',	 last => '8120069',	 list => '',  beginTime => '20070430.172642'}, # 	2007-04-30	17:26:42	2007-04-30	18:21:51	timestamp = 2007Production2_FF
'0339'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8120071',	 last => '8120072',	 list => '',  beginTime => '20070430.182151'}, # 	2007-04-30	18:21:51	2007-04-30	19:31:33
'0340'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8120077',	 last => '8120077',	 list => '',  beginTime => '20070430.193133'}, # 	2007-04-30	19:31:33	2007-04-30	19:39:26
'0341'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8120078',	 last => '8120081',	 list => '',  beginTime => '20070430.193926'}, # 	2007-04-30	19:39:26	2007-04-30	21:00:20	timestamp = 2007ProductionMinBias_FF
'0342'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8120084',	 last => '8120084',	 list => '',  beginTime => '20070430.210020'}, # 	2007-04-30	21:00:20	2007-04-30	21:41:53
'0343'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8120086',	 last => '8120086',	 list => '',  beginTime => '20070430.214153'}, # 	2007-04-30	21:41:53	2007-04-30	23:44:50
'0344'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8120106',	 last => '8120106',	 list => '',  beginTime => '20070430.234450'}, # 	2007-04-30	23:44:50	2007-05-01	00:19:43	timestamp = 2007Production2_FF
'0345'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8120108',	 last => '8120108',	 list => '',  beginTime => '20070501.001943'}, # 	2007-05-01	00:19:43	2007-05-01	00:53:55
'0346'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8120109',	 last => '8120109',	 list => '',  beginTime => '20070501.005355'}, # 	2007-05-01	00:53:55	2007-05-01	01:04:05	timestamp = 2007ProductionMinBias_FF
'0347'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8120111',	 last => '8120111',	 list => '',  beginTime => '20070501.010405'}, # 	2007-05-01	01:04:05	2007-05-01	01:29:16
'0348'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8120113',	 last => '8120114',	 list => '',  beginTime => '20070501.012916'}, # 	2007-05-01	01:29:16	2007-05-01	02:07:38
'0349'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8120118',	 last => '8120119',	 list => '',  beginTime => '20070501.020738'}, # 	2007-05-01	02:07:38	2007-05-01	02:52:50
'0350'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8120123',	 last => '8120126',	 list => '',  beginTime => '20070501.025250'}, # 	2007-05-01	02:52:50	2007-05-01	05:42:11
'0351'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8121010',	 last => '8121012',	 list => '',  beginTime => '20070501.054211'}, # 	2007-05-01	05:42:11	2007-05-01	06:58:45	timestamp = 2007Production2_FF
'0352'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8121014',	 last => '8121014',	 list => '',  beginTime => '20070501.065845'}, # 	2007-05-01	06:58:45	2007-05-01	07:28:42
'0353'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8121015',	 last => '8121019',	 list => '',  beginTime => '20070501.072842'}, # 	2007-05-01	07:28:42	2007-05-01	09:30:41	timestamp = 2007ProductionMinBias_FF
'0354'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8121022',	 last => '8121022',	 list => '',  beginTime => '20070501.093041'}, # 	2007-05-01	09:30:41	2007-05-01	09:47:07
'0355'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8121025',	 last => '8121025',	 list => '',  beginTime => '20070501.094707'}, # 	2007-05-01	09:47:07	2007-05-01	12:50:29
'0356'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8121035',	 last => '8121036',	 list => '',  beginTime => '20070501.125029'}, # 	2007-05-01	12:50:29	2007-05-01	14:11:59	timestamp = 2007Production2_FF
'0357'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8121042',	 last => '8121042',	 list => '',  beginTime => '20070501.141159'}, # 	2007-05-01	14:11:59	2007-05-01	14:45:23
'0358'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8121043',	 last => '8121043',	 list => '',  beginTime => '20070501.144523'}, # 	2007-05-01	14:45:23	2007-05-01	20:06:31	timestamp = 2007ProductionMinBias_FF
'0359'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8121087',	 last => '8121088',	 list => '',  beginTime => '20070501.200631'}, # 	2007-05-01	20:06:31	2007-05-01	20:41:00	timestamp = 2007Production2_FF
'0360'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8121090',	 last => '8121091',	 list => '',  beginTime => '20070501.204100'}, # 	2007-05-01	20:41:00	2007-05-01	21:24:20
'0361'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8121093',	 last => '8121094',	 list => '',  beginTime => '20070501.212420'}, # 	2007-05-01	21:24:20	2007-05-01	22:27:42
'0362'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8121095',	 last => '8121097',	 list => '',  beginTime => '20070501.222742'}, # 	2007-05-01	22:27:42	2007-05-01	23:11:54	timestamp = 2007ProductionMinBias_FF
'0363'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8121101',	 last => '8121102',	 list => '',  beginTime => '20070501.231154'}, # 	2007-05-01	23:11:54	2007-05-01	23:56:49
'0364'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8121106',	 last => '8121106',	 list => '',  beginTime => '20070501.235649'}, # 	2007-05-01	23:56:49	2007-05-02	01:44:07
'0365'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8121118',	 last => '8121119',	 list => '',  beginTime => '20070502.014407'}, # 	2007-05-02	01:44:07	2007-05-02	02:22:21	timestamp = 2007Production2_FF
'0366'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8121121',	 last => '8121121',	 list => '',  beginTime => '20070502.022221'}, # 	2007-05-02	02:22:21	2007-05-02	02:48:19
'0367'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8121122',	 last => '8121123',	 list => '',  beginTime => '20070502.024819'}, # 	2007-05-02	02:48:19	2007-05-02	03:43:59	timestamp = 2007ProductionMinBias_FF
'0368'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8121126',	 last => '8121126',	 list => '',  beginTime => '20070502.034359'}, # 	2007-05-02	03:43:59	2007-05-02	04:09:41
'0369'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8122001',	 last => '8122004',	 list => '',  beginTime => '20070502.040941'}, # 	2007-05-02	04:09:41	2007-05-02	07:46:57
'0370'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8122020',	 last => '8122022',	 list => '',  beginTime => '20070502.074657'}, # 	2007-05-02	07:46:57	2007-05-02	23:09:51	timestamp = 2007Production2_FF
'0371'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8122076',	 last => '8122078',	 list => '',  beginTime => '20070502.230951'}, # 	2007-05-02	23:09:51	2007-05-02	23:48:51
'0372'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8122081',	 last => '8122083',	 list => '',  beginTime => '20070502.234851'}, # 	2007-05-02	23:48:51	2007-05-03	00:46:58
'0373'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8122084',	 last => '8122091',	 list => '',  beginTime => '20070503.004658'}, # 	2007-05-03	00:46:58	2007-05-03	03:09:30	timestamp = 2007ProductionMinBias_FF
'0374'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8122096',	 last => '8122096',	 list => '',  beginTime => '20070503.030930'}, # 	2007-05-03	03:09:30	2007-05-03	07:59:20
'0375'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8123008',	 last => '8123009',	 list => '',  beginTime => '20070503.075920'}, # 	2007-05-03	07:59:20	2007-05-03	08:55:34	timestamp = 2007Production2_FF
'0376'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8123011',	 last => '8123012',	 list => '',  beginTime => '20070503.085534'}, # 	2007-05-03	08:55:34	2007-05-03	09:52:26
'0377'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8123013',	 last => '8123015',	 list => '',  beginTime => '20070503.095226'}, # 	2007-05-03	09:52:26	2007-05-03	11:25:39	timestamp = 2007ProductionMinBias_FF
'0378'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8123017',	 last => '8123020',	 list => '',  beginTime => '20070503.112539'}, # 	2007-05-03	11:25:39	2007-05-03	21:51:23
'0379'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8123057',	 last => '8123058',	 list => '',  beginTime => '20070503.215123'}, # 	2007-05-03	21:51:23	2007-05-03	22:30:12	timestamp = 2007Production2_FF
'0380'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8123060',	 last => '8123062',	 list => '',  beginTime => '20070503.223012'}, # 	2007-05-03	22:30:12	2007-05-03	23:20:28
'0381'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8123066',	 last => '8123068',	 list => '',  beginTime => '20070503.232028'}, # 	2007-05-03	23:20:28	2007-05-04	00:04:50
'0382'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8123069',	 last => '8123071',	 list => '',  beginTime => '20070504.000450'}, # 	2007-05-04	00:04:50	2007-05-04	00:57:25	timestamp = 2007ProductionMinBias_FF
'0383'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8123073',	 last => '8123074',	 list => '',  beginTime => '20070504.005725'}, # 	2007-05-04	00:57:25	2007-05-04	02:04:31
'0384'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8123076',	 last => '8123076',	 list => '',  beginTime => '20070504.020431'}, # 	2007-05-04	02:04:31	2007-05-04	03:39:54
'0385'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8123088',	 last => '8123089',	 list => '',  beginTime => '20070504.033954'}, # 	2007-05-04	03:39:54	2007-05-04	04:00:43	timestamp = 2007Production2_FF
'0386'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8124001',	 last => '8124002',	 list => '',  beginTime => '20070504.040043'}, # 	2007-05-04	04:00:43	2007-05-04	04:36:06
'0387'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8124004',	 last => '8124006',	 list => '',  beginTime => '20070504.043606'}, # 	2007-05-04	04:36:06	2007-05-04	05:43:37
'0388'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8124007',	 last => '8124010',	 list => '',  beginTime => '20070504.054337'}, # 	2007-05-04	05:43:37	2007-05-04	07:51:21	timestamp = 2007ProductionMinBias_FF
'0389'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8124012',	 last => '8124013',	 list => '',  beginTime => '20070504.075121'}, # 	2007-05-04	07:51:21	2007-05-04	10:15:12
'0390'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8124024',	 last => '8124025',	 list => '',  beginTime => '20070504.101512'}, # 	2007-05-04	10:15:12	2007-05-04	11:12:40	timestamp = 2007Production2_FF
'0391'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8124027',	 last => '8124028',	 list => '',  beginTime => '20070504.111240'}, # 	2007-05-04	11:12:40	2007-05-04	11:58:51
'0392'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8124029',	 last => '8124030',	 list => '',  beginTime => '20070504.115851'}, # 	2007-05-04	11:58:51	2007-05-04	12:42:26	timestamp = 2007ProductionMinBias_FF
'0393'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8124032',	 last => '8124033',	 list => '',  beginTime => '20070504.124226'}, # 	2007-05-04	12:42:26	2007-05-04	13:32:15
'0394'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8124035',	 last => '8124036',	 list => '',  beginTime => '20070504.133215'}, # 	2007-05-04	13:32:15	2007-05-04	15:59:14
'0395'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8124059',	 last => '8124059',	 list => '',  beginTime => '20070504.155914'}, # 	2007-05-04	15:59:14	2007-05-04	21:08:24	timestamp = 2007Production2_FF
'0396'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8124082',	 last => '8124085',	 list => '',  beginTime => '20070504.210824'}, # 	2007-05-04	21:08:24	2007-05-04	22:11:58
'0397'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8124089',	 last => '8124091',	 list => '',  beginTime => '20070504.221158'}, # 	2007-05-04	22:11:58	2007-05-04	23:20:06
'0398'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8124093',	 last => '8124096',	 list => '',  beginTime => '20070504.232006'}, # 	2007-05-04	23:20:06	2007-05-05	00:41:19	timestamp = 2007ProductionMinBias_FF
'0399'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8124098',	 last => '8124099',	 list => '',  beginTime => '20070505.004119'}, # 	2007-05-05	00:41:19	2007-05-05	02:37:40
'0400'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8124111',	 last => '8124112',	 list => '',  beginTime => '20070505.023740'}, # 	2007-05-05	02:37:40	2007-05-05	03:45:38	timestamp = 2007Production2_FF
'0401'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8124120',	 last => '8124120',	 list => '',  beginTime => '20070505.034538'}, # 	2007-05-05	03:45:38	2007-05-05	04:38:08
'0402'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8125010',	 last => '8125010',	 list => '',  beginTime => '20070505.043808'}, # 	2007-05-05	04:38:08	2007-05-05	04:53:11
'0403'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8125012',	 last => '8125013',	 list => '',  beginTime => '20070505.045311'}, # 	2007-05-05	04:53:11	2007-05-05	08:07:17	timestamp = 2007ProductionMinBias_FF
'0404'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8125020',	 last => '8125021',	 list => '',  beginTime => '20070505.080717'}, # 	2007-05-05	08:07:17	2007-05-05	09:16:19	timestamp = 2007Production2_FF
'0405'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8125033',	 last => '8125033',	 list => '',  beginTime => '20070505.091619'}, # 	2007-05-05	09:16:19	2007-05-05	09:55:23
'0406'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8125035',	 last => '8125036',	 list => '',  beginTime => '20070505.095523'}, # 	2007-05-05	09:55:23	2007-05-05	10:26:53	timestamp = 2007ProductionMinBias_FF
'0407'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8125039',	 last => '8125039',	 list => '',  beginTime => '20070505.102653'}, # 	2007-05-05	10:26:53	2007-05-05	11:02:16
'0408'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8125042',	 last => '8125042',	 list => '',  beginTime => '20070505.110216'}, # 	2007-05-05	11:02:16	2007-05-05	13:48:21
'0409'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8125062',	 last => '8125063',	 list => '',  beginTime => '20070505.134821'}, # 	2007-05-05	13:48:21	2007-05-05	14:50:49	timestamp = 2007Production2_FF
'0410'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8125065',	 last => '8125066',	 list => '',  beginTime => '20070505.145049'}, # 	2007-05-05	14:50:49	2007-05-05	16:06:16
'0411'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8125073',	 last => '8125076',	 list => '',  beginTime => '20070505.160616'}, # 	2007-05-05	16:06:16	2007-05-05	17:03:39	timestamp = 2007ProductionMinBias_FF
'0412'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8125078',	 last => '8125078',	 list => '',  beginTime => '20070505.170339'}, # 	2007-05-05	17:03:39	2007-05-05	17:30:43
'0413'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8125080',	 last => '8125080',	 list => '',  beginTime => '20070505.173043'}, # 	2007-05-05	17:30:43	2007-05-05	17:55:56
'0414'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8125082',	 last => '8125083',	 list => '',  beginTime => '20070505.175556'}, # 	2007-05-05	17:55:56	2007-05-05	19:54:43
'0415'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8125092',	 last => '8125093',	 list => '',  beginTime => '20070505.195443'}, # 	2007-05-05	19:54:43	2007-05-05	20:41:47	timestamp = 2007Production2_FF
'0416'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8125095',	 last => '8125095',	 list => '',  beginTime => '20070505.204147'}, # 	2007-05-05	20:41:47	2007-05-06	01:06:00
'0417'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8125106',	 last => '8125108',	 list => '',  beginTime => '20070506.010600'}, # 	2007-05-06	01:06:00	2007-05-06	02:06:26
'0418'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8125110',	 last => '8125112',	 list => '',  beginTime => '20070506.020626'}, # 	2007-05-06	02:06:26	2007-05-06	02:51:52
'0419'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8125113',	 last => '8125113',	 list => '',  beginTime => '20070506.025152'}, # 	2007-05-06	02:51:52	2007-05-06	03:15:29	timestamp = 2007ProductionMinBias_FF
'0420'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8125116',	 last => '8125116',	 list => '',  beginTime => '20070506.031529'}, # 	2007-05-06	03:15:29	2007-05-06	03:44:41
'0421'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8125118',	 last => '8125119',	 list => '',  beginTime => '20070506.034441'}, # 	2007-05-06	03:44:41	2007-05-06	04:22:01
'0422'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8126001',	 last => '8126001',	 list => '',  beginTime => '20070506.042201'}, # 	2007-05-06	04:22:01	2007-05-06	05:02:36
'0423'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8126003',	 last => '8126004',	 list => '',  beginTime => '20070506.050236'}, # 	2007-05-06	05:02:36	2007-05-06	06:43:07
'0424'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8126013',	 last => '8126016',	 list => '',  beginTime => '20070506.064307'}, # 	2007-05-06	06:43:07	2007-05-06	07:47:05	timestamp = 2007Production2_FF
'0425'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8126018',	 last => '8126019',	 list => '',  beginTime => '20070506.074705'}, # 	2007-05-06	07:47:05	2007-05-06	08:47:18
'0426'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8126020',	 last => '8126021',	 list => '',  beginTime => '20070506.084718'}, # 	2007-05-06	08:47:18	2007-05-06	09:48:47	timestamp = 2007ProductionMinBias_FF
'0427'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8126023',	 last => '8126024',	 list => '',  beginTime => '20070506.094847'}, # 	2007-05-06	09:48:47	2007-05-06	10:24:18
'0428'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8126027',	 last => '8126027',	 list => '',  beginTime => '20070506.102418'}, # 	2007-05-06	10:24:18	2007-05-06	10:43:10
'0429'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8126030',	 last => '8126030',	 list => '',  beginTime => '20070506.104310'}, # 	2007-05-06	10:43:10	2007-05-06	12:26:29
'0430'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8126040',	 last => '8126043',	 list => '',  beginTime => '20070506.122629'}, # 	2007-05-06	12:26:29	2007-05-06	13:40:01	timestamp = 2007Production2_FF
'0431'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8126045',	 last => '8126046',	 list => '',  beginTime => '20070506.134001'}, # 	2007-05-06	13:40:01	2007-05-06	14:42:54
'0432'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8126047',	 last => '8126049',	 list => '',  beginTime => '20070506.144254'}, # 	2007-05-06	14:42:54	2007-05-06	16:16:30	timestamp = 2007ProductionMinBias_FF
'0433'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8126051',	 last => '8126051',	 list => '',  beginTime => '20070506.161630'}, # 	2007-05-06	16:16:30	2007-05-06	16:41:19
'0434'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8126054',	 last => '8126054',	 list => '',  beginTime => '20070506.164119'}, # 	2007-05-06	16:41:19	2007-05-06	18:03:25
'0435'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8126068',	 last => '8126071',	 list => '',  beginTime => '20070506.180325'}, # 	2007-05-06	18:03:25	2007-05-06	18:56:14	timestamp = 2007Production2_FF
'0436'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8126073',	 last => '8126073',	 list => '',  beginTime => '20070506.185614'}, # 	2007-05-06	18:56:14	2007-05-06	22:30:49
'0437'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8126084',	 last => '8126085',	 list => '',  beginTime => '20070506.223049'}, # 	2007-05-06	22:30:49	2007-05-07	01:14:32
'0438'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8126093',	 last => '8126094',	 list => '',  beginTime => '20070507.011432'}, # 	2007-05-07	01:14:32	2007-05-07	02:33:47
'0439'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8126096',	 last => '8126096',	 list => '',  beginTime => '20070507.023347'}, # 	2007-05-07	02:33:47	2007-05-07	03:03:16
'0440'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8126097',	 last => '8126097',	 list => '',  beginTime => '20070507.030316'}, # 	2007-05-07	03:03:16	2007-05-07	03:31:56	timestamp = 2007ProductionMinBias_FF
'0441'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8126102',	 last => '8126102',	 list => '',  beginTime => '20070507.033156'}, # 	2007-05-07	03:31:56	2007-05-07	04:00:14
'0442'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8126107',	 last => '8126107',	 list => '',  beginTime => '20070507.040014'}, # 	2007-05-07	04:00:14	2007-05-07	04:07:09
'0443'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8127001',	 last => '8127002',	 list => '',  beginTime => '20070507.040709'}, # 	2007-05-07	04:07:09	2007-05-07	05:17:35
'0444'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8127004',	 last => '8127004',	 list => '',  beginTime => '20070507.051735'}, # 	2007-05-07	05:17:35	2007-05-07	09:19:21
'0445'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8127012',	 last => '8127013',	 list => '',  beginTime => '20070507.091921'}, # 	2007-05-07	09:19:21	2007-05-07	10:13:48	timestamp = 2007Production2_FF
'0446'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8127015',	 last => '8127016',	 list => '',  beginTime => '20070507.101348'}, # 	2007-05-07	10:13:48	2007-05-07	11:12:26
'0447'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8127017',	 last => '8127021',	 list => '',  beginTime => '20070507.111226'}, # 	2007-05-07	11:12:26	2007-05-07	12:22:15	timestamp = 2007ProductionMinBias_FF
'0448'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8127024',	 last => '8127025',	 list => '',  beginTime => '20070507.122215'}, # 	2007-05-07	12:22:15	2007-05-07	13:34:34
'0449'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8127028',	 last => '8127029',	 list => '',  beginTime => '20070507.133434'}, # 	2007-05-07	13:34:34	2007-05-07	15:55:36
'0450'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8127046',	 last => '8127048',	 list => '',  beginTime => '20070507.155536'}, # 	2007-05-07	15:55:36	2007-05-07	17:10:00	timestamp = 2007Production2_FF
'0451'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8127050',	 last => '8127052',	 list => '',  beginTime => '20070507.171000'}, # 	2007-05-07	17:10:00	2007-05-07	22:56:12
'0452'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8127072',	 last => '8127074',	 list => '',  beginTime => '20070507.225612'}, # 	2007-05-07	22:56:12	2007-05-07	23:06:01	timestamp = 2007ProductionMinBias_FF
'0453'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8127075',	 last => '8127076',	 list => '',  beginTime => '20070507.230601'}, # 	2007-05-07	23:06:01	2007-05-08	00:00:40	timestamp = 2007Production2_FF
'0454'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8127078',	 last => '8127078',	 list => '',  beginTime => '20070508.000040'}, # 	2007-05-08	00:00:40	2007-05-08	02:34:37
'0455'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8127084',	 last => '8127086',	 list => '',  beginTime => '20070508.023437'}, # 	2007-05-08	02:34:37	2007-05-08	05:52:05
'0456'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8128006',	 last => '8128008',	 list => '',  beginTime => '20070508.055205'}, # 	2007-05-08	05:52:05	2007-05-08	06:47:20
'0457'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8128010',	 last => '8128012',	 list => '',  beginTime => '20070508.064720'}, # 	2007-05-08	06:47:20	2007-05-08	07:33:51
'0458'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8128014',	 last => '8128016',	 list => '',  beginTime => '20070508.073351'}, # 	2007-05-08	07:33:51	2007-05-08	08:22:17
'0459'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8128018',	 last => '8128020',	 list => '',  beginTime => '20070508.082217'}, # 	2007-05-08	08:22:17	2007-05-08	09:11:00
'0460'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8128022',	 last => '8128023',	 list => '',  beginTime => '20070508.091100'}, # 	2007-05-08	09:11:00	2007-05-08	09:57:24
'0461'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8128026',	 last => '8128026',	 list => '',  beginTime => '20070508.095724'}, # 	2007-05-08	09:57:24	2007-05-08	11:22:51
'0462'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8128033',	 last => '8128035',	 list => '',  beginTime => '20070508.112251'}, # 	2007-05-08	11:22:51	2007-05-08	12:01:27
'0463'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8128037',	 last => '8128037',	 list => '',  beginTime => '20070508.120127'}, # 	2007-05-08	12:01:27	2007-05-08	12:31:38
'0464'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8128039',	 last => '8128039',	 list => '',  beginTime => '20070508.123138'}, # 	2007-05-08	12:31:38	2007-05-08	13:07:39
'0465'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8128041',	 last => '8128048',	 list => '',  beginTime => '20070508.130739'}, # 	2007-05-08	13:07:39	2007-05-08	15:39:38	timestamp = 2007ProductionMinBias_FF
'0466'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8128052',	 last => '8128052',	 list => '',  beginTime => '20070508.153938'}, # 	2007-05-08	15:39:38	2007-05-08	22:18:12
'0467'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8128066',	 last => '8128067',	 list => '',  beginTime => '20070508.221812'}, # 	2007-05-08	22:18:12	2007-05-08	23:09:59	timestamp = 2007Production2_FF
'0468'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8128068',	 last => '8128069',	 list => '',  beginTime => '20070508.230959'}, # 	2007-05-08	23:09:59	2007-05-11	06:16:09	timestamp = 2007ProductionMinBias_FF
'0469'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8131012',	 last => '8131014',	 list => '',  beginTime => '20070511.061609'}, # 	2007-05-11	06:16:09	2007-05-11	07:51:01	timestamp = 2007Production2_FF
'0470'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8131016',	 last => '8131016',	 list => '',  beginTime => '20070511.075101'}, # 	2007-05-11	07:51:01	2007-05-11	08:42:42	timestamp = 2007ProductionMinBias_FF
'0471'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8131024',	 last => '8131024',	 list => '',  beginTime => '20070511.084242'}, # 	2007-05-11	08:42:42	2007-05-11	09:10:21
'0472'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8131026',	 last => '8131027',	 list => '',  beginTime => '20070511.091021'}, # 	2007-05-11	09:10:21	2007-05-11	17:05:57
'0473'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8131050',	 last => '8131051',	 list => '',  beginTime => '20070511.170557'}, # 	2007-05-11	17:05:57	2007-05-11	18:07:43	timestamp = 2007Production2_FF
'0474'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8131057',	 last => '8131057',	 list => '',  beginTime => '20070511.180743'}, # 	2007-05-11	18:07:43	2007-05-11	18:43:16
'0475'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8131059',	 last => '8131061',	 list => '',  beginTime => '20070511.184316'}, # 	2007-05-11	18:43:16	2007-05-12	02:20:25	timestamp = 2007ProductionMinBias_FF
'0476'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8131089',	 last => '8131089',	 list => '',  beginTime => '20070512.022025'}, # 	2007-05-12	02:20:25	2007-05-12	17:04:48	timestamp = 2007Production2_FF
'0477'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8132014',	 last => '8132015',	 list => '',  beginTime => '20070512.170448'}, # 	2007-05-12	17:04:48	2007-05-12	17:51:14
'0478'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8132017',	 last => '8132017',	 list => '',  beginTime => '20070512.175114'}, # 	2007-05-12	17:51:14	2007-05-12	18:16:38	timestamp = 2007ProductionMinBias_FF
'0479'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8132019',	 last => '8132019',	 list => '',  beginTime => '20070512.181638'}, # 	2007-05-12	18:16:38	2007-05-12	18:36:03
'0480'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8132020',	 last => '8132020',	 list => '',  beginTime => '20070512.183603'}, # 	2007-05-12	18:36:03	2007-05-12	19:07:38	timestamp = 2007Production2_FF
'0481'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8132021',	 last => '8132024',	 list => '',  beginTime => '20070512.190738'}, # 	2007-05-12	19:07:38	2007-05-12	19:56:19	timestamp = 2007ProductionMinBias_FF
'0482'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8132026',	 last => '8132026',	 list => '',  beginTime => '20070512.195619'}, # 	2007-05-12	19:56:19	2007-05-12	20:00:24	timestamp = 2007Production2_FF
'0483'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8132027',	 last => '8132027',	 list => '',  beginTime => '20070512.200024'}, # 	2007-05-12	20:00:24	2007-05-13	04:28:02	timestamp = 2007ProductionMinBias_FF
'0484'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8133006',	 last => '8133006',	 list => '',  beginTime => '20070513.042802'}, # 	2007-05-13	04:28:02	2007-05-13	04:35:17	timestamp = 2007Production2_FF
'0485'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8133008',	 last => '8133009',	 list => '',  beginTime => '20070513.043517'}, # 	2007-05-13	04:35:17	2007-05-13	05:23:32
'0486'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8133011',	 last => '8133011',	 list => '',  beginTime => '20070513.052332'}, # 	2007-05-13	05:23:32	2007-05-13	05:41:32
'0487'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8133015',	 last => '8133016',	 list => '',  beginTime => '20070513.054132'}, # 	2007-05-13	05:41:32	2007-05-13	06:13:38
'0488'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8133017',	 last => '8133022',	 list => '',  beginTime => '20070513.061338'}, # 	2007-05-13	06:13:38	2007-05-13	15:31:09	timestamp = 2007ProductionMinBias_FF
'0489'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8133036',	 last => '8133037',	 list => '',  beginTime => '20070513.153109'}, # 	2007-05-13	15:31:09	2007-05-13	16:18:02	timestamp = 2007Production2_FF
'0490'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8133039',	 last => '8133040',	 list => '',  beginTime => '20070513.161802'}, # 	2007-05-13	16:18:02	2007-05-13	17:08:21
'0491'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8133041',	 last => '8133042',	 list => '',  beginTime => '20070513.170821'}, # 	2007-05-13	17:08:21	2007-05-13	18:14:36	timestamp = 2007ProductionMinBias_FF
'0492'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8133045',	 last => '8133048',	 list => '',  beginTime => '20070513.181436'}, # 	2007-05-13	18:14:36	2007-05-13	22:00:38
'0493'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8133062',	 last => '8133063',	 list => '',  beginTime => '20070513.220038'}, # 	2007-05-13	22:00:38	2007-05-13	22:45:45	timestamp = 2007Production2_FF
'0494'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8133066',	 last => '8133066',	 list => '',  beginTime => '20070513.224545'}, # 	2007-05-13	22:45:45	2007-05-13	23:09:02
'0495'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8133067',	 last => '8133070',	 list => '',  beginTime => '20070513.230902'}, # 	2007-05-13	23:09:02	2007-05-14	01:15:29	timestamp = 2007ProductionMinBias_FF
'0496'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8133078',	 last => '8133080',	 list => '',  beginTime => '20070514.011529'}, # 	2007-05-14	01:15:29	2007-05-14	02:01:25
'0497'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8133083',	 last => '8133083',	 list => '',  beginTime => '20070514.020125'}, # 	2007-05-14	02:01:25	2007-05-14	04:51:03
'0498'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8134007',	 last => '8134008',	 list => '',  beginTime => '20070514.045103'}, # 	2007-05-14	04:51:03	2007-05-14	05:16:39
'0499'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8134010',	 last => '8134010',	 list => '',  beginTime => '20070514.051639'}, # 	2007-05-14	05:16:39	2007-05-14	05:37:22
'0500'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8134013',	 last => '8134014',	 list => '',  beginTime => '20070514.053722'}, # 	2007-05-14	05:37:22	2007-05-14	07:19:35	timestamp = 2007Production2_FF
'0501'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8134015',	 last => '8134016',	 list => '',  beginTime => '20070514.071935'}, # 	2007-05-14	07:19:35	2007-05-14	08:42:53	timestamp = 2007ProductionMinBias_FF
'0502'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8134019',	 last => '8134021',	 list => '',  beginTime => '20070514.084253'}, # 	2007-05-14	08:42:53	2007-05-14	17:33:16
'0503'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8134036',	 last => '8134037',	 list => '',  beginTime => '20070514.173316'}, # 	2007-05-14	17:33:16	2007-05-14	18:21:41	timestamp = 2007Production2_FF
'0504'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8134039',	 last => '8134040',	 list => '',  beginTime => '20070514.182141'}, # 	2007-05-14	18:21:41	2007-05-14	19:11:29
'0505'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8134041',	 last => '8134041',	 list => '',  beginTime => '20070514.191129'}, # 	2007-05-14	19:11:29	2007-05-15	00:36:43	timestamp = 2007ProductionMinBias_FF
'0506'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8134057',	 last => '8134057',	 list => '',  beginTime => '20070515.003643'}, # 	2007-05-15	00:36:43	2007-05-15	01:14:03	timestamp = 2007Production2_FF
'0507'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8134059',	 last => '8134064',	 list => '',  beginTime => '20070515.011403'}, # 	2007-05-15	01:14:03	2007-05-15	04:19:32	timestamp = 2007ProductionMinBias_FF
'0508'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8135002',	 last => '8135002',	 list => '',  beginTime => '20070515.041932'}, # 	2007-05-15	04:19:32	2007-05-15	06:43:47
'0509'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8135019',	 last => '8135020',	 list => '',  beginTime => '20070515.064347'}, # 	2007-05-15	06:43:47	2007-05-15	07:36:27	timestamp = 2007Production2_FF
'0510'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8135023',	 last => '8135024',	 list => '',  beginTime => '20070515.073627'}, # 	2007-05-15	07:36:27	2007-05-15	08:44:34
'0511'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8135025',	 last => '8135027',	 list => '',  beginTime => '20070515.084434'}, # 	2007-05-15	08:44:34	2007-05-15	09:45:23	timestamp = 2007ProductionMinBias_FF
'0512'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8135029',	 last => '8135032',	 list => '',  beginTime => '20070515.094523'}, # 	2007-05-15	09:45:23	2007-05-15	12:31:45
'0513'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8135048',	 last => '8135050',	 list => '',  beginTime => '20070515.123145'}, # 	2007-05-15	12:31:45	2007-05-15	13:20:03	timestamp = 2007Production2_FF
'0514'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8135052',	 last => '8135053',	 list => '',  beginTime => '20070515.132003'}, # 	2007-05-15	13:20:03	2007-05-15	13:51:12
'0515'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8135054',	 last => '8135057',	 list => '',  beginTime => '20070515.135112'}, # 	2007-05-15	13:51:12	2007-05-15	14:50:44	timestamp = 2007ProductionMinBias_FF
'0516'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8135060',	 last => '8135062',	 list => '',  beginTime => '20070515.145044'}, # 	2007-05-15	14:50:44	2007-05-15	15:34:09
'0517'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8135064',	 last => '8135064',	 list => '',  beginTime => '20070515.153409'}, # 	2007-05-15	15:34:09	2007-05-15	15:46:08
'0518'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8135067',	 last => '8135067',	 list => '',  beginTime => '20070515.154608'}, # 	2007-05-15	15:46:08	2007-05-15	16:06:26
'0519'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8135070',	 last => '8135074',	 list => '',  beginTime => '20070515.160626'}, # 	2007-05-15	16:06:26	2007-05-15	22:41:01
'0520'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8135097',	 last => '8135101',	 list => '',  beginTime => '20070515.224101'}, # 	2007-05-15	22:41:01	2007-05-15	23:51:54	timestamp = 2007Production2_FF
'0521'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8135106',	 last => '8135108',	 list => '',  beginTime => '20070515.235154'}, # 	2007-05-15	23:51:54	2007-05-16	07:24:13
'0522'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8136011',	 last => '8136012',	 list => '',  beginTime => '20070516.072413'}, # 	2007-05-16	07:24:13	2007-05-16	08:09:56
'0523'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8136014',	 last => '8136015',	 list => '',  beginTime => '20070516.080956'}, # 	2007-05-16	08:09:56	2007-05-16	21:07:03	timestamp = 2007ProductionMinBias_FF
'0524'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8136053',	 last => '8136055',	 list => '',  beginTime => '20070516.210703'}, # 	2007-05-16	21:07:03	2007-05-16	22:20:05	timestamp = 2007Production2_FF
'0525'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8136058',	 last => '8136060',	 list => '',  beginTime => '20070516.222005'}, # 	2007-05-16	22:20:05	2007-05-16	23:06:55
'0526'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8136061',	 last => '8136062',	 list => '',  beginTime => '20070516.230655'}, # 	2007-05-16	23:06:55	2007-05-16	23:31:08	timestamp = 2007ProductionMinBias_FF
'0527'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8136063',	 last => '8136063',	 list => '',  beginTime => '20070516.233108'}, # 	2007-05-16	23:31:08	2007-05-16	23:55:09	timestamp = 2007Production2_FF
'0528'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8136067',	 last => '8136067',	 list => '',  beginTime => '20070516.235509'}, # 	2007-05-16	23:55:09	2007-05-17	00:04:45	timestamp = 2007ProductionMinBias_FF
'0529'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8136068',	 last => '8136068',	 list => '',  beginTime => '20070517.000445'}, # 	2007-05-17	00:04:45	2007-05-17	00:06:45	timestamp = 2007Production2_FF
'0530'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8136069',	 last => '8136073',	 list => '',  beginTime => '20070517.000645'}, # 	2007-05-17	00:06:45	2007-05-17	00:35:33	timestamp = 2007ProductionMinBias_FF
'0531'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8136076',	 last => '8136078',	 list => '',  beginTime => '20070517.003533'}, # 	2007-05-17	00:35:33	2007-05-17	00:54:10
'0532'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8136080',	 last => '8136083',	 list => '',  beginTime => '20070517.005410'}, # 	2007-05-17	00:54:10	2007-05-17	02:37:33
'0533'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8136092',	 last => '8136093',	 list => '',  beginTime => '20070517.023733'}, # 	2007-05-17	02:37:33	2007-05-17	03:29:46	timestamp = 2007Production2_FF
'0534'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8136095',	 last => '8136096',	 list => '',  beginTime => '20070517.032946'}, # 	2007-05-17	03:29:46	2007-05-17	04:26:31
'0535'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8137001',	 last => '8137001',	 list => '',  beginTime => '20070517.042631'}, # 	2007-05-17	04:26:31	2007-05-17	04:38:06
'0536'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8137002',	 last => '8137003',	 list => '',  beginTime => '20070517.043806'}, # 	2007-05-17	04:38:06	2007-05-17	05:53:56	timestamp = 2007ProductionMinBias_FF
'0537'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8137007',	 last => '8137009',	 list => '',  beginTime => '20070517.055356'}, # 	2007-05-17	05:53:56	2007-05-17	08:32:32
'0538'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8137017',	 last => '8137018',	 list => '',  beginTime => '20070517.083232'}, # 	2007-05-17	08:32:32	2007-05-17	09:27:17	timestamp = 2007Production2_FF
'0539'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8137020',	 last => '8137021',	 list => '',  beginTime => '20070517.092717'}, # 	2007-05-17	09:27:17	2007-05-17	10:19:43
'0540'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8137022',	 last => '8137024',	 list => '',  beginTime => '20070517.101943'}, # 	2007-05-17	10:19:43	2007-05-17	11:39:30	timestamp = 2007ProductionMinBias_FF
'0541'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8137026',	 last => '8137029',	 list => '',  beginTime => '20070517.113930'}, # 	2007-05-17	11:39:30	2007-05-18	00:07:00
'0542'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8137070',	 last => '8137072',	 list => '',  beginTime => '20070518.000700'}, # 	2007-05-18	00:07:00	2007-05-18	01:40:39	timestamp = 2007Production2_FF
'0543'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8137075',	 last => '8137076',	 list => '',  beginTime => '20070518.014039'}, # 	2007-05-18	01:40:39	2007-05-18	02:29:30
'0544'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8137077',	 last => '8137080',	 list => '',  beginTime => '20070518.022930'}, # 	2007-05-18	02:29:30	2007-05-18	04:11:22	timestamp = 2007ProductionMinBias_FF
'0545'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8138001',	 last => '8138001',	 list => '',  beginTime => '20070518.041122'}, # 	2007-05-18	04:11:22	2007-05-18	04:30:21
'0546'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8138003',	 last => '8138003',	 list => '',  beginTime => '20070518.043021'}, # 	2007-05-18	04:30:21	2007-05-18	05:58:51
'0547'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8138014',	 last => '8138017',	 list => '',  beginTime => '20070518.055851'}, # 	2007-05-18	05:58:51	2007-05-18	07:13:00	timestamp = 2007Production2_FF
'0548'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8138019',	 last => '8138021',	 list => '',  beginTime => '20070518.071300'}, # 	2007-05-18	07:13:00	2007-05-18	08:08:50
'0549'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8138022',	 last => '8138023',	 list => '',  beginTime => '20070518.080850'}, # 	2007-05-18	08:08:50	2007-05-18	18:49:10	timestamp = 2007ProductionMinBias_FF
'0550'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8138066',	 last => '8138067',	 list => '',  beginTime => '20070518.184910'}, # 	2007-05-18	18:49:10	2007-05-18	19:30:38	timestamp = 2007Production2_FF
'0551'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8138069',	 last => '8138069',	 list => '',  beginTime => '20070518.193038'}, # 	2007-05-18	19:30:38	2007-05-18	19:46:33
'0552'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8138071',	 last => '8138071',	 list => '',  beginTime => '20070518.194633'}, # 	2007-05-18	19:46:33	2007-05-18	20:29:37
'0553'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8138072',	 last => '8138077',	 list => '',  beginTime => '20070518.202937'}, # 	2007-05-18	20:29:37	2007-05-18	22:54:11	timestamp = 2007ProductionMinBias_FF
'0554'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8138080',	 last => '8138080',	 list => '',  beginTime => '20070518.225411'}, # 	2007-05-18	22:54:11	2007-05-19	01:46:40
'0555'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8138091',	 last => '8138092',	 list => '',  beginTime => '20070519.014640'}, # 	2007-05-19	01:46:40	2007-05-19	02:50:43	timestamp = 2007Production2_FF
'0556'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8138097',	 last => '8138098',	 list => '',  beginTime => '20070519.025043'}, # 	2007-05-19	02:50:43	2007-05-19	03:51:29
'0557'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8138099',	 last => '8138099',	 list => '',  beginTime => '20070519.035129'}, # 	2007-05-19	03:51:29	2007-05-19	04:14:33	timestamp = 2007ProductionMinBias_FF
'0558'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8139001',	 last => '8139005',	 list => '',  beginTime => '20070519.041433'}, # 	2007-05-19	04:14:33	2007-05-19	07:32:16
'0559'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8139015',	 last => '8139017',	 list => '',  beginTime => '20070519.073216'}, # 	2007-05-19	07:32:16	2007-05-19	08:44:10	timestamp = 2007Production2_FF
'0560'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8139020',	 last => '8139021',	 list => '',  beginTime => '20070519.084410'}, # 	2007-05-19	08:44:10	2007-05-19	09:43:09
'0561'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8139022',	 last => '8139026',	 list => '',  beginTime => '20070519.094309'}, # 	2007-05-19	09:43:09	2007-05-19	11:51:20	timestamp = 2007ProductionMinBias_FF
'0562'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8139028',	 last => '8139028',	 list => '',  beginTime => '20070519.115120'}, # 	2007-05-19	11:51:20	2007-05-19	13:13:44
'0563'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8139042',	 last => '8139042',	 list => '',  beginTime => '20070519.131344'}, # 	2007-05-19	13:13:44	2007-05-19	14:06:57	timestamp = 2007Production2_FF
'0564'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8139044',	 last => '8139044',	 list => '',  beginTime => '20070519.140657'}, # 	2007-05-19	14:06:57	2007-05-19	14:50:53
'0565'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8139045',	 last => '8139049',	 list => '',  beginTime => '20070519.145053'}, # 	2007-05-19	14:50:53	2007-05-19	16:56:15	timestamp = 2007ProductionMinBias_FF
'0566'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8139051',	 last => '8139054',	 list => '',  beginTime => '20070519.165615'}, # 	2007-05-19	16:56:15	2007-05-19	19:26:24
'0567'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8139064',	 last => '8139065',	 list => '',  beginTime => '20070519.192624'}, # 	2007-05-19	19:26:24	2007-05-19	20:25:17	timestamp = 2007Production2_FF
'0568'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8139067',	 last => '8139068',	 list => '',  beginTime => '20070519.202517'}, # 	2007-05-19	20:25:17	2007-05-19	21:55:00
'0569'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8139069',	 last => '8139072',	 list => '',  beginTime => '20070519.215500'}, # 	2007-05-19	21:55:00	2007-05-20	01:39:53	timestamp = 2007ProductionMinBias_FF
'0570'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8139086',	 last => '8139086',	 list => '',  beginTime => '20070520.013953'}, # 	2007-05-20	01:39:53	2007-05-20	01:50:02	timestamp = 2007Production2_FF
'0571'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8139091',	 last => '8139092',	 list => '',  beginTime => '20070520.015002'}, # 	2007-05-20	01:50:02	2007-05-20	03:15:10
'0572'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8139095',	 last => '8139095',	 list => '',  beginTime => '20070520.031510'}, # 	2007-05-20	03:15:10	2007-05-20	03:33:29
'0573'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8139096',	 last => '8139096',	 list => '',  beginTime => '20070520.033329'}, # 	2007-05-20	03:33:29	2007-05-20	03:54:46	timestamp = 2007ProductionMinBias_FF
'0574'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8139097',	 last => '8139097',	 list => '',  beginTime => '20070520.035446'}, # 	2007-05-20	03:54:46	2007-05-20	06:41:01	timestamp = 2007Production2_FF
'0575'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8140013',	 last => '8140015',	 list => '',  beginTime => '20070520.064101'}, # 	2007-05-20	06:41:01	2007-05-20	07:44:50
'0576'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8140017',	 last => '8140022',	 list => '',  beginTime => '20070520.074450'}, # 	2007-05-20	07:44:50	2007-05-20	12:14:51
'0577'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8140035',	 last => '8140035',	 list => '',  beginTime => '20070520.121451'}, # 	2007-05-20	12:14:51	2007-05-20	13:06:04
'0578'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8140037',	 last => '8140037',	 list => '',  beginTime => '20070520.130604'}, # 	2007-05-20	13:06:04	2007-05-20	14:44:20
'0579'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8140039',	 last => '8140040',	 list => '',  beginTime => '20070520.144420'}, # 	2007-05-20	14:44:20	2007-05-20	15:51:29
'0580'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8140042',	 last => '8140042',	 list => '',  beginTime => '20070520.155129'}, # 	2007-05-20	15:51:29	2007-05-20	23:17:02
'0581'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8140058',	 last => '8140058',	 list => '',  beginTime => '20070520.231702'}, # 	2007-05-20	23:17:02	2007-05-20	23:30:13	timestamp = 2007ProductionMinBias_FF
'0582'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8140059',	 last => '8140061',	 list => '',  beginTime => '20070520.233013'}, # 	2007-05-20	23:30:13	2007-05-21	00:37:13	timestamp = 2007Production2_FF
'0583'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8140064',	 last => '8140065',	 list => '',  beginTime => '20070521.003713'}, # 	2007-05-21	00:37:13	2007-05-21	01:24:23
'0584'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8140066',	 last => '8140068',	 list => '',  beginTime => '20070521.012423'}, # 	2007-05-21	01:24:23	2007-05-21	03:19:19	timestamp = 2007ProductionMinBias_FF
'0585'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8140076',	 last => '8140076',	 list => '',  beginTime => '20070521.031919'}, # 	2007-05-21	03:19:19	2007-05-21	04:34:21
'0586'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8141012',	 last => '8141014',	 list => '',  beginTime => '20070521.043421'}, # 	2007-05-21	04:34:21	2007-05-21	06:00:22	timestamp = 2007Production2_FF
'0587'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8141016',	 last => '8141017',	 list => '',  beginTime => '20070521.060022'}, # 	2007-05-21	06:00:22	2007-05-21	07:03:56
'0588'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8141018',	 last => '8141020',	 list => '',  beginTime => '20070521.070356'}, # 	2007-05-21	07:03:56	2007-05-21	08:47:36	timestamp = 2007ProductionMinBias_FF
'0589'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8141027',	 last => '8141027',	 list => '',  beginTime => '20070521.084736'}, # 	2007-05-21	08:47:36	2007-05-21	10:17:29
'0590'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8141041',	 last => '8141043',	 list => '',  beginTime => '20070521.101729'}, # 	2007-05-21	10:17:29	2007-05-21	11:31:10	timestamp = 2007Production2_FF
'0591'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8141045',	 last => '8141046',	 list => '',  beginTime => '20070521.113110'}, # 	2007-05-21	11:31:10	2007-05-21	12:07:11
'0592'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8141047',	 last => '8141048',	 list => '',  beginTime => '20070521.120711'}, # 	2007-05-21	12:07:11	2007-05-21	19:41:41	timestamp = 2007ProductionMinBias_FF
'0593'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8141069',	 last => '8141071',	 list => '',  beginTime => '20070521.194141'}, # 	2007-05-21	19:41:41	2007-05-21	20:51:07	timestamp = 2007Production2_FF
'0594'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8141073',	 last => '8141073',	 list => '',  beginTime => '20070521.205107'}, # 	2007-05-21	20:51:07	2007-05-21	21:04:23
'0595'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8141074',	 last => '8141076',	 list => '',  beginTime => '20070521.210423'}, # 	2007-05-21	21:04:23	2007-05-21	22:21:38	timestamp = 2007ProductionMinBias_FF
'0596'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8141079',	 last => '8141080',	 list => '',  beginTime => '20070521.222138'}, # 	2007-05-21	22:21:38	2007-05-22	00:26:54
'0597'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8141105',	 last => '8141106',	 list => '',  beginTime => '20070522.002654'}, # 	2007-05-22	00:26:54	2007-05-22	02:10:01	timestamp = 2007Production2_FF
'0598'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8141109',	 last => '8141109',	 list => '',  beginTime => '20070522.021001'}, # 	2007-05-22	02:10:01	2007-05-22	02:45:55
'0599'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8141110',	 last => '8141113',	 list => '',  beginTime => '20070522.024555'}, # 	2007-05-22	02:45:55	2007-05-22	04:09:49	timestamp = 2007ProductionMinBias_FF
'0600'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8142001',	 last => '8142001',	 list => '',  beginTime => '20070522.040949'}, # 	2007-05-22	04:09:49	2007-05-22	15:59:50
'0601'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8142021',	 last => '8142023',	 list => '',  beginTime => '20070522.155950'}, # 	2007-05-22	15:59:50	2007-05-22	16:59:04	timestamp = 2007Production2_FF
'0602'=> {trig=>'2007Production2',       	field => 'FF',	first=> '8142025',	 last => '8142026',	 list => '',  beginTime => '20070522.165904'}, # 	2007-05-22	16:59:04	2007-05-22	17:59:37
'0603'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8142027',	 last => '8142031',	 list => '',  beginTime => '20070522.175937'}, # 	2007-05-22	17:59:37	2007-05-22	19:26:23	timestamp = 2007ProductionMinBias_FF
'0604'=> {trig=>'2007ProductionMinBias', 	field => 'FF',	first=> '8142034',	 last => '8142034',	 list => '',  beginTime => '20070522.192623'}, # 	2007-05-22	19:26:23	2007-05-23	22:44:55
'0605'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8143049',	 last => '8143049',	 list => '',  beginTime => '20070523.224455'}, # 	2007-05-23	22:44:55	2007-05-23	23:23:03	timestamp = 2007Production2_RF
'0606'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8143053',	 last => '8143054',	 list => '',  beginTime => '20070523.232303'}, # 	2007-05-23	23:23:03	2007-05-24	00:08:59
'0607'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8143056',	 last => '8143056',	 list => '',  beginTime => '20070524.000859'}, # 	2007-05-24	00:08:59	2007-05-24	00:52:23
'0608'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8143057',	 last => '8143058',	 list => '',  beginTime => '20070524.005223'}, # 	2007-05-24	00:52:23	2007-05-24	02:22:05	timestamp = 2007ProductionMinBias_RF
'0609'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8143061',	 last => '8143062',	 list => '',  beginTime => '20070524.022205'}, # 	2007-05-24	02:22:05	2007-05-24	21:59:55
'0610'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8144015',	 last => '8144016',	 list => '',  beginTime => '20070524.215955'}, # 	2007-05-24	21:59:55	2007-05-24	22:59:55	timestamp = 2007Production2_RF
'0611'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8144018',	 last => '8144021',	 list => '',  beginTime => '20070524.225955'}, # 	2007-05-24	22:59:55	2007-05-25	01:02:54	timestamp = 2007ProductionMinBias_RF
'0612'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8144023',	 last => '8144025',	 list => '',  beginTime => '20070525.010254'}, # 	2007-05-25	01:02:54	2007-05-25	03:46:13
'0613'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8144035',	 last => '8144036',	 list => '',  beginTime => '20070525.034613'}, # 	2007-05-25	03:46:13	2007-05-25	04:46:40	timestamp = 2007Production2_RF
'0614'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8145004',	 last => '8145005',	 list => '',  beginTime => '20070525.044640'}, # 	2007-05-25	04:46:40	2007-05-25	05:39:06
'0615'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8145006',	 last => '8145006',	 list => '',  beginTime => '20070525.053906'}, # 	2007-05-25	05:39:06	2007-05-25	06:01:28	timestamp = 2007ProductionMinBias_RF
'0616'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8145008',	 last => '8145012',	 list => '',  beginTime => '20070525.060128'}, # 	2007-05-25	06:01:28	2007-05-25	21:38:24
'0617'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8145062',	 last => '8145064',	 list => '',  beginTime => '20070525.213824'}, # 	2007-05-25	21:38:24	2007-05-25	22:47:05	timestamp = 2007Production2_RF
'0618'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8145067',	 last => '8145069',	 list => '',  beginTime => '20070525.224705'}, # 	2007-05-25	22:47:05	2007-05-25	23:17:29
'0619'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8145071',	 last => '8145071',	 list => '',  beginTime => '20070525.231729'}, # 	2007-05-25	23:17:29	2007-05-25	23:35:02	timestamp = 2007ProductionMinBias_RF
'0620'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8145073',	 last => '8145074',	 list => '',  beginTime => '20070525.233502'}, # 	2007-05-25	23:35:02	2007-05-26	00:18:43
'0621'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8145076',	 last => '8145077',	 list => '',  beginTime => '20070526.001843'}, # 	2007-05-26	00:18:43	2007-05-26	01:08:52
'0622'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8145079',	 last => '8145080',	 list => '',  beginTime => '20070526.010852'}, # 	2007-05-26	01:08:52	2007-05-26	03:02:46
'0623'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8145094',	 last => '8145095',	 list => '',  beginTime => '20070526.030246'}, # 	2007-05-26	03:02:46	2007-05-26	04:00:20	timestamp = 2007Production2_RF
'0624'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8146001',	 last => '8146002',	 list => '',  beginTime => '20070526.040020'}, # 	2007-05-26	04:00:20	2007-05-26	04:56:54
'0625'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8146003',	 last => '8146003',	 list => '',  beginTime => '20070526.045654'}, # 	2007-05-26	04:56:54	2007-05-26	05:24:05	timestamp = 2007ProductionMinBias_RF
'0626'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8146005',	 last => '8146006',	 list => '',  beginTime => '20070526.052405'}, # 	2007-05-26	05:24:05	2007-05-26	05:56:05
'0627'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8146008',	 last => '8146009',	 list => '',  beginTime => '20070526.055605'}, # 	2007-05-26	05:56:05	2007-05-26	06:40:06
'0628'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8146013',	 last => '8146014',	 list => '',  beginTime => '20070526.064006'}, # 	2007-05-26	06:40:06	2007-05-26	07:26:25
'0629'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8146016',	 last => '8146016',	 list => '',  beginTime => '20070526.072625'}, # 	2007-05-26	07:26:25	2007-05-26	07:41:29
'0630'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8146019',	 last => '8146019',	 list => '',  beginTime => '20070526.074129'}, # 	2007-05-26	07:41:29	2007-05-26	08:11:20
'0631'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8146022',	 last => '8146027',	 list => '',  beginTime => '20070526.081120'}, # 	2007-05-26	08:11:20	2007-05-26	10:31:50
'0632'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8146031',	 last => '8146031',	 list => '',  beginTime => '20070526.103150'}, # 	2007-05-26	10:31:50	2007-05-26	10:52:34
'0633'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8146033',	 last => '8146036',	 list => '',  beginTime => '20070526.105234'}, # 	2007-05-26	10:52:34	2007-05-26	13:27:04
'0634'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8146038',	 last => '8146039',	 list => '',  beginTime => '20070526.132704'}, # 	2007-05-26	13:27:04	2007-05-26	14:13:51
'0635'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8146041',	 last => '8146041',	 list => '',  beginTime => '20070526.141351'}, # 	2007-05-26	14:13:51	2007-05-26	14:32:29
'0636'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8146043',	 last => '8146045',	 list => '',  beginTime => '20070526.143229'}, # 	2007-05-26	14:32:29	2007-05-26	18:06:39
'0637'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8146059',	 last => '8146060',	 list => '',  beginTime => '20070526.180639'}, # 	2007-05-26	18:06:39	2007-05-26	19:08:47	timestamp = 2007Production2_RF
'0638'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8146062',	 last => '8146063',	 list => '',  beginTime => '20070526.190847'}, # 	2007-05-26	19:08:47	2007-05-26	20:09:23
'0639'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8146065',	 last => '8146068',	 list => '',  beginTime => '20070526.200923'}, # 	2007-05-26	20:09:23	2007-05-26	21:40:20	timestamp = 2007ProductionMinBias_RF
'0640'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8146071',	 last => '8146071',	 list => '',  beginTime => '20070526.214020'}, # 	2007-05-26	21:40:20	2007-05-27	00:47:03
'0641'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8146083',	 last => '8146083',	 list => '',  beginTime => '20070527.004703'}, # 	2007-05-27	00:47:03	2007-05-27	01:01:32	timestamp = 2007Production2_RF
'0642'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8146085',	 last => '8146087',	 list => '',  beginTime => '20070527.010132'}, # 	2007-05-27	01:01:32	2007-05-27	02:02:41
'0643'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8146089',	 last => '8146089',	 list => '',  beginTime => '20070527.020241'}, # 	2007-05-27	02:02:41	2007-05-27	02:34:30
'0644'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8146090',	 last => '8146092',	 list => '',  beginTime => '20070527.023430'}, # 	2007-05-27	02:34:30	2007-05-27	03:53:25	timestamp = 2007ProductionMinBias_RF
'0645'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8146095',	 last => '8146096',	 list => '',  beginTime => '20070527.035325'}, # 	2007-05-27	03:53:25	2007-05-27	04:21:54
'0646'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8147001',	 last => '8147001',	 list => '',  beginTime => '20070527.042154'}, # 	2007-05-27	04:21:54	2007-05-27	04:35:34
'0647'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8147005',	 last => '8147006',	 list => '',  beginTime => '20070527.043534'}, # 	2007-05-27	04:35:34	2007-05-27	06:30:49
'0648'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8147018',	 last => '8147019',	 list => '',  beginTime => '20070527.063049'}, # 	2007-05-27	06:30:49	2007-05-27	07:19:09	timestamp = 2007Production2_RF
'0649'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8147021',	 last => '8147022',	 list => '',  beginTime => '20070527.071909'}, # 	2007-05-27	07:19:09	2007-05-27	08:11:21
'0650'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8147023',	 last => '8147026',	 list => '',  beginTime => '20070527.081121'}, # 	2007-05-27	08:11:21	2007-05-27	09:32:39	timestamp = 2007ProductionMinBias_RF
'0651'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8147030',	 last => '8147031',	 list => '',  beginTime => '20070527.093239'}, # 	2007-05-27	09:32:39	2007-05-27	10:12:56
'0652'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8147033',	 last => '8147036',	 list => '',  beginTime => '20070527.101256'}, # 	2007-05-27	10:12:56	2007-05-27	13:11:12
'0653'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8147049',	 last => '8147050',	 list => '',  beginTime => '20070527.131112'}, # 	2007-05-27	13:11:12	2007-05-27	14:05:11	timestamp = 2007Production2_RF
'0654'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8147052',	 last => '8147053',	 list => '',  beginTime => '20070527.140511'}, # 	2007-05-27	14:05:11	2007-05-27	15:10:50
'0655'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8147055',	 last => '8147055',	 list => '',  beginTime => '20070527.151050'}, # 	2007-05-27	15:10:50	2007-05-27	15:21:51
'0656'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8147057',	 last => '8147057',	 list => '',  beginTime => '20070527.152151'}, # 	2007-05-27	15:21:51	2007-05-27	15:35:53
'0657'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8147058',	 last => '8147058',	 list => '',  beginTime => '20070527.153553'}, # 	2007-05-27	15:35:53	2007-05-27	22:23:41	timestamp = 2007ProductionMinBias_RF
'0658'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8147088',	 last => '8147089',	 list => '',  beginTime => '20070527.222341'}, # 	2007-05-27	22:23:41	2007-05-27	22:57:02	timestamp = 2007Production2_RF
'0659'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8147091',	 last => '8147092',	 list => '',  beginTime => '20070527.225702'}, # 	2007-05-27	22:57:02	2007-05-27	23:56:58
'0660'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8147094',	 last => '8147094',	 list => '',  beginTime => '20070527.235658'}, # 	2007-05-27	23:56:58	2007-05-28	00:31:34
'0661'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8147095',	 last => '8147096',	 list => '',  beginTime => '20070528.003134'}, # 	2007-05-28	00:31:34	2007-05-28	00:47:44	timestamp = 2007ProductionMinBias_RF
'0662'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8147098',	 last => '8147101',	 list => '',  beginTime => '20070528.004744'}, # 	2007-05-28	00:47:44	2007-05-28	02:05:21
'0663'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8147103',	 last => '8147104',	 list => '',  beginTime => '20070528.020521'}, # 	2007-05-28	02:05:21	2007-05-28	07:37:24
'0664'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8148008',	 last => '8148009',	 list => '',  beginTime => '20070528.073724'}, # 	2007-05-28	07:37:24	2007-05-28	08:31:43	timestamp = 2007Production2_RF
'0665'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8148012',	 last => '8148012',	 list => '',  beginTime => '20070528.083143'}, # 	2007-05-28	08:31:43	2007-05-28	16:10:41
'0666'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8148024',	 last => '8148025',	 list => '',  beginTime => '20070528.161041'}, # 	2007-05-28	16:10:41	2007-05-29	03:36:01
'0667'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8148037',	 last => '8148038',	 list => '',  beginTime => '20070529.033601'}, # 	2007-05-29	03:36:01	2007-05-29	04:08:13
'0668'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8149001',	 last => '8149001',	 list => '',  beginTime => '20070529.040813'}, # 	2007-05-29	04:08:13	2007-05-29	04:43:12
'0669'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8149003',	 last => '8149004',	 list => '',  beginTime => '20070529.044312'}, # 	2007-05-29	04:43:12	2007-05-29	05:27:46
'0670'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8149005',	 last => '8149005',	 list => '',  beginTime => '20070529.052746'}, # 	2007-05-29	05:27:46	2007-05-29	05:42:10	timestamp = 2007ProductionMinBias_RF
'0671'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8149007',	 last => '8149007',	 list => '',  beginTime => '20070529.054210'}, # 	2007-05-29	05:42:10	2007-05-29	05:55:58
'0672'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8149008',	 last => '8149008',	 list => '',  beginTime => '20070529.055558'}, # 	2007-05-29	05:55:58	2007-05-29	06:07:06	timestamp = 2007Production2_RF
'0673'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8149009',	 last => '8149012',	 list => '',  beginTime => '20070529.060706'}, # 	2007-05-29	06:07:06	2007-05-29	07:39:22	timestamp = 2007ProductionMinBias_RF
'0674'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8149014',	 last => '8149014',	 list => '',  beginTime => '20070529.073922'}, # 	2007-05-29	07:39:22	2007-05-29	09:14:29
'0675'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8149024',	 last => '8149025',	 list => '',  beginTime => '20070529.091429'}, # 	2007-05-29	09:14:29	2007-05-29	10:31:57	timestamp = 2007Production2_RF
'0676'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8149031',	 last => '8149031',	 list => '',  beginTime => '20070529.103157'}, # 	2007-05-29	10:31:57	2007-05-29	10:52:02
'0677'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8149032',	 last => '8149033',	 list => '',  beginTime => '20070529.105202'}, # 	2007-05-29	10:52:02	2007-05-29	11:50:59	timestamp = 2007ProductionMinBias_RF
'0678'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8149035',	 last => '8149035',	 list => '',  beginTime => '20070529.115059'}, # 	2007-05-29	11:50:59	2007-05-29	12:22:47
'0679'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8149037',	 last => '8149038',	 list => '',  beginTime => '20070529.122247'}, # 	2007-05-29	12:22:47	2007-05-29	13:10:37
'0680'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8149041',	 last => '8149042',	 list => '',  beginTime => '20070529.131037'}, # 	2007-05-29	13:10:37	2007-05-30	06:43:15
'0681'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8150010',	 last => '8150011',	 list => '',  beginTime => '20070530.064315'}, # 	2007-05-30	06:43:15	2007-05-30	07:08:29	timestamp = 2007Production2_RF
'0682'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8150014',	 last => '8150016',	 list => '',  beginTime => '20070530.070829'}, # 	2007-05-30	07:08:29	2007-05-30	08:40:39
'0683'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8150017',	 last => '8150018',	 list => '',  beginTime => '20070530.084039'}, # 	2007-05-30	08:40:39	2007-05-30	09:36:30	timestamp = 2007ProductionMinBias_RF
'0684'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8150020',	 last => '8150022',	 list => '',  beginTime => '20070530.093630'}, # 	2007-05-30	09:36:30	2007-05-30	22:38:20
'0685'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8150052',	 last => '8150053',	 list => '',  beginTime => '20070530.223820'}, # 	2007-05-30	22:38:20	2007-05-30	23:46:21	timestamp = 2007Production2_RF
'0686'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8150056',	 last => '8150056',	 list => '',  beginTime => '20070530.234621'}, # 	2007-05-30	23:46:21	2007-05-31	00:26:55
'0687'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8150058',	 last => '8150058',	 list => '',  beginTime => '20070531.002655'}, # 	2007-05-31	00:26:55	2007-05-31	00:37:51	timestamp = 2007ProductionMinBias_RF
'0688'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8150061',	 last => '8150061',	 list => '',  beginTime => '20070531.003751'}, # 	2007-05-31	00:37:51	2007-05-31	01:14:29
'0689'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8150063',	 last => '8150064',	 list => '',  beginTime => '20070531.011429'}, # 	2007-05-31	01:14:29	2007-05-31	04:52:38
'0690'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8151008',	 last => '8151010',	 list => '',  beginTime => '20070531.045238'}, # 	2007-05-31	04:52:38	2007-05-31	06:16:07	timestamp = 2007Production2_RF
'0691'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8151013',	 last => '8151013',	 list => '',  beginTime => '20070531.061607'}, # 	2007-05-31	06:16:07	2007-05-31	07:09:09
'0692'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8151016',	 last => '8151018',	 list => '',  beginTime => '20070531.070909'}, # 	2007-05-31	07:09:09	2007-05-31	20:05:07	timestamp = 2007ProductionMinBias_RF
'0693'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8151043',	 last => '8151044',	 list => '',  beginTime => '20070531.200507'}, # 	2007-05-31	20:05:07	2007-05-31	21:19:12	timestamp = 2007Production2_RF
'0694'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8151050',	 last => '8151051',	 list => '',  beginTime => '20070531.211912'}, # 	2007-05-31	21:19:12	2007-05-31	22:28:40
'0695'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8151052',	 last => '8151053',	 list => '',  beginTime => '20070531.222840'}, # 	2007-05-31	22:28:40	2007-05-31	22:59:04	timestamp = 2007ProductionMinBias_RF
'0696'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8151057',	 last => '8151057',	 list => '',  beginTime => '20070531.225904'}, # 	2007-05-31	22:59:04	2007-05-31	23:33:15
'0697'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8151059',	 last => '8151060',	 list => '',  beginTime => '20070531.233315'}, # 	2007-05-31	23:33:15	2007-06-01	01:31:48
'0698'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8151072',	 last => '8151073',	 list => '',  beginTime => '20070601.013148'}, # 	2007-06-01	01:31:48	2007-06-01	02:31:07	timestamp = 2007Production2_RF
'0699'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8151075',	 last => '8151076',	 list => '',  beginTime => '20070601.023107'}, # 	2007-06-01	02:31:07	2007-06-01	03:03:17
'0700'=> {trig=>'2007Production2',       	field => 'RHF',	first=> '8151076',	 last => '8151076',	 list => '',  beginTime => '20070601.030317'}, # 	2007-06-01	03:03:17	2007-06-01	12:36:30	timestamp = 2007Production2_RHF
'0701'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8152009',	 last => '8152010',	 list => '',  beginTime => '20070601.123630'}, # 	2007-06-01	12:36:30	2007-06-01	14:10:53	timestamp = 2007Production2_RF
'0702'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8152017',	 last => '8152018',	 list => '',  beginTime => '20070601.141053'}, # 	2007-06-01	14:10:53	2007-06-01	15:10:07
'0703'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8152020',	 last => '8152022',	 list => '',  beginTime => '20070601.151007'}, # 	2007-06-01	15:10:07	2007-06-01	16:18:40	timestamp = 2007ProductionMinBias_RF
'0704'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8152024',	 last => '8152024',	 list => '',  beginTime => '20070601.161840'}, # 	2007-06-01	16:18:40	2007-06-01	16:46:57
'0705'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8152026',	 last => '8152026',	 list => '',  beginTime => '20070601.164657'}, # 	2007-06-01	16:46:57	2007-06-02	03:49:53
'0706'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8152059',	 last => '8152059',	 list => '',  beginTime => '20070602.034953'}, # 	2007-06-02	03:49:53	2007-06-02	04:14:35	timestamp = 2007Production2_RF
'0707'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8153001',	 last => '8153001',	 list => '',  beginTime => '20070602.041435'}, # 	2007-06-02	04:14:35	2007-06-02	04:57:47
'0708'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8153004',	 last => '8153005',	 list => '',  beginTime => '20070602.045747'}, # 	2007-06-02	04:57:47	2007-06-02	06:13:30
'0709'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8153006',	 last => '8153008',	 list => '',  beginTime => '20070602.061330'}, # 	2007-06-02	06:13:30	2007-06-02	06:43:44	timestamp = 2007ProductionMinBias_RF
'0710'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8153010',	 last => '8153010',	 list => '',  beginTime => '20070602.064344'}, # 	2007-06-02	06:43:44	2007-06-02	07:05:00
'0711'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8153013',	 last => '8153019',	 list => '',  beginTime => '20070602.070500'}, # 	2007-06-02	07:05:00	2007-06-02	13:44:50
'0712'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8153032',	 last => '8153032',	 list => '',  beginTime => '20070602.134450'}, # 	2007-06-02	13:44:50	2007-06-02	23:29:35	timestamp = 2007Production2_RF
'0713'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8153049',	 last => '8153050',	 list => '',  beginTime => '20070602.232935'}, # 	2007-06-02	23:29:35	2007-06-03	00:30:11	timestamp = 2007ProductionMinBias_RF
'0714'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8153052',	 last => '8153056',	 list => '',  beginTime => '20070603.003011'}, # 	2007-06-03	00:30:11	2007-06-03	18:26:29
'0715'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8154024',	 last => '8154027',	 list => '',  beginTime => '20070603.182629'}, # 	2007-06-03	18:26:29	2007-06-03	19:40:54	timestamp = 2007Production2_RF
'0716'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8154029',	 last => '8154029',	 list => '',  beginTime => '20070603.194054'}, # 	2007-06-03	19:40:54	2007-06-03	20:20:37
'0717'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8154031',	 last => '8154033',	 list => '',  beginTime => '20070603.202037'}, # 	2007-06-03	20:20:37	2007-06-03	21:33:08
'0718'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8154034',	 last => '8154035',	 list => '',  beginTime => '20070603.213308'}, # 	2007-06-03	21:33:08	2007-06-03	22:30:44	timestamp = 2007ProductionMinBias_RF
'0719'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8154037',	 last => '8154037',	 list => '',  beginTime => '20070603.223044'}, # 	2007-06-03	22:30:44	2007-06-04	07:03:35
'0720'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8155009',	 last => '8155010',	 list => '',  beginTime => '20070604.070335'}, # 	2007-06-04	07:03:35	2007-06-04	07:44:12	timestamp = 2007Production2_RF
'0721'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8155012',	 last => '8155013',	 list => '',  beginTime => '20070604.074412'}, # 	2007-06-04	07:44:12	2007-06-04	08:47:02
'0722'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8155014',	 last => '8155016',	 list => '',  beginTime => '20070604.084702'}, # 	2007-06-04	08:47:02	2007-06-04	23:04:14	timestamp = 2007ProductionMinBias_RF
'0723'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8155040',	 last => '8155040',	 list => '',  beginTime => '20070604.230414'}, # 	2007-06-04	23:04:14	2007-06-04	23:18:57	timestamp = 2007Production2_RF
'0724'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8155041',	 last => '8155041',	 list => '',  beginTime => '20070604.231857'}, # 	2007-06-04	23:18:57	2007-06-04	23:21:42	timestamp = 2007ProductionMinBias_RF
'0725'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8155042',	 last => '8155043',	 list => '',  beginTime => '20070604.232142'}, # 	2007-06-04	23:21:42	2007-06-04	23:33:23	timestamp = 2007Production2_RF
'0726'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8155045',	 last => '8155045',	 list => '',  beginTime => '20070604.233323'}, # 	2007-06-04	23:33:23	2007-06-04	23:42:55	timestamp = 2007ProductionMinBias_RF
'0727'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8155046',	 last => '8155046',	 list => '',  beginTime => '20070604.234255'}, # 	2007-06-04	23:42:55	2007-06-05	04:30:34	timestamp = 2007Production2_RF
'0728'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8156006',	 last => '8156010',	 list => '',  beginTime => '20070605.043034'}, # 	2007-06-05	04:30:34	2007-06-05	05:53:42
'0729'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8156012',	 last => '8156013',	 list => '',  beginTime => '20070605.055342'}, # 	2007-06-05	05:53:42	2007-06-05	06:45:18
'0730'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8156014',	 last => '8156019',	 list => '',  beginTime => '20070605.064518'}, # 	2007-06-05	06:45:18	2007-06-05	10:09:33	timestamp = 2007ProductionMinBias_RF
'0731'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8156029',	 last => '8156031',	 list => '',  beginTime => '20070605.100933'}, # 	2007-06-05	10:09:33	2007-06-05	11:09:33	timestamp = 2007Production2_RF
'0732'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8156033',	 last => '8156034',	 list => '',  beginTime => '20070605.110933'}, # 	2007-06-05	11:09:33	2007-06-05	15:15:06
'0733'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8156048',	 last => '8156049',	 list => '',  beginTime => '20070605.151506'}, # 	2007-06-05	15:15:06	2007-06-05	16:28:47
'0734'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8156051',	 last => '8156051',	 list => '',  beginTime => '20070605.162847'}, # 	2007-06-05	16:28:47	2007-06-05	16:51:47
'0735'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8156052',	 last => '8156052',	 list => '',  beginTime => '20070605.165147'}, # 	2007-06-05	16:51:47	2007-06-05	17:19:48	timestamp = 2007ProductionMinBias_RF
'0736'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8156054',	 last => '8156057',	 list => '',  beginTime => '20070605.171948'}, # 	2007-06-05	17:19:48	2007-06-05	21:51:02
'0737'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8156106',	 last => '8156110',	 list => '',  beginTime => '20070605.215102'}, # 	2007-06-05	21:51:02	2007-06-05	23:19:59	timestamp = 2007Production2_RF
'0738'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8156112',	 last => '8156112',	 list => '',  beginTime => '20070605.231959'}, # 	2007-06-05	23:19:59	2007-06-06	00:00:34
'0739'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8156113',	 last => '8156115',	 list => '',  beginTime => '20070606.000034'}, # 	2007-06-06	00:00:34	2007-06-08	00:54:07	timestamp = 2007ProductionMinBias_RF
'0740'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8158161',	 last => '8158167',	 list => '',  beginTime => '20070608.005407'}, # 	2007-06-08	00:54:07	2007-06-08	02:49:23	timestamp = 2007Production2_RF
'0741'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8158170',	 last => '8158172',	 list => '',  beginTime => '20070608.024923'}, # 	2007-06-08	02:49:23	2007-06-08	03:43:58
'0742'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8158174',	 last => '8158174',	 list => '',  beginTime => '20070608.034358'}, # 	2007-06-08	03:43:58	2007-06-08	03:55:47	timestamp = 2007ProductionMinBias_RF
'0743'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8158176',	 last => '8158176',	 list => '',  beginTime => '20070608.035547'}, # 	2007-06-08	03:55:47	2007-06-08	04:23:45
'0744'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8159001',	 last => '8159003',	 list => '',  beginTime => '20070608.042345'}, # 	2007-06-08	04:23:45	2007-06-08	13:47:23
'0745'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8159015',	 last => '8159015',	 list => '',  beginTime => '20070608.134723'}, # 	2007-06-08	13:47:23	2007-06-08	14:00:41	timestamp = 2007Production2_RF
'0746'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8159018',	 last => '8159018',	 list => '',  beginTime => '20070608.140041'}, # 	2007-06-08	14:00:41	2007-06-08	14:11:57
'0747'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8159021',	 last => '8159021',	 list => '',  beginTime => '20070608.141157'}, # 	2007-06-08	14:11:57	2007-06-08	14:42:48
'0748'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8159027',	 last => '8159028',	 list => '',  beginTime => '20070608.144248'}, # 	2007-06-08	14:42:48	2007-06-08	15:22:11
'0749'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8159031',	 last => '8159033',	 list => '',  beginTime => '20070608.152211'}, # 	2007-06-08	15:22:11	2007-06-08	23:15:38	timestamp = 2007ProductionMinBias_RF
'0750'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8159067',	 last => '8159067',	 list => '',  beginTime => '20070608.231538'}, # 	2007-06-08	23:15:38	2007-06-08	23:54:39	timestamp = 2007Production2_RF
'0751'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8159069',	 last => '8159070',	 list => '',  beginTime => '20070608.235439'}, # 	2007-06-08	23:54:39	2007-06-09	00:33:34
'0752'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8159071',	 last => '8159074',	 list => '',  beginTime => '20070609.003334'}, # 	2007-06-09	00:33:34	2007-06-09	02:02:38	timestamp = 2007ProductionMinBias_RF
'0753'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8159078',	 last => '8159081',	 list => '',  beginTime => '20070609.020238'}, # 	2007-06-09	02:02:38	2007-06-09	04:26:58
'0754'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8160006',	 last => '8160011',	 list => '',  beginTime => '20070609.042658'}, # 	2007-06-09	04:26:58	2007-06-09	06:51:01
'0755'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8160013',	 last => '8160013',	 list => '',  beginTime => '20070609.065101'}, # 	2007-06-09	06:51:01	2007-06-09	10:15:48
'0756'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8160024',	 last => '8160027',	 list => '',  beginTime => '20070609.101548'}, # 	2007-06-09	10:15:48	2007-06-09	11:48:17	timestamp = 2007Production2_RF
'0757'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8160029',	 last => '8160029',	 list => '',  beginTime => '20070609.114817'}, # 	2007-06-09	11:48:17	2007-06-09	12:24:54
'0758'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8160030',	 last => '8160031',	 list => '',  beginTime => '20070609.122454'}, # 	2007-06-09	12:24:54	2007-06-10	05:52:08	timestamp = 2007ProductionMinBias_RF
'0759'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8161016',	 last => '8161017',	 list => '',  beginTime => '20070610.055208'}, # 	2007-06-10	05:52:08	2007-06-10	06:58:43	timestamp = 2007Production2_RF
'0760'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8161019',	 last => '8161024',	 list => '',  beginTime => '20070610.065843'}, # 	2007-06-10	06:58:43	2007-06-10	10:26:24	timestamp = 2007ProductionMinBias_RF
'0761'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8161035',	 last => '8161037',	 list => '',  beginTime => '20070610.102624'}, # 	2007-06-10	10:26:24	2007-06-10	11:52:19	timestamp = 2007Production2_RF
'0762'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8161039',	 last => '8161039',	 list => '',  beginTime => '20070610.115219'}, # 	2007-06-10	11:52:19	2007-06-10	12:15:28
'0763'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8161040',	 last => '8161041',	 list => '',  beginTime => '20070610.121528'}, # 	2007-06-10	12:15:28	2007-06-10	13:15:35	timestamp = 2007ProductionMinBias_RF
'0764'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8161045',	 last => '8161049',	 list => '',  beginTime => '20070610.131535'}, # 	2007-06-10	13:15:35	2007-06-10	17:29:46
'0765'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8161062',	 last => '8161063',	 list => '',  beginTime => '20070610.172946'}, # 	2007-06-10	17:29:46	2007-06-10	18:22:17	timestamp = 2007Production2_RF
'0766'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8161065',	 last => '8161066',	 list => '',  beginTime => '20070610.182217'}, # 	2007-06-10	18:22:17	2007-06-10	19:20:56
'0767'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8161067',	 last => '8161068',	 list => '',  beginTime => '20070610.192056'}, # 	2007-06-10	19:20:56	2007-06-10	20:00:30	timestamp = 2007ProductionMinBias_RF
'0768'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8161070',	 last => '8161073',	 list => '',  beginTime => '20070610.200030'}, # 	2007-06-10	20:00:30	2007-06-10	21:40:37
'0769'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8161075',	 last => '8161075',	 list => '',  beginTime => '20070610.214037'}, # 	2007-06-10	21:40:37	2007-06-11	07:35:57
'0770'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8162007',	 last => '8162008',	 list => '',  beginTime => '20070611.073557'}, # 	2007-06-11	07:35:57	2007-06-11	08:31:13	timestamp = 2007Production2_RF
'0771'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8162010',	 last => '8162013',	 list => '',  beginTime => '20070611.083113'}, # 	2007-06-11	08:31:13	2007-06-11	10:26:09
'0772'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8162014',	 last => '8162016',	 list => '',  beginTime => '20070611.102609'}, # 	2007-06-11	10:26:09	2007-06-11	11:51:25	timestamp = 2007ProductionMinBias_RF
'0773'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8162018',	 last => '8162018',	 list => '',  beginTime => '20070611.115125'}, # 	2007-06-11	11:51:25	2007-06-11	14:40:43
'0774'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8162036',	 last => '8162037',	 list => '',  beginTime => '20070611.144043'}, # 	2007-06-11	14:40:43	2007-06-11	15:38:58	timestamp = 2007Production2_RF
'0775'=> {trig=>'2007Production2',       	field => 'ZF',	first=> '8162040',	 last => '8162040',	 list => '',  beginTime => '20070611.153858'}, # 	2007-06-11	15:38:58	2007-06-11	15:38:58	timestamp = 2007Production2_ZF
'0776'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8162040',	 last => '8162040',	 list => '',  beginTime => '20070611.153858'}, # 	2007-06-11	15:38:58	2007-06-11	17:54:14	timestamp = 2007Production2_RF
'0777'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8162047',	 last => '8162048',	 list => '',  beginTime => '20070611.175414'}, # 	2007-06-11	17:54:14	2007-06-11	18:57:50	timestamp = 2007ProductionMinBias_RF
'0778'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8162050',	 last => '8162051',	 list => '',  beginTime => '20070611.185750'}, # 	2007-06-11	18:57:50	2007-06-11	20:56:57
'0779'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8162061',	 last => '8162062',	 list => '',  beginTime => '20070611.205657'}, # 	2007-06-11	20:56:57	2007-06-12	05:02:23	timestamp = 2007Production2_RF
'0780'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8163006',	 last => '8163007',	 list => '',  beginTime => '20070612.050223'}, # 	2007-06-12	05:02:23	2007-06-12	05:57:16
'0781'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8163009',	 last => '8163010',	 list => '',  beginTime => '20070612.055716'}, # 	2007-06-12	05:57:16	2007-06-12	06:42:05
'0782'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8163011',	 last => '8163015',	 list => '',  beginTime => '20070612.064205'}, # 	2007-06-12	06:42:05	2007-06-12	09:09:40	timestamp = 2007ProductionMinBias_RF
'0783'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8163019',	 last => '8163024',	 list => '',  beginTime => '20070612.090940'}, # 	2007-06-12	09:09:40	2007-06-12	12:49:11
'0784'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8163034',	 last => '8163036',	 list => '',  beginTime => '20070612.124911'}, # 	2007-06-12	12:49:11	2007-06-12	13:57:06	timestamp = 2007Production2_RF
'0785'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8163039',	 last => '8163040',	 list => '',  beginTime => '20070612.135706'}, # 	2007-06-12	13:57:06	2007-06-13	02:55:48
'0786'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8163073',	 last => '8163073',	 list => '',  beginTime => '20070613.025548'}, # 	2007-06-13	02:55:48	2007-06-13	03:39:25
'0787'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8163075',	 last => '8163075',	 list => '',  beginTime => '20070613.033925'}, # 	2007-06-13	03:39:25	2007-06-13	04:15:10
'0788'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8164001',	 last => '8164001',	 list => '',  beginTime => '20070613.041510'}, # 	2007-06-13	04:15:10	2007-06-13	23:56:48	timestamp = 2007ProductionMinBias_RF
'0789'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8164032',	 last => '8164034',	 list => '',  beginTime => '20070613.235648'}, # 	2007-06-13	23:56:48	2007-06-14	01:14:16	timestamp = 2007Production2_RF
'0790'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8164038',	 last => '8164038',	 list => '',  beginTime => '20070614.011416'}, # 	2007-06-14	01:14:16	2007-06-14	01:42:11
'0791'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8164039',	 last => '8164045',	 list => '',  beginTime => '20070614.014211'}, # 	2007-06-14	01:42:11	2007-06-14	03:57:02	timestamp = 2007ProductionMinBias_RF
'0792'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8164047',	 last => '8164047',	 list => '',  beginTime => '20070614.035702'}, # 	2007-06-14	03:57:02	2007-06-14	04:04:34
'0793'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8165001',	 last => '8165001',	 list => '',  beginTime => '20070614.040434'}, # 	2007-06-14	04:04:34	2007-06-14	15:28:28
'0794'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8165026',	 last => '8165026',	 list => '',  beginTime => '20070614.152828'}, # 	2007-06-14	15:28:28	2007-06-14	22:32:18	timestamp = 2007Production2_RF
'0795'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8165041',	 last => '8165043',	 list => '',  beginTime => '20070614.223218'}, # 	2007-06-14	22:32:18	2007-06-15	00:35:59
'0796'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8165047',	 last => '8165049',	 list => '',  beginTime => '20070615.003559'}, # 	2007-06-15	00:35:59	2007-06-15	02:16:17	timestamp = 2007ProductionMinBias_RF
'0797'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8165051',	 last => '8165051',	 list => '',  beginTime => '20070615.021617'}, # 	2007-06-15	02:16:17	2007-06-15	07:04:28
'0798'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8166014',	 last => '8166014',	 list => '',  beginTime => '20070615.070428'}, # 	2007-06-15	07:04:28	2007-06-15	07:24:08
'0799'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8166016',	 last => '8166017',	 list => '',  beginTime => '20070615.072408'}, # 	2007-06-15	07:24:08	2007-06-15	07:52:19
'0800'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8166018',	 last => '8166018',	 list => '',  beginTime => '20070615.075219'}, # 	2007-06-15	07:52:19	2007-06-15	08:14:42	timestamp = 2007Production2_RF
'0801'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8166020',	 last => '8166020',	 list => '',  beginTime => '20070615.081442'}, # 	2007-06-15	08:14:42	2007-06-15	08:53:42	timestamp = 2007ProductionMinBias_RF
'0802'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8166023',	 last => '8166023',	 list => '',  beginTime => '20070615.085342'}, # 	2007-06-15	08:53:42	2007-06-15	10:04:48
'0803'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8166031',	 last => '8166031',	 list => '',  beginTime => '20070615.100448'}, # 	2007-06-15	10:04:48	2007-06-15	11:10:19
'0804'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8166035',	 last => '8166035',	 list => '',  beginTime => '20070615.111019'}, # 	2007-06-15	11:10:19	2007-06-15	11:17:53
'0805'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8166038',	 last => '8166044',	 list => '',  beginTime => '20070615.111753'}, # 	2007-06-15	11:17:53	2007-06-15	14:06:13
'0806'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8166047',	 last => '8166049',	 list => '',  beginTime => '20070615.140613'}, # 	2007-06-15	14:06:13	2007-06-16	19:43:36
'0807'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8167036',	 last => '8167036',	 list => '',  beginTime => '20070616.194336'}, # 	2007-06-16	19:43:36	2007-06-16	20:04:33
'0808'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8167039',	 last => '8167039',	 list => '',  beginTime => '20070616.200433'}, # 	2007-06-16	20:04:33	2007-06-16	20:32:40
'0809'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8167042',	 last => '8167042',	 list => '',  beginTime => '20070616.203240'}, # 	2007-06-16	20:32:40	2007-06-16	20:58:56
'0810'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8167045',	 last => '8167047',	 list => '',  beginTime => '20070616.205856'}, # 	2007-06-16	20:58:56	2007-06-16	22:07:46
'0811'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8167050',	 last => '8167052',	 list => '',  beginTime => '20070616.220746'}, # 	2007-06-16	22:07:46	2007-06-16	23:22:29
'0812'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8167055',	 last => '8167056',	 list => '',  beginTime => '20070616.232229'}, # 	2007-06-16	23:22:29	2007-06-17	01:19:11
'0813'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8167060',	 last => '8167060',	 list => '',  beginTime => '20070617.011911'}, # 	2007-06-17	01:19:11	2007-06-17	01:53:02
'0814'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8167063',	 last => '8167064',	 list => '',  beginTime => '20070617.015302'}, # 	2007-06-17	01:53:02	2007-06-17	02:48:39
'0815'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8167066',	 last => '8167069',	 list => '',  beginTime => '20070617.024839'}, # 	2007-06-17	02:48:39	2007-06-17	04:20:54
'0816'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8168001',	 last => '8168001',	 list => '',  beginTime => '20070617.042054'}, # 	2007-06-17	04:20:54	2007-06-17	04:54:43
'0817'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8168003',	 last => '8168004',	 list => '',  beginTime => '20070617.045443'}, # 	2007-06-17	04:54:43	2007-06-17	05:34:26
'0818'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8168006',	 last => '8168006',	 list => '',  beginTime => '20070617.053426'}, # 	2007-06-17	05:34:26	2007-06-17	06:46:58
'0819'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8168013',	 last => '8168013',	 list => '',  beginTime => '20070617.064658'}, # 	2007-06-17	06:46:58	2007-06-17	06:54:02
'0820'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8168015',	 last => '8168017',	 list => '',  beginTime => '20070617.065402'}, # 	2007-06-17	06:54:02	2007-06-17	12:50:49
'0821'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8168039',	 last => '8168040',	 list => '',  beginTime => '20070617.125049'}, # 	2007-06-17	12:50:49	2007-06-17	13:21:23
'0822'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8168043',	 last => '8168044',	 list => '',  beginTime => '20070617.132123'}, # 	2007-06-17	13:21:23	2007-06-17	13:52:21
'0823'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8168048',	 last => '8168048',	 list => '',  beginTime => '20070617.135221'}, # 	2007-06-17	13:52:21	2007-06-17	14:17:23
'0824'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8168049',	 last => '8168051',	 list => '',  beginTime => '20070617.141723'}, # 	2007-06-17	14:17:23	2007-06-17	15:48:35	timestamp = 2007Production2_RF
'0825'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8168052',	 last => '8168053',	 list => '',  beginTime => '20070617.154835'}, # 	2007-06-17	15:48:35	2007-06-17	18:59:00	timestamp = 2007ProductionMinBias_RF
'0826'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8168071',	 last => '8168072',	 list => '',  beginTime => '20070617.185900'}, # 	2007-06-17	18:59:00	2007-06-17	19:15:05
'0827'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8168075',	 last => '8168076',	 list => '',  beginTime => '20070617.191505'}, # 	2007-06-17	19:15:05	2007-06-17	19:42:40
'0828'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8168077',	 last => '8168078',	 list => '',  beginTime => '20070617.194240'}, # 	2007-06-17	19:42:40	2007-06-17	19:52:33	timestamp = 2007Production2_RF
'0829'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8168079',	 last => '8168079',	 list => '',  beginTime => '20070617.195233'}, # 	2007-06-17	19:52:33	2007-06-17	20:20:32	timestamp = 2007ProductionMinBias_RF
'0830'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8168084',	 last => '8168084',	 list => '',  beginTime => '20070617.202032'}, # 	2007-06-17	20:20:32	2007-06-17	20:54:51
'0831'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8168095',	 last => '8168096',	 list => '',  beginTime => '20070617.205451'}, # 	2007-06-17	20:54:51	2007-06-17	21:43:14
'0832'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8168097',	 last => '8168097',	 list => '',  beginTime => '20070617.214314'}, # 	2007-06-17	21:43:14	2007-06-17	21:58:06	timestamp = 2007Production2_RF
'0833'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8168099',	 last => '8168099',	 list => '',  beginTime => '20070617.215806'}, # 	2007-06-17	21:58:06	2007-06-17	22:23:45	timestamp = 2007ProductionMinBias_RF
'0834'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8168100',	 last => '8168100',	 list => '',  beginTime => '20070617.222345'}, # 	2007-06-17	22:23:45	2007-06-17	22:59:17	timestamp = 2007Production2_RF
'0835'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8168102',	 last => '8168102',	 list => '',  beginTime => '20070617.225917'}, # 	2007-06-17	22:59:17	2007-06-18	00:54:00	timestamp = 2007ProductionMinBias_RF
'0836'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8168106',	 last => '8168106',	 list => '',  beginTime => '20070618.005400'}, # 	2007-06-18	00:54:00	2007-06-18	01:31:16
'0837'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8168108',	 last => '8168109',	 list => '',  beginTime => '20070618.013116'}, # 	2007-06-18	01:31:16	2007-06-18	03:00:17	timestamp = 2007Production2_RF
'0838'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8168110',	 last => '8168111',	 list => '',  beginTime => '20070618.030017'}, # 	2007-06-18	03:00:17	2007-06-18	03:46:57	timestamp = 2007ProductionMinBias_RF
'0839'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8168113',	 last => '8168113',	 list => '',  beginTime => '20070618.034657'}, # 	2007-06-18	03:46:57	2007-06-18	04:11:49
'0840'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8169001',	 last => '8169002',	 list => '',  beginTime => '20070618.041149'}, # 	2007-06-18	04:11:49	2007-06-18	06:26:49
'0841'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8169013',	 last => '8169013',	 list => '',  beginTime => '20070618.062649'}, # 	2007-06-18	06:26:49	2007-06-18	06:33:58	timestamp = 2007Production2_RF
'0842'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8169015',	 last => '8169016',	 list => '',  beginTime => '20070618.063358'}, # 	2007-06-18	06:33:58	2007-06-18	07:27:21
'0843'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8169019',	 last => '8169020',	 list => '',  beginTime => '20070618.072721'}, # 	2007-06-18	07:27:21	2007-06-18	08:15:47
'0844'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8169021',	 last => '8169027',	 list => '',  beginTime => '20070618.081547'}, # 	2007-06-18	08:15:47	2007-06-18	10:24:44	timestamp = 2007ProductionMinBias_RF
'0845'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8169029',	 last => '8169031',	 list => '',  beginTime => '20070618.102444'}, # 	2007-06-18	10:24:44	2007-06-18	12:03:05
'0846'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8169042',	 last => '8169043',	 list => '',  beginTime => '20070618.120305'}, # 	2007-06-18	12:03:05	2007-06-18	13:06:08	timestamp = 2007Production2_RF
'0847'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8169046',	 last => '8169048',	 list => '',  beginTime => '20070618.130608'}, # 	2007-06-18	13:06:08	2007-06-18	14:41:47
'0848'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8169049',	 last => '8169050',	 list => '',  beginTime => '20070618.144147'}, # 	2007-06-18	14:41:47	2007-06-18	15:40:07	timestamp = 2007ProductionMinBias_RF
'0849'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8169053',	 last => '8169054',	 list => '',  beginTime => '20070618.154007'}, # 	2007-06-18	15:40:07	2007-06-18	18:34:44
'0850'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8169089',	 last => '8169090',	 list => '',  beginTime => '20070618.183444'}, # 	2007-06-18	18:34:44	2007-06-18	19:26:36	timestamp = 2007Production2_RF
'0851'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8169094',	 last => '8169099',	 list => '',  beginTime => '20070618.192636'}, # 	2007-06-18	19:26:36	2007-06-18	23:53:36
'0852'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8169120',	 last => '8169122',	 list => '',  beginTime => '20070618.235336'}, # 	2007-06-18	23:53:36	2007-06-19	00:55:08
'0853'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8169124',	 last => '8169124',	 list => '',  beginTime => '20070619.005508'}, # 	2007-06-19	00:55:08	2007-06-19	01:29:28
'0854'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8169125',	 last => '8169128',	 list => '',  beginTime => '20070619.012928'}, # 	2007-06-19	01:29:28	2007-06-19	02:51:36	timestamp = 2007ProductionMinBias_RF
'0855'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8169130',	 last => '8169131',	 list => '',  beginTime => '20070619.025136'}, # 	2007-06-19	02:51:36	2007-06-19	03:31:05
'0856'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8169133',	 last => '8169136',	 list => '',  beginTime => '20070619.033105'}, # 	2007-06-19	03:31:05	2007-06-19	04:38:09
'0857'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8170003',	 last => '8170003',	 list => '',  beginTime => '20070619.043809'}, # 	2007-06-19	04:38:09	2007-06-19	06:26:53	timestamp = 2007Production2_RF
'0858'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8170009',	 last => '8170009',	 list => '',  beginTime => '20070619.062653'}, # 	2007-06-19	06:26:53	2007-06-19	08:22:54	timestamp = 2007ProductionMinBias_RF
'0859'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8170019',	 last => '8170020',	 list => '',  beginTime => '20070619.082254'}, # 	2007-06-19	08:22:54	2007-06-19	09:21:41	timestamp = 2007Production2_RF
'0860'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8170022',	 last => '8170024',	 list => '',  beginTime => '20070619.092141'}, # 	2007-06-19	09:21:41	2007-06-19	10:28:20
'0861'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8170025',	 last => '8170026',	 list => '',  beginTime => '20070619.102820'}, # 	2007-06-19	10:28:20	2007-06-19	11:35:04	timestamp = 2007ProductionMinBias_RF
'0862'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8170028',	 last => '8170029',	 list => '',  beginTime => '20070619.113504'}, # 	2007-06-19	11:35:04	2007-06-19	14:38:26
'0863'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8170043',	 last => '8170044',	 list => '',  beginTime => '20070619.143826'}, # 	2007-06-19	14:38:26	2007-06-19	15:09:28
'0864'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8170045',	 last => '8170046',	 list => '',  beginTime => '20070619.150928'}, # 	2007-06-19	15:09:28	2007-06-19	16:14:59	timestamp = 2007Production2_RF
'0865'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8170048',	 last => '8170049',	 list => '',  beginTime => '20070619.161459'}, # 	2007-06-19	16:14:59	2007-06-19	17:05:48
'0866'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8170050',	 last => '8170051',	 list => '',  beginTime => '20070619.170548'}, # 	2007-06-19	17:05:48	2007-06-19	18:04:30	timestamp = 2007ProductionMinBias_RF
'0867'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8170053',	 last => '8170054',	 list => '',  beginTime => '20070619.180430'}, # 	2007-06-19	18:04:30	2007-06-19	20:36:10
'0868'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8170071',	 last => '8170073',	 list => '',  beginTime => '20070619.203610'}, # 	2007-06-19	20:36:10	2007-06-19	21:28:21	timestamp = 2007Production2_RF
'0869'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8170075',	 last => '8170075',	 list => '',  beginTime => '20070619.212821'}, # 	2007-06-19	21:28:21	2007-06-19	21:41:59
'0870'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8170077',	 last => '8170077',	 list => '',  beginTime => '20070619.214159'}, # 	2007-06-19	21:41:59	2007-06-19	22:39:43
'0871'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8170079',	 last => '8170079',	 list => '',  beginTime => '20070619.223943'}, # 	2007-06-19	22:39:43	2007-06-19	22:50:41	timestamp = 2007ProductionMinBias_RF
'0872'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8170080',	 last => '8170080',	 list => '',  beginTime => '20070619.225041'}, # 	2007-06-19	22:50:41	2007-06-19	23:17:53	timestamp = 2007Production2_RF
'0873'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8170082',	 last => '8170082',	 list => '',  beginTime => '20070619.231753'}, # 	2007-06-19	23:17:53	2007-06-19	23:40:33
'0874'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8170084',	 last => '8170086',	 list => '',  beginTime => '20070619.234033'}, # 	2007-06-19	23:40:33	2007-06-20	08:22:36	timestamp = 2007ProductionMinBias_RF
'0875'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8171007',	 last => '8171009',	 list => '',  beginTime => '20070620.082236'}, # 	2007-06-20	08:22:36	2007-06-20	09:28:45	timestamp = 2007Production2_RF
'0876'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8171011',	 last => '8171011',	 list => '',  beginTime => '20070620.092845'}, # 	2007-06-20	09:28:45	2007-06-20	09:56:12	timestamp = 2007ProductionMinBias_RF
'0877'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8171013',	 last => '8171013',	 list => '',  beginTime => '20070620.095612'}, # 	2007-06-20	09:56:12	2007-06-20	10:10:48	timestamp = 2007Production2_RF
'0878'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8171014',	 last => '8171015',	 list => '',  beginTime => '20070620.101048'}, # 	2007-06-20	10:10:48	2007-06-20	23:42:11	timestamp = 2007ProductionMinBias_RF
'0879'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8171034',	 last => '8171035',	 list => '',  beginTime => '20070620.234211'}, # 	2007-06-20	23:42:11	2007-06-21	00:37:45
'0880'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8171037',	 last => '8171038',	 list => '',  beginTime => '20070621.003745'}, # 	2007-06-21	00:37:45	2007-06-21	01:11:34
'0881'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8171040',	 last => '8171040',	 list => '',  beginTime => '20070621.011134'}, # 	2007-06-21	01:11:34	2007-06-21	01:27:42
'0882'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8171042',	 last => '8171042',	 list => '',  beginTime => '20070621.012742'}, # 	2007-06-21	01:27:42	2007-06-21	01:53:19
'0883'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8171044',	 last => '8171045',	 list => '',  beginTime => '20070621.015319'}, # 	2007-06-21	01:53:19	2007-06-21	02:07:14
'0884'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8171049',	 last => '8171052',	 list => '',  beginTime => '20070621.020714'}, # 	2007-06-21	02:07:14	2007-06-21	06:26:01
'0885'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8172033',	 last => '8172033',	 list => '',  beginTime => '20070621.062601'}, # 	2007-06-21	06:26:01	2007-06-21	06:53:24
'0886'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8172035',	 last => '8172036',	 list => '',  beginTime => '20070621.065324'}, # 	2007-06-21	06:53:24	2007-06-21	09:38:25
'0887'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8172048',	 last => '8172050',	 list => '',  beginTime => '20070621.093825'}, # 	2007-06-21	09:38:25	2007-06-21	10:57:17
'0888'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8172056',	 last => '8172061',	 list => '',  beginTime => '20070621.105717'}, # 	2007-06-21	10:57:17	2007-06-21	13:33:24
'0889'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8172065',	 last => '8172067',	 list => '',  beginTime => '20070621.133324'}, # 	2007-06-21	13:33:24	2007-06-21	15:50:10
'0890'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8172082',	 last => '8172084',	 list => '',  beginTime => '20070621.155010'}, # 	2007-06-21	15:50:10	2007-06-21	16:51:47	timestamp = 2007Production2_RF
'0891'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8172086',	 last => '8172088',	 list => '',  beginTime => '20070621.165147'}, # 	2007-06-21	16:51:47	2007-06-21	18:35:41
'0892'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8172090',	 last => '8172091',	 list => '',  beginTime => '20070621.183541'}, # 	2007-06-21	18:35:41	2007-06-21	19:10:47	timestamp = 2007ProductionMinBias_RF
'0893'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8172094',	 last => '8172094',	 list => '',  beginTime => '20070621.191047'}, # 	2007-06-21	19:10:47	2007-06-21	19:47:07
'0894'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8172097',	 last => '8172100',	 list => '',  beginTime => '20070621.194707'}, # 	2007-06-21	19:47:07	2007-06-21	22:46:52
'0895'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8172111',	 last => '8172111',	 list => '',  beginTime => '20070621.224652'}, # 	2007-06-21	22:46:52	2007-06-22	01:55:21
'0896'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8172131',	 last => '8172131',	 list => '',  beginTime => '20070622.015521'}, # 	2007-06-22	01:55:21	2007-06-22	02:21:47
'0897'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8172135',	 last => '8172135',	 list => '',  beginTime => '20070622.022147'}, # 	2007-06-22	02:21:47	2007-06-22	02:34:16
'0898'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8172136',	 last => '8172137',	 list => '',  beginTime => '20070622.023416'}, # 	2007-06-22	02:34:16	2007-06-22	03:46:31	timestamp = 2007Production2_RF
'0899'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8172139',	 last => '8172139',	 list => '',  beginTime => '20070622.034631'}, # 	2007-06-22	03:46:31	2007-06-22	04:02:17
'0900'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8173001',	 last => '8173002',	 list => '',  beginTime => '20070622.040217'}, # 	2007-06-22	04:02:17	2007-06-22	05:11:01
'0901'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8173003',	 last => '8173006',	 list => '',  beginTime => '20070622.051101'}, # 	2007-06-22	05:11:01	2007-06-22	08:31:29	timestamp = 2007ProductionMinBias_RF
'0902'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8173016',	 last => '8173018',	 list => '',  beginTime => '20070622.083129'}, # 	2007-06-22	08:31:29	2007-06-22	09:17:24	timestamp = 2007Production2_RF
'0903'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8173020',	 last => '8173022',	 list => '',  beginTime => '20070622.091724'}, # 	2007-06-22	09:17:24	2007-06-22	10:31:52
'0904'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8173023',	 last => '8173027',	 list => '',  beginTime => '20070622.103152'}, # 	2007-06-22	10:31:52	2007-06-22	12:42:13	timestamp = 2007ProductionMinBias_RF
'0905'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8173029',	 last => '8173029',	 list => '',  beginTime => '20070622.124213'}, # 	2007-06-22	12:42:13	2007-06-22	18:19:34
'0906'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8173061',	 last => '8173062',	 list => '',  beginTime => '20070622.181934'}, # 	2007-06-22	18:19:34	2007-06-22	22:24:58	timestamp = 2007Production2_RF
'0907'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8173077',	 last => '8173077',	 list => '',  beginTime => '20070622.222458'}, # 	2007-06-22	22:24:58	2007-06-22	23:54:16
'0908'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8173088',	 last => '8173090',	 list => '',  beginTime => '20070622.235416'}, # 	2007-06-22	23:54:16	2007-06-23	02:03:01
'0909'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8173091',	 last => '8173091',	 list => '',  beginTime => '20070623.020301'}, # 	2007-06-23	02:03:01	2007-06-23	02:34:40	timestamp = 2007ProductionMinBias_RF
'0910'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8173094',	 last => '8173094',	 list => '',  beginTime => '20070623.023440'}, # 	2007-06-23	02:34:40	2007-06-23	04:42:31
'0911'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8174008',	 last => '8174009',	 list => '',  beginTime => '20070623.044231'}, # 	2007-06-23	04:42:31	2007-06-23	05:44:30	timestamp = 2007Production2_RF
'0912'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8174011',	 last => '8174011',	 list => '',  beginTime => '20070623.054430'}, # 	2007-06-23	05:44:30	2007-06-23	06:25:20
'0913'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8174013',	 last => '8174013',	 list => '',  beginTime => '20070623.062520'}, # 	2007-06-23	06:25:20	2007-06-23	06:35:56	timestamp = 2007ProductionMinBias_RF
'0914'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8174015',	 last => '8174017',	 list => '',  beginTime => '20070623.063556'}, # 	2007-06-23	06:35:56	2007-06-23	10:33:53
'0915'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8174026',	 last => '8174027',	 list => '',  beginTime => '20070623.103353'}, # 	2007-06-23	10:33:53	2007-06-23	11:34:07	timestamp = 2007Production2_RF
'0916'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8174029',	 last => '8174031',	 list => '',  beginTime => '20070623.113407'}, # 	2007-06-23	11:34:07	2007-06-23	12:44:21	timestamp = 2007ProductionMinBias_RF
'0917'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8174032',	 last => '8174032',	 list => '',  beginTime => '20070623.124421'}, # 	2007-06-23	12:44:21	2007-06-23	13:06:04	timestamp = 2007Production2_RF
'0918'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8174033',	 last => '8174037',	 list => '',  beginTime => '20070623.130604'}, # 	2007-06-23	13:06:04	2007-06-23	14:30:24	timestamp = 2007ProductionMinBias_RF
'0919'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8174039',	 last => '8174039',	 list => '',  beginTime => '20070623.143024'}, # 	2007-06-23	14:30:24	2007-06-23	15:54:39
'0920'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8174052',	 last => '8174056',	 list => '',  beginTime => '20070623.155439'}, # 	2007-06-23	15:54:39	2007-06-23	17:52:09	timestamp = 2007Production2_RF
'0921'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8174058',	 last => '8174060',	 list => '',  beginTime => '20070623.175209'}, # 	2007-06-23	17:52:09	2007-06-23	19:20:54
'0922'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8174061',	 last => '8174062',	 list => '',  beginTime => '20070623.192054'}, # 	2007-06-23	19:20:54	2007-06-23	22:08:11	timestamp = 2007ProductionMinBias_RF
'0923'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8174084',	 last => '8174084',	 list => '',  beginTime => '20070623.220811'}, # 	2007-06-23	22:08:11	2007-06-23	22:17:51
'0924'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8174085',	 last => '8174085',	 list => '',  beginTime => '20070623.221751'}, # 	2007-06-23	22:17:51	2007-06-23	22:40:56	timestamp = 2007Production2_RF
'0925'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8174087',	 last => '8174088',	 list => '',  beginTime => '20070623.224056'}, # 	2007-06-23	22:40:56	2007-06-23	23:36:00
'0926'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8174091',	 last => '8174091',	 list => '',  beginTime => '20070623.233600'}, # 	2007-06-23	23:36:00	2007-06-23	23:58:51
'0927'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8174094',	 last => '8174096',	 list => '',  beginTime => '20070623.235851'}, # 	2007-06-23	23:58:51	2007-06-24	03:09:57
'0928'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8174103',	 last => '8174103',	 list => '',  beginTime => '20070624.030957'}, # 	2007-06-24	03:09:57	2007-06-24	03:37:30
'0929'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8174105',	 last => '8174105',	 list => '',  beginTime => '20070624.033730'}, # 	2007-06-24	03:37:30	2007-06-24	04:05:38
'0930'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8175001',	 last => '8175003',	 list => '',  beginTime => '20070624.040538'}, # 	2007-06-24	04:05:38	2007-06-24	05:34:44
'0931'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8175004',	 last => '8175005',	 list => '',  beginTime => '20070624.053444'}, # 	2007-06-24	05:34:44	2007-06-24	06:35:19	timestamp = 2007ProductionMinBias_RF
'0932'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8175007',	 last => '8175008',	 list => '',  beginTime => '20070624.063519'}, # 	2007-06-24	06:35:19	2007-06-24	07:33:06
'0933'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8175010',	 last => '8175010',	 list => '',  beginTime => '20070624.073306'}, # 	2007-06-24	07:33:06	2007-06-24	11:40:17
'0934'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8175020',	 last => '8175022',	 list => '',  beginTime => '20070624.114017'}, # 	2007-06-24	11:40:17	2007-06-24	13:06:30	timestamp = 2007Production2_RF
'0935'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8175024',	 last => '8175026',	 list => '',  beginTime => '20070624.130630'}, # 	2007-06-24	13:06:30	2007-06-24	14:19:27
'0936'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8175027',	 last => '8175028',	 list => '',  beginTime => '20070624.141927'}, # 	2007-06-24	14:19:27	2007-06-24	15:19:22	timestamp = 2007ProductionMinBias_RF
'0937'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8175030',	 last => '8175030',	 list => '',  beginTime => '20070624.151922'}, # 	2007-06-24	15:19:22	2007-06-24	16:56:55
'0938'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8175044',	 last => '8175047',	 list => '',  beginTime => '20070624.165655'}, # 	2007-06-24	16:56:55	2007-06-24	18:01:22	timestamp = 2007Production2_RF
'0939'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8175049',	 last => '8175049',	 list => '',  beginTime => '20070624.180122'}, # 	2007-06-24	18:01:22	2007-06-24	18:19:00
'0940'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8175051',	 last => '8175051',	 list => '',  beginTime => '20070624.181900'}, # 	2007-06-24	18:19:00	2007-06-24	18:54:09
'0941'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8175053',	 last => '8175055',	 list => '',  beginTime => '20070624.185409'}, # 	2007-06-24	18:54:09	2007-06-24	20:15:33	timestamp = 2007ProductionMinBias_RF
'0942'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8175057',	 last => '8175060',	 list => '',  beginTime => '20070624.201533'}, # 	2007-06-24	20:15:33	2007-06-24	22:51:10
'0943'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8175067',	 last => '8175067',	 list => '',  beginTime => '20070624.225110'}, # 	2007-06-24	22:51:10	2007-06-24	23:13:31
'0944'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8175070',	 last => '8175071',	 list => '',  beginTime => '20070624.231331'}, # 	2007-06-24	23:13:31	2007-06-25	00:11:26	timestamp = 2007Production2_RF
'0945'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8175074',	 last => '8175075',	 list => '',  beginTime => '20070625.001126'}, # 	2007-06-25	00:11:26	2007-06-25	05:12:02
'0946'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8176005',	 last => '8176007',	 list => '',  beginTime => '20070625.051202'}, # 	2007-06-25	05:12:02	2007-06-25	06:17:26	timestamp = 2007ProductionMinBias_RF
'0947'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8176013',	 last => '8176013',	 list => '',  beginTime => '20070625.061726'}, # 	2007-06-25	06:17:26	2007-06-25	06:57:33	timestamp = 2007Production2_RF
'0948'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8176015',	 last => '8176018',	 list => '',  beginTime => '20070625.065733'}, # 	2007-06-25	06:57:33	2007-06-25	08:00:09	timestamp = 2007ProductionMinBias_RF
'0949'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8176019',	 last => '8176019',	 list => '',  beginTime => '20070625.080009'}, # 	2007-06-25	08:00:09	2007-06-25	08:21:22	timestamp = 2007Production2_RF
'0950'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8176020',	 last => '8176021',	 list => '',  beginTime => '20070625.082122'}, # 	2007-06-25	08:21:22	2007-06-25	09:25:42	timestamp = 2007ProductionMinBias_RF
'0951'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8176024',	 last => '8176025',	 list => '',  beginTime => '20070625.092542'}, # 	2007-06-25	09:25:42	2007-06-25	11:05:06
'0952'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8176035',	 last => '8176037',	 list => '',  beginTime => '20070625.110506'}, # 	2007-06-25	11:05:06	2007-06-25	12:21:17	timestamp = 2007Production2_RF
'0953'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8176040',	 last => '8176041',	 list => '',  beginTime => '20070625.122117'}, # 	2007-06-25	12:21:17	2007-06-25	13:34:36
'0954'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8176043',	 last => '8176046',	 list => '',  beginTime => '20070625.133436'}, # 	2007-06-25	13:34:36	2007-06-25	15:24:22	timestamp = 2007ProductionMinBias_RF
'0955'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8176048',	 last => '8176048',	 list => '',  beginTime => '20070625.152422'}, # 	2007-06-25	15:24:22	2007-06-25	19:40:06
'0956'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8176062',	 last => '8176064',	 list => '',  beginTime => '20070625.194006'}, # 	2007-06-25	19:40:06	2007-06-25	21:21:03	timestamp = 2007Production2_RF
'0957'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8176077',	 last => '8176081',	 list => '',  beginTime => '20070625.212103'}, # 	2007-06-25	21:21:03	2007-06-25	23:13:39	timestamp = 2007ProductionMinBias_RF
'0958'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8176083',	 last => '8176083',	 list => '',  beginTime => '20070625.231339'}, # 	2007-06-25	23:13:39	2007-06-25	23:57:18
'0959'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8176090',	 last => '8176090',	 list => '',  beginTime => '20070625.235718'}, # 	2007-06-25	23:57:18	2007-06-26	01:35:17
'0960'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8176103',	 last => '8176104',	 list => '',  beginTime => '20070626.013517'}, # 	2007-06-26	01:35:17	2007-06-26	02:29:26
'0961'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8176107',	 last => '8176110',	 list => '',  beginTime => '20070626.022926'}, # 	2007-06-26	02:29:26	2007-06-26	04:03:30
'0962'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8177001',	 last => '8177001',	 list => '',  beginTime => '20070626.040330'}, # 	2007-06-26	04:03:30	2007-06-26	04:38:44
'0963'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8177003',	 last => '8177003',	 list => '',  beginTime => '20070626.043844'}, # 	2007-06-26	04:38:44	2007-06-26	06:13:06
'0964'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8177014',	 last => '8177015',	 list => '',  beginTime => '20070626.061306'}, # 	2007-06-26	06:13:06	2007-06-26	07:14:57	timestamp = 2007Production2_RF
'0965'=> {trig=>'2007Production2',       	field => 'RF',	first=> '8177017',	 last => '8177017',	 list => '',  beginTime => '20070626.071457'}, # 	2007-06-26	07:14:57	2007-06-26	08:49:30
'0966'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8177020',	 last => '8177023',	 list => '',  beginTime => '20070626.084930'}, # 	2007-06-26	08:49:30	2007-06-26	13:26:47	timestamp = 2007ProductionMinBias_RF
'0967'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8177055',	 last => '8177056',	 list => '',  beginTime => '20070626.132647'}, # 	2007-06-26	13:26:47	2007-06-26	14:20:43
'0968'=> {trig=>'2007ProductionMinBias', 	field => 'RF',	first=> '8177058',	 last => '8177059',	 list => '',  beginTime => '20070626.142043'}, # 	2007-06-26	14:20:43	2007-06-26	14:43:55
);
1;
