#pragma once

#include <ptcl_codec/ptcl_module.h>
#include <ptcl_codec/ptcl_packet_sg.h>

class PTCL_CODEC_EXPORT ptcl_module_sg : public ptcl_module
{
protected:
	ptcl_module_sg(void);
	virtual ~ptcl_module_sg(void);
public:
	//Ӧ�ò㹦���붨��
	enum afn_code
	{
		AFN_ACK						=	0x00, //ȷ�� ����
		AFN_RESET					=	0x01, //��λ
		AFN_CONNECT_TEST			=	0x02, //��·�ӿڼ��(��½,����,ע��)
		AFN_RELAY_STATION_COMMAND	=	0x03, //�м�վ����
		AFN_SET_PARAM				=	0x04, //���ò���
		AFN_COMMAND					=	0x05, //��������
		AFN_ID_PSW					=	0x06, //���ȷ�� �� ����Э��
		AFN_READ_PARAM				=	0x0A, //��ȡ����
		AFN_READ_DATA_REALTIME		=	0x0C, //��1�����ݣ�ʵʱ���ݣ�
		AFN_READ_DATA_HISTORY		=	0x0D, //��2�����ݣ���ʷ���ݣ�
		AFN_READ_DATA_EVENT			=	0x0E, //��3�����ݣ��¼����ݣ�
		AFN_FILE_TRANS				=	0x0F, //�ļ�����
		AFN_DATA_TRANSMIT			=	0x10, //����ת��
	};

	//���ݵ�Ԫ
	struct pnfn_data
	{
		int pn;
		int fn;
	};


	static int format_pnfn(pnfn_data *pnfn,unsigned char *buffer);
	static int parse_pnfn(unsigned char *buffer,pnfn_data *pnfn);

	//�¼�������
	struct ec_data
	{
		unsigned char important_ec;//��Ҫ�¼�������
		unsigned char generic_ec;//��ͨ�¼�������
	};
	//�¼�������
	static int format_ec(ec_data *ec,unsigned char *buffer);
	static int parse_ec(unsigned char *buffer,ec_data *ec);

	//ʱ���ʶ
	struct tp_data
	{
		unsigned char pfc;//����֡֡��ż�����
		unsigned char sec;//��
		unsigned char min;//��
		unsigned char hour;//ʱ
		unsigned char day;//��
		unsigned char time_out;//��ʱʱ��
	};
	//ʱ���ǩ
	static int format_tp(tp_data *tp,unsigned char *buffer);
	static int parse_tp(unsigned char *buffer,tp_data *tp);

	//���ݵ�Ԫ�ṹ
	struct pnfn_struct
	{
		unsigned char pn[2];
		unsigned char fn[2];
	};

	int get_aux_len();

	static ptcl_module_sg *get_instance();

	////����������///////////////////////////////////////////////////////////////////////
	struct pnfn_data_uint
	{
		pnfn_data pnfn;
		unsigned char data_buffer[1024];
		int len_data;
	};
	void format_packet_read_data_history(	ptcl_packet_sg *packet,
											pnfn_data_uint* v_data_uint,int count_data_uint,
											tp_data *tp = NULL);
	/*
	packet: ֻ��Ҫ��д���ֳ�Ա �ն˵�ַ
			 ���ҷ�����װ�õı���
	v_data_uint:���ݵ�Ԫ����
	count_data_uint:���ݵ�Ԫ����
	*/


	//ȷ��֡//////////////////////////////////////////////////////////////////////////////
	void format_packet_confirm_frame(	ptcl_packet_sg *packet);
	/*
	packet: ֻ��Ҫ��д���ֳ�Ա �ն˵�ַ
			 ���ҷ�����װ�õı���
	*/

	//��ʱ//////////////////////////////////////////////////////////////////////////////
	void format_packet_set_param(	ptcl_packet_sg *packet,
									pnfn_data_uint* v_data_uint,
									int count_data_uint,
									unsigned char *psw,
									tp_data *tp = NULL
									);
	/*
	packet: ֻ��Ҫ��д���ֳ�Ա �ն˵�ַ
			 ���ҷ�����װ�õı���
	*/
	/////д����//////////////////////////////////////////////////////////////////////////////
	void format_packet_write_param(	ptcl_packet_sg *packet,
									pnfn_data_uint* v_data_uint,
									int count_data_uint,
									unsigned char *psw,
									tp_data *tp = NULL
									);
	/*
	packet: ֻ��Ҫ��д���ֳ�Ա �ն˵�ַ
			 ���ҷ�����װ�õı���
	*/
	//����ת��//////////////////////////////////////////////////////////////////////////////
	void format_packet_transmit(	ptcl_packet_sg *packet,
									pnfn_data_uint &data_uint,
									unsigned char *psw,
									tp_data *tp = NULL
									);
	/*
	packet: ֻ��Ҫ��д���ֳ�Ա �ն˵�ַ
			 ���ҷ�����װ�õı���
	*/
	//�����泭//////////////////////////////////////////////////////////////////////////////
	void format_packet_rand_data(
									ptcl_packet_sg *packet, 
									pnfn_data_uint* v_data_uint,
									int count_data_uint,
									tp_data *tp = NULL);
	/*
	packet: ֻ��Ҫ��д���ֳ�Ա �ն˵�ַ
			 ���ҷ�����װ�õı���
	*/
	
	//response for event push
	void format_packet_confirm_event_push(	ptcl_packet_sg *packet, 
											unsigned char afn, 
											unsigned char seq, 
											pnfn_data_uint &data_uint,
											tp_data *tp = NULL
											);
	

protected:
	static ptcl_module_sg *instance_;


};
