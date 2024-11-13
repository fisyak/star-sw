#!/usr/bin/perl
use strict;
use warnings;
our @Runs = ( # onl CURRENT | SortRun.pl 
'0000'=> {trig=>'production2009_test-zdc',	field => 'RF',	first=> '10066129',	 last => '10066129',	 list => '',  beginTime => '20090307.213507'}, # 	2009-03-07	21:35:07	2009-03-08	05:28:43	timestamp = production2009_test-zdc_RF
'0001'=> {trig=>'production2009_test-zdc',	field => 'RF',	first=> '10067003',	 last => '10067008',	 list => '',  beginTime => '20090308.052843'}, # 	2009-03-08	05:28:43	2009-03-10	08:22:51
'0002'=> {trig=>'production2009_test-zdc',	field => 'RF',	first=> '10069030',	 last => '10069035',	 list => '',  beginTime => '20090310.082251'}, # 	2009-03-10	08:22:51	2009-03-10	09:16:34
'0003'=> {trig=>'production2009_test-zdc',	field => 'RF',	first=> '10069038',	 last => '10069043',	 list => '',  beginTime => '20090310.091634'}, # 	2009-03-10	09:16:34	2009-03-11	09:44:38
'0004'=> {trig=>'production2009_jeff',   	field => 'RF',	first=> '10070034',	 last => '10070034',	 list => '',  beginTime => '20090311.094438'}, # 	2009-03-11	09:44:38	2009-03-11	10:17:07	timestamp = production2009_jeff_RF
'0005'=> {trig=>'production2009_jeff',   	field => 'RF',	first=> '10070036',	 last => '10070036',	 list => '',  beginTime => '20090311.101707'}, # 	2009-03-11	10:17:07	2009-03-12	06:17:08
'0006'=> {trig=>'production2009_jeff',   	field => 'RF',	first=> '10071009',	 last => '10071016',	 list => '',  beginTime => '20090312.061708'}, # 	2009-03-12	06:17:08	2009-03-12	06:47:41
'0007'=> {trig=>'production2009_jeff',   	field => 'RF',	first=> '10071021',	 last => '10071030',	 list => '',  beginTime => '20090312.064741'}, # 	2009-03-12	06:47:41	2009-03-12	07:19:36
'0008'=> {trig=>'production2009_jeff',   	field => 'RF',	first=> '10071032',	 last => '10071032',	 list => '',  beginTime => '20090312.071936'}, # 	2009-03-12	07:19:36	2009-03-12	07:28:03
'0009'=> {trig=>'production2009_jeff',   	field => 'RF',	first=> '10071034',	 last => '10071034',	 list => '',  beginTime => '20090312.072803'}, # 	2009-03-12	07:28:03	2009-03-12	10:20:22
'0010'=> {trig=>'production2009_jeff',   	field => 'RF',	first=> '10071051',	 last => '10071052',	 list => '',  beginTime => '20090312.102022'}, # 	2009-03-12	10:20:22	2009-03-12	10:41:12
'0011'=> {trig=>'production2009_jeff',   	field => 'RF',	first=> '10071054',	 last => '10071054',	 list => '',  beginTime => '20090312.104112'}, # 	2009-03-12	10:41:12	2009-03-12	15:53:23
'0012'=> {trig=>'production2009_jeff',   	field => 'RF',	first=> '10071069',	 last => '10071069',	 list => '',  beginTime => '20090312.155323'}, # 	2009-03-12	15:53:23	2009-03-13	13:31:50
'0013'=> {trig=>'production2009_jeff',   	field => 'RF',	first=> '10072003',	 last => '10072003',	 list => '',  beginTime => '20090313.133150'}, # 	2009-03-13	13:31:50	2009-03-13	13:56:12
'0014'=> {trig=>'production2009_jeff',   	field => 'RF',	first=> '10072013',	 last => '10072013',	 list => '',  beginTime => '20090313.135612'}, # 	2009-03-13	13:56:12	2009-03-13	15:46:15
'0015'=> {trig=>'production2009_jeff',   	field => 'RF',	first=> '10072033',	 last => '10072033',	 list => '',  beginTime => '20090313.154615'}, # 	2009-03-13	15:46:15	2009-03-13	16:04:24
'0016'=> {trig=>'production2009_jeff',   	field => 'RF',	first=> '10072037',	 last => '10072040',	 list => '',  beginTime => '20090313.160424'}, # 	2009-03-13	16:04:24	2009-03-20	00:45:56
'0017'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10078069',	 last => '10078069',	 list => '',  beginTime => '20090320.004556'}, # 	2009-03-20	00:45:56	2009-03-20	01:34:43	timestamp = production2009_500GeV_RF
'0018'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10078075',	 last => '10078078',	 list => '',  beginTime => '20090320.013443'}, # 	2009-03-20	01:34:43	2009-03-20	02:27:03
'0019'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10078081',	 last => '10078082',	 list => '',  beginTime => '20090320.022703'}, # 	2009-03-20	02:27:03	2009-03-20	02:46:17
'0020'=> {trig=>'vpdtest',               	field => 'RF',	first=> '10078083',	 last => '10078091',	 list => '',  beginTime => '20090320.024617'}, # 	2009-03-20	02:46:17	2009-03-20	03:23:19	timestamp = vpdtest_RF
'0021'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10078092',	 last => '10078094',	 list => '',  beginTime => '20090320.032319'}, # 	2009-03-20	03:23:19	2009-03-20	04:18:33	timestamp = production2009_500GeV_RF
'0022'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10079002',	 last => '10079005',	 list => '',  beginTime => '20090320.041833'}, # 	2009-03-20	04:18:33	2009-03-20	05:05:39
'0023'=> {trig=>'production2009_500GeV_carl',	field => 'RF',	first=> '10079006',	 last => '10079007',	 list => '',  beginTime => '20090320.050539'}, # 	2009-03-20	05:05:39	2009-03-20	06:06:00	timestamp = production2009_500GeV_carl_RF
'0024'=> {trig=>'production2009_500GeV_carl',	field => 'RF',	first=> '10079015',	 last => '10079017',	 list => '',  beginTime => '20090320.060600'}, # 	2009-03-20	06:06:00	2009-03-20	09:22:04
'0025'=> {trig=>'production2009_500GeV_carl',	field => 'RF',	first=> '10079027',	 last => '10079035',	 list => '',  beginTime => '20090320.092204'}, # 	2009-03-20	09:22:04	2009-03-20	10:38:33
'0026'=> {trig=>'production2009_500GeV_carl',	field => 'RF',	first=> '10079037',	 last => '10079037',	 list => '',  beginTime => '20090320.103833'}, # 	2009-03-20	10:38:33	2009-03-20	11:06:55
'0027'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10079040',	 last => '10079040',	 list => '',  beginTime => '20090320.110655'}, # 	2009-03-20	11:06:55	2009-03-20	11:14:25	timestamp = production2009_500GeV_RF
'0028'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10079042',	 last => '10079042',	 list => '',  beginTime => '20090320.111425'}, # 	2009-03-20	11:14:25	2009-03-20	11:38:52
'0029'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10079045',	 last => '10079047',	 list => '',  beginTime => '20090320.113852'}, # 	2009-03-20	11:38:52	2009-03-20	12:21:21
'0030'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10079049',	 last => '10079049',	 list => '',  beginTime => '20090320.122121'}, # 	2009-03-20	12:21:21	2009-03-20	12:29:49
'0031'=> {trig=>'production2009_500GeV_carl',	field => 'RF',	first=> '10079050',	 last => '10079050',	 list => '',  beginTime => '20090320.122949'}, # 	2009-03-20	12:29:49	2009-03-20	12:35:10	timestamp = production2009_500GeV_carl_RF
'0032'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10079051',	 last => '10079051',	 list => '',  beginTime => '20090320.123510'}, # 	2009-03-20	12:35:10	2009-03-20	13:12:53	timestamp = production2009_500GeV_RF
'0033'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10079057',	 last => '10079063',	 list => '',  beginTime => '20090320.131253'}, # 	2009-03-20	13:12:53	2009-03-20	14:50:04
'0034'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10079069',	 last => '10079071',	 list => '',  beginTime => '20090320.145004'}, # 	2009-03-20	14:50:04	2009-03-20	15:35:56
'0035'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10079074',	 last => '10079075',	 list => '',  beginTime => '20090320.153556'}, # 	2009-03-20	15:35:56	2009-03-20	16:22:09
'0036'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10079078',	 last => '10079081',	 list => '',  beginTime => '20090320.162209'}, # 	2009-03-20	16:22:09	2009-03-20	23:44:04
'0037'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10079128',	 last => '10079131',	 list => '',  beginTime => '20090320.234404'}, # 	2009-03-20	23:44:04	2009-03-21	00:39:12
'0038'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10079135',	 last => '10079135',	 list => '',  beginTime => '20090321.003912'}, # 	2009-03-21	00:39:12	2009-03-21	00:52:32
'0039'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10079137',	 last => '10079139',	 list => '',  beginTime => '20090321.005232'}, # 	2009-03-21	00:52:32	2009-03-21	09:57:22
'0040'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10080019',	 last => '10080019',	 list => '',  beginTime => '20090321.095722'}, # 	2009-03-21	09:57:22	2009-03-21	18:19:14
'0041'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10080033',	 last => '10080033',	 list => '',  beginTime => '20090321.181914'}, # 	2009-03-21	18:19:14	2009-03-21	18:58:20
'0042'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10080039',	 last => '10080040',	 list => '',  beginTime => '20090321.185820'}, # 	2009-03-21	18:58:20	2009-03-21	21:50:30
'0043'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10080061',	 last => '10080062',	 list => '',  beginTime => '20090321.215030'}, # 	2009-03-21	21:50:30	2009-03-21	22:49:36
'0044'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10080074',	 last => '10080082',	 list => '',  beginTime => '20090321.224936'}, # 	2009-03-21	22:49:36	2009-03-22	05:31:30
'0045'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10081007',	 last => '10081007',	 list => '',  beginTime => '20090322.053130'}, # 	2009-03-22	05:31:30	2009-03-22	06:25:59
'0046'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10081013',	 last => '10081013',	 list => '',  beginTime => '20090322.062559'}, # 	2009-03-22	06:25:59	2009-03-22	07:49:23
'0047'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10081024',	 last => '10081024',	 list => '',  beginTime => '20090322.074923'}, # 	2009-03-22	07:49:23	2009-03-22	08:08:00
'0048'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10081026',	 last => '10081027',	 list => '',  beginTime => '20090322.080800'}, # 	2009-03-22	08:08:00	2009-03-22	10:47:47
'0049'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10081046',	 last => '10081047',	 list => '',  beginTime => '20090322.104747'}, # 	2009-03-22	10:47:47	2009-03-23	00:32:45
'0050'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10081095',	 last => '10081096',	 list => '',  beginTime => '20090323.003245'}, # 	2009-03-23	00:32:45	2009-03-23	01:08:15
'0051'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10081102',	 last => '10081104',	 list => '',  beginTime => '20090323.010815'}, # 	2009-03-23	01:08:15	2009-03-23	01:55:22
'0052'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10081107',	 last => '10081108',	 list => '',  beginTime => '20090323.015522'}, # 	2009-03-23	01:55:22	2009-03-23	02:28:47
'0053'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10081110',	 last => '10081112',	 list => '',  beginTime => '20090323.022847'}, # 	2009-03-23	02:28:47	2009-03-23	03:28:42
'0054'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10081115',	 last => '10081115',	 list => '',  beginTime => '20090323.032842'}, # 	2009-03-23	03:28:42	2009-03-23	03:48:33
'0055'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10081117',	 last => '10081117',	 list => '',  beginTime => '20090323.034833'}, # 	2009-03-23	03:48:33	2009-03-23	04:06:05
'0056'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10082002',	 last => '10082003',	 list => '',  beginTime => '20090323.040605'}, # 	2009-03-23	04:06:05	2009-03-23	04:37:38
'0057'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10082005',	 last => '10082005',	 list => '',  beginTime => '20090323.043738'}, # 	2009-03-23	04:37:38	2009-03-23	05:10:23
'0058'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10082008',	 last => '10082008',	 list => '',  beginTime => '20090323.051023'}, # 	2009-03-23	05:10:23	2009-03-23	05:39:28
'0059'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10082011',	 last => '10082011',	 list => '',  beginTime => '20090323.053928'}, # 	2009-03-23	05:39:28	2009-03-23	05:59:50
'0060'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10082014',	 last => '10082014',	 list => '',  beginTime => '20090323.055950'}, # 	2009-03-23	05:59:50	2009-03-23	06:31:18
'0061'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10082018',	 last => '10082018',	 list => '',  beginTime => '20090323.063118'}, # 	2009-03-23	06:31:18	2009-03-23	06:50:41
'0062'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10082021',	 last => '10082022',	 list => '',  beginTime => '20090323.065041'}, # 	2009-03-23	06:50:41	2009-03-23	07:22:32
'0063'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10082027',	 last => '10082027',	 list => '',  beginTime => '20090323.072232'}, # 	2009-03-23	07:22:32	2009-03-23	07:41:12
'0064'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10082029',	 last => '10082029',	 list => '',  beginTime => '20090323.074112'}, # 	2009-03-23	07:41:12	2009-03-23	07:58:36
'0065'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10082031',	 last => '10082032',	 list => '',  beginTime => '20090323.075836'}, # 	2009-03-23	07:58:36	2009-03-23	08:20:11
'0066'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10082034',	 last => '10082035',	 list => '',  beginTime => '20090323.082011'}, # 	2009-03-23	08:20:11	2009-03-23	08:53:29
'0067'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10082043',	 last => '10082043',	 list => '',  beginTime => '20090323.085329'}, # 	2009-03-23	08:53:29	2009-03-23	11:28:49
'0068'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10082071',	 last => '10082071',	 list => '',  beginTime => '20090323.112849'}, # 	2009-03-23	11:28:49	2009-03-23	14:16:52
'0069'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10082091',	 last => '10082091',	 list => '',  beginTime => '20090323.141652'}, # 	2009-03-23	14:16:52	2009-03-24	06:49:33
'0070'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10083013',	 last => '10083013',	 list => '',  beginTime => '20090324.064933'}, # 	2009-03-24	06:49:33	2009-03-24	07:20:06
'0071'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10083018',	 last => '10083019',	 list => '',  beginTime => '20090324.072006'}, # 	2009-03-24	07:20:06	2009-03-24	07:58:33
'0072'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10083023',	 last => '10083023',	 list => '',  beginTime => '20090324.075833'}, # 	2009-03-24	07:58:33	2009-03-24	08:10:56
'0073'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10083026',	 last => '10083026',	 list => '',  beginTime => '20090324.081056'}, # 	2009-03-24	08:10:56	2009-03-24	09:58:19
'0074'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10083037',	 last => '10083038',	 list => '',  beginTime => '20090324.095819'}, # 	2009-03-24	09:58:19	2009-03-24	10:25:54
'0075'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10083040',	 last => '10083041',	 list => '',  beginTime => '20090324.102554'}, # 	2009-03-24	10:25:54	2009-03-24	11:15:57
'0076'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10083045',	 last => '10083045',	 list => '',  beginTime => '20090324.111557'}, # 	2009-03-24	11:15:57	2009-03-24	12:30:37
'0077'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10083052',	 last => '10083056',	 list => '',  beginTime => '20090324.123037'}, # 	2009-03-24	12:30:37	2009-03-24	13:35:11
'0078'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10083058',	 last => '10083058',	 list => '',  beginTime => '20090324.133511'}, # 	2009-03-24	13:35:11	2009-03-25	06:18:07
'0079'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10084010',	 last => '10084010',	 list => '',  beginTime => '20090325.061807'}, # 	2009-03-25	06:18:07	2009-03-26	05:52:38
'0080'=> {trig=>'productionZDCpolarimetry',	field => 'RF',	first=> '10085007',	 last => '10085007',	 list => '',  beginTime => '20090326.055238'}, # 	2009-03-26	05:52:38	2009-03-26	06:36:53	timestamp = productionZDCpolarimetry_RF
'0081'=> {trig=>'productionZDCpolarimetry',	field => 'RF',	first=> '10085012',	 last => '10085012',	 list => '',  beginTime => '20090326.063653'}, # 	2009-03-26	06:36:53	2009-03-26	06:59:52
'0082'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10085016',	 last => '10085019',	 list => '',  beginTime => '20090326.065952'}, # 	2009-03-26	06:59:52	2009-03-26	08:17:28	timestamp = production2009_500GeV_RF
'0083'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10085022',	 last => '10085032',	 list => '',  beginTime => '20090326.081728'}, # 	2009-03-26	08:17:28	2009-03-27	00:39:00
'0084'=> {trig=>'production2009_500Gev_b',	field => 'RF',	first=> '10085111',	 last => '10085115',	 list => '',  beginTime => '20090327.003900'}, # 	2009-03-27	00:39:00	2009-03-27	02:00:15	timestamp = production2009_500Gev_b_RF
'0085'=> {trig=>'production2009_500Gev_b',	field => 'RF',	first=> '10085123',	 last => '10085124',	 list => '',  beginTime => '20090327.020015'}, # 	2009-03-27	02:00:15	2009-03-27	02:15:55
'0086'=> {trig=>'production2009_500Gev_b',	field => 'RF',	first=> '10085126',	 last => '10085127',	 list => '',  beginTime => '20090327.021555'}, # 	2009-03-27	02:15:55	2009-03-27	02:36:04
'0087'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10085131',	 last => '10085140',	 list => '',  beginTime => '20090327.023604'}, # 	2009-03-27	02:36:04	2009-03-27	04:17:51	timestamp = production2009_500Gev_c_RF
'0088'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10086001',	 last => '10086001',	 list => '',  beginTime => '20090327.041751'}, # 	2009-03-27	04:17:51	2009-03-27	04:51:09
'0089'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10086007',	 last => '10086008',	 list => '',  beginTime => '20090327.045109'}, # 	2009-03-27	04:51:09	2009-03-27	05:24:41
'0090'=> {trig=>'productionZDCpolarimetry',	field => 'RF',	first=> '10086010',	 last => '10086010',	 list => '',  beginTime => '20090327.052441'}, # 	2009-03-27	05:24:41	2009-03-27	05:48:24	timestamp = productionZDCpolarimetry_RF
'0091'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10086015',	 last => '10086015',	 list => '',  beginTime => '20090327.054824'}, # 	2009-03-27	05:48:24	2009-03-27	06:07:48	timestamp = production2009_500Gev_c_RF
'0092'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10086018',	 last => '10086019',	 list => '',  beginTime => '20090327.060748'}, # 	2009-03-27	06:07:48	2009-03-27	06:47:38
'0093'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10086022',	 last => '10086024',	 list => '',  beginTime => '20090327.064738'}, # 	2009-03-27	06:47:38	2009-03-27	07:16:00
'0094'=> {trig=>'productionZDCpolarimetry',	field => 'RF',	first=> '10086025',	 last => '10086025',	 list => '',  beginTime => '20090327.071600'}, # 	2009-03-27	07:16:00	2009-03-27	08:04:12	timestamp = productionZDCpolarimetry_RF
'0095'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10086037',	 last => '10086037',	 list => '',  beginTime => '20090327.080412'}, # 	2009-03-27	08:04:12	2009-03-27	08:32:59	timestamp = production2009_500Gev_c_RF
'0096'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10086039',	 last => '10086039',	 list => '',  beginTime => '20090327.083259'}, # 	2009-03-27	08:32:59	2009-03-27	08:59:37
'0097'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10086043',	 last => '10086044',	 list => '',  beginTime => '20090327.085937'}, # 	2009-03-27	08:59:37	2009-03-27	09:21:52
'0098'=> {trig=>'productionZDCpolarimetry',	field => 'RF',	first=> '10086045',	 last => '10086045',	 list => '',  beginTime => '20090327.092152'}, # 	2009-03-27	09:21:52	2009-03-27	09:29:02	timestamp = productionZDCpolarimetry_RF
'0099'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10086046',	 last => '10086046',	 list => '',  beginTime => '20090327.092902'}, # 	2009-03-27	09:29:02	2009-03-27	10:04:36	timestamp = production2009_500Gev_c_RF
'0100'=> {trig=>'productionZDCpolarimetry',	field => 'RF',	first=> '10086050',	 last => '10086050',	 list => '',  beginTime => '20090327.100436'}, # 	2009-03-27	10:04:36	2009-03-28	04:33:39	timestamp = productionZDCpolarimetry_RF
'0101'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10087004',	 last => '10087004',	 list => '',  beginTime => '20090328.043339'}, # 	2009-03-28	04:33:39	2009-03-28	04:56:06	timestamp = production2009_500GeV_RF
'0102'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10087009',	 last => '10087009',	 list => '',  beginTime => '20090328.045606'}, # 	2009-03-28	04:56:06	2009-03-28	05:14:56	timestamp = production2009_500Gev_c_RF
'0103'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10087011',	 last => '10087012',	 list => '',  beginTime => '20090328.051456'}, # 	2009-03-28	05:14:56	2009-03-28	06:26:47
'0104'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10087017',	 last => '10087023',	 list => '',  beginTime => '20090328.062647'}, # 	2009-03-28	06:26:47	2009-03-28	08:18:10
'0105'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10087025',	 last => '10087025',	 list => '',  beginTime => '20090328.081810'}, # 	2009-03-28	08:18:10	2009-03-28	08:47:12
'0106'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10087028',	 last => '10087028',	 list => '',  beginTime => '20090328.084712'}, # 	2009-03-28	08:47:12	2009-03-28	09:18:53
'0107'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10087030',	 last => '10087037',	 list => '',  beginTime => '20090328.091853'}, # 	2009-03-28	09:18:53	2009-03-28	11:10:46
'0108'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10087039',	 last => '10087039',	 list => '',  beginTime => '20090328.111046'}, # 	2009-03-28	11:10:46	2009-03-28	11:24:37
'0109'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10087041',	 last => '10087041',	 list => '',  beginTime => '20090328.112437'}, # 	2009-03-28	11:24:37	2009-03-28	14:31:23
'0110'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10087051',	 last => '10087054',	 list => '',  beginTime => '20090328.143123'}, # 	2009-03-28	14:31:23	2009-03-28	15:51:27
'0111'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10087057',	 last => '10087059',	 list => '',  beginTime => '20090328.155127'}, # 	2009-03-28	15:51:27	2009-03-28	16:49:42
'0112'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10087061',	 last => '10087063',	 list => '',  beginTime => '20090328.164942'}, # 	2009-03-28	16:49:42	2009-03-28	17:38:49
'0113'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10087065',	 last => '10087067',	 list => '',  beginTime => '20090328.173849'}, # 	2009-03-28	17:38:49	2009-03-28	18:14:38
'0114'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10087069',	 last => '10087071',	 list => '',  beginTime => '20090328.181438'}, # 	2009-03-28	18:14:38	2009-03-28	19:37:14
'0115'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10087077',	 last => '10087077',	 list => '',  beginTime => '20090328.193714'}, # 	2009-03-28	19:37:14	2009-03-28	20:30:10
'0116'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10087081',	 last => '10087082',	 list => '',  beginTime => '20090328.203010'}, # 	2009-03-28	20:30:10	2009-03-28	20:53:17
'0117'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10087084',	 last => '10087085',	 list => '',  beginTime => '20090328.205317'}, # 	2009-03-28	20:53:17	2009-03-28	21:33:11
'0118'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10087088',	 last => '10087088',	 list => '',  beginTime => '20090328.213311'}, # 	2009-03-28	21:33:11	2009-03-28	22:21:34
'0119'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10087093',	 last => '10087094',	 list => '',  beginTime => '20090328.222134'}, # 	2009-03-28	22:21:34	2009-03-28	22:41:59
'0120'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10087096',	 last => '10087097',	 list => '',  beginTime => '20090328.224159'}, # 	2009-03-28	22:41:59	2009-03-29	01:34:45
'0121'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10087110',	 last => '10087110',	 list => '',  beginTime => '20090329.013445'}, # 	2009-03-29	01:34:45	2009-03-29	05:27:08
'0122'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10088010',	 last => '10088013',	 list => '',  beginTime => '20090329.052708'}, # 	2009-03-29	05:27:08	2009-03-29	06:41:12
'0123'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10088016',	 last => '10088016',	 list => '',  beginTime => '20090329.064112'}, # 	2009-03-29	06:41:12	2009-03-29	07:12:43
'0124'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10088022',	 last => '10088022',	 list => '',  beginTime => '20090329.071243'}, # 	2009-03-29	07:12:43	2009-03-29	07:33:20
'0125'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10088024',	 last => '10088024',	 list => '',  beginTime => '20090329.073320'}, # 	2009-03-29	07:33:20	2009-03-29	07:49:23
'0126'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10088026',	 last => '10088031',	 list => '',  beginTime => '20090329.074923'}, # 	2009-03-29	07:49:23	2009-03-29	09:26:32
'0127'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10088033',	 last => '10088033',	 list => '',  beginTime => '20090329.092632'}, # 	2009-03-29	09:26:32	2009-03-29	09:39:51
'0128'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10088036',	 last => '10088036',	 list => '',  beginTime => '20090329.093951'}, # 	2009-03-29	09:39:51	2009-03-29	16:00:21
'0129'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10088058',	 last => '10088058',	 list => '',  beginTime => '20090329.160021'}, # 	2009-03-29	16:00:21	2009-03-29	16:26:22
'0130'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10088061',	 last => '10088064',	 list => '',  beginTime => '20090329.162622'}, # 	2009-03-29	16:26:22	2009-03-29	17:47:06
'0131'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10088069',	 last => '10088071',	 list => '',  beginTime => '20090329.174706'}, # 	2009-03-29	17:47:06	2009-03-29	19:20:03
'0132'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10088077',	 last => '10088077',	 list => '',  beginTime => '20090329.192003'}, # 	2009-03-29	19:20:03	2009-03-29	19:57:41
'0133'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10088081',	 last => '10088081',	 list => '',  beginTime => '20090329.195741'}, # 	2009-03-29	19:57:41	2009-03-29	20:13:56
'0134'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10088083',	 last => '10088085',	 list => '',  beginTime => '20090329.201356'}, # 	2009-03-29	20:13:56	2009-03-30	00:10:06
'0135'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10088096',	 last => '10088096',	 list => '',  beginTime => '20090330.001006'}, # 	2009-03-30	00:10:06	2009-03-30	00:31:08
'0136'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10088099',	 last => '10088099',	 list => '',  beginTime => '20090330.003108'}, # 	2009-03-30	00:31:08	2009-03-30	00:49:20
'0137'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10088102',	 last => '10088103',	 list => '',  beginTime => '20090330.004920'}, # 	2009-03-30	00:49:20	2009-03-30	02:10:49
'0138'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10088111',	 last => '10088111',	 list => '',  beginTime => '20090330.021049'}, # 	2009-03-30	02:10:49	2009-03-30	02:31:00
'0139'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10088113',	 last => '10088113',	 list => '',  beginTime => '20090330.023100'}, # 	2009-03-30	02:31:00	2009-03-30	03:31:55
'0140'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10088121',	 last => '10088121',	 list => '',  beginTime => '20090330.033155'}, # 	2009-03-30	03:31:55	2009-03-30	03:51:18	timestamp = production2009_500GeV_RF
'0141'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10088122',	 last => '10088122',	 list => '',  beginTime => '20090330.035118'}, # 	2009-03-30	03:51:18	2009-03-30	04:02:55	timestamp = production2009_500Gev_c_RF
'0142'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10089001',	 last => '10089001',	 list => '',  beginTime => '20090330.040255'}, # 	2009-03-30	04:02:55	2009-03-30	04:18:31	timestamp = production2009_500GeV_RF
'0143'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10089004',	 last => '10089004',	 list => '',  beginTime => '20090330.041831'}, # 	2009-03-30	04:18:31	2009-03-30	05:05:13
'0144'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10089008',	 last => '10089008',	 list => '',  beginTime => '20090330.050513'}, # 	2009-03-30	05:05:13	2009-03-30	05:26:46	timestamp = production2009_500Gev_c_RF
'0145'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10089010',	 last => '10089011',	 list => '',  beginTime => '20090330.052646'}, # 	2009-03-30	05:26:46	2009-03-30	06:14:44
'0146'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10089014',	 last => '10089016',	 list => '',  beginTime => '20090330.061444'}, # 	2009-03-30	06:14:44	2009-03-30	07:18:06
'0147'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10089019',	 last => '10089019',	 list => '',  beginTime => '20090330.071806'}, # 	2009-03-30	07:18:06	2009-03-30	07:43:52
'0148'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10089021',	 last => '10089021',	 list => '',  beginTime => '20090330.074352'}, # 	2009-03-30	07:43:52	2009-03-30	08:03:07
'0149'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10089023',	 last => '10089023',	 list => '',  beginTime => '20090330.080307'}, # 	2009-03-30	08:03:07	2009-03-31	01:13:26
'0150'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10089077',	 last => '10089077',	 list => '',  beginTime => '20090331.011326'}, # 	2009-03-31	01:13:26	2009-03-31	01:22:10
'0151'=> {trig=>'production2009_500Gev_25',	field => 'RF',	first=> '10089079',	 last => '10089079',	 list => '',  beginTime => '20090331.012210'}, # 	2009-03-31	01:22:10	2009-03-31	01:33:10	timestamp = production2009_500Gev_25_RF
'0152'=> {trig=>'production2009_500Gev_b',	field => 'RF',	first=> '10089080',	 last => '10089081',	 list => '',  beginTime => '20090331.013310'}, # 	2009-03-31	01:33:10	2009-03-31	04:10:04	timestamp = production2009_500Gev_b_RF
'0153'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10090001',	 last => '10090001',	 list => '',  beginTime => '20090331.041004'}, # 	2009-03-31	04:10:04	2009-03-31	04:35:40	timestamp = production2009_500Gev_c_RF
'0154'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10090004',	 last => '10090005',	 list => '',  beginTime => '20090331.043540'}, # 	2009-03-31	04:35:40	2009-03-31	05:52:18
'0155'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10090013',	 last => '10090013',	 list => '',  beginTime => '20090331.055218'}, # 	2009-03-31	05:52:18	2009-03-31	06:42:13
'0156'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10090015',	 last => '10090015',	 list => '',  beginTime => '20090331.064213'}, # 	2009-03-31	06:42:13	2009-03-31	07:12:17
'0157'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10090017',	 last => '10090020',	 list => '',  beginTime => '20090331.071217'}, # 	2009-03-31	07:12:17	2009-03-31	08:15:00
'0158'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10090022',	 last => '10090022',	 list => '',  beginTime => '20090331.081500'}, # 	2009-03-31	08:15:00	2009-03-31	08:48:15
'0159'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10090026',	 last => '10090027',	 list => '',  beginTime => '20090331.084815'}, # 	2009-03-31	08:48:15	2009-03-31	12:01:36
'0160'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10090037',	 last => '10090038',	 list => '',  beginTime => '20090331.120136'}, # 	2009-03-31	12:01:36	2009-03-31	12:34:13
'0161'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10090040',	 last => '10090042',	 list => '',  beginTime => '20090331.123413'}, # 	2009-03-31	12:34:13	2009-03-31	13:51:33
'0162'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10090046',	 last => '10090047',	 list => '',  beginTime => '20090331.135133'}, # 	2009-03-31	13:51:33	2009-03-31	17:53:26
'0163'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10090072',	 last => '10090072',	 list => '',  beginTime => '20090331.175326'}, # 	2009-03-31	17:53:26	2009-03-31	18:16:38
'0164'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10090074',	 last => '10090074',	 list => '',  beginTime => '20090331.181638'}, # 	2009-03-31	18:16:38	2009-03-31	18:34:31
'0165'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10090076',	 last => '10090076',	 list => '',  beginTime => '20090331.183431'}, # 	2009-03-31	18:34:31	2009-03-31	18:56:18
'0166'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10090079',	 last => '10090081',	 list => '',  beginTime => '20090331.185618'}, # 	2009-03-31	18:56:18	2009-03-31	19:41:28
'0167'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10090084',	 last => '10090084',	 list => '',  beginTime => '20090331.194128'}, # 	2009-03-31	19:41:28	2009-03-31	20:35:49
'0168'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10090089',	 last => '10090089',	 list => '',  beginTime => '20090331.203549'}, # 	2009-03-31	20:35:49	2009-03-31	21:07:36
'0169'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10090094',	 last => '10090094',	 list => '',  beginTime => '20090331.210736'}, # 	2009-03-31	21:07:36	2009-03-31	21:14:01	timestamp = production2009_500GeV_RF
'0170'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10090095',	 last => '10090096',	 list => '',  beginTime => '20090331.211401'}, # 	2009-03-31	21:14:01	2009-03-31	21:29:10	timestamp = production2009_500Gev_c_RF
'0171'=> {trig=>'production2009_500GeV', 	field => 'RF',	first=> '10090097',	 last => '10090097',	 list => '',  beginTime => '20090331.212910'}, # 	2009-03-31	21:29:10	2009-03-31	21:52:57	timestamp = production2009_500GeV_RF
'0172'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10090100',	 last => '10090100',	 list => '',  beginTime => '20090331.215257'}, # 	2009-03-31	21:52:57	2009-03-31	22:14:32	timestamp = production2009_500Gev_c_RF
'0173'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10090108',	 last => '10090109',	 list => '',  beginTime => '20090331.221432'}, # 	2009-03-31	22:14:32	2009-03-31	22:56:27
'0174'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10090111',	 last => '10090113',	 list => '',  beginTime => '20090331.225627'}, # 	2009-03-31	22:56:27	2009-04-02	04:38:38
'0175'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10092004',	 last => '10092004',	 list => '',  beginTime => '20090402.043838'}, # 	2009-04-02	04:38:38	2009-04-02	05:15:36
'0176'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10092009',	 last => '10092009',	 list => '',  beginTime => '20090402.051536'}, # 	2009-04-02	05:15:36	2009-04-02	05:40:20
'0177'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10092011',	 last => '10092011',	 list => '',  beginTime => '20090402.054020'}, # 	2009-04-02	05:40:20	2009-04-02	07:35:59
'0178'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10092021',	 last => '10092021',	 list => '',  beginTime => '20090402.073559'}, # 	2009-04-02	07:35:59	2009-04-02	07:58:10
'0179'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10092024',	 last => '10092024',	 list => '',  beginTime => '20090402.075810'}, # 	2009-04-02	07:58:10	2009-04-02	08:28:00
'0180'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10092027',	 last => '10092034',	 list => '',  beginTime => '20090402.082800'}, # 	2009-04-02	08:28:00	2009-04-02	10:14:03
'0181'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10092036',	 last => '10092040',	 list => '',  beginTime => '20090402.101403'}, # 	2009-04-02	10:14:03	2009-04-02	11:24:17
'0182'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10092042',	 last => '10092042',	 list => '',  beginTime => '20090402.112417'}, # 	2009-04-02	11:24:17	2009-04-02	12:01:38
'0183'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10092044',	 last => '10092044',	 list => '',  beginTime => '20090402.120138'}, # 	2009-04-02	12:01:38	2009-04-02	12:19:09
'0184'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10092046',	 last => '10092050',	 list => '',  beginTime => '20090402.121909'}, # 	2009-04-02	12:19:09	2009-04-03	01:17:29
'0185'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10092105',	 last => '10092105',	 list => '',  beginTime => '20090403.011729'}, # 	2009-04-03	01:17:29	2009-04-03	01:27:00
'0186'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10092107',	 last => '10092107',	 list => '',  beginTime => '20090403.012700'}, # 	2009-04-03	01:27:00	2009-04-03	01:41:43
'0187'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10092109',	 last => '10092109',	 list => '',  beginTime => '20090403.014143'}, # 	2009-04-03	01:41:43	2009-04-03	02:06:19
'0188'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10092114',	 last => '10092114',	 list => '',  beginTime => '20090403.020619'}, # 	2009-04-03	02:06:19	2009-04-03	02:17:29
'0189'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10092117',	 last => '10092117',	 list => '',  beginTime => '20090403.021729'}, # 	2009-04-03	02:17:29	2009-04-03	02:36:44
'0190'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10092120',	 last => '10092120',	 list => '',  beginTime => '20090403.023644'}, # 	2009-04-03	02:36:44	2009-04-03	02:58:47
'0191'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10092122',	 last => '10092122',	 list => '',  beginTime => '20090403.025847'}, # 	2009-04-03	02:58:47	2009-04-03	03:42:15
'0192'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10092130',	 last => '10092131',	 list => '',  beginTime => '20090403.034215'}, # 	2009-04-03	03:42:15	2009-04-03	04:12:36
'0193'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10093003',	 last => '10093004',	 list => '',  beginTime => '20090403.041236'}, # 	2009-04-03	04:12:36	2009-04-03	04:33:37
'0194'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10093006',	 last => '10093006',	 list => '',  beginTime => '20090403.043337'}, # 	2009-04-03	04:33:37	2009-04-03	04:49:02
'0195'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10093008',	 last => '10093008',	 list => '',  beginTime => '20090403.044902'}, # 	2009-04-03	04:49:02	2009-04-03	05:02:58
'0196'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10093011',	 last => '10093013',	 list => '',  beginTime => '20090403.050258'}, # 	2009-04-03	05:02:58	2009-04-03	06:59:06
'0197'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10093025',	 last => '10093030',	 list => '',  beginTime => '20090403.065906'}, # 	2009-04-03	06:59:06	2009-04-03	09:12:30
'0198'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10093033',	 last => '10093034',	 list => '',  beginTime => '20090403.091230'}, # 	2009-04-03	09:12:30	2009-04-03	09:46:53
'0199'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10093036',	 last => '10093036',	 list => '',  beginTime => '20090403.094653'}, # 	2009-04-03	09:46:53	2009-04-03	14:25:29
'0200'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10093048',	 last => '10093048',	 list => '',  beginTime => '20090403.142529'}, # 	2009-04-03	14:25:29	2009-04-03	17:22:22
'0201'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10093082',	 last => '10093085',	 list => '',  beginTime => '20090403.172222'}, # 	2009-04-03	17:22:22	2009-04-04	01:37:22
'0202'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10093110',	 last => '10093110',	 list => '',  beginTime => '20090404.013722'}, # 	2009-04-04	01:37:22	2009-04-04	04:13:39
'0203'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10094003',	 last => '10094003',	 list => '',  beginTime => '20090404.041339'}, # 	2009-04-04	04:13:39	2009-04-04	04:40:51
'0204'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10094005',	 last => '10094007',	 list => '',  beginTime => '20090404.044051'}, # 	2009-04-04	04:40:51	2009-04-04	06:32:57
'0205'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10094012',	 last => '10094012',	 list => '',  beginTime => '20090404.063257'}, # 	2009-04-04	06:32:57	2009-04-04	07:08:46
'0206'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10094018',	 last => '10094019',	 list => '',  beginTime => '20090404.070846'}, # 	2009-04-04	07:08:46	2009-04-04	07:59:02
'0207'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10094021',	 last => '10094024',	 list => '',  beginTime => '20090404.075902'}, # 	2009-04-04	07:59:02	2009-04-04	19:40:54
'0208'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10094063',	 last => '10094063',	 list => '',  beginTime => '20090404.194054'}, # 	2009-04-04	19:40:54	2009-04-04	20:26:09
'0209'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10094067',	 last => '10094068',	 list => '',  beginTime => '20090404.202609'}, # 	2009-04-04	20:26:09	2009-04-04	20:41:16
'0210'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10094071',	 last => '10094071',	 list => '',  beginTime => '20090404.204116'}, # 	2009-04-04	20:41:16	2009-04-04	21:03:58
'0211'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10094073',	 last => '10094073',	 list => '',  beginTime => '20090404.210358'}, # 	2009-04-04	21:03:58	2009-04-04	21:56:51
'0212'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10094077',	 last => '10094080',	 list => '',  beginTime => '20090404.215651'}, # 	2009-04-04	21:56:51	2009-04-04	22:42:55
'0213'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10094084',	 last => '10094090',	 list => '',  beginTime => '20090404.224255'}, # 	2009-04-04	22:42:55	2009-04-05	00:40:16
'0214'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10094092',	 last => '10094093',	 list => '',  beginTime => '20090405.004016'}, # 	2009-04-05	00:40:16	2009-04-05	01:07:11
'0215'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10094095',	 last => '10094096',	 list => '',  beginTime => '20090405.010711'}, # 	2009-04-05	01:07:11	2009-04-05	02:14:30
'0216'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10094098',	 last => '10094099',	 list => '',  beginTime => '20090405.021430'}, # 	2009-04-05	02:14:30	2009-04-05	11:45:47
'0217'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10095021',	 last => '10095022',	 list => '',  beginTime => '20090405.114547'}, # 	2009-04-05	11:45:47	2009-04-05	12:16:16
'0218'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10095024',	 last => '10095025',	 list => '',  beginTime => '20090405.121616'}, # 	2009-04-05	12:16:16	2009-04-05	12:42:31
'0219'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10095027',	 last => '10095027',	 list => '',  beginTime => '20090405.124231'}, # 	2009-04-05	12:42:31	2009-04-05	13:04:27
'0220'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10095030',	 last => '10095032',	 list => '',  beginTime => '20090405.130427'}, # 	2009-04-05	13:04:27	2009-04-05	13:49:09
'0221'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10095036',	 last => '10095041',	 list => '',  beginTime => '20090405.134909'}, # 	2009-04-05	13:49:09	2009-04-05	15:49:39
'0222'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10095045',	 last => '10095053',	 list => '',  beginTime => '20090405.154939'}, # 	2009-04-05	15:49:39	2009-04-06	02:34:51
'0223'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10095120',	 last => '10095121',	 list => '',  beginTime => '20090406.023451'}, # 	2009-04-06	02:34:51	2009-04-06	03:39:27
'0224'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10095125',	 last => '10095125',	 list => '',  beginTime => '20090406.033927'}, # 	2009-04-06	03:39:27	2009-04-06	04:05:53
'0225'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10096001',	 last => '10096002',	 list => '',  beginTime => '20090406.040553'}, # 	2009-04-06	04:05:53	2009-04-06	04:59:18
'0226'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10096005',	 last => '10096009',	 list => '',  beginTime => '20090406.045918'}, # 	2009-04-06	04:59:18	2009-04-06	07:13:01
'0227'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10096014',	 last => '10096015',	 list => '',  beginTime => '20090406.071301'}, # 	2009-04-06	07:13:01	2009-04-06	08:13:24
'0228'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10096019',	 last => '10096019',	 list => '',  beginTime => '20090406.081324'}, # 	2009-04-06	08:13:24	2009-04-06	09:00:02
'0229'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10096025',	 last => '10096027',	 list => '',  beginTime => '20090406.090002'}, # 	2009-04-06	09:00:02	2009-04-07	03:08:30
'0230'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10096139',	 last => '10096141',	 list => '',  beginTime => '20090407.030830'}, # 	2009-04-07	03:08:30	2009-04-07	04:59:18
'0231'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10097008',	 last => '10097008',	 list => '',  beginTime => '20090407.045918'}, # 	2009-04-07	04:59:18	2009-04-07	06:04:56
'0232'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10097015',	 last => '10097016',	 list => '',  beginTime => '20090407.060456'}, # 	2009-04-07	06:04:56	2009-04-07	07:13:17
'0233'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10097019',	 last => '10097019',	 list => '',  beginTime => '20090407.071317'}, # 	2009-04-07	07:13:17	2009-04-07	07:56:39
'0234'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10097021',	 last => '10097022',	 list => '',  beginTime => '20090407.075639'}, # 	2009-04-07	07:56:39	2009-04-07	08:55:26
'0235'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10097025',	 last => '10097026',	 list => '',  beginTime => '20090407.085526'}, # 	2009-04-07	08:55:26	2009-04-07	10:11:59
'0236'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10097029',	 last => '10097030',	 list => '',  beginTime => '20090407.101159'}, # 	2009-04-07	10:11:59	2009-04-07	10:45:30
'0237'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10097034',	 last => '10097034',	 list => '',  beginTime => '20090407.104530'}, # 	2009-04-07	10:45:30	2009-04-07	11:09:32
'0238'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10097038',	 last => '10097038',	 list => '',  beginTime => '20090407.110932'}, # 	2009-04-07	11:09:32	2009-04-07	11:30:11
'0239'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10097040',	 last => '10097040',	 list => '',  beginTime => '20090407.113011'}, # 	2009-04-07	11:30:11	2009-04-07	12:42:15
'0240'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10097044',	 last => '10097045',	 list => '',  beginTime => '20090407.124215'}, # 	2009-04-07	12:42:15	2009-04-07	19:11:48
'0241'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10097086',	 last => '10097090',	 list => '',  beginTime => '20090407.191148'}, # 	2009-04-07	19:11:48	2009-04-07	21:37:40
'0242'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10097102',	 last => '10097102',	 list => '',  beginTime => '20090407.213740'}, # 	2009-04-07	21:37:40	2009-04-07	21:48:26
'0243'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10097104',	 last => '10097104',	 list => '',  beginTime => '20090407.214826'}, # 	2009-04-07	21:48:26	2009-04-07	21:59:19
'0244'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10097106',	 last => '10097106',	 list => '',  beginTime => '20090407.215919'}, # 	2009-04-07	21:59:19	2009-04-07	22:20:55
'0245'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10097108',	 last => '10097108',	 list => '',  beginTime => '20090407.222055'}, # 	2009-04-07	22:20:55	2009-04-07	22:27:53
'0246'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10097110',	 last => '10097110',	 list => '',  beginTime => '20090407.222753'}, # 	2009-04-07	22:27:53	2009-04-08	00:31:53
'0247'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10097137',	 last => '10097137',	 list => '',  beginTime => '20090408.003153'}, # 	2009-04-08	00:31:53	2009-04-08	01:24:46
'0248'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10097140',	 last => '10097140',	 list => '',  beginTime => '20090408.012446'}, # 	2009-04-08	01:24:46	2009-04-08	08:09:03
'0249'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10098029',	 last => '10098029',	 list => '',  beginTime => '20090408.080903'}, # 	2009-04-08	08:09:03	2009-04-08	09:02:05
'0250'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10098035',	 last => '10098036',	 list => '',  beginTime => '20090408.090205'}, # 	2009-04-08	09:02:05	2009-04-08	09:33:12
'0251'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10098038',	 last => '10098038',	 list => '',  beginTime => '20090408.093312'}, # 	2009-04-08	09:33:12	2009-04-08	09:52:59
'0252'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10098040',	 last => '10098040',	 list => '',  beginTime => '20090408.095259'}, # 	2009-04-08	09:52:59	2009-04-08	10:28:12
'0253'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10098043',	 last => '10098046',	 list => '',  beginTime => '20090408.102812'}, # 	2009-04-08	10:28:12	2009-04-09	07:38:59
'0254'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10099055',	 last => '10099057',	 list => '',  beginTime => '20090409.073859'}, # 	2009-04-09	07:38:59	2009-04-09	08:56:29
'0255'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10099066',	 last => '10099068',	 list => '',  beginTime => '20090409.085629'}, # 	2009-04-09	08:56:29	2009-04-09	09:50:01
'0256'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10099071',	 last => '10099071',	 list => '',  beginTime => '20090409.095001'}, # 	2009-04-09	09:50:01	2009-04-09	10:11:51
'0257'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10099073',	 last => '10099074',	 list => '',  beginTime => '20090409.101151'}, # 	2009-04-09	10:11:51	2009-04-09	10:55:46
'0258'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10099077',	 last => '10099078',	 list => '',  beginTime => '20090409.105546'}, # 	2009-04-09	10:55:46	2009-04-10	02:02:07
'0259'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10099185',	 last => '10099189',	 list => '',  beginTime => '20090410.020207'}, # 	2009-04-10	02:02:07	2009-04-10	03:27:03
'0260'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10099194',	 last => '10099195',	 list => '',  beginTime => '20090410.032703'}, # 	2009-04-10	03:27:03	2009-04-10	04:48:23
'0261'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10100006',	 last => '10100006',	 list => '',  beginTime => '20090410.044823'}, # 	2009-04-10	04:48:23	2009-04-10	05:12:14
'0262'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10100008',	 last => '10100008',	 list => '',  beginTime => '20090410.051214'}, # 	2009-04-10	05:12:14	2009-04-10	05:29:04
'0263'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10100013',	 last => '10100017',	 list => '',  beginTime => '20090410.052904'}, # 	2009-04-10	05:29:04	2009-04-10	07:29:37
'0264'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10100021',	 last => '10100021',	 list => '',  beginTime => '20090410.072937'}, # 	2009-04-10	07:29:37	2009-04-10	09:28:06
'0265'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10100028',	 last => '10100029',	 list => '',  beginTime => '20090410.092806'}, # 	2009-04-10	09:28:06	2009-04-10	10:31:15
'0266'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10100032',	 last => '10100032',	 list => '',  beginTime => '20090410.103115'}, # 	2009-04-10	10:31:15	2009-04-10	15:04:20
'0267'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10100068',	 last => '10100068',	 list => '',  beginTime => '20090410.150420'}, # 	2009-04-10	15:04:20	2009-04-10	15:17:30
'0268'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10100070',	 last => '10100072',	 list => '',  beginTime => '20090410.151730'}, # 	2009-04-10	15:17:30	2009-04-10	16:28:12
'0269'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10100077',	 last => '10100077',	 list => '',  beginTime => '20090410.162812'}, # 	2009-04-10	16:28:12	2009-04-10	16:57:32
'0270'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10100079',	 last => '10100081',	 list => '',  beginTime => '20090410.165732'}, # 	2009-04-10	16:57:32	2009-04-10	18:10:32
'0271'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10100093',	 last => '10100093',	 list => '',  beginTime => '20090410.181032'}, # 	2009-04-10	18:10:32	2009-04-10	18:25:46
'0272'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10100095',	 last => '10100095',	 list => '',  beginTime => '20090410.182546'}, # 	2009-04-10	18:25:46	2009-04-10	18:46:48
'0273'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10100098',	 last => '10100098',	 list => '',  beginTime => '20090410.184648'}, # 	2009-04-10	18:46:48	2009-04-10	23:56:55
'0274'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10100164',	 last => '10100166',	 list => '',  beginTime => '20090410.235655'}, # 	2009-04-10	23:56:55	2009-04-11	01:04:08
'0275'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10100168',	 last => '10100169',	 list => '',  beginTime => '20090411.010408'}, # 	2009-04-11	01:04:08	2009-04-11	01:39:14
'0276'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10100172',	 last => '10100172',	 list => '',  beginTime => '20090411.013914'}, # 	2009-04-11	01:39:14	2009-04-11	02:02:36
'0277'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10100175',	 last => '10100176',	 list => '',  beginTime => '20090411.020236'}, # 	2009-04-11	02:02:36	2009-04-11	02:51:49
'0278'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10100178',	 last => '10100180',	 list => '',  beginTime => '20090411.025149'}, # 	2009-04-11	02:51:49	2009-04-11	04:06:57
'0279'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10101001',	 last => '10101001',	 list => '',  beginTime => '20090411.040657'}, # 	2009-04-11	04:06:57	2009-04-11	04:56:45
'0280'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10101006',	 last => '10101006',	 list => '',  beginTime => '20090411.045645'}, # 	2009-04-11	04:56:45	2009-04-11	05:11:08
'0281'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10101008',	 last => '10101009',	 list => '',  beginTime => '20090411.051108'}, # 	2009-04-11	05:11:08	2009-04-11	06:07:08
'0282'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10101011',	 last => '10101011',	 list => '',  beginTime => '20090411.060708'}, # 	2009-04-11	06:07:08	2009-04-11	06:49:47
'0283'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10101016',	 last => '10101016',	 list => '',  beginTime => '20090411.064947'}, # 	2009-04-11	06:49:47	2009-04-11	07:10:40
'0284'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10101018',	 last => '10101020',	 list => '',  beginTime => '20090411.071040'}, # 	2009-04-11	07:10:40	2009-04-11	10:48:21
'0285'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10101029',	 last => '10101030',	 list => '',  beginTime => '20090411.104821'}, # 	2009-04-11	10:48:21	2009-04-11	12:02:19
'0286'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10101037',	 last => '10101040',	 list => '',  beginTime => '20090411.120219'}, # 	2009-04-11	12:02:19	2009-04-11	20:27:48
'0287'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10101059',	 last => '10101065',	 list => '',  beginTime => '20090411.202748'}, # 	2009-04-11	20:27:48	2009-04-11	21:59:15
'0288'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10101069',	 last => '10101071',	 list => '',  beginTime => '20090411.215915'}, # 	2009-04-11	21:59:15	2009-04-11	22:54:13
'0289'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10101073',	 last => '10101074',	 list => '',  beginTime => '20090411.225413'}, # 	2009-04-11	22:54:13	2009-04-11	23:58:44
'0290'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10101078',	 last => '10101078',	 list => '',  beginTime => '20090411.235844'}, # 	2009-04-11	23:58:44	2009-04-12	00:22:31
'0291'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10101081',	 last => '10101081',	 list => '',  beginTime => '20090412.002231'}, # 	2009-04-12	00:22:31	2009-04-12	00:39:14
'0292'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10101083',	 last => '10101083',	 list => '',  beginTime => '20090412.003914'}, # 	2009-04-12	00:39:14	2009-04-12	01:23:44
'0293'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10101086',	 last => '10101092',	 list => '',  beginTime => '20090412.012344'}, # 	2009-04-12	01:23:44	2009-04-12	03:54:19
'0294'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10101094',	 last => '10101094',	 list => '',  beginTime => '20090412.035419'}, # 	2009-04-12	03:54:19	2009-04-12	04:36:30
'0295'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10102003',	 last => '10102003',	 list => '',  beginTime => '20090412.043630'}, # 	2009-04-12	04:36:30	2009-04-12	08:15:13
'0296'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10102031',	 last => '10102033',	 list => '',  beginTime => '20090412.081513'}, # 	2009-04-12	08:15:13	2009-04-12	09:21:51
'0297'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10102036',	 last => '10102039',	 list => '',  beginTime => '20090412.092151'}, # 	2009-04-12	09:21:51	2009-04-12	10:50:50
'0298'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10102045',	 last => '10102048',	 list => '',  beginTime => '20090412.105050'}, # 	2009-04-12	10:50:50	2009-04-12	11:53:47
'0299'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10102050',	 last => '10102051',	 list => '',  beginTime => '20090412.115347'}, # 	2009-04-12	11:53:47	2009-04-12	13:05:47
'0300'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10102055',	 last => '10102056',	 list => '',  beginTime => '20090412.130547'}, # 	2009-04-12	13:05:47	2009-04-12	14:04:50
'0301'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10102062',	 last => '10102063',	 list => '',  beginTime => '20090412.140450'}, # 	2009-04-12	14:04:50	2009-04-12	14:55:26
'0302'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10102065',	 last => '10102066',	 list => '',  beginTime => '20090412.145526'}, # 	2009-04-12	14:55:26	2009-04-12	16:13:54
'0303'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10102069',	 last => '10102070',	 list => '',  beginTime => '20090412.161354'}, # 	2009-04-12	16:13:54	2009-04-13	00:05:57
'0304'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10102094',	 last => '10102096',	 list => '',  beginTime => '20090413.000557'}, # 	2009-04-13	00:05:57	2009-04-13	00:52:15
'0305'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10102098',	 last => '10102098',	 list => '',  beginTime => '20090413.005215'}, # 	2009-04-13	00:52:15	2009-04-13	01:05:57
'0306'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10102100',	 last => '10102100',	 list => '',  beginTime => '20090413.010557'}, # 	2009-04-13	01:05:57	2009-04-13	01:49:35
'0307'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10102104',	 last => '10102105',	 list => '',  beginTime => '20090413.014935'}, # 	2009-04-13	01:49:35	2009-04-13	02:25:14
'0308'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10102107',	 last => '10102110',	 list => '',  beginTime => '20090413.022514'}, # 	2009-04-13	02:25:14	2009-04-13	03:42:53
'0309'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10102112',	 last => '10102112',	 list => '',  beginTime => '20090413.034253'}, # 	2009-04-13	03:42:53	2009-04-13	04:23:21
'0310'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10103001',	 last => '10103001',	 list => '',  beginTime => '20090413.042321'}, # 	2009-04-13	04:23:21	2009-04-13	05:50:18
'0311'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10103007',	 last => '10103008',	 list => '',  beginTime => '20090413.055018'}, # 	2009-04-13	05:50:18	2009-04-13	06:32:15
'0312'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10103010',	 last => '10103012',	 list => '',  beginTime => '20090413.063215'}, # 	2009-04-13	06:32:15	2009-04-13	07:29:10
'0313'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10103015',	 last => '10103018',	 list => '',  beginTime => '20090413.072910'}, # 	2009-04-13	07:29:10	2009-04-13	11:53:10
'0314'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10103027',	 last => '10103028',	 list => '',  beginTime => '20090413.115310'}, # 	2009-04-13	11:53:10	2009-04-13	13:01:30
'0315'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10103031',	 last => '10103031',	 list => '',  beginTime => '20090413.130130'}, # 	2009-04-13	13:01:30	2009-04-13	13:30:00
'0316'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10103034',	 last => '10103034',	 list => '',  beginTime => '20090413.133000'}, # 	2009-04-13	13:30:00	2009-04-13	14:30:23
'0317'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10103038',	 last => '10103038',	 list => '',  beginTime => '20090413.143023'}, # 	2009-04-13	14:30:23	2009-04-13	14:54:30
'0318'=> {trig=>'production2009_500Gev_c',	field => 'RF',	first=> '10103041',	 last => '10103042',	 list => '',  beginTime => '20090413.145430'}, # 	2009-04-13	14:54:30	2009-04-23	00:59:03
'0319'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10112099',	 last => '10112099',	 list => '',  beginTime => '20090423.005903'}, # 	2009-04-23	00:59:03	2009-04-23	01:47:39	timestamp = production2009_200Gev_Hi_RF
'0320'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10112105',	 last => '10112105',	 list => '',  beginTime => '20090423.014739'}, # 	2009-04-23	01:47:39	2009-04-23	02:14:02
'0321'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10112108',	 last => '10112109',	 list => '',  beginTime => '20090423.021402'}, # 	2009-04-23	02:14:02	2009-04-23	03:19:35
'0322'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10112111',	 last => '10112112',	 list => '',  beginTime => '20090423.031935'}, # 	2009-04-23	03:19:35	2009-04-23	03:56:47
'0323'=> {trig=>'production2009_200Gev_Lo',	field => 'RF',	first=> '10112121',	 last => '10112121',	 list => '',  beginTime => '20090423.035647'}, # 	2009-04-23	03:56:47	2009-04-23	04:07:42	timestamp = production2009_200Gev_Lo_RF
'0324'=> {trig=>'production2009_200Gev_Lo',	field => 'RF',	first=> '10113001',	 last => '10113001',	 list => '',  beginTime => '20090423.040742'}, # 	2009-04-23	04:07:42	2009-04-23	07:42:37
'0325'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10113011',	 last => '10113012',	 list => '',  beginTime => '20090423.074237'}, # 	2009-04-23	07:42:37	2009-04-23	08:50:21	timestamp = production2009_200Gev_Hi_RF
'0326'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10113015',	 last => '10113015',	 list => '',  beginTime => '20090423.085021'}, # 	2009-04-23	08:50:21	2009-04-23	09:08:43
'0327'=> {trig=>'production2009_200Gev_Lo',	field => 'RF',	first=> '10113018',	 last => '10113018',	 list => '',  beginTime => '20090423.090843'}, # 	2009-04-23	09:08:43	2009-04-23	09:53:08	timestamp = production2009_200Gev_Lo_RF
'0328'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10113021',	 last => '10113023',	 list => '',  beginTime => '20090423.095308'}, # 	2009-04-23	09:53:08	2009-04-23	11:04:36	timestamp = production2009_200Gev_Hi_RF
'0329'=> {trig=>'production2009_200Gev_Lo',	field => 'RF',	first=> '10113026',	 last => '10113026',	 list => '',  beginTime => '20090423.110436'}, # 	2009-04-23	11:04:36	2009-04-23	11:28:28	timestamp = production2009_200Gev_Lo_RF
'0330'=> {trig=>'production2009_200Gev_Lo',	field => 'RF',	first=> '10113028',	 last => '10113030',	 list => '',  beginTime => '20090423.112828'}, # 	2009-04-23	11:28:28	2009-04-23	21:31:16
'0331'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10113066',	 last => '10113066',	 list => '',  beginTime => '20090423.213116'}, # 	2009-04-23	21:31:16	2009-04-23	21:49:42	timestamp = production2009_200Gev_Hi_RF
'0332'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10113068',	 last => '10113068',	 list => '',  beginTime => '20090423.214942'}, # 	2009-04-23	21:49:42	2009-04-23	22:41:22
'0333'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10113073',	 last => '10113075',	 list => '',  beginTime => '20090423.224122'}, # 	2009-04-23	22:41:22	2009-04-24	00:04:34
'0334'=> {trig=>'production2009_200Gev_Lo',	field => 'RF',	first=> '10113081',	 last => '10113082',	 list => '',  beginTime => '20090424.000434'}, # 	2009-04-24	00:04:34	2009-04-24	00:12:05	timestamp = production2009_200Gev_Lo_RF
'0335'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10113084',	 last => '10113086',	 list => '',  beginTime => '20090424.001205'}, # 	2009-04-24	00:12:05	2009-04-24	01:31:40	timestamp = production2009_200Gev_Hi_RF
'0336'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10113088',	 last => '10113090',	 list => '',  beginTime => '20090424.013140'}, # 	2009-04-24	01:31:40	2009-04-24	03:49:16
'0337'=> {trig=>'production2009_200Gev_Lo',	field => 'RF',	first=> '10113105',	 last => '10113105',	 list => '',  beginTime => '20090424.034916'}, # 	2009-04-24	03:49:16	2009-04-24	05:02:19	timestamp = production2009_200Gev_Lo_RF
'0338'=> {trig=>'production2009_200Gev_Lo',	field => 'RF',	first=> '10114003',	 last => '10114003',	 list => '',  beginTime => '20090424.050219'}, # 	2009-04-24	05:02:19	2009-04-24	08:47:36
'0339'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10114016',	 last => '10114016',	 list => '',  beginTime => '20090424.084736'}, # 	2009-04-24	08:47:36	2009-04-24	09:17:44	timestamp = production2009_200Gev_Hi_RF
'0340'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10114021',	 last => '10114021',	 list => '',  beginTime => '20090424.091744'}, # 	2009-04-24	09:17:44	2009-04-24	09:42:53
'0341'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10114024',	 last => '10114034',	 list => '',  beginTime => '20090424.094253'}, # 	2009-04-24	09:42:53	2009-04-24	12:41:53
'0342'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10114037',	 last => '10114038',	 list => '',  beginTime => '20090424.124153'}, # 	2009-04-24	12:41:53	2009-04-24	13:37:10
'0343'=> {trig=>'production2009_200Gev_Lo',	field => 'RF',	first=> '10114039',	 last => '10114041',	 list => '',  beginTime => '20090424.133710'}, # 	2009-04-24	13:37:10	2009-04-24	15:21:29	timestamp = production2009_200Gev_Lo_RF
'0344'=> {trig=>'production2009_200Gev_Lo',	field => 'RF',	first=> '10114045',	 last => '10114046',	 list => '',  beginTime => '20090424.152129'}, # 	2009-04-24	15:21:29	2009-04-24	16:18:23
'0345'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10114053',	 last => '10114054',	 list => '',  beginTime => '20090424.161823'}, # 	2009-04-24	16:18:23	2009-04-24	21:47:48	timestamp = production2009_200Gev_Hi_RF
'0346'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10114070',	 last => '10114071',	 list => '',  beginTime => '20090424.214748'}, # 	2009-04-24	21:47:48	2009-04-24	22:21:34
'0347'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10114074',	 last => '10114074',	 list => '',  beginTime => '20090424.222134'}, # 	2009-04-24	22:21:34	2009-04-24	22:52:38
'0348'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10114077',	 last => '10114082',	 list => '',  beginTime => '20090424.225238'}, # 	2009-04-24	22:52:38	2009-04-25	01:15:06
'0349'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10114084',	 last => '10114084',	 list => '',  beginTime => '20090425.011506'}, # 	2009-04-25	01:15:06	2009-04-25	01:56:08
'0350'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10114087',	 last => '10114090',	 list => '',  beginTime => '20090425.015608'}, # 	2009-04-25	01:56:08	2009-04-25	03:57:00
'0351'=> {trig=>'production2009_200Gev_Lo',	field => 'RF',	first=> '10114091',	 last => '10114091',	 list => '',  beginTime => '20090425.035700'}, # 	2009-04-25	03:57:00	2009-04-25	04:14:18	timestamp = production2009_200Gev_Lo_RF
'0352'=> {trig=>'production2009_200Gev_Lo',	field => 'RF',	first=> '10115001',	 last => '10115002',	 list => '',  beginTime => '20090425.041418'}, # 	2009-04-25	04:14:18	2009-04-25	05:21:01
'0353'=> {trig=>'production2009_200Gev_Lo',	field => 'RF',	first=> '10115006',	 last => '10115006',	 list => '',  beginTime => '20090425.052101'}, # 	2009-04-25	05:21:01	2009-04-25	09:00:32
'0354'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10115017',	 last => '10115017',	 list => '',  beginTime => '20090425.090032'}, # 	2009-04-25	09:00:32	2009-04-25	09:13:58	timestamp = production2009_200Gev_Hi_RF
'0355'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10115019',	 last => '10115021',	 list => '',  beginTime => '20090425.091358'}, # 	2009-04-25	09:13:58	2009-04-25	10:07:47
'0356'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10115025',	 last => '10115029',	 list => '',  beginTime => '20090425.100747'}, # 	2009-04-25	10:07:47	2009-04-25	11:40:29
'0357'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10115031',	 last => '10115034',	 list => '',  beginTime => '20090425.114029'}, # 	2009-04-25	11:40:29	2009-04-25	13:20:57
'0358'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10115037',	 last => '10115043',	 list => '',  beginTime => '20090425.132057'}, # 	2009-04-25	13:20:57	2009-04-25	15:45:57
'0359'=> {trig=>'production2009_200Gev_Lo',	field => 'RF',	first=> '10115044',	 last => '10115044',	 list => '',  beginTime => '20090425.154557'}, # 	2009-04-25	15:45:57	2009-04-25	16:35:56	timestamp = production2009_200Gev_Lo_RF
'0360'=> {trig=>'production2009_200Gev_Lo',	field => 'RF',	first=> '10115047',	 last => '10115047',	 list => '',  beginTime => '20090425.163556'}, # 	2009-04-25	16:35:56	2009-04-25	17:12:23
'0361'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10115050',	 last => '10115053',	 list => '',  beginTime => '20090425.171223'}, # 	2009-04-25	17:12:23	2009-04-25	20:21:55	timestamp = production2009_200Gev_Hi_RF
'0362'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10115066',	 last => '10115067',	 list => '',  beginTime => '20090425.202155'}, # 	2009-04-25	20:21:55	2009-04-25	21:40:13
'0363'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10115072',	 last => '10115074',	 list => '',  beginTime => '20090425.214013'}, # 	2009-04-25	21:40:13	2009-04-25	22:52:15
'0364'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10115077',	 last => '10115077',	 list => '',  beginTime => '20090425.225215'}, # 	2009-04-25	22:52:15	2009-04-25	23:44:06
'0365'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10115082',	 last => '10115083',	 list => '',  beginTime => '20090425.234406'}, # 	2009-04-25	23:44:06	2009-04-26	00:58:46
'0366'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10115086',	 last => '10115086',	 list => '',  beginTime => '20090426.005846'}, # 	2009-04-26	00:58:46	2009-04-26	01:09:18
'0367'=> {trig=>'production2009_200Gev_Lo',	field => 'RF',	first=> '10115087',	 last => '10115088',	 list => '',  beginTime => '20090426.010918'}, # 	2009-04-26	01:09:18	2009-04-26	01:16:31	timestamp = production2009_200Gev_Lo_RF
'0368'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10115089',	 last => '10115089',	 list => '',  beginTime => '20090426.011631'}, # 	2009-04-26	01:16:31	2009-04-26	02:18:48	timestamp = production2009_200Gev_Hi_RF
'0369'=> {trig=>'production2009_200Gev_Lo',	field => 'RF',	first=> '10115093',	 last => '10115093',	 list => '',  beginTime => '20090426.021848'}, # 	2009-04-26	02:18:48	2009-04-26	02:21:19	timestamp = production2009_200Gev_Lo_RF
'0370'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10115094',	 last => '10115094',	 list => '',  beginTime => '20090426.022119'}, # 	2009-04-26	02:21:19	2009-04-26	03:00:47	timestamp = production2009_200Gev_Hi_RF
'0371'=> {trig=>'production2009_200Gev_Lo',	field => 'RF',	first=> '10115095',	 last => '10115095',	 list => '',  beginTime => '20090426.030047'}, # 	2009-04-26	03:00:47	2009-04-26	03:39:27	timestamp = production2009_200Gev_Lo_RF
'0372'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10115096',	 last => '10115096',	 list => '',  beginTime => '20090426.033927'}, # 	2009-04-26	03:39:27	2009-04-26	03:45:25	timestamp = production2009_200Gev_Hi_RF
'0373'=> {trig=>'production2009_200Gev_Lo',	field => 'RF',	first=> '10115097',	 last => '10115097',	 list => '',  beginTime => '20090426.034525'}, # 	2009-04-26	03:45:25	2009-04-26	04:07:57	timestamp = production2009_200Gev_Lo_RF
'0374'=> {trig=>'production2009_200Gev_Lo',	field => 'RF',	first=> '10116002',	 last => '10116002',	 list => '',  beginTime => '20090426.040757'}, # 	2009-04-26	04:07:57	2009-04-26	04:48:43
'0375'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10116003',	 last => '10116003',	 list => '',  beginTime => '20090426.044843'}, # 	2009-04-26	04:48:43	2009-04-26	08:59:35	timestamp = production2009_200Gev_Hi_RF
'0376'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10116009',	 last => '10116012',	 list => '',  beginTime => '20090426.085935'}, # 	2009-04-26	08:59:35	2009-04-26	10:15:13
'0377'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10116015',	 last => '10116016',	 list => '',  beginTime => '20090426.101513'}, # 	2009-04-26	10:15:13	2009-04-26	11:22:33
'0378'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10116018',	 last => '10116019',	 list => '',  beginTime => '20090426.112233'}, # 	2009-04-26	11:22:33	2009-04-26	17:00:55
'0379'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10116030',	 last => '10116033',	 list => '',  beginTime => '20090426.170055'}, # 	2009-04-26	17:00:55	2009-04-26	23:50:55
'0380'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10116042',	 last => '10116042',	 list => '',  beginTime => '20090426.235055'}, # 	2009-04-26	23:50:55	2009-04-27	00:18:31
'0381'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10116047',	 last => '10116048',	 list => '',  beginTime => '20090427.001831'}, # 	2009-04-27	00:18:31	2009-04-27	01:14:23
'0382'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10116051',	 last => '10116056',	 list => '',  beginTime => '20090427.011423'}, # 	2009-04-27	01:14:23	2009-04-27	04:12:33
'0383'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10117003',	 last => '10117004',	 list => '',  beginTime => '20090427.041233'}, # 	2009-04-27	04:12:33	2009-04-27	05:59:55
'0384'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10117012',	 last => '10117014',	 list => '',  beginTime => '20090427.055955'}, # 	2009-04-27	05:59:55	2009-04-27	06:59:49
'0385'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10117017',	 last => '10117017',	 list => '',  beginTime => '20090427.065949'}, # 	2009-04-27	06:59:49	2009-04-27	07:23:46
'0386'=> {trig=>'production2009_200Gev_Lo',	field => 'RF',	first=> '10117018',	 last => '10117020',	 list => '',  beginTime => '20090427.072346'}, # 	2009-04-27	07:23:46	2009-04-27	09:58:59	timestamp = production2009_200Gev_Lo_RF
'0387'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10117027',	 last => '10117028',	 list => '',  beginTime => '20090427.095859'}, # 	2009-04-27	09:58:59	2009-04-27	11:54:59	timestamp = production2009_200Gev_Hi_RF
'0388'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10117039',	 last => '10117046',	 list => '',  beginTime => '20090427.115459'}, # 	2009-04-27	11:54:59	2009-04-27	15:56:22
'0389'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10117051',	 last => '10117052',	 list => '',  beginTime => '20090427.155622'}, # 	2009-04-27	15:56:22	2009-04-27	16:41:29
'0390'=> {trig=>'production2009_200Gev_Lo',	field => 'RF',	first=> '10117055',	 last => '10117055',	 list => '',  beginTime => '20090427.164129'}, # 	2009-04-27	16:41:29	2009-04-27	16:50:01	timestamp = production2009_200Gev_Lo_RF
'0391'=> {trig=>'production2009_200Gev_Lo',	field => 'RF',	first=> '10117058',	 last => '10117062',	 list => '',  beginTime => '20090427.165001'}, # 	2009-04-27	16:50:01	2009-04-28	03:08:06
'0392'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10117085',	 last => '10117087',	 list => '',  beginTime => '20090428.030806'}, # 	2009-04-28	03:08:06	2009-04-28	04:18:09	timestamp = production2009_200Gev_Hi_RF
'0393'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10118003',	 last => '10118003',	 list => '',  beginTime => '20090428.041809'}, # 	2009-04-28	04:18:09	2009-04-28	05:02:19
'0394'=> {trig=>'production2009_200Gev_Lo',	field => 'RF',	first=> '10118006',	 last => '10118006',	 list => '',  beginTime => '20090428.050219'}, # 	2009-04-28	05:02:19	2009-04-28	05:08:07	timestamp = production2009_200Gev_Lo_RF
'0395'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10118007',	 last => '10118008',	 list => '',  beginTime => '20090428.050807'}, # 	2009-04-28	05:08:07	2009-04-28	06:10:53	timestamp = production2009_200Gev_Hi_RF
'0396'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10118011',	 last => '10118012',	 list => '',  beginTime => '20090428.061053'}, # 	2009-04-28	06:10:53	2009-04-28	07:20:11
'0397'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10118015',	 last => '10118015',	 list => '',  beginTime => '20090428.072011'}, # 	2009-04-28	07:20:11	2009-04-28	08:05:10
'0398'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10118018',	 last => '10118018',	 list => '',  beginTime => '20090428.080510'}, # 	2009-04-28	08:05:10	2009-04-28	08:30:45
'0399'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10118021',	 last => '10118022',	 list => '',  beginTime => '20090428.083045'}, # 	2009-04-28	08:30:45	2009-04-28	09:45:06
'0400'=> {trig=>'production2009_200Gev_Lo',	field => 'RF',	first=> '10118025',	 last => '10118027',	 list => '',  beginTime => '20090428.094506'}, # 	2009-04-28	09:45:06	2009-04-28	11:33:36	timestamp = production2009_200Gev_Lo_RF
'0401'=> {trig=>'production2009_200Gev_Lo',	field => 'RF',	first=> '10118029',	 last => '10118029',	 list => '',  beginTime => '20090428.113336'}, # 	2009-04-28	11:33:36	2009-04-28	22:07:36
'0402'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10118084',	 last => '10118086',	 list => '',  beginTime => '20090428.220736'}, # 	2009-04-28	22:07:36	2009-04-28	22:17:42	timestamp = production2009_200Gev_Hi_RF
'0403'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10118088',	 last => '10118089',	 list => '',  beginTime => '20090428.221742'}, # 	2009-04-28	22:17:42	2009-04-28	22:24:34
'0404'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10118091',	 last => '10118092',	 list => '',  beginTime => '20090428.222434'}, # 	2009-04-28	22:24:34	2009-04-30	06:56:18
'0405'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10120014',	 last => '10120015',	 list => '',  beginTime => '20090430.065618'}, # 	2009-04-30	06:56:18	2009-04-30	08:07:44
'0406'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10120019',	 last => '10120021',	 list => '',  beginTime => '20090430.080744'}, # 	2009-04-30	08:07:44	2009-04-30	09:33:37
'0407'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10120023',	 last => '10120023',	 list => '',  beginTime => '20090430.093337'}, # 	2009-04-30	09:33:37	2009-04-30	10:25:27
'0408'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10120025',	 last => '10120025',	 list => '',  beginTime => '20090430.102527'}, # 	2009-04-30	10:25:27	2009-04-30	10:52:47
'0409'=> {trig=>'production2009_200Gev_Lo',	field => 'RF',	first=> '10120027',	 last => '10120027',	 list => '',  beginTime => '20090430.105247'}, # 	2009-04-30	10:52:47	2009-04-30	11:40:48	timestamp = production2009_200Gev_Lo_RF
'0410'=> {trig=>'production2009_200Gev_Lo',	field => 'RF',	first=> '10120032',	 last => '10120035',	 list => '',  beginTime => '20090430.114048'}, # 	2009-04-30	11:40:48	2009-04-30	17:16:21
'0411'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10120063',	 last => '10120063',	 list => '',  beginTime => '20090430.171621'}, # 	2009-04-30	17:16:21	2009-04-30	18:07:45	timestamp = production2009_200Gev_Hi_RF
'0412'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10120065',	 last => '10120065',	 list => '',  beginTime => '20090430.180745'}, # 	2009-04-30	18:07:45	2009-04-30	20:32:31
'0413'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10120078',	 last => '10120079',	 list => '',  beginTime => '20090430.203231'}, # 	2009-04-30	20:32:31	2009-04-30	21:44:36
'0414'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10120082',	 last => '10120082',	 list => '',  beginTime => '20090430.214436'}, # 	2009-04-30	21:44:36	2009-04-30	22:55:10
'0415'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10120085',	 last => '10120086',	 list => '',  beginTime => '20090430.225510'}, # 	2009-04-30	22:55:10	2009-05-01	02:11:52
'0416'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10120093',	 last => '10120093',	 list => '',  beginTime => '20090501.021152'}, # 	2009-05-01	02:11:52	2009-05-01	03:03:24
'0417'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10120097',	 last => '10120097',	 list => '',  beginTime => '20090501.030324'}, # 	2009-05-01	03:03:24	2009-05-01	03:53:55
'0418'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10120100',	 last => '10120100',	 list => '',  beginTime => '20090501.035355'}, # 	2009-05-01	03:53:55	2009-05-01	04:43:34
'0419'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10121001',	 last => '10121001',	 list => '',  beginTime => '20090501.044334'}, # 	2009-05-01	04:43:34	2009-05-01	07:25:20
'0420'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10121017',	 last => '10121017',	 list => '',  beginTime => '20090501.072520'}, # 	2009-05-01	07:25:20	2009-05-01	10:44:22
'0421'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10121040',	 last => '10121040',	 list => '',  beginTime => '20090501.104422'}, # 	2009-05-01	10:44:22	2009-05-01	11:31:21
'0422'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10121043',	 last => '10121044',	 list => '',  beginTime => '20090501.113121'}, # 	2009-05-01	11:31:21	2009-05-01	12:29:47
'0423'=> {trig=>'production2009_200Gev_Lo',	field => 'RF',	first=> '10121045',	 last => '10121045',	 list => '',  beginTime => '20090501.122947'}, # 	2009-05-01	12:29:47	2009-05-01	13:33:31	timestamp = production2009_200Gev_Lo_RF
'0424'=> {trig=>'production2009_200Gev_Lo',	field => 'RF',	first=> '10121051',	 last => '10121053',	 list => '',  beginTime => '20090501.133331'}, # 	2009-05-01	13:33:31	2009-05-01	21:02:24
'0425'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10121088',	 last => '10121088',	 list => '',  beginTime => '20090501.210224'}, # 	2009-05-01	21:02:24	2009-05-01	21:42:22	timestamp = production2009_200Gev_Hi_RF
'0426'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10121091',	 last => '10121097',	 list => '',  beginTime => '20090501.214222'}, # 	2009-05-01	21:42:22	2009-05-02	04:21:20
'0427'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10122006',	 last => '10122007',	 list => '',  beginTime => '20090502.042120'}, # 	2009-05-02	04:21:20	2009-05-02	05:30:46
'0428'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10122010',	 last => '10122010',	 list => '',  beginTime => '20090502.053046'}, # 	2009-05-02	05:30:46	2009-05-02	06:36:30
'0429'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10122013',	 last => '10122019',	 list => '',  beginTime => '20090502.063630'}, # 	2009-05-02	06:36:30	2009-05-02	08:58:23
'0430'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10122022',	 last => '10122024',	 list => '',  beginTime => '20090502.085823'}, # 	2009-05-02	08:58:23	2009-05-02	10:44:37
'0431'=> {trig=>'production2009_200Gev_Lo',	field => 'RF',	first=> '10122025',	 last => '10122025',	 list => '',  beginTime => '20090502.104437'}, # 	2009-05-02	10:44:37	2009-05-02	11:49:30	timestamp = production2009_200Gev_Lo_RF
'0432'=> {trig=>'production2009_200Gev_Lo',	field => 'RF',	first=> '10122031',	 last => '10122031',	 list => '',  beginTime => '20090502.114930'}, # 	2009-05-02	11:49:30	2009-05-02	12:28:19
'0433'=> {trig=>'production2009_200Gev_Lo',	field => 'RF',	first=> '10122033',	 last => '10122033',	 list => '',  beginTime => '20090502.122819'}, # 	2009-05-02	12:28:19	2009-05-02	14:39:02
'0434'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10122047',	 last => '10122049',	 list => '',  beginTime => '20090502.143902'}, # 	2009-05-02	14:39:02	2009-05-02	16:37:30	timestamp = production2009_200Gev_Hi_RF
'0435'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10122054',	 last => '10122055',	 list => '',  beginTime => '20090502.163730'}, # 	2009-05-02	16:37:30	2009-05-02	17:45:27
'0436'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10122060',	 last => '10122061',	 list => '',  beginTime => '20090502.174527'}, # 	2009-05-02	17:45:27	2009-05-02	19:08:10
'0437'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10122065',	 last => '10122065',	 list => '',  beginTime => '20090502.190810'}, # 	2009-05-02	19:08:10	2009-05-02	19:52:57
'0438'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10122067',	 last => '10122067',	 list => '',  beginTime => '20090502.195257'}, # 	2009-05-02	19:52:57	2009-05-02	20:30:11
'0439'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10122071',	 last => '10122071',	 list => '',  beginTime => '20090502.203011'}, # 	2009-05-02	20:30:11	2009-05-02	21:10:41
'0440'=> {trig=>'production2009_200Gev_Lo',	field => 'RF',	first=> '10122072',	 last => '10122075',	 list => '',  beginTime => '20090502.211041'}, # 	2009-05-02	21:10:41	2009-05-03	01:32:40	timestamp = production2009_200Gev_Lo_RF
'0441'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10122086',	 last => '10122087',	 list => '',  beginTime => '20090503.013240'}, # 	2009-05-03	01:32:40	2009-05-03	03:00:35	timestamp = production2009_200Gev_Hi_RF
'0442'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10122095',	 last => '10122095',	 list => '',  beginTime => '20090503.030035'}, # 	2009-05-03	03:00:35	2009-05-03	03:34:27
'0443'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10122098',	 last => '10122099',	 list => '',  beginTime => '20090503.033427'}, # 	2009-05-03	03:34:27	2009-05-03	04:24:59
'0444'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10123004',	 last => '10123004',	 list => '',  beginTime => '20090503.042459'}, # 	2009-05-03	04:24:59	2009-05-03	04:44:45
'0445'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10123007',	 last => '10123007',	 list => '',  beginTime => '20090503.044445'}, # 	2009-05-03	04:44:45	2009-05-03	05:36:36
'0446'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10123010',	 last => '10123010',	 list => '',  beginTime => '20090503.053636'}, # 	2009-05-03	05:36:36	2009-05-03	06:13:48
'0447'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10123013',	 last => '10123015',	 list => '',  beginTime => '20090503.061348'}, # 	2009-05-03	06:13:48	2009-05-03	07:44:23
'0448'=> {trig=>'production2009_200Gev_Lo',	field => 'RF',	first=> '10123016',	 last => '10123019',	 list => '',  beginTime => '20090503.074423'}, # 	2009-05-03	07:44:23	2009-05-03	09:00:44	timestamp = production2009_200Gev_Lo_RF
'0449'=> {trig=>'production2009_200Gev_Lo',	field => 'RF',	first=> '10123022',	 last => '10123024',	 list => '',  beginTime => '20090503.090044'}, # 	2009-05-03	09:00:44	2009-05-04	03:11:02
'0450'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10123086',	 last => '10123088',	 list => '',  beginTime => '20090504.031102'}, # 	2009-05-04	03:11:02	2009-05-04	03:42:54	timestamp = production2009_200Gev_Hi_RF
'0451'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10123090',	 last => '10123090',	 list => '',  beginTime => '20090504.034254'}, # 	2009-05-04	03:42:54	2009-05-04	05:00:59
'0452'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10124011',	 last => '10124012',	 list => '',  beginTime => '20090504.050059'}, # 	2009-05-04	05:00:59	2009-05-04	05:39:38
'0453'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10124014',	 last => '10124014',	 list => '',  beginTime => '20090504.053938'}, # 	2009-05-04	05:39:38	2009-05-04	07:06:21
'0454'=> {trig=>'production2009_200Gev_Lo',	field => 'RF',	first=> '10124024',	 last => '10124026',	 list => '',  beginTime => '20090504.070621'}, # 	2009-05-04	07:06:21	2009-05-04	10:09:36	timestamp = production2009_200Gev_Lo_RF
'0455'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10124037',	 last => '10124038',	 list => '',  beginTime => '20090504.100936'}, # 	2009-05-04	10:09:36	2009-05-04	11:30:35	timestamp = production2009_200Gev_Hi_RF
'0456'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10124044',	 last => '10124046',	 list => '',  beginTime => '20090504.113035'}, # 	2009-05-04	11:30:35	2009-05-04	13:12:29
'0457'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10124049',	 last => '10124050',	 list => '',  beginTime => '20090504.131229'}, # 	2009-05-04	13:12:29	2009-05-04	13:59:09
'0458'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10124053',	 last => '10124053',	 list => '',  beginTime => '20090504.135909'}, # 	2009-05-04	13:59:09	2009-05-04	14:10:46
'0459'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10124055',	 last => '10124055',	 list => '',  beginTime => '20090504.141046'}, # 	2009-05-04	14:10:46	2009-05-04	14:18:49
'0460'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10124057',	 last => '10124057',	 list => '',  beginTime => '20090504.141849'}, # 	2009-05-04	14:18:49	2009-05-04	14:44:04
'0461'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10124062',	 last => '10124062',	 list => '',  beginTime => '20090504.144404'}, # 	2009-05-04	14:44:04	2009-05-04	15:38:36
'0462'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10124066',	 last => '10124066',	 list => '',  beginTime => '20090504.153836'}, # 	2009-05-04	15:38:36	2009-05-04	16:15:54
'0463'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10124071',	 last => '10124072',	 list => '',  beginTime => '20090504.161554'}, # 	2009-05-04	16:15:54	2009-05-04	17:17:44
'0464'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10124075',	 last => '10124076',	 list => '',  beginTime => '20090504.171744'}, # 	2009-05-04	17:17:44	2009-05-05	03:37:21
'0465'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10124110',	 last => '10124113',	 list => '',  beginTime => '20090505.033721'}, # 	2009-05-05	03:37:21	2009-05-05	04:10:09
'0466'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10125001',	 last => '10125001',	 list => '',  beginTime => '20090505.041009'}, # 	2009-05-05	04:10:09	2009-05-05	05:15:11
'0467'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10125008',	 last => '10125010',	 list => '',  beginTime => '20090505.051511'}, # 	2009-05-05	05:15:11	2009-05-05	06:50:45
'0468'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10125014',	 last => '10125017',	 list => '',  beginTime => '20090505.065045'}, # 	2009-05-05	06:50:45	2009-05-05	09:01:13
'0469'=> {trig=>'production2009_200Gev_Hi',	field => 'RF',	first=> '10125022',	 last => '10125023',	 list => '',  beginTime => '20090505.090113'}, # 	2009-05-05	09:01:13	2009-05-05	10:08:47
'0470'=> {trig=>'production2009_200Gev_Lo',	field => 'RF',	first=> '10125024',	 last => '10125024',	 list => '',  beginTime => '20090505.100847'}, # 	2009-05-05	10:08:47	2009-05-05	11:25:45	timestamp = production2009_200Gev_Lo_RF
'0471'=> {trig=>'production2009_200Gev_Lo',	field => 'RF',	first=> '10125026',	 last => '10125027',	 list => '',  beginTime => '20090505.112545'}, # 	2009-05-05	11:25:45	2009-05-05	18:47:45
'0472'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10125055',	 last => '10125055',	 list => '',  beginTime => '20090505.184745'}, # 	2009-05-05	18:47:45	2009-05-05	19:42:43	timestamp = production2009_200Gev_Single_RF
'0473'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10125064',	 last => '10125066',	 list => '',  beginTime => '20090505.194243'}, # 	2009-05-05	19:42:43	2009-05-05	20:54:30
'0474'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10125068',	 last => '10125069',	 list => '',  beginTime => '20090505.205430'}, # 	2009-05-05	20:54:30	2009-05-05	23:34:51
'0475'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10125076',	 last => '10125076',	 list => '',  beginTime => '20090505.233451'}, # 	2009-05-05	23:34:51	2009-05-06	00:28:06
'0476'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10125080',	 last => '10125080',	 list => '',  beginTime => '20090506.002806'}, # 	2009-05-06	00:28:06	2009-05-06	00:50:38
'0477'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10125083',	 last => '10125083',	 list => '',  beginTime => '20090506.005038'}, # 	2009-05-06	00:50:38	2009-05-06	03:50:34
'0478'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10125091',	 last => '10125091',	 list => '',  beginTime => '20090506.035034'}, # 	2009-05-06	03:50:34	2009-05-06	04:28:58
'0479'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10126003',	 last => '10126005',	 list => '',  beginTime => '20090506.042858'}, # 	2009-05-06	04:28:58	2009-05-06	07:25:35
'0480'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10126012',	 last => '10126012',	 list => '',  beginTime => '20090506.072535'}, # 	2009-05-06	07:25:35	2009-05-06	08:08:19
'0481'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10126016',	 last => '10126020',	 list => '',  beginTime => '20090506.080819'}, # 	2009-05-06	08:08:19	2009-05-06	10:24:37
'0482'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10126024',	 last => '10126026',	 list => '',  beginTime => '20090506.102437'}, # 	2009-05-06	10:24:37	2009-05-06	16:56:23
'0483'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10126046',	 last => '10126047',	 list => '',  beginTime => '20090506.165623'}, # 	2009-05-06	16:56:23	2009-05-06	17:57:37
'0484'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10126052',	 last => '10126052',	 list => '',  beginTime => '20090506.175737'}, # 	2009-05-06	17:57:37	2009-05-06	20:21:07
'0485'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10126064',	 last => '10126064',	 list => '',  beginTime => '20090506.202107'}, # 	2009-05-06	20:21:07	2009-05-06	21:01:28
'0486'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10126067',	 last => '10126069',	 list => '',  beginTime => '20090506.210128'}, # 	2009-05-06	21:01:28	2009-05-06	22:31:22
'0487'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10126073',	 last => '10126075',	 list => '',  beginTime => '20090506.223122'}, # 	2009-05-06	22:31:22	2009-05-06	23:19:32
'0488'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10126080',	 last => '10126084',	 list => '',  beginTime => '20090506.231932'}, # 	2009-05-06	23:19:32	2009-05-07	01:39:26
'0489'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10126087',	 last => '10126090',	 list => '',  beginTime => '20090507.013926'}, # 	2009-05-07	01:39:26	2009-05-07	10:49:13
'0490'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10127007',	 last => '10127011',	 list => '',  beginTime => '20090507.104913'}, # 	2009-05-07	10:49:13	2009-05-08	02:44:19
'0491'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10127039',	 last => '10127039',	 list => '',  beginTime => '20090508.024419'}, # 	2009-05-08	02:44:19	2009-05-08	03:21:09
'0492'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10127043',	 last => '10127044',	 list => '',  beginTime => '20090508.032109'}, # 	2009-05-08	03:21:09	2009-05-08	03:40:57
'0493'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10127047',	 last => '10127047',	 list => '',  beginTime => '20090508.034057'}, # 	2009-05-08	03:40:57	2009-05-08	04:10:11
'0494'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10128001',	 last => '10128004',	 list => '',  beginTime => '20090508.041011'}, # 	2009-05-08	04:10:11	2009-05-08	05:06:57
'0495'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10128008',	 last => '10128008',	 list => '',  beginTime => '20090508.050657'}, # 	2009-05-08	05:06:57	2009-05-08	05:18:08
'0496'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10128010',	 last => '10128010',	 list => '',  beginTime => '20090508.051808'}, # 	2009-05-08	05:18:08	2009-05-08	05:26:32
'0497'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10128012',	 last => '10128012',	 list => '',  beginTime => '20090508.052632'}, # 	2009-05-08	05:26:32	2009-05-08	06:13:55
'0498'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10128018',	 last => '10128021',	 list => '',  beginTime => '20090508.061355'}, # 	2009-05-08	06:13:55	2009-05-08	07:57:02
'0499'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10128026',	 last => '10128027',	 list => '',  beginTime => '20090508.075702'}, # 	2009-05-08	07:57:02	2009-05-08	08:22:59
'0500'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10128029',	 last => '10128032',	 list => '',  beginTime => '20090508.082259'}, # 	2009-05-08	08:22:59	2009-05-08	09:53:26
'0501'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10128036',	 last => '10128036',	 list => '',  beginTime => '20090508.095326'}, # 	2009-05-08	09:53:26	2009-05-08	12:09:05
'0502'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10128041',	 last => '10128041',	 list => '',  beginTime => '20090508.120905'}, # 	2009-05-08	12:09:05	2009-05-08	12:34:22
'0503'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10128043',	 last => '10128043',	 list => '',  beginTime => '20090508.123422'}, # 	2009-05-08	12:34:22	2009-05-08	13:03:57
'0504'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10128046',	 last => '10128050',	 list => '',  beginTime => '20090508.130357'}, # 	2009-05-08	13:03:57	2009-05-08	14:42:46
'0505'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10128052',	 last => '10128056',	 list => '',  beginTime => '20090508.144246'}, # 	2009-05-08	14:42:46	2009-05-08	16:23:20
'0506'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10128059',	 last => '10128061',	 list => '',  beginTime => '20090508.162320'}, # 	2009-05-08	16:23:20	2009-05-08	17:43:11
'0507'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10128063',	 last => '10128063',	 list => '',  beginTime => '20090508.174311'}, # 	2009-05-08	17:43:11	2009-05-08	18:20:23
'0508'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10128065',	 last => '10128066',	 list => '',  beginTime => '20090508.182023'}, # 	2009-05-08	18:20:23	2009-05-08	19:40:10
'0509'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10128070',	 last => '10128072',	 list => '',  beginTime => '20090508.194010'}, # 	2009-05-08	19:40:10	2009-05-08	23:14:49
'0510'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10128089',	 last => '10128089',	 list => '',  beginTime => '20090508.231449'}, # 	2009-05-08	23:14:49	2009-05-09	00:14:44
'0511'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10128094',	 last => '10128094',	 list => '',  beginTime => '20090509.001444'}, # 	2009-05-09	00:14:44	2009-05-09	01:17:02
'0512'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10128098',	 last => '10128102',	 list => '',  beginTime => '20090509.011702'}, # 	2009-05-09	01:17:02	2009-05-09	04:26:08
'0513'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10129003',	 last => '10129003',	 list => '',  beginTime => '20090509.042608'}, # 	2009-05-09	04:26:08	2009-05-09	05:08:41
'0514'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10129005',	 last => '10129008',	 list => '',  beginTime => '20090509.050841'}, # 	2009-05-09	05:08:41	2009-05-09	07:18:19
'0515'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10129011',	 last => '10129011',	 list => '',  beginTime => '20090509.071819'}, # 	2009-05-09	07:18:19	2009-05-09	16:41:39
'0516'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10129029',	 last => '10129030',	 list => '',  beginTime => '20090509.164139'}, # 	2009-05-09	16:41:39	2009-05-10	00:44:16
'0517'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10129043',	 last => '10129043',	 list => '',  beginTime => '20090510.004416'}, # 	2009-05-10	00:44:16	2009-05-10	01:03:04
'0518'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10129047',	 last => '10129050',	 list => '',  beginTime => '20090510.010304'}, # 	2009-05-10	01:03:04	2009-05-10	06:28:12
'0519'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10130001',	 last => '10130001',	 list => '',  beginTime => '20090510.062812'}, # 	2009-05-10	06:28:12	2009-05-10	08:53:12
'0520'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10130004',	 last => '10130004',	 list => '',  beginTime => '20090510.085312'}, # 	2009-05-10	08:53:12	2009-05-10	09:48:31
'0521'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10130011',	 last => '10130012',	 list => '',  beginTime => '20090510.094831'}, # 	2009-05-10	09:48:31	2009-05-10	10:54:47
'0522'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10130014',	 last => '10130015',	 list => '',  beginTime => '20090510.105447'}, # 	2009-05-10	10:54:47	2009-05-11	08:00:58
'0523'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10131003',	 last => '10131003',	 list => '',  beginTime => '20090511.080058'}, # 	2009-05-11	08:00:58	2009-05-11	08:17:57
'0524'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10131006',	 last => '10131006',	 list => '',  beginTime => '20090511.081757'}, # 	2009-05-11	08:17:57	2009-05-11	08:28:07
'0525'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10131009',	 last => '10131009',	 list => '',  beginTime => '20090511.082807'}, # 	2009-05-11	08:28:07	2009-05-11	08:52:57
'0526'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10131011',	 last => '10131013',	 list => '',  beginTime => '20090511.085257'}, # 	2009-05-11	08:52:57	2009-05-11	13:45:04
'0527'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10131023',	 last => '10131024',	 list => '',  beginTime => '20090511.134504'}, # 	2009-05-11	13:45:04	2009-05-11	14:49:59
'0528'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10131029',	 last => '10131031',	 list => '',  beginTime => '20090511.144959'}, # 	2009-05-11	14:49:59	2009-05-11	15:52:42
'0529'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10131034',	 last => '10131034',	 list => '',  beginTime => '20090511.155242'}, # 	2009-05-11	15:52:42	2009-05-11	16:24:56
'0530'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10131039',	 last => '10131041',	 list => '',  beginTime => '20090511.162456'}, # 	2009-05-11	16:24:56	2009-05-11	17:43:17
'0531'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10131043',	 last => '10131045',	 list => '',  beginTime => '20090511.174317'}, # 	2009-05-11	17:43:17	2009-05-11	18:09:17
'0532'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10131047',	 last => '10131047',	 list => '',  beginTime => '20090511.180917'}, # 	2009-05-11	18:09:17	2009-05-11	18:55:46
'0533'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10131052',	 last => '10131052',	 list => '',  beginTime => '20090511.185546'}, # 	2009-05-11	18:55:46	2009-05-11	21:17:46
'0534'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10131075',	 last => '10131076',	 list => '',  beginTime => '20090511.211746'}, # 	2009-05-11	21:17:46	2009-05-12	00:30:57
'0535'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10131083',	 last => '10131083',	 list => '',  beginTime => '20090512.003057'}, # 	2009-05-12	00:30:57	2009-05-12	01:13:23
'0536'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10131087',	 last => '10131088',	 list => '',  beginTime => '20090512.011323'}, # 	2009-05-12	01:13:23	2009-05-12	02:14:07
'0537'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10131090',	 last => '10131092',	 list => '',  beginTime => '20090512.021407'}, # 	2009-05-12	02:14:07	2009-05-12	03:39:24
'0538'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10131094',	 last => '10131094',	 list => '',  beginTime => '20090512.033924'}, # 	2009-05-12	03:39:24	2009-05-12	04:17:48
'0539'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10132001',	 last => '10132001',	 list => '',  beginTime => '20090512.041748'}, # 	2009-05-12	04:17:48	2009-05-12	05:06:08
'0540'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10132003',	 last => '10132004',	 list => '',  beginTime => '20090512.050608'}, # 	2009-05-12	05:06:08	2009-05-12	06:42:36
'0541'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10132008',	 last => '10132012',	 list => '',  beginTime => '20090512.064236'}, # 	2009-05-12	06:42:36	2009-05-14	10:38:11
'0542'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10134017',	 last => '10134017',	 list => '',  beginTime => '20090514.103811'}, # 	2009-05-14	10:38:11	2009-05-14	10:56:06
'0543'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10134021',	 last => '10134021',	 list => '',  beginTime => '20090514.105606'}, # 	2009-05-14	10:56:06	2009-05-14	11:21:14
'0544'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10134024',	 last => '10134028',	 list => '',  beginTime => '20090514.112114'}, # 	2009-05-14	11:21:14	2009-05-14	13:54:09
'0545'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10134030',	 last => '10134030',	 list => '',  beginTime => '20090514.135409'}, # 	2009-05-14	13:54:09	2009-05-14	14:37:11
'0546'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10134035',	 last => '10134037',	 list => '',  beginTime => '20090514.143711'}, # 	2009-05-14	14:37:11	2009-05-14	17:29:00
'0547'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10134044',	 last => '10134044',	 list => '',  beginTime => '20090514.172900'}, # 	2009-05-14	17:29:00	2009-05-15	00:19:06
'0548'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10134080',	 last => '10134080',	 list => '',  beginTime => '20090515.001906'}, # 	2009-05-15	00:19:06	2009-05-15	01:37:30
'0549'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10134086',	 last => '10134086',	 list => '',  beginTime => '20090515.013730'}, # 	2009-05-15	01:37:30	2009-05-15	02:58:06
'0550'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10134101',	 last => '10134103',	 list => '',  beginTime => '20090515.025806'}, # 	2009-05-15	02:58:06	2009-05-15	04:22:57
'0551'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10135001',	 last => '10135002',	 list => '',  beginTime => '20090515.042257'}, # 	2009-05-15	04:22:57	2009-05-15	05:22:56
'0552'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10135005',	 last => '10135009',	 list => '',  beginTime => '20090515.052256'}, # 	2009-05-15	05:22:56	2009-05-15	07:32:34
'0553'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10135011',	 last => '10135011',	 list => '',  beginTime => '20090515.073234'}, # 	2009-05-15	07:32:34	2009-05-15	08:19:26
'0554'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10135016',	 last => '10135018',	 list => '',  beginTime => '20090515.081926'}, # 	2009-05-15	08:19:26	2009-05-15	12:39:59
'0555'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10135029',	 last => '10135030',	 list => '',  beginTime => '20090515.123959'}, # 	2009-05-15	12:39:59	2009-05-15	20:06:48
'0556'=> {trig=>'tof2009_single',        	field => 'RF',	first=> '10135055',	 last => '10135055',	 list => '',  beginTime => '20090515.200648'}, # 	2009-05-15	20:06:48	2009-05-15	20:23:58	timestamp = tof2009_single_RF
'0557'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10135058',	 last => '10135059',	 list => '',  beginTime => '20090515.202358'}, # 	2009-05-15	20:23:58	2009-05-15	21:20:28	timestamp = production2009_200Gev_Single_RF
'0558'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10135063',	 last => '10135066',	 list => '',  beginTime => '20090515.212028'}, # 	2009-05-15	21:20:28	2009-05-15	23:13:02
'0559'=> {trig=>'tof2009_single',        	field => 'RF',	first=> '10135069',	 last => '10135069',	 list => '',  beginTime => '20090515.231302'}, # 	2009-05-15	23:13:02	2009-05-15	23:28:45	timestamp = tof2009_single_RF
'0560'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10135070',	 last => '10135070',	 list => '',  beginTime => '20090515.232845'}, # 	2009-05-15	23:28:45	2009-05-16	00:12:48	timestamp = production2009_200Gev_Single_RF
'0561'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10135072',	 last => '10135072',	 list => '',  beginTime => '20090516.001248'}, # 	2009-05-16	00:12:48	2009-05-16	01:02:26
'0562'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10135076',	 last => '10135077',	 list => '',  beginTime => '20090516.010226'}, # 	2009-05-16	01:02:26	2009-05-16	02:14:15
'0563'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10135081',	 last => '10135083',	 list => '',  beginTime => '20090516.021415'}, # 	2009-05-16	02:14:15	2009-05-16	04:24:23
'0564'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10136001',	 last => '10136001',	 list => '',  beginTime => '20090516.042423'}, # 	2009-05-16	04:24:23	2009-05-16	06:24:12
'0565'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10136011',	 last => '10136012',	 list => '',  beginTime => '20090516.062412'}, # 	2009-05-16	06:24:12	2009-05-16	07:38:50
'0566'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10136017',	 last => '10136017',	 list => '',  beginTime => '20090516.073850'}, # 	2009-05-16	07:38:50	2009-05-16	08:14:01
'0567'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10136019',	 last => '10136021',	 list => '',  beginTime => '20090516.081401'}, # 	2009-05-16	08:14:01	2009-05-16	09:17:38
'0568'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10136024',	 last => '10136031',	 list => '',  beginTime => '20090516.091738'}, # 	2009-05-16	09:17:38	2009-05-16	12:28:03
'0569'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10136035',	 last => '10136038',	 list => '',  beginTime => '20090516.122803'}, # 	2009-05-16	12:28:03	2009-05-16	14:07:07
'0570'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10136041',	 last => '10136042',	 list => '',  beginTime => '20090516.140707'}, # 	2009-05-16	14:07:07	2009-05-16	17:25:48
'0571'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10136061',	 last => '10136061',	 list => '',  beginTime => '20090516.172548'}, # 	2009-05-16	17:25:48	2009-05-16	17:34:42
'0572'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10136063',	 last => '10136063',	 list => '',  beginTime => '20090516.173442'}, # 	2009-05-16	17:34:42	2009-05-16	18:02:07
'0573'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10136069',	 last => '10136071',	 list => '',  beginTime => '20090516.180207'}, # 	2009-05-16	18:02:07	2009-05-16	19:15:33
'0574'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10136073',	 last => '10136074',	 list => '',  beginTime => '20090516.191533'}, # 	2009-05-16	19:15:33	2009-05-16	20:10:29
'0575'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10136077',	 last => '10136080',	 list => '',  beginTime => '20090516.201029'}, # 	2009-05-16	20:10:29	2009-05-17	01:12:09
'0576'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10136092',	 last => '10136092',	 list => '',  beginTime => '20090517.011209'}, # 	2009-05-17	01:12:09	2009-05-17	02:03:25
'0577'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10136096',	 last => '10136097',	 list => '',  beginTime => '20090517.020325'}, # 	2009-05-17	02:03:25	2009-05-17	03:15:51
'0578'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10136099',	 last => '10136100',	 list => '',  beginTime => '20090517.031551'}, # 	2009-05-17	03:15:51	2009-05-17	04:19:40
'0579'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10137002',	 last => '10137004',	 list => '',  beginTime => '20090517.041940'}, # 	2009-05-17	04:19:40	2009-05-17	04:58:32
'0580'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10137006',	 last => '10137006',	 list => '',  beginTime => '20090517.045832'}, # 	2009-05-17	04:58:32	2009-05-17	05:35:02
'0581'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10137008',	 last => '10137008',	 list => '',  beginTime => '20090517.053502'}, # 	2009-05-17	05:35:02	2009-05-17	19:33:58
'0582'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10137045',	 last => '10137049',	 list => '',  beginTime => '20090517.193358'}, # 	2009-05-17	19:33:58	2009-05-17	21:01:21
'0583'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10137051',	 last => '10137052',	 list => '',  beginTime => '20090517.210121'}, # 	2009-05-17	21:01:21	2009-05-17	22:00:47
'0584'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10137055',	 last => '10137055',	 list => '',  beginTime => '20090517.220047'}, # 	2009-05-17	22:00:47	2009-05-17	22:48:46
'0585'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10137059',	 last => '10137061',	 list => '',  beginTime => '20090517.224846'}, # 	2009-05-17	22:48:46	2009-05-18	01:04:09
'0586'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10137063',	 last => '10137067',	 list => '',  beginTime => '20090518.010409'}, # 	2009-05-18	01:04:09	2009-05-18	05:46:53
'0587'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10138008',	 last => '10138008',	 list => '',  beginTime => '20090518.054653'}, # 	2009-05-18	05:46:53	2009-05-18	06:28:10
'0588'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10138011',	 last => '10138014',	 list => '',  beginTime => '20090518.062810'}, # 	2009-05-18	06:28:10	2009-05-18	07:54:53
'0589'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10138016',	 last => '10138016',	 list => '',  beginTime => '20090518.075453'}, # 	2009-05-18	07:54:53	2009-05-18	08:31:21
'0590'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10138021',	 last => '10138027',	 list => '',  beginTime => '20090518.083121'}, # 	2009-05-18	08:31:21	2009-05-18	11:34:56
'0591'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10138030',	 last => '10138030',	 list => '',  beginTime => '20090518.113456'}, # 	2009-05-18	11:34:56	2009-05-18	11:59:59
'0592'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10138032',	 last => '10138032',	 list => '',  beginTime => '20090518.115959'}, # 	2009-05-18	11:59:59	2009-05-18	18:13:52
'0593'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10138047',	 last => '10138049',	 list => '',  beginTime => '20090518.181352'}, # 	2009-05-18	18:13:52	2009-05-18	19:22:42
'0594'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10138052',	 last => '10138054',	 list => '',  beginTime => '20090518.192242'}, # 	2009-05-18	19:22:42	2009-05-18	20:13:12
'0595'=> {trig=>'production2009_200Gev_Single',	field => 'RHF',	first=> '10138055',	 last => '10138055',	 list => '',  beginTime => '20090518.201312'}, # 	2009-05-18	20:13:12	2009-05-18	20:13:12	timestamp = production2009_200Gev_Single_RHF
'0596'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10138055',	 last => '10138055',	 list => '',  beginTime => '20090518.201312'}, # 	2009-05-18	20:13:12	2009-05-19	03:22:51	timestamp = production2009_200Gev_Single_RF
'0597'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10138098',	 last => '10138100',	 list => '',  beginTime => '20090519.032251'}, # 	2009-05-19	03:22:51	2009-05-19	04:06:34
'0598'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10139001',	 last => '10139003',	 list => '',  beginTime => '20090519.040634'}, # 	2009-05-19	04:06:34	2009-05-19	04:58:04
'0599'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10139007',	 last => '10139010',	 list => '',  beginTime => '20090519.045804'}, # 	2009-05-19	04:58:04	2009-05-19	08:01:37
'0600'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10139014',	 last => '10139015',	 list => '',  beginTime => '20090519.080137'}, # 	2009-05-19	08:01:37	2009-05-19	09:08:33
'0601'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10139017',	 last => '10139018',	 list => '',  beginTime => '20090519.090833'}, # 	2009-05-19	09:08:33	2009-05-19	12:53:57
'0602'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10139031',	 last => '10139031',	 list => '',  beginTime => '20090519.125357'}, # 	2009-05-19	12:53:57	2009-05-19	13:36:05
'0603'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10139038',	 last => '10139038',	 list => '',  beginTime => '20090519.133605'}, # 	2009-05-19	13:36:05	2009-05-19	14:33:44
'0604'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10139040',	 last => '10139040',	 list => '',  beginTime => '20090519.143344'}, # 	2009-05-19	14:33:44	2009-05-19	15:23:40
'0605'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10139043',	 last => '10139044',	 list => '',  beginTime => '20090519.152340'}, # 	2009-05-19	15:23:40	2009-05-19	16:19:22
'0606'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10139054',	 last => '10139055',	 list => '',  beginTime => '20090519.161922'}, # 	2009-05-19	16:19:22	2009-05-19	16:55:45
'0607'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10139067',	 last => '10139070',	 list => '',  beginTime => '20090519.165545'}, # 	2009-05-19	16:55:45	2009-05-19	18:24:55
'0608'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10139073',	 last => '10139074',	 list => '',  beginTime => '20090519.182455'}, # 	2009-05-19	18:24:55	2009-05-19	19:25:16
'0609'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10139076',	 last => '10139078',	 list => '',  beginTime => '20090519.192516'}, # 	2009-05-19	19:25:16	2009-05-20	02:46:34
'0610'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10139102',	 last => '10139102',	 list => '',  beginTime => '20090520.024634'}, # 	2009-05-20	02:46:34	2009-05-20	04:00:46
'0611'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10139107',	 last => '10139107',	 list => '',  beginTime => '20090520.040046'}, # 	2009-05-20	04:00:46	2009-05-20	04:19:54
'0612'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10140001',	 last => '10140002',	 list => '',  beginTime => '20090520.041954'}, # 	2009-05-20	04:19:54	2009-05-20	05:31:38
'0613'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10140005',	 last => '10140007',	 list => '',  beginTime => '20090520.053138'}, # 	2009-05-20	05:31:38	2009-05-20	08:39:29
'0614'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10140010',	 last => '10140011',	 list => '',  beginTime => '20090520.083929'}, # 	2009-05-20	08:39:29	2009-05-21	08:04:33
'0615'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10141008',	 last => '10141008',	 list => '',  beginTime => '20090521.080433'}, # 	2009-05-21	08:04:33	2009-05-21	08:11:50
'0616'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10141010',	 last => '10141011',	 list => '',  beginTime => '20090521.081150'}, # 	2009-05-21	08:11:50	2009-05-21	08:21:10
'0617'=> {trig=>'production2009_200Gev_nocal',	field => 'RF',	first=> '10141012',	 last => '10141012',	 list => '',  beginTime => '20090521.082110'}, # 	2009-05-21	08:21:10	2009-05-21	08:27:32	timestamp = production2009_200Gev_nocal_RF
'0618'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10141013',	 last => '10141013',	 list => '',  beginTime => '20090521.082732'}, # 	2009-05-21	08:27:32	2009-05-21	08:38:48	timestamp = production2009_200Gev_Single_RF
'0619'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10141015',	 last => '10141015',	 list => '',  beginTime => '20090521.083848'}, # 	2009-05-21	08:38:48	2009-05-21	08:40:56
'0620'=> {trig=>'production2009_200Gev_nocal',	field => 'RF',	first=> '10141016',	 last => '10141017',	 list => '',  beginTime => '20090521.084056'}, # 	2009-05-21	08:40:56	2009-05-21	08:59:32	timestamp = production2009_200Gev_nocal_RF
'0621'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10141018',	 last => '10141020',	 list => '',  beginTime => '20090521.085932'}, # 	2009-05-21	08:59:32	2009-05-21	10:50:03	timestamp = production2009_200Gev_Single_RF
'0622'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10141023',	 last => '10141023',	 list => '',  beginTime => '20090521.105003'}, # 	2009-05-21	10:50:03	2009-05-21	11:44:02
'0623'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10141025',	 last => '10141027',	 list => '',  beginTime => '20090521.114402'}, # 	2009-05-21	11:44:02	2009-05-21	13:36:04
'0624'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10141030',	 last => '10141032',	 list => '',  beginTime => '20090521.133604'}, # 	2009-05-21	13:36:04	2009-05-21	19:32:52
'0625'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10141049',	 last => '10141049',	 list => '',  beginTime => '20090521.193252'}, # 	2009-05-21	19:32:52	2009-05-22	08:51:14
'0626'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10142011',	 last => '10142012',	 list => '',  beginTime => '20090522.085114'}, # 	2009-05-22	08:51:14	2009-05-22	09:00:48
'0627'=> {trig=>'production2009_200Gev_nocal',	field => 'RF',	first=> '10142014',	 last => '10142014',	 list => '',  beginTime => '20090522.090048'}, # 	2009-05-22	09:00:48	2009-05-22	09:12:39	timestamp = production2009_200Gev_nocal_RF
'0628'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10142019',	 last => '10142020',	 list => '',  beginTime => '20090522.091239'}, # 	2009-05-22	09:12:39	2009-05-22	09:17:31	timestamp = production2009_200Gev_Single_RF
'0629'=> {trig=>'production2009_200Gev_nocal',	field => 'RF',	first=> '10142021',	 last => '10142021',	 list => '',  beginTime => '20090522.091731'}, # 	2009-05-22	09:17:31	2009-05-22	09:34:03	timestamp = production2009_200Gev_nocal_RF
'0630'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10142023',	 last => '10142023',	 list => '',  beginTime => '20090522.093403'}, # 	2009-05-22	09:34:03	2009-05-22	09:36:42	timestamp = production2009_200Gev_Single_RF
'0631'=> {trig=>'production2009_200Gev_nocal',	field => 'RF',	first=> '10142024',	 last => '10142025',	 list => '',  beginTime => '20090522.093642'}, # 	2009-05-22	09:36:42	2009-05-22	10:07:56	timestamp = production2009_200Gev_nocal_RF
'0632'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10142029',	 last => '10142029',	 list => '',  beginTime => '20090522.100756'}, # 	2009-05-22	10:07:56	2009-05-22	10:13:27	timestamp = production2009_200Gev_Single_RF
'0633'=> {trig=>'production2009_200Gev_nocal',	field => 'RF',	first=> '10142030',	 last => '10142030',	 list => '',  beginTime => '20090522.101327'}, # 	2009-05-22	10:13:27	2009-05-22	10:27:22	timestamp = production2009_200Gev_nocal_RF
'0634'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10142031',	 last => '10142032',	 list => '',  beginTime => '20090522.102722'}, # 	2009-05-22	10:27:22	2009-05-22	11:18:20	timestamp = production2009_200Gev_Single_RF
'0635'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10142034',	 last => '10142036',	 list => '',  beginTime => '20090522.111820'}, # 	2009-05-22	11:18:20	2009-05-22	13:00:50
'0636'=> {trig=>'tof2009_single',        	field => 'RF',	first=> '10142037',	 last => '10142037',	 list => '',  beginTime => '20090522.130050'}, # 	2009-05-22	13:00:50	2009-05-22	13:16:20	timestamp = tof2009_single_RF
'0637'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10142041',	 last => '10142047',	 list => '',  beginTime => '20090522.131620'}, # 	2009-05-22	13:16:20	2009-05-22	15:14:37	timestamp = production2009_200Gev_Single_RF
'0638'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10142050',	 last => '10142050',	 list => '',  beginTime => '20090522.151437'}, # 	2009-05-22	15:14:37	2009-05-22	15:58:11
'0639'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10142056',	 last => '10142058',	 list => '',  beginTime => '20090522.155811'}, # 	2009-05-22	15:58:11	2009-05-22	22:50:07
'0640'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10142085',	 last => '10142086',	 list => '',  beginTime => '20090522.225007'}, # 	2009-05-22	22:50:07	2009-05-22	23:31:24
'0641'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10142092',	 last => '10142093',	 list => '',  beginTime => '20090522.233124'}, # 	2009-05-22	23:31:24	2009-05-23	00:30:06
'0642'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10142098',	 last => '10142098',	 list => '',  beginTime => '20090523.003006'}, # 	2009-05-23	00:30:06	2009-05-23	04:31:17
'0643'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10143006',	 last => '10143009',	 list => '',  beginTime => '20090523.043117'}, # 	2009-05-23	04:31:17	2009-05-23	05:35:24
'0644'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10143014',	 last => '10143015',	 list => '',  beginTime => '20090523.053524'}, # 	2009-05-23	05:35:24	2009-05-23	07:07:54
'0645'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10143018',	 last => '10143018',	 list => '',  beginTime => '20090523.070754'}, # 	2009-05-23	07:07:54	2009-05-23	08:03:34
'0646'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10143023',	 last => '10143023',	 list => '',  beginTime => '20090523.080334'}, # 	2009-05-23	08:03:34	2009-05-23	08:23:37
'0647'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10143025',	 last => '10143027',	 list => '',  beginTime => '20090523.082337'}, # 	2009-05-23	08:23:37	2009-05-23	09:47:57
'0648'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10143029',	 last => '10143029',	 list => '',  beginTime => '20090523.094757'}, # 	2009-05-23	09:47:57	2009-05-23	12:24:58
'0649'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10143038',	 last => '10143038',	 list => '',  beginTime => '20090523.122458'}, # 	2009-05-23	12:24:58	2009-05-23	12:51:19
'0650'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10143043',	 last => '10143047',	 list => '',  beginTime => '20090523.125119'}, # 	2009-05-23	12:51:19	2009-05-23	14:04:29
'0651'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10143051',	 last => '10143055',	 list => '',  beginTime => '20090523.140429'}, # 	2009-05-23	14:04:29	2009-05-23	16:04:16
'0652'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10143058',	 last => '10143058',	 list => '',  beginTime => '20090523.160416'}, # 	2009-05-23	16:04:16	2009-05-23	16:38:21
'0653'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10143060',	 last => '10143065',	 list => '',  beginTime => '20090523.163821'}, # 	2009-05-23	16:38:21	2009-05-23	20:51:58
'0654'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10143076',	 last => '10143078',	 list => '',  beginTime => '20090523.205158'}, # 	2009-05-23	20:51:58	2009-05-23	22:10:53
'0655'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10143082',	 last => '10143083',	 list => '',  beginTime => '20090523.221053'}, # 	2009-05-23	22:10:53	2009-05-23	23:09:18
'0656'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10143085',	 last => '10143086',	 list => '',  beginTime => '20090523.230918'}, # 	2009-05-23	23:09:18	2009-05-24	00:04:09
'0657'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10143090',	 last => '10143092',	 list => '',  beginTime => '20090524.000409'}, # 	2009-05-24	00:04:09	2009-05-24	01:23:56
'0658'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10143095',	 last => '10143095',	 list => '',  beginTime => '20090524.012356'}, # 	2009-05-24	01:23:56	2009-05-24	01:59:35
'0659'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10143098',	 last => '10143099',	 list => '',  beginTime => '20090524.015935'}, # 	2009-05-24	01:59:35	2009-05-24	02:55:17
'0660'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10143102',	 last => '10143104',	 list => '',  beginTime => '20090524.025517'}, # 	2009-05-24	02:55:17	2009-05-24	03:50:24
'0661'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10143106',	 last => '10143106',	 list => '',  beginTime => '20090524.035024'}, # 	2009-05-24	03:50:24	2009-05-24	04:33:57
'0662'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10144001',	 last => '10144003',	 list => '',  beginTime => '20090524.043357'}, # 	2009-05-24	04:33:57	2009-05-24	07:40:33
'0663'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10144022',	 last => '10144022',	 list => '',  beginTime => '20090524.074033'}, # 	2009-05-24	07:40:33	2009-05-24	08:17:39
'0664'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10144026',	 last => '10144030',	 list => '',  beginTime => '20090524.081739'}, # 	2009-05-24	08:17:39	2009-05-24	10:24:28
'0665'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10144033',	 last => '10144038',	 list => '',  beginTime => '20090524.102428'}, # 	2009-05-24	10:24:28	2009-05-24	13:23:16
'0666'=> {trig=>'production2009_200Gev_nocal',	field => 'RF',	first=> '10144041',	 last => '10144043',	 list => '',  beginTime => '20090524.132316'}, # 	2009-05-24	13:23:16	2009-05-24	14:22:49	timestamp = production2009_200Gev_nocal_RF
'0667'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10144044',	 last => '10144047',	 list => '',  beginTime => '20090524.142249'}, # 	2009-05-24	14:22:49	2009-05-24	18:59:48	timestamp = production2009_200Gev_Single_RF
'0668'=> {trig=>'production2009_200Gev_nocal',	field => 'RF',	first=> '10144065',	 last => '10144065',	 list => '',  beginTime => '20090524.185948'}, # 	2009-05-24	18:59:48	2009-05-24	19:01:13	timestamp = production2009_200Gev_nocal_RF
'0669'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10144066',	 last => '10144067',	 list => '',  beginTime => '20090524.190113'}, # 	2009-05-24	19:01:13	2009-05-24	19:30:34	timestamp = production2009_200Gev_Single_RF
'0670'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10144072',	 last => '10144076',	 list => '',  beginTime => '20090524.193034'}, # 	2009-05-24	19:30:34	2009-05-24	21:42:04
'0671'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10144082',	 last => '10144087',	 list => '',  beginTime => '20090524.214204'}, # 	2009-05-24	21:42:04	2009-05-25	00:46:13
'0672'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10144090',	 last => '10144093',	 list => '',  beginTime => '20090525.004613'}, # 	2009-05-25	00:46:13	2009-05-25	03:12:13
'0673'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10144097',	 last => '10144099',	 list => '',  beginTime => '20090525.031213'}, # 	2009-05-25	03:12:13	2009-05-25	05:46:54
'0674'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10145011',	 last => '10145013',	 list => '',  beginTime => '20090525.054654'}, # 	2009-05-25	05:46:54	2009-05-25	07:09:45
'0675'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10145016',	 last => '10145018',	 list => '',  beginTime => '20090525.070945'}, # 	2009-05-25	07:09:45	2009-05-25	08:35:44
'0676'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10145027',	 last => '10145027',	 list => '',  beginTime => '20090525.083544'}, # 	2009-05-25	08:35:44	2009-05-25	08:50:37
'0677'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10145030',	 last => '10145030',	 list => '',  beginTime => '20090525.085037'}, # 	2009-05-25	08:50:37	2009-05-25	09:23:27
'0678'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10145032',	 last => '10145032',	 list => '',  beginTime => '20090525.092327'}, # 	2009-05-25	09:23:27	2009-05-25	10:02:38
'0679'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10145034',	 last => '10145034',	 list => '',  beginTime => '20090525.100238'}, # 	2009-05-25	10:02:38	2009-05-25	10:53:49
'0680'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10145036',	 last => '10145036',	 list => '',  beginTime => '20090525.105349'}, # 	2009-05-25	10:53:49	2009-05-25	11:24:48
'0681'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10145038',	 last => '10145038',	 list => '',  beginTime => '20090525.112448'}, # 	2009-05-25	11:24:48	2009-05-25	12:02:16
'0682'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10145042',	 last => '10145042',	 list => '',  beginTime => '20090525.120216'}, # 	2009-05-25	12:02:16	2009-05-25	13:01:16
'0683'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10145046',	 last => '10145047',	 list => '',  beginTime => '20090525.130116'}, # 	2009-05-25	13:01:16	2009-05-25	13:48:20
'0684'=> {trig=>'production2009_200Gev_nocal',	field => 'RF',	first=> '10145048',	 last => '10145048',	 list => '',  beginTime => '20090525.134820'}, # 	2009-05-25	13:48:20	2009-05-26	00:47:49	timestamp = production2009_200Gev_nocal_RF
'0685'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10145073',	 last => '10145073',	 list => '',  beginTime => '20090526.004749'}, # 	2009-05-26	00:47:49	2009-05-26	01:10:48	timestamp = production2009_200Gev_Single_RF
'0686'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10145076',	 last => '10145079',	 list => '',  beginTime => '20090526.011048'}, # 	2009-05-26	01:10:48	2009-05-26	02:38:31
'0687'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10145081',	 last => '10145083',	 list => '',  beginTime => '20090526.023831'}, # 	2009-05-26	02:38:31	2009-05-26	07:12:25
'0688'=> {trig=>'production2009_200Gev_nocal',	field => 'RF',	first=> '10146023',	 last => '10146023',	 list => '',  beginTime => '20090526.071225'}, # 	2009-05-26	07:12:25	2009-05-26	08:18:23	timestamp = production2009_200Gev_nocal_RF
'0689'=> {trig=>'production2009_200Gev_nocal',	field => 'RF',	first=> '10146032',	 last => '10146032',	 list => '',  beginTime => '20090526.081823'}, # 	2009-05-26	08:18:23	2009-05-26	09:10:15
'0690'=> {trig=>'production2009_200Gev_nocal',	field => 'RF',	first=> '10146035',	 last => '10146037',	 list => '',  beginTime => '20090526.091015'}, # 	2009-05-26	09:10:15	2009-05-26	10:58:33
'0691'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10146040',	 last => '10146041',	 list => '',  beginTime => '20090526.105833'}, # 	2009-05-26	10:58:33	2009-05-26	11:15:42	timestamp = production2009_200Gev_Single_RF
'0692'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10146043',	 last => '10146043',	 list => '',  beginTime => '20090526.111542'}, # 	2009-05-26	11:15:42	2009-05-26	11:58:47
'0693'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10146046',	 last => '10146052',	 list => '',  beginTime => '20090526.115847'}, # 	2009-05-26	11:58:47	2009-05-26	14:16:38
'0694'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10146054',	 last => '10146055',	 list => '',  beginTime => '20090526.141638'}, # 	2009-05-26	14:16:38	2009-05-26	17:54:30
'0695'=> {trig=>'production2009_200Gev_nocal',	field => 'RF',	first=> '10146071',	 last => '10146071',	 list => '',  beginTime => '20090526.175430'}, # 	2009-05-26	17:54:30	2009-05-26	18:07:32	timestamp = production2009_200Gev_nocal_RF
'0696'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10146073',	 last => '10146073',	 list => '',  beginTime => '20090526.180732'}, # 	2009-05-26	18:07:32	2009-05-26	19:31:10	timestamp = production2009_200Gev_Single_RF
'0697'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10146084',	 last => '10146084',	 list => '',  beginTime => '20090526.193110'}, # 	2009-05-26	19:31:10	2009-05-26	20:11:59
'0698'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10146086',	 last => '10146087',	 list => '',  beginTime => '20090526.201159'}, # 	2009-05-26	20:11:59	2009-05-26	21:55:00
'0699'=> {trig=>'production2009_200Gev_Single',	field => 'RF',	first=> '10146091',	 last => '10146091',	 list => '',  beginTime => '20090526.215500'}, # 	2009-05-26	21:55:00	2009-05-28	03:30:17
'0700'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10147120',	 last => '10147120',	 list => '',  beginTime => '20090528.033017'}, # 	2009-05-28	03:30:17	2009-05-28	04:46:05	timestamp = production2009_200Gev_Single_FF
'0701'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10148005',	 last => '10148006',	 list => '',  beginTime => '20090528.044605'}, # 	2009-05-28	04:46:05	2009-05-28	07:09:31
'0702'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10148021',	 last => '10148021',	 list => '',  beginTime => '20090528.070931'}, # 	2009-05-28	07:09:31	2009-05-28	07:34:11
'0703'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10148025',	 last => '10148028',	 list => '',  beginTime => '20090528.073411'}, # 	2009-05-28	07:34:11	2009-05-28	09:51:29
'0704'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10148033',	 last => '10148036',	 list => '',  beginTime => '20090528.095129'}, # 	2009-05-28	09:51:29	2009-05-29	04:57:34
'0705'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10149006',	 last => '10149006',	 list => '',  beginTime => '20090529.045734'}, # 	2009-05-29	04:57:34	2009-05-29	05:07:51
'0706'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10149008',	 last => '10149008',	 list => '',  beginTime => '20090529.050751'}, # 	2009-05-29	05:07:51	2009-05-29	05:55:41
'0707'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10149012',	 last => '10149012',	 list => '',  beginTime => '20090529.055541'}, # 	2009-05-29	05:55:41	2009-05-29	06:32:12
'0708'=> {trig=>'production2009_200Gev_nocal',	field => 'FF',	first=> '10149016',	 last => '10149016',	 list => '',  beginTime => '20090529.063212'}, # 	2009-05-29	06:32:12	2009-05-29	06:41:51	timestamp = production2009_200Gev_nocal_FF
'0709'=> {trig=>'production2009_200Gev_nocal',	field => 'FF',	first=> '10149018',	 last => '10149018',	 list => '',  beginTime => '20090529.064151'}, # 	2009-05-29	06:41:51	2009-05-29	07:13:56
'0710'=> {trig=>'production2009_200Gev_nocal',	field => 'FF',	first=> '10149022',	 last => '10149022',	 list => '',  beginTime => '20090529.071356'}, # 	2009-05-29	07:13:56	2009-05-29	07:16:19
'0711'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10149023',	 last => '10149026',	 list => '',  beginTime => '20090529.071619'}, # 	2009-05-29	07:16:19	2009-05-29	09:10:22	timestamp = production2009_200Gev_Single_FF
'0712'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10149028',	 last => '10149028',	 list => '',  beginTime => '20090529.091022'}, # 	2009-05-29	09:10:22	2009-05-29	09:53:06
'0713'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10149031',	 last => '10149032',	 list => '',  beginTime => '20090529.095306'}, # 	2009-05-29	09:53:06	2009-05-30	03:16:30
'0714'=> {trig=>'production2009_200Gev_noendcap',	field => 'FF',	first=> '10149086',	 last => '10149086',	 list => '',  beginTime => '20090530.031630'}, # 	2009-05-30	03:16:30	2009-05-30	03:43:32	timestamp = production2009_200Gev_noendcap_FF
'0715'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10149087',	 last => '10149087',	 list => '',  beginTime => '20090530.034332'}, # 	2009-05-30	03:43:32	2009-05-30	04:11:52	timestamp = production2009_200Gev_Single_FF
'0716'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10150001',	 last => '10150001',	 list => '',  beginTime => '20090530.041152'}, # 	2009-05-30	04:11:52	2009-05-30	11:04:03
'0717'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10150010',	 last => '10150013',	 list => '',  beginTime => '20090530.110403'}, # 	2009-05-30	11:04:03	2009-05-30	13:33:46
'0718'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10150018',	 last => '10150018',	 list => '',  beginTime => '20090530.133346'}, # 	2009-05-30	13:33:46	2009-05-30	13:52:23
'0719'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10150021',	 last => '10150025',	 list => '',  beginTime => '20090530.135223'}, # 	2009-05-30	13:52:23	2009-05-31	02:19:15
'0720'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10150051',	 last => '10150053',	 list => '',  beginTime => '20090531.021915'}, # 	2009-05-31	02:19:15	2009-05-31	03:25:15
'0721'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10150056',	 last => '10150057',	 list => '',  beginTime => '20090531.032515'}, # 	2009-05-31	03:25:15	2009-05-31	04:22:22
'0722'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10151001',	 last => '10151002',	 list => '',  beginTime => '20090531.042222'}, # 	2009-05-31	04:22:22	2009-05-31	06:36:16
'0723'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10151005',	 last => '10151006',	 list => '',  beginTime => '20090531.063616'}, # 	2009-05-31	06:36:16	2009-05-31	20:02:08
'0724'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10151034',	 last => '10151035',	 list => '',  beginTime => '20090531.200208'}, # 	2009-05-31	20:02:08	2009-05-31	21:26:47
'0725'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10151039',	 last => '10151047',	 list => '',  beginTime => '20090531.212647'}, # 	2009-05-31	21:26:47	2009-06-01	01:09:07
'0726'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10151050',	 last => '10151050',	 list => '',  beginTime => '20090601.010907'}, # 	2009-06-01	01:09:07	2009-06-01	03:41:58
'0727'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10151057',	 last => '10151057',	 list => '',  beginTime => '20090601.034158'}, # 	2009-06-01	03:41:58	2009-06-01	03:51:32
'0728'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10151060',	 last => '10151060',	 list => '',  beginTime => '20090601.035132'}, # 	2009-06-01	03:51:32	2009-06-01	03:58:22
'0729'=> {trig=>'production2009_200Gev_noendcap',	field => 'FF',	first=> '10151061',	 last => '10151061',	 list => '',  beginTime => '20090601.035822'}, # 	2009-06-01	03:58:22	2009-06-01	04:26:51	timestamp = production2009_200Gev_noendcap_FF
'0730'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10152001',	 last => '10152001',	 list => '',  beginTime => '20090601.042651'}, # 	2009-06-01	04:26:51	2009-06-01	05:06:35	timestamp = production2009_200Gev_Single_FF
'0731'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10152004',	 last => '10152010',	 list => '',  beginTime => '20090601.050635'}, # 	2009-06-01	05:06:35	2009-06-03	20:38:58
'0732'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10154060',	 last => '10154061',	 list => '',  beginTime => '20090603.203858'}, # 	2009-06-03	20:38:58	2009-06-03	21:50:39
'0733'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10154064',	 last => '10154069',	 list => '',  beginTime => '20090603.215039'}, # 	2009-06-03	21:50:39	2009-06-04	03:48:32
'0734'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10154083',	 last => '10154083',	 list => '',  beginTime => '20090604.034832'}, # 	2009-06-04	03:48:32	2009-06-04	04:30:10
'0735'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10155001',	 last => '10155001',	 list => '',  beginTime => '20090604.043010'}, # 	2009-06-04	04:30:10	2009-06-04	05:33:07
'0736'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10155010',	 last => '10155010',	 list => '',  beginTime => '20090604.053307'}, # 	2009-06-04	05:33:07	2009-06-04	06:40:32
'0737'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10155014',	 last => '10155016',	 list => '',  beginTime => '20090604.064032'}, # 	2009-06-04	06:40:32	2009-06-04	09:28:10
'0738'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10155019',	 last => '10155020',	 list => '',  beginTime => '20090604.092810'}, # 	2009-06-04	09:28:10	2009-06-04	10:11:04
'0739'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10155022',	 last => '10155022',	 list => '',  beginTime => '20090604.101104'}, # 	2009-06-04	10:11:04	2009-06-05	03:28:00
'0740'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10155095',	 last => '10155095',	 list => '',  beginTime => '20090605.032800'}, # 	2009-06-05	03:28:00	2009-06-05	03:52:15
'0741'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10155097',	 last => '10155097',	 list => '',  beginTime => '20090605.035215'}, # 	2009-06-05	03:52:15	2009-06-05	04:23:20
'0742'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10156004',	 last => '10156004',	 list => '',  beginTime => '20090605.042320'}, # 	2009-06-05	04:23:20	2009-06-05	05:03:07
'0743'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10156007',	 last => '10156009',	 list => '',  beginTime => '20090605.050307'}, # 	2009-06-05	05:03:07	2009-06-05	07:01:13
'0744'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10156011',	 last => '10156011',	 list => '',  beginTime => '20090605.070113'}, # 	2009-06-05	07:01:13	2009-06-05	07:31:59
'0745'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10156013',	 last => '10156013',	 list => '',  beginTime => '20090605.073159'}, # 	2009-06-05	07:31:59	2009-06-05	11:56:47
'0746'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10156031',	 last => '10156031',	 list => '',  beginTime => '20090605.115647'}, # 	2009-06-05	11:56:47	2009-06-05	12:36:58
'0747'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10156034',	 last => '10156034',	 list => '',  beginTime => '20090605.123658'}, # 	2009-06-05	12:36:58	2009-06-05	13:17:18
'0748'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10156037',	 last => '10156040',	 list => '',  beginTime => '20090605.131718'}, # 	2009-06-05	13:17:18	2009-06-05	16:25:42
'0749'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10156058',	 last => '10156058',	 list => '',  beginTime => '20090605.162542'}, # 	2009-06-05	16:25:42	2009-06-06	00:04:34
'0750'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10156086',	 last => '10156087',	 list => '',  beginTime => '20090606.000434'}, # 	2009-06-06	00:04:34	2009-06-06	01:17:21
'0751'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10156090',	 last => '10156093',	 list => '',  beginTime => '20090606.011721'}, # 	2009-06-06	01:17:21	2009-06-06	03:06:28
'0752'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10156095',	 last => '10156096',	 list => '',  beginTime => '20090606.030628'}, # 	2009-06-06	03:06:28	2009-06-06	04:38:58
'0753'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10157001',	 last => '10157001',	 list => '',  beginTime => '20090606.043858'}, # 	2009-06-06	04:38:58	2009-06-06	05:33:23
'0754'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10157004',	 last => '10157005',	 list => '',  beginTime => '20090606.053323'}, # 	2009-06-06	05:33:23	2009-06-06	11:13:30
'0755'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10157021',	 last => '10157023',	 list => '',  beginTime => '20090606.111330'}, # 	2009-06-06	11:13:30	2009-06-06	13:31:08
'0756'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10157027',	 last => '10157027',	 list => '',  beginTime => '20090606.133108'}, # 	2009-06-06	13:31:08	2009-06-06	23:56:00
'0757'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10157051',	 last => '10157052',	 list => '',  beginTime => '20090606.235600'}, # 	2009-06-06	23:56:00	2009-06-07	00:58:42
'0758'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10157056',	 last => '10157059',	 list => '',  beginTime => '20090607.005842'}, # 	2009-06-07	00:58:42	2009-06-07	04:25:37
'0759'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10158001',	 last => '10158001',	 list => '',  beginTime => '20090607.042537'}, # 	2009-06-07	04:25:37	2009-06-07	05:22:53
'0760'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10158004',	 last => '10158004',	 list => '',  beginTime => '20090607.052253'}, # 	2009-06-07	05:22:53	2009-06-07	07:18:16
'0761'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10158010',	 last => '10158010',	 list => '',  beginTime => '20090607.071816'}, # 	2009-06-07	07:18:16	2009-06-07	07:57:23
'0762'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10158013',	 last => '10158018',	 list => '',  beginTime => '20090607.075723'}, # 	2009-06-07	07:57:23	2009-06-07	12:27:02
'0763'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10158021',	 last => '10158021',	 list => '',  beginTime => '20090607.122702'}, # 	2009-06-07	12:27:02	2009-06-07	15:16:40
'0764'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10158042',	 last => '10158043',	 list => '',  beginTime => '20090607.151640'}, # 	2009-06-07	15:16:40	2009-06-07	16:26:36
'0765'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10158046',	 last => '10158051',	 list => '',  beginTime => '20090607.162636'}, # 	2009-06-07	16:26:36	2009-06-07	20:06:51
'0766'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10158054',	 last => '10158055',	 list => '',  beginTime => '20090607.200651'}, # 	2009-06-07	20:06:51	2009-06-07	22:46:23
'0767'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10158074',	 last => '10158076',	 list => '',  beginTime => '20090607.224623'}, # 	2009-06-07	22:46:23	2009-06-08	00:31:09
'0768'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10158079',	 last => '10158080',	 list => '',  beginTime => '20090608.003109'}, # 	2009-06-08	00:31:09	2009-06-08	01:42:46
'0769'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10158082',	 last => '10158083',	 list => '',  beginTime => '20090608.014246'}, # 	2009-06-08	01:42:46	2009-06-08	03:03:28
'0770'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10158086',	 last => '10158087',	 list => '',  beginTime => '20090608.030328'}, # 	2009-06-08	03:03:28	2009-06-08	03:46:02
'0771'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10158089',	 last => '10158090',	 list => '',  beginTime => '20090608.034602'}, # 	2009-06-08	03:46:02	2009-06-08	07:41:00
'0772'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10159006',	 last => '10159006',	 list => '',  beginTime => '20090608.074100'}, # 	2009-06-08	07:41:00	2009-06-08	08:09:13
'0773'=> {trig=>'production2009_200Gev_noendcap',	field => 'FF',	first=> '10159008',	 last => '10159008',	 list => '',  beginTime => '20090608.080913'}, # 	2009-06-08	08:09:13	2009-06-08	09:13:35	timestamp = production2009_200Gev_noendcap_FF
'0774'=> {trig=>'production2009_200Gev_noendcap',	field => 'FF',	first=> '10159020',	 last => '10159020',	 list => '',  beginTime => '20090608.091335'}, # 	2009-06-08	09:13:35	2009-06-08	09:32:19
'0775'=> {trig=>'production2009_200Gev_noendcap',	field => 'FF',	first=> '10159022',	 last => '10159023',	 list => '',  beginTime => '20090608.093219'}, # 	2009-06-08	09:32:19	2009-06-08	14:32:32
'0776'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10159039',	 last => '10159040',	 list => '',  beginTime => '20090608.143232'}, # 	2009-06-08	14:32:32	2009-06-08	15:44:39	timestamp = production2009_200Gev_Single_FF
'0777'=> {trig=>'production2009_200Gev_noendcap',	field => 'FF',	first=> '10159043',	 last => '10159043',	 list => '',  beginTime => '20090608.154439'}, # 	2009-06-08	15:44:39	2009-06-08	16:24:28	timestamp = production2009_200Gev_noendcap_FF
'0778'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10159044',	 last => '10159046',	 list => '',  beginTime => '20090608.162428'}, # 	2009-06-08	16:24:28	2009-06-08	18:02:02	timestamp = production2009_200Gev_Single_FF
'0779'=> {trig=>'production2009_200Gev_noendcap',	field => 'FF',	first=> '10159047',	 last => '10159047',	 list => '',  beginTime => '20090608.180202'}, # 	2009-06-08	18:02:02	2009-06-08	18:15:49	timestamp = production2009_200Gev_noendcap_FF
'0780'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10159048',	 last => '10159049',	 list => '',  beginTime => '20090608.181549'}, # 	2009-06-08	18:15:49	2009-06-09	05:41:58	timestamp = production2009_200Gev_Single_FF
'0781'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10160005',	 last => '10160006',	 list => '',  beginTime => '20090609.054158'}, # 	2009-06-09	05:41:58	2009-06-09	06:37:41
'0782'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10160009',	 last => '10160017',	 list => '',  beginTime => '20090609.063741'}, # 	2009-06-09	06:37:41	2009-06-09	12:49:32
'0783'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10160024',	 last => '10160024',	 list => '',  beginTime => '20090609.124932'}, # 	2009-06-09	12:49:32	2009-06-09	21:16:53
'0784'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10160067',	 last => '10160072',	 list => '',  beginTime => '20090609.211653'}, # 	2009-06-09	21:16:53	2009-06-09	22:39:52
'0785'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10160075',	 last => '10160079',	 list => '',  beginTime => '20090609.223952'}, # 	2009-06-09	22:39:52	2009-06-10	01:38:34
'0786'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10160081',	 last => '10160081',	 list => '',  beginTime => '20090610.013834'}, # 	2009-06-10	01:38:34	2009-06-10	02:25:32
'0787'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10160084',	 last => '10160084',	 list => '',  beginTime => '20090610.022532'}, # 	2009-06-10	02:25:32	2009-06-10	04:22:25
'0788'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10161005',	 last => '10161006',	 list => '',  beginTime => '20090610.042225'}, # 	2009-06-10	04:22:25	2009-06-10	05:43:46
'0789'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10161010',	 last => '10161011',	 list => '',  beginTime => '20090610.054346'}, # 	2009-06-10	05:43:46	2009-06-10	06:49:36
'0790'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10161014',	 last => '10161016',	 list => '',  beginTime => '20090610.064936'}, # 	2009-06-10	06:49:36	2009-06-10	08:00:25
'0791'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10161019',	 last => '10161021',	 list => '',  beginTime => '20090610.080025'}, # 	2009-06-10	08:00:25	2009-06-10	10:52:56
'0792'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10161025',	 last => '10161027',	 list => '',  beginTime => '20090610.105256'}, # 	2009-06-10	10:52:56	2009-06-10	12:32:51
'0793'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10161030',	 last => '10161030',	 list => '',  beginTime => '20090610.123251'}, # 	2009-06-10	12:32:51	2009-06-11	09:04:07
'0794'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10162006',	 last => '10162007',	 list => '',  beginTime => '20090611.090407'}, # 	2009-06-11	09:04:07	2009-06-11	10:21:28
'0795'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10162010',	 last => '10162010',	 list => '',  beginTime => '20090611.102128'}, # 	2009-06-11	10:21:28	2009-06-11	15:52:28
'0796'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10162024',	 last => '10162025',	 list => '',  beginTime => '20090611.155228'}, # 	2009-06-11	15:52:28	2009-06-11	17:07:50
'0797'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10162028',	 last => '10162038',	 list => '',  beginTime => '20090611.170750'}, # 	2009-06-11	17:07:50	2009-06-11	19:22:58
'0798'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10162040',	 last => '10162040',	 list => '',  beginTime => '20090611.192258'}, # 	2009-06-11	19:22:58	2009-06-12	05:40:48
'0799'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10163007',	 last => '10163010',	 list => '',  beginTime => '20090612.054048'}, # 	2009-06-12	05:40:48	2009-06-12	22:52:34
'0800'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10163048',	 last => '10163048',	 list => '',  beginTime => '20090612.225234'}, # 	2009-06-12	22:52:34	2009-06-12	23:49:01
'0801'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10163051',	 last => '10163056',	 list => '',  beginTime => '20090612.234901'}, # 	2009-06-12	23:49:01	2009-06-13	03:59:34
'0802'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10163059',	 last => '10163059',	 list => '',  beginTime => '20090613.035934'}, # 	2009-06-13	03:59:34	2009-06-13	05:02:17
'0803'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10164002',	 last => '10164002',	 list => '',  beginTime => '20090613.050217'}, # 	2009-06-13	05:02:17	2009-06-13	07:19:16
'0804'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10164009',	 last => '10164011',	 list => '',  beginTime => '20090613.071916'}, # 	2009-06-13	07:19:16	2009-06-13	08:24:38
'0805'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10164013',	 last => '10164013',	 list => '',  beginTime => '20090613.082438'}, # 	2009-06-13	08:24:38	2009-06-13	09:06:15
'0806'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10164016',	 last => '10164018',	 list => '',  beginTime => '20090613.090615'}, # 	2009-06-13	09:06:15	2009-06-13	11:31:03
'0807'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10164025',	 last => '10164026',	 list => '',  beginTime => '20090613.113103'}, # 	2009-06-13	11:31:03	2009-06-13	12:32:42
'0808'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10164029',	 last => '10164031',	 list => '',  beginTime => '20090613.123242'}, # 	2009-06-13	12:32:42	2009-06-13	14:05:11
'0809'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10164034',	 last => '10164034',	 list => '',  beginTime => '20090613.140511'}, # 	2009-06-13	14:05:11	2009-06-13	22:34:08
'0810'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10164057',	 last => '10164057',	 list => '',  beginTime => '20090613.223408'}, # 	2009-06-13	22:34:08	2009-06-13	23:29:33
'0811'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10164060',	 last => '10164062',	 list => '',  beginTime => '20090613.232933'}, # 	2009-06-13	23:29:33	2009-06-14	01:36:55
'0812'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10164067',	 last => '10164067',	 list => '',  beginTime => '20090614.013655'}, # 	2009-06-14	01:36:55	2009-06-14	02:24:57
'0813'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10164078',	 last => '10164079',	 list => '',  beginTime => '20090614.022457'}, # 	2009-06-14	02:24:57	2009-06-14	03:35:15
'0814'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10164082',	 last => '10164082',	 list => '',  beginTime => '20090614.033515'}, # 	2009-06-14	03:35:15	2009-06-14	05:57:26
'0815'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10165007',	 last => '10165008',	 list => '',  beginTime => '20090614.055726'}, # 	2009-06-14	05:57:26	2009-06-14	07:23:32
'0816'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10165011',	 last => '10165011',	 list => '',  beginTime => '20090614.072332'}, # 	2009-06-14	07:23:32	2009-06-14	07:46:14
'0817'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10165013',	 last => '10165024',	 list => '',  beginTime => '20090614.074614'}, # 	2009-06-14	07:46:14	2009-06-14	12:53:05
'0818'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10165027',	 last => '10165027',	 list => '',  beginTime => '20090614.125305'}, # 	2009-06-14	12:53:05	2009-06-14	15:13:02
'0819'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10165040',	 last => '10165043',	 list => '',  beginTime => '20090614.151302'}, # 	2009-06-14	15:13:02	2009-06-14	16:02:23
'0820'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10165046',	 last => '10165054',	 list => '',  beginTime => '20090614.160223'}, # 	2009-06-14	16:02:23	2009-06-14	20:15:09
'0821'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10165057',	 last => '10165057',	 list => '',  beginTime => '20090614.201509'}, # 	2009-06-14	20:15:09	2009-06-14	23:38:17
'0822'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10165070',	 last => '10165070',	 list => '',  beginTime => '20090614.233817'}, # 	2009-06-14	23:38:17	2009-06-14	23:58:08
'0823'=> {trig=>'production2009_200Gev_noendcap',	field => 'FF',	first=> '10165072',	 last => '10165072',	 list => '',  beginTime => '20090614.235808'}, # 	2009-06-14	23:58:08	2009-06-15	00:11:25	timestamp = production2009_200Gev_noendcap_FF
'0824'=> {trig=>'production2009_200Gev_noendcap',	field => 'FF',	first=> '10165074',	 last => '10165074',	 list => '',  beginTime => '20090615.001125'}, # 	2009-06-15	00:11:25	2009-06-15	00:43:29
'0825'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10165077',	 last => '10165081',	 list => '',  beginTime => '20090615.004329'}, # 	2009-06-15	00:43:29	2009-06-15	04:11:46	timestamp = production2009_200Gev_Single_FF
'0826'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10166001',	 last => '10166001',	 list => '',  beginTime => '20090615.041146'}, # 	2009-06-15	04:11:46	2009-06-15	05:08:18
'0827'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10166003',	 last => '10166003',	 list => '',  beginTime => '20090615.050818'}, # 	2009-06-15	05:08:18	2009-06-15	10:08:01
'0828'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10166012',	 last => '10166012',	 list => '',  beginTime => '20090615.100801'}, # 	2009-06-15	10:08:01	2009-06-15	11:26:28
'0829'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10166021',	 last => '10166028',	 list => '',  beginTime => '20090615.112628'}, # 	2009-06-15	11:26:28	2009-06-16	00:08:07
'0830'=> {trig=>'production2009_200Gev_noendcap',	field => 'FF',	first=> '10166051',	 last => '10166051',	 list => '',  beginTime => '20090616.000807'}, # 	2009-06-16	00:08:07	2009-06-16	00:55:21	timestamp = production2009_200Gev_noendcap_FF
'0831'=> {trig=>'production2009_200Gev_noendcap',	field => 'FF',	first=> '10166054',	 last => '10166054',	 list => '',  beginTime => '20090616.005521'}, # 	2009-06-16	00:55:21	2009-06-16	01:32:26
'0832'=> {trig=>'production2009_200Gev_noendcap',	field => 'FF',	first=> '10166060',	 last => '10166060',	 list => '',  beginTime => '20090616.013226'}, # 	2009-06-16	01:32:26	2009-06-16	02:09:29
'0833'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10166061',	 last => '10166061',	 list => '',  beginTime => '20090616.020929'}, # 	2009-06-16	02:09:29	2009-06-16	02:28:28	timestamp = production2009_200Gev_Single_FF
'0834'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10166063',	 last => '10166063',	 list => '',  beginTime => '20090616.022828'}, # 	2009-06-16	02:28:28	2009-06-16	02:52:34
'0835'=> {trig=>'production2009_200Gev_noendcap',	field => 'FF',	first=> '10166064',	 last => '10166065',	 list => '',  beginTime => '20090616.025234'}, # 	2009-06-16	02:52:34	2009-06-16	03:32:04	timestamp = production2009_200Gev_noendcap_FF
'0836'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10166067',	 last => '10166067',	 list => '',  beginTime => '20090616.033204'}, # 	2009-06-16	03:32:04	2009-06-16	07:23:20	timestamp = production2009_200Gev_Single_FF
'0837'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10167007',	 last => '10167009',	 list => '',  beginTime => '20090616.072320'}, # 	2009-06-16	07:23:20	2009-06-16	08:50:51
'0838'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10167012',	 last => '10167017',	 list => '',  beginTime => '20090616.085051'}, # 	2009-06-16	08:50:51	2009-06-16	12:52:49
'0839'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10167020',	 last => '10167020',	 list => '',  beginTime => '20090616.125249'}, # 	2009-06-16	12:52:49	2009-06-16	16:19:52
'0840'=> {trig=>'production2009_200Gev_nocal',	field => 'FF',	first=> '10167047',	 last => '10167047',	 list => '',  beginTime => '20090616.161952'}, # 	2009-06-16	16:19:52	2009-06-16	16:23:52	timestamp = production2009_200Gev_nocal_FF
'0841'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10167048',	 last => '10167050',	 list => '',  beginTime => '20090616.162352'}, # 	2009-06-16	16:23:52	2009-06-16	18:41:39	timestamp = production2009_200Gev_Single_FF
'0842'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10167056',	 last => '10167059',	 list => '',  beginTime => '20090616.184139'}, # 	2009-06-16	18:41:39	2009-06-16	21:18:39
'0843'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10167067',	 last => '10167069',	 list => '',  beginTime => '20090616.211839'}, # 	2009-06-16	21:18:39	2009-06-18	04:58:20
'0844'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10169005',	 last => '10169006',	 list => '',  beginTime => '20090618.045820'}, # 	2009-06-18	04:58:20	2009-06-18	06:13:30
'0845'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10169009',	 last => '10169015',	 list => '',  beginTime => '20090618.061330'}, # 	2009-06-18	06:13:30	2009-06-18	10:19:57
'0846'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10169020',	 last => '10169021',	 list => '',  beginTime => '20090618.101957'}, # 	2009-06-18	10:19:57	2009-06-18	12:48:40
'0847'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10169030',	 last => '10169033',	 list => '',  beginTime => '20090618.124840'}, # 	2009-06-18	12:48:40	2009-06-18	15:24:53
'0848'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10169041',	 last => '10169044',	 list => '',  beginTime => '20090618.152453'}, # 	2009-06-18	15:24:53	2009-06-18	17:07:56
'0849'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10169047',	 last => '10169050',	 list => '',  beginTime => '20090618.170756'}, # 	2009-06-18	17:07:56	2009-06-18	23:26:18
'0850'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10169065',	 last => '10169065',	 list => '',  beginTime => '20090618.232618'}, # 	2009-06-18	23:26:18	2009-06-19	00:02:53
'0851'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10169070',	 last => '10169070',	 list => '',  beginTime => '20090619.000253'}, # 	2009-06-19	00:02:53	2009-06-19	00:40:04
'0852'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10169074',	 last => '10169078',	 list => '',  beginTime => '20090619.004004'}, # 	2009-06-19	00:40:04	2009-06-19	03:39:07
'0853'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10169080',	 last => '10169080',	 list => '',  beginTime => '20090619.033907'}, # 	2009-06-19	03:39:07	2009-06-19	04:26:16
'0854'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10170003',	 last => '10170003',	 list => '',  beginTime => '20090619.042616'}, # 	2009-06-19	04:26:16	2009-06-19	06:59:03
'0855'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10170011',	 last => '10170013',	 list => '',  beginTime => '20090619.065903'}, # 	2009-06-19	06:59:03	2009-06-19	08:27:27
'0856'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10170016',	 last => '10170020',	 list => '',  beginTime => '20090619.082727'}, # 	2009-06-19	08:27:27	2009-06-19	10:20:09
'0857'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10170023',	 last => '10170024',	 list => '',  beginTime => '20090619.102009'}, # 	2009-06-19	10:20:09	2009-06-19	11:27:56
'0858'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10170026',	 last => '10170026',	 list => '',  beginTime => '20090619.112756'}, # 	2009-06-19	11:27:56	2009-06-19	12:07:46
'0859'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10170029',	 last => '10170029',	 list => '',  beginTime => '20090619.120746'}, # 	2009-06-19	12:07:46	2009-06-19	14:33:53
'0860'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10170045',	 last => '10170047',	 list => '',  beginTime => '20090619.143353'}, # 	2009-06-19	14:33:53	2009-06-19	16:15:39
'0861'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10170050',	 last => '10170054',	 list => '',  beginTime => '20090619.161539'}, # 	2009-06-19	16:15:39	2009-06-19	19:09:16
'0862'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10170060',	 last => '10170061',	 list => '',  beginTime => '20090619.190916'}, # 	2009-06-19	19:09:16	2009-06-19	20:12:43
'0863'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10170064',	 last => '10170065',	 list => '',  beginTime => '20090619.201243'}, # 	2009-06-19	20:12:43	2009-06-19	22:52:22
'0864'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10170075',	 last => '10170075',	 list => '',  beginTime => '20090619.225222'}, # 	2009-06-19	22:52:22	2009-06-19	23:45:32
'0865'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10170078',	 last => '10170078',	 list => '',  beginTime => '20090619.234532'}, # 	2009-06-19	23:45:32	2009-06-20	00:03:00
'0866'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10170080',	 last => '10170081',	 list => '',  beginTime => '20090620.000300'}, # 	2009-06-20	00:03:00	2009-06-20	03:26:12
'0867'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10170089',	 last => '10170089',	 list => '',  beginTime => '20090620.032612'}, # 	2009-06-20	03:26:12	2009-06-20	09:06:58
'0868'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10171008',	 last => '10171009',	 list => '',  beginTime => '20090620.090658'}, # 	2009-06-20	09:06:58	2009-06-20	09:47:23
'0869'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10171011',	 last => '10171011',	 list => '',  beginTime => '20090620.094723'}, # 	2009-06-20	09:47:23	2009-06-20	10:23:37
'0870'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10171014',	 last => '10171017',	 list => '',  beginTime => '20090620.102337'}, # 	2009-06-20	10:23:37	2009-06-20	12:06:37
'0871'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10171019',	 last => '10171022',	 list => '',  beginTime => '20090620.120637'}, # 	2009-06-20	12:06:37	2009-06-20	13:27:56
'0872'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10171025',	 last => '10171026',	 list => '',  beginTime => '20090620.132756'}, # 	2009-06-20	13:27:56	2009-06-20	16:46:41
'0873'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10171034',	 last => '10171034',	 list => '',  beginTime => '20090620.164641'}, # 	2009-06-20	16:46:41	2009-06-20	16:54:58
'0874'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10171036',	 last => '10171037',	 list => '',  beginTime => '20090620.165458'}, # 	2009-06-20	16:54:58	2009-06-20	18:50:25
'0875'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10171041',	 last => '10171045',	 list => '',  beginTime => '20090620.185025'}, # 	2009-06-20	18:50:25	2009-06-20	21:33:47
'0876'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10171048',	 last => '10171048',	 list => '',  beginTime => '20090620.213347'}, # 	2009-06-20	21:33:47	2009-06-21	00:39:07
'0877'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10171060',	 last => '10171061',	 list => '',  beginTime => '20090621.003907'}, # 	2009-06-21	00:39:07	2009-06-21	01:51:55
'0878'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10171068',	 last => '10171071',	 list => '',  beginTime => '20090621.015155'}, # 	2009-06-21	01:51:55	2009-06-21	03:45:44
'0879'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10171078',	 last => '10171078',	 list => '',  beginTime => '20090621.034544'}, # 	2009-06-21	03:45:44	2009-06-21	04:26:26
'0880'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10172001',	 last => '10172003',	 list => '',  beginTime => '20090621.042626'}, # 	2009-06-21	04:26:26	2009-06-21	05:44:57
'0881'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10172007',	 last => '10172007',	 list => '',  beginTime => '20090621.054457'}, # 	2009-06-21	05:44:57	2009-06-21	08:30:53
'0882'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10172016',	 last => '10172018',	 list => '',  beginTime => '20090621.083053'}, # 	2009-06-21	08:30:53	2009-06-21	09:53:13
'0883'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10172021',	 last => '10172026',	 list => '',  beginTime => '20090621.095313'}, # 	2009-06-21	09:53:13	2009-06-21	11:36:24
'0884'=> {trig=>'production2009_200Gev_Single',	field => 'ZF',	first=> '10172026',	 last => '10172027',	 list => '',  beginTime => '20090621.113624'}, # 	2009-06-21	11:36:24	2009-06-21	12:05:24	timestamp = production2009_200Gev_Single_ZF
'0885'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10172027',	 last => '10172028',	 list => '',  beginTime => '20090621.120524'}, # 	2009-06-21	12:05:24	2009-06-21	18:13:13	timestamp = production2009_200Gev_Single_FF
'0886'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10172060',	 last => '10172061',	 list => '',  beginTime => '20090621.181313'}, # 	2009-06-21	18:13:13	2009-06-21	20:04:38
'0887'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10172064',	 last => '10172064',	 list => '',  beginTime => '20090621.200438'}, # 	2009-06-21	20:04:38	2009-06-21	22:33:24
'0888'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10172077',	 last => '10172079',	 list => '',  beginTime => '20090621.223324'}, # 	2009-06-21	22:33:24	2009-06-21	23:27:52
'0889'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10172082',	 last => '10172083',	 list => '',  beginTime => '20090621.232752'}, # 	2009-06-21	23:27:52	2009-06-22	01:08:35
'0890'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10172085',	 last => '10172086',	 list => '',  beginTime => '20090622.010835'}, # 	2009-06-22	01:08:35	2009-06-22	01:59:23
'0891'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10172089',	 last => '10172091',	 list => '',  beginTime => '20090622.015923'}, # 	2009-06-22	01:59:23	2009-06-22	03:28:54
'0892'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10172094',	 last => '10172094',	 list => '',  beginTime => '20090622.032854'}, # 	2009-06-22	03:28:54	2009-06-22	07:31:57
'0893'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10173007',	 last => '10173009',	 list => '',  beginTime => '20090622.073157'}, # 	2009-06-22	07:31:57	2009-06-22	09:09:19
'0894'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10173012',	 last => '10173017',	 list => '',  beginTime => '20090622.090919'}, # 	2009-06-22	09:09:19	2009-06-22	13:27:59
'0895'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10173031',	 last => '10173033',	 list => '',  beginTime => '20090622.132759'}, # 	2009-06-22	13:27:59	2009-06-22	15:07:54
'0896'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10173039',	 last => '10173039',	 list => '',  beginTime => '20090622.150754'}, # 	2009-06-22	15:07:54	2009-06-22	16:15:58
'0897'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10173048',	 last => '10173048',	 list => '',  beginTime => '20090622.161558'}, # 	2009-06-22	16:15:58	2009-06-22	16:46:02
'0898'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10173051',	 last => '10173055',	 list => '',  beginTime => '20090622.164602'}, # 	2009-06-22	16:46:02	2009-06-22	23:14:02
'0899'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10173077',	 last => '10173078',	 list => '',  beginTime => '20090622.231402'}, # 	2009-06-22	23:14:02	2009-06-23	00:42:25
'0900'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10173081',	 last => '10173085',	 list => '',  beginTime => '20090623.004225'}, # 	2009-06-23	00:42:25	2009-06-23	02:41:12
'0901'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10173087',	 last => '10173088',	 list => '',  beginTime => '20090623.024112'}, # 	2009-06-23	02:41:12	2009-06-23	03:52:09
'0902'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10173090',	 last => '10173090',	 list => '',  beginTime => '20090623.035209'}, # 	2009-06-23	03:52:09	2009-06-23	04:28:25
'0903'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10174001',	 last => '10174001',	 list => '',  beginTime => '20090623.042825'}, # 	2009-06-23	04:28:25	2009-06-23	06:28:56
'0904'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10174012',	 last => '10174013',	 list => '',  beginTime => '20090623.062856'}, # 	2009-06-23	06:28:56	2009-06-23	07:35:48
'0905'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10174016',	 last => '10174017',	 list => '',  beginTime => '20090623.073548'}, # 	2009-06-23	07:35:48	2009-06-23	09:05:51
'0906'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10174021',	 last => '10174028',	 list => '',  beginTime => '20090623.090551'}, # 	2009-06-23	09:05:51	2009-06-23	11:22:54
'0907'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10174031',	 last => '10174031',	 list => '',  beginTime => '20090623.112254'}, # 	2009-06-23	11:22:54	2009-06-23	13:36:53
'0908'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10174044',	 last => '10174045',	 list => '',  beginTime => '20090623.133653'}, # 	2009-06-23	13:36:53	2009-06-23	15:17:10
'0909'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10174048',	 last => '10174052',	 list => '',  beginTime => '20090623.151710'}, # 	2009-06-23	15:17:10	2009-06-23	20:52:28
'0910'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10174068',	 last => '10174068',	 list => '',  beginTime => '20090623.205228'}, # 	2009-06-23	20:52:28	2009-06-23	21:10:20
'0911'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10174071',	 last => '10174073',	 list => '',  beginTime => '20090623.211020'}, # 	2009-06-23	21:10:20	2009-06-23	22:53:04
'0912'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10174076',	 last => '10174076',	 list => '',  beginTime => '20090623.225304'}, # 	2009-06-23	22:53:04	2009-06-23	23:23:50
'0913'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10174078',	 last => '10174080',	 list => '',  beginTime => '20090623.232350'}, # 	2009-06-23	23:23:50	2009-06-24	01:49:54
'0914'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10174083',	 last => '10174083',	 list => '',  beginTime => '20090624.014954'}, # 	2009-06-24	01:49:54	2009-06-24	03:36:01
'0915'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10174093',	 last => '10174094',	 list => '',  beginTime => '20090624.033601'}, # 	2009-06-24	03:36:01	2009-06-24	04:06:48
'0916'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10175001',	 last => '10175001',	 list => '',  beginTime => '20090624.040648'}, # 	2009-06-24	04:06:48	2009-06-24	04:19:35
'0917'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10175004',	 last => '10175005',	 list => '',  beginTime => '20090624.041935'}, # 	2009-06-24	04:19:35	2009-06-24	05:14:16
'0918'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10175008',	 last => '10175014',	 list => '',  beginTime => '20090624.051416'}, # 	2009-06-24	05:14:16	2009-06-24	10:22:14
'0919'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10175019',	 last => '10175019',	 list => '',  beginTime => '20090624.102214'}, # 	2009-06-24	10:22:14	2009-06-25	03:26:46
'0920'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10175038',	 last => '10175038',	 list => '',  beginTime => '20090625.032646'}, # 	2009-06-25	03:26:46	2009-06-25	04:03:30
'0921'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10176001',	 last => '10176001',	 list => '',  beginTime => '20090625.040330'}, # 	2009-06-25	04:03:30	2009-06-25	07:48:02
'0922'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10176008',	 last => '10176008',	 list => '',  beginTime => '20090625.074802'}, # 	2009-06-25	07:48:02	2009-06-25	10:36:37
'0923'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10176016',	 last => '10176018',	 list => '',  beginTime => '20090625.103637'}, # 	2009-06-25	10:36:37	2009-06-25	11:58:53
'0924'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10176022',	 last => '10176022',	 list => '',  beginTime => '20090625.115853'}, # 	2009-06-25	11:58:53	2009-06-25	12:48:06
'0925'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10176025',	 last => '10176025',	 list => '',  beginTime => '20090625.124806'}, # 	2009-06-25	12:48:06	2009-06-25	13:35:05
'0926'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10176028',	 last => '10176028',	 list => '',  beginTime => '20090625.133505'}, # 	2009-06-25	13:35:05	2009-06-26	09:21:37
'0927'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10177014',	 last => '10177014',	 list => '',  beginTime => '20090626.092137'}, # 	2009-06-26	09:21:37	2009-06-26	09:47:25
'0928'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10177016',	 last => '10177019',	 list => '',  beginTime => '20090626.094725'}, # 	2009-06-26	09:47:25	2009-06-26	18:39:48
'0929'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10177055',	 last => '10177057',	 list => '',  beginTime => '20090626.183948'}, # 	2009-06-26	18:39:48	2009-06-26	20:26:50
'0930'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10177060',	 last => '10177061',	 list => '',  beginTime => '20090626.202650'}, # 	2009-06-26	20:26:50	2009-06-27	20:37:07
'0931'=> {trig=>'production2009_200Gev_nocal',	field => 'FF',	first=> '10178020',	 last => '10178021',	 list => '',  beginTime => '20090627.203707'}, # 	2009-06-27	20:37:07	2009-06-27	21:04:47	timestamp = production2009_200Gev_nocal_FF
'0932'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10178022',	 last => '10178022',	 list => '',  beginTime => '20090627.210447'}, # 	2009-06-27	21:04:47	2009-06-27	21:51:08	timestamp = production2009_200Gev_Single_FF
'0933'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10178026',	 last => '10178026',	 list => '',  beginTime => '20090627.215108'}, # 	2009-06-27	21:51:08	2009-06-27	22:30:36
'0934'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10178029',	 last => '10178029',	 list => '',  beginTime => '20090627.223036'}, # 	2009-06-27	22:30:36	2009-06-28	04:07:08
'0935'=> {trig=>'production2009_200Gev_noendcap',	field => 'FF',	first=> '10179001',	 last => '10179001',	 list => '',  beginTime => '20090628.040708'}, # 	2009-06-28	04:07:08	2009-06-28	05:23:47	timestamp = production2009_200Gev_noendcap_FF
'0936'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10179005',	 last => '10179010',	 list => '',  beginTime => '20090628.052347'}, # 	2009-06-28	05:23:47	2009-06-28	08:01:42	timestamp = production2009_200Gev_Single_FF
'0937'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10179018',	 last => '10179019',	 list => '',  beginTime => '20090628.080142'}, # 	2009-06-28	08:01:42	2009-06-28	09:05:10
'0938'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10179022',	 last => '10179022',	 list => '',  beginTime => '20090628.090510'}, # 	2009-06-28	09:05:10	2009-06-28	10:49:15
'0939'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10179031',	 last => '10179033',	 list => '',  beginTime => '20090628.104915'}, # 	2009-06-28	10:49:15	2009-06-28	12:43:36
'0940'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10179036',	 last => '10179036',	 list => '',  beginTime => '20090628.124336'}, # 	2009-06-28	12:43:36	2009-06-28	13:44:57
'0941'=> {trig=>'production2009_200Gev_nocal',	field => 'FF',	first=> '10179040',	 last => '10179041',	 list => '',  beginTime => '20090628.134457'}, # 	2009-06-28	13:44:57	2009-06-28	14:04:30	timestamp = production2009_200Gev_nocal_FF
'0942'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10179042',	 last => '10179045',	 list => '',  beginTime => '20090628.140430'}, # 	2009-06-28	14:04:30	2009-06-28	18:13:25	timestamp = production2009_200Gev_Single_FF
'0943'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10179059',	 last => '10179061',	 list => '',  beginTime => '20090628.181325'}, # 	2009-06-28	18:13:25	2009-06-28	19:49:37
'0944'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10179064',	 last => '10179065',	 list => '',  beginTime => '20090628.194937'}, # 	2009-06-28	19:49:37	2009-06-28	21:16:11
'0945'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10179072',	 last => '10179074',	 list => '',  beginTime => '20090628.211611'}, # 	2009-06-28	21:16:11	2009-06-28	23:10:13
'0946'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10179077',	 last => '10179077',	 list => '',  beginTime => '20090628.231013'}, # 	2009-06-28	23:10:13	2009-06-29	01:28:58
'0947'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10179085',	 last => '10179086',	 list => '',  beginTime => '20090629.012858'}, # 	2009-06-29	01:28:58	2009-06-29	02:23:43
'0948'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10179088',	 last => '10179088',	 list => '',  beginTime => '20090629.022343'}, # 	2009-06-29	02:23:43	2009-06-29	03:06:24
'0949'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10179096',	 last => '10179098',	 list => '',  beginTime => '20090629.030624'}, # 	2009-06-29	03:06:24	2009-06-29	04:18:50
'0950'=> {trig=>'production2009_200Gev_noendcap',	field => 'FF',	first=> '10180002',	 last => '10180002',	 list => '',  beginTime => '20090629.041850'}, # 	2009-06-29	04:18:50	2009-06-29	04:34:55	timestamp = production2009_200Gev_noendcap_FF
'0951'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10180003',	 last => '10180004',	 list => '',  beginTime => '20090629.043455'}, # 	2009-06-29	04:34:55	2009-06-29	05:34:07	timestamp = production2009_200Gev_Single_FF
'0952'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10180007',	 last => '10180007',	 list => '',  beginTime => '20090629.053407'}, # 	2009-06-29	05:34:07	2009-06-29	08:00:45
'0953'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10180020',	 last => '10180022',	 list => '',  beginTime => '20090629.080045'}, # 	2009-06-29	08:00:45	2009-06-29	09:32:45
'0954'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10180027',	 last => '10180030',	 list => '',  beginTime => '20090629.093245'}, # 	2009-06-29	09:32:45	2009-06-29	11:38:20
'0955'=> {trig=>'production2009_200Gev_noendcap',	field => 'FF',	first=> '10180034',	 last => '10180034',	 list => '',  beginTime => '20090629.113820'}, # 	2009-06-29	11:38:20	2009-06-30	04:43:08	timestamp = production2009_200Gev_noendcap_FF
'0956'=> {trig=>'production2009_200Gev_Single',	field => 'FF',	first=> '10181005',	 last => '10181005',	 list => '',  beginTime => '20090630.044308'}, # 	2009-06-30	04:43:08	2009-06-30	04:43:08	timestamp = production2009_200Gev_Single_FF
);
1;
