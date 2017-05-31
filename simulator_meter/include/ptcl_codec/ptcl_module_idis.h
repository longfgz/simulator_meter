#pragma once
#include <ptcl_codec/ptcl_module.h>
#include <ptcl_codec/ptcl_packet_sg.h>
#include <vector>


class PTCL_CODEC_EXPORT ptcl_module_idis : public ptcl_module
{
public:
	ptcl_module_idis(void);
	virtual ~ptcl_module_idis(void);

public:
	//Ӧ�ò㹦���붨��
	enum afn_code
	{
		AFN_ERROR_ACK					=	0x00, //��������Ӧ��
		AFN_SET_PARAM					=	0x04, //���ò���
		AFN_COMMAND						=	0x05, //��������
		AFN_READ_DATA					=	0x0C, //1�����ݻ������
		AFN_READ_DATA_HISTORY			=	0x0D, //2�����ݣ���ʷ���ݣ�
		AFN_CUSTOM                      =   0x20, //����
		AFN_CONCENTRATOR_GET_VERSION	=	0x43, //���������汾
		AFN_GET_DCU_PARAM				=	0xF1, //��ȡ����������
		AFN_SET_DCU_PARAM				=	0xF2, //���ü���������
		//�Զ��幦��������[0x21, 0x254],���ݲ�ͬ��Լ�Ĳ����ԣ����岻ͬ�Ĺ�����
	};

	typedef struct obis_struct
	{
		unsigned short class_id;
		unsigned char obis_code[6];
		unsigned char attribute_id;
	};

	typedef struct data_unit
	{
		unsigned char meter_asset_no[16];
		obis_struct os;
	};

	typedef struct data_unit_param
	{
		unsigned char meter_asset_no[16];
		obis_struct os;
		unsigned short length;
		unsigned char buffer[1024];
	};

	typedef struct req_history_data
	{
		data_unit du;
		unsigned int start_time;
		unsigned int end_time;
	};

	static ptcl_module_idis *get_instance();

	void format_packet_error_ack(ptcl_packet_sg *packet, int flag);

	int format_packet_with_param(ptcl_packet_sg *packet, int afn, std::vector<data_unit_param> &vec_item);
	void parse_packet_with_param(ptcl_packet_sg *packet, std::vector<data_unit_param> &vec_item);

	void format_packet_history_data(ptcl_packet_sg *packet, std::vector<req_history_data> &vec_item);
protected:
	static ptcl_module_idis *instance_;

	int format_data_unit_param(data_unit_param &dup, unsigned char *buffer);
	int parse_data_unit_param(data_unit_param &dup, unsigned char *buffer);

};

