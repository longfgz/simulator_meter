#pragma once

#include <ptcl_codec/ptcl_module.h>
#include <ptcl_codec/ptcl_packet_in.h>

class PTCL_CODEC_EXPORT ptcl_module_in : public ptcl_module
{
public:
	ptcl_module_in(void);
	virtual ~ptcl_module_in(void);


	enum event_type
	{
		et_subscription = 0x01,
		et_route		= 0x02
	};

	enum event_sub_type
	{
		//et_subscription
		est_sync_arch_req		   = 0xe1,
		est_sync_arch_rsp		   = 0xe2,

		est_alarm_active_req2	   = 0xef,

		est_login_req              = 0xf1,
		est_login_rsp              = 0xf2,
		est_logout_req             = 0xf3,
		est_logout_rsp             = 0xf4,
		est_heart_beat_req         = 0xf5,
		est_heart_beat_rsp         = 0xf6,
		est_repair_req             = 0xf7,
		est_repair_rsp             = 0xf8,
		est_reroot_req             = 0xf9,
		est_reroot_rsp             = 0xfa,
		est_dc_data_req            = 0xfb,
		est_dc_data_rsp            = 0xfc,
		est_alarm_active_req	   = 0xfd,
		est_alarm_active_rsp	   = 0xfe,

		est_alarm	               = 0xff, //�����ϱ��ĸ澯



	};

	//<!-- ID��Χ 1:router 2-8:fee 9-15:collection 16-19:alarm 20:web 21:proxy 22...app -->

	//<!-- ���� 1:terminal 2:router 3:alarm 4:fee 5:app 6:collection -->
	enum object_type
	{
		ot_terminal         = 0x01,
		ot_router           = 0x02,
		ot_alarm            = 0x03,
		ot_fee              = 0x04,
		ot_app              = 0x05,//ǰ�û�Ӧ�á�web��proxy
		ot_collection       = 0x06,
		ot_meter			= 0x08,//����router�ӿڹ淶�ĵ���ot_alarm����Ϊ0x07�ˣ���˸ĳ�0x08
	};

	enum ptcl_class_id
	{
		pci_gd       =   1,
		pci_sg       =   2,
		pci_719      =   3,
		pci_102      =   4,
		pci_dlms     =   5,
		pci_gx102	 =   6,
		//pci_eq		 =   7,
		pci_jc102	 =	 7,
		pci_ffc102	 =	 8,
		pci_hl102	 =	 9,
		pci_cq102	 =	 10,
		pci_ansi	 =	 11,
	};

	enum ptcl_id
	{
		pi_gd_vip	=	1001001,
		pi_gd_pb	=	1001002,
		pi_gd_dy	=	1001003,
		pi_sg_04	=	1002004,
		pi_719		=	1003005,
		pi_719_qtr  =	1003008,
		pi_102		=	1004006,
		pi_dlms		=	1105009,
		pi_gx102	=	1006007,
		pi_jc102	=	1007015,
		pi_jc102_hh	=	1007016,
		pi_ffc102	=	1008010,
		pi_hl102	=	1009011,
		pi_dsmr		=	1005019,
		pi_cq102	=	1010020,
		pi_idis		=	1005020,
		pi_mbus		=	1205001,
		pi_ansi		=	1111001  // 1111001,
	};



	static ptcl_module_in *get_instance();


	////��·��� ���� ��½/////////////////////////////////////////////////////////
	void format_packet_connect_test(ptcl_packet_in *packet,
									unsigned int sender_id,unsigned char sender_type,
									unsigned int receiver_id,unsigned char receiver_type,
									event_sub_type est);
	/*
	pPacket: ����Ҫ��д����
			 ���ҷ�����װ�õı���
	test_type:��sub_msg_type
	*/

	////����ת������/////////////////////////////////////////////////////////
	void format_packet_route(	ptcl_packet_in *packet,
								unsigned int sender_id,unsigned char sender_type,
								unsigned int transfer_id,unsigned char transfer_type,
								unsigned int receiver_id,unsigned char receiver_type,
								int ptcl_id,unsigned char seq,unsigned char *buffer,int len,
								unsigned char event_sub_type = 0);
	/*
	pPacket: ��д�ն�ID
			 ���ҷ�����װ�õı���
	buffer:��Ҫת���ı�������
	len:��Ҫת���ı��ĳ���
	*/

	void format_packet_dc_data(ptcl_packet_in *packet,
										   unsigned int sender_id,unsigned char sender_type,
										   unsigned char *buffer,int len);
	/*
	pPacket: ����Ҫ��д����
			 ���ҷ�����װ�õı���
	buffer:��������
	len:�������ݳ���
	*/

	void format_packet_rcs(ptcl_packet_in *packet,
										 unsigned int sender_id,unsigned char sender_type,
										 unsigned int transfer_id,unsigned char transfer_type,
										 unsigned int receiver_id,unsigned char receiver_type,
										 int ptcl_id,unsigned char seq,unsigned char *buffer,int len);

	void format_packet_dlms47_alarm(ptcl_packet_in *packet,
										 unsigned int sender_id,unsigned char sender_type,
										 unsigned int transfer_id,unsigned char transfer_type,
										 unsigned int receiver_id,unsigned char receiver_type,
										 int ptcl_id,unsigned char seq,unsigned char *buffer,int len);

	void format_packet_dlms47_alarm2(ptcl_packet_in *packet, 
									unsigned int sender_id,unsigned char sender_type,
									unsigned int transfer_id,unsigned char transfer_type,
									unsigned int receiver_id,unsigned char receiver_type,
									int ptcl_id,unsigned char seq,unsigned char *buffer,int len);

protected:
	static ptcl_module_in *instance_;
};
