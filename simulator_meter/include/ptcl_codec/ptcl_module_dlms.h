#pragma once

#include <ptcl_codec/ptcl_module.h>
#include <ptcl_codec/ptcl_packet_hdlc.h>
#include <ptcl_codec/ptcl_cosem_dlms.h>

class PTCL_CODEC_EXPORT ptcl_module_dlms : public ptcl_module
{
protected:
	ptcl_module_dlms(void);
	virtual ~ptcl_module_dlms(void);

public:
	enum ctrl_code 
	{
		ctrl_code_snrm			= 0x93,//��½֡SNRM
		ctrl_code_disc          = 0x53,//�Ͽ�֡SNRM
		ctrl_code_ua            = 0x73,//��½ȷ��֡UA
	};

	enum class_id
	{
		ci_data		= 1,//���ݽӿ���
		ci_register = 3,//�Ĵ����ӿ���
		ci_extended = 4,//��չ�Ĵ����ӿ���
		ci_demand   = 5,//�����Ĵ����ӿ���
		ci_profile	= 7,//ͨ�ü��ӿ���
		ci_clock	= 8,//ʱ�ӽӿ���
	};
	static ptcl_module_dlms *get_instance();

	void format_packet_hdlc_connect(ptcl_packet_hdlc *packet,
		short int max_send_bytes = 1024,short int max_recv_bytes = 1024,
		int send_window = 1,int recv_window = 7);

	void format_packet_hdlc_disconnect(ptcl_packet_hdlc *packet);
	
	/*contextID = 11 
	  senderAcseRequirements = 1 */
	void format_packet_cosem_connect(ptcl_packet_hdlc *packet,char* psw);
	
	void format_packet_cosem_disConnect(ptcl_packet_hdlc *packet);

	void format_packet_cosem(ptcl_packet_hdlc *packet, int invokeid, int recv_seq);

	void fill_packet_cosem_get(ptcl_packet_hdlc *packet, short obis_class, char* obis, unsigned char attr_id);
	void fill_packet_cosem_get(ptcl_packet_hdlc *packet, char* obis, time_t start, time_t end);
	void fill_packet_cosem_next(ptcl_packet_hdlc *packet, unsigned int block_no);

	void format_packet_cosem_set(ptcl_packet_hdlc *packet,int last_recv_seq,short obis_class,char* obis);

	/*//snrm����,��������
	int format_packet_SNRM(unsigned char *xml,unsigned int device_addr,unsigned char *psw);

	//disc����,�Ͽ�����
	int format_packet_DISC(unsigned char *xml,unsigned int device_addr);

	//ua����,��ʾ�ظ�
	int format_packet_UA(unsigned char *xml,unsigned int device_addr);

	//dm����,��ʾ�յ�disc����ǰ�Ѿ��Ͽ�����
	int format_packet_DM(unsigned char *xml,unsigned int device_addr);

	//Ӧ�ò㽨������
	int format_packet_AARQ(unsigned char *xml,unsigned int device_addr);

	//Ӧ�ò����ӽ����ظ�
	int format_packet_AARE(unsigned char *xml,unsigned int device_addr, unsigned int host_id);

	//�ɼ���ʷ����
	int format_packet_history_data(unsigned char *xml,unsigned char *obis,unsigned int device_addr,
		time_t start_time,time_t end_time);*/

protected:
	static ptcl_module_dlms *instance_;
};