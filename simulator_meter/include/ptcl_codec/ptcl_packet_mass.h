#pragma once

#include <ptcl_codec/ptcl_packet.h>

class PTCL_CODEC_EXPORT ptcl_packet_mass : public ptcl_packet
{
public:
	ptcl_packet_mass(bool packet_type = false);
	virtual ~ptcl_packet_mass(void);

	virtual void reset();

	//��װ���ģ�������set_packet_buffer
	virtual void format_packet();

	//�������� ������set_packet_buffer
	//����ֵ >0:�������ĳɹ� 0:���ĳ��Ȳ��� <0:���ĸ�ʽ����
	virtual int parse_packet();
	
	//����ֵ >0:�������ĳɹ� 0:���ĳ��Ȳ��� <0:���ĸ�ʽ����
	virtual int parse_header();

	//����ֵ >0:�������ĳɹ� 0:���ĳ��Ȳ��� <0:���ĸ�ʽ����
	virtual int parse_header(unsigned char *buffer,int len_buffer);

	//�����ն��߼���ַ ���ձ���˳��
	virtual unsigned int get_device_addr();

	//���ر������к�
	virtual int get_frame_seq();

	//������վID
	virtual unsigned char get_host_id();

	//�߼���ַ
	void set_device_addr(unsigned short dev_addr);

	//��վ��ַ
	void set_host_id(unsigned char id);

	//֡���
	void set_frame_seq(unsigned char seq);

protected:
	//�̶�����ͷ��getר��
	struct get_frame_header_struct
	{
		unsigned short version;
		unsigned short length;
	};

	//����ͷ�ṹ��
#pragma pack(push, 1)
	struct frame_header_struct
	{
		unsigned short version;
		unsigned short src_port;
		unsigned short dest_port;
		unsigned short length;
	};
#pragma pack(pop)

	frame_header_struct *frame_header_;
	get_frame_header_struct *get_frame_header_;
	bool is_get_packet_;
	unsigned short reverse_value(unsigned short value);
};
