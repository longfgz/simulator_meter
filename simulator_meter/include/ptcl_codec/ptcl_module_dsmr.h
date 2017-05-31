#pragma once

#include <ptcl_codec/ptcl_module.h>
#include <ptcl_codec/ptcl_packet_sg.h>
#include <vector>

class PTCL_CODEC_EXPORT ptcl_module_dsmr : public ptcl_module
{
protected:
	ptcl_module_dsmr(void);
	virtual ~ptcl_module_dsmr(void);
public:
	//Ӧ�ò㹦���붨��
	enum afn_code
	{
		AFN_CONFIRM						=	0x00, //ȷ�Ϸ���
		AFN_GET_REQUEST					=	0x01, //create�ظ�����
		AFN_CREATE_GET_RESPONSE			=	0x02, 
		AFN_SET_PARAM					=	0x04, //���ò���
		AFN_COMMAND						=	0x05, //��������
		AFN_READ_DATA_REALTIME			=	0x0C, //��1�����ݣ�ʵʱ���ݣ�
		AFN_READ_DATA_HISTORY			=	0x0D, //��2�����ݣ���ʷ���ݣ�
		
		AFN_DEL_REQUEST					=	0x0F,
	};
	typedef struct obis_struct
	{
		char class_id;
		char obis_code[6];
		char attribute_id;
	};

	typedef struct data_area_struct
	{
		char meter_asset_no[16];
		obis_struct os;
		char value[1024];
		int len_data;
	};
	
	static ptcl_module_dsmr *get_instance();

	//create request
	void format_create_history_data_request(ptcl_packet_sg *packet, std::vector<data_area_struct> & v_das);

	//create response
	void format_create_response(ptcl_packet_sg *packet, char *resource_id);

	//get request
	void format_get_request(ptcl_packet_sg *packet, char *resource_id);

	//get response
	void format_get_response(ptcl_packet_sg *packet, std::vector<data_area_struct> & v_das);

	//del
	void format_del_request(ptcl_packet_sg *packet, char *resource_id);

	//ȷ�ϣ�1 ���ϣ�0
	void format_confirm(ptcl_packet_sg *packet, int flag);


	
protected:
	static ptcl_module_dsmr *instance_;


};
