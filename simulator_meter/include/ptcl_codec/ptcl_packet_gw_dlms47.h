#pragma once

#include <ptcl_codec/ptcl_packet_dlms47.h>
#define MAX_GATEWAY_LENGTH 64

class PTCL_CODEC_EXPORT ptcl_packet_gw_dlms47 : public ptcl_packet_dlms47
{

public:
	ptcl_packet_gw_dlms47(int packet_type = 1);
	ptcl_packet_gw_dlms47(ptcl_packet_dlms47& packet,std::string meter_no);
	~ptcl_packet_gw_dlms47();

	std::string get_physical_addr();
	unsigned int unpack_to_std_dlms47_data(unsigned char* output_data);
	virtual void reset();
	virtual void format_packet();

	//����ֵ >0:�������ĳɹ� 0:���ĳ��Ȳ��� <0:���ĸ�ʽ����
	virtual int parse_header(unsigned char *buffer,int len_buffer);
	virtual int parse_header();

//����ͷ�ṹ��
#pragma pack(push, 1)
	struct gateway_header_struct
	{
		unsigned char header_flag;	// 0xE6 or 0xE7
		unsigned char network_id;	// 0
		unsigned char addr_len;		
	};
#pragma pack(pop)

protected:
	gateway_header_struct *gateway_header_;

};
